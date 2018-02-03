#pragma once
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
#include "src\Graphics\Renderer\Shader.h"
#include "src\Logics\Camera\Camera.h"




#include "src\Graphics\Renderables\BadTerrainTest.h"

namespace clockwork {
	namespace graphics {

		class NormalRenderer///NICHT FGERTIG, VON INSTANCEDRENDERER KOPIEREN, NOCH FALSCH 
		{
		private:
			Shader * m_shader;//pro shader ein renderer | ggf auch für terrain/ui eigene renderer
			logics::Camera** m_currentCamera;//pointer auf aktuelle camera pointer des states | alles hat eine camera
			maths::Mat4f* m_currentProjection;//muss bei updates neu an shader gesendet werden, also von state aufgerufen werden | methode update, oder so | pointer auf prohjection, kann geändert werden, gibt verschiedenne(ortographic/perspective)
			//ggf std::vector<model*> modellist 



			BadTerrainTest terrain;

		public:

			NormalRenderer() noexcept
				: m_shader(nullptr), m_currentCamera(nullptr), m_currentProjection(nullptr)
			{}

			//pointer to dynamic, or class owned shader, pointer to dynamic, or class owned pointer to camera, pointer to dynnamic, or class owned projection matrix
			NormalRenderer(Shader* shader, logics::Camera** camera, maths::Mat4f* projection) noexcept
				: m_shader(shader), m_currentCamera(camera), m_currentProjection(projection)
			{
				m_shader->enable();
				m_shader->setUniform("u_texture1", 0);
			}

			void render() noexcept
			{
				m_shader->enable();
				(*m_currentCamera)->update(m_shader);//so ähnlich dann hier die verschiedenen modelle vorbereiten, dann texturen und dann positionen, etc schicken

				terrain.render(m_shader);

			}

			void updateProjection() noexcept
			{
				m_shader->enable();
				m_shader->setUniform("u_projection", *m_currentProjection);
			}

		};

	}
}