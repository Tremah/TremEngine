#include <trpch.h>
#include "buffer_layout.h"

namespace Trem
{
  void BufferLayout::addBufferElement(const Data::BufferElement& element)
  {    
    bufferElements_.push_back(element);

    //update layout information
    //elementCount = total count of elements in one vertex
    layoutStats_.elementCount_ += element.offset_;
    layoutStats_.stride_ += element.size_;
  }

  void BufferLayout::addBufferElement(const std::string& name, const Data::BufferElementType type)
  {
    Data::BufferElement element{name, type};
    addBufferElement(element);
  } 

  Data::BufferElement BufferLayout::bufferElement(const std::string& name) const
  {
    TR_ASSERT(exists(name), "Buffer element could not be found!")
    TR_ASSERT(bufferElements_.empty() != 0, "Bufferlayout does not contain any elements!")

    for (auto element : bufferElements_)
    {
      if(element.name_ == name)
      {
        return element;
      }
    }

    return Data::BufferElement{"Empty", Data::BufferElementType::Empty};
  }

  std::vector<Data::BufferElement> BufferLayout::bufferElements() const
  {
    return bufferElements_;
  }

  bool BufferLayout::exists(const std::string& name) const
  {
    return std::any_of(bufferElements_.begin(), bufferElements_.end(), [&name](const Data::BufferElement& element)
    {
      return (element.name_ == name);
    });
  }

  Data::LayoutInfo BufferLayout::layoutStats() const
  {
    return layoutStats_;
  }
}
