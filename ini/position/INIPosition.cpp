//
// Created by Carbs0126 on 2023/12/16.
//
#include "INIPosition.h"
#include <string>

using namespace std;

string INIPosition::getDescription() {
    string des;
    des.append("INIPosition{fileLocation='");
    des.append(this->fileLocation);
    des.append("\'");
    des.append(", lineNumber=");
    des.append(to_string(this->lineNumber));
    des.append(", charBegin=");
    des.append(to_string(this->charBegin));
    des.append(", charEnd=");
    des.append(to_string(this->charEnd));
    des.append("}");
    return std::move(des);
}