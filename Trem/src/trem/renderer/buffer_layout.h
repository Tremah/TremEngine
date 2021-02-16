#pragma once

//c++ includes

//external (custom) library includes

//game engine includes

namespace Trem
{
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
   * \brief Returns the Size of a buffer element.
   * @param type Type of the buffer element.
   * \return Size of the buffer element
   */
  static constexpr uint32_t bufferElementTypeSize(BufferElementType type);

  /**
   *  \brief Class to define the layout of an opengl buffer. Includes a struct to define a buffer element.
   *
   */
  class BufferLayout
  {
  public:
    //Constructors and deconstructors
    //Member variables
    
    //Member functions
    /**
      \brief Adds an element to the buffer layout
      @param element Element to be added
    */
    void addBufferElement(const BufferElement& element);

    /**
      \brief Constructs a buffer element and adds it to bufferElements_
      @param name Name of the new buffer element
      @param type Buffer element type of the new buffer element
     */
    void addBufferElement(const std::string& name, BufferElementType type);

    /**
      \brief Returns a buffer element
      @param name Name of the requested buffer element
     */
    BufferElement bufferElement(const std::string& name) const;

    /**
      \brief Returns all buffer elements
     */
    std::vector<BufferElement> bufferElements() const;

    /**
      \brief Returns a LayoutInfo struct, containing information about the layout
    */
    LayoutInfo layoutStats() const;

  protected:
    //Member variables

    //Member functions

  private:
    //Member variables
    std::vector<BufferElement> bufferElements_; /**< Unordered map which holds the buffer elements for the buffer layout*/

    //struct containing statistics about the current info
    LayoutInfo layoutStats_;

    bool exists(const std::string& name) const;


    //Member functions
  };
}
