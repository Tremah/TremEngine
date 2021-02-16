#pragma once

//c++ includes

//external library includes
#include <json/json.hpp>

//custom (own) library includes

//game engine includes
#include <trem/renderer/shader.h>
#include <trem/util/file.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class ShaderLibrary
  {
    public:
      //Constructors and deconstructors 
      //Member variables

      //Member functions
      /**
       * \brief Loads shader assets from an asset list into the library.<br>
       *        The asset list provides names and file paths for different shader assets.<br>
       *        Each shader asset can contain several glsl shaders (vertex, fragment, etc).<br>
       */
      void loadFromAssetList();

      /**
       * \brief Removes a shader from the library.
       * @param name Name of the shader
       */
      void remove(const std::string &name);

      /**
       * \brief Returns a shader from the shader library.
       * @param name Name of the shader
       */      
      ShaPtr<Shader> shader(const std::string& name) const;

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      std::unordered_map<std::string, ShaPtr<Shader>> shaderLibrary_; 
      static constexpr char assetList_[] = "assets/assets.json";

      //Member functions
      /**
       * \brief Adds a shader to the shader library.
       * @param shader Shader to be added
       */
      void add(ShaPtr<Shader>&& shader);

      /**
       * \brief Checks if a shader already exists.
       * @param name Name of the shader
       */
      bool exists(const std::string& name) const;
  };
}
  
