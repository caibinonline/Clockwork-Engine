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
// 			m_vbo = VertexBuffer(//you could also create a local nameless array of vertices, where vertex is a struct with vec2 of float for position and vec2 of float for colour
// 										  floatarr//floats
// 										  {//positions          texture coords	 vertex normals
// 										   //back
// 											  -1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,//0
// 											  1.0f, -1.0f, 1.0f,      1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
// 											  -1.0f, 1.0f, 1.0f,      0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
// 											  1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
// 											  //top								
// 											  -1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f, //4
// 											  1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
// 											  -1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
// 											  1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
// 											  //front							
// 											  -1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,//8
// 											  1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
// 											  -1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
// 											  1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
// 											  //bot								
// 											  -1.0f, -1.0f, -1.0f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,//12
// 											  1.0f, -1.0f, -1.0f,     0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
// 											  -1.0f, -1.0f,  1.0f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
// 											  1.0f, -1.0f,  1.0f,     0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
// 											  //right			    			    
// 											  1.0f, -1.0f,  1.0f,     0.0f, 0.0f,     1.0f,  0.0f, 0.0f,//16
// 											  1.0f, -1.0f, -1.0f,     1.0f, 0.0f,     1.0f,  0.0f, 0.0f,
// 											  1.0f,  1.0f,  1.0f,     0.0f, 1.0f,     1.0f,  0.0f, 0.0f,
// 											  1.0f,  1.0f, -1.0f,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
// 											  //left				    			    
// 											  -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,//20
// 											  -1.0f, -1.0f, 1.0f,	    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
// 											  -1.0f, 1.0f, -1.0f,	    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
// 											  -1.0f, 1.0f, 1.0f,	    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f
// 										  }, 8 * 4 * 6 * sizeof(float)
// 			);

			//WICHTIG in indexbuffer noch drawlines, oder drawpoints methode machen 


// 			m_positions.push_back(maths::Vec3f { -1,-1,-1 });
// 			m_positions.push_back(maths::Vec3f { 1,-1,-1 });
// 
// 			m_positions.push_back(maths::Vec3f { -1,-1,1 });
// 			m_positions.push_back(maths::Vec3f { 1,-1,1 });
// 
// 
// 			m_positions.push_back(maths::Vec3f { -1,1,-1 });
// 			m_positions.push_back(maths::Vec3f { 1,1,-1 });
// 
// 			m_positions.push_back(maths::Vec3f { -1,1,1 });
// 			m_positions.push_back(maths::Vec3f { 1,1,1 });
// 				for ( unsigned int i = 0; i < 4; ++i )
// 				{
// 					if ( i % 2 == 0 )
// 						glBegin(GL_LINES);
// 					vec = mat * m_positions.at(i);
// 					glVertex3f(vec.x, vec.y, vec.z);
// 					if ( i ==1 )
// 						glEnd();
// 				}
// 				vec = mat * m_positions.at(0);
// 				glVertex3f(vec.x, vec.y, vec.z);
// 				glEnd();
// 
// 				for ( unsigned int i = 4; i < 8; ++i )
// 				{
// 					if ( i % 2 == 0 )
// 						glBegin(GL_LINES);
// 					vec = mat * m_positions.at(i);
// 					glVertex3f(vec.x, vec.y, vec.z);
// 					if ( i == 5 )
// 						glEnd();
// 				}
// 				vec = mat * m_positions.at(4);
// 				glVertex3f(vec.x, vec.y, vec.z);
// 				glEnd();
// 
// 				for ( unsigned int i = 0; i < 4; ++i )
// 				{
// 					vec = mat * m_positions.at(i);
// 					glVertex3f(vec.x, vec.y, vec.z);
// 
// 					vec = mat * m_positions.at(i+4);
// 					glVertex3f(vec.x, vec.y, vec.z);
// 				}
		}

		void BorderManager::render() noexcept
		{
			for ( unsigned int i = 0; i < m_cubeBorders.size(); ++i )
			{
				m_renderer->m_borderShader->setUniform("u_model", *m_cubeBorders[i]->m_modelMatrixPointer);



			}
		}

	}
}