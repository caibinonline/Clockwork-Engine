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
#include "src\Maths\MathFunctions.h"

#define CHUNK_BORDER 1

namespace clockwork {
	namespace graphics {
		class CubeBorder;
	}

	namespace logics {

		class State;
		class ChunkSystem;
		class RenderListener;
		class GameObject;
		class RenderListener;
		class MovingTickListener;
		class StaticTickListener;

		class Chunk
		{

		private:
			friend class ChunkSystem;

		private:
			maths::Vec3f m_min;
			maths::Vec3f m_max;
			maths::Vec3i m_id;//id is 0 to chunksize-1
			ChunkSystem* m_chunkSystem;

#if CHUNK_BORDER
			graphics::CubeBorder* m_border;
#endif

			std::vector<RenderListener*> m_renderList;//noch in konstruktor/movekonstruktor/copy/etc einbinden | ggf auch von gameobjects setchunk zum ändern machen und in destruktor von gameobject müssen sie sich auch löschen | die moving sachen können sich auch von chunk zu chunk bewegen(ggf testen ob x höher ist, dann id.x++ und auch so für andere, etc)
			std::vector<MovingTickListener*> m_movingTickList;
			std::vector<StaticTickListener*> m_staticTickList;

		public:
			Chunk() noexcept;
			~Chunk() noexcept;

		private:
			void init(const maths::Vec3f& min, const maths::Vec3f& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept;

		public:
			void renderAdd() noexcept;
			void renderRemove() noexcept;
			void fastTick() noexcept;
			void mediumTick() noexcept;
			void slowTick() noexcept;
			void updateCollision() noexcept;

			void addRenderListener(RenderListener* listener) noexcept;
			void removeRenderListener(RenderListener* listener) noexcept;
			void addMovingTickListener(MovingTickListener* listener) noexcept;
			void removeMovingTickListener(MovingTickListener* listener) noexcept;
			void addStaticTickListener(StaticTickListener* listener) noexcept;
			void removeStaticTickListener(StaticTickListener* listener) noexcept;

			/*passes a function to the chunk itself and the sorrounding chunks(3x3 cube) | you have to call this method with a functor struct layout like the following
			the positions can be negative below 0, or above the count and the method will cut it into the range
			struct SlowTickFunctor
			{
			void function(Chunk& chunk) noexcept
			{
			chunk.slowTick();
			}
			};
			passFunctionToArea<SlowTickFunctor>();
			*/
			template<typename functor>void passFunctionToArea() noexcept;
			//in relation zum currentchunk, ob der chunk hier in renderdistance liegt
			const bool inRenderDistance() const noexcept;
			const bool inTickDistance() const noexcept;
		public:
			friend bool operator==(const Chunk& c1, const Chunk& c2) noexcept;
			friend bool operator!=(const Chunk& c1, const Chunk& c2) noexcept;

		public:
			const maths::Vec3i getId() const noexcept{return m_id;}//braucht wahrscheinlich keine mutex, da es nur beim erstellen der chunks verändert wird und dann nicht mehr
			const ChunkSystem& getChunkSystem() const noexcept;
			ChunkSystem& getChunkSystem() noexcept;
		};

	}
}