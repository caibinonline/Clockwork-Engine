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
#include "MovingTickListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		MovingTickListener::MovingTickListener() noexcept
			: m_mass(0), m_hitbox(this)
		{
			m_chunk->addMovingTickListener(this);
		}

		MovingTickListener::~MovingTickListener() noexcept
		{
			m_chunk->removeMovingTickListener(this);
		}


	}
}