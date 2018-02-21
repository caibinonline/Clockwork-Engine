#pragma once
#include "Listener\RenderListener.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Graphics\Renderables\Cube\Cube.h"
#include "src\Core\Engine.h"
#include "src\Core\Window.h"

namespace clockwork {
	namespace logics {

		class InstancedTest : public RenderListener, public MovingTickListener//müsste eigentlich staticTickListener sein
		{
		public:
			graphics::InstancedCube cube;


			InstancedTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				RenderListener::init();
			}

		protected:

			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);
			}
		public:
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
			void tick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_RIGHT) )
					m_rotation.y += 60*time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60*time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60*time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60*time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;

				this->GameObject::updateModelMatrix();
			}
			void slowTick() noexcept override
			{

			}

		};

		class NormalTest : public RenderListener
		{
		public:
			graphics::NormalCube cube;

			NormalTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, false, this, renderer)
			{
				RenderListener::init();
			}
		protected:

			void onMatrixChange() noexcept override
			{

			}
		public:
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
		};

		class TransparentTest : public RenderListener
		{
		public:
			graphics::NormalCube cube;

			TransparentTest(const std::string& test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				RenderListener::init();
			}
			TransparentTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				: GameObject(size, rotation, position, state), cube(test, true, this, renderer)
			{
				RenderListener::init();
			}
		protected:

			void onMatrixChange() noexcept override
			{

			}
		public:
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
		};

		class MovingTest : public RenderListener, public MovingTickListener
		{
		public:
			graphics::InstancedCube cube;
			maths::Vec3f vel;

			MovingTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				RenderListener::init();
			}
		protected:

			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);//wenn instanced
			}
		public:
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
			void tick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				m_position += vel * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_RIGHT) )
					m_rotation.y += 60*time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60*time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60*time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60*time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;

				this->GameObject::updateModelMatrix();
			}
			void slowTick() noexcept override
			{
				float vel1 = -(float) ( rand() % 4000 + 1 ) / 1000 + (float) ( rand() % 4000 + 1 ) / 1000;
				float vel2 = -(float) ( rand() % 4000 + 1 ) / 1000 + (float) ( rand() % 4000 + 1 ) / 1000;
				float vel3 = -(float) ( rand() % 4000 + 1 ) / 1000 + (float) ( rand() % 4000 + 1 ) / 1000;
				vel = { vel1,vel2,vel3 };
			}

		};

	}
}