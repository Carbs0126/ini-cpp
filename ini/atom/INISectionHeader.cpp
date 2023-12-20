//
// Created by Carbs0126 on 2023/12/18.
//

#include "INISectionHeader.h"

INIPosition *INISectionHeader::getPosition() {
    return this->position;
}

string INISectionHeader::toINIOutputString() {
    if (this->name.length() == 0) {
        throw std::runtime_error("Key of INISectionHeader should not be empty");
    }
    return this->name;
};

string INISectionHeader::getDescription() {
    string des;
    des.append("INISectionHeader{name='");
    des.append(this->name);
    des.append("\'");
    des.append(", iniPosition=");
    des.append(this->position->getDescription());
    des.append("}");
    return std::move(des);
}