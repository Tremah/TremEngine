#include "trpch.h"
#include "camera.h"

namespace Trem
{
  Camera::Camera(float left, float right, float bottom, float top)
  {
    //createBuffers the cameras transform (view matrix) and the projection matrix for the entire scene
    //and combine them into the view-projection matrix     
    viewMatrix_           = glm::translate(glm::mat4{1.f}, position_) * glm::rotate(glm::mat4{1.f}, rotationAngle_, {0.f, 0.f, 1.f});
    projectionMatrix_     = glm::ortho(left, right, bottom, top, 1.f, -1.f);
    viewProjectionMatrix_ = projectionMatrix_ * glm::inverse(viewMatrix_);
  }

  bool Camera::move(KeyEvent* ev)
  {
    glm::vec3 distance{0.f};
    bool moved = false;
    switch (ev->keycode())
    {
      case Key::W:
        distance.y =  movementSpeed_;
        moved = true;
        break;
      case Key::S:
        distance.y = -movementSpeed_;
        moved = true;
        break;
      case Key::A:
        distance.x = -movementSpeed_;
        moved = true;
        break;
      case Key::D:
        distance.x =  movementSpeed_;
        moved = true;
        break;
      default:
        moved = false;
    }
    setPosition(position_ + distance);    

    if(moved)
    {
      ServiceLocator::logger().debug("camera moved to x:{0}, y:{1}", position_.x, position_.y);
    }

    return moved;
  }

  //setters
  void Camera::setProjectionMatrix(const glm::mat4& projectionMatrix)
  {
    projectionMatrix_ = projectionMatrix;
    calculateViewProjectionMatrix();
  }

  void Camera::setViewMatrix(const glm::mat4& viewMatrix)
  {
    viewMatrix_ = viewMatrix;
    calculateViewProjectionMatrix();
  }

  void Camera::setMsgCallback(const MsgQueueCallback& callback)
  {
    msgCallback_ = callback;
  }

  void Camera::setPosition(const glm::vec3& position)
  {
    position_ = position;
    calculateViewProjectionMatrix();
  }

  void Camera::setRotation(const float rotationAngle)
  {
    rotationAngle_ = rotationAngle;
    calculateViewProjectionMatrix();
  }

  void Camera::calculateProjectionMatrix(float left, float right, float bottom, float top)
  {   
    projectionMatrix_ = glm::ortho(left, right, bottom, top, 1.f, -1.f);
    calculateViewProjectionMatrix();
  }

  void Camera::calculateViewProjectionMatrix()
  {
    viewMatrix_ = glm::translate(glm::mat4{1.f}, position_) * glm::rotate(glm::mat4{1.f}, rotationAngle_, {0.f, 0.f, 1.f});
    //needs to be inverse because the position of each object multiplied with the matrix
    //needs to be moved to the opposite direction of the cameras movement
    viewProjectionMatrix_ = projectionMatrix_ * glm::inverse(viewMatrix_);
  }

  //getters
  glm::vec3 Camera::position() const
  {
    return position_;
  }

  glm::mat4 Camera::viewMatrix() const
  {
    return viewMatrix_;
  }

  glm::mat4 Camera::projectionMatrix() const
  {
    return projectionMatrix_;
  }

  glm::mat4 Camera::viewProjectionMatrix() const
  {
    return viewProjectionMatrix_;
  }

  bool Camera::handleMessage(const UnqPtr<Message>& msg)
  {
    if(msg->inCategory(MsgCategories::KeyboardEvent))
    {
      KeyEvent* keyEvent = static_cast<KeyEvent*>(msg.get());
      return move(keyEvent);
    }

    if(msg->type() == MsgTypes::WindowResized)
    {
      WindowResizedEvent* windowResizedEvent = static_cast<WindowResizedEvent*>(msg.get());
      float right = static_cast<float>(windowResizedEvent->windowSize_.x);
      float top = static_cast<float>(windowResizedEvent->windowSize_.y);
      calculateProjectionMatrix(0.f, right, 0.f, top);
      return true;
    }
    return false;
  }
}
