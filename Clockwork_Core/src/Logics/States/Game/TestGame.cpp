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


#include "src\Logics\Entities\Test.h"
#include "src\Logics\ChunkSystem\ChunkSystem.h"


namespace clockwork {
	namespace logics {

		TestGame::TestGame() noexcept
		{

		}

		TestGame::~TestGame() noexcept
		{

		}

		void TestGame::enter() noexcept
		{
			using namespace graphics;
			using namespace utils;
			setCurrentCamera(m_defaultCamera);//muss aufgerufen werden, nachdem alle renderer erstellt wurden, aber vor chunksystem
			m_chunkSystem = new ChunkSystem({ -5000,-5000,-5000 }, { 5000,5000,5000 }, { 100,100,100 }, { 1,1,1 }, { 2,2,2 }, this);//chunksystem in erbenden states mit den jeweiligenn gr��en erstellen | nachdem camera und renderer erstellt wurden, aber bevor gameobjects hinzugef�gt werden 
			///immoment nur renderdistance 1 zum testen | sp�ter auch chunkdistanz erh�hen, da man immoment error bekommt, wenn camerapos ausserhalb des chunks ist | auch gucken wie z is(negativ/nicht) wegen opengl right hand system


			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/brick.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/stone.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/granite.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/moss.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/brick2.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/granite2.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/wood.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/grass.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/blue.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/red.jpg").load());
			m_defaultRenderer->cubeManager.addTextureBoth(utils::Image("res/Images/purple.jpg").load());


			std::srand(engine->getWindow()->getTimer() * 10);

			for ( int i = 0; i < 100; ++i )//10000 objects: normal 300fps, instancing 2300fps | 1000objects: normal 2000fps, instancing 5000fps | 100 objects: normal 5500fps, instancing 6100fps | 10 objects: normal 5500fps, instancing 5500fps | 1 object: normal 6300fps, instancing 6100fps
			{
				maths::Vec3f pos = maths::Vec3f(-( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10);
				logics::InstancedTest* inst = new logics::InstancedTest(rand() % 11, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos, this, m_defaultRenderer);
			}

			for ( int i = 0; i < 100; ++i )
			{
				maths::Vec3f pos = maths::Vec3f(-( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10, -( rand() % 500 + 1 ) / 10 + ( rand() % 500 + 1 ) / 10);
				logics::TransparentTest* inst = new logics::TransparentTest("res/Images/transparent.png", maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos, this, m_defaultRenderer);
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

			m_chunkSystem->tick();

		}

		void TestGame::slowTick() noexcept
		{
			m_chunkSystem->slowTick();
		}

		void TestGame::render() noexcept
		{
			m_chunkSystem->update();
			m_defaultRenderer->render();//ggf in state render verschieben
			m_defaultRenderer->renderTransparent();
		}


		void TestGame::onResize(int width, int height, graphics::Window* window) noexcept
		{

		}

		void TestGame::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
		{
			if ( key == CLOCKWORK_KEY_X && action == CLOCKWORK_PRESS )
				m_currentCamera->movePos({ +50, +50, +50 });
			else if ( key == CLOCKWORK_KEY_C && action == CLOCKWORK_PRESS )
				m_currentCamera->movePos({ -50, -50, -50 });
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
					maths::Vec3f pos1 = m_currentCamera->getPosition() + m_currentCamera->getDirection() * 2;
					maths::Vec3f pos2 = m_currentCamera->getPosition() + m_currentCamera->getDirection() * 4;
					maths::Vec3f pos3 = m_currentCamera->getPosition() + m_currentCamera->getDirection() * 6;

					logics::InstancedTest* inst1 = new logics::InstancedTest(rand() % 11, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos1, this, m_defaultRenderer);
					logics::NormalTest* inst2 = new logics::NormalTest(rand() % 11, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos2, this, m_defaultRenderer);
					logics::TransparentTest* inst3 = new logics::TransparentTest(0, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos3, this, m_defaultRenderer);

				}
				else if ( button == CLOCKWORK_MOUSE_BUTTON_2 )
				{
					m_defaultRenderer->cubeManager.removeLastInstancedCube();
					m_defaultRenderer->cubeManager.removeLastNormalCube();
					m_defaultRenderer->cubeManager.removeLastTransparentCube();
				}
			}

		}

		void TestGame::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
		{
			m_currentCamera->rotate(xoffset/10, yoffset /10);
		}

		void TestGame::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
		{
			if ( m_currentCamera->getFov()> 120 )//zooming by changing fov and then updating projectionmatrix 
				m_currentCamera->setFov(120);
			else if ( m_currentCamera->getFov() < 1 )
				m_currentCamera->setFov(1);
			else
				m_currentCamera->setFov(m_currentCamera->getFov() - yoffset);
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