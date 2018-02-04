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

		/*
		CAREFUL: the size of each image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
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

			/*dont use the object at the position in the cubemanager, because it will change places with the last object in the list and the last object will then be removed */
			void removeAt(int pos) noexcept;///neu besser kommentieren		| kommentieren, funktioniert nicht, wenn man 3. letztes mehrmals hintereinander entfernt, da es die sachen mischt und nicht aufrückt, also das letzte objekt kommt zur position des gelöschten objekts | ist richtig so, nur dazu schreiben | vorher binden | objekt danach nicht mehr benutzen

			void removeLast() noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[image] the texture/image that will be used for this model*/
			void addTexture(const utils::Image& image) noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[imagePath] the path of a texture/image that will be used for this model*/
			void addTexture(const std::string& imagePath) noexcept;

			void removeTexture(int textureId) noexcept;

			void removeTexture(const utils::Image& image) noexcept;

			void removeTexture(const std::string& imagePath) noexcept;

			inline const unsigned int getCount() const noexcept {return m_instanceCount;}


		};

	}
}