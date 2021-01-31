#include <trpch.h>
#include "data.h"

namespace Trem::Data
{
  //Quad
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

  //Vertex buffer layout
  BufferElement::BufferElement(const std::string& name, const BufferElementType type)
  {
    name_ = name;
    type_ = type;
    size_ = bufferElementTypeSize(type_);

    //calculate the elements offset
    switch (type_)
    {
    case BufferElementType::Bool:
    case BufferElementType::Float:
    case BufferElementType::Int:
      offset_ = 1;
      break;
    case BufferElementType::Float2:
    case BufferElementType::Int2:
      offset_ = 2;
      break;
    case BufferElementType::Float3:
    case BufferElementType::Int3:
      offset_ = 3;
      break;
    case BufferElementType::Float4:
    case BufferElementType::Int4:
      offset_ = 4;
      break;
    case BufferElementType::Mat3:
      offset_ = 9; //3 * 3
      break;
    case BufferElementType::Mat4:
      offset_ = 4 * 4; //4 * 4
      break;
    default:
      TR_ASSERT(type != BufferElementType::Empty, "Invalid buffer element type provided!")
      break;
    }
  }

  constexpr uint32_t bufferElementTypeSize(BufferElementType type)
  {
    switch (type)
    {
    case BufferElementType::Bool:   return 1;
    case BufferElementType::Float:  return 4;
    case BufferElementType::Float2: return 4 * 2;
    case BufferElementType::Float3: return 4 * 3;
    case BufferElementType::Float4: return 4 * 4;
    case BufferElementType::Int:    return 4;
    case BufferElementType::Int2:   return 4 * 2;
    case BufferElementType::Int3:   return 4 * 3;
    case BufferElementType::Int4:   return 4 * 4;
    case BufferElementType::Mat3:   return 4 * 3 * 3;
    case BufferElementType::Mat4:   return 4 * 4 * 4;
    default:
      TR_ASSERT(type != BufferElementType::Empty, "No buffer element type provided")
      break;
    }

    return 0;
  }
}

