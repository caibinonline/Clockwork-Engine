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
#include "ChunkSystem.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "Chunk.h"

namespace clockwork {
	namespace logics {

		void Chunk::init(const maths::Vec3<float>& min, const maths::Vec3<float>& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept
		{
			m_min = min;
			m_max = max;
			m_id.x = idX;
			m_id.y = idY;
			m_id.z = idZ;
			m_chunkSystem = chunkSystem;
		}

		void Chunk::tick() noexcept
		{
			std::cout << m_id << std::endl;
		}

		void Chunk::slowTick() noexcept
		{

		}

	}
}
