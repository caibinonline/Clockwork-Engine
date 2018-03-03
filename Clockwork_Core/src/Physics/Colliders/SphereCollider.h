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

		class SphereCollider : public Collider//wichtig dazu kommentieren, bei spherecollider müssen alle size werte gleich skaliert sein, also (2,2,2), da es nur einen radius gibt und dies nicht in alle dimensionen anpassbar ist | sonst anderen collider nehmen
		{

		private:
			friend class Hitbox;

		protected:
			maths::Vec3f m_position;
			float m_radius;

		public:
			SphereCollider(logics::GameObject* gameObject, const maths::Vec3f& position = maths::Vec3f { 0,0,0 }, float radius = 1.5) noexcept;
			virtual bool collides(const Collider* other) const noexcept override;

		};

	}
}