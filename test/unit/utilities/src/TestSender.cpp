#include <boost/signals2.hpp>
#include <gtest/gtest.h>
#include <string>

#include <utilities/Sender.h>

namespace example::test {

class ReceiverMock
{
public:
  ReceiverMock(example::utilities::Sender& sender)
    : m_sender(sender)
  {
    m_connection = m_sender.connect([this] {
      refresh();
    });
  }

  ~ReceiverMock()
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
  example::utilities::Sender& m_sender;
  boost::signals2::connection m_connection;
  std::string m_received;
};

TEST(Sender, Constructor_Shall_Be_Default_Constructible)
{
  static_assert(std::is_constructible<example::utilities::Sender>());
  SUCCEED();
}

TEST(Sender, On_Signal_Shall_Call_Slot)
{
  std::string const EXPECTED_MSG{"Shut up and take my money!"};
  example::utilities::Sender sender;
  ReceiverMock receiver(sender);
  sender.updateText(EXPECTED_MSG.c_str());
  EXPECT_EQ(EXPECTED_MSG, receiver.received());
}

} // namespace example::test
