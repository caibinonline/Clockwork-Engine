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
#include <vector>
#include "src\Maths\Vec3.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace physics {

		class Collider;

		class Hitbox//wichtig dazu kommentieren hitbox hat automatisch eine art spherecollider um den 0 punkt(0,0,0) mit verschiebung einberechnet und gr��ter size als radius f�r erste collision abfragen | hitbox sollte wahrscheinlich aber weitere collider haben
		{
			
		private:
			logics::GameObject* m_gameObject;
			std::vector<Collider*> m_colliders;
			float m_radius;

		private:
			float getRadius(Collider* collider) noexcept;

		public:
			Hitbox(logics::GameObject* gameObject) noexcept;




			void addCollider(Collider* collider) noexcept;
			void removeCollider(Collider* collider) noexcept;
			void removeCollider(unsigned int position) noexcept;
			void removeLastCollider() noexcept;


			bool fastCollides(const Hitbox& other, const maths::Vec3f& mypos, const maths::Vec3f& otherpos) const noexcept;
			//vergleicht die liste von collidern mit den collidern vom anderen objekt und speichert dann die positionen an der memoryadresse vom positions pointer
			//am besten dann in chunksystem collision durchgehen in for schleife, vorher aber collisioninfo objekt abspeichern, dann die methode hier immer aufrufen und bei true das collisioninfo objekt an listener weiterleiten
			bool slowCollides(const Hitbox& other, int* ownColliderNumber, int* otherColliderNumber) const noexcept;

		};

	}
}