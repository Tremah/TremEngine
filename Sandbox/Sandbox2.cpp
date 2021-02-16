#include <trem.h>
#include <trem/core/entry.hpp>
#include "SandboxLayer.h"

class Sandbox : public Trem::Game
{
  public:
    Sandbox() : Game("Sandbox")
    {
      addLayer(new SandboxLayer{});
    }  

    Sandbox(const std::string& name) : Game(name)
    {
      addLayer(new SandboxLayer{});
    }
};

Trem::UnqPtr<Trem::Game> Trem::createGame()
{
  return Trem::CreateUnique<Sandbox>("Sandbox");
}