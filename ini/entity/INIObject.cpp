//
// Created by Carbs0126 on 2023/12/19.
//

#include "INIObject.h"

void INIObject::addSection(INISectionObject *section) {
    if (section == nullptr) {
        return;
    }
    this->orderedSectionsName.push_back(section->getName());
    this->sectionsMap.insert(std::make_pair(section->getName(), section));
}

INISectionObject *INIObject::getSection(string sectionName) {
    if (sectionName.length() == 0 || !this->sectionsMap.contains(sectionName)) {
        return nullptr;
    }
    return this->sectionsMap[sectionName];
}

std::map<string, INISectionObject *> *INIObject::getSectionMap() {
    return &this->sectionsMap;
}

std::vector<string> *INIObject::getOrderedSectionsName() {
    return &this->orderedSectionsName;
}

std::vector<string> INIObject::generateStringLines() {
    vector<IINIContent *> iniContentLines;
    for (auto sectionName: this->orderedSectionsName) {
        if (this->sectionsMap.contains(sectionName)) {
            INISectionObject *iniSectionObject = this->sectionsMap[sectionName];
            vector<IINIContent *> oneSectionLines = iniSectionObject->generateContentLines();
            if (!oneSectionLines.empty()) {
                for (auto *p: oneSectionLines) {
                    if (p != nullptr) {
                        iniContentLines.push_back(p);
                    }
                }
            }
        }
    }

    std::sort(iniContentLines.begin(), iniContentLines.end(), [](IINIContent *a, IINIContent *b) -> bool {
        if (a == nullptr || b == nullptr) {
            return 0;
        }
        INIPosition *iniPositionA = a->getPosition();
        INIPosition *iniPositionB = b->getPosition();
        // 将 position 为空的元素排到最后
        if (iniPositionA == nullptr) {
            return 1;
        }
        if (iniPositionB == nullptr) {
            return -1;
        }
        int deltaLineNumber = iniPositionA->lineNumber - iniPositionB->lineNumber;
        if (deltaLineNumber != 0) {
            return deltaLineNumber < 0;
        }
        return iniPositionA->charBegin < iniPositionB->charBegin;
    });

    std::vector<string> stringlines;
    string sbOneLine;
    int preLineNumber = -1;
    int curLineNumber = -1;
    for (IINIContent *iiniContent : iniContentLines) {
        if (iiniContent == nullptr) {
            continue;
        }
        INIPosition *curINIPosition = iiniContent->getPosition();
        if (curINIPosition == nullptr) {
            if (sbOneLine.length() > 0) {
                stringlines.push_back(sbOneLine);
                sbOneLine.clear();
            }
            stringlines.push_back(iiniContent->toINIOutputString());
            continue;
        }
        curLineNumber = curINIPosition->lineNumber;
        if (preLineNumber != curLineNumber) {
            if (preLineNumber > -1) {
                stringlines.push_back(sbOneLine);
                sbOneLine.clear();
            }
            int lineDelta = curLineNumber - preLineNumber;
            if (lineDelta > 1) {
                // 中间有空行
                for (int i = 0; i < lineDelta - 1; ++i) {
                    stringlines.push_back("");
                }
            }
            sbOneLine.append(iiniContent->toINIOutputString());
        } else {
            sbOneLine.append(iiniContent->toINIOutputString());
        }
        preLineNumber = curLineNumber;
    }
    stringlines.push_back(sbOneLine);
    return stringlines;
}