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
#include <vector>
#include "src\Maths\Mat4x4.h"
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\CopyBuffer.h"
#include "src\Graphics\Buffers\InternalCopyBuffer.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Utils\Image.h"
#include "src\Graphics\Textures\TextureArray2D.h"

namespace clockwork {
	namespace graphics {

		class InstancedCube;

		class CubeManager
		{

		private:
			friend class InstancedCube;
			using floatarr = float[8 * 4 * 6];
			using uchararr = unsigned  char[36];

		private:
			VertexArray m_vertexArray;
			VertexBuffer m_vertexBuffer;
			VertexBuffer m_modelBuffer;
			CopyBuffer m_copyBuffer;
			IndexBuffer<unsigned char> m_indexBuffer;
			std::vector<InstancedCube*> m_instances;
			TextureArray2D m_textureArray;
			unsigned int m_instanceCount;



		public:

			CubeManager() noexcept;

			CubeManager(unsigned int reserved) noexcept;

			~CubeManager() noexcept;

			CubeManager(const CubeManager& other) = delete;

			CubeManager(CubeManager&& other) noexcept;

			CubeManager& operator=(const CubeManager& other) = delete;

			CubeManager& operator=(CubeManager&& other) noexcept;

		public:

			void render() noexcept;

			void removeAt(int pos) noexcept;//bei allen hier muss copyBuffer vorher gebindet werden, auch überall unten dazu schreiben | hiernach das objekt an der position nicht mehr benutzen, m_pos ist dann -1

			void removeLast() noexcept;

			void addTexture(const utils::Image& image) noexcept;

			void addTexture(const std::string& imagePath) noexcept;

			void removeTexture(int textureId) noexcept;

			void removeTexture(const utils::Image& image) noexcept;

			void removeTexture(const std::string& imagePath) noexcept;

			inline const unsigned int getCount() noexcept {return m_instanceCount;}


		};

	}
}