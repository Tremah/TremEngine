#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/renderer/renderer.h>
#include <trem/util/timer.h>


/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class Layer
  {
    public:  
      //Constructors and deconstructors 
      Layer(const Layer&) = default;
      Layer(Layer&&) = default;
      Layer& operator=(const Layer&) = default;
      Layer& operator=(Layer&&) = default;
      virtual ~Layer(){}

      Layer() : enabled_{true} {}
      Layer(const std::string& name) : name_{name}, enabled_{true} {}

      //Member variables

      //Member functions
      virtual void init(const TextureManager& textureManager);
      virtual void update(DeltaSeconds timestep);
      virtual void render(Renderer& renderer);

    protected:
      //Member variables
      std::string name_;
      bool enabled_;

      std::vector<Quad> gameObjects_; /** physical storage for game objects*/

      //Member functions

    private:
      //Member variables

      //Member functions
      
  };
}
