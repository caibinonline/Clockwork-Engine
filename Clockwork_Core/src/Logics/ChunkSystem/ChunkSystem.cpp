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



		ChunkSystem::ChunkSystem(const maths::Vec3<float>& min, const maths::Vec3<float>& max, const maths::Vec3<float>& chunkSize, State* state) noexcept
			: m_min(min), m_max(max), m_chunkSize(chunkSize), m_state(state)
		{
			maths::Vec3<float> count = ( max - min ) / chunkSize;
			m_count.x = clockwork::maths::ceil(count.x);
			m_count.y = clockwork::maths::ceil(count.y);
			m_count.z = clockwork::maths::ceil(count.z);

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
							min.z + z * chunkSize.z};
						maths::Vec3<float> tempMax
						{ maths::min(tempMin.x + chunkSize.x, max.x),
							maths::min(tempMin.y + chunkSize.y, max.y),
							maths::min(tempMin.z + chunkSize.z, max.z)};
						m_chunks[x][y][z].init(tempMin, tempMax, x, y, z, this);
					}
				}
			}


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

		const unsigned int ChunkSystem::getBytes() const noexcept
		{
			return m_count.x*m_count.y*m_count.z * sizeof(Chunk);
		}
		const unsigned int ChunkSystem::getChunkCount() const noexcept
		{
			return m_count.x*m_count.y*m_count.z;
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

		void ChunkSystem::tick(const maths::Vec3<int>& chunkid, int range) noexcept
		{
			for ( int x = chunkid.x - range; x < chunkid.x + range + 1; ++x )
			{
				for ( int y = chunkid.y - range; y < chunkid.y + range + 1; ++y )
				{
					for ( int z = chunkid.z - range; z < chunkid.z + range + 1; ++z )
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
									m_chunks[newX][newY][newZ].tick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].tick();
								}
								else
								{
									m_chunks[newX][newY][z].tick();
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									m_chunks[newX][newY][newZ].tick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].tick();
								}
								else
								{
									m_chunks[newX][newY][z].tick();
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[newX][y][newZ].tick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[newX][y][newZ].tick();
							}
							else
							{
								m_chunks[newX][y][z].tick();
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
									m_chunks[newX][newY][newZ].tick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].tick();
								}
								else
								{
									m_chunks[newX][newY][z].tick();
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									m_chunks[newX][newY][newZ].tick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].tick();
								}
								else
								{
									m_chunks[newX][newY][z].tick();
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[newX][y][newZ].tick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[newX][y][newZ].tick();
							}
							else
							{
								m_chunks[newX][y][z].tick();
							}

						}
						else if ( y < 0 )
						{
							int newY = m_count.y + y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[x][newY][newZ].tick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[x][newY][newZ].tick();
							}
							else
							{
								m_chunks[x][newY][z].tick();
							}
						}
						else if ( y >= m_count.y )
						{
							int newY = y - m_count.y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[x][newY][newZ].tick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[x][newY][newZ].tick();
							}
							else
							{
								m_chunks[x][newY][z].tick();
							}
						}
						else if ( z < 0 )
						{
							int newZ = m_count.z + z;
							m_chunks[x][y][newZ].tick();
						}
						else if ( z >= m_count.z )
						{
							int newZ = z - m_count.z;
							m_chunks[x][y][newZ].tick();
						}
						else
						{
							m_chunks[x][y][z].tick();
						}
					}
				}
			}
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

		void ChunkSystem::slowTick(const maths::Vec3<int>& chunkid, int range) noexcept
		{
			for ( int x = chunkid.x - range; x < chunkid.x + range + 1; ++x )
			{
				for ( int y = chunkid.y - range; y < chunkid.y + range + 1; ++y )
				{
					for ( int z = chunkid.z - range; z < chunkid.z + range + 1; ++z )
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
									m_chunks[newX][newY][newZ].slowTick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else
								{
									m_chunks[newX][newY][z].slowTick();
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else
								{
									m_chunks[newX][newY][z].slowTick();
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[newX][y][newZ].slowTick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[newX][y][newZ].slowTick();
							}
							else
							{
								m_chunks[newX][y][z].slowTick();
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
									m_chunks[newX][newY][newZ].slowTick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else
								{
									m_chunks[newX][newY][z].slowTick();
								}
							}
							else if ( y >= m_count.y )
							{
								int newY = y - m_count.y;
								if ( z < 0 )
								{
									int newZ = m_count.z + z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else if ( z >= m_count.z )
								{
									int newZ = z - m_count.z;
									m_chunks[newX][newY][newZ].slowTick();
								}
								else
								{
									m_chunks[newX][newY][z].slowTick();
								}
							}
							else if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[newX][y][newZ].slowTick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[newX][y][newZ].slowTick();
							}
							else
							{
								m_chunks[newX][y][z].slowTick();
							}

						}
						else if ( y < 0 )
						{
							int newY = m_count.y + y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[x][newY][newZ].slowTick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[x][newY][newZ].slowTick();
							}
							else
							{
								m_chunks[x][newY][z].slowTick();
							}
						}
						else if ( y >= m_count.y )
						{
							int newY = y - m_count.y;
							if ( z < 0 )
							{
								int newZ = m_count.z + z;
								m_chunks[x][newY][newZ].slowTick();
							}
							else if ( z >= m_count.z )
							{
								int newZ = z - m_count.z;
								m_chunks[x][newY][newZ].slowTick();
							}
							else
							{
								m_chunks[x][newY][z].slowTick();
							}
						}
						else if ( z < 0 )
						{
							int newZ = m_count.z + z;
							m_chunks[x][y][newZ].slowTick();
						}
						else if ( z >= m_count.z )
						{
							int newZ = z - m_count.z;
							m_chunks[x][y][newZ].slowTick();
						}
						else
						{
							m_chunks[x][y][z].slowTick();
						}
					}
				}
			}
		}

	}
}