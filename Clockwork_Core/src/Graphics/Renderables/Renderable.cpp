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
#include "Renderable.h"
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace graphics {

		Renderable::Renderable(int textureId, logics::GameObject* gameObject) noexcept
			: m_textureId(textureId), m_gameObject(gameObject)
		{}
		Renderable::~Renderable() noexcept
		{}
		Renderable::Renderable(Renderable&& other) noexcept
			: m_textureId(other.m_textureId), m_gameObject(other.m_gameObject)
		{}
		Renderable& Renderable::operator=(Renderable&& other) noexcept
		{
			m_textureId = other.m_textureId;
			m_gameObject = other.m_gameObject;
			return *this;
		}
		const logics::GameObject& Renderable::getGameObject() const noexcept
		{
			return *m_gameObject;
		}

		logics::GameObject& Renderable::getGameObject() noexcept
		{
			return *m_gameObject;
		}
		void Renderable::setGameObject(logics::GameObject* gameObject) noexcept
		{
			m_gameObject = gameObject;
		}

	}
}
