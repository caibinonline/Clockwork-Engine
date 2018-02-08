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
#include<iostream>
#include <sstream>
#include <cmath>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace clockwork {
	namespace maths {

		template<typename type>struct Mat2x2;
		template<typename type>struct Mat2x3;
		template<typename type>struct Mat2x4;
		template<typename type>struct Mat3x2;
		template<typename type>struct Mat3x3;
		template<typename type>struct Mat3x4;
		template<typename type>struct Mat4x2;
		template<typename type>struct Mat4x3;
		template<typename type>struct Mat4x4;

		/*matrices are defined as first row(--) then column(|) and to name elements in a matrix its the same, so x2 would be mat.at(1,2) | row-major layout in memory and in methods*/
		template<typename type>
		struct Mat4x2
		{

		public:
			/*first row(--), first column(|)
			ME x2
			y1 y2
			z1 z2
			w1 w2*/
			type x1;

			/*first row(--), second column(|)
			x1 ME
			y1 y2
			z1 z2
			w1 w2*/
			type x2;

			/*second row(--), first column(|)
			x1 x2
			ME y2
			z1 z2
			w1 w2*/
			type y1;

			/*second row(--), second column(|)
			x1 x2
			y1 ME
			z1 z2
			w1 w2*/
			type y2;

			/*third row(--), first column(|)
			x1 x2
			y1 y2
			ME z2
			w1 w2*/
			type z1;

			/*third row(--), second column(|)
			x1 x2
			y1 y2
			z1 ME
			w1 w2*/
			type z2;

			/*fourth row(--), first column(|)
			x1 x2
			y1 y2
			z1 z2
			ME w2*/
			type w1;

			/*fourth row(--), second column(|)
			x1 x2
			y1 y2
			z1 z2
			w1 ME*/
			type w2;

		public:
			/*seperate values constructor
			x1 x2
			y1 y2
			z1 z2
			w1 w2*/
			Mat4x2
			(
				type x1=0, type x2=0,
				type y1=0, type y2=0,
				type z1=0, type z2=0,
				type w1=0, type w2=0
			) noexcept
				:x1(x1), y1(y1), z1(z1), w1(w1), x2(x2), y2(y2), z2(z2), w2(w2)
			{}


			/*returns an identity matrix | matrices or vectors multiplied by this do not change
			1 0
			0 1
			0 0
			0 0*/
			static Mat4x2<type> identity() noexcept
			{
				return Mat4x2<type> {
						1, 0,
						0, 1,
						0, 0,
						0, 0 };
			}
		};

	}
}