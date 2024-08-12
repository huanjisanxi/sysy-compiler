#include "ast.h"

int block_cnt = 0;

void CompUnitAST::Dump() const  {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
}

std::string CompUnitAST::koopa_ir() const {
    return func_def->koopa_ir();
}

void FuncDefAST::Dump() const  {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();
    std::cout << " }";
}

std::string FuncDefAST::koopa_ir() const {
    std::string str;
    str += "fun @"+ident+"(): "+func_type->koopa_ir()+" {\n";
    str += "%entry:\n";
    str += block->koopa_ir();
    str += "}\n";
    return str;
}

void FuncTypeAST::Dump() const  {
    std::cout << "FuncTypeAST { ";
    std::cout << type ;
    std::cout << " }";
}

std::string FuncTypeAST::koopa_ir() const {
    if(type == "int"){
        return "i32";
    } 
    return "i32";
}

void BlockAST::Dump() const  {
    std::cout << "BlockAST { ";
    stmt->Dump();
    std::cout << " }";
}

std::string BlockAST::koopa_ir() const {
    return stmt->koopa_ir();
}

void StmtAST::Dump() const  {
    std::cout << "StmtAST { ";
    std::cout << num;
    std::cout << " }";
}

std::string StmtAST::koopa_ir() const {
    return "\tret "+ num + "\n";
}