Must Read
opengl starts rendering at O.  
Any method we apply, like glTranslate, glRotate, glLookAt happens with respect to previous method.  
GL keeps a transformations matrix, Pnew = M * P, resulting in the new coordinates of the point being rendered.  
GL function "glLoadIndentity()" resets M back to Identity matrix, ie default params.  
GL function "glPushMatrix()" and "glPopMatrix()" create a new copy of current matrix and push to stack. Hence the translate and 
rotation happens between this is temporary and only for that block.

See: https://stackoverflow.com/questions/628796/what-does-glloadidentity-do-in-opengl
