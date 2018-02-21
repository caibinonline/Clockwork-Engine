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
#include <algorithm>
#include "src\Logics\States\State.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "CubeBorder.h"
#include "BorderManager.h"

namespace clockwork {
	namespace graphics {



		CubeBorder::CubeBorder(maths::Mat4f* modelMatrixPointer, bool deleteModelMatrixPointer, logics::State* state) noexcept
			: m_modelMatrixPointer(modelMatrixPointer), m_deleteModelMatrixPointer(deleteModelMatrixPointer), m_manager(&state->getDefaultRenderer().m_borderManager)
		{}

		CubeBorder::~CubeBorder() noexcept
		{
			remove();
			if ( m_deleteModelMatrixPointer )
				delete m_modelMatrixPointer;
		}

		void CubeBorder::add() noexcept
		{
			auto iterator = std::find(m_manager->m_cubeBorders.begin(), m_manager->m_cubeBorders.end(), this);
			if ( iterator == m_manager->m_cubeBorders.end() )
				return;
			m_manager->m_cubeBorders.push_back(this);

		}

		void CubeBorder::remove() noexcept
		{
 			auto iterator = std::find(m_manager->m_cubeBorders.begin(), m_manager->m_cubeBorders.end(), this);
			if ( iterator != m_manager->m_cubeBorders.end() )
				m_manager->m_cubeBorders.erase(iterator);
		}

	}
}