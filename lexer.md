    /* Author: Christal Mangolopa
    * INFO0085 - Compilers
    * Uliege - Academic year 2025-2026
    * This flex/bison lexer implements the first part of the project
    * for a simple compiler for VSOP.
    *
    * You can use the '-l' flag to list all the tokens found in the 
    * source file, and the '-p' flag (or no flag) to parse the file
    * and to compute the result.
    *
    */


%{
    /* Includes */
    #include <string>

    #include "parser.hpp"
    #include "driver.hpp"
%}

    /* Flex options
     * - noyywrap: yylex will not call yywrap() function
     * - nounput: do not generate yyunput() function
     * - noinput: do not generate yyinput() function
     * - batch: tell Flex that the lexer will not often be used interactively
     */
%option noyywrap nounput noinput batch

%{
    /* Code to include at the beginning of the lexer file. */
    using namespace std;
    using namespace VSOP;

    // Print an lexical error message.
    static void print_error(const position &pos,
                            const string &m);

    // Code run each time a pattern is matched.
    #define YY_USER_ACTION  loc.columns(yyleng);

    // Global variable used to maintain the current location.
    location loc;

    // Global variable used to track the comment nesting level.
    int comment_depth = 0;
    position comment_start;

    // Global variables used for strings
    std::string string_buffer;
    position string_start;
%}

%x IN_COMMENT
%x IN_STRING

    /* Definitions */
t_id            [A-Z][a-zA-Z_0-9]*
o_id            [a-z][a-zA-Z_0-9]*
hexa_int        0x[0-9a-fA-F]+
bad_hexa_suffix 0x[0-9a-fA-F]+[a-zA-Z_][a-zA-Z0-9_]*
incomplet_hexa  0x
bad_int         [0-9]+[a-zA-Z_][a-zA-Z0-9_]*
int             [0-9]+
blank           [ \t\r\f]
line_comment    "//"[^\n]*

%%
%{
    // Code run each time yylex is called.
    loc.step();
%}
    /* Rules */
    
    /* Multi-line comments */

        /* Enter in comment */
"(*"        { BEGIN(IN_COMMENT); comment_depth++ ; comment_start = loc.begin; }

        /* Inside comment */
<IN_COMMENT>"(*" { comment_depth++; }
<IN_COMMENT>"*)" { comment_depth--; 
                    if (comment_depth == 0) 
                        BEGIN(INITIAL); }
<IN_COMMENT>\n   { loc.lines(1);loc.step(); }
<IN_COMMENT>.    { loc.step(); }
<IN_COMMENT><<EOF>> { print_error(comment_start, "unterminated comment");
                      BEGIN(INITIAL);
                      return Parser::make_YYerror(loc); }

    /* White spaces */
{blank}+    loc.step();
\n+         loc.lines(yyleng); loc.step();

    /* Single-line comments */
{line_comment}  loc.step();

    /* Operators */
"{"         return Parser::make_LBRACE(loc);
"}"         return Parser::make_RBRACE(loc);
"("         return Parser::make_LPAR(loc);
")"         return Parser::make_RPAR(loc);
":"         return Parser::make_COLON(loc);
";"         return Parser::make_SEMICOLON(loc);
","         return Parser::make_COMMA(loc);
"+"         return Parser::make_PLUS(loc);
"-"         return Parser::make_MINUS(loc);
"*"         return Parser::make_TIMES(loc);
"/"         return Parser::make_DIV(loc);
"^"         return Parser::make_POW(loc);
"."         return Parser::make_DOT(loc);
"="         return Parser::make_EQUAL(loc);
"<="        return Parser::make_LOWER_EQUAL(loc);
"<-"        return Parser::make_ASSIGN(loc);
"<"         return Parser::make_LOWER(loc);

    /* Keywords */
"and"    return Parser::make_AND(loc);
"bool"   return Parser::make_BOOL(loc);
"class"  return Parser::make_CLASS(loc);
"do"     return Parser::make_DO(loc);
"else"   return Parser::make_ELSE(loc);
"extends" return Parser::make_EXTENDS(loc);
"false"  return Parser::make_FALSE(loc);
"if"     return Parser::make_IF(loc);
"in"     return Parser::make_IN(loc);
"int32"  return Parser::make_INT32(loc);
"isnull" return Parser::make_ISNULL(loc);
"let"    return Parser::make_LET(loc);
"new"    return Parser::make_NEW(loc);
"not"    return Parser::make_NOT(loc);
"self"   return Parser::make_SELF(loc);
"string" return Parser::make_STRING(loc);
"then"   return Parser::make_THEN(loc);
"true"   return Parser::make_TRUE(loc);
"unit"   return Parser::make_UNIT(loc);
"while"  return Parser::make_WHILE(loc);

    /* Identifiers */
{t_id}    return Parser::make_TYPE_ID(std::string(yytext), loc);
{o_id}  return Parser::make_OBJECT_ID(std::string(yytext), loc);

    /* Integer literals */
{hexa_int}         { return Parser::make_INTEGER_LITERAL(stoi(yytext, nullptr, 16), loc); }
{incomplet_hexa}   { print_error(loc.begin, "invalid integer literal: " + string(yytext)); 
                    return Parser::make_YYerror(loc); }
{bad_int}          { print_error(loc.begin, "invalid integer literal: " + string(yytext)); 
                    return Parser::make_YYerror(loc); }
{int}              { return Parser::make_INTEGER_LITERAL(stoi(yytext), loc); }

    /* String literals */

        /* Enter in string */
\"          { string_buffer = "\"" ; string_start = loc.begin; BEGIN(IN_STRING); }

        /* Special characters */
<IN_STRING>\\b     { loc.step(); string_buffer += "\\x08"; }
<IN_STRING>\\t     { loc.step(); string_buffer += "\\x09"; }
<IN_STRING>\\n     { loc.step(); string_buffer += "\\x0a"; }
<IN_STRING>\\r     { loc.step(); string_buffer += "\\x0d"; }
<IN_STRING>\\\"    { loc.step(); string_buffer += "\\x22"; }
<IN_STRING>\\\\    { loc.step(); string_buffer += "\\x5c"; }

        /* \xhh hex escape */
<IN_STRING>\\x[0-9a-fA-F]{2} {
        int val = stoi(string(yytext + 2), nullptr, 16);
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "\\x%02x", val);
    string_buffer += buffer;
}
        /* Line continuation */
<IN_STRING>\\\n[ \t]*  { loc.lines(1); loc.step(); loc.columns(yyleng - 2);}

        /* Jump to next line -> error */
<IN_STRING>\n  { print_error(loc.begin, "raw newline in string");
                 BEGIN(INITIAL);
                 return Parser::make_YYerror(loc); }
        
        /* Close string */
<IN_STRING>\"  { string_buffer += "\"";
                 BEGIN(INITIAL);
                 location string_loc(string_start, loc.end);
                 return Parser::make_STRING_LITERAL(string_buffer, string_loc); }

        /* EOF in string -> error */
<IN_STRING><<EOF>>  { print_error(string_start, "unterminated string");
                      return Parser::make_YYerror(loc); }

        /* \x with less than 2 hex digits -> error */
<IN_STRING>\\x[0-9a-fA-F]?[^0-9a-fA-F]  {
    loc.step();
    print_error(loc.begin, "invalid \\x escape sequence");
    BEGIN(INITIAL);
    return Parser::make_YYerror(loc);
}

        /* \x followed by end of file -> error */
<IN_STRING>\\x<<EOF>> {
    print_error(loc.begin, "invalid \\x escape sequence");
    BEGIN(INITIAL);
    return Parser::make_YYerror(loc);
}

        /* Any other sequence \? -> error */
<IN_STRING>\\.  {
    loc.step();
    print_error(loc.begin, "invalid escape sequence");
    BEGIN(INITIAL);
    return Parser::make_YYerror(loc);
}

        /* Any other character */
<IN_STRING>.  { loc.step(); string_buffer += yytext[0]; }

    /* Invalid characters */
.           {
                print_error(loc.begin, "invalid character: " + string(yytext));
                return Parser::make_YYerror(loc);
}
    
    /* End of file */
<<EOF>>     return Parser::make_YYEOF(loc);
%%

    /* User code */


static void print_error(const position &pos, const string &m)
{
    cerr << *(pos.filename) << ":"
         << pos.line << ":"
         << pos.column << ":"
         << " lexical error: "
         << m
         << endl;
}

void Driver::scan_begin()
{
    loc.initialize(&source_file);

    if (source_file.empty() || source_file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(source_file.c_str(), "r")))
    {
        cerr << "cannot open " << source_file << ": " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
}

void Driver::scan_end()
{
    fclose(yyin);
}
