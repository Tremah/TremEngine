#include "SandboxLayer.h"

inline uint64_t lcg(const long long pSeed)
  {
    long long seed = pSeed;
    long long increment = 1013904223;
    long long multiplier = 1664525;
    long long modulo = 4294967296;

    seed = ((multiplier * seed) + increment) % modulo;
    return seed;
  }

void SandboxLayer::init(const Trem::TextureManager& textureManager)
{  
  std::size_t elementCount = 300;  
  gameObjects_.reserve(elementCount); 
  
  for(std::size_t i=0; i < elementCount; i++)
  {  
    Trem::Quad white{};
    white.setScale({10.f, 10.f, 1.f});
    gameObjects_.push_back(white);
  }
  Trem::Quad cowboy{glm::vec4{1.f}, glm::vec3{200.f, 300.f, 0.f}, textureManager.texture("cowboy_large")};
  gameObjects_.push_back(cowboy);
}

void SandboxLayer::update(Trem::DeltaSeconds timestep)
{
  std::mt19937::result_type seed = Trem::Timer::now().time_since_epoch().count();
  auto posRand = std::bind(std::uniform_real_distribution<float>(0,1600), std::mt19937(seed));
  auto colorRand = std::bind(std::uniform_real_distribution<float>(0,255), std::mt19937(seed));
  
  for(std::size_t i=0; i < gameObjects_.size() - 1; i++)
  { 
    float xPos = posRand();
    float yPos = posRand();
        
    float r = static_cast<float>(colorRand()) / 255.0f;
    float g = static_cast<float>(colorRand()) / 255.0f;
    float b = static_cast<float>(colorRand()) / 255.0f;
    
    gameObjects_.at(i).setColor({r, g, b, 1.f});
    gameObjects_.at(i).setPosition({xPos, yPos, 0.f});
  } 
}

void SandboxLayer::render(Trem::Renderer& renderer)
{
  for(auto object : gameObjects_)
  {
    if(object.texture_ == nullptr)
    {
      renderer.drawQuad(object);
    }
    else
    {      
      renderer.drawQuad(object, object.texture_);
    }
  }
}

