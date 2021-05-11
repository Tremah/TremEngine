﻿#pragma once

//c++ includes

//external library includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//custom (own) library includes

//game engine includes
#include <trem/util/logger.h>
#include <trem/event/key_events.h>
#include <trem/event/window_events.h>
#include <trem/core/service_locator.h>

/**
 *  \brief Defines an orthographic camera.<br>
 *         Combines projection matrix and view matrix into the view transform.
 */
namespace Trem
{  
  class Camera
  {
    public:
      Camera(){}
      //Constructors and deconstructors 

      //Member variables

      //Member functions
      void init(const float left, const float right, const float bottom, const float top);

      //camera movement
      bool move(KeyPressedEvent& ev);

      //setter
      void setPosition(const glm::vec3& position);
      void setRotation(float rotationAngle);
      void setProjectionMatrix(const glm::mat4& projectionMatrix);
      void setViewMatrix(const glm::mat4& viewMatrix);

      //getter
      glm::vec3 position() const;
      glm::mat4 viewMatrix() const;
      glm::mat4 projectionMatrix() const;
      glm::mat4 viewProjectionMatrix() const;

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      //camera properties
      glm::vec3 position_{0.f};
      float     rotationAngle_{0.f};
      float     movementSpeed_{10.f};

      //transforms
      glm::mat4 viewMatrix_{1.f};
      glm::mat4 projectionMatrix_{1.f};
      glm::mat4 viewProjectionMatrix_{1.f};

      //Member functions
      /**
       * \brief Calculates the projection matrix.
       * @param left    Left limit of the projection matrix.
       * @param right   Right limit of the projection matrix.
       * @param bottom  Bottom limit of the projection matrix.
       * @param top     Top limit of the projection matrix.
       */
      void calculateProjectionMatrix(float left, float right, float bottom, float top);

      /**
       * \brief Calculates the view-projection matrix.
       */
      void calculateViewProjectionMatrix(); 

      //Event handlers
      void handleWindowResizedEvent(WindowResizedEvent& wREvent);
  };
}