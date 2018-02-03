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
#include "VertexBuffer.h"
#include "CopyBuffer.h"
#include "InternalCopyBuffer.h"
#include "VertexArray.h"

namespace clockwork {
	namespace graphics {

		GLuint VertexBuffer::vaoOffset { 0 };
		GLuint VertexBuffer::VaoPos { 0 };
		InternalCopyBuffer* VertexBuffer::copyBuffer { nullptr };
#if CLOCKWORK_DEBUG
		std::vector<VertexBuffer*> VertexBuffer::debug_buffers;
		std::vector<VertexArray*> VertexArray::debug_vertexarrays;
#endif

		void VertexBuffer::setData(const void* data, unsigned int size, unsigned int offset/*=0*/) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error VertexBuffer::setData(): VertexBuffer was not bound" << std::endl;
#endif
			glBufferSubData(bufferType, offset, size, data);
		}

		void VertexBuffer::setSize(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error VertexBuffer::setSize(): VertexBuffer was not bound" << std::endl;
#endif
			copyBuffer->bind();
			if ( size > copyBuffer->getSize() )
				copyBuffer->reset(size);
			copyBuffer->copy(*this);
			this->copy(*copyBuffer);
		}

		void VertexBuffer::reset(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error VertexBuffer::reset(): VertexBuffer was not bound" << std::endl;
#endif
			glBufferData(bufferType, size, nullptr, m_bufferMode);
			m_size = size;
		}

		VertexBuffer& VertexBuffer::copy(const VertexBuffer& other) noexcept
		{
			copyBuffer->bind();
			if ( other.m_size > copyBuffer->getSize() )
				copyBuffer->reset(other.m_size);
			 other.bind();
			copyBuffer->copy(other);
			this->bind();
			if ( other.m_size > m_size )
				this->reset(other.m_size);
			this->copy(*copyBuffer);
			return *this;
		}

		VertexBuffer& VertexBuffer::copy(const CopyBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error VertexBuffer::copy(): VertexBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error VertexBuffer::copy(): CopyBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

		VertexBuffer& VertexBuffer::copy(const InternalCopyBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error VertexBuffer::copy(): VertexBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error VertexBuffer::copy(): InternalCopyBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

	}
}