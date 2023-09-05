#include "picture.h"

#include <fstream>

void ReadPicture(const std::string& file_path, Picture &pic) {
    std::fstream picture_stream;
    picture_stream.open(file_path, std::ios_base::in | std::ios_base::binary);
    if (!picture_stream.is_open()) {
        throw std::runtime_error("Cannot open the file");
    }
    BitmapFileHeader& file_header = pic.GetFileHeader();
    BitmapInfoHeader& info_header = pic.GetInfoHeader();

    picture_stream.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    picture_stream.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    pic.SetSize(info_header.height, info_header.width);

    const std::streamsize SIZE_OF_GARBAGE = info_header.width % 4;

    for (int64_t row = info_header.height - 1; row >= 0; --row) {
        for (size_t col = 0; col < info_header.width; ++col) {
            Pixel pixel;
            picture_stream.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            pic.SetPixel(row, col, pixel);
        }
        picture_stream.ignore(SIZE_OF_GARBAGE);
    }

    picture_stream.close();
}

void WritePicture(const std::string& file_path, Picture& pic) {
    std::ofstream picture_stream;
    picture_stream.open(file_path, std::ios_base::out | std::ios_base::binary);

    BitmapFileHeader& file_header = pic.GetFileHeader();
    BitmapInfoHeader& info_header = pic.GetInfoHeader();

    picture_stream.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    picture_stream.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    const std::streamsize SIZE_OF_GARBAGE = info_header.width % 4;

    for (int64_t row = info_header.height - 1; row >= 0; --row) {
        for (size_t col = 0; col < info_header.width; ++col) {
            Pixel pixel_to_write = pic.GetPixel(row, col);
            picture_stream.write(reinterpret_cast<char*>(&pixel_to_write), sizeof(pixel_to_write));
        }
        Pixel garbage_pixel(0, 0, 0);
        picture_stream.write(reinterpret_cast<const char*> (&garbage_pixel), SIZE_OF_GARBAGE);
    }
    picture_stream.close();
}