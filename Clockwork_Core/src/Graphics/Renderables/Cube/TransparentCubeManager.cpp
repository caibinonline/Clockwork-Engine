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
#include "InstancedCube.h"
#include "NormalCube.h"
#include "TransparentCubeManager.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "src\Logics\Camera\Camera.h"
#include <algorithm>


namespace clockwork {
	namespace graphics {

		struct NormalCubeCompare//namen und alle prototypes ändern zu TransparentCubeCompare
		{
			TransparentCubeManager* m_manager;
			NormalCubeCompare(TransparentCubeManager* manager)
				:m_manager(manager)
			{}
			inline bool operator()(NormalCube* ptr1, NormalCube* ptr2)
			{
				return ptr1->position.distance(( *m_manager->m_renderer->m_currentCamera )->getPosition()) > ptr2->position.distance(( *m_manager->m_renderer->m_currentCamera )->getPosition());
			}
		};

		TransparentCubeManager::TransparentCubeManager() noexcept
			: CubeManager()
		{
			m_transparent = true;
		}

		TransparentCubeManager::TransparentCubeManager(unsigned int reserved, Renderer* renderer) noexcept
			: CubeManager(reserved, renderer)
		{
			m_transparent = true;
		}

		void TransparentCubeManager::renderInstancedCubes() noexcept
		{
// 			m_textureArray.bind();
// 			m_copyBuffer.bind();
// 			m_modelBuffer.bind();
// 			std::sort(m_instanceCubes.begin(), m_instanceCubes.end(), InstancedCubeCompare {this});
// 			for ( unsigned int i = 0; i < m_instanceCubes.size(); ++i )
// 			{
// 				InstancedCube* cube = m_instanceCubes.at(i);
// 				cube->m_pos = i;
// 				cube->updateBufferData();
// 			}
// 			m_modelBuffer.copy(m_copyBuffer);
// 			m_instanceArray.bind();
// 			m_indexBuffer.drawInstanced(m_instanceCubes.size());
		}

		void TransparentCubeManager::renderNormalCubes() noexcept
		{
			m_normalArray.bind();
			std::sort(m_normalCubes.begin(), m_normalCubes.end(), NormalCubeCompare { this });
			for ( unsigned int i = 0; i < m_normalCubes.size(); ++i )
			{
				NormalCube* cube = m_normalCubes.at(i);
				cube->m_pos = i;
				if ( cube->m_visible )
				{
					cube->updateModelMatrix();
					m_textures.at(cube->m_textureId).bind();
					cube->render();

					const maths::Vec3f& cameradirection = (*m_renderer->m_currentCamera)->getPosition();
					//hier testen ob die camera auf welche seiten zeigt 


					m_indexBuffer.draw();
				}
			}
		}



	}
}