#include <trpch.h>
#include "shader.h"

namespace Trem
{
  Shader::Shader(const std::string& name, const std::string& filePath) : shaderId_{0}
  {
    auto shaderSources = separateShaders(Util::readFile(filePath));
    load(shaderSources);
    name_ = name;
  }

  void Shader::bind() const
  {
    glUseProgram(shaderId_);
  }

  void Shader::unbind()
  {
    glUseProgram(0);
  }

  std::string Shader::name() const
  {
    return name_;
  }

  void Shader::load(const std::unordered_map<GLenum, std::string>& shaderSources)
  {
    std::array<GLenum, 2> shaderIds{};
    std::size_t shaderIdCount = 0;    
    auto program = glCreateProgram();

    for (const auto& [type, source] : shaderSources)
    {
      //createBuffers and compile shader
      uint32_t shader = glCreateShader(type);
      const char* shaderCode = source.c_str();
      glShaderSource(shader, 1, &shaderCode, nullptr);
      glCompileShader(shader);
      GLint compiled = 0;
      //check shader compilation status
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled)
      {
        //if compile error, delete shader
        GLint maxLen;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);
        std::vector<GLchar> infoLog(maxLen);
				glGetShaderInfoLog(shader, maxLen, &maxLen, &infoLog[0]);
        glDeleteShader(shader);

        LOG(infoLog.data())
        TR_ASSERT(false, "Error compiling shader!" )
        return;
      }
      glAttachShader(program, shader);
      shaderIds[shaderIdCount++] = shader;
    }

    //link program
    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
      //if linking error reverse everything
      GLint maxLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);
			std::vector<GLchar> infoLog(maxLen);
			glGetProgramInfoLog(program, maxLen, &maxLen, &infoLog[0]);
      
      for(auto i : shaderIds)
      {
        glDeleteShader(i);
      }
      glDeleteProgram(program);

      LOG(infoLog.data())
      TR_ASSERT(false, "Error linking shader program!" )
      return;
    }

    //already linked shaders can be deleted
    for(auto i : shaderIds)
    {
       glDetachShader(program, i);
       glDeleteShader(i);
    }

    //save program id
    shaderId_ = program;
  }

  std::unordered_map<GLenum, std::string> Shader::separateShaders(const std::string& shaderSource)
  {
    std::string typeToken = "#type";
    std::size_t typeTokenLen = typeToken.length();    
    std::size_t offset = 0;
    std::size_t typePos = shaderSource.find(typeToken, offset);
    TR_ASSERT(typePos != std::string::npos, "Syntax error in shader file: No shaders defined!")

    std::unordered_map<GLenum, std::string> shaders;
    while (typePos != std::string::npos)
    {
      //find end of line for shader type statement
      std::size_t eol = shaderSource.find_first_of("\r\n", typePos);
      //determine shader type
      std::size_t nameStart = shaderSource.find_first_not_of(' ', typePos + typeTokenLen);
      std::size_t nameEnd = shaderSource.find_last_not_of(' ', eol -1);
      std::string shaderType = shaderSource.substr(nameStart, nameEnd - nameStart + 1);
      //find start of shader code
      std::size_t shaderStart = shaderSource.find_first_not_of("\r\n", eol); /*start position for shader source code*/
      TR_ASSERT(shaderStart != std::string::npos, "Syntax error in shader file: No shader code found!")
      //find start of the next shader
      std::size_t nextShaderPos = ((shaderSource.find(typeToken, shaderStart) != std::string::npos)
        ? shaderSource.find(typeToken, shaderStart) : shaderSource.length()) - 1;
      //find the end of the current shader code
      std::size_t shaderEnd = shaderSource.find_last_not_of("\r\n", nextShaderPos) - shaderStart + 1;

      shaders.insert({shaderTypeFromString(shaderType), shaderSource.substr(shaderStart, shaderEnd)});

      offset += shaderEnd;
      typePos = shaderSource.find(typeToken, offset);
    }

    return shaders;    
  }

  GLenum Shader::shaderTypeFromString(std::string& type)
  {
    if(type == "vertex")
      return GL_VERTEX_SHADER;  
    if(type == "fragment")
      return GL_FRAGMENT_SHADER; 

    TR_ASSERT(false, "Invalid shader type!")
    return 0;
  }

  int32_t Shader::getUniformLocation(const std::string& name) const
  {
    int32_t location = glGetUniformLocation(shaderId_, name.c_str());
    TR_ASSERT(location != -1, "Uniform " + name  + " could not be found!")
    return location;
  }

  void Shader::uploadUniformMat4(const std::string& name, const glm::mat4& value) const
  {
    int32_t location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
  }  

  void Shader::uploadUniformInt1(const std::string& name, const int value) const
  {    
    int32_t location = getUniformLocation(name);
    glUniform1i(location, value);
  }

  void Shader::uploadUniformIntArray(const std::string& name, const int32_t* values, const uint32_t count) const
  {
    int32_t location = getUniformLocation(name);
    glUniform1iv(location, count, values);
  }
}
