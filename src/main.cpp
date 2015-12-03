#include "main.hpp"
#include "log.h"
#include "gflags/gflags.h"

DEFINE_string(name, "", "Name for salutation");

int main(int argc, char *argv[]) {
  LOG("LOG MESSAGE");

  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << "Hello World!" << " " << FLAGS_name << std::endl;
  return 0;
}
