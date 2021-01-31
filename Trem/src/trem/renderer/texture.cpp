#include <trpch.h>
#include "texture.h"

namespace Trem
{
  Texture::Texture(const std::string& filePath) : textureId_{0}, width_{0}, height_{0}, bPP_{0}, textureBuffer_{nullptr}
  {
    stbi_set_flip_vertically_on_load(1);
    //load texture
    textureBuffer_ = stbi_load(filePath.c_str(), &width_, &height_, &bPP_, 4);

    glGenTextures(1, &textureId_);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer_);

    name_ = Util::fileNameFromFilePath(filePath);

    if(textureBuffer_)
    {
      stbi_image_free(textureBuffer_);
    }
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &textureId_);
  }

  glm::vec2 Texture::dimensions() const
  {
    return glm::vec2{width_, height_};
  }
  
  uint32_t Texture::id() const
  {
    return textureId_;
  }
  
  std::string Texture::name() const
  {
    return name_;
  }
}
