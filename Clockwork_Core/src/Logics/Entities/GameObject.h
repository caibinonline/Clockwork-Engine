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
#include "src\Maths\Mat4x4.h"


namespace clockwork {
	namespace logics {

		class GameObject
		{

		public:
			int m_textureId;
			maths::Mat4f m_modelMatrix;
			maths::Vec3f size;
			maths::Vec3f rotation;
			maths::Vec3f position;


		public:
			GameObject() noexcept;
			GameObject(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position) noexcept;
			~GameObject() noexcept;
			GameObject(const GameObject& other) = delete;
			GameObject(GameObject&& other) noexcept;
			GameObject& operator=(const GameObject& other) = delete;
			GameObject& operator=(GameObject&& other) noexcept;
			

		public:
			virtual void updateModelMatrix() noexcept
			{

			}


		};

	}
}


