#ifndef IMAGE_PROCESSOR_FILTERS_H
#define IMAGE_PROCESSOR_FILTERS_H

#include "picture.h"
#include <vector>
#include <string>
#include <string_view>
#include <cmath>
#include <map>

struct AppliedFilter {
    std::string filter_name;
    std::vector<std::string> filter_parameters;
    void Clear() {
        filter_name = "";
        filter_parameters.clear();
    }
    bool Empty() const {
        return filter_name.empty();
    }
};

class Filters {
public:
    Filters(){};
    virtual void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {

    };
protected:
};

class Crop: public Filters {
public:
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture);
};

class Grayscale: public Filters{
public:
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture);
};

class Negative: public Filters {
public:
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture);
    static uint8_t InverseColor(uint8_t color_to_inverse) {
        double max = 255;
        return static_cast<uint8_t>(std::round((1 - (static_cast<double>(color_to_inverse) / max)) * max));
    }
};

class Sharpening: public Filters {
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {

    };
};

class EdgeDetection: public Filters {
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {

    };
};

class GaussianBlur: public Filters {
    void Apply(const std::vector<std::string>& filter_parameters, Picture &processing_picture) {

    };
};

void FilterApplicator(std::vector<AppliedFilter>&, Picture& pic);

#endif //IMAGE_PROCESSOR_FILTERS_H
