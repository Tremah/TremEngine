#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//custom (own) libary includes

//game engine includes
#include <trem/util/file.h>

/**
 *  \brief Class to represent a collection of shaders via a given name (engine related) or a shaderId (opengl related).<br>
 *         Shaders are supplied in a file, possibly containing several shaders (vertex, fragment, etc.).
 *
 */
namespace Trem
{
  class Shader
  {
  public:
    //Constructors and deconstructors 
    Shader() : shaderId_{0} {}

    /**
     * \brief Parameterized constructor to construct a shader from a file.<br>
     *        The name of the shader is set via input parameter name
     * @param name Name of the shader
     * @param filePath Path to the shader source file
     */
    Shader(const std::string& name, const std::string& filePath);

    //Member variables

    //Member functions
    /**
     * \brief Binds the shader.
     */
    void bind() const;
    /**
     * \brief Unbinds the shader.
     */
    static void unbind();
    /**
     * \brief Returns the name of the shader.
     * \return Name of the shader.
     */
    std::string name() const;

    /**
      \brief Uploads a 4x4 matrix to a uniform location.
      @param name Name of the uniform the data is transferred to.
      @param value 4x4 matrix to be uploaded to the gpu.
     */
    void uploadUniformMat4(const std::string& name, const glm::mat4& value) const;

    /**
     * \brief Uploads an integer value to a uniform location.
     * @param name Name of the uniform location.
     * @param value Value to be set.
     */
    void uploadUniformInt1(const std::string& name, int32_t value) const;

    /**
     * \brief Uploads an integer array to a uniform location
     * @param name   Name of the uniform location
     * @param values Pointer to the array
     * @param count  Element count in the array
     */
    void uploadUniformIntArray(const std::string& name, const int32_t* values, uint32_t count) const;

  protected:
    //Member variables

    //Member functions

  private:
    uint32_t shaderId_; /**< id for the shader*/
    std::string name_;
    //Member variables

    //Member functions
    /**
     * \brief Extract the different shaders from a string.
     * @param shaderSource Shader source.
     */
    static std::unordered_map<GLenum, std::string> separateShaders(const std::string& shaderSource);

    /**
     * \brief Create, compile, link and attach the shaders.
     * @param shaderSources Unordered map.
     */
    void load(const std::unordered_map<GLenum, std::string>& shaderSources);

    /**
     * \brief Returns the ShaderType for a given type string.
     * @param type Shader type as a string, read from the source file.
     * \return Shader type from enum ShaderType.
     */
    static GLenum shaderTypeFromString(std::string& type);

    /**
     * \brief Returns the location of a uniform.
     * @param name Name of the uniform location.
     * \return Location of the uniform.
     */
    int32_t getUniformLocation(const std::string& name) const;
  };


}
