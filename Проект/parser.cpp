#include "parser.h"

Parser::Parser(int argc, char** argv){
    if (argc < MINIMAL_NUMBER_OF_ARGUMENTS) {
        throw std::runtime_error("More arguments are needed");
    } else {
        program_name_ = argv[PROGRAM_NAME_POS];
        input_file_path_ = argv[INPUT_FILE_PATH_POS];
        output_file_path_ = argv[OUTPUT_FILE_PATH_POS];
        AppliedFilter current_filter;
        for (size_t i = MINIMAL_NUMBER_OF_ARGUMENTS; i < argc; ++i) {
            if (argv[i][0] == '-') {
                if (!current_filter.Empty()) {
                    applied_filters_.push_back(current_filter);
                    current_filter.Clear();
                }
                current_filter.filter_name = argv[i];
            } else {
                current_filter.filter_parameters.push_back(argv[i]);
            }
        }
        if (!current_filter.Empty()) {
            applied_filters_.push_back(current_filter);
        }
    }
}

