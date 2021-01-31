#pragma once

//c++ includes
#include "trpch.h"

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/event/event.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class EventHandler
  {
    public:
      //Default constructor;
      /*EventHandler()
      {        
        eventBuffer_.reserve(500);
      }*/

      //param. constructors
      EventHandler(Event& ev) : ev_{ev} {}

      //public member variables

      //public member functions
      /**
       * \brief Templated function which handles a received event.<br>
       *        The event handler is constructed with a received event.<br>
       *        It can then be called with an event type (dispatch) to be checked against the received events type.<br>
       *        If the types match, the transmitted function is called with the received event as its parameter.
       * @tparam EvType Type of the currently checked event.
       * @tparam EvFunc Type of the function which is to be called when both events types match.
       * @param evFunc  Address of the function which is to be called when both events match.
       */
      template<typename EvType, typename EvFunc>
      void dispatch(const EvFunc& evFunc)
      {
        //check if the received events type matches the currently dispatched type
        if(ev_.type() == EvType::staticType())
        {
          //call the function which was submitted as the dispatched events handler
          ev_.handled_ = evFunc(static_cast<EvType&>(ev_));
        }
      }

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables
      Event& ev_;
      //std::vector<Event&> eventBuffer_;

      //private member functions
      
  };
}
