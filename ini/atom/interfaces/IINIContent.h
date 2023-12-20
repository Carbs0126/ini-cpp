//
// Created by Carbs0126 on 2023/12/16.
//

#ifndef INI_CPP_IINICONTENT_H
#define INI_CPP_IINICONTENT_H

#include <string>
#include "../../position/INIPosition.h"

using namespace std;

class IINIContent {
public:
    virtual INIPosition *getPosition() = 0;

    virtual string toINIOutputString() = 0;

    virtual ~IINIContent() {};
};


#endif //INI_CPP_IINICONTENT_H
