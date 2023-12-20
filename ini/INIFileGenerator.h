//
// Created by Carbs0126 on 2023/12/19.
//

#ifndef INI_CPP_INIFILEGENERATOR_H
#define INI_CPP_INIFILEGENERATOR_H

#include <iostream>
#include <fstream>
#include "entity/INIObject.h"

using namespace std;

class INIFileGenerator {
public:
    static void generateFileFromINIObject(INIObject *iniObject, string fileAbsolutePath);
};


#endif //INI_CPP_INIFILEGENERATOR_H
