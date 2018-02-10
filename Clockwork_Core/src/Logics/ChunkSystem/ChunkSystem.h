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
			maths::Vec3<int> m_count;
			Chunk*** m_chunks;
			Chunk* m_currentChunk;
			State* m_state;

		public:
			ChunkSystem(const maths::Vec3<float>& min, const maths::Vec3<float>& max, const maths::Vec3<float>& chunkSize, State* state) noexcept;
			~ChunkSystem() noexcept;

		public:
			const unsigned int getBytes() const noexcept;
			const unsigned int getChunkCount() const noexcept;

		public:
			void tickAll() noexcept;
			void tick(const maths::Vec3<int>& chunkid, int range) noexcept;
			void slowTickAll() noexcept;
			void slowTick(const maths::Vec3<int>& chunkid, int range) noexcept;

		};

	}
}
