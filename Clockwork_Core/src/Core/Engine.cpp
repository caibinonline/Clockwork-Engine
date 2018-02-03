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
#pragma once
#include "glad\glad.h"
#include "glfw\glfw3.h"
#include "Engine.h"
#include "Window.h"
#include "src\Graphics\Renderer\Shader.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Logics\States\State.h"
#include "src\Logics\States\Loading\Loading.h"
#include "src\Graphics\Textures\Texture2D.h"
#include "src\Graphics\Textures\TextureArray2D.h"
#include "src\Graphics\Textures\SpriteSheet.h"
#include "src\Logics\States\Game\TestGame.h"
#include "src\Maths\MathFunctions.h"
#include <thread>

namespace clockwork {

	Engine::Engine(const char* title) noexcept
		:m_running(true), m_currentState(nullptr), m_passedTime { 0 }
	{
#if CLOCKWORK_DEBUG
		std::cout << "Clockwork Engine Debug Mode" << std::endl;
#else
		std::cout << "Clockwork Engine Release Mode" << std::endl;
#endif
		clockwork::maths::initMaths();
		graphics::Window::init();//hier ggf noch andere libs initialisieren, oder im window initialisieren | modelloader, fonts, etc
		m_window = new graphics::Window(title,800,800,1,false,0);//später size von static configmanager nehmen genau wie welcher screen benutzt wird ob fullscreen und vsync etc, sonst von screen ablesen | wird später alles hier dem window von configmanager übergeben | standard ist hier alles 0 in configmanager, wie bei window | beim ersten starten wird das window mit default sachen fullscreen mit size des primären monitors erstellt und config saved einmal, wenn game gestartet ist
		graphics::initBuffers(10);///später nach testen wieder zu 100000 bytes machen, genau wie cube mit mehr bytes reservieren | jede funktion, die mit grafik objekten arbeitet MUSS VOM RENDERING THREAD AUFGERUFEN WERDEN, also bei allen buffer sachen, etc hinzuschreiben, dass sie nur vom renderthread mit opengl context aufgerufen werden können, wie bei initbuffers
		graphics::openglParams();

		//immer muss zuerst window erstellt werden und dann loading und dann states und dann kann in start alles verwendet werden
		m_defaultLoading = new logics::Loading();//hier loadingstate und alle anderen state objekte erstellen, die game spezifischen initialisierungen finden dann in start statt, aber hier schonmal die objekte erstellen, damit auf sie zugegriffen werden kann | in den states die verschiedenen gameobjekt listen, etc ggf mit nullptr initialisieren und erst von loading mit start initialisieren lassen, z.b. chunksystem
		//die richtigen game objekte, etc, die lange dauern werden hier nicht erstellt, sondern im loading state zusammen mit den grafischen elementen und der server initialisierung
	}

	Engine::~Engine() noexcept
	{
		delete m_window;
		clockwork::maths::destroyMaths();
		graphics::Window::destroy();
	}

	void Engine::start() noexcept
	{
		using namespace graphics;
		using namespace utils;
		using namespace logics;

		m_currentState = new TestGame();
		m_currentState->enter();

		m_window->setVsync(1);//disable vsync and performancemode for most fps 
		bool performanceMode = true;
		m_window->hideCursor(true);

		int steps { 0 }, targetFps { 144 }, fps { targetFps };//you have to set your desired targetfps and you can then later see the true fps of your gameloop
		double timer { 0 }, newTime { 0 }, lastTime { m_window->getTimer() };
		while ( m_running )///später in multithread etc sachen | time wahrscheinlich von steuerthread und ggf noch renderthread seperat
		{
			newTime = m_window->getTimer();
			m_passedTime = newTime - lastTime;
			timer += m_passedTime;///timefactor ist später im thread, der die threadgruppe steuert(und window updated/input updated) und dann wartet bis alle threads fertig sind, dann aktualisiert er den timefactor | vielleicht ai, etc nicht so oft we movement, etc kalkulieren | renderthread hat dann gleichen gameloop, ausser m_passedtime
			lastTime = newTime;

			m_currentState->tick();///hier physics sachen adden, wie movement, etc, aber noch zweite funktion ai, oder so und davon nur jede sekunde sachen zu den threadworkern adden und nicht jeden tick | das dann ggf im timer >= 1 if machen und dann mehrere update funktionen in objekten haben, einmal pro tick, einmal pro sekunde | ggf auch für network benutzen
			m_currentState->render();
			m_window->updateWindow();
			m_window->updateInput();
#if CLOCKWORK_DEBUG
			m_window->checkError();
#endif
			++steps;
			if ( timer >= 1 )
			{
				fps = steps;
				steps = 0;
				timer = 0;
				std::cout << "FPS:" << fps << std::endl;//vielleicht immer laufend verändern mal ausprobieren anhand letztem loop und allen davor, damit es insgesamt flüssiger läuft
			}

			if ( performanceMode )
				std::this_thread::sleep_for(std::chrono::duration<double>(maths::max(0.0, 1.0 / static_cast<double>( targetFps ) - ( m_window->getTimer() - newTime + 0.00076 ))));//ggf auch als double in sekunden später boost für sleep benutzen und gucken, dass es nicht interuppted?
		
		}


	}


	void Engine::onResize(int width, int height, graphics::Window* window) noexcept
	{
		m_currentState->onResize(width, height, window);
		LOG("RESIZE")LOG(width)LOG("___")LOG(height)LOG("\n")
	}

	void Engine::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
	{
		m_currentState->onKeyPress(key, scancode, action, mods, window);
		if ( action == GLFW_PRESS )
		{
			if ( key == GLFW_KEY_F )
				m_window->setFullscreen(true);
			else if ( key == GLFW_KEY_G )
				m_window->setFullscreen(false);
			else if ( key == GLFW_KEY_R )
				m_window->hideCursor(true);
			else if ( key == GLFW_KEY_T )
				m_window->hideCursor(false);
			else if ( key == GLFW_KEY_ESCAPE )
				onClose(m_window);


		}
		else if ( action == GLFW_RELEASE )
		{

		}
	}

	void Engine::onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept
	{
		m_currentState->onCharTyped(keycode, mods, window);
	}

	void Engine::onMousePress(int button, int action, int mods, graphics::Window* window) noexcept
	{
		m_currentState->onMousePress(button, action, mods, window);
	}

	void Engine::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
	{
		m_currentState->onMouseMove(xoffset, yoffset, window);
	}

	void Engine::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
	{
		m_currentState->onScroll(xoffset, yoffset, window);
	}

	void Engine::onCursorEnter(int entered, graphics::Window* window) noexcept
	{
		m_currentState->onCursorEnter(entered, window);
	}

	void Engine::onFileDrop(int count, const char** paths, graphics::Window* window) noexcept
	{
		m_currentState->onFileDrop(count, paths, window);
	}

	void Engine::onFocus(int focus, graphics::Window* window) noexcept
	{
		m_currentState->onFocus(focus, window);
	}

	void Engine::onClose(graphics::Window* window) noexcept
	{
		m_currentState->onClose(window);
		m_running = false;
	}


	void Engine::setState(logics::Loading* loadingScreen, logics::State* newState) noexcept
	{
		loadingScreen->changeState(m_currentState, newState, &m_currentState);
		m_currentState = loadingScreen;
	}




	Engine* engine {};

}