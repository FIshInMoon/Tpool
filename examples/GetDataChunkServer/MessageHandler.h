// -*- mode: c++ -*-
#ifndef _GET_DATA_CHUNK_SERVER_MESSAGE_HANDLER_H_
#define _GET_DATA_CHUNK_SERVER_MESSAGE_HANDLER_H_

#include <google/protobuf/message.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>


class MessageHandler
{
public:
  typedef boost::shared_ptr<MessageHandler> Ptr;
  typedef google::protobuf::Message Message;
  
  MessageHandler()
  {}
  
  virtual ~MessageHandler()
  {}

  virtual Message* HandleMessage(Message* message) = 0;
};

template <typename T>
class FunctorMessageHandler : public MessageHandler
{
public:
  typedef boost::function<Message* (T* message)> Handler;
  
  FunctorMessageHandler(const Handler& handler)
    : m_handler(handler)
  {}
  
  virtual ~FunctorMessageHandler()
  {}

  virtual Message* HandleMessage(google::protobuf::Message* message)
  {
    T* concreteMessage = dynamic_cast<T*>(message);
    assert(concreteMessage != NULL);
    return m_handler(concreteMessage);
  }

private:
  Handler m_handler;
};

#endif
