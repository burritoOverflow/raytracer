#include "FileOBJParser.hpp"

namespace raytracer {
namespace io {

FileOBJParser::FileOBJParser(std::stringstream &ss) {
  std::string line;
  while (std::getline(ss, line, '\n')) {
    ParseLine(line);
  }
}

void FileOBJParser::ParseLine(std::string &line) { ignored_lines++; }

} // namespace io
} // namespace raytracer