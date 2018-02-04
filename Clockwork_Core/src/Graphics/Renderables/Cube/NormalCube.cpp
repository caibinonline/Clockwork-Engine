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
#include "NormalCube.h"
#include "src\Graphics\Renderer\InstancedRenderer.h"

namespace clockwork {
	namespace graphics {


		NormalCube::NormalCube(InstancedRenderer* renderer) noexcept
			: m_textureId(0), m_modelMatrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), m_visible(false), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::NormalCube(int textureId, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(textureId), m_modelMatrix(mat), m_visible(true), m_pos(-1), m_renderer(renderer)
		{
#if CLOCKWORK_DEBUG
			if ( m_renderer->cubeManager.m_textures.size() <= textureId )
				std::cout << "Error NormalCube::NormalCube(): TextureId is not in the texture list of the cubemanager" << std::endl;
#endif
		}

		NormalCube::NormalCube(const std::string& imagePath, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.getNormalTextureId(imagePath)), m_modelMatrix(mat), m_visible(true), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::NormalCube(const utils::Image& image, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.getNormalTextureId(image)), m_modelMatrix(mat), m_visible(true), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::NormalCube(int textureId, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(textureId), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_visible(false), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::NormalCube(const std::string& imagePath, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.getNormalTextureId(imagePath)), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_visible(true), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::NormalCube(const utils::Image& image, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept
			: m_textureId(m_renderer->cubeManager.getNormalTextureId(image)), m_modelMatrix(maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation)), m_visible(true), m_pos(-1), m_renderer(renderer)
		{

		}

		NormalCube::~NormalCube() noexcept
		{
			if ( m_pos!=-1 )
				this->remove();
		}

		NormalCube::NormalCube(NormalCube&& other) noexcept
			: m_textureId(other.m_textureId), m_modelMatrix(other.m_modelMatrix), m_visible(other.m_visible), m_pos(other.m_pos), m_renderer(other.m_renderer)
		{
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			other.m_visible = false;
			other.m_pos = -1;
			other.m_renderer = nullptr;
			if ( m_pos != -1 )
				m_renderer->cubeManager.m_normalCubes.at(m_pos) = this;
		}

		NormalCube& NormalCube::operator=(NormalCube&& other) noexcept
		{
			if ( m_pos != -1 )
				this->remove();
			m_textureId = other.m_textureId;
			m_modelMatrix = other.m_modelMatrix;
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			m_visible = other.m_visible;
			m_pos = other.m_pos;
			m_renderer = other.m_renderer;
			other.m_visible = false;
			other.m_pos = -1;
			other.m_renderer = nullptr;
			if ( m_pos != -1 )
				m_renderer->cubeManager.m_normalCubes.at(m_pos) = this;
			return *this;
		}

		void NormalCube::render() noexcept
		{
			if ( m_visible )
			{
			m_renderer->cubeManager.m_textures.at(m_textureId).bind();
			m_renderer->m_normalShader->setUniform("u_model",m_modelMatrix);
			m_renderer->cubeManager.m_indexBuffer.draw();
			}
		}

		void NormalCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos == -1 )
				std::cout << "Error NormalCube::remove(): NormalCube was already removed" << std::endl;
#endif
			m_renderer->cubeManager.m_normalCubes.back()->m_pos = m_pos;
			m_renderer->cubeManager.m_normalCubes.at(m_pos) = m_renderer->cubeManager.m_normalCubes.back();
			m_pos = -1;
			--m_renderer->cubeManager.m_normalCount;
			m_renderer->cubeManager.m_normalCubes.erase(m_renderer->cubeManager.m_normalCubes.end() - 1);
		}

		void NormalCube::add() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos != -1 )
				std::cout << "Error NormalCube::add(): NormalCube was already added" << std::endl;
#endif
			m_pos = m_renderer->cubeManager.m_normalCount;
			++m_renderer->cubeManager.m_normalCount;
			m_renderer->cubeManager.m_normalCubes.push_back(this);
		}

		void NormalCube::setModelMatrix(const maths::Mat4f& mat) noexcept
		{
			m_modelMatrix = mat;
		}

		void NormalCube::setModelMatrix(const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation) noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(scaling).rotateXD(rotation.x).rotateYD(rotation.y).rotateZD(rotation.z).translate(translation);
		}

		void NormalCube::setTexture(int textureId) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_renderer->cubeManager.m_textures.size() <= textureId )
				std::cout << "Error NormalCube::setTexture(): TextureId is not in the texture list of the cubemanager" << std::endl;
#endif
			m_textureId = textureId;
		}

		void NormalCube::setTexture(const utils::Image& image) noexcept
		{
			m_textureId = m_renderer->cubeManager.getNormalTextureId(image);
		}

		void NormalCube::setTexture(const std::string& imagePath) noexcept
		{
			m_textureId = m_renderer->cubeManager.getNormalTextureId(imagePath);
		}

		void NormalCube::setVisible(bool visible) noexcept
		{
			m_visible = visible;
		}

	}
}


