#include<Windows.h>
#include <gl\GL.h>

class Renderer;

class MyWindow
{
	HWND hWnd;
	WNDCLASSEX wndClass;
	MSG msg;
	Renderer *m_rc;
public:
	MyWindow();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT createMyWindow(HINSTANCE);
	~MyWindow();
};

class Renderer
{
private:
	HDC m_hDC;
	HGLRC m_hRC;
public:
	Renderer(){}
	~Renderer(){}
	void initGL(HWND);
	HDC getDC() const;
	void render();
};