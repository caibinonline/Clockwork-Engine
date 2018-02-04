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
#include "CubeManager.h"
#include "InstancedCube.h"
#include "src\Graphics\Renderer\InstancedRenderer.h"

namespace clockwork {
	namespace graphics {
		
		InstancedCube::InstancedCube(InstancedRenderer* renderer) noexcept
			: m_textureId(0), m_modelMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0), m_pos(-1), m_renderer(renderer)
		{}

		InstancedCube::InstancedCube(int textureId, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(textureId), m_modelMatrix(mat), m_pos(-1), m_renderer(renderer)
		{
#if CLOCKWORK_DEBUG
			if ( m_renderer->cubeManager.m_textureArray.getTextureCount() <= textureId )
				std::cout << "Error InstancedCube::InstancedCube(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
		}

		InstancedCube::InstancedCube(const std::string& imagePath, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.m_textureArray.getTextureId(imagePath)), m_modelMatrix(mat), m_pos(-1), m_renderer(renderer)
		{
		}

		InstancedCube::InstancedCube(const utils::Image& image, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.m_textureArray.getTextureId(image)), m_modelMatrix(mat), m_pos(-1), m_renderer(renderer)
		{
		}

		InstancedCube::InstancedCube(int textureId, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(textureId), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_pos(-1), m_renderer(renderer)
		{
#if CLOCKWORK_DEBUG
			if ( m_renderer->cubeManager.m_textureArray.getTextureCount() <= textureId )
				std::cout << "Error InstancedCube::InstancedCube(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
		}

		InstancedCube::InstancedCube(const std::string& imagePath, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.m_textureArray.getTextureId(imagePath)), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_pos(-1), m_renderer(renderer)
		{
		}

		InstancedCube::InstancedCube(const utils::Image& image, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.m_textureArray.getTextureId(image)), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_pos(-1), m_renderer(renderer)
		{
		}

		InstancedCube::~InstancedCube() noexcept
		{
			if ( m_pos != -1 )
				this->remove();
		}

		InstancedCube::InstancedCube(InstancedCube&& other) noexcept
			: m_textureId(other.m_textureId), m_modelMatrix(other.m_modelMatrix), m_pos(other.m_pos), m_renderer(other.m_renderer)
		{ 
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			other.m_pos = -1;
			other.m_renderer = nullptr;
			if ( m_pos != -1 )
				m_renderer->cubeManager.m_instanceCubes.at(m_pos) = this;
		}

		InstancedCube& InstancedCube::operator=(InstancedCube&& other) noexcept
		{
			if ( m_pos != -1 )
				this->remove();
			m_textureId = other.m_textureId;
			m_modelMatrix = other.m_modelMatrix;
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			m_pos = other.m_pos;
			m_renderer = other.m_renderer;
			other.m_pos = -1;
			other.m_renderer = nullptr;
			if ( m_pos != -1 )
				m_renderer->cubeManager.m_instanceCubes.at(m_pos) = this;
			return *this;
		}

		void InstancedCube::updateBufferData() noexcept
		{
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_textureId, sizeof(int) + sizeof(maths::Mat4f), m_pos *( sizeof(int) + sizeof(maths::Mat4f) ));
			}
#if CLOCKWORK_DEBUG == 2
			else
				std::cout << "Info InstancedCube::updateBufferData(): Cube is not added to the CubeManager" << std::endl;
#endif
		}

		void InstancedCube::clearBufferData() noexcept
		{
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				struct
				{
					int textureId = 0;
					maths::Mat4f m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				} temp;
				m_renderer->cubeManager.m_copyBuffer.setData(&temp, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
#if CLOCKWORK_DEBUG == 2
			else
				std::cout << "Info InstancedCube::deleteBufferData(): Cube is not added to the CubeManager" << std::endl;
#endif
		}

		void InstancedCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos == -1 )
				std::cout << "Error InstancedCube::remove(): InstancedCube was already removed" << std::endl;
#endif
			m_renderer->cubeManager.m_copyBuffer.bind();
			m_renderer->cubeManager.m_copyBuffer.setData(&m_renderer->cubeManager.m_instanceCubes.back()->m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_renderer->cubeManager.m_copyBuffer.setData(nullptr, ( sizeof(int) + sizeof(maths::Mat4f) ), ( m_renderer->cubeManager.m_instanceCount - 1 ) * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_renderer->cubeManager.m_instanceCubes.back()->m_pos = m_pos;
			m_renderer->cubeManager.m_instanceCubes.at(m_pos) = m_renderer->cubeManager.m_instanceCubes.back();
			m_pos = -1;
			--m_renderer->cubeManager.m_instanceCount;
			m_renderer->cubeManager.m_instanceCubes.erase(m_renderer->cubeManager.m_instanceCubes.end() - 1);
		}

		void InstancedCube::add() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos != -1 )
				std::cout << "Error InstancedCube::add(): InstancedCube was already added" << std::endl;
#endif
			m_pos = m_renderer->cubeManager.m_instanceCount;
			m_renderer->cubeManager.m_copyBuffer.bind();
			if ( m_renderer->cubeManager.m_instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) + ( sizeof(int) + sizeof(maths::Mat4f) ) >= m_renderer->cubeManager.m_copyBuffer.getSize() )
				m_renderer->cubeManager.m_copyBuffer.setSize(m_renderer->cubeManager.m_instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) * 2);
			m_renderer->cubeManager.m_copyBuffer.setData(&m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			++m_renderer->cubeManager.m_instanceCount;
			m_renderer->cubeManager.m_instanceCubes.push_back(this);
		}

		void InstancedCube::setModelMatrix(const maths::Mat4f& mat) noexcept
		{
			m_modelMatrix = mat;
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_modelMatrix, sizeof(maths::Mat4f), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ) + sizeof(int));
			}
		}

		void InstancedCube::setModelMatrix(const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation) noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation);
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_modelMatrix, sizeof(maths::Mat4f), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ) + sizeof(int));
			}
		}

		void InstancedCube::setTexture(int textureId) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_renderer->cubeManager.m_textureArray.getTextureCount()<=textureId)
				std::cout << "Error InstancedCube::setTexture(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
			m_textureId = textureId;
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setTexture(const utils::Image& image) noexcept
		{
			m_textureId = m_renderer->cubeManager.m_textureArray.getTextureId(image);
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setTexture(const std::string& imagePath) noexcept
		{
			m_textureId = m_renderer->cubeManager.m_textureArray.getTextureId(imagePath);
			if ( m_pos != -1 )
			{
				m_renderer->cubeManager.m_copyBuffer.bind();
				m_renderer->cubeManager.m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setVisible(bool visible) noexcept
		{
			if ( visible )
				this->updateBufferData();
			else
				this->clearBufferData();
		}

	}
}
