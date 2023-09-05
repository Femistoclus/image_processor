#include "pixel_matrix.h"

struct BitmapFileHeader {
    uint16_t file_type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_bits;
}__attribute__((__packed__));

struct BitmapInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes_count;
    uint16_t bits_count;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t clr_used;
    uint32_t clr_important;
}__attribute__((__packed__));

class Picture {
public:
    Picture(){};

    BitmapFileHeader& GetFileHeader() {
        return file_header_;
    }

    BitmapInfoHeader& GetInfoHeader() {
        return info_header_;
    }

    Pixel& GetPixel(int32_t row, int32_t column) {
       return pixel_matrix_.GetPixel(row, column);
    }

    void SetPixel(int32_t row, int32_t col, Pixel pixel) {
        pixel_matrix_.SetPixel(row, col, pixel);
    }

    void SetSize(int32_t height, int32_t width) {
        pixel_matrix_.SetMatrixOfPixels(height, width);
    }

    int32_t GetPictureWidth() const {
        return info_header_.width;
    }

    void SetPictureWidth(int32_t width) {
        info_header_.width = width;
    }

    int32_t GetPictureHeight() const {
        return info_header_.height;
    }

    void SetPictureHeight(int32_t height) {
        info_header_.height = height;
    }

    void ResizeHeight(int32_t new_height) {
        pixel_matrix_.ResizeHeight(new_height);
    }

    void ResizeWidth(int32_t new_width) {
        pixel_matrix_.ResizeWidth(new_width);
    }

private:
    BitmapFileHeader file_header_;
    BitmapInfoHeader info_header_;
    PixelMatrix pixel_matrix_;
};

void ReadPicture(const std::string& file_path, Picture &pic);
void WritePicture(const std::string& file_path, Picture &pic);