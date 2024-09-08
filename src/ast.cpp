#include "ast.h"



// for Dump

void show_table();
int ident_floor(std::string ident);
int ident_id(std::string ident);

void CompUnitAST::Dump() const  {
    std::cout << "CompUnitAST { ";
    // func_def->Dump();
    std::cout << " }";
}

void FuncDefAST::Dump() const  {
    std::cout << "FuncDefAST { ";
    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();
    std::cout << " }";
}

void FuncParamAST::Dump() const {

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
        case CALL:
            break;
    }
    std::cout << " }";
}

void CallParamAST::Dump() const{

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
    str+="decl @getint(): i32\ndecl @getch(): i32\ndecl @getarray(*i32): i32\ndecl @putint(i32)\ndecl @putch(i32)\ndecl @putarray(i32, *i32)\ndecl @starttime()\ndecl @stoptime()\n\n";
    func_ret["getint"]=true;
    func_ret["getch"]=true;
    func_ret["getarray"]=true;
    for(auto& item : unit_list){
        item->koopa_ir();
    }
    return "";
}

std::string FuncDefAST::koopa_ir() const {
    std::unordered_map<std::string, MyVar> next_table;
    symbol_tables.push_back(next_table);
    block_num++;
    now_func=ident;
    str += "fun @"+ident+"(";
    std::vector<std::string> ident_list;
    if(func_param_list.size()!= 0){
        for(int i=0;i<func_param_list.size();++i){
            std::string t = func_param_list[i]->koopa_ir();
            ident_list.push_back(t);
            if(i!=func_param_list.size()-1)
                str += ", ";
        }
    }
    str += ")";
    std::string ttype=func_type->koopa_ir();
    if(ttype=="int"){
        func_ret[ident] = true;
    }
    str += " {\n";
    std::string block_name = "%entry";
    str += block_name+":\n";
    for(auto ident : ident_list){
        symbol_tables[block_num][ident] = MyVar("int", 0, false, ident_cnt++, true);
        str+="\t%"+ident+"_"+std::to_string(ident_id(ident))+" = alloc i32\n";
        str+="\tstore @"+ident+", %"+ident+"_"+std::to_string(ident_id(ident))+"\n";
    }
    now_block = block_name;
    block_end[now_block] = false;
    block->koopa_ir();
    if(!has_ret[ident]){
        str += "\tret ";
        if(ttype=="int"){
            str+="0\n";
        }
        else{
            str+="\n";
        }
    }
    str += "}\n";
    symbol_tables.pop_back();
    block_num--;
    str+="\n";
    return "";
}

std::string FuncParamAST::koopa_ir() const{
    str+="@"+ident;
    if(btype=="int")
        str += ": i32";
    else if(btype=="void")
        ;
    return ident;
}

std::string FuncTypeAST::koopa_ir() const {
    if(type == "int"){
        str += ": i32";
        return "int";
    } 
    return "void";
}

std::string BlockAST::koopa_ir() const {
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
    if(block_end[now_block])
        return "";
    std::string ret="";
    if(flag == RETURN){
        auto res = expr->koopa_ir();
        str += "\tret " + res + "\n";
        block_end[now_block] = true;
        has_ret[now_func]=true;
    }
    else if (flag == ASSIGN){
        std::string ident = lval->koopa_ir();
        std::string id = std::to_string(ident_id(ident));
        std::string val = expr->koopa_ir();
        symbol_tables[ident_floor(ident)][ident].val = expr->getVal();
        auto p=(LeftLValAST*)lval.get();
        if(p->flag==LeftLValAST::IDENT)
            str += "\tstore " + val + ", %" + ident + "_" + id + "\n";
        else
            str += "\tstore " + val + ", " + ident + "\n";
    }
    else if(flag == BLOCK){
        std::unordered_map<std::string, MyVar> next_table;
        symbol_tables.push_back(next_table);
        block_num++;
        block->koopa_ir();
        symbol_tables.pop_back();
        block_num--;
    }
    else if(flag==EXPR){
        expr->koopa_ir();
    }
    else if(flag==RETURN_VOID){
        str += "\tret\n";
        block_end[now_block] = true;
        has_ret[now_func]=true;
    }
    else if(flag==IF){
        std::string val = cond->koopa_ir();
        std::string now_if = std::to_string(block_cnt);
        block_cnt ++;
        std::string then_block_name = "%then_"+now_if;
        std::string end_block_name = "%end_"+now_if;
        str += "\tbr " + val + ", " + then_block_name +", "+ end_block_name+"\n";
        block_end[now_block] = true;
        str += "\n";
        str += then_block_name+":\n";
        now_block = then_block_name;
        block_end[then_block_name] = false;
        if_stmt->koopa_ir();
        if(!block_end[now_block]){
            str += "\tjump %end_"+now_if+"\n";
            block_end[now_block] = true;
        }
        str += "\n";
        now_block = end_block_name;
        block_end[end_block_name] = false;
        str += end_block_name+":\n";
    }
    else if(flag==IF_ELSE){
        std::string val = cond->koopa_ir();
        std::string now_if= std::to_string(block_cnt);
        block_cnt++;
        std::string then_block_name = "%then_"+now_if;
        std::string else_block_name = "%else_"+now_if;
        std::string end_block_name = "%end_"+now_if;
        str += "\tbr " + val + ", "+then_block_name+", "+else_block_name+"\n";
        str += "\n";
        str += then_block_name+":\n";
        now_block=then_block_name;
        block_end[then_block_name] = false;
        if_stmt->koopa_ir();
        if(!block_end[now_block]){
            str += "\tjump %end_"+now_if+"\n";
            block_end[now_block] = true;
        }
        str += "\n";
        str += else_block_name+":\n";
        now_block = else_block_name;
        block_end[else_block_name] = false;
        else_stmt->koopa_ir();

        if(!block_end[now_block]){
            str += "\tjump %end_"+now_if+"\n";
            block_end[now_block] = true;
        }
        str += "\n";
        now_block = end_block_name;
        block_end[end_block_name] = false;
        str += "%end_"+now_if+":\n";
    }
    else if(flag==WHILE){
        std::string now_while = std::to_string(block_cnt);
        nested_while_stack.push_back(now_while);
        block_cnt++;
        std::string entry_name = "%while_entry_"+now_while;
        std::string body_name = "%while_body_"+now_while;
        std::string end_name = "%while_end_"+now_while;
        str += "\tjump "+entry_name+"\n";
        str += "\n";
        str += entry_name+":\n";
        std::string val = cond->koopa_ir();
        str += "\tbr " + val + ", " + body_name + ", " + end_name + "\n";
        str += "\n";
        str += body_name+":\n";
        now_block = body_name;
        block_end[body_name] = false;
        while_stmt->koopa_ir();
        if(!block_end[now_block]){
            str += "\tjump "+entry_name+"\n";
            block_end[now_block] = true;
        }
        str += "\n";
        now_block = end_name;
        block_end[end_name] = false;
        str += end_name+":\n";
        nested_while_stack.pop_back();
    }
    else if(flag==BREAK){
        str += "\tjump %while_end_" + nested_while_stack.back() + "\n";
        block_end[now_block] = true;
    }
    else if(flag==CONTINUE){
        str += "\tjump %while_entry_" + nested_while_stack.back() + "\n";
        block_end[now_block] = true;
    }
    return ret;
}

std::string ExprAST::koopa_ir() const {
    auto res = lor_expr->koopa_ir();
    return res;
}

std::string UnaryExprAST::koopa_ir() const {
    std::string ret;
    std::vector<std::string> tmp;
    switch(flag){
        case PRIMARY_EXPR:
            ret = primary_expr->koopa_ir();  
            break;
        case CALL:
            for(auto& param : call_expr_list){
                tmp.push_back(param->koopa_ir());
            }
            str+="\t";
            if(func_ret[call_ident]){
                ret = "%"+std::to_string(cnt++);
                str+=ret+" = ";
            }
            str += "call @"+call_ident+"(";
            for(int i=0;i<tmp.size();++i){
                str+=tmp[i];
                if(i!=tmp.size()-1)
                    str+=", ";
            }
            str += ")\n";
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

std::string CallParamAST::koopa_ir() const{
    return expr->koopa_ir();
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
            std::string now_if = std::to_string(block_cnt);
            block_cnt++;

            ret = "@result_" + now_if;
            str += "\t" + ret + " = alloc i32\n";
            str += "\tstore 1, " + ret + "\n"; 

            auto res1 = lor_expr->koopa_ir();
            std::string then_block_name = "%then_"+now_if;
            std::string end_block_name = "%end_"+now_if;
            std::string cond = "%" + std::to_string(cnt++);
            str += "\t" + cond + " = eq " + res1 + ", 0\n";
            str += "\tbr " + cond + ", " + then_block_name + ", " + end_block_name + "\n";
            str += "\n";
            
            str += then_block_name+":\n";
            now_block = then_block_name;
            block_end[then_block_name] = false;
            auto res2 = land_expr->koopa_ir();
            std::string tmp = "%" + std::to_string(cnt++);
            str += "\t" + tmp + " = ne " + res2 + ", 0\n";
            str += "\tstore " + tmp + ", "+ ret + "\n";
            str += "\tjump "+end_block_name+"\n";
            block_end[now_block] = true;
            str += "\n";

            now_block = end_block_name;
            block_end[end_block_name] = false;
            str += end_block_name+":\n";
            auto old_ret = ret;
            ret = "%" + std::to_string(cnt++);
            str += "\t" + ret + " = load " + old_ret + "\n";
            break;
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
            std::string now_if = std::to_string(block_cnt);
            block_cnt++;

            ret = "@result_" + now_if;
            str += "\t" + ret + " = alloc i32\n";
            str += "\tstore 0, " + ret + "\n"; 

            auto res1 = land_expr->koopa_ir();
            std::string then_block_name = "%then_"+now_if;
            std::string end_block_name = "%end_"+now_if;
            std::string cond = "%" + std::to_string(cnt++);
            str += "\t" + cond + " = ne " + res1 + ", 0\n";
            str += "\tbr " + cond + ", " + then_block_name + ", " + end_block_name + "\n";
            str += "\n";
            
            str += then_block_name+":\n";
            now_block = then_block_name;
            block_end[then_block_name] = false;
            auto res2 = eq_expr->koopa_ir();
            std::string tmp = "%" + std::to_string(cnt++);
            str += "\t" + tmp + " = ne " + res2 + ", 0\n";
            str += "\tstore " + tmp + ", "+ ret + "\n";
            str += "\tjump "+end_block_name+"\n";
            block_end[now_block] = true;
            str += "\n";

            now_block = end_block_name;
            block_end[end_block_name] = false;
            str += end_block_name+":\n";
            auto old_ret = ret;
            ret = "%" + std::to_string(cnt++);
            str += "\t" + ret + " = load " + old_ret + "\n";
            break;      
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
    if(flag==IDENT){
        if(symbol_tables[ident_floor(ident)][ident].is_const==true){
            return std::to_string(symbol_tables[ident_floor(ident)][ident].val);
        }
        else{
            std::string ret = "%" + std::to_string(cnt++);
            str += "\t" + ret + " = load %" + ident + "_" + std::to_string(ident_id(ident)) + "\n"; 
            return ret;
        }
    }
    else{
        std::string tmp = "%" + std::to_string(cnt++);
        std::string idx_ret = idx->koopa_ir();
        str += "\t" + tmp + " = getelemptr %" + ident+"_"+std::to_string(ident_id(ident)) + ", " + idx_ret + "\n"; 
        std::string ret = "%" + std::to_string(cnt++);
        str += "\t" + ret + " = load " + tmp + "\n";
        return ret;
    }
}

std::string LeftLValAST::koopa_ir() const {
    if(flag==IDENT)
        return ident;
    else{
        //TODO
        std::string tmp = "%" + std::to_string(cnt++);
        std::string idx_ret = idx->koopa_ir();
        str += "\t" + tmp + " = getelemptr %" + ident+"_"+std::to_string(ident_id(ident)) + ", " + idx_ret + "\n"; 
        return tmp;
    }
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
    if(flag==VAR){
        symbol_tables[block_num][ident] = MyVar("int", const_init_val->getVal(), true, ident_cnt++);
    }
    else if(flag==ARRAY){
        symbol_tables[block_num][ident] = MyVar("array", 0, false, ident_cnt++);
        symbol_tables[block_num][ident].array.resize(len->getVal(),0);
        auto p = (ConstInitValAST*)const_init_val.get();
        int init_len = p->const_expr_list.size();
        for(int i=0;i<init_len;++i){
            symbol_tables[block_num][ident].array[i]=p->const_expr_list[i]->getVal();
        }

        if(ident_floor(ident)!=0){
            str += "\t%" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc [i32, ";
            str += std::to_string(len->getVal()) + "]\n";
            for(int i=0;i<len->getVal();++i){
                std::string tmp = "%" + std::to_string(cnt++);
                str += "\t"+ tmp + " = getelemptr %" + ident +"_" + std::to_string(ident_id(ident))+", "+ std::to_string(i)+"\n";
                if(i<init_len){
                    str += "\tstore " + std::to_string(p->const_expr_list[i]->getVal()) + ", " + tmp + "\n";
                }
                else{
                    str += "\tstore 0, " +tmp+"\n";
                }
            }
        }
        else{
            str += "global %" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc [i32, ";
            str += std::to_string(len->getVal()) + "], {";
            for(int i=0;i<len->getVal();++i){
                if(i<init_len)
                    str += std::to_string(p->const_expr_list[i]->getVal());
                else
                    str += "0";
                if(i!=len->getVal()-1) str += ", ";
            }
            str += "}\n";
        }
    }
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
    if(flag==VAR){
        if(is_init){
            int val = var_init_val->getVal();
            symbol_tables[block_num][ident] = MyVar("int", val, false, ident_cnt++); 
        }
        else{
            symbol_tables[block_num][ident] = MyVar("int", 0, false, ident_cnt++, true);
        }

        if(ident_floor(ident)!=0){
            std::string type = "i32";
            str += "\t%" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc " + type + '\n';
            if(is_init){
                str += "\tstore " + var_init_val->koopa_ir() + ", %" + ident + "_" + std::to_string(ident_id(ident)) + "\n";
            }
        }
        else{
            str += "global %" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc i32, ";
            if(is_init){
                str+= var_init_val->koopa_ir() + '\n';
            } 
            else{
                str+= "0\n";
            }
        }
    }
    else if(flag==ARRAY){
        symbol_tables[block_num][ident] = MyVar("array", 0, false, ident_cnt++);
        symbol_tables[block_num][ident].array.resize(len->getVal(),0);
        auto p = (VarInitValAST*)var_init_val.get();
        int init_len = p->expr_list.size();
        for(int i=0;i<init_len;++i){
            symbol_tables[block_num][ident].array[i]=p->expr_list[i]->getVal();
        }

        if(ident_floor(ident)!=0){
            str += "\t%" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc [i32, ";
            str += std::to_string(len->getVal()) + "]\n";
            for(int i=0;i<len->getVal();++i){
                std::string tmp = "%" + std::to_string(cnt++);
                str += "\t"+ tmp + " = getelemptr %" + ident +"_" + std::to_string(ident_id(ident))+", "+ std::to_string(i)+"\n";
                if(i<init_len){
                    str += "\tstore " + p->expr_list[i]->koopa_ir() + ", " + tmp + "\n";
                }
                else{
                    str += "\tstore 0, " +tmp+"\n";
                }
            }
        }
        else{
            str += "global %" + ident + "_" + std::to_string(ident_id(ident)) + " = alloc [i32, ";
            str += std::to_string(len->getVal()) + "], {";
            for(int i=0;i<len->getVal();++i){
                if(i<init_len)
                    str += std::to_string(p->expr_list[i]->getVal());
                else
                    str += "0";
                if(i!=len->getVal()-1) str += ", ";
            }
            str += "}\n";
        }
    }
    return "";
}

std::string VarInitValAST::koopa_ir() const {
    return expr->koopa_ir();
}

int ident_floor(std::string ident){

    for(int i = block_num; i>=0; i--){
        if(symbol_tables[i].find(ident)!=symbol_tables[i].end()){
            return i;
        }
    }
    return block_num;
}

int ident_id(std::string ident){
    for(int i = block_num; i>=0; i--){
        if(symbol_tables[i].find(ident)!=symbol_tables[i].end()){
            return symbol_tables[i][ident].id;
        }
    }
    return 0;
}

void show_table(){
    for(int i=0;i<=block_num;i++){
        for(auto it = symbol_tables[i].begin(); it!= symbol_tables[i].end(); it++){
            std::cout<<it->first<<" : "<<it->second.val<<"  "<<it->second.type<<"  "<<it->second.is_const<<std::endl;
        }
    }
    std::cout<<std::endl;
}