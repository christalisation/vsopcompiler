    /* Author: Christal Mangolopa
    * INFO0085 - Compilers
    * Uliege - Academic year 2025-2026
    * This file defines the abstract syntax tree (AST) for the VSOP language
    * for the second part of the project.
    */

#pragma once
#include <string>
#include <vector>
    
struct ASTNode
{
    int line, col;      // Source code position of the node (for error reporting)
    virtual std::string toString() const = 0;
    virtual ~ASTNode() = default;
};

// Forward declarations
struct Expr;
struct Field;
struct Method;
struct ClassDecl;

// Expressions (base class for all expressions)
struct Expr : ASTNode {};

struct IntLiteral : Expr
{
    int value;
    std::string toString() const override{
        return std::to_string(value);
    }
};

struct StringLiteral : Expr
{
    std::string value;
    std::string toString() const override{
        return "\"" + value + "\"";
    }
};

struct BoolLiteral : Expr
{
    bool value;
    std::string toString() const override{
        return value ? "true" : "false";
    }
};

struct Program : ASTNode
{
    std::vector<ClassDecl*> classes;  // List of class declarations in the program
    std::string toString() const override{
        return classes->toString(); //mettre une fct qui boucle
    }
};

struct TypeID : ASTNode
{
    std::string type;     // "int32" | "bool" | "string" | "unit"
    std::string toString() const override{
        return type;
    }
};

struct FormalList : ASTNode
{
    std::vector<Formal> formals;
};

struct Formal : ASTNode
{
    std::string name;
    std::string type;
    std::string toString() const override{
        return name + " : " + type;
    }
};

struct Block : Expr
{
    std::vector<Expr*> expr_list;
    std::string toString() const override{
        return expr_list.toString(); // mettre ici une boucle pour vector qui rend .toString() for each el of expr-list
    }
};

struct If : Expr
{
    Expr* cond_expr;
    Expr* then_expr;
    Expr* else_expr; // can be null
    std::string toString() const override{
        std::string s = "If(" + cond_expr->toString() 
                        + ", " + then_expr->toString();
        if (else_expr) {s += ", " + else_expr->toString();}
        return s + ")";
    }
};

struct While : Expr {
    Expr* cond_expr;
    Expr* body_expr;
    std::string toString() const override {
        return "While(" + cond_expr->toString()
                + ", " + body_expr->toString() + ")";
    }
};

struct Let : Expr {
    std::string name;
    std::string type;
    Expr* init_expr;   // can be nullptr
    Expr* scope_expr;
    std::string toString() const override {
        std::string s = "Let(" + name + ", " + type;
        if (init_expr) s += ", " + init_expr->toString();
        return s + ", " + scope_expr->toString() + ")";
    }
};

struct Assign : Expr {
    std::string name;
    Expr* expr;
    std::string toString() const override {
        return "Assign(" + name + ", " + expr->toString() + ")";
    }
};

struct UnaryOp : Expr
{
    std::string op; // "not", "-" or "isnull"
    Expr* expr;
    std::string toString() const override{
        return "UnOp(" + op + ", " + expr->toString() + ")";
    }
};

struct BinaryOp : Expr
{
    std::string op; // "=", "<", "<=" | "+", "-" | "*", "/" | "^" | "and"
    Expr* left_expr;
    Expr* right_expr;
    std::string toString() const override{
        return "BinOp(" + op + ", " + left_expr->toString() 
                    + ", " + right_expr->toString() + ")";
    }
};

struct Call : Expr
{
    Expr* obj_expr;
    std::string method_name;
    std::vector<Expr*> expr_list;
    std::string toString() const override {
        return "Call(" + obj_expr->toString()
                + ", " + method_name + ", "
                + expr_list.toString()
                + ")";
    };
};

struct New : Expr
{
    TypeID* type_name;
    std::string toString() const override{
        return "New(" + type_name->toString() + ")";
    }
};

struct Method : ASTNode
{
    std::string name;
    FormalList* formals;
    std::string ret_type;
    Block* block;
    std::string toString() const override {
        return "Method(" + name + ", " + 
                        formals->toString() + ", "
                        + ret_type + ", " +
                        block->toString() + ")";
    }
};

struct Field : ASTNode
{
    std::string name;
    std::string type;
    Expr* init_expr;
    std::string toString(){
        std::string s = "Field(" + name + ", " + type;
        if (init_expr) s+= ", " + init_expr->toString();
        return s + ")";
    }
};

struct ClassDecl : ASTNode
{
    std::string name;
    std::string parent;
    std::vector<Field> fields;
    std::vector<Method> methods; 
    std::string toString() const override{
        if !(parent) parent = "Object";
        return "Class(" + name + ", " + 
                    fields->toString() ", " 
                    methods->toString() + ")";
    }
};

