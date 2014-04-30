#ifndef HEADER_FILE_OPENGLHELPER
#define HEADER_FILE__OPENGLHELPER

#ifdef _WIN32 /*windows*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

extern HDC			hDC;		// Private GDI Device Context
extern HGLRC		hRC;		// Permanent Rendering Context
extern HWND			hWnd;		// Holds Our Window Handle
extern HINSTANCE	hInstance;		// Holds The Instance Of The Application

#else /*UNIX*/

#include <GL/glut.h>    	// Header File For The GLUT Library
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library
#include <unistd.h>     	// Header file for sleeping.
#include <stdio.h>     	 	// Header file for standard file i/o.
#include <stdlib.h>     	// Header file for malloc/free.

#endif



struct Point3D
{
	GLdouble X;
	GLdouble Y;
	GLdouble Z;
};

typedef struct													// Create A Structure
{
	GLubyte	*imageData;											// Image Data (Up To 32 Bits)
	GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	width;												// Image Width
	GLuint	height;												// Image Height
	GLuint	texID;												// Texture ID Used To Select A Texture
} TextureImage;													// Structure Name

extern GLfloat glSphereVertex[12][3];
extern GLushort glSphereElementsArray[20][3];


extern bool	keys[256];			// Array Used For The Keyboard Routine
extern bool	active;		// Window Active Flag Set To TRUE By Default
extern bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default

extern GLsizei glWidth;
extern GLsizei glHeight;

extern int glMouseX;
extern int glMouseY;

extern const unsigned char font_tga_data[];

extern int (*onResizeGL)(GLsizei width, GLsizei height);
extern int (*onInitGL)(void);
extern int (*onDrawGL)(void);
extern int (*onDrawGLTargets)(bool isselectmode);
extern int (*onDrawGLOrtho)(void);
extern int (*onKillGL)(void);
extern int (*onKeyUP)(bool allkeys[256],int key);
extern int (*onKeyDOWN)(bool allkeys[256],int key);
extern int (*onActiveChange)(bool act);
extern int (*onMouseMove)(int x,int y,int dx,int dy);

extern int (*onMouseButton)(uint	uMsg);

int Selection(int mouse_x, int mouse_y);
Point3D GetOGLPos(int x, int y);
Point3D GetWPos(Point3D p);

#ifdef _WIN32 /*windows*/
int StartGL(		LPWSTR WindowTxt,
					int width,
					int height,
					bool fullscr
			);
#else /*UNIX*/
int StartGL(		char* WindowTxt,
					int width,
					int height,
					bool fullscr
			);
#endif


void BuildFont(void);
GLvoid glPrint(GLint x, GLint y, const char *string, ...);
bool LoadTGA(TextureImage *texture, char *filename);
void glRenderSphere(float size);

#endif

