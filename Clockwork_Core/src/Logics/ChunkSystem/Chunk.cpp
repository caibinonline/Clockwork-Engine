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
#include "ChunkSystem.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "src\Logics\Entities\Listener\RenderListener.h"
#include "Chunk.h"

namespace clockwork {
	namespace logics {

		void Chunk::init(const maths::Vec3f& min, const maths::Vec3f& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept
		{
			m_min = min;
			m_max = max;
			m_id.x = idX;
			m_id.y = idY;
			m_id.z = idZ;
			m_chunkSystem = chunkSystem;
		}

		void Chunk::renderAdd() noexcept
		{
			//std::cout << "RenderAdd: " << m_id << std::endl;
			if ( !m_renderList.empty() )
				for ( auto listener : m_renderList )
					( *listener ).renderAdd();
		}

		void Chunk::renderRemove() noexcept
		{
			//std::cout << "RenderRemove: " << m_id << std::endl;
			if(!m_renderList.empty() )
				for ( auto listener : m_renderList )
					( *listener ).renderRemove();
		}

		void Chunk::tick() noexcept
		{

		}

		void Chunk::slowTick() noexcept
		{

		}

		void Chunk::addRenderListener(RenderListener* listener) noexcept
		{
			m_renderList.push_back(listener);
		}

		void Chunk::removeRenderListener(RenderListener* listener) noexcept
		{
			auto iterator = std::find(m_renderList.begin(), m_renderList.end(), listener);
#if CLOCKWORK_DEBUG
			if ( iterator == m_renderList.end() )
				std::cout << "Error Chunk::removeRenderListener(): The listener pointer is not in the renderList" << std::endl;
#endif
			m_renderList.erase(iterator);

		}

		template<typename functor>void Chunk::passFunctionToArea() noexcept
		{
			m_chunkSystem->passFunctionToChunks<functor>(m_id - 1, m_id + 1);
		}

		const bool Chunk::inRenderDistance() const noexcept
		{
			const maths::Vec3i& otherId = m_chunkSystem->getCurrentChunk().getId();
			const maths::Vec3i& renderDistance = m_chunkSystem->getRenderDistance();
			if ( m_id.x >= otherId.x - renderDistance.x && m_id.x <= otherId.x + renderDistance.x && m_id.y >= otherId.y - renderDistance.y&& m_id.y <= otherId.y + renderDistance.y && m_id.z >= otherId.z - renderDistance.z && m_id.z <= otherId.z + renderDistance.z )
				return true;
			else
				return false;
		}

		bool operator==(const Chunk& c1, const Chunk& c2) noexcept
		{
			return c1.m_id == c2.m_id;
		}

		bool operator!=(const Chunk& c1, const Chunk& c2) noexcept
		{
			return c1.m_id != c2.m_id;
		}

	}
}
