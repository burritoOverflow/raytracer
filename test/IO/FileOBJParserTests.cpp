#include "FileOBJParser.hpp"

#include <gtest/gtest.h>

#include <sstream>

using namespace raytracer;
using namespace utility;

TEST(FileOBJParserTest, IgnoringUnrecognizedLines) {
  auto s = "The Ray Tracer\n Challenge";
  auto ss = std::stringstream(s);

  auto parser = io::FileOBJParser(ss);
  EXPECT_EQ(2, parser.ignored_lines);
}
