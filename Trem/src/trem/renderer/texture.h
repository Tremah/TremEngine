#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <stb/stb_image.h>

//custom (own) library includes
#include <glm/vec2.hpp>

//game engine includes
#include <trem/util/file.h>

/**
 *  \brief Class to represent a texture
 *
 */
namespace Trem
{
  class Texture
  {
    public:
      //Constructors and deconstructors 
      Texture(const Texture&) = default;
      Texture(Texture&&) = default;
      Texture& operator=(const Texture&) = default;
      Texture& operator=(Texture&&) = default;

      /**
       * \brief Parameterized constructor to construct a Texture from a file path.
       * @param filePath Path to the texture's source file.
       * @param name     Name of the texture.
      */
      Texture(const std::string& name, const std::string& filePath);
      ~Texture();

      //Member variables

      //Member functions
      /**
       * \brief Returns a 2D vector containing width and height of the texture.
       * \return 2D vector containing width and height
       */
      glm::vec2 dimensions() const;
      std::string name() const;
      uint32_t id() const;

    protected:
     //Member variables

     //Member functions

    private:
     //Member variables
      uint32_t textureId_;    
      std::string name_;
      int32_t width_;                
      int32_t height_;               
      int32_t bPP_;                  /**< bits per pixel, png channels, etc.*/
      unsigned char* textureBuffer_; /**< raw pointer bcs. of stb_image */

     //Member functions
 };
}