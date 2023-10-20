#ifndef DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP
#define DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP

#include "win32includes.hpp"
#include "../../gamewindow.hpp"

namespace dxna {
	class WindowsGameWindow : public GameWindow {
	public:
		WindowsGameWindow(HINSTANCE hinstance) : hinstance(hinstance) {
		}

		bool Create() {
			wndclass.style = CS_HREDRAW | CS_VREDRAW;
			wndclass.lpfnWndProc = WindowsGameWindow::WinProc;
			wndclass.cbClsExtra = 0;
			wndclass.cbWndExtra = 0;
			wndclass.hInstance = hinstance;
			wndclass.hIcon = LoadIcon(hinstance, NULL); //TODO: Verificar icon e cursor
			wndclass.hCursor = LoadCursor(hinstance, NULL);
			wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wndclass.lpszMenuName = NULL;
			wndclass.lpszClassName = classname;			

			if (!RegisterClass(&wndclass)) {
				return false;
			}

			int windowstyle = WS_OVERLAPPED | WS_SYSMENU;

			hwnd = CreateWindowEx(
				NULL,                           // estilos extras
				classname,	                   // nome da "window class"
				LPCSTR(Title().c_str()),                         // título da janela
				windowstyle,                    // estilo da janela
				CW_USEDEFAULT,                  // posição x inicial
				CW_USEDEFAULT,                  // posição y inicial
				DefaultClientWidth,             // largura da janela
				DefaultClientheight,            // altura da janela
				NULL,                           // identificador do objeto pai
				NULL,                           // identificador do menu
				hinstance,                      // identificador da aplicação
				NULL);                          // parâmetros de criação

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
			LPRECT lprect = nullptr;
			GetWindowRect(hwnd, lprect);

			return Rectangle(
				lprect->left,
				lprect->top,
				lprect->right - lprect->left,
				lprect->bottom - lprect->top);
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

		static LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message)
			{
			case WM_KILLFOCUS:
				return 0;

			case WM_SETFOCUS:
				return 0;

			default:
				return 0;
			}

			return 0;
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

		HWND hwnd;
		WNDCLASS wndclass;
		HINSTANCE hinstance;
		LPCSTR classname = "GameWindow";
	};
}

#endif