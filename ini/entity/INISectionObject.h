//
// Created by Carbs0126 on 2023/12/18.
//

#ifndef INI_CPP_INISECTIONOBJECT_H
#define INI_CPP_INISECTIONOBJECT_H

#include "../atom/INISectionHeader.h"
#include "../atom/INIComment.h"
#include "INIEntryObject.h"
#include <iostream>

using namespace std;

class INISectionObject {
public:
    INISectionObject() = default;

    ~INISectionObject() {
        if (ptrINISectionHeader != nullptr) {
            delete ptrINISectionHeader;
        }
        for (auto *p: this->ptrINIEntryObjects) {
            if (p != nullptr) {
                delete p;
            }
        }
        for (auto *p: this->ptrINIComments) {
            if (p != nullptr) {
                delete p;
            }
        }
    }

    INISectionObject(const INISectionObject &) = delete;

    INISectionObject &operator=(const INISectionObject &) = delete;

    void addComment(INIComment *comment);

    void addComments(vector<INIComment *> comments);

    vector<INIComment *> getComments();

    void addEntryObject(INIEntryObject *entryObject);

    string getName();

    void setSectionHeader(INISectionHeader *shared);

    INISectionHeader *getSectionHeader();

    vector<IINIContent *> generateContentLines();

private:
    INISectionHeader *ptrINISectionHeader;

    vector<INIEntryObject *> ptrINIEntryObjects;

    vector<INIComment *> ptrINIComments;

};


#endif //INI_CPP_INISECTIONOBJECT_H
