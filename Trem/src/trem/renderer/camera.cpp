#include "trpch.h"
#include "camera.h"

namespace Trem
{
  Camera::Camera(float left, float right, float bottom, float top)
  {
    //create the cameras transform (view matrix) and the projection matrix for the entire scene
    //and combine them into the view-projection matrix     
    viewMatrix_           = glm::translate(glm::mat4{1.f}, position_) * glm::rotate(glm::mat4{1.f}, rotationAngle_, {0.f, 0.f, 1.f});
    projectionMatrix_     = glm::ortho(left, right, bottom, top, 1.f, -1.f);
    viewProjectionMatrix_ = projectionMatrix_ * glm::inverse(viewMatrix_);
  }

  void Camera::move(KeyEvent* ev)
  {
    glm::vec3 camMovement{0.f};
    float camSpeed = 5.f;
    switch (ev->keycode())
    {
      case Key::W:
        camMovement.y = camSpeed;
        break;
      case Key::S:
        camMovement.y = -camSpeed;
        break;
      case Key::A:
        camMovement.x = -camSpeed;
        break;
      case Key::D:
        camMovement.x = camSpeed;
        break;
    }

    setPosition(position_ + camMovement);    
    Logger::logger()->info("camera moved to x:{0}, y:{1}", position_.x, position_.y);
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

  void Camera::setEventCallback(const std::function<void(Event&)>& callback)
  {
    eventCallback_ = callback;
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

  bool Camera::handleEvent(Event& ev)
  {
    if(ev.inCategory(EventCategory::KeyboardEvent))
    {
      KeyEvent* keyEvent = static_cast<KeyEvent*>(&ev);
      move(keyEvent);
    }
    if(ev.type() == EventType::WindowResized)
    {
      WindowResizedEvent* windowResizedEvent = static_cast<WindowResizedEvent*>(&ev);
      float right = static_cast<float>(windowResizedEvent->windowSize_.x);
      float top = static_cast<float>(windowResizedEvent->windowSize_.y);
      calculateProjectionMatrix(0.f, right, 0.f, top);
    }
    return false;
  }
}
