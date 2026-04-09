/* Author: Christal Mangolopa
 * INFO0085 - Compilers
 * Uliege - Academic year 2025-2026
 * This flex/bison parser implements the first part of the project
 * for a simple compiler for VSOP.
 *
 * You can use the '-l' flag to list all the tokens found in the 
 * source file, and the '-p' flag (or no flag) to parse the file
 * and to compute the result.
 *
 */

%skeleton "lalr1.cc" // -*- C++ -*-
%language "c++"
%require "3.7.5"
%locations

%defines

// Put parser inside a namespace
%define api.namespace {VSOP}

// Give the name of the parser class
%define api.parser.class {Parser}

// Force the token kind enum (used by the lexer) and the symbol kind enum
// (used by the parser) to use the same value for the tokens.
// (e.g. '+' will be represented by the same integer value in both enums.)
%define api.token.raw

// Tokens contain their type, value and location
// Also allow to use the make_TOKEN functions
%define api.token.constructor

// Allow to use C++ objects as semantic values
%define api.value.type variant

// Add some assertions.
%define parse.assert

// C++ code put inside header file
%code requires {
    #include <string>
    #include "ast.hpp"

    namespace VSOP
    {
        class Driver;
    }
}

// Add an argument to the parser constructor
%parse-param {VSOP::Driver &driver}

%code {
    #include "driver.hpp"

    using namespace std;
}

// Token and symbols definitions

// Keywords
%token
    AND     "and"
    BOOL    "bool"
    CLASS   "class"
    DO      "do"
    ELSE    "else"
    EXTENDS "extends"
    FALSE   "false"
    IF      "if"
    IN      "in"
    INT32   "int32"
    ISNULL  "isnull"
    LET     "let"
    NEW     "new"
    NOT     "not"
    SELF    "self"
    STRING  "string"
    THEN    "then"
    TRUE    "true"
    UNIT    "unit"
    WHILE   "while"
;

// Operators
%token
    LBRACE      "{"
    RBRACE      "}"
    LPAR        "("
    RPAR        ")"
    COLON       ":"
    SEMICOLON   ";"
    COMMA       ","
    PLUS        "+"
    MINUS       "-"
    TIMES       "*"
    DIV         "/"
    POW         "^"
    DOT         "."
    EQUAL       "="
    LOWER       "<"
    LOWER_EQUAL "<="
    ASSIGN      "<-"
;

// For some symbols, need to store a value:

%token <int>         INTEGER_LITERAL    "integer-literal"
%token <std::string> STRING_LITERAL     "string-literal"
%token <std::string> TYPE_ID            "type-identifier"
%token <std::string> OBJECT_ID          "object-identifier"

// Precedence
%right    ASSIGN
%left     AND
%right    NOT
%nonassoc EQUAL LOWER LOWER_EQUAL
%left     PLUS MINUS
%left     TIMES DIV
%right    ISNULL
%right    POW
%left     DOT

// Non-terminals types
%type <Program*> program
%type <std::vector<ClassDecl*>>   classes
%type <ClassDecl*>                class_decl
%type <std::vector<Field*>>       fields
%type <Field*>                    field
%type <std::vector<Method*>>      methods
%type <Method*>                   method
%type <TypeID>                    type_id
%type <std::vector<Formal*>>      formals
%type <Formal*>                   formal
%type <Expr*>                     expr
%type <Block*>                    block
%type <std::vector<Expr*>>        expr_list


%%
// Grammar rules
program:
    classes
    {
        auto* p = new Program();
        p->classes = $1;
        $$ = p;
        driver.program = p;
    }
;
classes:
    class_decl             { $$ = {$1}; }
  | classes class_decl     { $$ = $1; $$.push_back($2); }
;
class_decl:
    CLASS TYPE_ID LBRACE fields methods RBRACE
    {  
        auto* c = new ClassDecl();
        c->name = $2;
        c->parent = "Object"; // set default parent
        c->fields = $4;
        c->methods = $5;
        $$ = c;
    }
  | CLASS TYPE_ID EXTENDS TYPE_ID LBRACE fields methods RBRACE
        {
            auto* c = new ClassDecl();
            c->name = $2;
            c->parent = $4; // set parent from EXTENDS
            c->fields = $6;
            c->methods = $7;
            $$ = c;
        }
;
fields:
    /* empty */           { $$ = {}; }
  | fields field          { $$ = $1; $$.push_back($2); }
;
field:
    OBJECT_ID COLON type SEMICOLON
    {
        auto* f = new Field();
        f->name = $1;
        f->type = $3;
        f->init = nullptr; // no initializer for fields
        $$ = f;
    }
  | OBJECT_ID COLON type ASSIGN expr SEMICOLON
    {
        auto* f = new Field();
        f->name = $1;
        f->type = $3;
        f->init = $5; // set initializer from expression
        $$ = f;
    }
;
methods:
    /* empty */           { $$ = {}; }
  | methods method         { $$ = $1; $$.push_back($2); }
;
method:
    OBJECT_ID LPAR formals RPAR COLON type block
    {
        auto* m = new Method();
        m->name = $1;
        m->formals = $3;
        m->ret_type = $6;
        m->body = $7;
        $$ = m;
    }
;
type:
    TYPE_ID                { $$ = $1; }
    | INT32                   { $$ = "int32"; }
    | BOOL                   { $$ = "bool"; }
    | STRING                 { $$ = "string"; }
    | UNIT                   { $$ = "unit"; }
;
formals:
    /* empty */           { $$ = {}; }
  | formal_list         { $$ = $1; }
;
formal_list:
    formal                { $$ = {$1}; }
  | formal_list COMMA formal { $$ = $1; $$.push_back($3); }
;
formal:
    OBJECT_ID COLON type
    {
        auto* f = new Formal();
        f->name = $1;
        f->type = $3;
        $$ = f;
    }
;
block:
    LBRACE expr_list RBRACE
    {
        auto* b = new Block();
        b->exprs = $2;
        $$ = b;
    }
;
expr_list:
    expr_list expr          { $$ = $1; $$.push_back($2); }
    | expr                   { $$ = {$1}; }
;
expr:
    INTEGER_LITERAL          { auto* i = new IntLiteral(); i->value = $1; $$ = i; }
    | STRING_LITERAL           { auto* s = new StringLiteral(); s->value = $1; $$ = s; }
    | TRUE                     { auto* b = new BoolLiteral(); b->value = true; $$ = b; }
    | FALSE                    { auto* b = new BoolLiteral(); b->value = false; $$ = b; }
    | OBJECT_ID                { auto* o = new ObjectID(); o->name = $1; $$ = o; }
    | SELF                     { auto* o = new ObjectID(); o->name = "self"; $$ = o; }
    | NEW TYPE_ID              { auto* n = new New(); n->type_name = $2; $$ = n; }
    | OBJECT_ID ASSIGN expr    { auto* a = new Assign(); a->name = $1; a->value = $3; $$ = a; }
    | expr PLUS expr           { auto* b = new BinaryOp(); b->op = "+"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr MINUS expr          { auto* b = new BinaryOp(); b->op = "-"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr TIMES expr          { auto* b = new BinaryOp(); b->op = "*"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr DIV expr            { auto* b = new BinaryOp(); b->op = "/"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr POW expr            { auto* b = new BinaryOp(); b->op = "^"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr AND expr            { auto* b = new BinaryOp(); b->op = "and"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr EQUAL expr          { auto* b = new BinaryOp(); b->op = "=="; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr LOWER expr          { auto* b = new BinaryOp(); b->op = "<"; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | expr LOWER_EQUAL expr    { auto* b = new BinaryOp(); b->op = "<="; b->left_expr = $1; b->right_expr = $3; $$ = b; }
    | NOT expr                 { auto* u = new UnaryOp(); u->op = "not"; u->expr = $2; $$ = u; }
    | MINUS expr %prec UMINUS  { auto* u = new UnaryOp(); u->op = "-"; u->expr = $2; $$ = u; }
    | ISNULL expr              { auto* u = new UnaryOp(); u->op = "isnull"; u->expr = $2; $$ = u; }
    | IF expr THEN expr ELSE expr { auto* i = new If(); i->cond_expr = $2; i->then_expr = $4; i->else_expr = $6; $$ = i; }
    | IF expr THEN expr        { auto* i = new If(); i->cond_expr = $2; i->then_expr = $4; i->else_expr = nullptr; $$ = i; }
    | WHILE expr DO expr       { auto* w = new While(); w->cond_expr = $2; w->body = $4; $$ = w; }
    | LET OBJECT_ID COLON type ASSIGN expr IN expr
        {
            auto* l = new Let();
            l->var_name = $2;
            l->var_type = $4;
            l->init_expr = $6;
            l->scope_expr = $8;
            $$ = l;
        }
    | LET OBJECT_ID COLON type IN expr
        {
            auto* l = new Let();
            l->var_name = $2;
            l->var_type = $4;
            l-> init_expr = nullptr; // no initializer
            l->scope_expr = $6;
            $$ = l;
        }
    | expr DOT OBJECT_ID LPAR expr_list RPAR
        {
            auto* c = new Call();
            c->obj_expr = $1;
            c->method_name = $3;
            c->expr_list = $5;
            $$ = c;
        }
    | OBJECT_ID LPAR expr_list RPAR
        {
            auto* c = new Call();
            c->obj_expr = nullptr; // no object, it's a call on self
            c->method_name = $1;
            c->expr_list = $3;
            $$ = c;
        }
    | LPAR expr RPAR    { $$ = $2; }
    | block             { $$ = $1; }
;

%%
// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
