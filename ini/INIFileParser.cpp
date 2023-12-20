//
// Created by Carbs0126 on 2023/12/19.
//

#include "INIFileParser.h"

INIObject *INIFileParser::parseFileToINIObject(string fileName) {

    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open the file.");
    }

    vector<string> content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content.push_back(line);
    }
    inputFile.close();

    std::vector<IINIContent *> iniLines;
    iniLines.reserve(content.size());
    int lineNumber = 0;

    for (string &originLine: content) {
        string trimmedLine = INIUtil::trim(originLine);
        if (trimmedLine.starts_with(';')) {
            // comment
            INIComment *iniComment = new INIComment(originLine,
                                                    new INIPosition(fileName, lineNumber, 0, originLine.length()));
            appendLineContentIntoLineList(iniComment, &iniLines);
        } else if (trimmedLine.starts_with('[')) {
            // section header
            int rightSquareBracketsPosition = trimmedLine.find(']');
            if (rightSquareBracketsPosition < 2 || rightSquareBracketsPosition == std::string::npos) {
                throw std::runtime_error("Right square bracket's position should be greater than 1, now it is " +
                                         rightSquareBracketsPosition);
            }
            string sectionName = trimmedLine.substr(0, rightSquareBracketsPosition + 1);
            if (sectionName.find(';') != std::string::npos) {
                throw std::runtime_error("Section's name should not contain ';' symbol");
            }
            int charBegin = originLine.find('[');
            int charEnd = originLine.find(']');
            INISectionHeader *sectionHeader = new INISectionHeader(sectionName,
                                                                   new INIPosition(fileName, lineNumber, charBegin,
                                                                                   charEnd));
            appendLineContentIntoLineList(sectionHeader, &iniLines);
            checkSemicolon(originLine, charEnd + 1, &iniLines, fileName, lineNumber);
        } else if (trimmedLine.length() == 0) {
            INIEmpty *iniEmpty = new INIEmpty(new INIPosition(fileName, lineNumber, 0, 0));
            appendLineContentIntoLineList(iniEmpty, &iniLines);
        } else {
            // kv
            int indexOfEqualInTrimmedString = trimmedLine.find('=');
            if (indexOfEqualInTrimmedString == 0 || indexOfEqualInTrimmedString == std::string::npos) {
                throw std::runtime_error("Equal's position should be greater than 0");
            }
            int indexOfEqualInOriginString = originLine.find('=');
            string substr = trimmedLine.substr(0, indexOfEqualInTrimmedString);
            string keyName = INIUtil::trim(substr);
            string rightStringOfEqual = trimmedLine.substr(indexOfEqualInTrimmedString + 1);
            string valueNameSB;
            int length = rightStringOfEqual.length();
            if (length > 0) {
                // 0: 过滤前面的空格，还未找到value
                // 1: 正在记录value
                // 2: value结束
                int stat = 0;
                int i = 0;
                for (; i < length; i++) {
                    char c = rightStringOfEqual[i];
                    if (stat == 0) {
                        // 过滤前面的空格
                        if (c == ' ' || c == '\t') {
                            continue;
                        } else {
                            stat = 1;
                            valueNameSB.append(std::string(1, c));
                        }
                    } else if (stat == 1) {
                        // 正在记录value
                        // value中允许有空格
                        if (c == ';') {
                            // 记录 value 结束
                            stat = 2;
                            break;
                        } else {
                            stat = 1;
                            valueNameSB.append(std::string(1, c));
                        }
                    }
                }
                int charBegin = originLine.find(keyName);
                int charEnd = indexOfEqualInOriginString + 1 + i;
                INIKVPair *inikvPair = new INIKVPair(keyName, valueNameSB,
                                                     new INIPosition(fileName, lineNumber, charBegin, charEnd));
                appendLineContentIntoLineList(inikvPair, &iniLines);
                if (i != length) {
                    // 没有到结尾，检测是不是有分号
                    checkSemicolon(originLine, indexOfEqualInOriginString + 1 + i, &iniLines, fileName, lineNumber);
                }
            }
        }
        lineNumber++;
    }
    // 最终解析为一个实体
    INIObject *iniObject = new INIObject();
    // 收集 section 或者 kv 的 comments
    vector<INIComment *> commentsCache;
    // todo new的新对象需要析构
    // 解析完当前的 section ，一次存入
    INISectionObject *currentSectionObject = nullptr;
    // 解析当前的 kvPair
    INIEntryObject *currentEntryObject = nullptr;

    // 0 解析 section 阶段，还没有解析到 section
    // 1 已经解析出 sectionName 阶段，(刚刚解析完 sectionHeader ) 还没有解析到下一个 section
    int parseState = 0;
    IINIContent *preINIContent = nullptr;
    IINIContent *curINIContent = nullptr;

    for (IINIContent *iniContent: iniLines) {
        // INIEmpty 类型
        if (dynamic_cast<INIEmpty *>(iniContent) != nullptr) {
            continue;
        }
        curINIContent = iniContent;

        INIComment *iniComment = dynamic_cast<INIComment *>(iniContent);
        if (iniComment != nullptr) {
            if (parseState == 0) {
                commentsCache.push_back(iniComment);
            } else {
                if (preINIContent == nullptr) {
                    continue;
                }

                if (dynamic_cast<INISectionHeader *>(preINIContent) != nullptr) {
                    if (checkSameLine(preINIContent, curINIContent)) {
                        // 当前 comment 属于 section
                        commentsCache.push_back(iniComment);
                        if (currentSectionObject == nullptr) {
                            currentSectionObject = new INISectionObject();
                        }
                        currentSectionObject->addComments(commentsCache);
                        commentsCache.clear();
                        // 当前 section 的所有 comment 已经结束
                    } else {
                        // 当前 comment 属于当前 section 的 kv 或者下一个 section 的 section
                        if (currentSectionObject == nullptr) {
                            currentSectionObject = new INISectionObject();
                        }
                        currentSectionObject->addComments(commentsCache);
                        commentsCache.clear();
                        commentsCache.push_back(iniComment);
                    }
                } else if (dynamic_cast<INIComment *>(preINIContent) != nullptr) {
                    // comment 累加
                    commentsCache.push_back(iniComment);
                } else if (dynamic_cast<INIKVPair *>(preINIContent) != nullptr) {
                    if (checkSameLine(preINIContent, curINIContent)) {
                        // 当前 comment 属于 kv
                        commentsCache.push_back(iniComment);
                        if (currentEntryObject == nullptr) {
                            // 不走这里
                            currentEntryObject = new INIEntryObject();
                        }
                        currentEntryObject->addComments(commentsCache);
                        if (currentSectionObject == nullptr) {
                            currentSectionObject = new INISectionObject();
                        }
                        currentSectionObject->addEntryObject(currentEntryObject);
                        currentEntryObject = nullptr;
                        commentsCache.clear();
                        // 当前 kv 收尾
                    } else {
                        // 当前 comment 属于当前 section 的下一个 kv 或者下一个 section 的 section
                        commentsCache.clear();
                        commentsCache.push_back(iniComment);
                    }
                }
            }
        } else if (dynamic_cast<INISectionHeader *>(curINIContent) != nullptr) {
            INISectionHeader *iniSectionHeader = (INISectionHeader *) curINIContent;
            if (parseState == 0) {
                // 解析到第一个 section
                parseState = 1;
                currentSectionObject = new INISectionObject();
                currentSectionObject->setSectionHeader(iniSectionHeader);
            } else {
                if (dynamic_cast<INISectionHeader *>(preINIContent) != nullptr) {
                    // 连着两个 section header
                    // 收尾上一个 section header
                    if (currentSectionObject != nullptr) {
                        currentSectionObject->addComments(commentsCache);
                        commentsCache.clear();
                        iniObject->addSection(currentSectionObject);
                    }
                    // 新建 section header
                    currentSectionObject = new INISectionObject();
                    currentSectionObject->setSectionHeader(iniSectionHeader);
                } else if (dynamic_cast<INIComment *>(preINIContent) != nullptr) {
                    if (commentsCache.size() == 0) {
                        // 说明上一个 comment 和其之前的元素是一行，需要收尾上一个 section
                        if (currentSectionObject != nullptr) {
                            iniObject->addSection(currentSectionObject);
                        }
                        currentSectionObject = new INISectionObject();
                        currentSectionObject->setSectionHeader(iniSectionHeader);
                    } else {
                        currentSectionObject = new INISectionObject();
                        currentSectionObject->setSectionHeader(iniSectionHeader);
                        currentSectionObject->addComments(commentsCache);
                        commentsCache.clear();
                    }
                } else if (dynamic_cast<INIKVPair *>(preINIContent) != nullptr) {
                    // 说明上一个 section 结束了，需要收尾
                    if (currentSectionObject != nullptr) {
                        if (currentEntryObject != nullptr) {
                            currentSectionObject->addEntryObject(currentEntryObject);
                            currentEntryObject = nullptr;
                        }
                        iniObject->addSection(currentSectionObject);
                    }
                    currentSectionObject = new INISectionObject();
                    currentSectionObject->setSectionHeader(iniSectionHeader);
                }
            }
        } else if (dynamic_cast<INIKVPair *>(curINIContent) != nullptr) {
            INIKVPair *inikvPair = (INIKVPair *) curINIContent;
            if (parseState == 0) {
                // 没有 section，就出现了 kv，说明格式出错
                throw std::runtime_error("There should be a section header before key-value pairs");
            } else {
                if (dynamic_cast<INISectionHeader *>(preINIContent) != nullptr) {
                    currentEntryObject = new INIEntryObject();
                    currentEntryObject->setKVPair(inikvPair);
                } else if (dynamic_cast<INIComment *>(preINIContent) != nullptr) {
                    if (commentsCache.size() == 0) {
                        // 说明上一行中，comment 是右边的注释，还包含左边的元素
                        // 当上一行的左侧是 section 时，不需要关心 section
                        // 当上一行的左侧是 kv 时，不需要关心当前 section 或者上一个 kv
                        currentEntryObject = new INIEntryObject();
                        currentEntryObject->setKVPair(inikvPair);
                    } else {
                        currentEntryObject = new INIEntryObject();
                        currentEntryObject->setKVPair(inikvPair);
                    }
                } else if (dynamic_cast<INIKVPair *>(preINIContent) != nullptr) {
                    // 把前一个 kv 收尾到 section 中
                    if (currentEntryObject != nullptr) {
                        currentEntryObject->addComments(commentsCache);
                        commentsCache.clear();
                        if (currentSectionObject != nullptr) {
                            currentSectionObject->addEntryObject(currentEntryObject);
                        }
                    }
                    currentEntryObject = new INIEntryObject();
                    currentEntryObject->setKVPair(inikvPair);
                }
            }
        }
        preINIContent = curINIContent;
    }
    // 最后一个元素
    if (currentEntryObject != nullptr) {
        currentEntryObject->addComments(commentsCache);
        commentsCache.clear();
    }
    if (currentSectionObject != nullptr) {
        currentSectionObject->addComments(commentsCache);
        commentsCache.clear();
        if (currentEntryObject != nullptr) {
            currentSectionObject->addEntryObject(currentEntryObject);
            currentEntryObject = nullptr;
        }
        iniObject->addSection(currentSectionObject);
    }
    return iniObject;
}

bool INIFileParser::checkSameLine(IINIContent *preINIContent, IINIContent *curINIContent) {
    if (preINIContent != nullptr && curINIContent != nullptr) {
        INIPosition *prePosition = preINIContent->getPosition();
        INIPosition *curPosition = curINIContent->getPosition();
        return prePosition->lineNumber == curPosition->lineNumber;
    }
    return false;
}

void INIFileParser::appendLineContentIntoLineList(IINIContent *iiniContent, vector<IINIContent *> *iniLines) {
    iniLines->push_back(iiniContent);
}

INIComment *
INIFileParser::checkSemicolon(string originString, int charBegin, vector<IINIContent *> *iniLines, string fileLocation,
                              int lineNumber) {
    string remainStr = originString.substr(charBegin);
    string trimmedRemainStr = INIUtil::trim(remainStr);
    if (trimmedRemainStr.length() > 0) {
        if (trimmedRemainStr.starts_with(';')) {
            INIComment *iniComment = new INIComment(trimmedRemainStr,
                                                    new INIPosition(fileLocation, lineNumber,
                                                                    originString.find(';'), originString.length()));
            appendLineContentIntoLineList(iniComment, iniLines);
            return iniComment;
        } else {
            throw std::runtime_error("Need ';' symbol, but find " + std::string(1, trimmedRemainStr[0]) + " instead");
        }
    }
    return nullptr;
}