#include "gamewindow.hpp"
#include "structs.hpp"
#include "enumerations.hpp"
#include "gamewindow.hpp"

namespace dxna {
	void GameWindow::Title(std::string const& value) {
		if (title == value)
			return;

		title = value;
		SetTitle(title);
	}
}