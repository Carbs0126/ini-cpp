//
// Created by Carbs0126 on 2023/12/19.
//

#ifndef INI_CPP_INIOBJECT_H
#define INI_CPP_INIOBJECT_H

#include <string>
#include <map>
#include "INISectionObject.h"

using namespace std;

// 代表一个文件的内容
class INIObject {
public:
    INIObject() = default;
    ~INIObject() {
        for (const auto& pair : this->sectionsMap) {
            if (pair.second != nullptr) {
                delete pair.second;
            }
        }
    }

    void addSection(INISectionObject *section);

    INISectionObject *getSection(string sectionName);

    std::map<string, INISectionObject *> *getSectionMap();

    std::vector<string> *getOrderedSectionsName();

    std::vector<string> generateStringLines();

private:
    std::map<string, INISectionObject *> sectionsMap;
    std::vector<string> orderedSectionsName;
};


#endif //INI_CPP_INIOBJECT_H
