#pragma once

//c++ includes

//external (custom) library includes
#include <glad/glad.h>

//game engine includes

/**
 *  \brief Parent class for any object within the game
 *
 */
namespace Trem
{
  class IndexBuffer
  {
  public:
    IndexBuffer(const IndexBuffer&) = default;
    IndexBuffer(IndexBuffer&&) = default;
    IndexBuffer& operator=(const IndexBuffer&) = default;
    IndexBuffer& operator=(IndexBuffer&&) = default;
    
    ~IndexBuffer();
    //param. constructors
    IndexBuffer(uint32_t size);

    //public member variables

    //public member functions
    /**
      \brief Binds the index buffer
     */
    void bind() const;
    /**
      \brief Unbinds the index buffer
     */
    static void unbind();

  protected:
    //protected member variables

    //protected member functions

  private:
    //private member variables
    unsigned int indexBufferId_; /**< unique opengl id*/

    //private member functions
  };
}
