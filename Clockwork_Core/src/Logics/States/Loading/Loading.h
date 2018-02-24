#pragma once
/*************************************************************************
* Clockwork-Engine
* A C++/Opengl/GLFW3 game engine
* Website: clock-work.tk
*------------------------------------------------------------------------
* Copyright (C) 20017-2018 Niko Miklis <clock-work@gmx.de> - All Rights Reserved
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* You can use this software under the following License: https://github.com/Clock-work/Clockwork-Engine/blob/master/LICENSE
*************************************************************************/
#include "src\Logics\States\State.h"

namespace clockwork {
	namespace logics {

		class Loading
			: public State//muss noch angepasst werden und alles überschreiben
		{

		private:
			State** m_statePointer;
			State* m_newState;

		public:
			Loading() noexcept;
			virtual ~Loading() noexcept;

		public:
			virtual void changeState(State* prevState, State* newState, State** statePointer) noexcept;
			virtual void fastTick() noexcept override;
			virtual void render() noexcept override;


		};


	}
}