#include "trpch.h"
#include "layer.h"

namespace Trem
{
  void Layer::init(const TextureManager& textureManager)
  {
    std::cout << "base layer init" << std::endl;
  }

  //For debug only
  void Layer::update(DeltaSeconds timestep)
  {
    std::cout << "base layer update" << std::endl;
  }

  void Layer::render(Renderer& renderer)
  {
    std::cout << "base layer render" << std::endl;
  }
}
