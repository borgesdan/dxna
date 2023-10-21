#ifndef DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP
#define DXNA_PLATFORMS_WINDOWS_GAMEWINDOW_HPP

#include "win32includes.hpp"
#include "../../gamewindow.hpp"

namespace dxna {
	class WindowsGameWindow : public GameWindow {
	public:
		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc);
		WindowsGameWindow(HINSTANCE hinstance, WNDPROC winproc, int clientWidth, int clientHeigth);

		bool Create();
		void Show();
		virtual bool AllowUserResizing() const override;
		virtual void AllowUserResizing(bool value) override;
		virtual bool IsMouseVisible() const override;
		virtual void IsMouseVisible(bool value) override;
		virtual Rectangle ClientBounds() const override;
		virtual DisplayOrientation CurrentOrientation() const override;
		virtual bool IsMinimizedState() const override;
		virtual void BeginScreenDeviceChange(bool willBeFullScreen) override;
		virtual void EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) override;

		LRESULT InternalWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		
		cs::EventHandler<GameWindow, cs::EventArgs> Suspend;
		cs::EventHandler<GameWindow, cs::EventArgs> Resume;

	protected:
		virtual void SetTitle(std::string const& title) override;
		virtual void SetSupportedOrientations(DisplayOrientation orientations) override {}

		void OnSuspend() const;
		void OnResume() const;

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
