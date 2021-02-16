#pragma once

//c++ includes

//external (custom) library includes
#include <glad/glad.h>

//game engine includes
#include <trem/renderer/vertex_buffer.h>
#include <trem/renderer/buffer_layout.h>
#include <trem/renderer/index_buffer.h>

/**
 *  \brief Parent class for any object within the game
 *
 */
namespace Trem
{
  class VertexArray
  {
    public:
      VertexArray(const VertexArray&) = default;
      VertexArray(VertexArray&&) = default;
      VertexArray& operator=(const VertexArray&) = default;
      VertexArray& operator=(VertexArray&&) = default;

      VertexArray();
      ~VertexArray();

      //custom constructors

      //Member variables

      //Member functions
      /**
        \brief Binds the vertex array for usage.
       */
      void bind() const;

      /**
        \brief Breaks the binding of the current vertex array object.
       */
      static void unbind();

      /**
       * \brief Creates the underlying opengl buffer objects.
       * @param maxVertices Size of the vertex buffer.
       * @param maxIndices  Size of the index buffer.
       */
      void createBuffers(uint32_t maxVertices, uint32_t maxIndices);

      ShaPtr<IndexBuffer> indexBuffer() const;
      ShaPtr<VertexBuffer> vertexBuffer() const;
      ShaPtr<BufferLayout> bufferLayout() const;

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      unsigned int vertexArrayId_; /**< unique opengl id*/
      ShaPtr<VertexBuffer> vertexBuffer_;
      ShaPtr<BufferLayout> bufferLayout_;
      ShaPtr<IndexBuffer>  indexBuffer_;  

      /**
        \brief Defines the layout of the vertex buffer (engine side).
       */
      void defineVbLayout() const;

      /**
       * \brief Defines the vertex buffer (opengl side).<br>
       *        Sets the vertex attribute pointers according to the vertex buffer layout.
       */
      void defineVb() const; 

      //Member functions
  };
}
