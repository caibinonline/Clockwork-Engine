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
		class CubeManager;
		class Shader;

		class NormalCube
		{

		protected:
			friend class CubeManager;
			friend class TransparentCubeManager;
			friend class Renderer;
			friend struct InstancedCubeCompare;
			friend struct NormalCubeCompare;
			int m_textureId;///später wahrscheinlich materialid mit materialarray benutzen | dann auch materialarray, etc machen 
			maths::Mat4f m_modelMatrix;
			bool m_visible;
			bool m_transparent;
			int m_pos;
			CubeManager* m_manager;

		public:
			maths::Vec3f size;
			maths::Vec3f rotation;
			maths::Vec3f position;


		public:
			explicit NormalCube(Renderer* renderer, bool transparent) noexcept;

			NormalCube(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer, bool transparent) noexcept;

			NormalCube(const std::string& imagePath, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept;

			NormalCube(const utils::Image& image, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept;

			virtual ~NormalCube() noexcept;

			NormalCube(const NormalCube& other) = delete;

			NormalCube(NormalCube&& other) noexcept;

			NormalCube& operator=(const NormalCube& other) = delete;

			NormalCube& operator=(NormalCube&& other) noexcept;

		public:
			virtual void render() noexcept;

			void updateModelMatrix() noexcept;

			void remove() noexcept;

			void add() noexcept;

			//bleibt im gleichen cubemanager, wenn als bool transparent einfach istransparent getter mitgegeben wird 
			void setTexture(int textureId, bool transparent) noexcept;

			//kann auch zu transparentcubemanager wechseln
			void setTexture(const utils::Image& image) noexcept;

			void setTexture(const std::string& imagePath) noexcept;

			//hier gibt setvisible schon guten performance boost
			void setVisible(bool visible) noexcept;

			const utils::Image& getTextureImage() noexcept;

			const Renderer* const getRenderer() const noexcept;

		public:
			inline const bool isVisible() const noexcept { return m_visible;}
			inline const maths::Mat4f& getModelMatrix() const noexcept {return m_modelMatrix;}
			inline const bool isAdded() const noexcept {return m_pos!=-1;}
			inline const int getTextureId() const noexcept {return m_textureId;}
			inline const bool isTransparent() const noexcept {return m_transparent;}

		};

	}
}
