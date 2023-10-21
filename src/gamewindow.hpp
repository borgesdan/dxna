#ifndef DXNA_GAMEWINDOW_HPP
#define DXNA_GAMEWINDOW_HPP

#include "cs/cs.hpp"
#include "defincludes.hpp"
#include "structs.hpp"
#include "enumerations.hpp"

namespace dxna {

	//Representa a classe base para uma janela de jogo.
	class GameWindow {
	public:
		//Obt�m a largura padr�o da �rea cliente.
		static constexpr int DefaultClientWidth = 800;
		//Obt�m a altura padr�o da �rea cliente.
		static constexpr int DefaultClientHeight = 600;

		//Obt�m o t�tulo da janela.
		constexpr std::string Title() const {
			return std::string(title);
		}

		//Define o t�tulo da janela.
		void Title(std::string const& value);

		//Obt�m a orienta��o da janela.
		virtual DisplayOrientation CurrentOrientation() const = 0;		

		virtual void BeginScreenDeviceChange(bool willBeFullScreen) = 0;

		virtual void EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) = 0;
		
		//Obt�m se a janela permite ser redimensionada.
		virtual bool AllowUserResizing() const {
			return false;
		}

		//Define se a janela permite ser redimensionada.
		virtual void AlloUserResizing(bool value) {
		}

		//Obt�m se o mouse deve ser vis�vel na janela.
		virtual bool IsMouseVisible() const {
			return false;
		}

		//Define se o mouse deve ser vis�vel na janela.
		virtual void IsMouseVisible(bool value) {
		}

		//Obt�m se a janela est� minimizada.
		virtual bool IsMinimizedState() const {
			return false;
		}

		//Obt�m os limites da janela.
		virtual Rectangle ClientBounds() const = 0;

		//Eventos ativados quando a janela for ativada.
		cs::EventHandler<GameWindow, cs::EventArgs> Activated;
		//Eventos ativados quando a janela for desativada.
		cs::EventHandler<GameWindow, cs::EventArgs> Deactivated;
		//Eventos ativados quando a janela for desenhada.
		cs::EventHandler<GameWindow, cs::EventArgs> Paint;
		//Eventos ativados quando a janela tiver seu tamanho cliente mudado.
		cs::EventHandler<GameWindow, cs::EventArgs> ClientSizeChanged;
		//Eventos ativados quando a janela tiver sua orienta��o mudada.
		cs::EventHandler<GameWindow, cs::EventArgs> OrientationChanged;		

	protected:
		virtual void SetTitle(std::string const& title) = 0;
		virtual void SetSupportedOrientations(DisplayOrientation orientations) = 0;

		virtual void OnActivated() const;
		virtual void OnDeactivated() const;
		virtual void OnPaint() const;
		virtual void OnClientSizeChanged() const;
		virtual void OnOrientationChanged() const;

	private:
		std::string title;
	};
}

#endif