//
// Created by Carbs0126 on 2023/12/17.
//

#include "INIEmpty.h"

INIPosition *INIEmpty::getPosition() {
    return this->position;
}

string INIEmpty::toINIOutputString() {
    return "";
};

string INIEmpty::getDescription() {
    string des;
    des.append("INIEmpty{iniPosition=");
    des.append(this->position->getDescription());
    des.append("}");
    return std::move(des);
}