#include "trpch.h"
#include "message_handler.h"

namespace Trem
{
  MessageHandler::MessageHandler()
  {
    msgBuffer_.reserve(maxMessages_);

    for(std::size_t i=0; i < MsgTypes::count(); i++)
    {
      msgCallbacks_.push_back(std::vector<MsgDispatchCallback>{});
    }
  }

  void MessageHandler::subscribe(const MsgType msgType, const MsgDispatchCallback callback)
  {    
    msgCallbacks_.at(msgType).push_back(callback);
  }

  void MessageHandler::queue(UnqPtr<Message> msg)
  {    
    msgBuffer_.push_back(std::move(msg));      
  }

  void MessageHandler::dispatch(UnqPtr<Message> msg)
  {
  }

  void MessageHandler::processQueue()
  {
    std::for_each(msgBuffer_.begin(), msgBuffer_.end(), [this](UnqPtr<Message>& msg)
    {
      std::for_each(msgCallbacks_.at(msg->type()).begin(), msgCallbacks_.at(msg->type()).end(), [&msg] (MsgDispatchCallback callback)
      {
        ServiceLocator::logger().debug("dispatch message: {0}", MsgTypes::toString(msg->type()));
        msg->handled_ |= callback(msg);
      });
    });
   
    //remove all handled messages
    msgBuffer_.erase(std::remove_if(msgBuffer_.begin(), msgBuffer_.end(), [this](UnqPtr<Message>& msg)
    {
      ServiceLocator::logger().debug("delete message: {0}", MsgTypes::toString(msg->type()));
      return msg->handled_;
    }), msgBuffer_.end());
  }
}
