#pragma once
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
#include "src\Maths\Vec4.h"
#include "src\Maths\MathFunctions.h"

namespace clockwork {
	namespace utils {

		struct ChunkSystem2;
		struct Chunk
		{
			maths::Vec3<float> m_min;
			maths::Vec3<float> m_max;
			maths::Vec3<int> m_id;
			ChunkSystem2* m_ChunkSystem2;//vielleicht wird dieses nicht gebraucht, da über state auf ChunkSystem2 zugegriffen werden kann und hier ggf state gespeichert werden muss

			Chunk() noexcept
			{

			}

			~Chunk() noexcept
			{

			}

			void init(const maths::Vec3<float>& min, const maths::Vec3<float>& max, const maths::Vec3<int>& id, ChunkSystem2* ChunkSystem2) noexcept;

			void tick() noexcept
			{
				std::cout << m_id << std::endl;
			}

		};

		struct ChunkSystem2
		{
			friend struct Chunk;
			maths::Vec3<float> m_min;
			maths::Vec3<float> m_max;
			maths::Vec3<float> m_chunkSize;
			maths::Vec3<int> m_count;
			Chunk*** m_chunks;

			ChunkSystem2(const maths::Vec3<float>& min, const maths::Vec3<float>& max, const maths::Vec3<float>& chunksize) noexcept///das hier alles optimieren ohne temporäre objekte, indem die sachen direkt berechnet werden
				: m_min(min), m_max(max), m_chunkSize(chunksize)
			{
				maths::Vec3<float> count = ( max - min ) / chunksize;
				m_count.x = clockwork::maths::ceil(count.x);
				m_count.y = clockwork::maths::ceil(count.y);
				m_count.z = clockwork::maths::ceil(count.z);

				m_chunks = new Chunk**[m_count.x];

				for ( int x = 0; x < m_count.x; ++x)
				{
					m_chunks[x] = new Chunk*[m_count.y];
					for ( int y = 0; y < m_count.x; ++y )
					{
						m_chunks[x][y] = new Chunk[m_count.z];
						for ( int z = 0; z < m_count.x; ++z )
						{
							maths::Vec3<float> tempMin;//optimierbar
							tempMin.x = min.x + x * chunksize.x;
							tempMin.y = min.y + y * chunksize.y;
							tempMin.z = min.z + z * chunksize.z;

							maths::Vec3<float> tempMax;
							tempMax.x = clockwork::maths::min(tempMin.x + chunksize.x, max.x);
							tempMax.y = clockwork::maths::min(tempMin.y + chunksize.y, max.y);
							tempMax.z = clockwork::maths::min(tempMin.z + chunksize.z, max.z);

							m_chunks[x][y][z].init(tempMin, tempMax, maths::Vec3<int>(x, y, z), this);
						}

					}

				}
			}
			~ChunkSystem2() noexcept
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

			void tickall() noexcept
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

			void tick(const maths::Vec3<int>& chunkid, int range) noexcept
			{
				for (int x = chunkid.x - range; x < chunkid.x + range + 1; ++x )
				{
					for (int y = chunkid.y - range; y < chunkid.y + range + 1; ++y )
					{
						for (int z = chunkid.z - range; z < chunkid.z + range + 1; ++z )
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


			const unsigned int getBytes() const noexcept
			{
				return m_count.x*m_count.y*m_count.z * sizeof(Chunk);
			}
			const unsigned int getChunkCount() const noexcept
			{
				return m_count.x*m_count.y*m_count.z;
			}

		};

		void Chunk::init(const maths::Vec3<float>& min, const maths::Vec3<float>& max, const maths::Vec3<int>& id, ChunkSystem2* ChunkSystem2) noexcept
		{
			m_min = min;
			m_max = max;
			m_id = id;
			m_ChunkSystem2 = ChunkSystem2;
		}


	}
}
