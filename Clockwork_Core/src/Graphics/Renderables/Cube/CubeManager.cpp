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
#include "CubeManager.h"

namespace clockwork {
	namespace graphics {

		CubeManager::CubeManager() noexcept
			: m_instanceCount(0)
		{}

		CubeManager::CubeManager(unsigned int reserved) noexcept
			: m_textureArray(reserved), m_instanceCount(0)
		{
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
			m_modelBuffer = VertexBuffer(nullptr, reserved * sizeof(InstancedCube::Data), GL_STREAM_DRAW);
			m_copyBuffer = CopyBuffer(nullptr, reserved * sizeof(InstancedCube::Data), GL_STREAM_DRAW);
			m_indexBuffer = IndexBuffer<unsigned char>(uchararr {//unsigned chars
				0,1,2,		2,1,3,
				4,5,6,		6,5,7,
				8,9,10,		10,9,11,
				12,13,14,	14,13,15,
				16,17,18,	18,17,19,
				20,21,22,	22,21,23
				}, 36//6 indices
				);
#if CLOCKWORK_DEBUG
			m_vertexBuffer.debug_vertexarray = &m_vertexArray;
			m_modelBuffer.debug_vertexarray = &m_vertexArray;
			m_indexBuffer.debug_vertexarray = &m_vertexArray;
#endif
			m_vertexBuffer.bind();
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
			m_vertexBuffer.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normal
			VertexBuffer::vaoOffset = 0;
			m_modelBuffer.bind();
			m_modelBuffer.connectToVao<int>(1, false, sizeof(InstancedCube::Data), 1);
			m_modelBuffer.connectToVao<float>(4, false, sizeof(InstancedCube::Data), 1);//4 vec4s modelmatrices
			m_modelBuffer.connectToVao<float>(4, false, sizeof(InstancedCube::Data), 1);
			m_modelBuffer.connectToVao<float>(4, false, sizeof(InstancedCube::Data), 1);
			m_modelBuffer.connectToVao<float>(4, false, sizeof(InstancedCube::Data), 1);
			m_instances.reserve(reserved);
		}

		CubeManager::~CubeManager() noexcept
		{}

		CubeManager::CubeManager(CubeManager&& other) noexcept
			: m_vertexArray(std::move(other.m_vertexArray)), m_indexBuffer(std::move(other.m_indexBuffer)), m_vertexBuffer(std::move(other.m_vertexBuffer)), m_modelBuffer(std::move(other.m_modelBuffer)), m_copyBuffer(std::move(other.m_copyBuffer)), m_instanceCount(std::move(other.m_instanceCount)), m_instances(std::move(other.m_instances)), m_textureArray(std::move(other.m_textureArray))
		{
			other.m_instanceCount = 0;
		}

		CubeManager& CubeManager::operator=(CubeManager&& other) noexcept
		{
			m_vertexArray = std::move(other.m_vertexArray);
			m_indexBuffer = std::move(other.m_indexBuffer);
			m_vertexBuffer = std::move(other.m_vertexBuffer);
			m_modelBuffer = std::move(other.m_modelBuffer);
			m_copyBuffer = std::move(other.m_copyBuffer);
			m_instanceCount = std::move(other.m_instanceCount);
			m_instances = std::move(other.m_instances);
			m_textureArray = std::move(other.m_textureArray);
			other.m_instanceCount = 0;
			return *this;
		}

		void CubeManager::render() noexcept
		{
			m_textureArray.bind();
			m_copyBuffer.bind();
			m_modelBuffer.bind();
			m_modelBuffer.copy(m_copyBuffer);
			m_vertexArray.bind();
			m_indexBuffer.drawInstanced(m_instanceCount);
		}

		void CubeManager::removeAt(int pos) noexcept
		{
			//kommentieren, funktioniert nicht, wenn man 3. letztes mehrmals hintereinander entfernt, da es die sachen mischt und nicht aufrückt, also das letzte objekt kommt zur position des gelöschten objekts | ist richtig so, nur dazu schreiben | vorher binden | objekt danach nicht mehr benutzen
			m_copyBuffer.bind();
			m_copyBuffer.setData(&m_instances.back()->m_data, sizeof(InstancedCube::Data), pos * sizeof(InstancedCube::Data));
			m_copyBuffer.setData(nullptr, sizeof(InstancedCube::Data), ( m_instanceCount - 1 ) * sizeof(InstancedCube::Data));
			m_instances.back()->m_pos = pos;
			m_instances.at(pos)->m_pos = -1;
			m_instances.at(pos) = m_instances.back();
			--m_instanceCount;
			m_instances.erase(m_instances.end() - 1);
		}

		void CubeManager::removeLast() noexcept
		{
			m_copyBuffer.bind();
			m_copyBuffer.setData(nullptr, sizeof(InstancedCube::Data), ( m_instanceCount - 1 ) * sizeof(InstancedCube::Data));
			m_instances.back()->m_pos = -1;
			--m_instanceCount;
			m_instances.erase(m_instances.end() - 1);
		}

		void CubeManager::addTexture(const utils::Image& image) noexcept
		{
			m_textureArray.addTexture(image);
		}

		void CubeManager::addTexture(const std::string& imagePath) noexcept
		{
			m_textureArray.addTexture(imagePath);
		}

		void CubeManager::removeTexture(int textureId) noexcept
		{
			m_textureArray.removeTexture(textureId);
			for ( unsigned int i = 0; i < m_instanceCount; ++i )
			{
				if ( m_instances.at(i)->m_data.textureId == textureId )
				{
					m_instances.at(i)->m_data.textureId = 0;
					m_instances.at(i)->updateBufferData();
				}
				else if ( m_instances.at(i)->m_data.textureId > textureId )
				{
					--m_instances.at(i)->m_data.textureId;
					m_instances.at(i)->updateBufferData();
				}
			}
		}

		void CubeManager::removeTexture(const utils::Image& image) noexcept
		{
			removeTexture(m_textureArray.getTextureId(image));
		}

		void CubeManager::removeTexture(const std::string& imagePath) noexcept
		{
			removeTexture(m_textureArray.getTextureId(imagePath));
		}






	}
}