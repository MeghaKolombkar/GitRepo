#include"MainWindow.h"

/* this function is kept static  as a C function which has no this pointer.
*/
LRESULT  CALLBACK MyWindow::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

HRESULT MyWindow::createMyWindow(HINSTANCE hInstance)
{
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MyWindow::WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = TEXT("MyClass");
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	
	if (!RegisterClassEx(&wndClass))
		return E_FAIL;

	hWnd = CreateWindow(L"MyClass",
		L"MyWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
		
	ShowWindow(hWnd, 5);
	m_rc = new Renderer();
	m_rc->initGL(hWnd);
	HDC hDC = m_rc->getDC();
	while (1)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message)
			break;
		m_rc->render();
		SwapBuffers(hDC);
	}
	return S_OK;
}


MyWindow::MyWindow() :hWnd(NULL)
{

}

MyWindow::~MyWindow()
{

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
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glFlush();
}

HDC Renderer::getDC() const
{
	return m_hDC;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
	MyWindow *mywin = new MyWindow();
	mywin->createMyWindow(hInst);

	return(0);
}

