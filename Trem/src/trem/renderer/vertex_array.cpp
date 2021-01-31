#include <trpch.h>
#include "vertex_array.h"

namespace Trem
{
  VertexArray::VertexArray() : vertexArrayId_{0}
  {
    glCreateVertexArrays(1, &vertexArrayId_);
  }

  VertexArray::~VertexArray()
  {
    glDeleteVertexArrays(1, &vertexArrayId_);
  }

  void VertexArray::bind() const
  {
    glBindVertexArray(vertexArrayId_);
  }

  void VertexArray::unbind()
  {
    //value of 0 breaks the current binding
    glBindVertexArray(0);
  }

  void VertexArray::create(const uint32_t maxVertices, const uint32_t maxIndices)
  {    
    bind();
    //define the vertex buffer layout
    bufferLayout_ = CreateShared<BufferLayout>();
    defineVbLayout();

    //create the vertex buffer
    uint32_t vbSize = maxVertices * bufferLayout_->layoutStats().stride_;
    vertexBuffer_ = CreateShared<VertexBuffer>(vbSize);
    //set vertex attribute pointers for the vb
    defineVb();
    
    //create the index buffer
    uint32_t ibSize = maxIndices * sizeof(uint32_t);
    indexBuffer_ = CreateShared<IndexBuffer>(ibSize);
  }

  void VertexArray::defineVbLayout() const
  {
    //define vertex buffer layout
    bufferLayout_->addBufferElement("position",       Data::BufferElementType::Float4);
    bufferLayout_->addBufferElement("color",          Data::BufferElementType::Float4);
    bufferLayout_->addBufferElement("texCoordinates", Data::BufferElementType::Float2); 
    bufferLayout_->addBufferElement("texUnit",        Data::BufferElementType::Float); 
  }

  void VertexArray::defineVb() const
  {
    uint32_t offset = 0;
    uint32_t vertexAttribCount = 0;
    const uint32_t stride = bufferLayout_->layoutStats().stride_;
    const bool normalized = GL_FALSE;
    //define and enable opengl vertex attrib pointers for each element of the layout
    vertexBuffer_->bind();
    for (const auto& element : bufferLayout_->bufferElements())
    {
      glVertexAttribPointer(vertexAttribCount, element.offset_, GL_FLOAT, normalized, stride, (const void*) (offset * sizeof(GLfloat)));
      glEnableVertexAttribArray(vertexAttribCount);
      offset += element.offset_;
      vertexAttribCount++;
    }
  }

  ShaPtr<IndexBuffer> VertexArray::indexBuffer() const
  {
    return indexBuffer_;
  }

  ShaPtr<VertexBuffer> VertexArray::vertexBuffer() const
  {
    return vertexBuffer_;
  }

  ShaPtr<BufferLayout> VertexArray::bufferLayout() const
  {
    return bufferLayout_;
  }
}