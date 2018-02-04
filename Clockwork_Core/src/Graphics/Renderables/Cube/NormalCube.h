#pragma once
/*************************************************************************
* Clockwork Engine
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
	namespace graphics {

		class Renderer;

		class NormalCube
		{

		private:
			friend class CubeManager;
			friend class Renderer;
			int m_textureId;///später wahrscheinlich materialid mit materialarray benutzen | dann auch materialarray, etc machen 
			maths::Mat4f m_modelMatrix;
			bool m_visible;
			int m_pos;
			Renderer* m_renderer;

		public:
			explicit NormalCube(Renderer* renderer) noexcept;

			NormalCube(int textureId, const maths::Mat4f& mat, Renderer* renderer) noexcept;

			NormalCube(const std::string& imagePath, const maths::Mat4f& mat, Renderer* renderer) noexcept;

			NormalCube(const utils::Image& image, const maths::Mat4f& mat, Renderer* renderer) noexcept;

			NormalCube(int textureId, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, Renderer* renderer) noexcept;

			NormalCube(const std::string& imagePath, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, Renderer* renderer) noexcept;

			NormalCube(const utils::Image& image, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, Renderer* renderer) noexcept;

			virtual ~NormalCube() noexcept;

			NormalCube(const NormalCube& other) = delete;

			NormalCube(NormalCube&& other) noexcept;

			NormalCube& operator=(const NormalCube& other) = delete;

			NormalCube& operator=(NormalCube&& other) noexcept;

		public:
			virtual void render() noexcept;

			void remove() noexcept;

			void add() noexcept;

			void setModelMatrix(const maths::Mat4f& mat) noexcept;

			void setModelMatrix(const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation) noexcept;

			void setTexture(int textureId) noexcept;

			void setTexture(const utils::Image& image) noexcept;

			void setTexture(const std::string& imagePath) noexcept;

			//hier gibt setvisible schon guten performance boost
			void setVisible(bool visible) noexcept;


		};

	}
}
