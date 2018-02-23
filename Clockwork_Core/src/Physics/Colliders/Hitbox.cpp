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
#include <algorithm>
#include <iostream>
#include "Hitbox.h"
#include "Collider.h"
namespace clockwork {
	namespace physics {

		void Hitbox::addCollider(Collider* collider) noexcept
		{
			m_colliders.push_back(collider);
		}

		void Hitbox::removeCollider(Collider* collider) noexcept
		{
			auto iterator = std::find(m_colliders.begin(), m_colliders.end(), collider);
#if CLOCKWORK_DEBUG
			if ( iterator == m_colliders.end() )
				std::cout << "Error Chunk::removeCollider(): The collider pointer is not in the colliderlist" << std::endl;
#endif
			m_colliders.erase(iterator);
		}

		void Hitbox::removeCollider(unsigned int position) noexcept
		{
			m_colliders.erase(m_colliders.begin() + position);
		}

		void Hitbox::removeLastCollider() noexcept
		{
			m_colliders.erase(m_colliders.end() - 1);
		}

		bool Hitbox::collides(const Hitbox& other, int* ownColliderNumber, int* otherColliderNumber) const noexcept
		{
			for ( unsigned int me = 0; me < m_colliders.size(); ++me )
			{
				for ( unsigned int ot = 0; ot < other.m_colliders.size(); ++ot )
				{
					if ( m_colliders[me]->collides(other.m_colliders[ot]) )///TREAD_SAFE: wahrscheinlich auch wenn es von gleicher klasse ist nicht über member zugreifen, sondern auf das element des vektors mit einem getter mit mutex zugreifen, da das andere objekt auch gerade verändert werden könnte
					{
						*ownColliderNumber = me;
						*otherColliderNumber = ot;
						return true;
					}
				}
			}
			return false;
		}

	}
}