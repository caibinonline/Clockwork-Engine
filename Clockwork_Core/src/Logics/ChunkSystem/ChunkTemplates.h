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

#include "Chunk.h"
#include "ChunkSystem.h"

namespace clockwork {
	namespace logics {
		template<typename functor>void Chunk::passFunctionToArea() noexcept
		{
			m_chunkSystem->passFunctionToChunks<functor>(m_id - 1, m_id + 1);
		}

		template<typename functor>void ChunkSystem::passFunctionToChunks(const maths::Vec3<int>& pos1, const maths::Vec3<int>& pos2) noexcept
		{
			functor funct {};
#if CLOCKWORK_DEBUG
			if ( pos1.x < 0 || pos1.y < 0 || pos1.z < 0 )
				std::cout << "Error ChunkSystem::passFunctionToChunks(): pos1 is below 0" << std::endl;
			if ( pos2.x >= m_count.x || pos2.y >= m_count.y || pos2.z >= m_count.z )
				std::cout << "Error ChunkSystem::passFunctionToChunks(): pos2 is above, or equal to count of the chunksystem" << std::endl;
#endif

			for ( int x = pos1.x; x <= pos2.x; ++x )
			{
				for ( int y = pos1.y; y <= pos2.y; ++y )
				{
					for ( int z = pos1.z; z <= pos2.z; ++z )
					{
						funct.function(m_chunks[x][y][z]);
					}
				}
			}
		}

		template<typename functor>void ChunkSystem::passFunctionToAll() noexcept
		{
			functor funct {};
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						funct.function(m_chunks[x][y][z]);
					}
				}
			}
		}

	}
}



