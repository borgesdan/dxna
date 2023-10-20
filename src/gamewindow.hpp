#ifndef DXNA_GAMEWINDOW_HPP
#define DXNA_GAMEWINDOW_HPP

#include "cs/cs.hpp"
#include "defincludes.hpp"
#include "structs.hpp"
#include "enumerations.hpp"

namespace dxna {
	class GameWindow {
	public:
		static constexpr int DefaultClientWidth = 800;
		static constexpr int DefaultClientheight = 600;

		constexpr std::string Title() const {
			return std::string(title);
		}

		void Title(std::string const& value);

		virtual DisplayOrientation CurrentOrientation() const = 0;		

		virtual void BeginScreenDeviceChange(bool willBeFullScreen) = 0;

		virtual void EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) = 0;
		
		virtual bool AllowUserResizing() const {
			return false;
		}

		virtual void AlloUserResizing(bool value) {
		}

		virtual bool IsMouseVisible() const {
			return false;
		}

		virtual void IsMouseVisible(bool value) {
		}

		virtual bool IsMinimizedState() const {
			return false;
		}

		virtual Rectangle ClientBounds() const = 0;

		cs::EventHandler<GameWindow, cs::EventArgs> Activated;
		cs::EventHandler<GameWindow, cs::EventArgs> Deactivated;
		cs::EventHandler<GameWindow, cs::EventArgs> Paint;
		cs::EventHandler<GameWindow, cs::EventArgs> ScreenDevicenameChanged;
		cs::EventHandler<GameWindow, cs::EventArgs> ClientSizeChanged;
		cs::EventHandler<GameWindow, cs::EventArgs> OrientationChanged;

	protected:
		virtual void SetTitle(std::string const& title) = 0;
		virtual void SetSupportedOrientations(DisplayOrientation orientations) = 0;

		virtual void OnActivated() const;
		virtual void OnDeactivated() const;
		virtual void OnPaint() const;
		virtual void OnScreenDeviceNameChanged() const;
		virtual void OnClientSizeChanged() const;
		virtual void OnOrientationChanged() const;

	private:
		std::string title;
	};
}

#endif