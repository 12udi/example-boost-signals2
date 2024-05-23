#pragma once

#include <boost/signals2.hpp>

namespace example::utilities {

class Receiver
{
public:
  typedef boost::signals2::signal<void()> signal_t;

  Receiver();

  boost::signals2::connection connect(signal_t::slot_type const& subscriber)
  {
    return m_sig.connect(subscriber);
  }

  void append(char const* s)
  {
    m_text += s;
    m_sig();
  }

  std::string& getText()
  {
    return m_text;
  }

private:
  signal_t m_sig;
  std::string m_text;
};

} // namespace example::utilities
