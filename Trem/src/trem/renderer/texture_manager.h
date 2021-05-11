#pragma once

//c++ includes

//external library includes
#include <json/json.hpp>

//custom (own) library includes

//game engine includes
#include <trem/renderer/texture.h>
#include <trem/util/file.h>

/**
 *  \brief Class to manage textures and their binding to OpenGL texture units.
 *         Stores textures in a library.
 *         Manages an array which tracks the binding of textures to texture units.
 */
namespace Trem
{
  class TextureManager
  {
    public:
      //Constructors and deconstructors 
      TextureManager(): textureUnits_{nullptr} {}

      //Member variables

      //Member functions
      /**
       * \brief Load textures from the asset list
       * @param bind Bind the textures on load (default = false)
       */
      void loadFromAssetList();   

      /**
       * \brief Removes a texture.
       * @param name Name of the texture to be removed.
       */
      void remove(const std::string& name);

      /**
       * \brief Returns a texture by its name.
       * @param name Name of the texture to be returned.
       * \return Requested texture.
       */
      ShaPtr<Texture> texture(const std::string& name) const;

      /**
       * \brief Returns the next free texture unit.
       * \return Next free texture unit.
       */
      int32_t nextFreeTextureUnit() const;

      /**
       * \brief Binds a texture for usage.
       * @param name Texture to be bound.
       * \return Unit the texture was bound to.
       */
      int32_t bindTexture(const std::string& name);

      /**
       * \brief Unbinds a texture.
       * @param name Texture to be unbound.
       */
      void unbindTexture(const std::string& name);

      /**
       * \brief Returns the unit the texture is bound to.
       * @param name Texture name.
       * \return Texture unit the given texture is bound to. -1 if the texture is not bound.
       */
      int32_t textureUnit(const std::string& name) const;

      /**
       * \brief Returns the maximum number of texture units.
       * \return Maximum number of texture units.
       */
      static uint32_t maxTextureUnits();

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables    
      static constexpr uint8_t maxTextureUnits_ = 32; 
      std::unordered_map<std::string, ShaPtr<Texture>> textureLibrary_; /**< Texture storage, identified by texture name*/  

      //the array index represents the available texture units
      //if array[i] = nullptr, then there is no texture bound to the texture unit
      std::array<ShaPtr<Texture>, maxTextureUnits_> textureUnits_;
      static constexpr char assetList_[] = "assets/assets.json";

      //Member functions
      /**
       * \brief Adds a texture to the texture library, taking ownership of it.
       * @param name Name of the texture to be added.
       * @param texture Shared pointer to a texture.
       */
      void add(const std::string& name, ShaPtr<Texture>&& texture);

      /**
       * \brief Checks if a texture exists already.
       * @param name Name of the texture.
       * \return True if the texture exists, false if not.
       */
      bool exists(const std::string& name) const;

      /**
       * \brief Checks if a texture is currently bound to a texture unit.
       * @param name Name of the texture.
       * \return True if the texture is bound, false if not.
       */
      bool bound(const std::string& name) const;
      
  };
}
