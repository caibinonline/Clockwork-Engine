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
#include "src\Maths\Vec3.h"
#include "src\Maths\MathFunctions.h"

namespace clockwork {
	namespace logics {

		class State;
		class Chunk;

		class ChunkSystem
		{
			
		private:
			maths::Vec3f m_min;
			maths::Vec3f m_max;
			maths::Vec3f m_chunkSize;
			maths::Vec3i m_count;//neue größe machen ist noch nicht vorgesehen
			maths::Vec3i m_renderDistance;///noch miteinbeziehen KONSTRUKTOR | getter/setter(mit debug test) | ist wichtig für renderadd/renderremove | wird für tick nicht benötigt, da dort die range mitgegeben werden kann
			maths::Vec3i m_tickDistance;///sollte nicht größer als count sein ggf in debug abfragen | braucht noch getter und setter, bei setter natürlich auch mutex setzten, da es in tick/render gebraucht wird
			Chunk*** m_chunks;
			Chunk* m_currentChunk;
			State* m_state;

		public:
			ChunkSystem(const maths::Vec3f& min, const maths::Vec3f& max, const maths::Vec3f& chunkSize, const maths::Vec3i& renderDistance, const maths::Vec3i& tickDistance, State* state) noexcept;
			~ChunkSystem() noexcept;

		public:
			const Chunk& getChunk(const maths::Vec3i& id) const noexcept;
			Chunk& getChunk(const maths::Vec3i& id) noexcept;
			const Chunk& getChunk(int idX, int idY, int idZ) const noexcept;
			Chunk& getChunk(int idX, int idY, int idZ) noexcept;
			const Chunk& getChunkAt(const maths::Vec3f& position) const noexcept;
			Chunk& getChunkAt(const maths::Vec3f& position) noexcept;

			const unsigned int getBytes() const noexcept;
			const unsigned int getChunkCount() const noexcept;
			Chunk*** getChunkPointer() noexcept{return m_chunks;}//nicht wirklich threadsafe, nicht const | kann alles mit gemacht werden | wahrscheinlich nur in passFunction benutzen und dann in passFunction mutex für chunkSystem locken und in den einzelnen chunk.tick/render/etc methoden dann chunks locken

		public:
			void update() noexcept;
			void tickAll() noexcept;
			void tick() noexcept;
			void slowTickAll() noexcept;
			void slowTick() noexcept;
			/*passes a function to chunks at the given position(id) with the given range(id) | you have to call this method with a functor struct layout like the following 
			struct SlowTickFunctor
			{
				void function(Chunk& chunk) noexcept
				{
					chunk.slowTick();
				}
			};
			passFunction<SlowTickFunctor>(m_currentChunk->getId(), m_tickDistance);
			*/
			template<typename functor>void passFunctionToChunks(const maths::Vec3<int>& startId, const maths::Vec3<int>& range) noexcept;

		};

	}
}
