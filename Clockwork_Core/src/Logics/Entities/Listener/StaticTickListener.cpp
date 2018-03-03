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
#include "StaticTickListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		StaticTickListener::StaticTickListener() noexcept
			: m_mass(0), m_hitbox(this)
		{
			m_chunk->addStaticTickListener(this);
		}

		StaticTickListener::~StaticTickListener() noexcept
		{
			m_chunk->removeStaticTickListener(this);
		}


	}
}