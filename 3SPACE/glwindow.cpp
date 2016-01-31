/* An example of the minimal Win32 & OpenGL program.  It only works in
   16 bit color modes or higher (since it doesn't create a
   palette). */


#include <windows.h>			/* must include this before GL/gl.h */
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */
#include <stdio.h>


double x,y,z,yr,xr,timer_ms;
//int zr;
int x_pp,y_pp;
//static GLuint texName;
//static GLubyte texture[64][64][4]; // not used..at least I don't think
int tex1,tex2,tex3;


HDC hDC;

void
display()
{
    //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	//glBindTexture(GL_TEXTURE_2D,texName);
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xr,1,0,0);
	glRotatef(yr,0,1,0);
	glTranslatef(x,0,z);
	//glLoadIdentity();
	glPushMatrix();
	//glLoadIdentity();
	//glRotatef(45,0,1,0);
	glTranslatef(0,-25,-50);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex1);
	glBegin(GL_POLYGON);
	 glColor3f(0,50,0);
	 glTexCoord2f (0,0);
	 glVertex3f(-100,50,0);
	 glTexCoord2f (0,5);
	 glVertex3f(-100,0,0);
	 glTexCoord2f (15,5);
	 glVertex3f(100,0,0);
	 glTexCoord2f (15,0);
	 glVertex3f(100,50,0);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(50,-25,0);
	glRotatef(-90,0,1,0);
	glBegin(GL_POLYGON);
	 glColor3f(50,0,0);
	 glTexCoord2f (0,0);
	 glVertex3f(-100,50,0);
	 glTexCoord2f (0,5);
	 glVertex3f(-100,0,0);
	 glTexCoord2f (15,5);
	 glVertex3f(100,0,0);
	 glTexCoord2f (15,0);
	 glVertex3f(100,50,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(0,-25,50);
	glRotatef(180,0,1,0);
	glBegin(GL_POLYGON);
	 glTexCoord2f (0,0);
	 glVertex3f(-100,50,0);
	 glTexCoord2f (0,5);
	 glVertex3f(-100,0,0);
	 glTexCoord2f (15,5);
	 glVertex3f(100,0,0);
	 glTexCoord2f (15,0);
	 glVertex3f(100,50,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(-50,-25,0);
	glRotatef(90,0,1,0);
	glBegin(GL_POLYGON);
	 glTexCoord2f (0,0);
	 glVertex3f(-100,50,0);
	 glTexCoord2f (0,5);
	 glVertex3f(-100,0,0);
	 glTexCoord2f (15,5);
	 glVertex3f(100,0,0);
	 glTexCoord2f (15,0);
	 glVertex3f(100,50,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-25,0);
    glRotatef(-90,1,0,0);
	glBindTexture(GL_TEXTURE_2D,tex2);
	glBegin(GL_POLYGON);
     glTexCoord2f (0,0);
	 glVertex3f(-50,50,0);
	 glTexCoord2f (0,1);
	 glVertex3f(-50,-50,0);
	 glTexCoord2f (1,1);
	 glVertex3f(50,-50,0);
	 glTexCoord2f (1,0);
	 glVertex3f(50,50,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,25,0);
    glRotatef(90,1,0,0);
	//glBindTexture(GL_TEXTURE_2D,tex3);
	glBegin(GL_POLYGON);
     glTexCoord2f (0,0);
	 glVertex3f(-50,50,0);
	 glTexCoord2f (0,10);
	 glVertex3f(-50,-50,0);
	 glTexCoord2f (10,10);
	 glVertex3f(50,-50,0);
	 glTexCoord2f (10,0);
	 glVertex3f(50,50,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glFlush();
	SwapBuffers(hDC);
}


LONG WINAPI
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    static PAINTSTRUCT ps;

    switch(uMsg) {
    case WM_PAINT:
	display();
	BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
	return 0;

    case WM_SIZE:
	glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
	PostMessage(hWnd, WM_PAINT, 0, 0);
	return 0;

    case WM_CHAR:
	switch (wParam) {
	case 27:			/* ESC key */
	    PostQuitMessage(0);
		break;
	default:
		display();
	}
	return 0;

    case WM_CLOSE:
	PostQuitMessage(0);
	return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam); 
} 

HWND
CreateOpenGLWindow(char* title, int x, int y, int width, int height, 
		   BYTE type, DWORD flags)
{
    int         pf;
    HDC         hDC;
    HWND        hWnd;
    WNDCLASS    wc;
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;

    /* only register the window class once - use hInstance as a flag. */
    if (!hInstance) {
	hInstance = GetModuleHandle(NULL);
	wc.style         = CS_OWNDC;
	wc.lpfnWndProc   = (WNDPROC)WindowProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc)) {
	    MessageBox(NULL, "RegisterClass() failed:  "
		       "Cannot register window class.", "Error", MB_OK);
	    return NULL;
	}
    }

    hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW |
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			x, y, width, height, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
	MessageBox(NULL, "CreateWindow() failed:  Cannot create a window.",
		   "Error", MB_OK);
	return NULL;
    }

    hDC = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
    pfd.iPixelType   = type;
    pfd.cColorBits   = 32;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
	MessageBox(NULL, "ChoosePixelFormat() failed:  "
		   "Cannot find a suitable pixel format.", "Error", MB_OK); 
	return 0;
    } 
 
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
	MessageBox(NULL, "SetPixelFormat() failed:  "
		   "Cannot set format specified.", "Error", MB_OK);
	return 0;
    } 

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

//    ReleaseDC(hDC, hWnd);

    return hWnd;
}    

int APIENTRY
WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
    HDC hDC;				/* device context */
    HGLRC hRC;				/* opengl context */
    HWND  hWnd;				/* window */
    MSG   msg;				/* message */

    hWnd = CreateOpenGLWindow("Win32 Exp..", 0, 0, 640, 480, PFD_TYPE_RGBA, 0);
    if (hWnd == NULL)
	exit(1);

    hDC = GetDC(hWnd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    ShowWindow(hWnd, nCmdShow);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,800/600,1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

    while(GetMessage(&msg, hWnd, 0, 0)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    wglMakeCurrent(NULL, NULL);
    //ReleaseDC(hDC, hWnd);
    wglDeleteContext(hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}

