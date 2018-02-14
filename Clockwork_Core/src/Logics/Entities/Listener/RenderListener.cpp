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
#include "RenderListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		RenderListener::RenderListener() noexcept
		{
			m_chunk->addRenderListener(this);
		}

		RenderListener::~RenderListener() noexcept
		{
			m_chunk->removeRenderListener(this);
		}

		void RenderListener::init() noexcept
		{
			if ( m_chunk->inRenderDistance() )
				renderAdd();
		}

	}
}