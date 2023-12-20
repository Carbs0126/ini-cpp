//
// Created by Carbs0126 on 2023/12/18.
//

#include "INIKVPair.h"

INIPosition *INIKVPair::getPosition() {
    return this->position;
}

string INIKVPair::toINIOutputString() {
    if (this->key.length() == 0) {
        throw std::runtime_error("Key of INIEntry should not be empty");
    }
    return this->key + "=" + this->value;
};

string INIKVPair::getDescription() {
    string des;
    des.append("INIKVPair{key='");
    des.append(this->key);
    des.append("\'");
    des.append(", value='");
    des.append(this->value);
    des.append("\'");
    des.append(", iniPosition=");
    des.append(this->position->getDescription());
    des.append("}");
    return std::move(des);
}
