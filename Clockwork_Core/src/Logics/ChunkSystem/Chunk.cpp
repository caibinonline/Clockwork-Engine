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
#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "src\Logics\Entities\Listener\RenderListener.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "ChunkTemplates.h"
#include "src\Graphics\Renderables\Border\CubeBorder.h"

namespace clockwork {
	namespace logics {

		Chunk::Chunk() noexcept
			: m_chunkSystem(nullptr)
#if CHUNK_BORDER
			, m_border(nullptr)
#endif
		{

		}

		Chunk::~Chunk() noexcept//hier später wahrscheinlich alle gameobjects löschem
		{
#if CHUNK_BORDER
			if ( m_border )
			{
				delete m_border;
				m_border = nullptr;
			}
#endif
		}

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
			for ( unsigned int i = 0; i < m_renderList.size(); ++i )
			{
				m_renderList[i]->renderAdd();
			}
#if CHUNK_BORDER
			if ( !m_border )
			{
				maths::Mat4f* modelmatrix = new maths::Mat4f();
				modelmatrix->scale(m_chunkSystem->m_chunkSize*0.5 - 0.001).translate(m_min + ( m_max - m_min ) / 2);
				m_border = new graphics::CubeBorder(modelmatrix,true,&m_chunkSystem->getState());
				m_border->add();
			}
#endif
		}

		void Chunk::renderRemove() noexcept
		{
			for ( unsigned int i = 0; i < m_renderList.size(); ++i )
			{
				m_renderList[i]->renderRemove();
			}
#if CHUNK_BORDER
			if ( m_border )
			{
				delete m_border;
				m_border = nullptr;
			}
#endif
		}

		void Chunk::tick() noexcept
		{
			for ( unsigned int i = 0; i < m_movingTickList.size(); ++i )
			{
				MovingTickListener* listener = m_movingTickList[i];
				listener->tick();
				if ( m_chunkSystem->getChunkAt(listener->getPosition()) != *this )
				{
					Chunk& newChunk = m_chunkSystem->getChunkAt(listener->getPosition());
					this->removeMovingTickListener(listener);
					newChunk.addMovingTickListener(listener);
					RenderListener* r_listener  = dynamic_cast<RenderListener*>(listener);//WICHTIG AUCH FÜR ALLE ANDEREN LISTENER MACHEN(ausser static tick listener), aber keylistener, etc auch mit dynamic cast überprüfen
					if ( r_listener != nullptr )
					{
						this->removeRenderListener(r_listener);
						newChunk.addRenderListener(r_listener);
						if ( this->inRenderDistance()==true && newChunk.inRenderDistance() == false )
						{
							r_listener->renderRemove();
						}
						else if ( this->inRenderDistance() == false && newChunk.inRenderDistance() == true )
						{
							r_listener->renderAdd();
						}
					}
					listener->setChunk(&newChunk);
				}
			}
		}

		void Chunk::slowTick() noexcept
		{
			for ( unsigned int i = 0; i < m_movingTickList.size(); ++i )
			{
				m_movingTickList[i]->slowTick();
			}
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

		void Chunk::addMovingTickListener(MovingTickListener* listener) noexcept
		{
			m_movingTickList.push_back(listener);
		}

		void Chunk::removeMovingTickListener(MovingTickListener* listener) noexcept
		{
			auto iterator = std::find(m_movingTickList.begin(), m_movingTickList.end(), listener);
#if CLOCKWORK_DEBUG
			if ( iterator == m_movingTickList.end() )
				std::cout << "Error Chunk::removeMovingTickListener(): The listener pointer is not in the movingTickList" << std::endl;
#endif
			m_movingTickList.erase(iterator);
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

		const ChunkSystem& Chunk::getChunkSystem() const noexcept
		{
			return *m_chunkSystem;
		}

		ChunkSystem& Chunk::getChunkSystem() noexcept
		{
			return *m_chunkSystem;
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
