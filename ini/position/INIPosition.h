//
// Created by Carbs0126 on 2023/12/16.
//

#ifndef INI_CPP_INIPOSITION_H
#define INI_CPP_INIPOSITION_H

#include <string>

using namespace std;

class INIPosition {
public:
    string getDescription();

public:
    INIPosition() = default;

    INIPosition(string fileLocation, int lineNumber, int charBegin, int charEnd) : fileLocation(fileLocation),
                                                                                   lineNumber(lineNumber),
                                                                                   charBegin(charBegin),
                                                                                   charEnd(charEnd) {}
    INIPosition(const INIPosition &) = delete;

    INIPosition &operator=(const INIPosition &) = delete;

    string fileLocation;
    int lineNumber;
    int charBegin;
    int charEnd;
};

#endif //INI_CPP_INIPOSITION_H
