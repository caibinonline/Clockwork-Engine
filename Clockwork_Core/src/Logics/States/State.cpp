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
#include "src\Core\Engine.h"
#include "src\Core\Window.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Graphics\Renderer\Renderer.h"

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
				m_defaultCamera = new Camera({ 0,5,5 });
				m_currentCamera = m_defaultCamera;
				m_defaultRenderer = new graphics::Renderer(new graphics::Shader("res/Shaders/Default/Instancing.vs", "res/Shaders/Default/Instancing.fs"), new graphics::Shader("res/Shaders/Default/Normal.vs", "res/Shaders/Default/Normal.fs"), &m_currentCamera, &m_perspectiveProjection);
				updateProjection();//immer nach �ndern des fvo, near, oder far der currentcamera aufrufen(auch ggf, wenn pointer auf andere camera zeigen wird), oder beim resizen | aber ggf dann in erbenden states auch f�r andere renderer updateprojection aufrufen, wenn dort nochmal currentcamera �berarbeitet wird

			}

			void State::leave() noexcept
			{
				delete m_defaultCamera;
				delete m_defaultRenderer;
				//sachen/texturen l�schen
			}

			void State::tick() noexcept
			{

			}

			void State::slowTick() noexcept
			{

			}

			void State::render() noexcept
			{

			}

			void State::updateProjection() noexcept
			{
				if ( engine->getWindow()->getWidth() != 0 && engine->getWindow()->getHeight() != 0 )
				{
					m_perspectiveProjection = maths::Mat4x4<float>::perspective(maths::toRadians<float>(m_currentCamera->fov), static_cast<double>( engine->getWindow()->getWidth() ) / static_cast<double>( engine->getWindow()->getHeight() ), m_currentCamera->nearMin, m_currentCamera->farMax);//projection matrix for the scene to transform world coordinates into screen coordinates | has to be set once per update of the window size
					//auch noch orthographic updaten
					m_defaultRenderer->updateProjection();
				}
			}

			void State::onResize(int width, int height, graphics::Window* window) noexcept
			{
				updateProjection();
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