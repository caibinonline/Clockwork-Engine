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
#include "src\Utils\Image.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace graphics {

		class Renderable
		{

		protected:
			int m_textureId;///sp�ter wahrscheinlich materialid mit materialarray benutzen | dann auch materialarray, etc machen 
			logics::GameObject* m_gameObject;

		public:
			Renderable(int textureId, logics::GameObject* gameObject) noexcept;
			~Renderable() noexcept;
			Renderable(const Renderable& other) = delete;
			Renderable(Renderable&& other) noexcept;
			Renderable& operator=(const Renderable& other) = delete;
			Renderable& operator=(Renderable&& other) noexcept;

		public:
			logics::GameObject* const getGameObject() const noexcept;
			void setGameObject(logics::GameObject* gameObject) noexcept;
			inline const int getTextureId() const noexcept{return m_textureId;}

		};

	}
}




