#include "semantic.hpp"
#include <iostream>

bool SemanticAnalyzer::analyze(Program* program) {
    collect_classes(program);
    if (has_error) return false;

    check_cycles();
    if (has_error) return false;

    // collect_members(program);
    // if (has_error) return false;

    // type_check(program);

    return !has_error;
}

void SemanticAnalyzer::error(int line, int col, const std::string& msg) {
    std::cerr << line << ":" << col << ": semantic error: " << msg << std::endl;
    has_error = true;
}

void SemanticAnalyzer::collect_classes(Program* p) {
    // Predefined class root of the hierarchy
    class_table["Object"] = nullptr;

    // Loop 1 : 
    // - find all class declarations
    // - store them in classTable
    // - report error if duplicated class name
    for (auto* c : p->classes) {
        if (class_table.count(c->name)) {
            error(c->line, c->col, "class " + c->name + " is already defined");
        } else {
            class_table[c->name] = c;
        }
    }

    // Loop 2 : 
    // - check all parent exists
    for (auto* c : p->classes) {
        if (!class_table.count(c->parent)) {
            error(c->line, c->col, "unknown parent class " + c->parent);
        }
    }
}

void SemanticAnalyzer::check_cycles() {
    for (auto& [name, c] : class_table) {
        if (name == "Object") continue;

        std::set<std::string> visited_classes;
        std::string current = name;

        while (current != "Object") {
            if (visited_classes.count(current)) {
                error(c->line, c->col,
                      "class " + name + " is involved in an inheritance cycle");
                break;
            }
            visited_classes.insert(current);
            if (!class_table.count(class_table[current]->parent)) break;
            current = class_table[current]->parent;
        }
    }
}

void SemanticAnalyzer::collect_members(Program* p) {

    // Loop 1 : register all fields and method signatures per class
    for (auto* c : p->classes) {

        // --- Fields ---
        for (auto* f : c->fields) {
            if (!class_table.count(f->type)) {
                error(f->line, f->col, "unknown type " + f->type);
            }
            if (field_table[c->name].count(f->name)) {
                error(f->line, f->col, "field " + f->name + " already defined");
            } else {
                field_table[c->name][f->name] = f->type;
            }
        }

        // --- Methods ---
        for (auto* m : c->methods) {
            if (!class_table.count(m->ret_type)) {
                error(m->line, m->col, "unknown return type " + m->ret_type);
            }
            MethodSignature s;
            s.return_type = m->ret_type;
            for (auto* formal : m->formals) {
                if (!class_table.count(formal->type)) {
                    error(formal->line, formal->col, "unknown type " + formal->type);
                }
                s.param_types.push_back(formal->type);
            }
            method_table[c->name][m->name] = s;
        }
    }

    // Loop 2 : check method overrides have the same signature as parent
    for (auto* c : p->classes) {
        if (c->parent == "Object") continue;
        for (auto* m : c->methods) {
            // remonter la hiérarchie pour trouver si la méthode existe dans un parent
            std::string parent = c->parent;
            while (parent != "Object") {
                if (method_table[parent].count(m->name)) {
                    MethodSignature &parent_s = method_table[parent][m->name];
                    MethodSignature &child_s  = method_table[c->name][m->name];
                    if (parent_s.return_type  != child_s.return_type ||
                        parent_s.param_types  != child_s.param_types) {
                        error(m->line, m->col,
                              "overriding method " + m->name + " with different signature");
                    }
                    break;
                }
                parent = class_table[parent]->parent;
            }
        }
    }
}

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