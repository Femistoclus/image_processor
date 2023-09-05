#ifndef IMAGE_PROCESSOR_PARSER_H
#define IMAGE_PROCESSOR_PARSER_H

#include "filters.h"

const size_t MINIMAL_NUMBER_OF_ARGUMENTS = 4;
const size_t PROGRAM_NAME_POS = 1;
const size_t INPUT_FILE_PATH_POS = 2;
const size_t OUTPUT_FILE_PATH_POS = 3;


class Parser {
public:
    Parser(int argc, char* argv[]);
    std::vector<AppliedFilter>& GetFiltersWithParameters() {
        return applied_filters_;
    }
    std::string GetInputFilePath() {
        return input_file_path_;
    }
    std::string GetOutputFilePath() {
        return output_file_path_;
    }
private:
    std::string program_name_;
    std::string input_file_path_;
    std::string output_file_path_;
    std::vector<AppliedFilter> applied_filters_;
};

#endif //IMAGE_PROCESSOR_PARSER_H
