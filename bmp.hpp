#ifndef _BMP_H
#define _BMP_H

/*
 * A jelen bmp.hpp és bmp.cpp
 * az első beadandómból származik
 *
 */

#include <string>
#include <vector>
#include "graphics.hpp"

using namespace std;

// Taken from:
// https://en.wikipedia.org/wiki/BMP_file_format


// Need to fix struct alighnemt
// as BMP files are little-endian
#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t file_type   {0x4D42};
    uint32_t file_size   {0};
    uint16_t reserved1   {0};
    uint16_t reserved2   {0};
    uint32_t offset_data {0};
};


struct BMPInfoHeader {
    uint32_t size {0};
    int32_t  width {0};
    int32_t  height {0};
    uint16_t planes {1};
    uint16_t bit_count {0};
    uint32_t compression {0};
    uint32_t size_image {0};
    int32_t  x_pixels_per_meter {0};
    int32_t  y_pixels_per_meter {0};
    uint32_t colors_used {0};
    uint32_t colors_important {0};
};

struct BMPColorHeader {
    uint32_t red_mask {0x00ff0000};
    uint32_t green_mask {0x0000ff00};
    uint32_t blue_mask {0x000000ff};
    uint32_t alpha_mask {0xff000000};
    uint32_t color_space_type {0x73524742};
    uint32_t unused[16] {0};
};

#pragma pack(pop)

class BMP {
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
    BMPColorHeader bmp_color_header;
    vector<uint8_t> data;
    bool check_format();

public:
    BMP(string filename);
    bool read(string filename);
    genv::canvas to_canvas();
};

#endif
