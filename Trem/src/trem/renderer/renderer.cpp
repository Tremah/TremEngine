#include <trpch.h>
#include "renderer.h"

namespace Trem
{
  Renderer::Renderer() : rendererId_{0}, usedIndices_{0}, activeShader_{nullptr}
  {
    //initialize pointers to vertices
    vertexBufferBase_ = new Data::QuadVertex[maxVertices_];
    vertexBufferIndex_ = vertexBufferBase_;
  }

  Renderer::~Renderer()
  {
    delete[] vertexBufferBase_;
  }

  void Renderer::init()
  {
    //create opengl components
    vertexArray_ = CreateShared<VertexArray>();

    //load shaders
    shaderLibrary_.loadFromAssetList();

    //load textures
    textureManager_.loadFromAssetList(false);

    //upload texture unit indices to sampler2d array in the shader
    setActiveShader("Texture");
    const int32_t maxTextureUnits = static_cast<int32_t>(TextureManager::maxTextureUnits());
    std::vector<int32_t> samplers;
    samplers.reserve(maxTextureUnits);
    for(int32_t i=0; i < maxTextureUnits; i++)
    {
      samplers.push_back(i);
    }
    activeShader_->uploadUniformIntArray("uTextures", samplers.data(), maxTextureUnits);
        
    //create vao, vbo, ebo
    vertexArray_->create(maxVertices_, maxIndices_);
    //set ebo
    setIndices();
  }  

  void Renderer::setIndices()
  {
    //construct index buffer
    std::array<uint32_t, maxIndices_> indices{0};    
    uint32_t quadIndexCount = 6;
    uint32_t quadVertexCount = 4;
    uint32_t offset = 0;
    
    for (uint32_t i = 0; i < maxIndices_; i += quadIndexCount)
    {
      indices[i]   = offset + 0;
      indices[i + 1] = offset + 1;
      indices[i + 2] = offset + 2;
      indices[i + 3] = offset + 2;
      indices[i + 4] = offset + 3;
      indices[i + 5] = offset + 0;
      offset += quadVertexCount;
    }

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, maxIndices_ * sizeof(GLuint), &(indices.front()));
  }

  void Renderer::loadVerticesToVertexBuffer(const std::array<Data::QuadVertex, 4>& vertices, const glm::mat4& transform, const float textureUnit)
  {
    for (const auto& vertex : vertices)
    {
      vertexBufferIndex_->position_ = transform * vertex.position_;
      vertexBufferIndex_->color_ = vertex.color_;
      vertexBufferIndex_->texCoordinates_ = vertex.texCoordinates_;
      vertexBufferIndex_->texUnit_ = textureUnit;
      vertexBufferIndex_++;
    }
    usedIndices_ += 6;
  }

  void Renderer::setActiveShader(const std::string& name)
  {
    activeShader_ = shaderLibrary_.shader(name);
    activeShader_->bind();
  }

  ShaPtr<Shader> Renderer::activeShader() const
  {
    return activeShader_;
  }

  TextureManager& Renderer::textureManager() const
  {
    return const_cast<TextureManager&>(textureManager_);
  }

  void Renderer::drawIndexed(const uint32_t indexCount)
  {
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
  }

  //-------------------------
  //--- primitive drawing ---
  //-------------------------

  //proxy function for primitive drawing without texture
  void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
  {
    drawQuad(glm::vec3{position, 0.f}, glm::vec3{scale, 1.f}, color);
  }

  //proxy function for primitive drawing without texture
  void Renderer::drawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
  {
    glm::mat4 transform = glm::translate(glm::mat4{1.f}, position) * glm::scale(glm::mat4{1.f}, scale);
    drawQuad(transform, color);
  }

  //primitive drawing without texture
  void Renderer::drawQuad(const glm::mat4& transform, const glm::vec4& color)
  {
    //add quad vertices to intermediate storage 
    loadVerticesToVertexBuffer(Data::defaultVertices(color), transform, 0.f);

    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);

    if (vertexCount >= maxVertices_ || usedIndices_ >= maxIndices_)
    {
      flushBatch();
    }
  }
  
  //-----------------------
  //--- texture drawing ---
  //-----------------------

  void Renderer::drawQuad(const Data::Quad& quad, const ShaPtr<Texture>& texture)
  {
    //bind texture
    int32_t texUnit = textureManager_.bindTexture(quad.texture_->name());
    //glm::mat4 transform = Data::changeScale(quad.transform_, {texture->dimensions(), 1.f});
    loadVerticesToVertexBuffer(quad.vertices_, quad.transform_, static_cast<float>(texUnit));

    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);
    if (vertexCount >= maxVertices_ || usedIndices_ >= maxIndices_)
    {
      flushBatch();
    }
  }

  void Renderer::drawQuad(Data::Quad& quad)
  {
    //add quad vertices to intermediate storage 
    int32_t texUnit = 0;
    if(quad.texture_ != nullptr)
    {
      texUnit = textureManager_.bindTexture(quad.texture_->name());
    }
    loadVerticesToVertexBuffer(quad.vertices_, quad.transform_, static_cast<float>(texUnit));

    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);
    if (vertexCount >= maxVertices_ || usedIndices_ >= maxIndices_)
    {
      flushBatch();
    }
  }  

  void Renderer::flushBatch()
  {
    //upload vertex buffer data to the gpu
    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);
    const uint32_t vertexElementCount = vertexCount * vertexArray_->bufferLayout()->layoutStats().elementCount_;
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexElementCount * sizeof(GLfloat), vertexBufferBase_);

    //draw vertices by their indices
    drawIndexed(usedIndices_);

    //reset physical vertex storage and render variables
    vertexBufferIndex_ = vertexBufferBase_;
    usedIndices_ = 0;
  }
    
  void Renderer::clear(GLenum bits)
  {
    glClear(bits);
  }

  void Renderer::setClearColor(const glm::vec4& color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void Renderer::beginScene()
  {
    setClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    clear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::endScene()
  {
    flushBatch();
  }
}
