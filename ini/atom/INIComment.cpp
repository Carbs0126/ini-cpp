//
// Created by Carbs0126 on 2023/12/16.
//

#include "INIComment.h"

INIPosition *INIComment::getPosition() {
    return this->position;
}

string INIComment::toINIOutputString() {
    return this->comment;
};

string INIComment::getDescription() {
    string des;
    des.append("INIComment{comment='");
    des.append(this->comment);
    des.append("\'");
    des.append(", iniPosition=");
    des.append(this->position->getDescription());
    des.append("}");
    return std::move(des);
}

