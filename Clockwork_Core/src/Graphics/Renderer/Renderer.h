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
#include "src\Graphics\Renderer\Shader.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Graphics\Renderables\Cube\CubeManager.h"
#include "src\Graphics\Renderables\Cube\InstancedCube.h"
#include "src\Graphics\Renderables\Cube\NormalCube.h"



#include "src\Graphics\Renderables\BadTerrainTest.h"


namespace clockwork {
	namespace graphics {

		class Renderer
		{

		private:
			friend class NormalCube;

		private:
			Shader * m_instanceShader;
			Shader* m_normalShader;
			logics::Camera** m_currentCamera;
			maths::Mat4f* m_currentProjection;
			bool m_deleteShader;

		public:
			CubeManager cubeManager;



			BadTerrainTest terrain;

		public:

			Renderer() noexcept
				: m_instanceShader(nullptr), m_normalShader(nullptr), m_currentCamera(nullptr), m_currentProjection(nullptr), cubeManager(), m_deleteShader(false)
			{}

			//pointer to dynamic, or class owned shader, pointer to dynamic, or class owned pointer to camera, pointer to dynnamic, or class owned projection matrix
			//bool deleteshader this renderer deletes the shader with its destruktor call when its set to true | so if you have a shared shader in multiple renderers and you manage it/delete it in your game, then pass false as the boolean(just shader pointer passed as parameter, not new shader objekt created with new)
			Renderer(Shader* instanceShader, Shader* normalShader, logics::Camera** camera, maths::Mat4f* projection, unsigned int reserved = 10, bool deleteShader = true) noexcept
				: m_instanceShader(instanceShader), m_normalShader(normalShader), m_currentCamera(camera), m_currentProjection(projection), cubeManager(reserved), m_deleteShader(deleteShader)
			{
				prepare();
			}

			~Renderer() noexcept
			{
				if ( m_deleteShader )
				{
					delete m_instanceShader;
					delete m_normalShader;
				}
			}

			Renderer(const Renderer& other) = delete;

			Renderer(Renderer&& other) noexcept///WICHTIG auch für alle anderen cubemanager moven, etc, wenn meherere manager da sind | WICHTIG NOCH INSTANCEN UPDATEN POINTER AUF RENDERER 
				: m_instanceShader(other.m_instanceShader), m_normalShader(other.m_normalShader), m_currentCamera(other.m_currentCamera), m_currentProjection(other.m_currentProjection), m_deleteShader(other.m_deleteShader), cubeManager(std::move(other.cubeManager))
			{
				other.m_instanceShader = nullptr;
				other.m_normalShader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
				for ( unsigned int i = 0; i < cubeManager.m_instanceCount; ++i )
				{
					cubeManager.m_instanceCubes.at(i)->m_renderer = this;
				}
				for ( unsigned int i = 0; i < cubeManager.m_normalCount; ++i )
				{
					cubeManager.m_normalCubes.at(i)->m_renderer = this;
				}
			}

			Renderer& operator=(const Renderer& other) = delete;

			Renderer& operator=(Renderer&& other) noexcept
			{
				m_instanceShader = other.m_instanceShader;
				m_normalShader = other.m_normalShader;
				m_currentCamera = other.m_currentCamera;
				m_currentProjection = other.m_currentProjection;
				m_deleteShader = other.m_deleteShader;
				cubeManager = std::move(cubeManager);
				other.m_instanceShader = nullptr;
				other.m_normalShader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
				for ( unsigned int i = 0; i < cubeManager.m_instanceCount; ++i )
				{
					cubeManager.m_instanceCubes.at(i)->m_renderer = this;
				}
				for ( unsigned int i = 0; i < cubeManager.m_normalCount; ++i )
				{
					cubeManager.m_normalCubes.at(i)->m_renderer = this;
				}
				return *this;
			}

			//auch alle anderen methoden virtual machen
			virtual void prepare() noexcept//virtual, kann überschrieben werden und andere uniformen setzten, etc | alles andere neu kommentieren und neu machen(auch virtual destruktor) | auch dazu kommentieren, dass man vom renderer erben kann und soll, wenn man im render loop etwas verändern will(genausop bei normalcube dazu schreiben und bei engine, etc)
			{
				m_instanceShader->enable();
				m_instanceShader->setUniform("u_texture1", 0);//keine ahnung, wie ich später einzelne uniformen entweder seperat über methoden vom shader setze, oder hier standard sachen, die für alle shader angenommen werden | auf jedenfall getshader methode machen und ggf setstandarduniforms, oder so
															  //setting uniforms, but shader has to be enabled first | here binds the texture1 uniform to the first texture pos in the shader | is not necessary for the first texture, if only one texture is used and not more

				m_normalShader->enable();
				m_normalShader->setUniform("u_texture1", 0);
			}

			void render() noexcept
			{
				m_instanceShader->enable();
				(*m_currentCamera)->update(m_instanceShader);//so ähnlich dann hier die verschiedenen modelle vorbereiten, dann texturen und dann positionen, etc schicken
				cubeManager.renderInstancedCubes();

				m_normalShader->enable();
				( *m_currentCamera )->update(m_normalShader);
				cubeManager.renderNormalCubes();

				terrain.render(m_normalShader);

			}

			void updateProjection() noexcept
			{
				m_instanceShader->enable();
				m_instanceShader->setUniform("u_projection", *m_currentProjection);
				m_normalShader->enable();
				m_normalShader->setUniform("u_projection", *m_currentProjection);
			}

		};

	}
}