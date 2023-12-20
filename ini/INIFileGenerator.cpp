//
// Created by Carbs0126 on 2023/12/19.
//

#include "INIFileGenerator.h"

void INIFileGenerator::generateFileFromINIObject(INIObject *iniObject, string fileAbsolutePath) {
    if (iniObject == nullptr) {
        throw std::runtime_error("IniObject should not be null");
    }
    vector<string> lines = iniObject->generateStringLines();
    std::ofstream outputFile(fileAbsolutePath);
    if (outputFile.is_open()) {
        int length = lines.size();
        int index = 0;
        for (string &line: lines) {
            outputFile << line;
            if (index < length - 1) {
                outputFile << endl;
            }
            index++;
        }
        outputFile.close();
    } else {
        throw std::runtime_error("Failed to open the file for writing.");
    }
}