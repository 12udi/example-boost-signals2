#include <fmt/core.h>

#include <utilities/Receiver.h>
#include <utilities/Sender.h>

#include <chrono>
#include <cstdio>
#include <future>
#include <thread>

int
main()
{
  using namespace example::utilities;

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
        fmt::print(stderr, "{}", progress);

        running = false;
      }
    }
  });

  fmt::print(stderr, "######### start #########\n");

  signalThread.wait();

  fmt::print(stderr, "######### finished #########");

  return EXIT_SUCCESS;
}
