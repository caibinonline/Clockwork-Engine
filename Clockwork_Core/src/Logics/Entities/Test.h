#pragma once
#include "Listener\RenderListener.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "src\Graphics\Renderables\Cube\Cube.h"
#include "src\Core\Engine.h"
#include "src\Core\Window.h"

#include "src\Logics\ChunkSystem\ChunkTemplates.h"
#include "src\Logics\States\State.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Physics\Colliders\CubeCollider.h"
#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		struct Block : public RenderListener, public StaticTickListener
		{
			graphics::InstancedCube cube;
			physics::CubeCollider cubeCollider;
			Block(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(textureId, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
			}
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
					m_rotation.y += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60 * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60 * time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;
				this->GameObject::updateModelMatrix();
			}
			void slowTick() noexcept override
			{

			}
			void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				//MovingBlock* block = dynamic_cast<MovingBlock*>( otherMoving );///geht hier nicht, da alles in einer datei ist
				//std::cout << "COLLISION STATIC TO MOVING" << std::endl;
			}
		protected:
			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);
			}
		};

		struct MovingBlock : public RenderListener, public MovingTickListener
		{
			graphics::InstancedCube cube;
			physics::CubeCollider cubeCollider;
			MovingBlock(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(textureId, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
				m_direction.x = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				m_direction.y = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				m_direction.z = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
			}
		public:
			virtual void renderAdd() noexcept override
			{
				cube.add();
			}
			virtual void renderRemove() noexcept override
			{
				cube.remove();
			}
			virtual void tick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				m_position += m_direction * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_RIGHT) )
					m_rotation.y += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60 * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60 * time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;

				if ( m_position.distance(m_chunk->getChunkSystem().getState().getCurrentCamera().getPosition()) > 40 )
				{
					m_direction = (m_chunk->getChunkSystem().getState().getCurrentCamera().getPosition() - m_position)/2;
				}

				this->GameObject::updateModelMatrix();
			}
			virtual void slowTick() noexcept override
			{
// 				m_direction.x = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
// 				m_direction.y = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
// 				m_direction.z = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
			}
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				MovingBlock* block = dynamic_cast<MovingBlock*>( otherMoving );//eigentlich noch nullptr test
				m_direction = m_position - block->getPosition();;//other direction
				m_direction *= 4;
				m_position += m_direction * time;//offset, damit collision nicht mehrmals triggert
			}
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				Block* block = dynamic_cast<Block*>( otherStatic );
				m_direction = m_position - block->getPosition();//other direction
				m_direction *= 4;
				m_position += m_direction * time;//offset, damit collision nicht mehrmals triggert

			}
		protected:
			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);//wenn instanced
			}
		};

		struct TransparentBlock : public RenderListener
		{
			graphics::NormalCube cube;
			TransparentBlock(const std::string& test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				RenderListener::init();
			}
			TransparentBlock(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				: GameObject(size, rotation, position, state), cube(test, true, this, renderer)
			{
				RenderListener::init();
			}
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
		protected:
			void onMatrixChange() noexcept override
			{

			}
		};

	}
}