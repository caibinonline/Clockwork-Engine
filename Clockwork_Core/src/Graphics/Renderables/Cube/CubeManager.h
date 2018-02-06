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
#include "src\Graphics\Textures\Texture2D.h"

namespace clockwork {
	namespace graphics {

		class InstancedCube;
		class NormalCube;

		/*
		CAREFUL: the size of each image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
		class CubeManager
		{

		protected:
			friend class InstancedCube;
			friend class NormalCube;
			friend class Renderer;
			friend struct TransparentCubeCompare;
			using floatarr = float[8 * 4 * 6];
			using uchararr = unsigned  char[36];

		protected://wieder private machen und nnicht protected
			VertexArray m_instanceArray;
			VertexArray m_normalArray;
			VertexBuffer m_vertexBuffer;
			VertexBuffer m_modelBuffer;
			CopyBuffer m_copyBuffer;
			IndexBuffer<unsigned char> m_indexBuffer;
			TextureArray2D m_textureArray;
			std::vector<Texture2D> m_textures;
			std::vector<Texture2D> m_transparentTextures;
			std::vector<InstancedCube*> m_instanceCubes;
			std::vector<NormalCube*> m_normalCubes;
			std::vector<NormalCube*> m_transparentCubes;
			Renderer* m_renderer;

		public:

			CubeManager() noexcept;

			CubeManager(unsigned int reserved, Renderer* renderer) noexcept;

			~CubeManager() noexcept;

			CubeManager(const CubeManager& other) = delete;

			CubeManager(CubeManager&& other) noexcept;

			CubeManager& operator=(const CubeManager& other) = delete;

			CubeManager& operator=(CubeManager&& other) noexcept;

		private:
			int getNormalTextureId(const utils::Image& image) noexcept;
			int getNormalTextureId(const std::string& imagePath) noexcept;
			int getTransparentTextureId(const utils::Image& image) noexcept;
			int getTransparentTextureId(const std::string& imagePath) noexcept;
			int containsNormalTexture(const utils::Image& image) noexcept;
			int containsNormalTexture(const std::string& imagePath) noexcept;
			int containsTransparentTexture(const utils::Image& image) noexcept;
			int containsTransparentTexture(const std::string& imagePath) noexcept;

		public:

			void renderInstancedCubes() noexcept;

			void renderNormalCubes() noexcept;

			void renderTransparentCubes() noexcept;

			/*dont use the object at the position in the cubemanager, because it will change places with the last object in the list and the last object will then be removed */
			void removeInstancedCubesAt(int pos) noexcept;///neu besser kommentieren		| kommentieren, funktioniert nicht, wenn man 3. letztes mehrmals hintereinander entfernt, da es die sachen mischt und nicht aufrückt, also das letzte objekt kommt zur position des gelöschten objekts | ist richtig so, nur dazu schreiben | vorher binden | objekt danach nicht mehr benutzen
			
			//entfernt bei transparent immer das nächste
			void removeLastInstancedCube() noexcept;

			void removeNormalCubesAt(int pos) noexcept;

			void removeLastNormalCube() noexcept;

			void removeTransparentCubesAt(int pos) noexcept;

			void removeLastTransparentCube() noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[image] the texture/image that will be used for this model*/
			void addInstancedTexture(const utils::Image& image) noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[imagePath] the path of a texture/image that will be used for this model*/
			void addInstancedTexture(const std::string& imagePath) noexcept;

			void addNormalTexture(const utils::Image& image) noexcept;

			void addNormalTexture(const std::string& imagePath) noexcept;

			void addTextureBoth(const utils::Image& image) noexcept;//texture zu beiden hinzugefügt, kommentieren

			void addTextureBoth( const std::string& imagePath ) noexcept;

			void removeInstancedTexture(int textureId) noexcept;

			void removeInstancedTexture(const utils::Image& image) noexcept;

			void removeInstancedTexture(const std::string& imagePath) noexcept;

			void removeNormalTexture(int textureId, bool transparent) noexcept;

			void removeNormalTexture(const utils::Image& image) noexcept;

			void removeNormalTexture(const std::string& imagePath) noexcept;

			const Renderer* const getRenderer() const noexcept;

			inline const unsigned int getInstanceCount() const noexcept {return m_instanceCubes.size();}

			inline const unsigned int getNormalCount() const noexcept {return m_normalCubes.size();}

			inline const unsigned int getTransparentCount() const noexcept {return m_transparentCubes.size();}

		};

	}
}