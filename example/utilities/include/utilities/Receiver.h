#pragma once

#include <string>
#include <boost/signals2.hpp>

#include "Sender.h"

namespace example::utilities {

class Receiver
{
public:
  Receiver(Sender& sender)
    : m_sender(sender)
  {
    m_connection = m_sender.connect([this] {
      refresh();
    });
  }

  ~Receiver()
  {
    m_connection.disconnect();
  }

  void refresh()
  {
    m_received = m_sender.getText();
  }

  std::string received()
  {
    return m_received;
  }

private:
  Sender& m_sender;
  boost::signals2::connection m_connection;
  std::string m_received{};
};

}
