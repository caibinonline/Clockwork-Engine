/*************************************************************************
* Clockwork Engine
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
#include "glad\glad.h"
#include "glfw\glfw3.h"
#include "TestGame.h"
#include "src\Core\Window.h"
#include "src\Graphics\Renderer\Shader.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Logics\States\State.h"
#include "src\Logics\States\Loading\Loading.h"
#include "src\Graphics\Textures\Texture2D.h"
#include "src\Graphics\Textures\TextureArray2D.h"
#include "src\Graphics\Textures\SpriteSheet.h"
#include "src\Core\Engine.h"
#include "src\Logics\Camera\Camera.h"


#include "src\Graphics\Renderables\Cube\CubeManager.h"
#include "src\Graphics\Renderables\Cube\InstancedCube.h"


#include "src\Maths\Vec3.h"

namespace clockwork {
	namespace logics {


		TestGame::TestGame() noexcept
		{

		}

		TestGame::~TestGame() noexcept
		{

		}

		static float fov = 90.0f;

		void TestGame::enter() noexcept
		{
			using namespace graphics;
			using namespace utils;

			m_currentCamera = new Camera({ 0,10,5 });//

			m_instancedRenderer = new InstancedRenderer(new graphics::Shader("res/Shaders/Testing/Instancing.vs", "res/Shaders/Testing/Instancing.fs"), &m_currentCamera, &m_perspectiveProjection);
			m_normalRenderer = new NormalRenderer(new graphics::Shader("res/Shaders/Testing/Normal.vs", "res/Shaders/Testing/Normal.fs"), &m_currentCamera, &m_perspectiveProjection);

		
			if ( engine->getWindow()->getWidth() != 0 && engine->getWindow()->getHeight() != 0 )
			{
				m_perspectiveProjection = maths::Mat4x4<float>::perspective(maths::toRadians<float>(fov), static_cast<double>( engine->getWindow()->getWidth() ) / static_cast<double>( engine->getWindow()->getHeight() ), 0.1f, 1000.0f);//projection matrix for the scene to transform world coordinates into screen coordinates | has to be set once per update of the window size
				m_instancedRenderer->updateProjection();
				m_normalRenderer->updateProjection();
			}
			


			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/brick.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/stone.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/granite.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/moss.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/brick2.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/granite2.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/wood.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/grass.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/blue.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/red.jpg").load());
			m_instancedRenderer->cubeManager.addTexture(utils::Image("res/Images/purple.jpg").load());


			std::srand(engine->getWindow()->getTimer() * 10);

			for ( int i = 0; i < 1000; ++i )
			{
				maths::Mat4x4<float> modelMatrix = modelMatrix = maths::Mat4x4<float>::scaling(1, 1, 1);
				modelMatrix.translate(-( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10);
				InstancedCube* inst = new InstancedCube(rand() % 11, modelMatrix, m_instancedRenderer);
				inst->add();
			}


		}

		void TestGame::leave() noexcept
		{

		}

		void TestGame::tick() noexcept
		{
			double time = engine->getTimeFactor();//time scaling factor 

			//camera movement
			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_W) )
			{
				m_currentCamera->moveZ(5 * time);
			}
			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_S) )
			{
				m_currentCamera->moveZ(-5 * time);
			}
			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_A) )
			{
				m_currentCamera->moveX(-5 * time);
			}
			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_D) )
			{
				m_currentCamera->moveX(5 * time);
			}
			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT_CONTROL) )
			{
				m_currentCamera->moveY(-5 * time);
			}
			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_SPACE) )
			{
				m_currentCamera->moveY(5 * time);
			}

		}

		void TestGame::render() noexcept
		{
			m_instancedRenderer->render();
			m_normalRenderer->render();
		}


		void TestGame::onResize(int width, int height, graphics::Window* window) noexcept
		{
			if ( width != 0 && height != 0 )
			{
				m_perspectiveProjection = maths::Mat4x4<float>::perspective(maths::toRadians<float>(fov), static_cast<double>( width ) / static_cast<double>( height ), 0.1f, 1000.0f);//projection matrix for the scene to transform world coordinates into screen coordinates | has to be set once per update of the window size
				m_instancedRenderer->updateProjection();
				m_normalRenderer->updateProjection();
			}
		}

		void TestGame::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
		{
			if ( key == CLOCKWORK_KEY_J && action == CLOCKWORK_PRESS )
				m_currentCamera->setDirection({ -1,-1,-1 });
		}

		void TestGame::onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept
		{

		}

		void TestGame::onMousePress(int button, int action, int mods, graphics::Window* window) noexcept
		{
			if ( action == CLOCKWORK_PRESS )
			{
				if ( button == CLOCKWORK_MOUSE_BUTTON_1 )
				{
					maths::Vec3f pos = m_currentCamera->getPosition() + m_currentCamera->getDirection() * 2;
					maths::Mat4x4<float> modelMatrix = modelMatrix = maths::Mat4x4<float>::scaling(1, 1, 1);
					modelMatrix.translate(pos.x, pos.y, pos.z);
					graphics::InstancedCube* inst = new graphics::InstancedCube(rand() % 11, modelMatrix, m_instancedRenderer);
					inst->add();
				}
				else if ( button == CLOCKWORK_MOUSE_BUTTON_2 )
				{
					m_instancedRenderer->cubeManager.removeLast();
				}
			}

		}

		void TestGame::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
		{
			m_currentCamera->rotate(xoffset/10, yoffset /10);
		}

		void TestGame::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
		{
			if ( fov > 120 )//zooming by changing fov and then updating projectionmatrix 
				fov = 120;
			else if ( fov < 1 )
				fov = 1;
			else
				fov -= yoffset;
			if ( engine->getWindow()->getWidth() != 0 && engine->getWindow()->getHeight() != 0 )
			{
				m_perspectiveProjection = maths::Mat4x4<float>::perspective(maths::toRadians<float>(fov), static_cast<double>( engine->getWindow()->getWidth() ) / static_cast<double>( engine->getWindow()->getHeight() ), 0.1f, 1000.0f);//projection matrix for the scene to transform world coordinates into screen coordinates | has to be set once per update of the window size
				m_instancedRenderer->updateProjection();
				m_normalRenderer->updateProjection();
			}

		}

		void TestGame::onCursorEnter(int entered, graphics::Window* window) noexcept
		{

		}

		void TestGame::onFileDrop(int count, const char** paths, graphics::Window* window) noexcept
		{

		}

		void TestGame::onFocus(int focus, graphics::Window* window) noexcept
		{

		}

		void TestGame::onClose(graphics::Window* window) noexcept
		{

		}

	}
}