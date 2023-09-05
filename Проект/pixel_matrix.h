#ifndef IMAGE_PROCESSOR_PIXEL_MATRIX_H
#define IMAGE_PROCESSOR_PIXEL_MATRIX_H

#include <vector>
#include <tuple>
#include <string>

struct Pixel {
    Pixel():blue(0), green(0), red(0){};

    Pixel(uint8_t b, uint8_t g, uint8_t r) {
        blue = b;
        green = g;
        red = r;
    }

    Pixel& operator=(Pixel other_pixel) {
        blue = other_pixel.blue;
        green = other_pixel.green;
        red = other_pixel.red;
        return *this;
    }

    bool operator==(const Pixel& other_pixel) const {
        return (blue == other_pixel.blue) && (green == other_pixel.green) && (red == other_pixel.red);
    }

    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

class PixelMatrix{
public:
    PixelMatrix(){};

    void SetPixel(int32_t row, int32_t column, Pixel pixel_to_set) {
        pixels_[row][column] = pixel_to_set;
    }

    void SetMatrixOfPixels(int32_t height, int32_t width) {
        for (uint32_t row = 0; row < height; ++row) {
            pixels_.push_back(std::vector<Pixel>());
            for (uint32_t column = 0; column < width; ++column)
                pixels_[row].push_back(Pixel());

        }
    }

    Pixel& GetPixel(int32_t row, int32_t column) {
        return pixels_[row][column];
    }

    void ResizeHeight(int32_t new_height) {
        pixels_.resize(new_height);
    }

    void ResizeWidth(int32_t new_width) {
        for (std::vector<Pixel>& row : pixels_) {
            row.resize(new_width);
        }
    }

public:
    std::vector< std::vector<Pixel> > pixels_;
};

#endif //IMAGE_PROCESSOR_PIXEL_MATRIX_H
