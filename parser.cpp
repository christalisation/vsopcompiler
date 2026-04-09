// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 55 "parser.ypp"

    #include "driver.hpp"

    using namespace std;

#line 52 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 21 "parser.ypp"
namespace VSOP {
#line 145 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (VSOP::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< Block* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_decl: // class_decl
        value.YY_MOVE_OR_COPY< ClassDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_features: // features
        value.YY_MOVE_OR_COPY< Features > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< Formal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< Method* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
        value.YY_MOVE_OR_COPY< std::vector<ClassDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.YY_MOVE_OR_COPY< std::vector<Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< std::vector<Formal*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_methods: // methods
        value.YY_MOVE_OR_COPY< std::vector<Method*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.move< Block* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_decl: // class_decl
        value.move< ClassDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_features: // features
        value.move< Features > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< Formal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< Method* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_type: // type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
        value.move< std::vector<ClassDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<Formal*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_methods: // methods
        value.move< std::vector<Method*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.copy< Block* > (that.value);
        break;

      case symbol_kind::S_class_decl: // class_decl
        value.copy< ClassDecl* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< Expr* > (that.value);
        break;

      case symbol_kind::S_features: // features
        value.copy< Features > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< Field* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< Formal* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< Method* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Program* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_type: // type
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_classes: // classes
        value.copy< std::vector<ClassDecl*> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_fields: // fields
        value.copy< std::vector<Field*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.copy< std::vector<Formal*> > (that.value);
        break;

      case symbol_kind::S_methods: // methods
        value.copy< std::vector<Method*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.move< Block* > (that.value);
        break;

      case symbol_kind::S_class_decl: // class_decl
        value.move< ClassDecl* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< Expr* > (that.value);
        break;

      case symbol_kind::S_features: // features
        value.move< Features > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< Field* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< Formal* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< Method* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_type: // type
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_classes: // classes
        value.move< std::vector<ClassDecl*> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_fields: // fields
        value.move< std::vector<Field*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<Formal*> > (that.value);
        break;

      case symbol_kind::S_methods: // methods
        value.move< std::vector<Method*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_block: // block
        yylhs.value.emplace< Block* > ();
        break;

      case symbol_kind::S_class_decl: // class_decl
        yylhs.value.emplace< ClassDecl* > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< Expr* > ();
        break;

      case symbol_kind::S_features: // features
        yylhs.value.emplace< Features > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< Field* > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< Formal* > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< Method* > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Program* > ();
        break;

      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_type: // type
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_classes: // classes
        yylhs.value.emplace< std::vector<ClassDecl*> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< std::vector<Expr*> > ();
        break;

      case symbol_kind::S_fields: // fields
        yylhs.value.emplace< std::vector<Field*> > ();
        break;

      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< std::vector<Formal*> > ();
        break;

      case symbol_kind::S_methods: // methods
        yylhs.value.emplace< std::vector<Method*> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: classes
#line 153 "parser.ypp"
    {
        auto* p = new Program();
        p->classes = yystack_[0].value.as < std::vector<ClassDecl*> > ();
        yylhs.value.as < Program* > () = p;
        driver.program = p;
    }
#line 859 "parser.cpp"
    break;

  case 3: // classes: class_decl
#line 161 "parser.ypp"
                           { yylhs.value.as < std::vector<ClassDecl*> > () = {yystack_[0].value.as < ClassDecl* > ()}; }
#line 865 "parser.cpp"
    break;

  case 4: // classes: classes class_decl
#line 162 "parser.ypp"
                           { yylhs.value.as < std::vector<ClassDecl*> > () = yystack_[1].value.as < std::vector<ClassDecl*> > (); yylhs.value.as < std::vector<ClassDecl*> > ().push_back(yystack_[0].value.as < ClassDecl* > ()); }
#line 871 "parser.cpp"
    break;

  case 5: // class_decl: "class" "type-identifier" "{" features "}"
#line 166 "parser.ypp"
    {  
        auto* c = new ClassDecl();
        c->name = yystack_[3].value.as < std::string > ();
        c->parent = "Object"; // set default parent
        c->fields = yystack_[1].value.as < Features > ().fields;
        c->methods = yystack_[1].value.as < Features > ().methods;
        yylhs.value.as < ClassDecl* > () = c;
    }
#line 884 "parser.cpp"
    break;

  case 6: // class_decl: "class" "type-identifier" "extends" "type-identifier" "{" fields methods "}"
#line 175 "parser.ypp"
        {
            auto* c = new ClassDecl();
            c->name = yystack_[6].value.as < std::string > ();
            c->parent = yystack_[4].value.as < std::string > (); // set parent from EXTENDS
            c->fields = yystack_[2].value.as < std::vector<Field*> > ();
            c->methods = yystack_[1].value.as < std::vector<Method*> > ();
            yylhs.value.as < ClassDecl* > () = c;
        }
#line 897 "parser.cpp"
    break;

  case 7: // features: %empty
#line 185 "parser.ypp"
                         { yylhs.value.as < Features > () = {}; }
#line 903 "parser.cpp"
    break;

  case 8: // features: features field
#line 186 "parser.ypp"
                         { yylhs.value.as < Features > () = yystack_[1].value.as < Features > (); yylhs.value.as < Features > ().fields.push_back(yystack_[0].value.as < Field* > ()); }
#line 909 "parser.cpp"
    break;

  case 9: // features: features method
#line 187 "parser.ypp"
                         { yylhs.value.as < Features > () = yystack_[1].value.as < Features > (); yylhs.value.as < Features > ().methods.push_back(yystack_[0].value.as < Method* > ()); }
#line 915 "parser.cpp"
    break;

  case 10: // fields: %empty
#line 190 "parser.ypp"
                          { yylhs.value.as < std::vector<Field*> > () = {}; }
#line 921 "parser.cpp"
    break;

  case 11: // fields: fields field
#line 191 "parser.ypp"
                          { yylhs.value.as < std::vector<Field*> > () = yystack_[1].value.as < std::vector<Field*> > (); yylhs.value.as < std::vector<Field*> > ().push_back(yystack_[0].value.as < Field* > ()); }
#line 927 "parser.cpp"
    break;

  case 12: // field: "object-identifier" ":" type ";"
#line 195 "parser.ypp"
    {
        auto* f = new Field();
        f->name = yystack_[3].value.as < std::string > ();
        f->type = yystack_[1].value.as < std::string > ();
        f->init_expr = nullptr; // no initializer for fields
        yylhs.value.as < Field* > () = f;
    }
#line 939 "parser.cpp"
    break;

  case 13: // field: "object-identifier" ":" type "<-" expr ";"
#line 203 "parser.ypp"
    {
        auto* f = new Field();
        f->name = yystack_[5].value.as < std::string > ();
        f->type = yystack_[3].value.as < std::string > ();
        f->init_expr = yystack_[1].value.as < Expr* > (); // set initializer from expression
        yylhs.value.as < Field* > () = f;
    }
#line 951 "parser.cpp"
    break;

  case 14: // methods: %empty
#line 212 "parser.ypp"
                          { yylhs.value.as < std::vector<Method*> > () = {}; }
#line 957 "parser.cpp"
    break;

  case 15: // methods: methods method
#line 213 "parser.ypp"
                           { yylhs.value.as < std::vector<Method*> > () = yystack_[1].value.as < std::vector<Method*> > (); yylhs.value.as < std::vector<Method*> > ().push_back(yystack_[0].value.as < Method* > ()); }
#line 963 "parser.cpp"
    break;

  case 16: // method: "object-identifier" "(" formals ")" ":" type block
#line 217 "parser.ypp"
    {
        auto* m = new Method();
        m->name = yystack_[6].value.as < std::string > ();
        m->formals = yystack_[4].value.as < std::vector<Formal*> > ();
        m->ret_type = yystack_[1].value.as < std::string > ();
        m->block = yystack_[0].value.as < Block* > ();
        yylhs.value.as < Method* > () = m;
    }
#line 976 "parser.cpp"
    break;

  case 17: // type: "type-identifier"
#line 227 "parser.ypp"
                             { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 982 "parser.cpp"
    break;

  case 18: // type: "int32"
#line 228 "parser.ypp"
                             { yylhs.value.as < std::string > () = "int32"; }
#line 988 "parser.cpp"
    break;

  case 19: // type: "bool"
#line 229 "parser.ypp"
                             { yylhs.value.as < std::string > () = "bool"; }
#line 994 "parser.cpp"
    break;

  case 20: // type: "string"
#line 230 "parser.ypp"
                             { yylhs.value.as < std::string > () = "string"; }
#line 1000 "parser.cpp"
    break;

  case 21: // type: "unit"
#line 231 "parser.ypp"
                             { yylhs.value.as < std::string > () = "unit"; }
#line 1006 "parser.cpp"
    break;

  case 22: // formals: %empty
#line 234 "parser.ypp"
                          { yylhs.value.as < std::vector<Formal*> > () = {}; }
#line 1012 "parser.cpp"
    break;

  case 23: // formals: formal
#line 235 "parser.ypp"
                          { yylhs.value.as < std::vector<Formal*> > () = {yystack_[0].value.as < Formal* > ()}; }
#line 1018 "parser.cpp"
    break;

  case 24: // formals: formals "," formal
#line 236 "parser.ypp"
                         { yylhs.value.as < std::vector<Formal*> > () = yystack_[2].value.as < std::vector<Formal*> > (); yylhs.value.as < std::vector<Formal*> > ().push_back(yystack_[0].value.as < Formal* > ()); }
#line 1024 "parser.cpp"
    break;

  case 25: // formal: "object-identifier" ":" type
#line 240 "parser.ypp"
    {
        auto* f = new Formal();
        f->name = yystack_[2].value.as < std::string > ();
        f->type = yystack_[0].value.as < std::string > ();
        yylhs.value.as < Formal* > () = f;
    }
#line 1035 "parser.cpp"
    break;

  case 26: // block: "{" expr_list "}"
#line 249 "parser.ypp"
    {
        auto* b = new Block();
        b->expr_list = yystack_[1].value.as < std::vector<Expr*> > ();
        yylhs.value.as < Block* > () = b;
    }
#line 1045 "parser.cpp"
    break;

  case 27: // expr_list: expr_list ";" expr
#line 256 "parser.ypp"
                             { yylhs.value.as < std::vector<Expr*> > () = yystack_[2].value.as < std::vector<Expr*> > (); yylhs.value.as < std::vector<Expr*> > ().push_back(yystack_[0].value.as < Expr* > ()); }
#line 1051 "parser.cpp"
    break;

  case 28: // expr_list: expr
#line 257 "parser.ypp"
                             { yylhs.value.as < std::vector<Expr*> > () = {yystack_[0].value.as < Expr* > ()}; }
#line 1057 "parser.cpp"
    break;

  case 29: // expr: "integer-literal"
#line 260 "parser.ypp"
                             { auto* i = new IntLiteral(); i->value = yystack_[0].value.as < int > (); yylhs.value.as < Expr* > () = i; }
#line 1063 "parser.cpp"
    break;

  case 30: // expr: "string-literal"
#line 261 "parser.ypp"
                               { auto* s = new StringLiteral(); s->value = yystack_[0].value.as < std::string > (); yylhs.value.as < Expr* > () = s; }
#line 1069 "parser.cpp"
    break;

  case 31: // expr: "true"
#line 262 "parser.ypp"
                               { auto* b = new BoolLiteral(); b->value = true; yylhs.value.as < Expr* > () = b; }
#line 1075 "parser.cpp"
    break;

  case 32: // expr: "false"
#line 263 "parser.ypp"
                               { auto* b = new BoolLiteral(); b->value = false; yylhs.value.as < Expr* > () = b; }
#line 1081 "parser.cpp"
    break;

  case 33: // expr: "object-identifier"
#line 264 "parser.ypp"
                               { auto* o = new ObjectID(); o->name = yystack_[0].value.as < std::string > (); yylhs.value.as < Expr* > () = o; }
#line 1087 "parser.cpp"
    break;

  case 34: // expr: "self"
#line 265 "parser.ypp"
                               { auto* o = new ObjectID(); o->name = "self"; yylhs.value.as < Expr* > () = o; }
#line 1093 "parser.cpp"
    break;

  case 35: // expr: "new" type
#line 266 "parser.ypp"
                            { auto* n = new New(); n->type_name = yystack_[0].value.as < std::string > (); yylhs.value.as < Expr* > () = n; }
#line 1099 "parser.cpp"
    break;

  case 36: // expr: "object-identifier" "<-" expr
#line 267 "parser.ypp"
                               { auto* a = new Assign(); a->name = yystack_[2].value.as < std::string > (); a->expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = a; }
#line 1105 "parser.cpp"
    break;

  case 37: // expr: expr "+" expr
#line 268 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "+"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1111 "parser.cpp"
    break;

  case 38: // expr: "-" expr
#line 269 "parser.ypp"
                              { auto* u = new UnaryOp(); u->op = "-"; u->expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = u; }
#line 1117 "parser.cpp"
    break;

  case 39: // expr: expr "-" expr
#line 270 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "-"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1123 "parser.cpp"
    break;

  case 40: // expr: expr "*" expr
#line 271 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "*"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1129 "parser.cpp"
    break;

  case 41: // expr: expr "/" expr
#line 272 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "/"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1135 "parser.cpp"
    break;

  case 42: // expr: expr "^" expr
#line 273 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "^"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1141 "parser.cpp"
    break;

  case 43: // expr: expr "and" expr
#line 274 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "and"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1147 "parser.cpp"
    break;

  case 44: // expr: expr "=" expr
#line 275 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "="; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1153 "parser.cpp"
    break;

  case 45: // expr: expr "<" expr
#line 276 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "<"; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1159 "parser.cpp"
    break;

  case 46: // expr: expr "<=" expr
#line 277 "parser.ypp"
                               { auto* b = new BinaryOp(); b->op = "<="; b->left_expr = yystack_[2].value.as < Expr* > (); b->right_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = b; }
#line 1165 "parser.cpp"
    break;

  case 47: // expr: "not" expr
#line 278 "parser.ypp"
                               { auto* u = new UnaryOp(); u->op = "not"; u->expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = u; }
#line 1171 "parser.cpp"
    break;

  case 48: // expr: "isnull" expr
#line 279 "parser.ypp"
                               { auto* u = new UnaryOp(); u->op = "isnull"; u->expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = u; }
#line 1177 "parser.cpp"
    break;

  case 49: // expr: "if" expr "then" expr "else" expr
#line 280 "parser.ypp"
                                  { auto* i = new If(); i->cond_expr = yystack_[4].value.as < Expr* > (); i->then_expr = yystack_[2].value.as < Expr* > (); i->else_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = i; }
#line 1183 "parser.cpp"
    break;

  case 50: // expr: "if" expr "then" expr
#line 281 "parser.ypp"
                                         { auto* i = new If(); i->cond_expr = yystack_[2].value.as < Expr* > (); i->then_expr = yystack_[0].value.as < Expr* > (); i->else_expr = nullptr; yylhs.value.as < Expr* > () = i; }
#line 1189 "parser.cpp"
    break;

  case 51: // expr: "while" expr "do" expr
#line 282 "parser.ypp"
                                        { auto* w = new While(); w->cond_expr = yystack_[2].value.as < Expr* > (); w->body_expr = yystack_[0].value.as < Expr* > (); yylhs.value.as < Expr* > () = w; }
#line 1195 "parser.cpp"
    break;

  case 52: // expr: "let" "object-identifier" ":" type "<-" expr "in" expr
#line 284 "parser.ypp"
        {
            auto* l = new Let();
            l->name = yystack_[6].value.as < std::string > ();
            l->type = yystack_[4].value.as < std::string > ();
            l->init_expr = yystack_[2].value.as < Expr* > ();
            l->scope_expr = yystack_[0].value.as < Expr* > ();
            yylhs.value.as < Expr* > () = l;
        }
#line 1208 "parser.cpp"
    break;

  case 53: // expr: "let" "object-identifier" ":" type "in" expr
#line 293 "parser.ypp"
        {
            auto* l = new Let();
            l->name = yystack_[4].value.as < std::string > ();
            l->type = yystack_[2].value.as < std::string > ();
            l->init_expr = nullptr; // no initializer
            l->scope_expr = yystack_[0].value.as < Expr* > ();
            yylhs.value.as < Expr* > () = l;
        }
#line 1221 "parser.cpp"
    break;

  case 54: // expr: expr "." "object-identifier" "(" expr_list ")"
#line 302 "parser.ypp"
        {
            auto* c = new Call();
            c->obj_expr = yystack_[5].value.as < Expr* > ();
            c->method_name = yystack_[3].value.as < std::string > ();
            c->expr_list = yystack_[1].value.as < std::vector<Expr*> > ();
            yylhs.value.as < Expr* > () = c;
        }
#line 1233 "parser.cpp"
    break;

  case 55: // expr: "object-identifier" "(" expr_list ")"
#line 310 "parser.ypp"
        {
            auto* c = new Call();
            c->obj_expr = nullptr; // no object, call on self
            c->method_name = yystack_[3].value.as < std::string > ();
            c->expr_list = yystack_[1].value.as < std::vector<Expr*> > ();
            yylhs.value.as < Expr* > () = c;
        }
#line 1245 "parser.cpp"
    break;

  case 56: // expr: "(" expr ")"
#line 317 "parser.ypp"
                        { yylhs.value.as < Expr* > () = yystack_[1].value.as < Expr* > (); }
#line 1251 "parser.cpp"
    break;

  case 57: // expr: block
#line 318 "parser.ypp"
                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Block* > (); }
#line 1257 "parser.cpp"
    break;


#line 1261 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char Parser::yypact_ninf_ = -64;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      23,    20,    35,    23,   -64,     9,   -64,   -64,    31,   -64,
      57,   -20,   -64,   -64,    24,   -64,   -64,    40,    74,    -2,
      93,   -64,     3,    94,    39,   -64,   -64,   -64,   -64,   -64,
     -64,   -10,   -64,    99,   -64,    -2,    98,    74,   -64,    44,
     -64,    -2,   -64,   -64,    44,    44,    92,    -2,    44,   -64,
     -64,    44,    44,    44,    44,   -64,   -64,   -14,   -64,    59,
     114,    79,    21,   111,   -64,   150,    70,     2,   141,    96,
     -64,    44,    44,    44,   -64,    44,    44,    44,    44,    44,
      95,    44,    44,    44,   -64,    44,    -2,    44,   -64,    44,
     -64,    51,   141,   150,   -12,   -12,    21,    21,    21,   115,
     159,   159,   159,   116,    -8,   -64,   141,   -64,    44,    44,
      44,    44,    55,   141,   141,   132,   -64,    44,   141
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,     0,     7,
       0,     0,    10,     5,     0,     8,     9,    14,    22,     0,
       0,    11,     0,     0,     0,    23,    19,    18,    20,    21,
      17,     0,     6,     0,    15,     0,     0,     0,    12,     0,
      25,     0,    24,    32,     0,     0,     0,     0,     0,    34,
      31,     0,     0,     0,     0,    29,    30,    33,    57,     0,
       0,     0,    48,     0,    35,    47,     0,     0,    28,     0,
      38,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,     0,    26,     0,
      56,     0,    36,    43,    37,    39,    40,    41,    42,     0,
      44,    45,    46,    50,     0,    51,    27,    55,     0,     0,
       0,     0,     0,    49,    53,     0,    54,     0,    52
  };

  const short
  Parser::yypgoto_[] =
  {
     -64,   -64,   -64,   138,   -64,   -64,   125,   -64,   123,   -34,
     -64,   118,    97,   -63,   -39
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    11,    17,    15,    22,    16,    31,
      24,    25,    58,    67,    68
  };

  const signed char
  Parser::yytable_[] =
  {
      59,    40,    26,   110,    13,    61,    62,    60,    91,    65,
      27,    71,    66,    64,    69,    70,    28,     8,    38,    29,
      77,    78,    79,    80,    14,    72,    88,    32,     1,    39,
      89,   111,     9,    92,    93,     6,    94,    95,    96,    97,
      98,    30,   100,   101,   102,   112,   103,    33,   105,    18,
     106,    19,   104,    43,    44,    79,    80,    45,    46,    47,
      48,    49,    73,     5,    50,    36,    51,    52,    37,    53,
     113,   114,   115,    73,    10,    54,    87,   107,   118,    89,
      12,   116,    73,    89,    20,    55,    56,    74,    57,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    85,    73,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    23,    73,
      19,    35,    90,   109,    18,    41,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    73,    63,    52,    86,    99,
     108,     7,    21,   117,    73,    34,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    42,     0,    84,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1
  };

  const signed char
  Parser::yycheck_[] =
  {
      39,    35,     4,    11,    24,    44,    45,    41,    71,    48,
      12,    25,    51,    47,    53,    54,    18,     8,    28,    21,
      32,    33,    34,    35,    44,    39,    24,    24,     5,    39,
      28,    39,    23,    72,    73,     0,    75,    76,    77,    78,
      79,    43,    81,    82,    83,   108,    85,    44,    87,    25,
      89,    27,    86,     9,    10,    34,    35,    13,    14,    15,
      16,    17,     3,    43,    20,    26,    22,    23,    29,    25,
     109,   110,   111,     3,    43,    31,     6,    26,   117,    28,
      23,    26,     3,    28,    44,    41,    42,    28,    44,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    19,     3,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    44,     3,
      27,    27,    26,     7,    25,    27,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     3,    44,    23,    27,    44,
      25,     3,    17,    11,     3,    22,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    37,    -1,    60,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    30,
      31,    32,    33,    34,    35,    36,    37,    38
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     5,    46,    47,    48,    43,     0,    48,     8,    23,
      43,    49,    23,    24,    44,    51,    53,    50,    25,    27,
      44,    51,    52,    44,    55,    56,     4,    12,    18,    21,
      43,    54,    24,    44,    53,    27,    26,    29,    28,    39,
      54,    27,    56,     9,    10,    13,    14,    15,    16,    17,
      20,    22,    23,    25,    31,    41,    42,    44,    57,    59,
      54,    59,    59,    44,    54,    59,    59,    58,    59,    59,
      59,    25,    39,     3,    28,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    57,    19,    27,     6,    24,    28,
      26,    58,    59,    59,    59,    59,    59,    59,    59,    44,
      59,    59,    59,    59,    54,    59,    59,    26,    25,     7,
      11,    39,    58,    59,    59,    59,    26,    11,    59
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    48,    48,    49,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    54,    54,    54,
      54,    54,    55,    55,    55,    56,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     5,     8,     0,     2,     2,
       0,     2,     4,     6,     0,     2,     7,     1,     1,     1,
       1,     1,     0,     1,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     6,
       4,     4,     8,     6,     6,     4,     3,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"and\"", "\"bool\"",
  "\"class\"", "\"do\"", "\"else\"", "\"extends\"", "\"false\"", "\"if\"",
  "\"in\"", "\"int32\"", "\"isnull\"", "\"let\"", "\"new\"", "\"not\"",
  "\"self\"", "\"string\"", "\"then\"", "\"true\"", "\"unit\"",
  "\"while\"", "\"{\"", "\"}\"", "\"(\"", "\")\"", "\":\"", "\";\"",
  "\",\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"^\"", "\".\"", "\"=\"",
  "\"<\"", "\"<=\"", "\"<-\"", "UMINUS", "\"integer-literal\"",
  "\"string-literal\"", "\"type-identifier\"", "\"object-identifier\"",
  "$accept", "program", "classes", "class_decl", "features", "fields",
  "field", "methods", "method", "type", "formals", "formal", "block",
  "expr_list", "expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   152,   152,   161,   162,   165,   174,   185,   186,   187,
     190,   191,   194,   202,   212,   213,   216,   227,   228,   229,
     230,   231,   234,   235,   236,   239,   248,   256,   257,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   292,   301,   309,   317,   318
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 21 "parser.ypp"
} // VSOP
#line 1655 "parser.cpp"

#line 321 "parser.ypp"

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
