//
// Created by Carbs0126 on 2023/12/18.
//

#ifndef INI_CPP_INIENTRYOBJECT_H
#define INI_CPP_INIENTRYOBJECT_H

#include "../atom/INISectionHeader.h"
#include "../atom/INIComment.h"
#include "../atom/INIKVPair.h"

using namespace std;

class INIEntryObject {
public:
    INIEntryObject() = default;

    ~INIEntryObject() {
        if (this->ptrINIKVPair != nullptr) {
            delete this->ptrINIKVPair;
        }
        for (auto *p: this->ptrINIComments) {
            if (p != nullptr) {
                delete p;
            }
        }
    }

    INIEntryObject(const INIEntryObject &) = delete;

    INIEntryObject &operator=(const INIEntryObject &) = delete;

    void setKVPair(INIKVPair *iniKVPair);

    INIKVPair *getKVPair();

    void addComment(INIComment *comment);

    void addComments(vector<INIComment *> comments);

    vector<INIComment *> getComments();

    vector<IINIContent *> generateContentLines();

private:
    vector<INIComment *> ptrINIComments;
    INIKVPair *ptrINIKVPair;
};


#endif //INI_CPP_INIENTRYOBJECT_H
