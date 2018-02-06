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
#include "src\Graphics\Renderer\Renderer.h"

namespace clockwork {
	namespace graphics {


		NormalCube::NormalCube(Renderer* renderer, bool transparent) noexcept
			: m_textureId(0), m_modelMatrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), m_visible(false), m_transparent(transparent), m_pos(-1)
		{
			if ( transparent )
				m_manager = &renderer->transparentCubeManager;
			else
				m_manager = &renderer->cubeManager;
		}

		NormalCube::NormalCube(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer, bool transparent) noexcept
			: m_textureId(textureId), size(size), rotation(rotation), position(position), m_visible(true), m_transparent(transparent), m_pos(-1)
		{
			if ( transparent )
				m_manager = &renderer->transparentCubeManager;
			else
				m_manager = &renderer->cubeManager;
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textures.size() <= textureId )
				std::cout << "Error NormalCube::NormalCube(): TextureId is not in the texture list of the cubemanager" << std::endl;
#endif
			updateModelMatrix();
		}

		NormalCube::NormalCube(const std::string& imagePath, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: size(size), rotation(rotation), position(position), m_visible(true), m_pos(-1)
		{
			if ( renderer->cubeManager.containsNormalTexture(imagePath) )
			{
				m_manager = &renderer->cubeManager;
				m_textureId = m_manager->getNormalTextureId(imagePath);
			}
			else if ( renderer->transparentCubeManager.containsNormalTexture(imagePath) )
			{
				m_manager = &renderer->transparentCubeManager;
				m_textureId = m_manager->getNormalTextureId(imagePath);
			}
			else
			{
				utils::Image image(imagePath);
				image.load();
				if ( image.hasAlpha() )
				{
					m_manager = &renderer->transparentCubeManager;
				}
				else
				{
					m_manager = &renderer->cubeManager;
				}
				m_textureId = m_manager->getNormalTextureId(image);
			}
			m_transparent = m_manager->m_transparent;
			updateModelMatrix();
		}

		NormalCube::NormalCube(const utils::Image& image, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, Renderer* renderer) noexcept
			: size(size), rotation(rotation), position(position), m_visible(true), m_pos(-1)
		{
			if ( image.hasAlpha() )
				m_manager = &renderer->transparentCubeManager;
			else
				m_manager = &renderer->cubeManager;

			m_textureId = m_manager->getNormalTextureId(image);
			m_transparent = m_manager->m_transparent;
			updateModelMatrix();
		}

		NormalCube::~NormalCube() noexcept
		{
			if ( m_pos!=-1 )
				this->remove();
		}

		NormalCube::NormalCube(NormalCube&& other) noexcept
			: m_textureId(other.m_textureId), m_modelMatrix(other.m_modelMatrix), m_visible(other.m_visible), m_transparent(other.m_transparent), m_pos(other.m_pos), m_manager(other.m_manager)
		{
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			other.m_visible = false;
			other.m_transparent = false;
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_normalCubes.at(m_pos) = this;
		}

		NormalCube& NormalCube::operator=(NormalCube&& other) noexcept
		{
			if ( m_pos != -1 )
				this->remove();
			m_textureId = other.m_textureId;
			m_modelMatrix = other.m_modelMatrix;
			m_visible = other.m_visible;
			m_transparent = other.m_transparent;
			m_pos = other.m_pos;
			m_manager = other.m_manager;
			other.m_textureId = 0;
			other.m_modelMatrix = maths::Mat4f(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			other.m_visible = false;
			other.m_transparent = false;
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
				m_manager->m_normalCubes.at(m_pos) = this;
			return *this;
		}

		void NormalCube::render() noexcept
		{
			Shader* shader = m_manager->m_renderer->m_normalShader;
			shader->setUniform("u_model",m_modelMatrix);
		}

		void NormalCube::updateModelMatrix() noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(size);
			if ( rotation.x > 0 )
				m_modelMatrix.rotateXD(rotation.x);
			if ( rotation.y > 0 )
				m_modelMatrix.rotateYD(rotation.y);
			if ( rotation.z > 0 )
				m_modelMatrix.rotateZD(rotation.z);
			m_modelMatrix.translate(position);
		}

		void NormalCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos == -1 )
				std::cout << "Error NormalCube::remove(): NormalCube was already removed" << std::endl;
#endif
			m_manager->m_normalCubes.back()->m_pos = m_pos;
			m_manager->m_normalCubes.at(m_pos) = m_manager->m_normalCubes.back();
			m_pos = -1;
			m_manager->m_normalCubes.erase(m_manager->m_normalCubes.end() - 1);
		}

		void NormalCube::add() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_pos != -1 )
				std::cout << "Error NormalCube::add(): NormalCube was already added" << std::endl;
#endif
			m_pos = m_manager->m_normalCubes.size();
			m_manager->m_normalCubes.push_back(this);
		}

		void NormalCube::setTexture(int textureId, bool transparent) noexcept
		{
			if ( transparent != m_transparent )
			{
				if ( transparent )
				{
					m_transparent = true;
					if ( m_pos != -1 )
					{
						remove();
						m_manager = &m_manager->m_renderer->transparentCubeManager;
						add();
					}
					else
						m_manager = &m_manager->m_renderer->transparentCubeManager;
				}
				else
				{
					m_transparent = false;
					if ( m_pos != -1 )
					{
						remove();
						m_manager = &m_manager->m_renderer->cubeManager;
						add();
					}
					else
						m_manager = &m_manager->m_renderer->cubeManager;
				}
			}
#if CLOCKWORK_DEBUG
			if ( m_manager->m_textures.size() <= textureId )
				std::cout << "Error NormalCube::setTexture(): TextureId is not in the texture list of the cubemanager" << std::endl;
#endif
			m_textureId = textureId;
		}

		void NormalCube::setTexture(const utils::Image& image) noexcept
		{
			if ( image.hasAlpha() )
			{
				if ( m_manager != &m_manager->m_renderer->transparentCubeManager )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_manager = &m_manager->m_renderer->transparentCubeManager;
						add();
					}
					else
						m_manager = &m_manager->m_renderer->transparentCubeManager;
					m_transparent = true;
				}
			}
			else
			{
				if ( m_manager != &m_manager->m_renderer->cubeManager )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_manager = &m_manager->m_renderer->cubeManager;
						add();
					}
					else
						m_manager = &m_manager->m_renderer->cubeManager;
					m_transparent = false;
				}
			}
			m_textureId = m_manager->getNormalTextureId(image);
		}

		void NormalCube::setTexture(const std::string& imagePath) noexcept
		{
			if ( m_manager->m_renderer->cubeManager.containsNormalTexture(imagePath) )
			{
				if ( m_pos != -1 )
				{
					remove();
					m_manager = &m_manager->m_renderer->cubeManager;
					add();
				}
				else
					m_manager = &m_manager->m_renderer->cubeManager;
				m_transparent = false;
				m_textureId = m_manager->getNormalTextureId(imagePath);
			}
			else if ( m_manager->m_renderer->transparentCubeManager.containsNormalTexture(imagePath) )
			{
				if ( m_pos != -1 )
				{
					remove();
					m_manager = &m_manager->m_renderer->transparentCubeManager;
					add();
				}
				else
					m_manager = &m_manager->m_renderer->transparentCubeManager;
				m_transparent = true;
				m_textureId = m_manager->getNormalTextureId(imagePath);
			}
			else
			{
				utils::Image image(imagePath);
				image.load();
				setTexture(image);
			}
		}

		void NormalCube::setVisible(bool visible) noexcept
		{
			m_visible = visible;
		}

		const utils::Image& NormalCube::getTextureImage() noexcept
		{
			return m_manager->m_textures.at(m_textureId).getImage();
		}

		const Renderer* const NormalCube::getRenderer() const noexcept
		{
			return m_manager->m_renderer;
		}

	}
}


