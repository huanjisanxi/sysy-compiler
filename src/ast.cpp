#include "ast.h"

int block_cnt = 0;
static int cnt=0;

// for Dump

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
    for (auto& item : block_item_list) {
        item->Dump();
        std::cout << " ,";
    }
    std::cout << " }";
}

void BlockItemAST::Dump() const  {
    std::cout << "BlockItemAST { ";
    switch(flag){
        case DECL:
            decl->Dump();
            break;
        case STMT:
            stmt->Dump();
            break;
    }
    std::cout << " }";
}

void StmtAST::Dump() const  {
    std::cout << "StmtAST { ";
    expr->Dump();
    std::cout << " }";
}

void ExprAST::Dump() const {
    std::cout << "ExprAST { ";
    lor_expr->Dump();
    std::cout << " }";
}

void UnaryExprAST::Dump() const {
    std::cout << "UnaryExprAST { ";
    switch(flag){
        case PRIMARY_EXPR:
            primary_expr->Dump();
            break;
        case OP_UNARY:
            std::cout << " " << op << " ";
            unary_expr->Dump();
            break;
    }
    std::cout << " }";
}

void PrimaryExprAST::Dump() const {
    std::cout << "PrimaryExprAST { ";
    switch(flag){
        case NUMBER:
            std::cout << number;
            break;
        case WITH_BRACKETS:
            expr->Dump();
            break;
        case LVAL:
            //TODO
            break;
    }
    std::cout << " }";
}

void AddExprAST::Dump() const {
    std::cout << "AddExprAST { ";
    switch(flag){
        case ONLY_MUL:
            mul_expr->Dump();
            break;
        case ADD_MUL:
            add_expr->Dump();
            std::cout << " " << op << " ";
            mul_expr->Dump();
            break;
    }
    std::cout << " }";
}

void MulExprAST::Dump() const {
    std::cout << "MulExprAST { ";
    switch(flag){
        case ONLY_UNARY:
            unary_expr->Dump();
            break;
        case MUL_UNARY:
            mul_expr->Dump();
            std::cout << " " << op << " ";
            unary_expr->Dump();
            break;
    }
    std::cout << " }";
}

void LOrExprAST::Dump() const {
    land_expr->Dump();
}

void LAndExprAST::Dump() const {
    eq_expr->Dump();
}

void EqExprAST::Dump() const {
    rel_expr->Dump();   
}

void RelExprAST::Dump() const {
    add_expr->Dump();
}

void LValAST::Dump() const {
    
}

void LeftLValAST::Dump() const {
}

void DeclAST::Dump() const {
    const_decl->Dump();
}

void ConstDeclAST::Dump() const {
    for(auto& const_def : const_def_list)
        const_def->Dump();
}

void ConstDefAST::Dump() const {
    const_init_val->Dump();
}

void ConstInitValAST::Dump() const {
    const_expr->Dump();
}

void ConstExprAST::Dump() const {
    expr->Dump();
}

void VarDeclAST::Dump() const {
    for(auto& var_def : var_def_list)
        var_def->Dump();
}

void VarDefAST::Dump() const {
    //TODO
    var_init_val->Dump();
}


void VarInitValAST::Dump() const {
    expr->Dump();
}

// for koopa_ir

std::string CompUnitAST::koopa_ir() const {
    func_def->koopa_ir();
    return "";
}

std::string FuncDefAST::koopa_ir() const {
    str += "fun @"+ident+"(): ";
    func_type->koopa_ir();
    str += " {\n";
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
    str += "%entry:\n";
    for (auto& item: block_item_list){
        item->koopa_ir();
    }
    return "";
}

std::string BlockItemAST::koopa_ir() const {
    switch(flag){
        case DECL:
            decl->koopa_ir();
            break;
        case STMT:
            stmt->koopa_ir();
            break;
    }
    return "";
}

std::string StmtAST::koopa_ir() const {
    if(flag == RETURN){
        auto res = expr->koopa_ir();
        str += "\tret " + res + "\n";
    }
    else if (flag == ASSIGN){
        std::string ident = lval->koopa_ir();
        std::string val = expr->koopa_ir();
        str += "\tstore " + val + ", @" + ident + "\n";
        symbol_table[ident].val = expr->getVal();
    }
    return "";
}

std::string ExprAST::koopa_ir() const {
    auto res = lor_expr->koopa_ir();
    return res;
}

std::string UnaryExprAST::koopa_ir() const {
    std::string ret;
    switch(flag){
        case PRIMARY_EXPR:
            ret = primary_expr->koopa_ir();  
            break;
        case OP_UNARY:
            auto res = unary_expr->koopa_ir();
            if(op == "+"){
                ret = res;
                break;
            }

            ret = "%"+std::to_string(cnt++);
            if(op == "-"){
                str += "\t" + ret + " = sub 0, " + res + "\n";  
            }
            else if(op == "!"){
                str += "\t" + ret + " = eq 0, " + res + "\n";  
            }
            break;
    }
    return ret;
}

std::string PrimaryExprAST::koopa_ir() const {
    std::string ret;
    switch(flag){
        case NUMBER:
            ret = number;
            break;
        case WITH_BRACKETS:
            ret = expr->koopa_ir();
            break;
        case LVAL:
            ret = lval->koopa_ir();
            break;
    }
    return ret;
}

std::string AddExprAST::koopa_ir() const {
    std::string ret;
    switch(flag){
        case ONLY_MUL:
            ret = mul_expr->koopa_ir();
            break;
        case ADD_MUL:
            auto res1 = add_expr->koopa_ir();
            auto res2 = mul_expr->koopa_ir();
            ret = "%"+std::to_string(cnt++);
            if(op == "+"){
                str += "\t" + ret + " = add " + res1 + ", " + res2 + "\n";  
            }
            else if(op == "-"){
                str += "\t" + ret + " = sub " + res1 + ", " + res2 + "\n";  
            }
            break;
    }
    return ret;
}

std::string MulExprAST::koopa_ir() const { 
    std::string ret;
    switch(flag){
        case ONLY_UNARY:
            ret = unary_expr->koopa_ir();
            break;
        case MUL_UNARY:
            auto res1 = mul_expr->koopa_ir();
            auto res2 = unary_expr->koopa_ir();
            ret = "%"+std::to_string(cnt++);
            if(op == "*"){
                str += "\t" + ret + " = mul " + res1 + ", " + res2 + "\n";  
            }
            else if(op == "/"){
                str += "\t" + ret + " = div " + res1 + ", " + res2 + "\n";  
            }
            else if(op == "%"){
                str += "\t" + ret + " = mod " + res1 + ", " + res2 + "\n";  
            }
            break;
    }
    return ret;
}

std::string LOrExprAST::koopa_ir() const {
    std::string ret;
    switch(flag){
        case ONLY_LAND:
            ret = land_expr->koopa_ir();
            break;
        case LOR_LAND:
            auto res1 = lor_expr->koopa_ir();
            auto res2 = land_expr->koopa_ir();

            std::string temp1 = "%" + std::to_string(cnt++);
            std::string temp2 = "%" + std::to_string(cnt++);
            ret = "%" + std::to_string(cnt++);

            str += "\t" + temp1 + " = ne " + res1 + ", 0\n";
            str += "\t" + temp2 + " = ne " + res2 + ", 0\n";
            str += "\t" + ret + " = or " + temp1 + ", " + temp2 + "\n";
    }
    return ret;
}

std::string LAndExprAST::koopa_ir() const { 
    std::string ret;
    switch(flag){
        case ONLY_EQ:
            ret = eq_expr->koopa_ir();
            break;
        case LAND_EQ:
            auto res1 = land_expr->koopa_ir();
            auto res2 = eq_expr->koopa_ir();

            std::string temp1 = "%" + std::to_string(cnt++);
            std::string temp2 = "%" + std::to_string(cnt++);
            ret = "%" + std::to_string(cnt++);

            str += "\t" + temp1 + " = ne " + res1 + ", 0\n";
            str += "\t" + temp2 + " = ne " + res2 + ", 0\n";
            str += "\t" + ret + " = and " + temp1 + ", " + temp2 + "\n";
    }
    return ret;
}

std::string EqExprAST::koopa_ir() const { 
    std::string ret;
    switch(flag){
        case ONLY_REL:
            ret = rel_expr->koopa_ir();
            break;
        case EQ_REL:
            auto res1 = eq_expr->koopa_ir();
            auto res2 = rel_expr->koopa_ir();
            ret = "%"+std::to_string(cnt++);
            if(op == "=="){
                str += "\t" + ret + " = eq " + res1 + ", " + res2 + "\n";  
            }
            else if(op == "!="){
                str += "\t" + ret + " = ne " + res1 + ", " + res2 + "\n";  
            }
            break;
    }
    return ret;
}

std::string RelExprAST::koopa_ir() const {
    std::string ret;
    switch(flag){
        case ONLY_ADD:
            ret = add_expr->koopa_ir();
            break;
        case REL_ADD:
            auto res1 = rel_expr->koopa_ir();
            auto res2 = add_expr->koopa_ir();
            ret = "%"+std::to_string(cnt++);
            if(op == "<"){
                str += "\t" + ret + " = lt " + res1 + ", " + res2 + "\n";  
            }
            else if(op == ">"){
                str += "\t" + ret + " = gt " + res1 + ", " + res2 + "\n";  
            }
            else if(op == "<="){
                str += "\t" + ret + " = le " + res1 + ", " + res2 + "\n";  
            }
            else if(op == ">="){
                str += "\t" + ret + " = ge " + res1 + ", " + res2 + "\n";  
            }
            break;
    }
    return ret;
}

std::string LValAST::koopa_ir() const {
    if(symbol_table[ident].is_const==true){
        return std::to_string(symbol_table[ident].val);
    }
    else{
        std::string ret = "%" + std::to_string(cnt++);
        str += "\t" + ret + " = load @" + ident + "\n"; 
        return ret;
    }
}

std::string LeftLValAST::koopa_ir() const {
    return ident;
}

std::string DeclAST::koopa_ir() const {
    if(flag==CONST_DECL){
        const_decl->koopa_ir();
    }
    else if(flag==VAR_DECL){
        var_decl->koopa_ir();
    }
    return "";
}

std::string ConstDeclAST::koopa_ir() const {
    for(auto& item: const_def_list){
        item->koopa_ir();
    }
    return "";
}

std::string ConstDefAST::koopa_ir() const {
    symbol_table[ident].val = const_init_val->getVal();
    return "";
}

std::string ConstInitValAST::koopa_ir() const {
    return "";
}

std::string ConstExprAST::koopa_ir() const {
    std::string ret = expr->koopa_ir();
    return ret;
}

std::string VarDeclAST::koopa_ir() const {
    for(auto& item: var_def_list){
        item->koopa_ir();
    }
    return "";
}

std::string VarDefAST::koopa_ir() const {
    std::string type;
    if(symbol_table[ident].type=="int"){
        type = "i32";
    }
    str += "\t@" + ident + " = alloc " + type + '\n';
    if(symbol_table[ident].no_init==false){
        str += "\tstore " + var_init_val->koopa_ir() + ", @" + ident + "\n";
        symbol_table[ident].val = var_init_val->getVal();
    }
    return "";
}

std::string VarInitValAST::koopa_ir() const {
    return expr->koopa_ir();
}