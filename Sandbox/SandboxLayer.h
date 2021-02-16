#pragma once

//c++ includes
#include <random>

//external library includes

//custom (own) library includes

//game engine includes
#include <trem.h>
#include <trem/core/service_locator.h>

/**
 *  \brief Brief Description
 *
 */
class SandboxLayer : public Trem::Layer
{
  public:
    SandboxLayer() : Layer("SandboxLayer") {}
    //param. constructors

    //public member variables

    //public member functions
    void init(const Trem::TextureManager& textureManager)  override;
    void update(Trem::DeltaSeconds timestep) override;
    void render(Trem::Renderer& renderer) override;

  protected:
    //protected member variables

    //protected member functions

  private:
    //private member variables

    //private member functions
      
};
