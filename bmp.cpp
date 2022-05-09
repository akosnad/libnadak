#include "bmp.hpp"
#include <fstream>
#include <iostream>

using namespace std;

BMP::BMP(string filename) {
    if(!read(filename))
        exit(1);
}

bool BMP::read(string filename) {
    ifstream f(filename);
    if(!f.good()) {
        cout << "Failed to open file: " << filename << endl;
        return false;
    }
    f.read((char*)&file_header, sizeof(file_header));
    // Check file header
    if(file_header.file_type != 0x4D42) {
        cout << "Not a BMP file" << endl;
        return false;
    }

    f.read((char*)&bmp_info_header, sizeof(bmp_info_header));
    // Check info header
    if(bmp_info_header.bit_count == 32) {
        bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
    } else {
        bmp_info_header.size = sizeof(BMPInfoHeader);
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    }
    file_header.file_size = file_header.offset_data;

    // Init image data
    data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

    if(!check_format()) {
        cout << "Failed to load" << endl
             << "Only 24-bit, uncrompressed, no alpa channel BMPs are supported" << endl;
        return false;
    }

    // Check for alignment
    if(bmp_info_header.width % 4 == 0) {
        f.read((char*)data.data(), data.size());
        file_header.file_size += data.size();
    }
    else {
        cout << "Unknown alignment" << endl;
        return false;
    }

    // cout << "Loaded BMP: " << filename << endl;
    return true;
}

genv::canvas BMP::to_canvas() {
    genv::canvas c;
    c.open(bmp_info_header.width, bmp_info_header.height);

    int channels = bmp_info_header.bit_count / 8;
    for(int y = 0; y < bmp_info_header.height; ++y)
    {
        for(int x = 0; x < bmp_info_header.width; ++x)
        {
            c << genv::move_to(x, bmp_info_header.height - y - 1);
            c << genv::color(
                data[channels * (y * bmp_info_header.width + x) + 2],  // R
                data[channels * (y * bmp_info_header.width + x) + 1],  // G
                data[channels * (y * bmp_info_header.width + x) + 0]   // B
              );
            c << genv::dot;
        }
    }
    return c;
}

bool BMP::check_format() {
    // TODO: implement
    return true;
}
