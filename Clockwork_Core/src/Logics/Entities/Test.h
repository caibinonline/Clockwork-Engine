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
			void fastTick() noexcept override
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
			void mediumTick() noexcept override
			{

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
			virtual void fastTick() noexcept override
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
			virtual void mediumTick() noexcept override
			{

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
				if ( block != nullptr )//ggf noch mass und winkel berücksichtigen | reflektieren und ggf noch speed variable einbauen 
				{
				m_direction = m_position - block->getPosition();;//other direction
				m_direction *= 4;
				m_position += m_direction * time;//offset, damit collision nicht mehrmals triggert
				}
				this->GameObject::updateModelMatrix();
			}
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				Block* block = dynamic_cast<Block*>( otherStatic );
				if ( block != nullptr )
				{
				m_direction = m_position - block->getPosition();//other direction
				m_direction *= 4;
				m_position += m_direction * time;//offset, damit collision nicht mehrmals triggert | muss aber bei nur einer direction eigentlich nicht, da es im nächsten tick verarbeitet wird mit der neuen direction | nur bei 2 moving objekten ist es schwer, da sich beide ineinander bewegen könnten
				}
				this->GameObject::updateModelMatrix();
			}
		protected:
			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);//wenn instanced
			}
		};

		struct Player : public RenderListener, public MovingTickListener
		{
			graphics::InstancedCube cube;
			physics::CubeCollider cubeCollider;
			Player(State* state, graphics::Renderer* renderer) noexcept
				:GameObject({1.0f,2.0f,1.0f}, {0,0,0}, {0,0,0}, state), cube(1, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
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
			virtual void fastTick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 


				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_I) )//lieber später mit onkeypress machen und dann direction umschalten, aber noch mit boolean und onrelease wieder direction auf 0
				{
					m_direction.z = 1;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_K) )
				{
					m_direction.z = -1;
				}
				else
				{
					m_direction.z = 0;
				}
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_J) )
				{
					m_direction.x = -1;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_L) )
				{
					m_direction.x = 1;
				}
				else
				{
					m_direction.x = 0;
				}
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_U) )
				{
					m_direction.y = -1;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_O) )
				{
					m_direction.y = 1;
				}
				else
				{
					m_direction.y = 0;
				}


				m_position += m_direction * time;
				this->GameObject::updateModelMatrix();
			}
			virtual void mediumTick() noexcept override
			{

			}
			virtual void slowTick() noexcept override
			{
				std::cout << "Player: " << m_position << std::endl;
			}
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				MovingBlock* block = dynamic_cast<MovingBlock*>( otherMoving );//eigentlich noch nullptr test
				m_direction = m_position - block->getPosition();//other direction
				m_position += m_direction * time;
				this->GameObject::updateModelMatrix();
			}
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				Block* block = dynamic_cast<Block*>( otherStatic );
				//m_position += ( m_position - block->getPosition() ).normalizeSelf()*time;

				maths::Vec3f temp = ( ( m_size / 2 + block->getSize() / 2 ) - ( block->getPosition() - m_position ) );//guter ansatz, position so verschieben, je nachdem wie weit die blöcke ineinander sind 
				//velocity muss ja ggf nur bei moving blocks noch verändert werden abhängig von beiden velocitys 


				if ( temp.x > 0 )
					m_position.x -= temp.x;
				if ( temp.y > 0 )
					m_position.y -= temp.y;
				if ( temp.z > 0 )
					m_position.z -= temp.z;
// 				maths::Vec3f temp = ( ( block->getPosition() - block->getSize()/2 ) - ( m_position + m_size/2 ) );
// 				if ( temp.x <= 0 )
// 					m_position.x = temp.x;
// 				if ( temp.y <= 0 )
// 					m_position.y = temp.y;
// 				if ( temp.z <= 0 )
// 					m_position.z = temp.z;
				this->GameObject::updateModelMatrix();
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