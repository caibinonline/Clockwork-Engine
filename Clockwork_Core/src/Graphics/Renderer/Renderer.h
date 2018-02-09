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
#include "src\Graphics\Renderer\Shader.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Graphics\Renderables\Cube\InstancedCube.h"
#include "src\Graphics\Renderables\Cube\NormalCube.h"
#include "src\Graphics\Renderables\Cube\CubeManager.h"


#include "src\Graphics\Renderables\BadTerrainTest.h"


namespace clockwork {
	namespace graphics {

		class Renderer
		{

		private:
			friend class NormalCube;
			friend class CubeManager;
			friend class TransparentCubeManager;
			friend struct TransparentCubeCompare;

		private:
			logics::Camera** m_currentCamera;
			maths::Mat4f* m_currentProjection;
			bool m_deleteShader;

		public:
			Shader * instancedShader;
			Shader* normalShader;

			CubeManager cubeManager;



			BadTerrainTest terrain;

		public:

			Renderer() noexcept
				: instancedShader(nullptr), normalShader(nullptr), m_currentCamera(nullptr), m_currentProjection(nullptr), cubeManager(), m_deleteShader(false)
			{}

			//pointer to dynamic, or class owned shader, pointer to dynamic, or class owned pointer to camera, pointer to dynnamic, or class owned projection matrix
			//bool deleteshader this renderer deletes the shader with its destruktor call when its set to true | so if you have a shared shader in multiple renderers and you manage it/delete it in your game, then pass false as the boolean(just shader pointer passed as parameter, not new shader objekt created with new)
			Renderer(Shader* instanceShader, Shader* normalShader, logics::Camera** camera, maths::Mat4f* projection, unsigned int reserved = 10, bool deleteShader = true) noexcept
				: instancedShader(instanceShader), normalShader(normalShader), m_currentCamera(camera), m_currentProjection(projection), cubeManager(reserved, this), m_deleteShader(deleteShader)
			{
				prepare();
			}

			virtual ~Renderer() noexcept
			{
				if ( m_deleteShader )
				{
					delete instancedShader;
					delete normalShader;
				}
			}

			Renderer(const Renderer& other) = delete;

			Renderer(Renderer&& other) noexcept
				: instancedShader(other.instancedShader), normalShader(other.normalShader), m_currentCamera(other.m_currentCamera), m_currentProjection(other.m_currentProjection), m_deleteShader(other.m_deleteShader), cubeManager(std::move(other.cubeManager))
			{
				other.instancedShader = nullptr;
				other.normalShader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
			}

			Renderer& operator=(const Renderer& other) = delete;

			Renderer& operator=(Renderer&& other) noexcept
			{
				instancedShader = other.instancedShader;
				normalShader = other.normalShader;
				m_currentCamera = other.m_currentCamera;
				m_currentProjection = other.m_currentProjection;
				m_deleteShader = other.m_deleteShader;
				cubeManager = std::move(cubeManager);
				other.instancedShader = nullptr;
				other.normalShader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
				return *this;
			}

			//entweder das hier, den destruktor und ggf andere methoden virtual machen, oder durch public zugriff auf die shader sachen setzten | oder geht natürlich auch beides, aber auch dazu kommentieren, dass man virtuell erben kann, etc
			virtual void prepare() noexcept//virtual, kann überschrieben werden und andere uniformen setzten, etc | alles andere neu kommentieren und neu machen(auch virtual destruktor) | auch dazu kommentieren, dass man vom renderer erben kann und soll, wenn man im render loop etwas verändern will(genausop bei normalcube dazu schreiben und bei engine, etc)
			{
				instancedShader->enable();
				instancedShader->setUniform("u_texture1", 0);//keine ahnung, wie ich später einzelne uniformen entweder seperat über methoden vom shader setze, oder hier standard sachen, die für alle shader angenommen werden | auf jedenfall getshader methode machen und ggf setstandarduniforms, oder so
															  //setting uniforms, but shader has to be enabled first | here binds the texture1 uniform to the first texture pos in the shader | is not necessary for the first texture, if only one texture is used and not more

				normalShader->enable();
				normalShader->setUniform("u_texture1", 0);
			}

			virtual void render() noexcept
			{
				//und culling aktivieren für nicht transparent sachen
				glEnable(GL_CULL_FACE);
				instancedShader->enable();
				(*m_currentCamera)->update(instancedShader);//so ähnlich dann hier die verschiedenen modelle vorbereiten, dann texturen und dann positionen, etc schicken

				if ( cubeManager.m_instanceCubes.size() != 0 )
					cubeManager.renderInstancedCubes();


				normalShader->enable();
				( *m_currentCamera )->update(normalShader);

				if ( cubeManager.m_normalCubes.size() != 0 )
					cubeManager.renderNormalCubes();
				terrain.render(normalShader);

			}

			virtual void renderTransparent() noexcept
			{
				//ggf culling deaktivieren für transparent sachen 
				glDisable(GL_CULL_FACE);
				normalShader->enable();

				if ( cubeManager.m_transparentCubes.size() != 0 )
				cubeManager.renderTransparentCubes();
			}

			virtual void updateProjection() noexcept
			{
				instancedShader->enable();
				instancedShader->setUniform("u_projection", *m_currentProjection);
				normalShader->enable();
				normalShader->setUniform("u_projection", *m_currentProjection);

			}

		};

	}
}