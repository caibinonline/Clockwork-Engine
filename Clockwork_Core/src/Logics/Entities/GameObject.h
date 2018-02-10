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
#include "src\Maths\Vec3.h"
#include "src\Maths\Mat4x4.h"


namespace clockwork {
	namespace logics {

		class State;

		class GameObject
		{

		protected://auch in subklassen immer erst mutex locken, etc | oder getter/setter nehmen 
			State * m_state;
			maths::Mat4f m_modelMatrix;
			maths::Vec3f m_size;
			maths::Vec3f m_rotation;
			maths::Vec3f m_position;

		public:
			GameObject(State* state) noexcept;
			GameObject(const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state) noexcept;
			virtual ~GameObject() noexcept;
			GameObject(const GameObject& other) noexcept;
			GameObject(GameObject&& other) noexcept;
			GameObject& operator=(const GameObject& other) noexcept;
			GameObject& operator=(GameObject&& other) noexcept;
			

		protected:
			//muss überschrieben werden und dann für instancedcubes setchanged(true) aufrufen 
			virtual void onMatrixChange() noexcept = 0;

		public:
			//updated modelmatrix und ruft onMatrixChange auf | immer nach verändern der vektoren irgendwann updatemodelmatrix aufrufen
			void updateModelMatrix() noexcept;

			const State& getState() const noexcept;
			//hier threadsafe machen ohne const kann state verändert werden
			State& getState() noexcept;

			inline const maths::Mat4f& getModelMatrix() const noexcept {return m_modelMatrix;}
			inline const maths::Mat4f* getModelMatrixMemoryLocation() const noexcept {return &m_modelMatrix;}
			inline const maths::Vec3f& getSize() const noexcept {return m_size;}
			inline const maths::Vec3f& getRotation() const noexcept {return m_rotation;}
			inline const maths::Vec3f& getPosition() const noexcept {return m_position;}
			inline maths::Vec3f& getSize() noexcept{return m_size;}//ab hier mutex setzen
			inline maths::Vec3f& getRotation() noexcept{return m_rotation;}
			inline maths::Vec3f& getPosition() noexcept{return m_position;}

		};

	}
}


