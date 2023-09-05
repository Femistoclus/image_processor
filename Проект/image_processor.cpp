#include "parser.h"
#include "filters.h"

int main(int argc, char** argv) {
    Parser parsed_command_line(argc, argv);
    Picture processing_picture;
    ReadPicture(parsed_command_line.GetInputFilePath(), processing_picture);
    FilterApplicator(parsed_command_line.GetFiltersWithParameters(), processing_picture);
    WritePicture(parsed_command_line.GetOutputFilePath(), processing_picture);
    return 0;
}