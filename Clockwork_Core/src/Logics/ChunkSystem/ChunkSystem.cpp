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
#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "ChunkSystem.h"


namespace clockwork {
	namespace logics {



		ChunkSystem::ChunkSystem(const maths::Vec3f& min, const maths::Vec3f& max, const maths::Vec3f& chunkSize, const maths::Vec3i& renderDistance, const maths::Vec3i& tickDistance, State* state) noexcept
			: m_min(min), m_max(max), m_chunkSize(chunkSize), m_state(state), m_renderDistance(renderDistance), m_tickDistance(tickDistance)
		{
			maths::Vec3<float> count = ( max - min ) / chunkSize;
			m_count.x = maths::ceil(count.x);
			m_count.y = maths::ceil(count.y);
			m_count.z = maths::ceil(count.z);

			m_chunks = new Chunk**[m_count.x];
			for ( int x = 0; x < m_count.x; ++x )
			{
				m_chunks[x] = new Chunk*[m_count.y];
				for ( int y = 0; y < m_count.x; ++y )
				{
					m_chunks[x][y] = new Chunk[m_count.z];
					for ( int z = 0; z < m_count.x; ++z )
					{
						maths::Vec3<float> tempMin
						{ min.x + x * chunkSize.x,
							min.y + y * chunkSize.y,
							min.z + z * chunkSize.z };
						maths::Vec3<float> tempMax
						{ maths::min(tempMin.x + chunkSize.x, max.x),
							maths::min(tempMin.y + chunkSize.y, max.y),
							maths::min(tempMin.z + chunkSize.z, max.z) };
						m_chunks[x][y][z].init(tempMin, tempMax, x, y, z, this);
					}
				}
			}

#if CLOCKWORK_DEBUG 
			if ( m_renderDistance >= m_count )
				std::cout << "Error ChunkSystem::ChunkSystem(): RenderDistance too big" << std::endl;
			if ( m_tickDistance >= m_count )
				std::cout << "Error ChunkSystem::ChunkSystem(): TickDistance too big" << std::endl;
#endif
			m_currentChunk = &getChunkAt(m_state->getCurrentCamera().getPosition());
			struct RenderAddFunctor
			{
				void function(Chunk& chunk) noexcept
				{
					chunk.renderAdd();
				}
			};
			passFunctionToChunks<RenderAddFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
		}

		ChunkSystem::~ChunkSystem() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					delete[] m_chunks[x][y];
				}
				delete m_chunks[x];
			}
			delete[] m_chunks;
		}

		const Chunk& ChunkSystem::getChunk(const maths::Vec3i& id) const noexcept
		{
			return m_chunks[id.x][id.y][id.z];
		}
		Chunk& ChunkSystem::getChunk(const maths::Vec3i& id) noexcept
		{
			return m_chunks[id.x][id.y][id.z];
		}
		const Chunk& ChunkSystem::getChunk(int idX, int idY, int idZ) const noexcept
		{
			return m_chunks[idX][idY][idZ];
		}
		Chunk& ChunkSystem::getChunk(int idX, int idY, int idZ) noexcept
		{
			return m_chunks[idX][idY][idZ];
		}
		const Chunk& ChunkSystem::getChunkAt(const maths::Vec3f& position) const noexcept
		{
			return m_chunks[static_cast<int>( maths::floor(( position.x - m_min.x ) / m_chunkSize.x) )][static_cast<int>( maths::floor(( position.y - m_min.y ) / m_chunkSize.y) )][static_cast<int>( maths::floor(( position.z - m_min.z ) / m_chunkSize.z) )];
		}
		Chunk& ChunkSystem::getChunkAt(const maths::Vec3f& position) noexcept
		{
			return m_chunks[static_cast<int>( maths::floor(( position.x - m_min.x ) / m_chunkSize.x) )][static_cast<int>( maths::floor(( position.y - m_min.y ) / m_chunkSize.y) )][static_cast<int>( maths::floor(( position.z - m_min.z ) / m_chunkSize.z) )];
		}

		const unsigned int ChunkSystem::getBytes() const noexcept
		{
			return m_count.x*m_count.y*m_count.z * sizeof(Chunk);
		}
		const unsigned int ChunkSystem::getChunkCount() const noexcept
		{
			return m_count.x*m_count.y*m_count.z;
		}

		void  ChunkSystem::update() noexcept
		{
			if ( *m_currentChunk != getChunkAt(m_state->getCurrentCamera().getPosition()) )
			{
				Chunk& oldChunk = *m_currentChunk;
				Chunk& newChunk = getChunkAt(m_state->getCurrentCamera().getPosition());
				maths::Vec3i diffrence = newChunk.getId() - oldChunk.getId();
				std::cout << diffrence << std::endl;

// 				struct RenderAddFunctor
// 				{
// 					void function(Chunk& chunk) noexcept
// 					{
// 						chunk.renderAdd();
// 					}
// 				};
// 				passFunctionToChunks<RenderAddFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);

				//hier renderadd/renderremove mit currentchunklist vergleichen, etc ... | am besten gucken wie id ist was schon in renderrange liegt und was dann nicht mehr, etc | WICHTIG auch bei setrenderdistance, etc verändern 

				//beim erstellen müssen die einzelnen renderlistener objekte sich aber auch schon renderAdd von sich aufrufen, wenn der chunk, dem sie hinzugefügt werden in renderrange vom currentchunk ist(ggf methode in chunk machen inRenderRange() ) | das darf aber nicht im konstruktor von renderlistener geschehen, da renderadd wahrscheinlich virtuelle methode ist und der subklassenanteil noch nicht erstellt ist 
				//ggf aus subklassenkonstruktor von dem erbenden gameobject check methode, oder so der superklasse aufrufen(ist dann protected methode) | renderadd und renderremove werden ja dann virtuell überschrieben und werden von den modellen add und remove aufrufen(immer) | bei den modell methoden add/remove wird intern dann noch getestet, ob sie schon added/removed wurden und dann wird dies nicht ausgeführt
				//visible bool, etc von gameobject muss dann in renderadd/renderremove von gameobject geregelt werden, wo es an die modelle weitergeleitet wird 
				//gameobject hat dann wahrscheinlich auch nur noch einen chunk pointer auf aktuellen chunk und eine move funktion zu neuem chunk(von allen pointer listen render/tick/etc entfernen und beim neuen adden(ggf renderadd/renderremove aufrufen, wenn in rendersichtweite)
				//alwaysactive chunk nicht vergessen | dafür ggf noch bool in konstruktor von gameobject mitgeben, ob alwaysactive, oder nicht und dementsprechend wird es hinzugefügt | alwaysactivechunk kann auch von einer anderen klasse sein mit nur den listen ohne position, id, etc
				//von normalem chunk zu alwaysactive chunk und andersherum moven wird schwer

				m_currentChunk = &newChunk;
			}
		}

		void ChunkSystem::tickAll() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						m_chunks[x][y][z].tick();
					}
				}
			}
		}

		void ChunkSystem::tick() noexcept
		{
			struct TickFunctor
			{
				void function(Chunk& chunk) noexcept
				{
					chunk.tick();
				}
			};
			passFunctionToChunks<TickFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
		}

		void ChunkSystem::slowTickAll() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						m_chunks[x][y][z].slowTick();
					}
				}
			}
		}

		void ChunkSystem::slowTick() noexcept
		{
			struct SlowTickFunctor
			{
				void function(Chunk& chunk) noexcept
				{
					chunk.slowTick();
				}
			};
			passFunctionToChunks<SlowTickFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
		}

		template<typename functor>void ChunkSystem::passFunctionToChunks(const maths::Vec3<int>& pos1, const maths::Vec3<int>& pos2) noexcept
		{
			functor funct { };

			for ( int x = pos1.x; x <= pos2.x; ++x )
			{
				for ( int y = pos1.y; y <= pos2.y; ++y )
				{
					for ( int z = pos1.z; z <= pos2.z; ++z )
					{
						if ( x < 0 )
						{
							int newX = m_count.x + x;
							if ( y < 0 )
							{
								int newY = m_count.y + y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else
								{
									funct.function(m_chunks[newX][newY][z]);
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else
								{
									funct.function(m_chunks[newX][newY][z]);
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								funct.function(m_chunks[newX][y][newZ]);
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								funct.function(m_chunks[newX][y][newZ]);
							}
							else
							{
								funct.function(m_chunks[newX][y][z]);
							}
						}
						else if ( x >= m_count.x )
						{
							int newX = x - m_count.x;
							if ( y < 0 )
							{
								int newY = m_count.y + y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else
								{
									funct.function(m_chunks[newX][newY][z]);
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									funct.function(m_chunks[newX][newY][newZ]);
								}
								else
								{
									funct.function(m_chunks[newX][newY][z]);
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								funct.function(m_chunks[newX][y][newZ]);
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								funct.function(m_chunks[newX][y][newZ]);
							}
							else
							{
								funct.function(m_chunks[newX][y][z]);
							}
						}
						else if ( y < 0 )
						{
							int newY = m_count.y + y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								funct.function(m_chunks[x][newY][newZ]);
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								funct.function(m_chunks[x][newY][newZ]);
							}
							else
							{
								funct.function(m_chunks[x][newY][z]);
							}
						}
						else if ( y >= m_count.y )
						{
							int newY = y - m_count.y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								funct.function(m_chunks[x][newY][newZ]);
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								funct.function(m_chunks[x][newY][newZ]);
							}
							else
							{
								funct.function(m_chunks[x][newY][z]);
							}
						}
						else if ( z < 0 )
						{
							int newZ = m_count.z + z;
							funct.function(m_chunks[x][y][newZ]);
						}
						else if ( z >= m_count.z )
						{
							int newZ = z - m_count.z;
							funct.function(m_chunks[x][y][newZ]);
						}
						else
						{
							funct.function(m_chunks[x][y][z]);
						}
					}
				}
			}
		}

	}
}