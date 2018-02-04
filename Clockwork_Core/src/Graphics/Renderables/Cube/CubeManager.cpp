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
#include "InstancedCube.h"
#include "NormalCube.h"
#include "CubeManager.h"

namespace clockwork {
	namespace graphics {

		CubeManager::CubeManager() noexcept
			: m_instanceCount(0), m_normalCount(0)
		{}

		CubeManager::CubeManager(unsigned int reserved) noexcept
			: m_textureArray(10), m_instanceCount(0), m_normalCount(0)
		{
			m_instanceArray.bind();
			m_vertexBuffer = VertexBuffer(//you could also create a local nameless array of vertices, where vertex is a struct with vec2 of float for position and vec2 of float for colour
				floatarr//floats
				{//positions          texture coords	 vertex normals
				 //front
					-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,//0
					1.0f, -1.0f, 1.0f,      1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,      0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
					//top								
					-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f, //4
					1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
					1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
					//back								
					-1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,//8
					1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
					-1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
					1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,

					//bot								
					-1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,//12
					1.0f, -1.0f, -1.0f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
					-1.0f, -1.0f,  1.0f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
					1.0f, -1.0f,  1.0f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,

					//right			    			    
					1.0f, -1.0f,  1.0f,    0.0f, 0.0f,     1.0f,  0.0f, 0.0f,//16
					1.0f, -1.0f, -1.0f,    1.0f, 0.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f,  1.0f,    0.0f, 1.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f, -1.0f,    1.0f, 1.0f,     1.0f, 0.0f, 0.0f,

					//left				    			    
					-1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,//20
					-1.0f, -1.0f, 1.0f,	    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,	    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, 1.0f,	    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

				}, 8 * 4 * 6 * sizeof(float)
				);
			m_modelBuffer = VertexBuffer(nullptr, reserved * ( sizeof(int) + sizeof(maths::Mat4f) ), GL_STREAM_DRAW);
			m_indexBuffer = IndexBuffer<unsigned char>(uchararr {//unsigned chars
				0,1,2,		2,1,3,
				4,5,6,		6,5,7,
				8,9,10,		10,9,11,
				12,13,14,	14,13,15,
				16,17,18,	18,17,19,
				20,21,22,	22,21,23
				}, 36//6 indices
				);
			m_vertexBuffer.bind();
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
			m_vertexBuffer.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normal
			VertexBuffer::vaoOffset = 0;
			m_modelBuffer.bind();
			m_modelBuffer.connectToVao<int>(1, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);//4 vec4s modelmatrices
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			VertexBuffer::vaoOffset = 0;
			VertexBuffer::VaoPos = 0;
			m_normalArray.bind();
			m_vertexBuffer.bind();
			m_indexBuffer.bind();
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
			m_vertexBuffer.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normal
			m_normalArray.unbind();
			m_copyBuffer = CopyBuffer(nullptr, reserved * ( sizeof(int) + sizeof(maths::Mat4f) ), GL_STREAM_DRAW);
			m_instanceCubes.reserve(reserved);
			m_normalCubes.reserve(reserved);
			m_textures.reserve(10);
		}

		CubeManager::~CubeManager() noexcept
		{}

		CubeManager::CubeManager(CubeManager&& other) noexcept
			: m_instanceArray(std::move(other.m_instanceArray)), m_normalArray(std::move(other.m_normalArray)), m_indexBuffer(std::move(other.m_indexBuffer)), m_vertexBuffer(std::move(other.m_vertexBuffer)), m_modelBuffer(std::move(other.m_modelBuffer)),
			m_copyBuffer(std::move(other.m_copyBuffer)), m_textureArray(std::move(other.m_textureArray)), m_textures(std::move(other.m_textures)), m_instanceCubes(std::move(other.m_instanceCubes)), m_instanceCount(std::move(other.m_instanceCount)), 
			m_normalCubes(std::move(other.m_normalCubes)), m_normalCount(std::move(other.m_normalCount))
		{
			other.m_instanceCount = 0;
			other.m_normalCount = 0;
		}

		CubeManager& CubeManager::operator=(CubeManager&& other) noexcept
		{
			m_instanceArray = std::move(other.m_instanceArray);
			m_normalArray = std::move(other.m_normalArray);
			m_indexBuffer = std::move(other.m_indexBuffer);
			m_vertexBuffer = std::move(other.m_vertexBuffer);
			m_modelBuffer = std::move(other.m_modelBuffer);
			m_copyBuffer = std::move(other.m_copyBuffer);
			m_textureArray = std::move(other.m_textureArray);
			m_textures = std::move(other.m_textures);
			m_instanceCubes = std::move(other.m_instanceCubes);
			m_instanceCount = std::move(other.m_instanceCount);
			m_normalCubes = std::move(other.m_normalCubes);
			m_normalCount = std::move(other.m_normalCount);
			other.m_instanceCount = 0;
			other.m_normalCount = 0;
			return *this;
		}

		int CubeManager::getNormalTextureId(const utils::Image& image) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
			if ( m_textures.size() > 0 && m_textures.at(0).getImage().getSize() != image.getSize() )
				std::cout << "Error CubeManager::getNormalTextureId(): the new image has not the same size as the other images in the texture list" << std::endl;
#endif 
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == image.getFilepath() )
					return i;
			}
			m_textures.push_back(Texture2D(image));
		}

		int CubeManager::getNormalTextureId(const std::string& imagePath) noexcept
		{
			utils::Image image(imagePath);
			image.load();
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
			if ( m_textures.size() > 0 && m_textures.at(0).getImage().getSize() != image.getSize() )
				std::cout << "Error CubeManager::getNormalTextureId(): the new image has not the same size as the other images in the texture list" << std::endl;
#endif 
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == image.getFilepath() )
					return i;
			}
			m_textures.push_back(Texture2D(image));
		}

		void CubeManager::renderInstancedCubes() noexcept
		{
			m_textureArray.bind();
			m_copyBuffer.bind();
			m_modelBuffer.bind();
			m_modelBuffer.copy(m_copyBuffer);
			m_instanceArray.bind();
			m_indexBuffer.drawInstanced(m_instanceCount);
		}

		void CubeManager::renderNormalCubes() noexcept
		{
			m_normalArray.bind();
			for ( auto& cube : m_normalCubes )
			{
				cube->render();
			}
		}

		void CubeManager::removeInstancedCubesAt(int pos) noexcept
		{
			m_copyBuffer.bind();
			m_copyBuffer.setData(&m_instanceCubes.back()->m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_copyBuffer.setData(nullptr, ( sizeof(int) + sizeof(maths::Mat4f) ), ( m_instanceCount - 1 ) * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_instanceCubes.back()->m_pos = pos;
			m_instanceCubes.at(pos)->m_pos = -1;
			m_instanceCubes.at(pos) = m_instanceCubes.back();
			--m_instanceCount;
			m_instanceCubes.erase(m_instanceCubes.end() - 1);
		}

		void CubeManager::removeLastInstancedCube() noexcept
		{
			m_copyBuffer.bind();
			m_copyBuffer.setData(nullptr, ( sizeof(int) + sizeof(maths::Mat4f) ), ( m_instanceCount - 1 ) * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_instanceCubes.back()->m_pos = -1;
			--m_instanceCount;
			m_instanceCubes.erase(m_instanceCubes.end() - 1);
		}

		void CubeManager::removeNormalCubesAt(int pos) noexcept
		{
			m_normalCubes.erase(m_normalCubes.begin() + pos);
			--m_normalCount;
		}

		void CubeManager::removeLastNormalCube() noexcept
		{
			m_normalCubes.erase(m_normalCubes.end() - 1);
			--m_normalCount;
		}

		void CubeManager::addInstancedTexture(const utils::Image& image) noexcept
		{
			m_textureArray.addTexture(image);
		}

		void CubeManager::addInstancedTexture(const std::string& imagePath) noexcept
		{
			m_textureArray.addTexture(imagePath);
		}

		void CubeManager::addNormalTexture(const utils::Image& image) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::addNormalTexture(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
			if ( m_textures.size() > 0 && m_textures.at(0).getImage().getSize() != image.getSize() )
				std::cout << "Error CubeManager::addNormalTexture(): the new image has not the same size as the other images in the texture list" << std::endl;
#endif 
#if CLOCKWORK_DEBUG
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == image.getFilepath() )
				{
					std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
					return;
				}
			}
#endif 
			m_textures.push_back(Texture2D(image));
		}

		void CubeManager::addNormalTexture(const std::string& imagePath) noexcept
		{
			utils::Image image(imagePath);
			image.load();
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::addNormalTexture(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
			if ( m_textures.size() > 0 && m_textures.at(0).getImage().getSize() != image.getSize() )
				std::cout << "Error CubeManager::addNormalTexture(): the new image has not the same size as the other images in the texture list" << std::endl;
#endif 
#if CLOCKWORK_DEBUG
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == image.getFilepath() )
				{
					std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
					return;
				}
			}
#endif 
			m_textures.push_back(Texture2D(image));
		}

		void CubeManager::removeInstancedTexture(int textureId) noexcept
		{
			m_textureArray.removeTexture(textureId);
			for ( unsigned int i = 0; i < m_instanceCount; ++i )
			{
				if ( m_instanceCubes.at(i)->m_textureId == textureId )
				{
					m_instanceCubes.at(i)->m_textureId = 0;
					m_instanceCubes.at(i)->updateBufferData();
				}
				else if ( m_instanceCubes.at(i)->m_textureId > textureId )
				{
					--m_instanceCubes.at(i)->m_textureId;
					m_instanceCubes.at(i)->updateBufferData();
				}
			}
		}

		void CubeManager::removeInstancedTexture(const utils::Image& image) noexcept
		{
			removeInstancedTexture(m_textureArray.getTextureId(image));
		}

		void CubeManager::removeInstancedTexture(const std::string& imagePath) noexcept
		{
			removeInstancedTexture(m_textureArray.getTextureId(imagePath));
		}

		void CubeManager::removeNormalTexture(int textureId) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_textures.size() <= textureId )
				std::cout << "Error CubeManager::removeNormalTexture(): TextureId is not in the texture list" << std::endl;
#endif
			m_textures.erase(m_textures.begin() + textureId);
			for ( unsigned int i = 0; i < m_normalCount; ++i )
			{
				if ( m_normalCubes.at(i)->m_textureId == textureId )
				{
					m_normalCubes.at(i)->m_textureId = 0;
				}
				else if ( m_instanceCubes.at(i)->m_textureId > textureId )
				{
					--m_normalCubes.at(i)->m_textureId;
				}
			}
		}

		void CubeManager::removeNormalTexture(const utils::Image& image) noexcept
		{
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == image.getFilepath() )
				{
					removeNormalTexture(i);
					break;
				}
			}
		}

		void CubeManager::removeNormalTexture(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_textures.size(); ++i )
			{
				if ( m_textures.at(i).getImage().getFilepath() == imagePath )
				{
					removeNormalTexture(i);
					break;
				}
			}
		}




	}
}