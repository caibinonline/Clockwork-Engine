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
#include "InternalCopyBuffer.h"
#include "CopyBuffer.h"
#include "VertexBuffer.h"

namespace clockwork {
	namespace graphics {

		CopyBuffer* InternalCopyBuffer::copyBuffer { nullptr };
#if CLOCKWORK_DEBUG
		std::vector<InternalCopyBuffer*> InternalCopyBuffer::debug_buffers;
#endif

		void InternalCopyBuffer::setData(const void* data, unsigned int size, unsigned int offset /*= 0*/) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error InternalCopyBuffer::setData(): InternalCopyBuffer was not bound" << std::endl;
#endif
			glBufferSubData(bufferType, offset, size, data);
		}

		void InternalCopyBuffer::setSize(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error InternalCopyBuffer::setSize(): InternalCopyBuffer was not bound" << std::endl;
#endif
			copyBuffer->bind();
			if ( size > copyBuffer->getSize() )
				copyBuffer->reset(size);
			copyBuffer->copy(*this);
			this->copy(*copyBuffer);
		}

		void InternalCopyBuffer::reset(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error InternalCopyBuffer::reset(): InternalCopyBuffer was not bound" << std::endl;
#endif
			glBufferData(bufferType, size, nullptr, m_bufferMode);
			m_size = size;
		}

		InternalCopyBuffer& InternalCopyBuffer::copy(const InternalCopyBuffer& other) noexcept
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

		InternalCopyBuffer& InternalCopyBuffer::copy(const VertexBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error InternalCopyBuffer::copy(): InternalCopyBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error InternalCopyBuffer::copy(): VertexBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

		InternalCopyBuffer& InternalCopyBuffer::copy(const CopyBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error InternalCopyBuffer::copy(): InternalCopyBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error InternalCopyBuffer::copy(): CopyBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

	}
}