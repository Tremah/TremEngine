#include <trpch.h>
#include "buffer_layout.h"

namespace Trem
{
  void BufferLayout::addBufferElement(const BufferElement& element)
  {    
    bufferElements_.push_back(element);

    //update layout information
    //elementCount = total count of elements in one vertex
    layoutStats_.elementCount_ += element.offset_;
    layoutStats_.stride_ += element.size_;
  }

  void BufferLayout::addBufferElement(const std::string& name, const BufferElementType type)
  {
    BufferElement element{name, type};
    addBufferElement(element);
  } 

  BufferElement BufferLayout::bufferElement(const std::string& name) const
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

    return BufferElement{"Empty", BufferElementType::Empty};
  }

  std::vector<BufferElement> BufferLayout::bufferElements() const
  {
    return bufferElements_;
  }

  bool BufferLayout::exists(const std::string& name) const
  {
    return std::any_of(bufferElements_.begin(), bufferElements_.end(), [&name](const BufferElement& element)
    {
      return (element.name_ == name);
    });
  }

  LayoutInfo BufferLayout::layoutStats() const
  {
    return layoutStats_;
  }

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
