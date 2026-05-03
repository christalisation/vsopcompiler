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

struct MethodSignature {
        std::vector<std::string> param_types;
        std::string return_type;
    };

class SemanticAnalyzer {

public:
    /**
     * @brief Runs all semantic analysis passes.
     * @param program The root AST node.
     * @return `true` if semantically valid, `false` if errors were found.
     */
    bool analyze(Program* program);

private:
    /**
     * PASS 1 —
     * 
     * @brief Collects all class declarations into classTable.
     * 
     * Reports errors for duplicate class names and undefined parent classes.
     * Must be run before any other pass.
     * 
     * @param p The root AST node of the program.
     */
    void collect_classes(Program* p);

    
    /**
     * PASS 2 —
     * 
     * @brief Checks for cycles in the inheritance hierarchy.
     * 
     * Walks up the parent chain of each class until Object or a cycle is detected.
     * Must be run after collect_classes.
     */
    void check_cycles();

    /**
     * PASS 3 —
     * 
     * @brief Collects field types and method signatures for all classes into
     *        `field_table` and `method_table`.
     *
     * Also verifies that:
     * - All used types exist in `class_table`.
     * - No field is defined twice in the same class.
     * - Overriding methods have the same signature as their parent declaration.
     *
     * Must be run after `check_cycles()`.
     *
     * @param p The root AST node of the program.
     */
    void collect_members(Program* p);

    /**
     * PASS 4 —
     * 
     * @brief Recursively type-checks all method bodies and field initializers.
     * 
     * Checks that:
     * - All expressions are well-typed.
     * - Method calls have correct number and types of arguments.
     * - The return type of each method body matches its declared return type.
     * 
     * Must be run after `collect_members()`.
     * 
     * @param e The expression to type-check.
     */
    std::string typecheck_expr(Expr* e, std::map<std::string, std::string>& scope, const std::string& current_class);

    /**
     * @brief Checks if type A is a subtype of type B in the class hierarchy.
     *        Needed for: assignment, method arguments, if-then-else branches.
     * @return true if A == B or A inherits from B (directly or transitively).
     */
    bool is_subtype(const std::string& type_a, const std::string& type_b);

    /**
     * @brief Computes the Lowest Common Ancestor of two types in the hierarchy.
     *        Needed for: if-then-else return type (common type of both branches).
     * @return The nearest common ancestor type (always exists since Object is root).
     */
    std::string lca(const std::string& l_type, const std::string& r_type);

    // Shared data struct
    std::map<std::string, ClassDecl*> class_table;
    std::map<std::string, std::map<std::string, std::string>>     field_table;  // class -> {field -> type}
    std::map<std::string, std::map<std::string, MethodSignature>> method_table; // class -> {method -> sig}

    bool has_error = false;
    void error(int line, int col, const std::string& msg);
    
};