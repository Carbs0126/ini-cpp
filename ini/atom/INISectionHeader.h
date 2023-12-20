//
// Created by Carbs0126 on 2023/12/18.
//

#ifndef INI_CPP_INISECTIONHEADER_H
#define INI_CPP_INISECTIONHEADER_H

#include "../position/INIPosition.h"
#include "interfaces/IINIContent.h"
#include <iostream>

class INISectionHeader : public IINIContent {
public:
    string name;
    INIPosition *position;
public:
    INISectionHeader(string name, INIPosition *position) : name(name),
                                                           position(position) {
    }

    ~INISectionHeader() {
        if (this->position != nullptr) {
            delete this->position;
        }
    }

    INISectionHeader(const INISectionHeader &) = delete;

    INISectionHeader &operator=(const INISectionHeader &) = delete;

    INIPosition *getPosition() override;

    string toINIOutputString() override;

    string getDescription();

};

#endif //INI_CPP_INISECTIONHEADER_H
