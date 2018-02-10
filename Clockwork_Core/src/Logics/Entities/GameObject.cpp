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
#include "GameObject.h"

namespace clockwork {
	namespace logics {

		GameObject::GameObject(State* state) noexcept
			: m_state(state)
		{}

		GameObject::GameObject(const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state) noexcept
			: m_size(size), m_rotation(rotation), m_position(position), m_modelMatrix(maths::Mat4f::scaling(size)), m_state(state)
		{
			if ( rotation.x > 0 )
				m_modelMatrix.rotateXD(rotation.x);
			if ( rotation.y > 0 )
				m_modelMatrix.rotateYD(rotation.y);
			if ( rotation.z > 0 )
				m_modelMatrix.rotateZD(rotation.z);
			m_modelMatrix.translate(position);
		}

		GameObject::~GameObject() noexcept
		{

		}

		GameObject::GameObject(const GameObject& other) noexcept
			: m_size(other.m_size), m_rotation(other.m_rotation), m_position(other.m_position), m_modelMatrix(other.m_modelMatrix), m_state(other.m_state)
		{

		}

		GameObject::GameObject(GameObject&& other) noexcept
			: m_size(other.m_size), m_rotation(other.m_rotation), m_position(other.m_position), m_modelMatrix(other.m_modelMatrix), m_state(other.m_state)
		{

		}

		GameObject& GameObject::operator=(const GameObject& other) noexcept
		{
			m_size = other.m_size;
			m_rotation = other.m_rotation;
			m_position = other.m_position;
			m_modelMatrix = other.m_modelMatrix;
			m_state = other.m_state;
			this->onMatrixChange();
			return *this;
		}

		GameObject& GameObject::operator=(GameObject&& other) noexcept
		{
			m_size = other.m_size;
			m_rotation = other.m_rotation;
			m_position = other.m_position;
			m_modelMatrix = other.m_modelMatrix;
			m_state = other.m_state;
			this->onMatrixChange();
			return *this;
		}

		void GameObject::updateModelMatrix() noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(m_size);
			if ( m_rotation.x > 0 )
				m_modelMatrix.rotateXD(m_rotation.x);
			if ( m_rotation.y > 0 )
				m_modelMatrix.rotateYD(m_rotation.y);
			if ( m_rotation.z > 0 )
				m_modelMatrix.rotateZD(m_rotation.z);
			m_modelMatrix.translate(m_position);
			this->onMatrixChange();
		}

		const State& GameObject::getState() const noexcept
		{
			return *m_state;
		}

		State& GameObject::getState() noexcept
		{
			return *m_state;
		}

	}
}
