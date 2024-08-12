%code requires {
  #include <memory>
  #include <string>
  #include "ast.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;

%}

%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
}

%token INT VOID RETURN CONST IF ELSE WHILE BREAK CONTINUE
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt Expr UnaryExpr PrimaryExpr AddExpr MulExpr
%type <ast_val> LOrExpr LAndExpr EqExpr RelExpr
%type <int_val> Number

%%

CompUnit
  : FuncDef {
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->func_def = unique_ptr<BaseAST>($1);
    ast = move(comp_unit);
  }
  ;

FuncDef
  :FuncType IDENT '(' ')' Block{
    auto func_def = new FuncDefAST();
    func_def->func_type = unique_ptr<BaseAST>($1);
    func_def->ident = *unique_ptr<string>($2);
    func_def->block = unique_ptr<BaseAST>($5);
    $$ = func_def;
  }
  ;

FuncType
  : INT{
    auto func_type = new FuncTypeAST();
    func_type->type = string("int");
    $$ = func_type;
  }
  ;

Block
  : '{' Stmt '}' {
    auto block = new BlockAST();
    block->stmt = unique_ptr<BaseAST>($2);
    $$ = block;
  }
  ;

Stmt
  : RETURN Expr ';' {
    auto stmt = new StmtAST();
    stmt->expr = unique_ptr<BaseAST>($2);
    $$ = stmt;
  }
  ;

Expr 
  : LOrExpr {
    auto expr = new ExprAST();
    expr->lor_expr = unique_ptr<BaseAST>($1);
    $$ = expr;
  }
  ;

UnaryExpr
  : PrimaryExpr {
    auto unary_expr = new UnaryExprAST();
    unary_expr->flag=UnaryExprAST::PRIMARY_EXPR;
    unary_expr->primary_expr = unique_ptr<BaseAST>($1);
    $$ = unary_expr;
  }
  | '+' UnaryExpr {
    auto unary_expr = new UnaryExprAST();
    unary_expr->flag=UnaryExprAST::OP_UNARY;
    unary_expr->op = "+";
    unary_expr->unary_expr = unique_ptr<BaseAST>($2);
    $$ = unary_expr;
  }
  | '-' UnaryExpr {
    auto unary_expr = new UnaryExprAST();
    unary_expr->flag=UnaryExprAST::OP_UNARY;
    unary_expr->op = "-";
    unary_expr->unary_expr = unique_ptr<BaseAST>($2);
    $$ = unary_expr;
  }
  | '!' UnaryExpr {
    auto unary_expr = new UnaryExprAST();
    unary_expr->flag=UnaryExprAST::OP_UNARY;
    unary_expr->op = "!";
    unary_expr->unary_expr = unique_ptr<BaseAST>($2);
    $$ = unary_expr;
  }
  ;

PrimaryExpr
  : Number {
    auto primary_expr = new PrimaryExprAST();
    primary_expr->flag=PrimaryExprAST::NUMBER;
    primary_expr->number = to_string($1);
    $$ = primary_expr;
  }
  | '(' Expr ')' {
    auto primary_expr = new PrimaryExprAST();
    primary_expr->flag=PrimaryExprAST::WITH_BRACKETS;
    primary_expr->expr = unique_ptr<BaseAST>($2);
    $$ = primary_expr;
  }
  ;

AddExpr
  : MulExpr {
    auto add_expr = new AddExprAST();
    add_expr->flag = AddExprAST::ONLY_MUL;
    add_expr->mul_expr = unique_ptr<BaseAST>($1);
    $$ = add_expr;
  }
  | AddExpr '+' MulExpr {
    auto add_expr = new AddExprAST();
    add_expr->flag = AddExprAST::ADD_MUL;
    add_expr->add_expr = unique_ptr<BaseAST>($1);
    add_expr->op = "+";
    add_expr->mul_expr = unique_ptr<BaseAST>($3);
    $$ = add_expr;
  }
  | AddExpr '-' MulExpr {
    auto add_expr = new AddExprAST();
    add_expr->flag = AddExprAST::ADD_MUL;
    add_expr->add_expr = unique_ptr<BaseAST>($1);
    add_expr->op = "-";
    add_expr->mul_expr = unique_ptr<BaseAST>($3);
    $$ = add_expr;
  }
  ;

MulExpr
  : UnaryExpr {
    auto mul_expr = new MulExprAST();
    mul_expr->flag = MulExprAST::ONLY_UNARY;
    mul_expr->unary_expr = unique_ptr<BaseAST>($1);
    $$ = mul_expr;
  }
  | MulExpr '*' UnaryExpr {
    auto mul_expr = new MulExprAST();
    mul_expr->flag = MulExprAST::MUL_UNARY;
    mul_expr->mul_expr = unique_ptr<BaseAST>($1);
    mul_expr->op = "*";
    mul_expr->unary_expr = unique_ptr<BaseAST>($3);
    $$ = mul_expr;
  }
  | MulExpr '/' UnaryExpr {
    auto mul_expr = new MulExprAST();
    mul_expr->flag = MulExprAST::MUL_UNARY;
    mul_expr->mul_expr = unique_ptr<BaseAST>($1);
    mul_expr->op = "/";
    mul_expr->unary_expr = unique_ptr<BaseAST>($3);
    $$ = mul_expr;
  }
  | MulExpr '%' UnaryExpr {
    auto mul_expr = new MulExprAST();
    mul_expr->flag = MulExprAST::MUL_UNARY;
    mul_expr->mul_expr = unique_ptr<BaseAST>($1);
    mul_expr->op = "%";
    mul_expr->unary_expr = unique_ptr<BaseAST>($3);
    $$ = mul_expr;
  }
  ;

LOrExpr
  : LAndExpr {
    auto lor_expr = new LOrExprAST();
    lor_expr->flag = LOrExprAST::ONLY_LAND;
    lor_expr->land_expr = unique_ptr<BaseAST>($1);
    $$ = lor_expr;
  }
  | LOrExpr '|' '|' LAndExpr {
    auto lor_expr = new LOrExprAST();
    lor_expr->flag = LOrExprAST::LOR_LAND;
    lor_expr->lor_expr = unique_ptr<BaseAST>($1);
    lor_expr->op = "||";
    lor_expr->land_expr = unique_ptr<BaseAST>($4);
    $$ = lor_expr;
  }
  ;

LAndExpr
  : EqExpr {
    auto land_expr = new LAndExprAST();
    land_expr->flag = LAndExprAST::ONLY_EQ;
    land_expr->eq_expr = unique_ptr<BaseAST>($1);
    $$ = land_expr;
  }
  | LAndExpr '&' '&' EqExpr {
    auto land_expr = new LAndExprAST();
    land_expr->flag = LAndExprAST::LAND_EQ;
    land_expr->land_expr = unique_ptr<BaseAST>($1);
    land_expr->op = "&&";
    land_expr->eq_expr = unique_ptr<BaseAST>($4);
    $$ = land_expr;
  }
  ;

EqExpr
  : RelExpr {
    auto eq_expr = new EqExprAST();
    eq_expr->flag = EqExprAST::ONLY_REL;
    eq_expr->rel_expr = unique_ptr<BaseAST>($1);
    $$ = eq_expr;
  }
  | EqExpr '=' '=' RelExpr {
    auto eq_expr = new EqExprAST();
    eq_expr->flag = EqExprAST::EQ_REL;
    eq_expr->eq_expr = unique_ptr<BaseAST>($1);
    eq_expr->op = "==";
    eq_expr->rel_expr = unique_ptr<BaseAST>($4);
    $$ = eq_expr;
  }
  | EqExpr '!' '=' RelExpr {
    auto eq_expr = new EqExprAST();
    eq_expr->flag = EqExprAST::EQ_REL;
    eq_expr->eq_expr = unique_ptr<BaseAST>($1);
    eq_expr->op = "!=";
    eq_expr->rel_expr = unique_ptr<BaseAST>($4);
    $$ = eq_expr;
  }
  ;

RelExpr
  : AddExpr {
    auto rel_expr = new RelExprAST();
    rel_expr->flag = RelExprAST::ONLY_ADD;
    rel_expr->add_expr = unique_ptr<BaseAST>($1);
    $$ = rel_expr;
  }
  | RelExpr '<' AddExpr {
    auto rel_expr = new RelExprAST();
    rel_expr->flag = RelExprAST::REL_ADD;
    rel_expr->rel_expr = unique_ptr<BaseAST>($1);
    rel_expr->op = "<";
    rel_expr->add_expr = unique_ptr<BaseAST>($3);
    $$ = rel_expr;
  }
  | RelExpr '>' AddExpr {
    auto rel_expr = new RelExprAST();
    rel_expr->flag = RelExprAST::REL_ADD;
    rel_expr->rel_expr = unique_ptr<BaseAST>($1);
    rel_expr->op = ">";
    rel_expr->add_expr = unique_ptr<BaseAST>($3);
    $$ = rel_expr;
  }
  | RelExpr '<' '=' AddExpr {
    auto rel_expr = new RelExprAST();
    rel_expr->flag = RelExprAST::REL_ADD;
    rel_expr->rel_expr = unique_ptr<BaseAST>($1);
    rel_expr->op = "<=";
    rel_expr->add_expr = unique_ptr<BaseAST>($4);
    $$ = rel_expr;
  }
  | RelExpr '>' '=' AddExpr {
    auto rel_expr = new RelExprAST();
    rel_expr->flag = RelExprAST::REL_ADD;
    rel_expr->rel_expr = unique_ptr<BaseAST>($1);
    rel_expr->op = ">=";
    rel_expr->add_expr = unique_ptr<BaseAST>($4);
    $$ = rel_expr;
  }
  ;


Number
  : INT_CONST {
    $$ = $1;
  }
  ;

%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
/* void yyerror(std::unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
} */
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s) {
  
    extern int yylineno;    // defined and maintained in lex
    extern char *yytext;    // defined and maintained in lex
    int len=strlen(yytext);
    int i;
    char buf[512]={0};
    for (i=0;i<len;++i)
    {
        sprintf(buf,"%s%d ",buf,yytext[i]);
    }
    fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);

}