#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include "koopa.h"

class BaseAST;
class CompUnitAST;
class FuncDef;
class FuncTypeAST;
class BlockAST;
class StmtAST;

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;

    virtual void Dump() const = 0;  
    virtual std::string koopa_ir() const = 0;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
public:
    // 用智能指针管理对象
    std::unique_ptr<BaseAST> func_def;

    void Dump() const override;
    std::string koopa_ir() const override;
};

// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class FuncTypeAST : public BaseAST{
public:
    std::string type;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class BlockAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> stmt;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class StmtAST : public BaseAST{
public:
    std::string num;

    void Dump() const override;
    std::string koopa_ir() const override;
};

