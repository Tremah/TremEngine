#include <trpch.h>
#include "index_buffer.h"

namespace Trem
{
  IndexBuffer::IndexBuffer(const uint32_t size) : indexBufferId_{0}
  {
    //createBuffers index buffer
    glCreateBuffers(1, &indexBufferId_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
  }

  IndexBuffer::~IndexBuffer()
  {
    glDeleteBuffers(1, &indexBufferId_);
  }

  void IndexBuffer::bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);
  }

  void IndexBuffer::unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

}
