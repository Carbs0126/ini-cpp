//
// Created by Carbs0126 on 2023/12/17.
//

#ifndef INI_CPP_INIEMPTY_H
#define INI_CPP_INIEMPTY_H


#include "../position/INIPosition.h"
#include "interfaces/IINIContent.h"

class INIEmpty : public IINIContent {
public:
    INIPosition *position;
public:
    INIEmpty(INIPosition *position) : position(position) {
    }

    ~INIEmpty() {
        if (this->position != nullptr) {
            delete position;
        }
    }

    INIEmpty(const INIEmpty &) = delete;

    INIEmpty &operator=(const INIEmpty &) = delete;

    INIPosition *getPosition() override;

    string toINIOutputString() override;

    string getDescription();
};


#endif //INI_CPP_INIEMPTY_H
