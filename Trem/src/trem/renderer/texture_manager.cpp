#include <trpch.h>
#include "texture_manager.h"

namespace Trem
{
  void TextureManager::loadFromAssetList(const bool bind)
  {
    const std::string fileContent = Util::readFile(assetList_);
    using json = nlohmann::json;

    json textureList = json::parse(fileContent).at("textures");
    TR_ASSERT(!textureList.empty(), "Asset list does not contain any textures!")

    for (auto texture : textureList)
    {
      std::string name = texture.at("name");
      add(name, CreateShared<Texture>(texture.at("filepath")));
      if (bind)
      {
        bindTexture(name);
      }
    }

    //make sure white color texture is always in texture unit 0
    bindTexture("default");
  }
  void TextureManager::add(const std::string& name, ShaPtr<Texture>&& texture)
  {
    TR_ASSERT(!exists(name), "Texture " + name + " already defined!")

    //move shared pointer to avoid atomic ref increase/decrease
    textureLibrary_[name] = std::move(texture);
  }

  void TextureManager::remove(const std::string& name)
  {
    TR_ASSERT(exists(name), "Texture " + name + " not found!")
    if (bound(name)) textureLibrary_.erase(name);
  }

  int32_t TextureManager::bindTexture(const std::string& name)
  {
    if (!bound(name))
    {
      int32_t texUnit = nextFreeTextureUnit();
      TR_ASSERT(texUnit != -1, "Texture " + name + " could not be bound!")
      //bind the texture to a texture unit
      glActiveTexture(GL_TEXTURE0 + texUnit);
      glBindTexture(GL_TEXTURE_2D, texture(name)->id());
      textureUnits_[texUnit] = texture(name);
      return texUnit;
    }

    return textureUnit(name);
  }

  void TextureManager::unbindTexture(const std::string& name)
  {
    for (std::size_t i = 0; i < textureUnits_.size(); i++)
    {
      if (textureUnits_[i]->name() == name)
      {
        glActiveTexture(GL_TEXTURE0 + static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, 0);
        textureUnits_[i] = nullptr;
      }
    }
  }

  int32_t TextureManager::nextFreeTextureUnit() const
  {
    for (std::size_t i = 0; i < textureUnits_.size(); i++)
    {
      if (textureUnits_[i] == nullptr)
      {
        return static_cast<int32_t>(i);
      }
    }

    return -1;
  }

  uint32_t TextureManager::maxTextureUnits()
  {
    return maxTextureUnits_;
  }

  ShaPtr<Texture> TextureManager::texture(const std::string& name) const
  {
    TR_ASSERT(exists(name), "Texture " + name + " not found!")
    return textureLibrary_.at(name);
  }

  int32_t TextureManager::textureUnit(const std::string& name) const
  {
    int32_t texUnit = -1;
    for (std::size_t i = 0; i < textureUnits_.size(); i++)
    {
      if(textureUnits_[i] != nullptr)
      {
        if (textureUnits_[i]->name() == name)
        {
          texUnit = static_cast<int32_t>(i);
        }
      }
    }

    return texUnit;
  }

  bool TextureManager::exists(const std::string& name) const
  {
    return textureLibrary_.find(name) != textureLibrary_.end();
  }

  bool TextureManager::bound(const std::string& name) const
  {
    return std::any_of(textureUnits_.begin(), textureUnits_.end(), [&name](const ShaPtr<Texture> texture)
    {
      if(texture != nullptr)
      {
        return (texture->name() == name);
      }
      return false;
    });
  }
}