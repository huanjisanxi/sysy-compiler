#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include "koopa.h"

extern std::string str;

class BaseAST;
class CompUnitAST;
class FuncDef;
class FuncTypeAST;
class BlockAST;
class StmtAST;
class ExprAST;
class UnaryExprAST;
class PrimaryExprAST;
class AddExprAST;
class MulExprAST;
class LOrExpr;
class LAndExpr;
class EqExpr;
class RelExpr;

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
    std::unique_ptr<BaseAST> expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class ExprAST : public BaseAST{
public:

    std::unique_ptr<BaseAST> lor_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class UnaryExprAST : public BaseAST{
public:
    enum Flag{
        PRIMARY_EXPR=0, //PrimaryExp
        OP_UNARY,   //UnaryOp UnaryExp
    }flag;

    std::string op;
    std::unique_ptr<BaseAST> unary_expr;
    std::unique_ptr<BaseAST> primary_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class PrimaryExprAST : public BaseAST{
public:
    enum Flag{
        NUMBER=0, // Num
        WITH_BRACKETS, // "(" Exp ")"
    }flag;

    std::string number;
    std::unique_ptr<BaseAST> expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class AddExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_MUL=0, // MulExp
        ADD_MUL,    // AddExp Op MulExp;
    }flag;

    std::unique_ptr<BaseAST> mul_expr;
    std::unique_ptr<BaseAST> add_expr;
    std::string op;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class MulExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_UNARY=0, // UnaryExp
        MUL_UNARY,    // MulExp Op UnaryExp;
    }flag;

    std::unique_ptr<BaseAST> unary_expr;
    std::unique_ptr<BaseAST> mul_expr;
    std::string op;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class LOrExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_LAND=0, // LAndExpr
        LOR_LAND,    // LOrExpr "||" LAndExpr;
    }flag;

    std::unique_ptr<BaseAST> land_expr;
    std::string op;
    std::unique_ptr<BaseAST> lor_expr;

    void Dump() const override; 
    std::string koopa_ir() const override;

};

class LAndExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_EQ=0, // EqExpr
        LAND_EQ,    // LAndExpr "&&" EqExpr;
    }flag;
    std::unique_ptr<BaseAST> eq_expr;
    std::string op;
    std::unique_ptr<BaseAST> land_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class EqExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_REL=0, // RelExpr
        EQ_REL,    // EqExpr ("=="|"!=") RelExpr;
    }flag;
    std::unique_ptr<BaseAST> rel_expr;
    std::string op;
    std::unique_ptr<BaseAST> eq_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class RelExprAST : public BaseAST{
public:
    enum Flag{
        ONLY_ADD=0, // AddExpr
        REL_ADD,    // RelExpr ("<"|"<="|">"|">=") AddExpr;
    }flag;
    std::unique_ptr<BaseAST> add_expr;
    std::string op;
    std::unique_ptr<BaseAST> rel_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

