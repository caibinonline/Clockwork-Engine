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
#include "Camera.h"
#include "src\Logics\States\State.h"

namespace clockwork {
	namespace logics {

		Camera::Camera(State* state, const maths::Vec3f& position, const maths::Vec3f& direction, const maths::Vec3f& up) noexcept
			: m_state(state), m_position(position), m_direction(direction), m_worldUp(up), m_yaw(90.0), m_pitch(0.0), m_fov(90.0), m_near(0.1f), m_far(1000.0f)///später auch hier werte von konstruktor übernehmen | pitch yaw sind hier noch fest und werden nicht anhand direction bestimmt
		{
			m_direction.normalizeSelf();
			m_worldUp.normalizeSelf();
			m_right = m_direction.crossproduct(m_worldUp).normalizeSelf();
			m_up = m_right.crossproduct(m_direction).normalizeSelf();
		}

		void Camera::setFov(float fov) noexcept
		{
			m_fov = fov;
			m_state->updateProjection();
		}
		void Camera::setNear(float near_) noexcept
		{
			m_near = near_;
			m_state->updateProjection();
		}
		void Camera::setFar(float far_) noexcept
		{
			m_far = far_;
			m_state->updateProjection();
		}

		const State&  Camera::getState() const noexcept
		{
			return *m_state;
		}
		State&  Camera::getState() noexcept
		{
			return *m_state;
		}

	}
}