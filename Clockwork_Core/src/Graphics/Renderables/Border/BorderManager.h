#pragma once
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
#include <vector>
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"

namespace clockwork {
	namespace graphics {

		//nur defaultrenderer hat dann bordermanager objekt und rendert ihn mit dem extra bordershader, der nicht anpassbar ist 
		//hier werden dann linien mit den vbos/vaos für die borders gemalt

		class CubeBorder;
		class Renderer;

		class BorderManager
		{

		private:
			friend class Renderer;
			friend class CubeBorder;
			friend class SphereBorder;
			using floatarr = float[8*3];
			using uchararr = unsigned  char[24];

		private:
			std::vector<CubeBorder*> m_cubeBorders;
			Renderer* m_renderer;
			VertexArray m_vao;
			VertexBuffer m_vbo;
			IndexBuffer<unsigned char> m_ibo;

		public:
			BorderManager(Renderer* renderer);

		public:
			void render() noexcept;
			const unsigned int getSize() noexcept{return m_cubeBorders.size();}//hier auch noch size von sphereborders drauf addieren

		};


	}
}