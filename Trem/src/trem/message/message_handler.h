#pragma once

//c++ includes

//external library includes

//game engine includes
#include "message.h"

/**
 *  \brief Message handler to supply messaging functionality.
 *
 */
namespace Trem
{
  //callback to queue a message

  class MessageHandler
  {
    public:
      //Constructors and deconstructors
      MessageHandler();

      //Member variables
      //Member functions

      /**
       * \brief Subscribes a game object to the message handler.
       * @param callback  Callback to be executed when a message is dispatched.
       * @param msgType Message type for which the callback is used.
       */
      void subscribe(MsgType msgType, MsgDispatchCallback callback);

      /**
       * \brief Queues a message in the respective message buffer.
       * @param msg Message to be queued.
       */
      void queue(UnqPtr<Message> msg);

      /**
       * \brief Dispatch 
       * @param msg Message to be dispatched.
       */
      void dispatch(UnqPtr<Message> msg);

      /**
       * \brief Processes messages in the queue.
       */
      void processQueue();

    protected:
      //Constructors and deconstructors
      //Member variables
      //Member functions

    private:
      //Constructors and deconstructors
      //Member variables
      static constexpr uint32_t maxMessages_ = 10000; /** Maximum number of messages which can be stored before dispatching them */
      std::vector<UnqPtr<Message>> msgBuffer_;

      //callback storage
      std::vector<std::vector<MsgDispatchCallback>> msgCallbacks_; /** storage for dispatch callback function, accessed via [MessageType][MessageCallback]*/

      //Member functions 
  };
}
