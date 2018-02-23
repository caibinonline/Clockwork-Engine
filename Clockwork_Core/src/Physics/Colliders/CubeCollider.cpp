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
#include "CubeCollider.h"
#include "src\Logics\Entities\GameObject.h"
namespace clockwork {
	namespace physics {

		CubeCollider::CubeCollider(logics::GameObject* gameObject, const maths::Vec3f& frontBotLeft, const maths::Vec3f& backTopRight) noexcept
			: Collider(gameObject), m_frontBotLeft(frontBotLeft), m_backTopRight(backTopRight)
		{

		}

		bool CubeCollider::collides(const Collider* other) const noexcept
		{
			const CubeCollider* cube = dynamic_cast<const CubeCollider*>( other );
			if ( cube )
			{
				maths::Vec3f myfbl = m_gameObject->getModelMatrix()*m_frontBotLeft;
				maths::Vec3f mybtr = m_gameObject->getModelMatrix()*m_backTopRight;
				maths::Vec3f otherfbl = cube->m_gameObject->getModelMatrix()*cube->m_frontBotLeft;//THREAD_SAFE: ggf mit getter machen
				maths::Vec3f otherbtr = cube->m_gameObject->getModelMatrix()*cube->m_backTopRight;

				if ( myfbl.x <= otherbtr.x&&mybtr.x >= otherfbl.x//schlechte collision ohne rotation miteinbezogen, lieber https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169  https://gamedev.stackexchange.com/questions/112883/simple-3d-obb-collision-directx9-c  http://www.randygaul.net/2014/05/22/deriving-obb-to-obb-intersection-sat/
					&&myfbl.y <= otherbtr.y&&mybtr.y >= otherfbl.y
					&&myfbl.z <= otherbtr.z&&mybtr.z >= otherfbl.z )
				{
					return true;
				}
			}

			return false;
		}

	}
}