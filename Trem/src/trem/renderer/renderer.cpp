#include <trpch.h>
#include "renderer.h"

namespace Trem
{
  Renderer::Renderer() : rendererId_{0}, usedIndices_{0}, activeShader_{nullptr}
  {
    //initialize pointers to vertices
    vertexBufferBase_ = new QuadVertex[maxVertices_];
    vertexBufferIndex_ = vertexBufferBase_;
  }

  Renderer::~Renderer()
  {
    delete[] vertexBufferBase_;
  }

  void Renderer::init()
  {
    //createBuffers opengl components
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
        
    //createBuffers vao, vbo, ebo
    vertexArray_->createBuffers(maxVertices_, maxIndices_);
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

  void Renderer::loadVerticesToVertexBuffer(const std::array<QuadVertex, 4>& vertices, const glm::mat4& transform, const float textureUnit)
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
    loadVerticesToVertexBuffer(defaultVertices(color), transform, 0.f);

    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);

    if (vertexCount >= maxVertices_ || usedIndices_ >= maxIndices_)
    {
      flushBatch();
    }
  }
  
  //-----------------------
  //--- texture drawing ---
  //-----------------------

  void Renderer::drawQuad(const Quad& quad, const ShaPtr<Texture>& texture)
  {
    //bind texture
    int32_t texUnit = textureManager_.bindTexture(quad.texture_->name());
    //glm::mat4 transform = changeScale(quad.transform_, {texture->dimensions(), 1.f});
    loadVerticesToVertexBuffer(quad.vertices_, quad.transform_, static_cast<float>(texUnit));

    const uint32_t vertexCount = static_cast<uint32_t>(vertexBufferIndex_ - vertexBufferBase_);
    if (vertexCount >= maxVertices_ || usedIndices_ >= maxIndices_)
    {
      flushBatch();
    }
  }

  void Renderer::drawQuad(Quad& quad)
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



  //---------------------------------------------------------
  //--- Object data, definition of geometrical primitives ---
  //---------------------------------------------------------
  
  Quad::Quad()
  { 
    //define vertices with white color
    vertices_ = defaultVertices(glm::vec4{1.f});
  }

  Quad::Quad(const glm::vec4& color, const glm::mat4& transform) : transform_{transform}
  {
    vertices_ = defaultVertices(color);
  }

  Quad::Quad(const glm::vec4& color, const glm::vec3& position, const glm::vec3& scale, const glm::mat4& transform)
  {
    vertices_  = defaultVertices(color);
    position_  = position;
    scale_     = scale;
    transform_ = glm::translate(glm::mat4{1.f}, position_) * glm::scale(glm::mat4{1.f}, scale_);
  }

  Quad::Quad(const glm::vec4& color, ShaPtr<Texture> texture) : texture_{std::move(texture)}
  {
    vertices_  = defaultVertices(color);
    //use size of texture to scale the quad
    scale_     = {texture_->dimensions(), 1.f};
    transform_ = glm::scale(glm::mat4{1.f}, scale_);
  }

  Quad::Quad(const glm::vec4& color, const glm::vec3& position, ShaPtr<Texture> texture) : texture_{std::move(texture)}
  {
    vertices_  = defaultVertices(color); 
    scale_     = {texture_->dimensions(), 1.f};
    position_  = position;
    transform_ = glm::translate(glm::mat4{1.f}, position_) * glm::scale(glm::mat4{1.f}, scale_);
  }

  Quad::Quad(const glm::vec4& color, const glm::vec3& position, const glm::vec3& scale, ShaPtr<Texture> texture) : texture_{std::move(texture)}
  {
    vertices_  = defaultVertices(color); 
    scale_     = scale;
    position_  = position;
    transform_ = glm::translate(glm::mat4{1.f}, position_) * glm::scale(glm::mat4{1.f}, scale_);
  }

  void Quad::setPosition(const glm::vec3& position)
  {
    position_ = position;
    calculateTransform();
  }

  void Quad::setScale(const glm::vec3& scale)
  {
    scale_ = scale;
    calculateTransform();
  }

  void Quad::setRotation(const float rotation)
  {
    rotation_ = rotation;
    calculateTransform();
  }

  void Quad::setColor(const glm::vec4& color)
  {
    vertices_ = defaultVertices(color);
  }

  void Quad::calculateTransform()
  {
    transform_ = glm::translate(glm::mat4{1.f}, position_) * 
                 glm::rotate(glm::mat4{1.f}, rotation_, {0.f, 0.f, 1.f}) *
                 glm::scale(glm::mat4{1.f}, scale_);
  }

  std::array<QuadVertex, 4> defaultVertices(const glm::vec4& color)
  {
    std::array<QuadVertex, 4> vertices =
    {
      QuadVertex{glm::vec4{0.f, 0.f, 0.f, 1.0f}, color, glm::vec2{0.0f, 0.0f}}, //bottom left
      QuadVertex{glm::vec4{1.f, 0.f, 0.f, 1.0f}, color, glm::vec2{1.0f, 0.0f}}, // bottom right
      QuadVertex{glm::vec4{1.f, 1.f, 0.f, 1.0f}, color, glm::vec2{1.f, 1.f}},   //top right
      QuadVertex{glm::vec4{0.f, 1.f, 0.f, 1.0f}, color, glm::vec2{0.f, 1.f}}    // top left
    };

    return vertices;
  }

  glm::mat4 composeTransform(const TransformContainer& transformContainer)
  {
    glm::mat4 rotation    = transformContainer.rotation_;
    glm::mat4 translation = glm::translate(glm::mat4{1.f}, transformContainer.translation_);
    glm::mat4 scale       = glm::scale(glm::mat4{1.f}, transformContainer.scale_);
    glm::mat4 transform   = translation * rotation * scale;

    return transform;
  }

  TransformContainer decomposeTransform(const glm::mat4& transform)
  {
    TransformContainer transformContainer{};
    glm::quat orientation;
    glm::decompose(transform, transformContainer.scale_, orientation, transformContainer.translation_, transformContainer.skew_, transformContainer.perspective_);
    //convert quaternion to 4x4 matrix
    transformContainer.rotation_ = glm::toMat4(orientation);

    return transformContainer;
  }

  glm::mat4 changePosition(const glm::mat4& transform, const glm::vec3& position)
  {
    TransformContainer tContainer = decomposeTransform(transform);
    tContainer.translation_ = position;

    return composeTransform(tContainer);
  }

  glm::mat4 changeScale(const glm::mat4& transform, const glm::vec3& scale)
  {
    TransformContainer tContainer = decomposeTransform(transform);
    tContainer.scale_ = scale;

    return composeTransform(tContainer);
  }

  glm::mat4 changeRotation(const glm::mat4& transform, const float angle, const glm::vec3& axis)
  {
    TransformContainer tContainer = decomposeTransform(transform);
    tContainer.rotation_ = glm::rotate(glm::mat4{1.f}, angle, axis);

    return composeTransform(tContainer);
  }

}
