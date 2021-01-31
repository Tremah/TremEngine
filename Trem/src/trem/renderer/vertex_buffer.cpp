#include <trpch.h>
#include "vertex_buffer.h"

namespace Trem
{
  VertexBuffer::VertexBuffer(uint32_t size)
  {
    glCreateBuffers(1, &vertexBufferID_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
  }

  VertexBuffer::~VertexBuffer()
  {
    glDeleteBuffers(1, &vertexBufferID_);
  }

  void VertexBuffer::bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_);
  }

  void VertexBuffer::unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}
