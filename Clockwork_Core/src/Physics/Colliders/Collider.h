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

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace physics {

		class Collider//wahrscheinlich mit virtueller vererbung machen und dann in cube/spehere vertex positions in relation zu 0 speichern für collisionbox position in relation zum model
		{

		protected:
			logics::GameObject * m_gameObject;

		public:
			Collider(logics::GameObject* gameObject) noexcept;
			virtual bool collides(const Collider* other) const noexcept = 0;

		};

	}
}