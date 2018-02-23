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
#include "src\Maths\Mat4x4.h"

namespace clockwork {
	namespace physics {

		class Collider//wahrscheinlich mit virtueller vererbung machen und dann in cube/spehere vertex positions in relation zu 0 speichern f�r collisionbox position in relation zum model
		{

		private:
			maths::Mat4f* m_modelMatrix;




		public:
			bool collides(const Collider* other) const noexcept;

		};

	}
}