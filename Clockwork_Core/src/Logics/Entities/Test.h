#pragma once
#include "Listener\RenderListener.h"
#include "src\Graphics\Renderables\Cube\Cube.h"

namespace clockwork {
	namespace logics {

		class InstancedTest : public RenderListener
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

	}
}