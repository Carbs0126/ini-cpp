cmake_minimum_required(VERSION 3.25)
project(ini_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(ini_cpp main.cpp ini/atom/interfaces/IINIContent.h ini/position/INIPosition.h ini/position/INIPosition.cpp ini/atom/INIComment.cpp ini/atom/INIComment.h ini/atom/INIEmpty.cpp ini/atom/INIEmpty.h ini/atom/INIKVPair.cpp ini/atom/INIKVPair.h ini/atom/INISectionHeader.cpp ini/atom/INISectionHeader.h ini/entity/INISectionObject.cpp ini/entity/INISectionObject.h ini/entity/INIEntryObject.cpp ini/entity/INIEntryObject.h ini/entity/INIObject.cpp ini/entity/INIObject.h ini/INIFileParser.cpp ini/INIFileParser.h ini/INIFileGenerator.cpp ini/INIFileGenerator.h ini/INIUtil.cpp ini/INIUtil.h)
