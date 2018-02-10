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
		class ChunkSystem;

		class Chunk
		{

		private:
			maths::Vec3f m_min;
			maths::Vec3f m_max;
			maths::Vec3<int> m_id;
			ChunkSystem* m_chunkSystem;

		public:
			Chunk() noexcept = default;
			~Chunk() noexcept = default;

		public:
			void init(const maths::Vec3<float>& min, const maths::Vec3<float>& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept;
			void tick() noexcept;
			void slowTick() noexcept;

		};

	}
}