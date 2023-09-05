#include "filters.h"

void Grayscale::Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {
    for (int32_t row = 0; row < processing_picture.GetPictureHeight(); ++row) {
        for (int32_t column = 0; column < processing_picture.GetPictureWidth(); ++column) {
            Pixel cur_pixel = processing_picture.GetPixel(row, column);
            uint8_t updated_value = 0.299 * cur_pixel.red + 0.587 * cur_pixel.green + 0.114 * cur_pixel.blue;
            cur_pixel.blue = updated_value;
            cur_pixel.green = updated_value;
            cur_pixel.red = updated_value;
            processing_picture.SetPixel(row, column, cur_pixel);
        }
    }
}

void Negative::Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {
    for (int32_t row = 0; row < processing_picture.GetPictureHeight(); ++row) {
        for (int32_t column = 0; column < processing_picture.GetPictureWidth(); ++column) {
            Pixel cur_pixel = processing_picture.GetPixel(row, column);
            cur_pixel.blue = InverseColor(cur_pixel.blue);
            cur_pixel.green = InverseColor(cur_pixel.green);
            cur_pixel.red = InverseColor(cur_pixel.red);
            processing_picture.SetPixel(row, column, cur_pixel);
        }
    }
}

void Crop::Apply(const std::vector<std::string> &filter_parameters, Picture &processing_picture) {
    int32_t crop_width = std::min(std::stoi(filter_parameters[0]), processing_picture.GetPictureWidth());
    int32_t crop_height = std::min(std::stoi(filter_parameters[1]), processing_picture.GetPictureHeight());
    processing_picture.SetPictureWidth(crop_width);
    processing_picture.SetPictureHeight(crop_height);
    processing_picture.ResizeHeight(crop_height);
    processing_picture.ResizeWidth(crop_width);
}

void FilterApplicator(std::vector<AppliedFilter>& filters_to_apply, Picture& pic) {
    Grayscale gs;
    Negative neg;
    Crop crop;
    Sharpening sharp;
    EdgeDetection edge;
    GaussianBlur blur;
    std::map<std::string, Filters *> filters_links;
    filters_links["-gs"] = &gs;
    filters_links["-neg"] = &neg;
    filters_links["-crop"] = &crop;
    filters_links["-sharp"] = &sharp;
    filters_links["-edge"] = &edge;
    filters_links["-blur"] = &blur;
    for (const AppliedFilter& current_filter : filters_to_apply) {
        filters_links[current_filter.filter_name]->Apply(current_filter.filter_parameters, pic);
    }
}