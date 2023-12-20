//
// Created by Carbs0126 on 2023/12/18.
//

#include "INISectionObject.h"

void INISectionObject::addComment(INIComment *comment) {
    this->ptrINIComments.push_back(comment);
}

void INISectionObject::addComments(vector<INIComment *> comments) {
    this->ptrINIComments.insert(this->ptrINIComments.end(),
                                std::make_move_iterator(comments.begin()),
                                std::make_move_iterator(comments.end()));
}

vector<INIComment *> INISectionObject::getComments() {
    return this->ptrINIComments;
}

void INISectionObject::addEntryObject(INIEntryObject *entryObject) {
    this->ptrINIEntryObjects.push_back(entryObject);
}

string INISectionObject::getName() {
    if (this->ptrINISectionHeader != nullptr) {
        return this->ptrINISectionHeader->name;
    }
    return "";
}

void INISectionObject::setSectionHeader(INISectionHeader *shared) {
    this->ptrINISectionHeader = shared;
}

INISectionHeader *INISectionObject::getSectionHeader() {
    return this->ptrINISectionHeader;
}

vector<IINIContent *> INISectionObject::generateContentLines() {
    vector<IINIContent *> lines;

    for (auto *p: this->ptrINIComments) {
        if (p != nullptr) {
            lines.push_back(p);
        }
    }
    if (this->ptrINISectionHeader != nullptr) {
        lines.push_back(this->ptrINISectionHeader);
    }
    for (auto *p: this->ptrINIEntryObjects) {
        if (p != nullptr) {
            vector<IINIContent *> entryLines = p->generateContentLines();
            if (!entryLines.empty()) {
                for (IINIContent *pINIContent : entryLines) {
                    lines.push_back(pINIContent);
                }
            }
        }
    }
    return lines;
}