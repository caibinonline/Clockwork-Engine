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
#include "State.h"
#include "src\Core\Window.h"

namespace clockwork {
	namespace logics {

			State::State() noexcept
			{

			}

			State::~State() noexcept
			{

			}

			void State::enter() noexcept
			{
				//sachen/texturen vorbereiten/der renterwarteschlange adden 
			}

			void State::leave() noexcept
			{
				//sachen/texturen löschen
			}

			void State::tick() noexcept
			{

			}

			void State::render() noexcept
			{

			}

			void State::onResize(int width, int height, graphics::Window* window) noexcept
			{

			}

			void State::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onMousePress(int button, int action, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
			{

			}

			void State::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
			{

			}

			void State::onCursorEnter(int entered, graphics::Window* window) noexcept
			{

			}

			void State::onFileDrop(int count, const char** paths, graphics::Window* window) noexcept
			{

			}

			void State::onFocus(int focus, graphics::Window* window) noexcept
			{

			}

			void State::onClose(graphics::Window* window) noexcept
			{

			}

	}
}