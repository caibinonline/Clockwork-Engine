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
#include "OpenglStuff.h"
#include "Buffers\VertexBuffer.h"
#include "Buffers\CopyBuffer.h"
#include "Buffers\InternalCopyBuffer.h"

namespace clockwork {
	namespace graphics {

		void initBuffers(unsigned int size) noexcept
		{
			VertexBuffer::copyBuffer = new InternalCopyBuffer(nullptr, size, GL_STREAM_DRAW);
			CopyBuffer::copyBuffer = new InternalCopyBuffer(nullptr, size, GL_STREAM_DRAW);
			InternalCopyBuffer::copyBuffer = new CopyBuffer(nullptr, size, GL_STREAM_DRAW);
		}

		void openglParams(bool enableCulling, int cullFace, int windingOrder, bool enableDepthTest, int depthCompare, bool enableBlending, int blendSourceFactor, int blendDestinationFactor, int blendFunc) noexcept
		{
			if ( enableCulling )
			{
				glEnable(GL_CULL_FACE);
				glCullFace(cullFace);
				glFrontFace(windingOrder);
			}
			else
				glDisable(GL_CULL_FACE);
			if ( enableDepthTest )
			{
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(depthCompare);
			}
			else
				glDisable(GL_DEPTH_TEST);
			if ( enableBlending )
			{
				glEnable(GL_BLEND);
				glBlendEquation(blendFunc);
				glBlendFunc(blendSourceFactor, blendDestinationFactor);
			}
			else
				glDisable(GL_BLEND);
		}

	}
}