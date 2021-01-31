#pragma once

//c++ includes

//external (custom) library includes

//game engine includes
#include <trem/data/data.h>

/**
 *  \brief Class to define the layout of an opengl buffer. Includes a struct to define a buffer element.
 *
 */
namespace Trem
{
  class BufferLayout
  {
  public:
    //param. constructors

    //public member variables

    //public member functions
    /**
      \brief Adds an element to the buffer layout
      @param element Element to be added
    */
    void addBufferElement(const Data::BufferElement& element);

    /**
      \brief Constructs a buffer element and adds it to bufferElements_
      @param name Name of the new buffer element
      @param type Buffer element type of the new buffer element
     */
    void addBufferElement(const std::string& name, Data::BufferElementType type);

    /**
      \brief Returns a buffer element
      @param name Name of the requested buffer element
     */
    Data::BufferElement bufferElement(const std::string& name) const;

    /**
      \brief Returns all buffer elements
     */
    std::vector<Data::BufferElement> bufferElements() const;

    /**
      \brief Returns a LayoutInfo struct, containing information about the layout
    */
    Data::LayoutInfo layoutStats() const;

  protected:
    //protected member variables

    //protected member functions

  private:
    //private member variables
    std::vector<Data::BufferElement> bufferElements_; /**< Unordered map which holds the buffer elements for the buffer layout*/

    //struct containing statistics about the current info
    Data::LayoutInfo layoutStats_;

    bool exists(const std::string& name) const;


    //private member functions
  };
}
