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
#include "Collider.h"
#include "src\Maths\Mat4x4.h"

namespace clockwork {
	namespace physics {

		class CubeCollider : public Collider
		{

		private:
			friend class Hitbox;
		
		protected:
			maths::Vec3f m_frontBotLeft;
			maths::Vec3f m_backTopRight;//range of cube collision box(size compared to model)

		public:
			CubeCollider(logics::GameObject* gameObject, const maths::Vec3f& frontBotLeft = maths::Vec3f { -1,-1,-1 }, const maths::Vec3f& backTopRight = maths::Vec3f { 1,1,1 }) noexcept;
			virtual bool collides(const Collider* other) const noexcept override;

		};

	}
}