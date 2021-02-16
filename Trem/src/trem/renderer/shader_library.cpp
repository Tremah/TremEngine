#include <trpch.h>
#include "shader_library.h"

namespace Trem
{
  void ShaderLibrary::loadFromAssetList()
  {
    const std::string fileContent = Util::readFile(assetList_);
    using json = nlohmann::json;

    json shaderList = json::parse(fileContent).at("shaders");
    TR_ASSERT(!shaderList.empty(), "Asset list does not contain any shaders!")
    for(auto shaderAsset : shaderList)
    {
      add(CreateShared<Shader>(shaderAsset.at("name"), shaderAsset.at("filepath")));
    }    
  }

  void ShaderLibrary::add(ShaPtr<Shader>&& shader)
  {
    const auto& name = shader->name();
    TR_ASSERT(!exists(name), "Shader " + name + " already defined!")
    shaderLibrary_[name] = std::move(shader);
  }

  void ShaderLibrary::remove(const std::string& name)
  {
    TR_ASSERT(exists(name), "Shader " + name + " not found!")
    shaderLibrary_.erase(name);
  }

  bool ShaderLibrary::exists(const std::string& name) const
  {
    return shaderLibrary_.find(name) != shaderLibrary_.end();
  }

  ShaPtr<Shader> ShaderLibrary::shader(const std::string& name) const
  {
    TR_ASSERT(exists(name), "Shader " + name + " not found!")
    return shaderLibrary_.at(name);
  }
}
  
