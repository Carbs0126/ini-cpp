//
// Created by Carbs0126 on 2023/12/16.
//

#ifndef INI_CPP_INICOMMENT_H
#define INI_CPP_INICOMMENT_H

#include "../position/INIPosition.h"
#include "interfaces/IINIContent.h"

using namespace std;

class INIComment : public IINIContent {
public:
    string comment;
    INIPosition *position;
public:
    INIComment(string comment, INIPosition *position) : comment(comment),
                                                        position(position) {
    }

    INIComment(const INIComment &) = delete;

    INIComment &operator=(const INIComment &) = delete;

    ~ INIComment() {
        if (this->position != nullptr) {
            delete this->position;
        }
    }

    INIPosition *getPosition() override;

    string toINIOutputString() override;

    string getDescription();
};


#endif //INI_CPP_INICOMMENT_H
