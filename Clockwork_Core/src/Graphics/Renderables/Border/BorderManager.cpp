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
#include "BorderManager.h"
#include "CubeBorder.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "src\Graphics\Renderer\Shader.h"

namespace clockwork {
	namespace graphics {

		BorderManager::BorderManager(Renderer* renderer)
			: m_renderer(renderer)
		{
			m_vbo = VertexBuffer(	  floatarr//floats
										  {//positions          
					-1,-1,-1,
					1,-1,-1,

					1,-1,1,
					-1,-1,1,

					-1,1,-1,
					1,1,-1,

					1,1,1,
					-1,1,1

								 }, 8 * 3 *sizeof(float)
			);
			m_ibo = IndexBuffer<unsigned char>(uchararr {
				0,1, 1,2, 2,3, 3,0, 
				0,4, 1,5, 2,6, 3,7,
				7,4, 4,5, 5,6, 6,7
											   },24);
			m_vbo.connectToVao<float>(3, false, 3 * sizeof(float));
		}

		void BorderManager::render() noexcept
		{
			for ( unsigned int i = 0; i < m_cubeBorders.size(); ++i )
			{
				m_renderer->m_borderShader->setUniform("u_model", *m_cubeBorders[i]->m_modelMatrixPointer);
				m_vao.bind();
				m_ibo.drawLine();
			}
		}

	}
}