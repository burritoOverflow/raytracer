#pragma once

#include <sstream>

#include "Point.hpp"

namespace raytracer {
namespace io {

class FileOBJParser {
public:
  FileOBJParser(std::stringstream &ss);

  size_t ignored_lines = 0;

private:
  void ParseLine(std::string &line);
};

} // namespace io
} // namespace raytracer
