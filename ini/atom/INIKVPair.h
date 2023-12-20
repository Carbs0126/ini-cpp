//
// Created by Carbs0126 on 2023/12/18.
//

#ifndef INI_CPP_INIKVPAIR_H
#define INI_CPP_INIKVPAIR_H

#include "../position/INIPosition.h"
#include "interfaces/IINIContent.h"

class INIKVPair : public IINIContent {
public:
    string key;
    string value;
    INIPosition *position;
public:
    INIKVPair(string key, string value, INIPosition *position) : key(key), value(value),
                                                                 position(position) {
    }

    ~ INIKVPair() {
        if (this->position != nullptr) {
            delete this->position;
        }
    }

    INIKVPair(const INIKVPair &) = delete;

    INIKVPair &operator=(const INIKVPair &) = delete;

    INIPosition *getPosition() override;

    string toINIOutputString() override;

    string getDescription();

};


#endif //INI_CPP_INIKVPAIR_H
