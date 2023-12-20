//
// Created by Carbs0126 on 2023/12/18.
//

#include "INIEntryObject.h"

void INIEntryObject::setKVPair(INIKVPair *iniKVPair) {
    this->ptrINIKVPair = iniKVPair;
}

INIKVPair *INIEntryObject::getKVPair() {
    return this->ptrINIKVPair;
}

void INIEntryObject::addComment(INIComment *comment) {
    this->ptrINIComments.push_back(comment);
}

void INIEntryObject::addComments(vector<INIComment *> comments) {
    this->ptrINIComments.insert(this->ptrINIComments.end(),
                                std::make_move_iterator(comments.begin()),
                                std::make_move_iterator(comments.end()));
}

vector<INIComment *> INIEntryObject::getComments() {
    return this->ptrINIComments;
}

vector<IINIContent *> INIEntryObject::generateContentLines() {
    vector<IINIContent *> vec;

    for (auto *p: this->ptrINIComments) {
        if (p != nullptr) {
            vec.push_back(p);
        }
    }
    if (this->ptrINIKVPair != nullptr) {
        vec.push_back(this->ptrINIKVPair);
    }
    return vec;
}
