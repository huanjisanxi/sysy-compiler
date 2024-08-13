#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include "koopa.h"
#include <unordered_map>
#include <vector>
#include <set>

extern std::string str;
extern std::unordered_map<std::string, int> symbol_table;
extern std::set<std::string> const_symbol;
extern int test_val;

class BaseAST;
class CompUnitAST;
class FuncDef;
class FuncTypeAST;
class BlockAST;
class BlockItemAST;
class StmtAST;
class BaseExprAST;
class ExprAST;
class UnaryExprAST;
class PrimaryExprAST;
class AddExprAST;
class MulExprAST;
class LOrExpr;
class LAndExpr;
class EqExpr;
class RelExpr;
class LValAST;
class DeclAST;
class ConstDeclAST;
class ConstDef;
class ConstInitValAST;
class ConstExprAST;

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
    // std::unique_ptr<BaseAST> block_item;
  std::vector<std::unique_ptr<BaseAST>> block_item_list;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class BlockItemAST : public BaseAST{
public:
    enum Flag{
        STMT=0, // Stmt
        DECL, // Decl
    }flag;

    std::unique_ptr<BaseAST> decl;
    std::unique_ptr<BaseAST> stmt;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class StmtAST : public BaseAST{
public:
    
    std::unique_ptr<BaseExprAST> expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class BaseExprAST : public BaseAST{
public:
    int val;

    BaseExprAST(){}
    BaseExprAST(int val) : val(val) {}
    BaseExprAST(const BaseExprAST& other) : val(other.val) {}
    int getVal() const {
        return val;
    }
};

class ExprAST : public BaseExprAST{
public:

    std::unique_ptr<BaseExprAST> lor_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class UnaryExprAST : public BaseExprAST{
public:
    enum Flag{
        PRIMARY_EXPR=0, //PrimaryExp
        OP_UNARY,   //UnaryOp UnaryExp
    }flag;

    std::string op;
    std::unique_ptr<BaseExprAST> unary_expr;
    std::unique_ptr<BaseExprAST> primary_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class PrimaryExprAST : public BaseExprAST{
public:
    enum Flag{
        NUMBER=0, // Num
        WITH_BRACKETS, // "(" Exp ")"
        LVAL, // Ident
    }flag;

    std::string number;
    std::unique_ptr<BaseExprAST> expr;
    std::unique_ptr<BaseAST> lval;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class AddExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_MUL=0, // MulExp
        ADD_MUL,    // AddExp Op MulExp;
    }flag;

    std::unique_ptr<BaseExprAST> mul_expr;
    std::unique_ptr<BaseExprAST> add_expr;
    std::string op;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class MulExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_UNARY=0, // UnaryExp
        MUL_UNARY,    // MulExp Op UnaryExp;
    }flag;

    std::unique_ptr<BaseExprAST> unary_expr;
    std::unique_ptr<BaseExprAST> mul_expr;
    std::string op;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class LOrExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_LAND=0, // LAndExpr
        LOR_LAND,    // LOrExpr "||" LAndExpr;
    }flag;

    std::unique_ptr<BaseExprAST> land_expr;
    std::string op;
    std::unique_ptr<BaseExprAST> lor_expr;

    void Dump() const override; 
    std::string koopa_ir() const override;

};

class LAndExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_EQ=0, // EqExpr
        LAND_EQ,    // LAndExpr "&&" EqExpr;
    }flag;
    std::unique_ptr<BaseExprAST> eq_expr;
    std::string op;
    std::unique_ptr<BaseExprAST> land_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class EqExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_REL=0, // RelExpr
        EQ_REL,    // EqExpr ("=="|"!=") RelExpr;
    }flag;
    std::unique_ptr<BaseExprAST> rel_expr;
    std::string op;
    std::unique_ptr<BaseExprAST> eq_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class RelExprAST : public BaseExprAST{
public:
    enum Flag{
        ONLY_ADD=0, // AddExpr
        REL_ADD,    // RelExpr ("<"|"<="|">"|">=") AddExpr;
    }flag;
    std::unique_ptr<BaseExprAST> add_expr;
    std::string op;
    std::unique_ptr<BaseExprAST> rel_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class LValAST : public BaseExprAST{
public:
    std::string ident;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class DeclAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> const_decl;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class ConstDeclAST : public BaseAST{
public:
    std::string btype;
    // std::unique_ptr<BaseAST> const_def;
    std::vector<std::unique_ptr<BaseAST>> const_def_list;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class ConstDefAST : public BaseAST{
public:
    std::string ident;
    std::unique_ptr<BaseAST> const_init_val;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class ConstInitValAST : public BaseExprAST{
public:
    std::unique_ptr<BaseExprAST> const_expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};

class ConstExprAST : public BaseExprAST{
public:
    std::unique_ptr<BaseExprAST> expr;

    void Dump() const override;
    std::string koopa_ir() const override;
};