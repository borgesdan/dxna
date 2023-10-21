#ifndef DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP
#define DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP

#include "win32includes.hpp"
#include "../../gamewindow.hpp"

namespace dxna {
	class WindowsGameWindow : public GameWindow {
	public:
		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc)
			: hinstance(hinstance), wndproc(winproc) {
		}

		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc, int clientWidth, int clientHeigth) :
			hinstance(hinstance), wndproc(winproc),
			currentClientWidth(clientWidth), currentClientHeight(clientHeigth) {
		}

		bool Create() {
			if (hasCreated)
				return false;

			wndclass.style = CS_HREDRAW | CS_VREDRAW;
			wndclass.lpfnWndProc = wndproc;
			wndclass.cbClsExtra = 0;
			wndclass.cbWndExtra = 0;
			wndclass.hInstance = hinstance;
			wndclass.hIcon = LoadIcon(hinstance, 0); //TODO: Verificar icon e cursor
			wndclass.hCursor = LoadCursor(hinstance, 0);
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

		void Show() {
			if (!hasCreated) {
				auto result = Create();

				if (!result)
					return;
			}

			ShowWindow(hwnd, 0);
			UpdateWindow(hwnd);
		}

		virtual bool AllowUserResizing() const override {
			return allowUserResizing;
		}

		virtual void AlloUserResizing(bool value) override {
			allowUserResizing = value;
		}

		virtual bool IsMouseVisible() const override {
			return isMouseVisible;
		}

		virtual void IsMouseVisible(bool value) override {
			isMouseVisible = value;
			ShowCursor(value);
		}

		virtual Rectangle ClientBounds() const override {
			RECT rect{};
			GetWindowRect(hwnd, &rect);

			return Rectangle(
				rect.left,
				rect.top,
				rect.right - rect.left,
				rect.bottom - rect.top);
		}

		virtual DisplayOrientation CurrentOrientation() const override {
			return DisplayOrientation::Default;
		}

		virtual bool IsMinimizedState() const override {
			return IsIconic(hwnd);
		}

		virtual void BeginScreenDeviceChange(bool willBeFullScreen) override {

		}

		virtual void EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) override {

		}

		cs::EventHandler<GameWindow, cs::EventArgs> Suspend;
		cs::EventHandler<GameWindow, cs::EventArgs> Resume;

		LRESULT InternalWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
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

	protected:
		virtual void SetTitle(std::string const& title) override {
			SetWindowText(hwnd, LPCSTR(title.c_str()));
		}

		virtual void SetSupportedOrientations(DisplayOrientation orientations) override {
		}

		void OnSuspend() {
			Suspend.Invoke(*this, cs::EventArgs::Empty());
		}

		void OnResume() {
			Resume.Invoke(*this, cs::EventArgs::Empty());
		}

	private:
		bool allowUserResizing{ false };
		bool isMouseVisible{ false };
		bool inDeviceTransition{ false };
		bool hasCreated{ false };
		int currentClientWidth{ DefaultClientWidth };
		int currentClientHeight{ DefaultClientHeight };
		

		HWND hwnd = nullptr;
		WNDCLASS wndclass{};
		HINSTANCE hinstance;
		LPCSTR classname = "GameWindow";
		WNDPROC wndproc;
	};
}

#endif
