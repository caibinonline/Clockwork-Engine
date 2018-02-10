#pragma once
#include "GameObject.h"
#include "src\Graphics\Renderables\Cube\Cube.h"

namespace clockwork {
	namespace logics {

		class InstancedTest : public GameObject
		{
		public:
			graphics::InstancedCube cube;


			InstancedTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				cube.add();
			}

		protected:

			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);
			}
		};

		class NormalTest : public GameObject
		{
		public:
			graphics::NormalCube cube;

			NormalTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, false, this, renderer)
			{
				cube.add();
			}
		protected:

			void onMatrixChange() noexcept override
			{

			}
		};

		class TransparentTest : public GameObject
		{
		public:
			graphics::NormalCube cube;

			TransparentTest(const std::string& test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				cube.add();
			}
			TransparentTest(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				: GameObject(size, rotation, position, state), cube(test, true, this, renderer)
			{
				cube.add();
			}
		protected:

			void onMatrixChange() noexcept override
			{

			}
		};

	}
}