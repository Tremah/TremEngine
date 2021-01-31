#pragma once

//c++ includes

//external library includes
#include <json/json.hpp>

//custom (own) library includes

//game engine includes
#include <trem/renderer/texture.h>
#include <trem/data/data.h>
#include <trem/util/file.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class TextureManager
  {
    public:
      TextureManager(): textureUnits_{nullptr} {}
      //param. constructors

      //public member variables

      //public member functions
      /**
       * \brief Load textures from the asset list
       * @param bind Bind the textures on load (default = false)
       */
      void loadFromAssetList(bool bind=false);   
      void remove(const std::string& name);
      ShaPtr<Texture> texture(const std::string& name) const;
      int32_t nextFreeTextureUnit() const;
      int32_t bindTexture(const std::string& name);
      void unbindTexture(const std::string& name);
      int32_t textureUnit(const std::string& name) const;
      static uint32_t maxTextureUnits();

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables    
      //TODO can/will be replaced by dynamic deduction from opengl parameter
      static constexpr uint8_t maxTextureUnits_ = 32; 
      std::unordered_map<std::string, ShaPtr<Texture>> textureLibrary_; /**< Texture storage, identified by texture name*/  

      //the array index represents the available texture units
      //if array[i] = nullptr, then there is no texture bound to the texture unit
      std::array<ShaPtr<Texture>, maxTextureUnits_> textureUnits_;
      static constexpr char assetList_[] = "assets/assets.json";

      //private member functions
      void add(const std::string& name, ShaPtr<Texture>&& texture);
      bool exists(const std::string& name) const;
      bool bound(const std::string& name) const;
      
  };
}
