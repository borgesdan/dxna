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
		//Obtém a largura padrão da área cliente.
		static constexpr int DefaultClientWidth = 800;
		//Obtém a altura padrão da área cliente.
		static constexpr int DefaultClientHeight = 600;

		//Obtém o título da janela.
		constexpr std::string Title() const {
			return std::string(title);
		}

		//Define o título da janela.
		void Title(std::string const& value);

		//Obtém a orientação da janela.
		virtual DisplayOrientation CurrentOrientation() const = 0;		

		virtual void BeginScreenDeviceChange(bool willBeFullScreen) = 0;

		virtual void EndScreenDeviceChange(std::string const& screnDeviceName, int clientWidth, int clientHeight) = 0;
		
		//Obtém se a janela permite ser redimensionada.
		virtual bool AllowUserResizing() const {
			return false;
		}

		//Define se a janela permite ser redimensionada.
		virtual void AlloUserResizing(bool value) {
		}

		//Obtém se o mouse deve ser visível na janela.
		virtual bool IsMouseVisible() const {
			return false;
		}

		//Define se o mouse deve ser visível na janela.
		virtual void IsMouseVisible(bool value) {
		}

		//Obtém se a janela está minimizada.
		virtual bool IsMinimizedState() const {
			return false;
		}

		//Obtém os limites da janela.
		virtual Rectangle ClientBounds() const = 0;

		//Eventos ativados quando a janela for ativada.
		cs::EventHandler<GameWindow, cs::EventArgs> Activated;
		//Eventos ativados quando a janela for desativada.
		cs::EventHandler<GameWindow, cs::EventArgs> Deactivated;
		//Eventos ativados quando a janela for desenhada.
		cs::EventHandler<GameWindow, cs::EventArgs> Paint;
		//Eventos ativados quando a janela tiver seu tamanho cliente mudado.
		cs::EventHandler<GameWindow, cs::EventArgs> ClientSizeChanged;
		//Eventos ativados quando a janela tiver sua orientação mudada.
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