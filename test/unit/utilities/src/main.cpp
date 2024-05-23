#include <fmt/core.h>
#include <gtest/gtest.h>

namespace example::test {

class Utilities_UnitTest : public testing::Environment
{
  void SetUp() override {}

  void TearDown() override {}
};
} // namespace example::test

int
main(int argc, char* argv[])
{
  using namespace example::test;

  try {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new Utilities_UnitTest{});
    return RUN_ALL_TESTS();
  } catch (std::runtime_error const& x) {
    fmt::print("error {}", x.what());
    throw;
  } catch (std::exception const& x) {
    fmt::print("error {}", x.what());
    throw;
  }
}
