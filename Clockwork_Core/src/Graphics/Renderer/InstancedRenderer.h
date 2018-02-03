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

namespace clockwork {
	namespace graphics {

		class InstancedRenderer
		{

		private:
			Shader * m_shader;
			logics::Camera** m_currentCamera;
			maths::Mat4f* m_currentProjection;
			bool m_deleteShader;

		public:
			CubeManager cubeManager;

		public:

			InstancedRenderer() noexcept
				: m_shader(nullptr), m_currentCamera(nullptr), m_currentProjection(nullptr), cubeManager(), m_deleteShader(false)
			{}

			//pointer to dynamic, or class owned shader, pointer to dynamic, or class owned pointer to camera, pointer to dynnamic, or class owned projection matrix
			//bool deleteshader this renderer deletes the shader with its destruktor call when its set to true | so if you have a shared shader in multiple renderers and you manage it/delete it in your game, then pass false as the boolean(just shader pointer passed as parameter, not new shader objekt created with new)
			InstancedRenderer(Shader* shader, logics::Camera** camera, maths::Mat4f* projection, unsigned int reserved = 10, bool deleteShader = true) noexcept
				: m_shader(shader), m_currentCamera(camera), m_currentProjection(projection), cubeManager(reserved), m_deleteShader(deleteShader)
			{
				m_shader->enable();
				m_shader->setUniform("u_texture1", 0);//keine ahnung, wie ich später einzelne uniformen entweder seperat über methoden vom shader setze, oder hier standard sachen, die für alle shader angenommen werden | auf jedenfall getshader methode machen und ggf setstandarduniforms, oder so
				//setting uniforms, but shader has to be enabled first | here binds the texture1 uniform to the first texture pos in the shader | is not necessary for the first texture, if only one texture is used and not more
			}

			~InstancedRenderer() noexcept
			{
				if ( m_deleteShader )
					delete m_shader;
			}

			InstancedRenderer(const InstancedRenderer& other) = delete;

			InstancedRenderer(InstancedRenderer&& other) noexcept///WICHTIG auch für alle anderen cubemanager moven, etc, wenn meherere manager da sind
				: m_shader(other.m_shader), m_currentCamera(other.m_currentCamera), m_currentProjection(other.m_currentProjection), m_deleteShader(other.m_deleteShader), cubeManager(std::move(other.cubeManager))
			{
				other.m_shader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
			}

			InstancedRenderer& operator=(const InstancedRenderer& other) = delete;

			InstancedRenderer& operator=(InstancedRenderer&& other) noexcept
			{
				m_shader = other.m_shader;
				m_currentCamera = other.m_currentCamera;
				m_currentProjection = other.m_currentProjection;
				m_deleteShader = other.m_deleteShader;
				cubeManager = std::move(cubeManager);
				other.m_shader = nullptr;
				other.m_currentCamera = nullptr;
				other.m_currentProjection = nullptr;
				other.m_deleteShader = false;
				return *this;
			}

			void render() noexcept
			{
				m_shader->enable();
				(*m_currentCamera)->update(m_shader);//so ähnlich dann hier die verschiedenen modelle vorbereiten, dann texturen und dann positionen, etc schicken
				cubeManager.render();

			}

			void updateProjection() noexcept
			{
				m_shader->enable();
				m_shader->setUniform("u_projection", *m_currentProjection);
			}

		};

	}
}