#pragma once
#include <string>

class MyVar{
public:
    std::string type;
    int val;
    bool is_const;
    bool no_init;

    MyVar(){}
    MyVar(std::string _type, int _val, bool _is_const, bool _no_init=false)
        : type(_type), val(_val), is_const(_is_const), no_init(_no_init) {}
};