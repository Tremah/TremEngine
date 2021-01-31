#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

//game engine includes
#include <trem/data/data.h>
#include <trem/renderer/vertex_array.h>
#include <trem/renderer/texture_manager.h>
#include <trem/renderer/shader_library.h>

/**
 *  \brief Implementation of a 2D renderer for OpenGL.
 */
namespace Trem
{
  class Renderer
  {
    public:
      Renderer(const Renderer&) = default;
      Renderer(Renderer&&) = default;
      Renderer& operator=(const Renderer&) = default;
      Renderer& operator=(Renderer&&) = default;
            
      Renderer();
      ~Renderer();
      //param. constructors

      //public member variables

      //public member functions

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
      void drawQuad(const Data::Quad& quad, const ShaPtr<Texture>& texture);

      /**
       * \brief Draw a quad with default texture.
       * @param quad Quad to be drawn.
       */
      void drawQuad(Data::Quad& quad);

      void beginScene();

      /**
       * \brief Performs actions to end a scene (render loop)
       */
      void endScene();

    protected:
      //protected member variables

      //protected member functions

    private:
      unsigned int rendererId_; /**< unique id for the renderer*/

      //data members
      static constexpr uint32_t maxQuads_    = 20000;
      static constexpr uint32_t maxVertices_ = maxQuads_ * 4; /**< each quad has 4 vertices*/
      static constexpr uint32_t maxIndices_  = maxQuads_ * 6; /**< each quad needs 6 indices to be drawn*/

      uint32_t usedIndices_; /**< Number of indices in use by the current batch*/
     
      //buffer storage
      Data::QuadVertex* vertexBufferBase_; /**< physical storage for vertices */
      Data::QuadVertex* vertexBufferIndex_;
   
      //render components
      ShaPtr<VertexArray> vertexArray_;
      ShaPtr<Shader>      activeShader_;
      ShaderLibrary       shaderLibrary_;
      TextureManager      textureManager_;

      //private member functions
      //batch rendering
      /**
       * \brief Finishes as a batch and issues a draw call to draw the scene.
       */
      void flushBatch();

      /**
       * \brief Creates the vertex indices for indexed drawing.
       */
      void setIndices();

      void loadVerticesToVertexBuffer(const std::array<Data::QuadVertex, 4>& vertices, const glm::mat4& transform, float textureUnit);
  };

}
