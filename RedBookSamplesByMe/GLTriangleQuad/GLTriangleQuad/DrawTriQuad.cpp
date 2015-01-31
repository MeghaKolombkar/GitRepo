#include"WindowRender.h"

LRESULT CALLBACK MyWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

HRESULT MyWindow::createWindow(HINSTANCE hInst)
{
	m_wndClass.cbSize = sizeof(WNDCLASSEX);
	m_wndClass.hInstance = hInst;
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.lpfnWndProc = MyWindow::WndProc;
	m_wndClass.lpszClassName = L"MyOpenGLClass";
	m_wndClass.hCursor = LoadCursor(hInst, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndClass.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	m_wndClass.hIconSm = LoadIcon(hInst, IDI_APPLICATION);
	m_wndClass.lpszMenuName = NULL;

	if (!RegisterClassEx(&m_wndClass))
		E_FAIL;

	m_hWnd = CreateWindow(L"MyOpenGLClass",
		L"TriangleQuad",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);
	ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
	Renderer *pRenderer = new Renderer();
	pRenderer->initGL(m_hWnd);
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message)
			break;
		pRenderer->render();
		SwapBuffers(pRenderer->getDC());
	}
	return S_OK;
}

void Renderer::initGL(HWND hWnd)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	pfd.nSize = sizeof(pfd);
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	m_hDC = ::GetDC(hWnd);
	iFormat = ChoosePixelFormat(m_hDC, &pfd);
	::SetPixelFormat(m_hDC, iFormat, &pfd);
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);
}
void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glFlush();
}

HDC Renderer::getDC() const
{
	return m_hDC;
}


MyWindow::MyWindow() : m_hWnd(NULL), m_Renderer(NULL)
{}

MyWindow::~MyWindow()
{
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
	MyWindow *pMyWin = new MyWindow();
	pMyWin->createWindow(hInstance);
	
	return 0;
}