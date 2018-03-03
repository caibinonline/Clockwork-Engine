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
#include "src\Logics\Entities\GameObject.h"
#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		class Chunk;
		class MovingTickListener;

		class StaticTickListener//unterschied zu staticticklistener dazu schreiben | der hier verändert chunk, wenn er sich bewegt | static listener darf auch nicht mehr position so verändert kriegen, dass er in nem anderen chunk ist
			: public virtual GameObject
		{

		protected:
			float m_mass;
			physics::Hitbox m_hitbox;

		public:
			StaticTickListener() noexcept;
			~StaticTickListener() noexcept;

		public:
			virtual void fastTick() noexcept = 0;
			virtual void slowTick() noexcept = 0;
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept = 0;

			inline const physics::Hitbox& getHitbox() const {return m_hitbox;}//ggf auch noch nicht const getter, wenn benötigt

		};

	}
}

