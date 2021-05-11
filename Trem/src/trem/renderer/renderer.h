#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

//game engine includes
#include <trem/renderer/vertex_array.h>
#include <trem/renderer/texture_manager.h>
#include <trem/renderer/shader_library.h>

namespace Trem
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

  /**
   *  \brief Implementation of a 2D renderer for OpenGL.
   */
  class Renderer
  {
    public:
      //Constructors and deconstructors 
      Renderer(const Renderer&) = default;
      Renderer(Renderer&&) = default;
      Renderer& operator=(const Renderer&) = default;
      Renderer& operator=(Renderer&&) = default;
      ~Renderer();
            
      Renderer();

      //Member variables

      //Member functions

      /**
       * \brief Initializes the renderer. Creates vertex array and buffer layout for the vertex buffer.
       */
      void init();

      /**
       * \brief Clears bits from the current opengl context.
       * @param bits Bits to be cleared.
       */
      void clear(GLenum bits);

      /**
       * \brief Sets the background color for the current window.
       * @param color Background color to be set.
       */
      void setClearColor(const glm::vec4& color);

      /**
       * \brief Sets a shader for rendering.
       * @param name Name of the shader.
       */
      void setActiveShader(const std::string& name);

      /**
       * \brief Returns the active shader.
       * \return Active shader.
       */
      ShaPtr<Shader> activeShader() const;

      //temporary
      TextureManager& textureManager() const;

      /**
       * \brief Draw indexed data.<br>Writes the current vertex buffer to the gpu.
       */
      static void drawIndexed(uint32_t indexCount);

      /**
       * \brief Proxy drawing function to draw a quad via transform and color.
       * @param position Position of the quad.
       * @param scale Scale of the quad.
       * @param color Color of the quad.
       */
      void drawQuad(const glm::vec2& position,  const glm::vec2& scale, const glm::vec4& color);

      /**
       * \brief Proxy drawing function to draw a quad via transform and color.
       * @param position Position of the quad.
       * @param scale Scale of the quad.
       * @param color Color of the quad.
       */
      void drawQuad(const glm::vec3& position,  const glm::vec3& scale, const glm::vec4& color);

      /**
       * \brief Draw a quad via a transform and a color.
       * @param transform Transform of the quad.
       * @param color Color of the quad.
       */
      void drawQuad(const glm::mat4& transform, const glm::vec4& color);

      /**
       * \brief Adds data for a quad to the vertex buffer.<br>
       *        The quads transform is used for rendering.
       * @param quad Quad to be drawn.
       * @param texture Name of the texture to be used for rendering.
       */
      void drawQuad(const Quad& quad, const ShaPtr<Texture>& texture);

      /**
       * \brief Draw a quad with default texture.
       * @param quad Quad to be drawn.
       */
      void drawQuad(Quad& quad);

      void beginScene();

      /**
       * \brief Performs actions to end a scene (render loop)
       */
      void endScene();

    protected:
      //Member variables
      //Member functions

    private:
      unsigned int rendererId_; /**< unique id for the renderer*/

      //data members
      static constexpr uint32_t maxQuads_    = 20000;
      static constexpr uint32_t maxVertices_ = maxQuads_ * 4; /**< each quad has 4 vertices*/
      static constexpr uint32_t maxIndices_  = maxQuads_ * 6; /**< each quad needs 6 indices to be drawn*/

      uint32_t usedIndices_; /**< Number of indices in use by the current batch*/
     
      //buffer storage
      QuadVertex* vertexBufferBase_; /**< physical storage for vertices */
      QuadVertex* vertexBufferIndex_;
   
      //render components
      ShaPtr<VertexArray> vertexArray_;
      ShaPtr<Shader>      activeShader_;
      ShaderLibrary       shaderLibrary_;
      TextureManager      textureManager_;

      //Member functions
      //batch rendering

      /**
       * \brief Finishes as a batch and issues a draw call to draw the scene.
       */
      void flushBatch();

      /**
       * \brief Creates the vertex indices for indexed drawing.
       */
      void setIndices();

      /**
       * \brief Loads a set of vertices to the intermediate vertex buffer.
       * @param vertices Array of quad vertices.
       * @param transform Transform which is to be applied to the vertices.
       * @param textureUnit Texture unit of the texture which is to be used for the quad.
       */
      void loadVerticesToVertexBuffer(const std::array<QuadVertex, 4>& vertices, const glm::mat4& transform, float textureUnit);
  };

}
