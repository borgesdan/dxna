#include "gamewindow.hpp"

namespace dxna {
	void GameWindow::OnActivated() const {
		Activated.Invoke(*this, cs::EventArgs::Empty());
	}

	void GameWindow::OnDeactivated() const {
		Deactivated.Invoke(*this, cs::EventArgs::Empty());
	}

	void GameWindow::OnPaint() const {
		Paint.Invoke(*this, cs::EventArgs::Empty());
	}

	void GameWindow::OnScreenDeviceNameChanged() const {
		ScreenDevicenameChanged.Invoke(*this, cs::EventArgs::Empty());
	}

	void GameWindow::OnClientSizeChanged() const {
		ClientSizeChanged.Invoke(*this, cs::EventArgs::Empty());
	}

	void GameWindow::OnOrientationChanged() const {
		OrientationChanged.Invoke(*this, cs::EventArgs::Empty());
	}
}