#include <boost/signals2.hpp>
#include <gtest/gtest.h>
#include <string>

#include <utilities/Receiver.h>

namespace example::test {

class ReceiverMock
{
public:
  ReceiverMock(example::utilities::Receiver& receiver)
    : m_receiver(receiver)
  {
    m_connection = m_receiver.connect([this] {
      refresh();
    });
  }

  ~ReceiverMock()
  {
    m_connection.disconnect();
  }

  void refresh()
  {
    m_received = m_receiver.getText();
  }

  std::string received()
  {
    return m_received;
  }

private:
  example::utilities::Receiver& m_receiver;
  boost::signals2::connection m_connection;
  std::string m_received;
};

TEST(Receiver, Constructor_Shall_Be_Default_Constructible)
{
  static_assert(std::is_constructible<example::utilities::Receiver>());
  SUCCEED();
}

TEST(Receiver, On_Signal_Shall_Call_Slot)
{
  std::string const EXPECTED_MSG{"Shut up and take my money!"};
  example::utilities::Receiver sender;
  ReceiverMock receiver(sender);
  sender.append(EXPECTED_MSG.c_str());
  EXPECT_EQ(EXPECTED_MSG, receiver.received());
}

} // namespace example::test
