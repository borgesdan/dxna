#ifndef DXNA_PLT_WIN_WGAMEWINDOW_HPP
#define DXNA_PLT_WIN_WGAMEWINDOW_HPP

#include "win32includes.hpp"
#include "../../gamewindow.hpp"

namespace dxna {
	class WindowsGameWindow : public GameWindow {
	public:
		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc);
		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc, int clientWidth, int clientHeigth);

		bool Create();
		void Show();
		
		inline virtual bool AllowUserResizing() const override {
			return allowUserResizing;
		}
		
		inline virtual void AllowUserResizing(bool value) override {
			allowUserResizing = value;
		}

		inline virtual bool IsMouseVisible() const override {
			return isMouseVisible;
		}

		inline virtual void IsMouseVisible(bool value) override {
			isMouseVisible = value;
			ShowCursor(value);
		}

		virtual Rectangle ClientBounds() const override;
		
		inline virtual DisplayOrientation CurrentOrientation() const override {
			return DisplayOrientation::Default;
		}

		virtual bool IsMinimizedState() const override {
			return IsIconic(hwnd);
		}

		LRESULT InternalWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		
		cs::EventHandler<GameWindow, cs::EventArgs> Suspend;
		cs::EventHandler<GameWindow, cs::EventArgs> Resume;

	protected:
		inline virtual void SetTitle(std::string const& title) override {
			SetWindowText(hwnd, LPCSTR(title.c_str()));
		}

		virtual void SetSupportedOrientations(DisplayOrientation orientations) override {}

		inline void OnSuspend() const {
			Suspend.Invoke(*this, cs::EventArgs::Empty());
		}

		inline void OnResume() const {
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
