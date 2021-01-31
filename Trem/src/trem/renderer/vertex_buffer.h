#pragma once

//c++ includes

//external (custom) library includes
#include <glad/glad.h>

//game engine includes

/**
 *  \brief Vertex buffer object
 *
 */
namespace Trem
{
  class VertexBuffer
  {
  public:
    VertexBuffer(const VertexBuffer&) = default;
    VertexBuffer(VertexBuffer&&) = default;
    VertexBuffer& operator=(const VertexBuffer&) = default;
    VertexBuffer& operator=(VertexBuffer&&) = default;
    
    ~VertexBuffer();

    //custom constructors
    VertexBuffer(uint32_t size);

    //public member variables

    //public member functions
    /**
      \brief Binds the vertex buffer for usage.
     */
    void bind() const;

    /**
      \brief Breaks the binding of the vertex buffer
     */
    static void unbind();

  protected:
    //protected member variables

    //protected member functions

  private:
    //private member variables
    unsigned int vertexBufferID_; /**< unique opengl id*/
  };
}