//
// Created by Carbs0126 on 2023/12/19.
//

#ifndef INI_CPP_INIFILEPARSER_H
#define INI_CPP_INIFILEPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include "entity/INIObject.h"
#include "atom/INIEmpty.h"
#include "INIUtil.h"

class INIFileParser {
public:
    static INIObject *parseFileToINIObject(string fileName);

    static bool checkSameLine(IINIContent *preINIContent, IINIContent *curINIContent);

    static void appendLineContentIntoLineList(IINIContent *iiniContent, vector<IINIContent *> *iniLines);

    static INIComment *checkSemicolon(string originString,
                                      int charBegin,
                                      vector<IINIContent *> *iniLines,
                                      string fileLocation,
                                      int lineNumber);
};


#endif //INI_CPP_INIFILEPARSER_H
