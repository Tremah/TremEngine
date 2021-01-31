#pragma once

//c++ includes

//external library includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

//custom (own) library includes

//game engine includes
#include <trem/renderer/texture_manager.h>

/**
 *  \brief Data definitions for different parts of Trem-Engine.
 *         Provides lookup functionality for some of the data types.
 */

namespace Trem::Data
{  
  //---------------------------------------------------------
  //--- Object data, definition of geometrical primitives ---
  //---------------------------------------------------------
    
  /**
   *  \brief Struct to hold information about a vertex of a quad.
   */
  struct QuadVertex
  {
    QuadVertex() : position_{}, color_{}, texCoordinates_{}, texUnit_{0.f} {}
    QuadVertex(glm::vec4 position, glm::vec4 color, glm::vec2 textureCoordinates) : position_{position}, color_{color}, texCoordinates_{textureCoordinates}, texUnit_{0.f}  {}

    glm::vec4 position_;
    glm::vec4 color_;
    glm::vec2 texCoordinates_;
    float     texUnit_;
  };

  /**
   *  \brief Struct to hold information about a quad.
   */
  struct Quad
  {
    Quad();
    Quad(const glm::vec4& color, const glm::mat4& transform);
    Quad(const glm::vec4& color, const glm::vec3& position, const glm::vec3& scale, const glm::mat4& transform);
    Quad(const glm::vec4& color, ShaPtr<Texture> texture);
    Quad(const glm::vec4& color, const glm::vec3& position, ShaPtr<Texture> texture);
    Quad(const glm::vec4& color, const glm::vec3& position, const glm::vec3& scale, ShaPtr<Texture> texture);

    void setPosition(const glm::vec3& position);
    void setScale(const glm::vec3& scale);
    void setRotation(float rotation);
    void setColor(const glm::vec4& color);
    void calculateTransform();
    
    std::array<QuadVertex, 4> vertices_;
    glm::vec3 position_{0.f};
    glm::vec3 scale_{1.f};
    float     rotation_ = 0.f;
    glm::mat4 transform_{1.f};

    ShaPtr<Texture> texture_{nullptr};
  };

  /**
   * \brief Struct to hold the different parts of a model matrix.<br>
   *        Serves only as a return type and temporary data storage.
   */
  struct TransformContainer
  {
    TransformContainer() : scale_{1.f}, rotation_{1.f}, translation_{1.f}, skew_{1.f}, perspective_{1.f}{}
    glm::vec3 scale_;
    glm::mat4 rotation_;
    glm::vec3 translation_;
    glm::vec3 skew_;
    glm::vec4 perspective_;    
  };

  //functions to compose/change a transform
  std::array<QuadVertex, 4> defaultVertices(const glm::vec4& color);
  glm::mat4 composeTransform(const TransformContainer& transformContainer);
  TransformContainer decomposeTransform(const glm::mat4& transform);

  glm::mat4 changePosition(const glm::mat4& transform, const glm::vec3& position);
  glm::mat4 changeScale(const glm::mat4& transform, const glm::vec3& scale);
  glm::mat4 changeRotation(const glm::mat4& transform, float angle, const glm::vec3& axis);
  
  //----------------------------
  //--- Vertex buffer layout ---
  //----------------------------
  
  /**
   *  \brief Scoped enumeration for data types.
   */
  enum class BufferElementType
  {
    Empty = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
  };

  /**
   *  \brief Struct to hold data for a buffer element.
   */
  struct BufferElement
  {
    BufferElement(const std::string& name, const BufferElementType type, const uint32_t offset, const uint32_t size)
      : name_{name}, type_{type}, offset_{offset}, size_{size} {};
    BufferElement(const std::string& name, BufferElementType type);
    BufferElement() : name_{}, type_{0}, offset_{0}, size_{0} {}

    std::string name_;
    BufferElementType type_;
    uint32_t offset_;
    uint32_t size_; /**< size in bytes*/
  };

  /**
   *  \brief Struct to hold information about the entire layout.
   */
  struct LayoutInfo
  {
    LayoutInfo() : stride_{0}, elementCount_{0} {};
    uint32_t stride_; /**< total stride of the layout*/
    uint32_t elementCount_; /**< number of elements in the layout*/
  };  

  /**
    \brief Returns the Size of a buffer element.
    @param type type of the buffer element.
   */
  static constexpr uint32_t bufferElementTypeSize(Data::BufferElementType type);
    
}