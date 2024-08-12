#include "ast.h"

int block_cnt = 0;
int cnt;

void CompUnitAST::Dump() const  {
    std::cout << "CompUnitAST { ";
    func_def->Dump();
    std::cout << " }";
}

void FuncDefAST::Dump() const  {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();
    std::cout << " }";
}

void FuncTypeAST::Dump() const  {
    std::cout << "FuncTypeAST { ";
    std::cout << type ;
    std::cout << " }";
}

void BlockAST::Dump() const  {
    std::cout << "BlockAST { ";
    stmt->Dump();
    std::cout << " }";
}

void StmtAST::Dump() const  {
    std::cout << "StmtAST { ";
    std::cout << num;
    std::cout << " }";
}

std::string CompUnitAST::koopa_ir() const {
    func_def->koopa_ir();
    return "";
}

std::string FuncDefAST::koopa_ir() const {
    str += "fun @"+ident+"(): ";
    func_type->koopa_ir();
    str += " {\n";
    str += "%entry:\n";
    block->koopa_ir();
    str += "}\n";
    return "";
}

std::string FuncTypeAST::koopa_ir() const {
    if(type == "int"){
        str += "i32";
    } 
    return "";
}

std::string BlockAST::koopa_ir() const {
    stmt->koopa_ir();
    return "";
}

std::string StmtAST::koopa_ir() const {
    str += "\tret "+ num + "\n";
    return "";
}