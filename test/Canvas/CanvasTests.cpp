#include "Canvas.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(CanvasTests, CreateCanvas) {
  size_t width = 10;
  size_t height = 10;
  raytracer::Canvas c(width, height);
  ASSERT_EQ(width, c.width_);
  ASSERT_EQ(height, c.height_);

  utility::Color black(0, 0, 0);
  for (size_t i = 0; i < width; ++i) {
    for (size_t j = 0; j < height; ++j) {
      EXPECT_TRUE(black == c(i, j));
    }
  }
}

TEST(CanvasTests, WritePixelToCanvas) {
  raytracer::Canvas c(10, 20);
  utility::Color red(1, 0, 0);
  c.WritePixel(2, 3, red);
  EXPECT_TRUE(red == c(2, 3));
  EXPECT_TRUE(red == c.GetPixel(2, 3));
}

TEST(CanvasTests, ConstructPpmHeader) {
  raytracer::Canvas c(5, 3);
  std::string ppm = c.ToPpm();
  std::istringstream strStream(ppm);

  std::string ppm_identifier;
  std::getline(strStream, ppm_identifier);
  EXPECT_EQ("P3", ppm_identifier);

  std::string width_and_height;
  std::getline(strStream, width_and_height);
  EXPECT_EQ("5 3", width_and_height);

  std::string max_color_value;
  std::getline(strStream, max_color_value);
  EXPECT_EQ("255", max_color_value);
}

TEST(CanvasTests, ConstructPpmPixelData) {
  raytracer::Canvas c(5, 3);
  utility::Color c1(1.5, 0, 0);
  utility::Color c2(0, 0.5, 0);
  utility::Color c3(-0.5, 0, 1);
  c.WritePixel(0, 0, c1);
  c.WritePixel(2, 1, c2);
  c.WritePixel(4, 2, c3);

  std::string ppm = c.ToPpm();
  std::istringstream ppm_stream(ppm);

  std::string header;
  for (size_t i = 0; i < 3; ++i) {
    std::getline(ppm_stream, header);
  }

  std::string row1, row2, row3;
  std::getline(ppm_stream, row1);
  std::getline(ppm_stream, row2);
  std::getline(ppm_stream, row3);
  EXPECT_EQ("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0", row1);
  EXPECT_EQ("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0", row2);
  EXPECT_EQ("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255", row3);
}

TEST(CanvasTests, SplitLongLinesInPpmFiles) {
  size_t width = 10;
  size_t height = 2;
  raytracer::Canvas c(width, height);
  for (size_t x = 0; x < width; ++x) {
    for (size_t y = 0; y < height; ++y) {
      c.WritePixel(x, y, utility::Color(1, 0.8, 0.6));
    }
  }
  std::string ppm = c.ToPpm();
  std::istringstream ppm_stream(ppm);

  std::string header;
  for (size_t i = 0; i < 3; ++i) {
    std::getline(ppm_stream, header);
  }

  std::string row1, row2, row3, row4;
  std::getline(ppm_stream, row1);
  std::getline(ppm_stream, row2);
  std::getline(ppm_stream, row3);
  std::getline(ppm_stream, row4);
  EXPECT_EQ(
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
      row1);
  EXPECT_EQ("153 255 204 153 255 204 153 255 204 153 255 204 153", row2);
  EXPECT_EQ(
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
      row3);
  EXPECT_EQ("153 255 204 153 255 204 153 255 204 153 255 204 153", row4);
}

TEST(CanvasTests, PpmFilesAreTerminatedByNewline) {
  raytracer::Canvas c(5, 3);
  std::string ppm = c.ToPpm();
  EXPECT_EQ('\n', ppm.at(ppm.length() - 1));
}