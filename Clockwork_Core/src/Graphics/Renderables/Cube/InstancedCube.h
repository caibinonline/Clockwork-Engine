#pragma once
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
#include "src\Maths\Vec3.h"
#include "src\Maths\Mat4x4.h"
#include "src\Utils\Image.h"

namespace clockwork {
	namespace graphics {

		class InstancedRenderer;

		/*this is an instanced textured cube for drawing many small models with the same shader
		there will be one model and some textures in the cubemanager and each instancedcube is an instance of this model 
		where the modelmatrix is used to display the instance with its transformation in the world and the textureid is used to display the correct texture
		the instancedcube will have a pointer to a renderer, where a cubemanager will render all instancedcubes that are added to the cubemanager
		the cubemanager can also add a texture to prepare for instancedcubes(textures are also automaticly added when adding instancedcubes), or remove an instancedcube from the render list
		every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
		class InstancedCube
		{

		private:
			friend class CubeManager;
			/*the data of each instance/object of the model(textureid for the texturearray and modelmatrix fro the transformation in the world*/
			struct Data
			{
				int textureId;///später wahrscheinlich materialid mit materialarray benutzen | dann auch materialarray, etc machen 
				maths::Mat4f modelMatrix;
				Data() noexcept;
				Data(int textureId, const maths::Mat4f& modelMatrix) noexcept;
				Data(const Data& other) noexcept;
				Data(Data&& other) noexcept;
				Data& operator=(const Data& other) noexcept;
				Data& operator=(Data&& other) noexcept;
			} m_data;
			int m_pos;
			InstancedRenderer* m_renderer;

		public:

			/*creates an empty instancedcube data = 0 that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			explicit InstancedCube(InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			dont use this constructor, if the count of textures/images in the texturearray2d of the cubemanager is equal or less than the textureID, because it will give an error
			@param[textureId] the id of the texture in the texturearray2d of the cubemanager that will be used for this model
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[mat] the modelmatrix of the instance/object that will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(int textureId, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[imagePath] the path of a texture/image that will be used for this model 
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[mat] the modelmatrix of the instance/object that will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const std::string& imagePath, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[imagePath] the texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			@param[mat] the modelmatrix of the instance/object that will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const utils::Image& image, const maths::Mat4f& mat, InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			dont use this constructor, if the count of textures/images in the texturearray2d of the cubemanager is equal or less than the textureID, because it will give an error
			@param[textureId] the id of the texture in the texturearray2d of the cubemanager that will be used for this model
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[scaling] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[translation] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(int textureId, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[imagePath] the path of a texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[scaling] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[translation] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const std::string& imagePath, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[image] the texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[scaling] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[translation] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const utils::Image& image, const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation, InstancedRenderer* renderer) noexcept;

			/*removes the instancedcube from the cubemanager, if its currently added to it*/
			~InstancedCube() noexcept;

			InstancedCube(const InstancedCube& other) = delete;

			/*moves the data, removes the old this object from the cubemanager and changes the pointer in the list of the cubemanager from the other object to this object*/
			InstancedCube(InstancedCube&& other) noexcept;

			InstancedCube& operator=(const InstancedCube& other) = delete;

			/*moves the data, removes the old this object from the cubemanager and changes the pointer in the list of the cubemanager from the other object to this object*/
			InstancedCube& operator=(InstancedCube&& other) noexcept;

		public:
			/*updates the data(textureid, modelmatrix) of this instancedcube in the buffer(gpu side) of the cubemanager | will be called from setVisible() and must not be called manually*/
			void updateBufferData() noexcept;

			/*sets the data(textureid, modelmatrix) of this instancedcube in the buffer(gpu side) of the cubemanager to 0(instance, object will not be visible) | will be called from setVisible() and must not be called manually*/
			void clearBufferData() noexcept;

			/*removes the instancedcube from the cubemanager in the instancedrender | the last instancedcube in the list of the cubemanager will swap positions with this instancedcube and then this instancedcube(then the last instancedcube in the list) will be removed from the list
			dont call the remove function again if the instancedcube is already removed | you have to call add first | the destructor will also call remove
			use add()/remove() for few changes with many models to hide/show objects/instances and use setVisible(true/false) for many changes with few models
			BUT setvisible will not give any performance boost, because the render call will still happen | add/remove will give a performanceboost, because the render call will not happen*/
			void remove() noexcept;

			/*adds the instancedcube to the cubemanager in the instancedrender | the instancedcube will be added to the end of the list
			dont call the add function again if the instancedcube is already added | you have to call remove first | the constructor will not automaticly call add()
			use add()/remove() for few changes with many models to hide/show objects/instances and use setVisible(true/false) for many changes with few models
			BUT setvisible will not give any performance boost, because the render call will still happen | add/remove will give a performanceboost, because the render call will not happen*/
			void add() noexcept;

			/*changes the modelmatrix of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager*/
			void setModelMatrix(const maths::Mat4f& mat) noexcept;

			/*changes the modelmatrix of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			calculates the modelmatrix from the 3 vectors by first applying scaling, then rotation and then translation to the modelmatrix 
			@param[scaling] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[translation] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world*/
			void setModelMatrix(const maths::Vec3f& scaling, const maths::Vec3f& rotation, const maths::Vec3f& translation) noexcept;

			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			dont use this method, if the count of textures/images in the texturearray2d of the cubemanager is equal or less than the textureID, because it will give an error
			@param[textureId] the id of the texture in the texturearray2d of the cubemanager that will be used for this model
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(int textureId) noexcept;

			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			@param[image] the texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(const utils::Image& image) noexcept;

			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			@param[imagePath] the path of a texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(const std::string& imagePath) noexcept;

			/*hides, or shows the instance/object of the model, by setting its modelmatrix and textureid in the buffer(gpu side) of the cubemanager to the actual modelmatrix and textureid of the instancedcube for true
			or setting them to 0 in the buffer for false | use add()/remove() for few changes with many models to hide/show objects/instances and use setVisible(true/false) for many changes with few models
			BUT setvisible will not give any performance boost, because the render call will still happen | add/remove will give a performanceboost, because the render call will not happen*/
			void setVisible(bool visible) noexcept;

		};

	}
}