/* LIBRARY:   ImageIO Library v0.13
 * 
 * FILE:      imageio.cpp
 *
 * COPYRIGHT: Copyright (c) 2003-2004 Adrien Treuille
 * 
 * AUTHORS:   Adrien Treuille (treuille [AT] cs [DOT] washington [DOT] edu)
 *
 * LICENSE:   The ImageIO Library is supplied "AS IS".  The Authors
 *            disclaim all warranties, expressed or implied,
 *            including, without limitation, the warranties of
 *            merchantability and of fitness for any purpose. 
 *            The Authors assume no liability for direct, indirect,
 *            incidental, special, exemplary, or consequential
 *            damages, which may result from the use of the ImageIO
 *            Library, even if advised of the possibility of such
 *            damage.
 *
 *            Permission is hereby granted to use, copy, modify,
 *            and distribute this source code, or portions hereof,
 *            for any purpose, without fee, for non-commercial
 *            purposes. All rights reserved for commercial uses of
 *            this source code.
 */
#include<string.h>
#include "imageio.h"

// ***** generic internal functions ***** //

// Call this function if there was an error.
unsigned char *_loadImgError(int *width, int *height) {
  *width = *height = -1;
  return 0;
}

// Returns true iff the string s ends with postfix
bool _endsWith(char *s, char *postfix) {
  int sLen = strlen(s);
  int postfixLen = strlen(postfix);
  if (postfixLen > sLen)
    return false;
  else
    return (!strcmp(s + sLen - postfixLen, postfix));
}

// ***** tiff internal functions ***** //

unsigned char *_loadImageRGBAtiff(char *fileName, int *width, int *height) {
  unsigned char *returnBuffer = 0; // will be nonzero only on success

  TIFF* tif = TIFFOpen(fileName, "r");
  if (!tif)

    return _loadImgError(width, height);

  // figure out dimensions
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  int numPixels = (*width) * (*height);

  // allocate the *internal* raster
  int numBytes = numPixels * sizeof (uint32);
  uint32* internalBuffer = (uint32*) _TIFFmalloc(numBytes);
  if (!internalBuffer)
    return _loadImgError(width, height);

  // read the image
  if (!TIFFReadRGBAImage(tif, *width, *height, internalBuffer, 0))
    return _loadImgError(width, height);

  // allocate the external raster
  returnBuffer = (unsigned char *) malloc(numBytes);
  if (!returnBuffer)
    return _loadImgError(width, height);

  // copy
  memcpy(returnBuffer, internalBuffer, numBytes);

  // deallocate stuff
  _TIFFfree(internalBuffer); 
  TIFFClose(tif); 

  // return the return buffer
  return returnBuffer;
}

bool _saveImageRGBAtiff(char *fileName, unsigned char *buffer, int width, int height) {
  // create the output image
  TIFF *out= TIFFOpen(fileName, "w");
  int sampleperpixel = 4;                                         // indicates RGBA
  bool success = true;

  // set appropriate tags
  TIFFSetField (out, TIFFTAG_IMAGEWIDTH, width);                  // set the width of the image
  TIFFSetField(out, TIFFTAG_IMAGELENGTH, height);                 // set the height of the image
  TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, sampleperpixel);     // set number of channels per pixel
  TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);                    // set the size of the channels
  TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);    // set the origin of the image.
  TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

  tsize_t linebytes = sampleperpixel * width;     // length in memory of one row of pixel in the image.
  unsigned char *lineBuf = NULL;                  // the row itself

  //    Allocating memory to store the pixels of current row
  if (TIFFScanlineSize(out) == linebytes)
    lineBuf =(unsigned char *)_TIFFmalloc(linebytes);
  else
    lineBuf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(out));

  // We set the strip size of the file to be size of one row of pixels
  TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, width*sampleperpixel));

  //Now writing image to the file one strip at a time
  for (uint32 row = 0; row < height; row++) {
    memcpy(lineBuf, &buffer[(height - row - 1) * linebytes], linebytes);
    if (TIFFWriteScanline(out, lineBuf, row, 0) < 0) {
      success = false;
      break;
    }
  }

  TIFFClose(out);
  if (lineBuf)
    _TIFFfree(lineBuf);

  return success;
}

// ***** png related internal functions ***** //

unsigned char *_loadImageRGBApng(char *fileName, int *width, int *height) {
  // open the file
  FILE *fp = fopen(fileName, "rb");
  if (!fp)
    return _loadImgError(width, height);

  // read the header
  const int HEADER_LENGTH = 8;
  png_byte header[HEADER_LENGTH];
  fread(header, 1, HEADER_LENGTH, fp);
  if (png_sig_cmp(header, 0, HEADER_LENGTH))
    return _loadImgError(width, height);

  // try to create the loading structures
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if (!png_ptr) {
    fclose(fp);
    return _loadImgError(width, height);
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp) 0, (png_infopp) 0);
    fclose(fp);
    return _loadImgError(width, height);
  }

  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
    fclose(fp);
    return _loadImgError(width, height);
  }

  //if (setjmp(png_ptr->jmpbuf)) {
  if (setjmp(png_jmpbuf(png_ptr))){ //png later version
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return _loadImgError(width, height);
  }

  // start the io
  png_init_io(png_ptr, fp);

  // indicate that we have already read some of the hearder
  png_set_sig_bytes(png_ptr, HEADER_LENGTH);

  // read the image info, get some info
  png_read_info(png_ptr, info_ptr);
  *width = png_get_image_width(png_ptr, info_ptr);
  *height = png_get_image_height(png_ptr, info_ptr);
  int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  
  // force the image into RGBA, 8 bits per channel
  if (color_type != PNG_COLOR_TYPE_RGBA)
    png_set_expand(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);
  if (bit_depth < 8)
    png_set_packing(png_ptr);
  else if (bit_depth == 16)
    png_set_strip_16(png_ptr);
  if (color_type != PNG_COLOR_TYPE_RGBA)
    png_set_filler(png_ptr, 255, PNG_FILLER_AFTER);  
  png_read_update_info(png_ptr, info_ptr);

  // make sure we're actually in rgba mode
  if (png_get_rowbytes(png_ptr, info_ptr) != ((*width) * 4)) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return _loadImgError(width, height);
  }

  // finally, read the file
  unsigned char *buffer = (unsigned char *) malloc((*width) * (*height) * 4);
  png_bytep row_pointers[*height];
  for (int y = 0 ; y < (*height) ; y++)
    row_pointers[y] = (png_byte *) (buffer + ((*height) - 1 - y) * (*width) * 4);
  png_read_rows(png_ptr, row_pointers, 0, (long unsigned int) (*height));

  // deallocate memory and return
  fclose(fp);
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  return buffer;
}

bool _saveImageRGBApng(char *fileName, unsigned char *buffer, int width, int height) {
  // open the file
  FILE *fp = fopen(fileName, "wb");
  if (!fp)
    return false;

  // create the needed data structures
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if (!png_ptr) {
    fclose(fp);
    return false;
  }
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, (png_infopp) 0);
    return false;
  }

  // do the setjmp thingy
  //if (setjmp(png_ptr->jmpbuf)) {
  if (setjmp(png_jmpbuf(png_ptr))){ //png later version
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  // set up the io
  png_init_io(png_ptr, fp);
  
  // write the header
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, 
	       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  png_set_flush(png_ptr, 10);

  // write the image
  png_bytep row_pointers[height];
  for (int y = 0 ; y < height ; y++)
    row_pointers[y] = (png_byte *) (buffer + (height - 1 - y) * width * 4);
  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, info_ptr);
  
  // clean up memory, and finish
  fclose(fp);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  return true;
}

// ***** external functions ***** //

// Sets tbe width and height to the appropriate values and mallocs
// a char *buffer loading up the values in row-major, RGBA format.
// The memory associated with the buffer can be deallocated with free().
// If there was an error reading file, then 0 is returned, and
// width = height = -1.
unsigned char *loadImageRGBA(char *fileName, int *width, int *height) {
  if (_endsWith(fileName, ".tif") || _endsWith(fileName, ".tiff"))
    return _loadImageRGBAtiff(fileName, width, height);
  else if (_endsWith(fileName, ".png"))
    return _loadImageRGBApng(fileName, width, height);
  else
    return _loadImgError(width, height);
}

// Saves image given by buffer with specicified with and height
// to the given file name, returns true on success, false otherwise.
// The image format is RGBA.
bool saveImageRGBA(char *fileName, unsigned char *buffer, int width, int height) {
  if (_endsWith(fileName, ".tif") || _endsWith(fileName, ".tiff"))
    return _saveImageRGBAtiff(fileName, buffer, width, height);
  else if (_endsWith(fileName, ".png"))
    return _saveImageRGBApng(fileName, buffer, width, height);
  else
    return false;
}

//added by Tong
void save_image( char *n1, int x0, int y0, int width, int height )
{
  //  int width, height;
  //  char *n1 = "lit_sphere.png";
  unsigned char *myImgBuffer; 
  //  width = 380;
  //height = 380;
  myImgBuffer = ( unsigned char *) malloc( 4 * width * height );
  glReadPixels( x0, y0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, myImgBuffer);
  saveImageRGBA( n1, myImgBuffer, width, height);
}

void load_image( char *fname, int x0, int y0  )
{
  int width, height;

  unsigned char *ibuffer = _loadImageRGBApng( fname, &width, &height);

  glRasterPos2i( x0, y0 );
  glDrawPixels(  width, height, GL_RGBA, GL_UNSIGNED_BYTE, ibuffer);

}
