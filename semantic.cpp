#include "semantic.hpp"
#include <iostream>

bool SemanticAnalyzer::analyze(Program* program) {

    // ---pass 1
    collect_classes(program);
    if (has_error) return false;

    // ---pass 2
    check_cycles();
    if (has_error) return false;

    // ---pass 3
    collect_members(program);

    // Main class + main() method with no arg
    if (!class_table.count("Main"))
        error(0, 0, "missing class Main");
    else if (class_table["Main"] != nullptr) {
        auto& methods = method_table["Main"];
        if (!methods.count("main"))
            error(0, 0, "class Main has no method main");
        else if (!methods["main"].param_types.empty())
            error(0, 0, "method main must take no arguments");
    }
    if (has_error) return false;

    // ---pass 4
    for (auto* c : program->classes) {
        //
        for (auto* f : c->fields) {
            if (f->init_expr) {
            std::map<std::string, std::string> scope;
            scope["self"] = c->name;
            // fields des parents aussi visibles dans les initialiseurs
            std::string klass = c->name;
            while (klass != "Object" && class_table.count(klass) && class_table[klass]) {
                for (auto& [fname, ftype] : field_table[klass])
                    if (!scope.count(fname))
                        scope[fname] = ftype;
                klass = class_table[klass]->parent;
            }
            std::string t = typecheck_expr(f->init_expr, scope, c->name);
            if (!is_subtype(t, f->type))
                error(f->line, f->col,
                    "field " + f->name + " init type " + t +
                    " not subtype of " + f->type);
            }
        }
        for (auto* m : c->methods) {
            std::map<std::string, std::string> scope;
            scope["self"] = c->name;
            std::string clas = c->name;
            while (clas != "Object" && class_table.count(clas) && class_table[clas]) {
                for (auto& [fname, ftype] : field_table[clas])
                    if (!scope.count(fname))  // ne pas écraser un field plus proche
                        scope[fname] = ftype;
                clas = class_table[clas]->parent;
            }
            for (auto* f : m->formals)
                scope[f->name] = f->type;   // shadowing formals > fields OK en VSOP
            typecheck_expr(m->block, scope, c->name);
        }
    }

    return !has_error;
}

void SemanticAnalyzer::error(int line, int col, const std::string& msg) {
    std::cerr << filename << ":" << line << ":" << col << ": semantic error: " << msg << std::endl;
    has_error = true;
}

void SemanticAnalyzer::collect_classes(Program* p) {

    // Built-in types stored as nullptr , not real ClassDecl nodes

    class_table["Object"] = nullptr; // Predefined class root of the hierarchy

    class_table["int32"]  = nullptr; // All primitives
    class_table["bool"]   = nullptr;
    class_table["string"] = nullptr;
    class_table["unit"]   = nullptr;

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
        if (c == nullptr) continue;  // skip built-in types (Object and primitives)

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
    // Built-in methods of Object
    method_table["Object"]["print"]      = { {"string"}, "Object" };
    method_table["Object"]["printBool"]  = { {"bool"},   "Object" };
    method_table["Object"]["printInt32"] = { {"int32"},  "Object" };
    method_table["Object"]["inputLine"]  = { {},         "string" };
    method_table["Object"]["inputBool"]  = { {},         "bool"   };
    method_table["Object"]["inputInt32"] = { {},         "int32"  };

    // Loop 1 : register all fields and method signatures per class
    for (auto* c : p->classes) {

        // --- Fields ---
        for (auto* field : c->fields) {
            if (!class_table.count(field->type)) {
                error(field->line, field->col, "unknown type " + field->type);
            }
            if (field_table[c->name].count(field->name)) {
                error(field->line, field->col, "field " + field->name + " already defined");
            } else {
                // infer a type
                field_table[c->name][field->name] = field->type;
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
            // find method in parent
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

std::string SemanticAnalyzer::typecheck_expr(Expr* e, std::map<std::string, std::string>& scope, const std::string& current_class) {

    // --- litterals ---
    if (dynamic_cast<IntLiteral*>(e))    return e->inferred_type = "int32";
    if (dynamic_cast<BoolLiteral*>(e))   return e->inferred_type = "bool";
    if (dynamic_cast<StringLiteral*>(e)) return e->inferred_type = "string";
    if (dynamic_cast<UnitLiteral*>(e))   return e->inferred_type = "unit";

    // --- self ---
    if (auto* node = dynamic_cast<ObjectID*>(e)) {
        if (node->name == "self") return e->inferred_type = current_class;
        if (scope.count(node->name)) return e->inferred_type = scope[node->name];
        error(e->line, e->col, "unbound variable " + node->name);
        return e->inferred_type = "__error__";
    }

    // --- New ---
    if (auto* node = dynamic_cast<New*>(e)) {
        if (!class_table.count(node->type_name))
            error(e->line, e->col, "unknown type " + node->type_name);
        return e->inferred_type = node->type_name;
    }

    // --- Block ---
    if (auto* node = dynamic_cast<Block*>(e)) {
        std::string t = "unit";
        for (auto* expr : node->expr_list)
            t = typecheck_expr(expr, scope, current_class);
        return e->inferred_type = t;  // type = dernière expr
    }

    // --- Assign ---
    if (auto* node = dynamic_cast<Assign*>(e)) {
        if (!scope.count(node->name))
            error(e->line, e->col, "unbound variable " + node->name);
        std::string t = typecheck_expr(node->expr, scope, current_class);
        return e->inferred_type = t;
    }

    // --- If ---
    if (auto* node = dynamic_cast<If*>(e)) {
        std::string cond = typecheck_expr(node->cond_expr, scope, current_class);
        if (cond != "bool")
            error(e->line, e->col, "condition of if must be bool, got " + cond);
        std::string t_then = typecheck_expr(node->then_expr, scope, current_class);
        if (!node->else_expr)
            return e->inferred_type = "unit";  // if-then sans else -> unit
        std::string t_else = typecheck_expr(node->else_expr, scope, current_class);
        return e->inferred_type = lca(t_then, t_else);
    }

    // --- While ---
    if (auto* node = dynamic_cast<While*>(e)) {
        std::string cond = typecheck_expr(node->cond_expr, scope, current_class);
        if (cond != "bool")
            error(e->line, e->col, "condition of while must be bool, got " + cond);
        typecheck_expr(node->body_expr, scope, current_class);
        return e->inferred_type = "unit";  // while -> toujours unit
    }

    // --- Let ---
    if (auto* node = dynamic_cast<Let*>(e)) {
        if (!class_table.count(node->type))
            error(e->line, e->col, "unknown type " + node->type);
        if (node->init_expr) {
            std::string t = typecheck_expr(node->init_expr, scope, current_class);
            if (!is_subtype(t, node->type))
                error(e->line, e->col, "init type " + t + " not subtype of " + node->type);
        }
        // Nouvelle variable dans le scope — shadowing OK en VSOP
        auto saved = scope;
        scope[node->name] = node->type;
        std::string t = typecheck_expr(node->scope_expr, scope, current_class);
        scope = saved;  // restore scope après le let
        return e->inferred_type = t;
    }

    // --- BinaryOp ---
    if (auto* node = dynamic_cast<BinaryOp*>(e)) {
        std::string l = typecheck_expr(node->left_expr, scope, current_class);
        std::string r = typecheck_expr(node->right_expr, scope, current_class);
        std::string op = node->op;
        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^") {
            if (l != "int32") error(e->line, e->col, "left operand of " + op + " must be int32");
            if (r != "int32") error(e->line, e->col, "right operand of " + op + " must be int32");
            return e->inferred_type = "int32";
        }
        if (op == "<" || op == "<=") {
            if (l != "int32") error(e->line, e->col, "left operand of " + op + " must be int32");
            if (r != "int32") error(e->line, e->col, "right operand of " + op + " must be int32");
            return e->inferred_type = "bool";
        }
        if (op == "and") {
            if (l != "bool") error(e->line, e->col, "left operand of and must be bool");
            if (r != "bool") error(e->line, e->col, "right operand of and must be bool");
            return e->inferred_type = "bool";
        }
        if (op == "=") {
            // = n'est valide qu'entre mêmes primitifs ou entre types object
            bool l_prim = (l=="int32"||l=="bool"||l=="string"||l=="unit");
            bool r_prim = (r=="int32"||r=="bool"||r=="string"||r=="unit");
            if (l_prim || r_prim) {
                if (l != r) error(e->line, e->col, "cannot compare " + l + " with " + r);
            }
            return e->inferred_type = "bool";
        }
    }

    // --- UnaryOp ---
    if (auto* node = dynamic_cast<UnaryOp*>(e)) {
        std::string t = typecheck_expr(node->expr, scope, current_class);
        if (node->op == "not") {
            if (t != "bool") error(e->line, e->col, "operand of not must be bool");
            return e->inferred_type = "bool";
        }
        if (node->op == "-") {
            if (t != "int32") error(e->line, e->col, "operand of unary - must be int32");
            return e->inferred_type = "int32";
        }
        if (node->op == "isnull") {
            // isnull valide sur tout type objet (pas primitif)
            if (t=="int32"||t=="bool"||t=="string"||t=="unit")
                error(e->line, e->col, "isnull requires object type, got " + t);
            return e->inferred_type = "bool";
        }
    }

    // --- Call ---
    if (auto* node = dynamic_cast<Call*>(e)) {
        std::string recv = node->obj_expr
            ? typecheck_expr(node->obj_expr, scope, current_class)
            : current_class;  // pas d'objet -> appel sur self implicite
        // Chercher la méthode dans recv et ses parents
        std::string klass = recv;
        while (true) {
            if (method_table.count(klass) && method_table[klass].count(node->method_name)) {
                auto& sig = method_table[klass][node->method_name];
                // Vérifier arité
                if (node->expr_list.size() != sig.param_types.size())
                    error(e->line, e->col, "wrong number of args for " + node->method_name);
                else {
                    for (size_t i = 0; i < node->expr_list.size(); ++i) {
                        std::string arg = typecheck_expr(node->expr_list[i], scope, current_class);
                        if (!is_subtype(arg, sig.param_types[i]))
                            error(e->line, e->col, "argument " + std::to_string(i+1)
                                + " type mismatch in call to " + node->method_name);
                    }
                }
                return e->inferred_type = sig.return_type;
            }
            if (klass == "Object" || !class_table.count(klass) || class_table[klass] == nullptr) break;
            klass = class_table[klass]->parent;
        }
        error(e->line, e->col, "unknown method " + node->method_name + " in " + recv);
        return e->inferred_type = "__error__";
    }

    return e->inferred_type = "__error__";
}

bool SemanticAnalyzer::is_subtype(const std::string& type_a, const std::string& type_b) {
    if (type_a == type_b) return true;
    if (type_a == "__error__") 
        return true;        // error recovery
    std::string current = type_a;
    while (current != "Object") {
        if (!class_table.count(current) || class_table[current] == nullptr) break;
        current = class_table[current]->parent;
        if (current == type_b) return true;
    }
    return type_b == "Object";  // tout est sous-type d'Object
}

std::string SemanticAnalyzer::lca(const std::string& l_type, const std::string& r_type) {
    if (l_type == r_type) return l_type;
    if (l_type == "__error__") return r_type;
    if (r_type == "__error__") return l_type;
    // Collecter les ancêtres de l_type
    std::vector<std::string> l_ancestors;
    std::string current = l_type;
    while (true) {
        l_ancestors.push_back(current);
        if (current == "Object" || !class_table.count(current) || class_table[current] == nullptr) break;
        current = class_table[current]->parent;
    }
    // Remonter r_type jusqu'à trouver un ancêtre commun
    current = r_type;
    while (true) {
        for (auto& anc : l_ancestors)
            if (anc == current) return current;
        if (current == "Object" || !class_table.count(current) || class_table[current] == nullptr) break;
        current = class_table[current]->parent;
    }
    return "Object";
}