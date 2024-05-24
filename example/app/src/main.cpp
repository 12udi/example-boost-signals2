#include <chrono>
#include <cstdio>
#include <future>
#include <thread>

#include <boost/signals2.hpp>
#include <fmt/core.h>

#include <utilities/Receiver.h>
#include <utilities/Sender.h>

using namespace boost::signals2;

void
hello()
{
  fmt::print(stderr, "Hello");
}

void
world()
{
  fmt::print(stderr, ", world!\n");
}

void
payload(std::string const& text)
{
  fmt::print(stderr, "{}", text);
}

int
main()
{
  using namespace example::utilities;

  // example with void signal
  signal<void()> s1;
  s1.connect(1, world);
  s1.connect(0, hello);
  s1();
  s1.disconnect(hello);
  s1.disconnect(world);
  s1();

  // example with payload signal
  signal<void(std::string const&)> s2;
  s2.connect(&payload);
  s2("First payload\n");
  s2.disconnect(&payload);
  s2("Second payload\n");

  // example with countdown
  Sender sender{};
  Receiver receiver(sender);

  bool running = true;
  int progress = 0;

  auto signalThread = std::async(std::launch::async, [&]() {
    while (running) {
      sender.updateText(std::to_string(progress).c_str());
      progress++;
      fmt::print(stderr, "{}\n", receiver.received());
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      if (progress == 10) {
        fmt::print(stderr, "{}\n", progress);

        running = false;
      }
    }
  });

  fmt::print(stderr, "######### start #########\n");

  signalThread.wait();

  fmt::print(stderr, "######### finished #########\n");

  return EXIT_SUCCESS;
}
