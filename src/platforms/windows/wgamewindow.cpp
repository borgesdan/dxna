#include "wgamewindow.hpp"

namespace dxna {
	WindowsGameWindow::WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc) : hinstance(hinstance), wndproc(winproc) {
	}
	
	WindowsGameWindow::WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc, int clientWidth, int clientHeigth) :
		hinstance(hinstance), wndproc(winproc),
		currentClientWidth(clientWidth), currentClientHeight(clientHeigth) {
	}

	bool WindowsGameWindow::Create() {
		if (hasCreated)
			return false;

		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = wndproc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hinstance;
		wndclass.hIcon = LoadIcon(hinstance, IDI_APPLICATION); //TODO: Verificar icon e cursor
		wndclass.hCursor = LoadCursor(hinstance, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = classname;

		if (!RegisterClass(&wndclass)) {
			return false;
		}

		int windowstyle = WS_OVERLAPPED | WS_SYSMENU;

		hwnd = CreateWindowEx(
			NULL,                           // estilos extras
			classname,						// nome da "window class"
			LPCSTR(Title().c_str()),        // título da janela
			windowstyle,                    // estilo da janela
			CW_USEDEFAULT,                  // posição x inicial
			CW_USEDEFAULT,                  // posição y inicial
			DefaultClientWidth,             // largura da janela
			DefaultClientHeight,            // altura da janela
			NULL,                           // identificador do objeto pai
			NULL,                           // identificador do menu
			hinstance,                      // identificador da aplicação
			NULL);                          // parâmetros de criação

		// retângulo com o tamanho da área cliente desejada
		RECT winRect = { 0, 0, currentClientWidth, currentClientHeight };

		// ajuste do tamanho da área cliente desejada
		AdjustWindowRectEx(&winRect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd));

		// atualiza posição da janela
		int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
		int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

		// redimensiona janela com uma chamada a MoveWindow
		MoveWindow(
			hwnd,									// identificador da janela
			windowPosX,								// posição x
			windowPosY,								// posição y
			winRect.right - winRect.left,		// largura
			winRect.bottom - winRect.top,	// altura
			TRUE);							// repintar

		hasCreated = true;
		return true;
	}

	void WindowsGameWindow::Show() {
		if (!hasCreated) {
			auto result = Create();

			if (!result)
				return;
		}

		ShowWindow(hwnd, 0);
		UpdateWindow(hwnd);
	}

	void WindowsGameWindow::AllowUserResizing(bool value) {
		allowUserResizing = value;
	}

	bool WindowsGameWindow::AllowUserResizing() const {
		return allowUserResizing;
	}

	bool WindowsGameWindow::IsMouseVisible() const {
		return isMouseVisible;
	}

	void WindowsGameWindow::IsMouseVisible(bool value) {
		isMouseVisible = value;
		ShowCursor(value);
	}

	Rectangle WindowsGameWindow::ClientBounds() const {
		RECT rect{};
		GetWindowRect(hwnd, &rect);

		return Rectangle(
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top);
	}

	DisplayOrientation WindowsGameWindow::CurrentOrientation() const {
		return DisplayOrientation::Default;
	}

	bool WindowsGameWindow::IsMinimizedState() const {
		return IsIconic(hwnd);
	}

	void WindowsGameWindow::BeginScreenDeviceChange(bool willBeFullScreen) {}

	void WindowsGameWindow::EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) {}

	LRESULT WindowsGameWindow::InternalWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		case WM_ACTIVATE:
			if (wParam == WA_INACTIVE)
				OnDeactivated();
			else
				OnActivated();
			return 0;

		case WM_PAINT:
			OnPaint();
			return 0;

		case WM_KILLFOCUS:
			OnSuspend();
			return 0;

		case WM_SETFOCUS:
			OnResume();
			return 0;

		default:
			return 0;
		}
	}

	void WindowsGameWindow::SetTitle(std::string const& title) {
		SetWindowText(hwnd, LPCSTR(title.c_str()));
	}

	void WindowsGameWindow::OnSuspend() const {
		Suspend.Invoke(*this, cs::EventArgs::Empty());
	}

	void WindowsGameWindow::OnResume() const {
		Resume.Invoke(*this, cs::EventArgs::Empty());
	}
}