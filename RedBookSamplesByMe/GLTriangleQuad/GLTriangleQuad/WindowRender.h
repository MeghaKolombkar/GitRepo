
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

//Class is used to render 
class Renderer
{
	HGLRC m_hRC;
	HDC m_hDC;
public: 
	Renderer() :m_hDC(NULL), m_hRC(NULL){}
	~Renderer(){}
	void initGL(HWND);
	void render();
	HDC getDC() const;
};