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
#include "src\Graphics\Renderer\Renderer.h"

namespace clockwork {
	namespace graphics {
		
		InstancedCube::InstancedCube(Renderer* renderer) noexcept
			: m_textureId(0), m_modelMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0), m_visible(false), m_changed(false), m_pos(-1), m_manager(&renderer->cubeManager)
		{//einziger konstruktor, der fertig ist | bei anderen konstruktoren changed true machen und vektoren verarbeiten 
		}

		InstancedCube::InstancedCube(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: m_textureId(textureId), m_scaling(size), m_rotation(rotation), m_translation(position), m_visible(true), m_changed(true), m_pos(-1), m_manager(&renderer->cubeManager)
		{
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textureArray.getTextureCount() <= textureId )
				std::cout << "Error InstancedCube::InstancedCube(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
		}

		InstancedCube::InstancedCube(const std::string& imagePath, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: m_textureId(renderer->cubeManager.m_textureArray.getTextureId(imagePath)), m_scaling(size), m_rotation(rotation), m_translation(position), m_modelMatrix(maths::Mat4f::scaling(size).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(position)), m_visible(true), m_pos(-1), m_manager(&renderer->cubeManager)
		{
		}

		InstancedCube::InstancedCube(const utils::Image& image, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: m_textureId(renderer->cubeManager.m_textureArray.getTextureId(image)), m_scaling(size), m_rotation(rotation), m_translation(position), m_modelMatrix(maths::Mat4f::scaling(size).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(position)), m_visible(true), m_pos(-1), m_manager(&renderer->cubeManager)
		{
		}

		InstancedCube::~InstancedCube() noexcept
		{
			if ( m_pos != -1 )
				this->remove();
		}

		InstancedCube::InstancedCube(InstancedCube&& other) noexcept
			: m_textureId(other.m_textureId), m_modelMatrix(other.m_modelMatrix), m_visible(other.m_visible), m_pos(other.m_pos), m_manager(other.m_manager)
		{ 
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			other.m_visible = false;
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_instanceCubes.at(m_pos) = this;
		}

		InstancedCube& InstancedCube::operator=(InstancedCube&& other) noexcept
		{
			if ( m_pos != -1 )
				this->remove();
			m_textureId = other.m_textureId;
			m_modelMatrix = other.m_modelMatrix;
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			m_visible = other.m_visible;
			m_pos = other.m_pos;
			m_manager = other.m_manager;
			other.m_visible = false;
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_instanceCubes.at(m_pos) = this;
			return *this;
		}

		void InstancedCube::updateModelMatrix() noexcept
		{
			if ( m_changed )
			{
				m_modelMatrix = maths::Mat4f::scaling(m_scaling);
				if ( m_rotation.x > 0 )
					m_modelMatrix.rotateXD(m_rotation.x);
				if ( m_rotation.y > 0 )
					m_modelMatrix.rotateYD(m_rotation.y);
				if ( m_rotation.z > 0 )
					m_modelMatrix.rotateZD(m_rotation.z);
				m_modelMatrix.translate(m_translation);
				if ( m_pos != -1 )
				{
					m_manager->m_copyBuffer.setData(&m_modelMatrix, sizeof(maths::Mat4f), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ) + sizeof(int));
				}
				m_changed = false;
			}
		}

		void InstancedCube::updateBufferData() noexcept
		{
			m_manager->m_copyBuffer.setData(&m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
		}

		void InstancedCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos == -1 )
				std::cout << "Error InstancedCube::remove(): InstancedCube was already removed" << std::endl;
#endif
			m_manager->m_copyBuffer.bind();
			m_manager->m_copyBuffer.setData(&m_manager->m_instanceCubes.back()->m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_manager->m_copyBuffer.setData(nullptr, ( sizeof(int) + sizeof(maths::Mat4f) ), ( m_manager->m_instanceCubes.size() - 1 ) * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_manager->m_instanceCubes.back()->m_pos = m_pos;
			m_manager->m_instanceCubes.at(m_pos) = m_manager->m_instanceCubes.back();
			m_pos = -1;
			m_manager->m_instanceCubes.erase(m_manager->m_instanceCubes.end() - 1);
		}

		void InstancedCube::add() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos != -1 )
				std::cout << "Error InstancedCube::add(): InstancedCube was already added" << std::endl;
#endif
			unsigned int instanceCount = m_manager->m_instanceCubes.size();
			m_pos = instanceCount;
			m_manager->m_copyBuffer.bind();
			if ( instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) + ( sizeof(int) + sizeof(maths::Mat4f) ) >= m_manager->m_copyBuffer.getSize() )
				m_manager->m_copyBuffer.setSize(instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) * 2);
			m_manager->m_copyBuffer.setData(&m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			m_manager->m_instanceCubes.push_back(this);
		}

		void InstancedCube::setTexture(int textureId) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textureArray.getTextureCount()<=textureId)
				std::cout << "Error InstancedCube::setTexture(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
			m_textureId = textureId;
			if ( m_pos != -1 )
			{
				m_manager->m_copyBuffer.bind();
				m_manager->m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setTexture(const utils::Image& image) noexcept
		{
			m_textureId = m_manager->m_textureArray.getTextureId(image);
			if ( m_pos != -1 )
			{
				m_manager->m_copyBuffer.bind();
				m_manager->m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setTexture(const std::string& imagePath) noexcept
		{
			m_textureId = m_manager->m_textureArray.getTextureId(imagePath);
			if ( m_pos != -1 )
			{
				m_manager->m_copyBuffer.bind();
				m_manager->m_copyBuffer.setData(&m_textureId, sizeof(int), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
			}
		}

		void InstancedCube::setVisible(bool visible) noexcept
		{
			m_visible = visible;
			if ( m_visible )
			{
				if ( m_pos != -1 )
				{
					m_manager->m_copyBuffer.bind();
					m_manager->m_copyBuffer.setData(&m_textureId, sizeof(int) + sizeof(maths::Mat4f), m_pos *( sizeof(int) + sizeof(maths::Mat4f) ));
				}
#if CLOCKWORK_DEBUG == 2
				else
					std::cout << "Info InstancedCube::updateBufferData(): Cube is not added to the CubeManager" << std::endl;
#endif
			}
			else
			{
				if ( m_pos != -1 )
				{
					m_manager->m_copyBuffer.bind();
					struct
					{
						int textureId = 0;
						maths::Mat4f m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
					} temp;
					m_manager->m_copyBuffer.setData(&temp, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
				}
#if CLOCKWORK_DEBUG == 2
				else
					std::cout << "Info InstancedCube::deleteBufferData(): Cube is not added to the CubeManager" << std::endl;
#endif
			}
		}

		const utils::Image& InstancedCube::getTextureImage() noexcept
		{
			return m_manager->m_textureArray.getTexture(m_textureId);
		}

		const Renderer* const InstancedCube::getRenderer() const noexcept
		{
			return m_manager->m_renderer;
		}

	}
}
