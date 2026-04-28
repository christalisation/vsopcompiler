#include "semantic.hpp"
#include <iostream>

bool SemanticAnalyzer::analyze(Program* program) {
    collectClasses(program);
    if (hasError) return false;

    checkCycles();
    if (hasError) return false;

    // collectMembers(program);
    // if (hasError) return false;

    // typeCheck(program);

    return !hasError;
}

void SemanticAnalyzer::error(int line, int col, const std::string& msg) {
    std::cerr << line << ":" << col << ": semantic error: " << msg << std::endl;
    hasError = true;
}

void SemanticAnalyzer::collectClasses(Program* p) {
    // Predefined class root of the hierarchy
    classTable["Object"] = nullptr;

    // Loop 1 : 
    // - find all class declarations
    // - store them in classTable
    // - report error if duplicated class name
    for (auto* c : p->classes) {
        if (classTable.count(c->name)) {
            error(c->line, c->col, "class " + c->name + " is already defined");
        } else {
            classTable[c->name] = c;
        }
    }

    // Loop 2 : 
    // - check all parent exists
    for (auto* c : p->classes) {
        if (!classTable.count(c->parent)) {
            error(c->line, c->col, "unknown parent class " + c->parent);
        }
    }
}

void SemanticAnalyzer::checkCycles() {
    for (auto& [name, classDecl] : classTable) {
        if (name == "Object") continue;

        std::set<std::string> visited;
        std::string current = name;

        while (current != "Object") {
            if (visited.count(current)) {
                error(classDecl->line, classDecl->col,
                      "class " + name + " is involved in an inheritance cycle");
                break;
            }
            visited.insert(current);
            if (!classTable.count(classTable[current]->parent)) break;
            current = classTable[current]->parent;
        }
    }
}

// Une struct légère pour stocker la signature d'une méthode
struct MethodSig {
    std::vector<std::string> param_types;
    std::string return_type;
};

std::map<std::string, std::map<std::string, std::string>>   fieldTable;  // class → {field → type}
std::map<std::string, std::map<std::string, MethodSig>>     methodTable; // class → {method → sig}

std::string typeCheckExpr(Expr* e, 
                           std::map<std::string, std::string>& scope,
                           const std::string& currentClass) {
    if (auto* i = dynamic_cast<IntLiteral*>(e)) {
        return e->inferred_type = "int32";
    }
    if (auto* b = dynamic_cast<BinaryOp*>(e)) {
        auto l = typeCheckExpr(b->left_expr,  scope, currentClass);
        auto r = typeCheckExpr(b->right_expr, scope, currentClass);
        if (b->op == "+" || b->op == "-" || ...) {
            if (l != "int32" || r != "int32") error(...);
            return e->inferred_type = "int32";
        }
        // ...
    }
    if (auto* call = dynamic_cast<Call*>(e)) {
        // ...
    }
    // etc.
    return e->inferred_type = "__error__"; // dummy fallback
}