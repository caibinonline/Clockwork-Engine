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
#include "Renderable.h"

namespace clockwork {
	namespace graphics {

		Renderable::Renderable() noexcept
			: m_textureId(0), m_modelMatrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
		{}
		Renderable::Renderable(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position) noexcept
			: m_textureId(textureId), size(size), rotation(rotation), position(position)
		{}
		Renderable::~Renderable() noexcept
		{}
		Renderable::Renderable(Renderable&& other) noexcept
			: m_textureId(other.m_textureId), m_modelMatrix(std::move(other.m_modelMatrix)), size(std::move(other.size)), rotation(std::move(other.rotation)), position(std::move(other.position))
		{}
		Renderable& Renderable::operator=(Renderable&& other) noexcept
		{
			m_textureId = other.m_textureId;
			m_modelMatrix = std::move(other.m_modelMatrix);
			size = std::move(other.size);
			rotation = std::move(other.rotation);
			position = std::move(other.position);
			return *this;
		}

	}
}
