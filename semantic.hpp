    /* Author: Christal Mangolopa
    * INFO0085 - Compilers
    * Uliege - Academic year 2025-2026
    * This file defines the abstract syntax tree (AST) for the VSOP language
    * for the third part of the project.
    */

#include <map>
#include <set>
#include <string>
#include "ast.hpp"

class SemanticAnalyzer {

public:
    /**
     * Runs all semantic analysis passes on the given program.
     * Returns true if the program is semantically valid, false otherwise.
     */
    bool analyze(Program* program);
    
private:
    /**
     * PASS 1 — Collects all class declarations into classTable.
     * Reports errors for 
     *      - duplicate class names and 
     *      - undefined parent classes.
     */
    void collectClasses(Program* p);

    /**
     * PASS 2 — Checks for cycles in the inheritance hierarchy.
     * For each class, walks up the parent chain until Object or a cycle is detected.
     * Relies on classTable being fully populated (runs after collectClasses).
     */
    void checkCycles();

    // === PASS 3: Collect field and method signatures ===
    void collectMembers(Program* p);

    // === PASS 4: Type-check method bodies and field initializers ===
    void typeCheck(Program* p);
    void typeCheckMethod(Method* m, ClassDecl* cls);
    std::string typeCheckExpr(Expr* e, /* scope */);

    // Shared data
    std::map<std::string, ClassDecl*> classTable;
    std::map<std::string, std::map<std::string, std::string>>  fieldTable;  // class -> {field -> type}
    std::map<std::string, std::map<std::string, MethodSig>>    methodTable; // class -> {method -> sig}
    
    bool hasError = false;
    void error(int line, int col, const std::string& msg);
    struct MethodSig {
        std::vector<std::string> param_types;
        std::string return_type;
    };
};