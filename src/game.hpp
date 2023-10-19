#ifndef DXNA_GAME_HPP
#define DXNA_GAME_HPP

#include "gametime.hpp"

namespace dxna {
	class Game {
	public:
		void Run();
		void RunOneFrame();
		void Tick();
		void SupressDraw();
		void Exit();

	protected:
		virtual void BeginRun(){}
		virtual void EndRun(){}
		virtual void Update(GameTime const& gameTime);
		virtual bool BeginDraw();
		virtual void Draw(GameTime const& gameTime);
		virtual void Initialize();
		void ResetElapsedTime();
		virtual void OnActived();
		virtual void OnDeactivated();
		virtual void OnExiting();
		virtual void LoadContent();
		virtual void UnloadContent();

	private:
		void RunGame(bool useBlockingRun);
		void DrawFrame();
		void EnsureHost();
	};
}

#endif