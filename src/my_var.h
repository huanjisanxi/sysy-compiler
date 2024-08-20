#pragma once
#include <string>

class MyVar{
public:
    std::string type;
    int val;
    bool is_const;
    int id;
    bool no_init;

    MyVar(){}
    MyVar(std::string _type, int _val, bool _is_const, int _id, bool _no_init=false)
        : type(_type), val(_val), is_const(_is_const), id(_id), no_init(_no_init) {}
};