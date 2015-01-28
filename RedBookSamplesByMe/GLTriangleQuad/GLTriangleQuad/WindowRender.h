
#include<Windows.h>
#include<gl\GL.h>

class Renderer;

class MyWindow
{
	HWND m_hWnd;
	WNDCLASSEX m_wndClass;
	MSG msg;
	Renderer *m_Renderer;
public:
	MyWindow();
	~MyWindow();
	HRESULT createWindow(HINSTANCE);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

class Renderer
{
	HGLRC m_hglRC;
	HDC m_hDC;
public: 
	void initGL(HWND);
	void render();
};