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

namespace clockwork {
	namespace physics {

		class Collider;

		class Hitbox
		{
			
		private:
			std::vector<Collider*> m_colliders;

		public:





			void addCollider(Collider* collider) noexcept;
			void removeCollider(Collider* collider) noexcept;
			void removeCollider(unsigned int position) noexcept;
			void removeLastCollider() noexcept;

			//vergleicht die liste von collidern mit den collidern vom anderen objekt und speichert dann die positionen an der memoryadresse vom positions pointer
			//am besten dann in chunksystem collision durchgehen in for schleife, vorher aber collisioninfo objekt abspeichern, dann die methode hier immer aufrufen und bei true das collisioninfo objekt an listener weiterleiten
			bool collides(const Hitbox& other, int* ownColliderNumber, int* otherColliderNumber) const noexcept;

		};

	}
}