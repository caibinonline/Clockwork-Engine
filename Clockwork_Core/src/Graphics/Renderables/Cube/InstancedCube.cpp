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
#include "CubeManager.h"
#include "InstancedCube.h"
#include "src\Graphics\Renderer\Renderer.h"

namespace clockwork {
	namespace graphics {
		
		InstancedCube::InstancedCube(Renderer* renderer) noexcept
			: Renderable(), m_changed(false), m_pos(-1), m_manager(&renderer->cubeManager)
		{
		}

		InstancedCube::InstancedCube(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: Renderable(textureId, size, rotation, position), m_changed(false), m_pos(-1), m_manager(&renderer->cubeManager)
		{
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textureArray.getTextureCount() <= textureId )
				std::cout << "Error InstancedCube::InstancedCube(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
			updateModelMatrix();
		}

		InstancedCube::InstancedCube(const std::string& imagePath, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: Renderable(renderer->cubeManager.m_textureArray.getTextureId(imagePath), size, rotation, position), m_changed(false), m_pos(-1), m_manager(&renderer->cubeManager)
		{
			updateModelMatrix();
		}

		InstancedCube::InstancedCube(const utils::Image& image, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: Renderable(renderer->cubeManager.m_textureArray.getTextureId(image), size, rotation, position), m_changed(false), m_pos(-1), m_manager(&renderer->cubeManager)
		{
			updateModelMatrix();
		}

		InstancedCube::~InstancedCube() noexcept
		{
			if ( m_pos != -1 )
				this->remove();
		}

		InstancedCube::InstancedCube(InstancedCube&& other) noexcept
			: Renderable(std::move(other)), m_changed(true), m_pos(other.m_pos), m_manager(other.m_manager)
		{ 
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_instanceCubes.at(m_pos) = this;
		}

		InstancedCube& InstancedCube::operator=(InstancedCube&& other) noexcept
		{
			if ( m_pos != -1 )
				this->remove();
			m_changed = true;
			m_pos = other.m_pos;
			m_manager = other.m_manager;
			Renderable::operator=(std::move(other));
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_instanceCubes.at(m_pos) = this;
			return *this;
		}

		void InstancedCube::updateModelMatrix() noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(size);
			if ( rotation.x > 0 )
				m_modelMatrix.rotateXD(rotation.x);
			if ( rotation.y > 0 )
				m_modelMatrix.rotateYD(rotation.y);
			if ( rotation.z > 0 )
				m_modelMatrix.rotateZD(rotation.z);
			m_modelMatrix.translate(position);
			m_changed = true;
		}

		void InstancedCube::updateBufferData() noexcept
		{
			if ( m_changed )
			{
				m_manager->m_copyBuffer.setData(&m_textureId, ( sizeof(int) + sizeof(maths::Mat4f) ), m_pos * ( sizeof(int) + sizeof(maths::Mat4f) ));
				m_changed = false;
			}
		}

		void InstancedCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos == -1 )
				std::cout << "Error InstancedCube::remove(): InstancedCube was already removed" << std::endl;
#endif
			m_manager->m_instanceCubes.back()->m_pos = m_pos;
			m_manager->m_instanceCubes.back()->m_changed = true;
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
			m_manager->m_instanceCubes.push_back(this);
			m_changed = true;
			if ( instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) + ( sizeof(int) + sizeof(maths::Mat4f) ) >= m_manager->m_copyBuffer.getSize() )
			{
				m_manager->m_copyBuffer.bind();
				m_manager->m_copyBuffer.setSize(instanceCount * ( sizeof(int) + sizeof(maths::Mat4f) ) * 2);
			}
		}

		void InstancedCube::setTexture(int textureId) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textureArray.getTextureCount()<=textureId)
				std::cout << "Error InstancedCube::setTexture(): TextureId is not in the texturearray2d of the cubemanager" << std::endl;
#endif
			m_textureId = textureId;
			m_changed = true;
		}

		void InstancedCube::setTexture(const utils::Image& image) noexcept
		{
			m_textureId = m_manager->m_textureArray.getTextureId(image);
			m_changed = true;
		}

		void InstancedCube::setTexture(const std::string& imagePath) noexcept
		{
			m_textureId = m_manager->m_textureArray.getTextureId(imagePath);
			m_changed = true;
		}

		const utils::Image& InstancedCube::getTextureImage() noexcept
		{
			return m_manager->m_textureArray.getTexture(m_textureId);
		}

		void InstancedCube::changeRenderer(Renderer* renderer) noexcept
		{
			const utils::Image& image = getTextureImage();
			if ( m_pos != -1 )
			{
				remove();
				m_manager = &renderer->cubeManager;
				add();
			}
			else
			{
				m_manager = &renderer->cubeManager;
			}
			m_textureId = m_manager->m_textureArray.getTextureId(image);
		}

		const Renderer* const InstancedCube::getRenderer() const noexcept
		{
			return m_manager->m_renderer;
		}

	}
}
