#include <iostream>
#include <filesystem>
#include "ini/position/INIPosition.h"
#include "ini/INIFileParser.h"
#include "ini/INIFileGenerator.h"

using namespace std;

int main() {
    {
        INIObject *iniObject = INIFileParser::parseFileToINIObject(
                std::filesystem::current_path().parent_path().append("test-input.ini"));
        INIFileGenerator::generateFileFromINIObject(iniObject, std::filesystem::current_path().parent_path().append(
                "test-output.ini"));
        delete iniObject;
    }
    return 0;
}
