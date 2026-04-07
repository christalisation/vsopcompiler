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


// Literals

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
        return "program";
    }
};


//Identifiers

struct TypeID : ASTNode
{
    std::string name;
    std::string toString() const override{
        return name;
    }
};

struct ObjectID : Expr
{
    std::string name;
    std::string toString() const override{
        return name;
    }
};


// Operations

// TODO: modify and verify
struct ClassDecl : ASTNode
{
    std::string name;                  // Name of the class
    std::vector<FeatureDecl*> features; // List of features (attributes and methods) in the class
    std::string toString() const override{
        return "class " + name;
    }
};



struct Block : Expr
{
    std::vector<Expr*> expressions;
    std::string toString() const override{
        // TODO
        return "Block(...)";
    }
};



struct New : Expr
{
    TypeID* type;
    std::string toString() const override{
        return "new " + type->toString();
    }
};

// Operations

struct BinaryOp : Expr
{
    std::string op; // Operator symbol (e.g., "+", "-", "*", "/")
    Expr* left;     // Left operand
    Expr* right;    // Right operand
    std::string toString() const override{
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

struct UnaryOp : Expr
{
    std::string op; // Operator symbol (e.g., "not", "-")
    Expr* operand;  // Operand
    std::string toString() const override{
        return "(" + op + " " + operand->toString() + ")";
    }
};

struct If : Expr
{
    Expr* condition;
    Expr* thenExpr;
    Expr* elseExpr; // can be null
    std::string toString() const override{
        return "if " + condition->toString() 
            + " then " + thenExpr->toString() 
            + " else " + elseExpr->toString();
    }
};