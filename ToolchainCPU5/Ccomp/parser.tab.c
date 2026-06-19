/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SP0 0x5fff       //0xc0ff
#define ArgLoc 0x6004    //0x7f02
#define ArgLocMax 0x7fff //0x7fff
#define VarLoc 0x8000    //0x4000
#define VarSpace 0x7fff  //0x3f00

#define SHORT_TYPE 0
#define LONG_TYPE 2
#define LONG_PTR_TYPE 3
#define SHORT_PTR_TYPE 4

#define UNSIGNED_SHORT_TYPE 6
#define UNSIGNED_LONG_TYPE 8
#define UNSIGNED_LONG_PTR_TYPE 9
#define UNSIGNED_SHORT_PTR_TYPE 10

#define IF_LOOP 1
#define WHILE_LOOP 2
#define FOR_LOOP 3

#define FIRST_REG 0
#define LAST_REG 14

int yylex(void);
void yyerror(const char *s);
int yywrap(void);

FILE *out;
extern FILE *yyin;

typedef struct {
    char name[64];
    int reg;
    int addr;
    int type;
} Var;

typedef struct {
    char name[64];
    int num_arg;
    int arg_offset;
    int ret_type;
    Var arg[32];
} Func;

Var vars[VarSpace];
Func func[4096];
int var_count = 0;
int func_count = 0;
int tmp_Arg_cnt = 0;
int Arg_set = 0;
int arg_count = 0;
int tmp_reg = 0; // R0..R14 pour temporaires
int labelCount = 0; // compteur global pour labels uniques
int LineCount = 0; // compteur de ligne du code source
int TMP_pipe = 0;
char func_pipe[64], func_expr_pipe[64];
const char Internal_Reg[11][8] = {"GPI0", "GPI1", "GPO0", "GPO1", "SPI", "CONFSPI", "UART","BAUDL", "BAUDH", "STATUS", "CONFINT"};


int test_name(const char *name){
    for (int i = 0; i < func_count; i++) {
        for (int j = 0; j < func[i].num_arg; j++) {
            if (strcmp(func[i].arg[j].name, name) == 0){
                yyerror(" Argument already exists with this name");
                return 1;
            }
        }
    }
    for (int j = 0; j < var_count; j++) {
        if (strcmp(vars[j].name, name) == 0){
            yyerror(" Variable already exists with this name");
            return 1;
        }
    }
    return 0; // Nom valide, pas de conflit
}
int get_func(const char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}


int create_var_reg(const char *name, short type, int byte_lenght) {
    if(test_name(name)) {
        return 0;
    }
    if (var_count >= VarSpace) {
        yyerror(" Variable limit reached, RAM full");
        return 0;
    }
    int reg = var_count;
    int addr = VarLoc + var_count;
    strncpy(vars[var_count].name, name, sizeof(vars[var_count].name)-1);
    vars[var_count].name[sizeof(vars[var_count].name)-1] = '\0';
    vars[var_count].addr = addr;
    var_count+=byte_lenght;
    switch (type) {
        case SHORT_TYPE:
            vars[reg].reg = reg;
            vars[reg].type = SHORT_TYPE;
            return reg;
        case SHORT_PTR_TYPE:
            vars[reg].reg = byte_lenght;
            vars[reg].type = SHORT_PTR_TYPE;
            return reg;
        case LONG_TYPE:
            vars[reg].reg = reg;
            vars[reg].type = LONG_TYPE;
            return reg;
        case LONG_PTR_TYPE:
            vars[reg].reg = byte_lenght;
            vars[reg].type = LONG_PTR_TYPE;
            return reg;

        case UNSIGNED_SHORT_TYPE:
            vars[reg].reg = reg;
            vars[reg].type = UNSIGNED_SHORT_TYPE;
            return reg;
        case UNSIGNED_SHORT_PTR_TYPE:
            vars[reg].reg = byte_lenght;
            vars[reg].type = UNSIGNED_SHORT_PTR_TYPE;
            return reg;
        case UNSIGNED_LONG_TYPE:
            vars[reg].reg = reg;
            vars[reg].type = UNSIGNED_LONG_TYPE;
            return reg;
        case UNSIGNED_LONG_PTR_TYPE:
            vars[reg].reg = byte_lenght;
            vars[reg].type = UNSIGNED_LONG_PTR_TYPE;
            return reg;
        default:
            yyerror(" Invalid variable type");
            return 0;
    }

}

int get_var_addr(const char *name, const char *func_name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) return vars[i].addr;
    }
    int tmp = get_func(func_name);
    for (int i = 0; i < func[tmp].num_arg; i++) {
        if (strcmp(func[tmp].arg[i].name, name) == 0) return func[tmp].arg[i].addr;
    }
    yyerror(" Variable/Arg doesn't exists");
    return 0;
}

int get_var_type(const char *name, const char *func_name) {
    int tmp = get_func(func_name);
    for (int i = 0; i < func[tmp].num_arg; i++) {
        if (strcmp(func[tmp].arg[i].name, name) == 0) return func[tmp].arg[i].type;
    }
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) return vars[i].type;
    }
    yyerror(" Variable doesn't exists");
    return 0;
}

int get_var_index(const char *name, const char *func_name) {
    int tmp = get_func(func_name);
    for (int i = 0; i < func[tmp].num_arg; i++) {
        if (strcmp(func[tmp].arg[i].name, name) == 0) return i;
    }
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) return i;
    }
    yyerror(" Variable doesn't exists");
    return 0;
}

int create_arg_reg(const char *name, int type,  const char *func_name) {
    if(test_name(name)) {
        yyerror(" Arg doesn't exists");
        return 0;
    }
    int tmp = get_func(func_name);
    int reg = func[tmp].num_arg;
    int addr = func[tmp].arg_offset + func[tmp].num_arg;
    strncpy(func[tmp].arg[reg].name, name, sizeof(func[tmp].arg[reg].name)-1);
    func[tmp].arg[reg].name[sizeof(func[tmp].arg[reg].name)-1] = '\0';
    func[tmp].arg[reg].reg = reg;
    func[tmp].arg[reg].addr = addr;
    func[tmp].arg[reg].type = type;
    if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
        func[tmp].num_arg+=2;
        arg_count+=2;
    }else{
        func[tmp].num_arg++;
        arg_count++;
    }
    return reg;
}

void create_func(const char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func[i].name, name) == 0){
            yyerror(" Function already exists");
            return;
        }
    }
    int reg = func_count;
    strncpy(func[func_count].name, name, sizeof(func[func_count].name)-1);
    func[func_count].name[sizeof(func[func_count].name)-1] = '\0';
    func[func_count].num_arg = 0;
    func[func_count].arg_offset = arg_count+ArgLoc;
    func_count++;
}


int new_tmp() {
    if (tmp_reg > LAST_REG) tmp_reg = FIRST_REG;
    return tmp_reg++;
}

int next_tmp(int reg) {
    if (reg > LAST_REG) reg = FIRST_REG;
    return reg++;
}

int get_reg_addr(const char* name) {
    for (int i = 0; i < 11; i++) {
        if (strcmp(name, Internal_Reg[i]) == 0)return i;
    }
    return -1;
}

int convert_str_intlist(char* list, int* intlist){
    int strlen_list = strlen(list);
    char buf[32];
    int num_cnt = 0;
    int buf_cnt = 0;
    for(int i = 0;i<strlen_list;i++){
        if(list[i]==','){
            buf[buf_cnt] = '\0';
            intlist[num_cnt]=atoi(buf);
            num_cnt++;
            buf_cnt=0;
        }else{
            buf[buf_cnt]=list[i];
            buf_cnt++;
        }
    }
    buf[buf_cnt] = '\0';
    intlist[num_cnt]=atoi(buf);
    num_cnt++;
    intlist[num_cnt]='\0';
    return num_cnt;
}

int label_stack[255];
int label_stack_ptr = 0;

int push_label(){
    label_stack[label_stack_ptr]=labelCount;
    label_stack_ptr++;
    labelCount++; 
    return labelCount-1;
}

int read_label(){
    return label_stack[label_stack_ptr-1];
}

int pop_label(){
    label_stack_ptr--;
    return label_stack[label_stack_ptr];
}


#line 354 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_SHORT = 7,                      /* SHORT  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_LONG = 9,                       /* LONG  */
  YYSYMBOL_USIGN = 10,                     /* USIGN  */
  YYSYMBOL_SIGN = 11,                      /* SIGN  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_LE = 19,                        /* LE  */
  YYSYMBOL_GE = 20,                        /* GE  */
  YYSYMBOL_LT = 21,                        /* LT  */
  YYSYMBOL_GT = 22,                        /* GT  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MUL = 25,                       /* MUL  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_SHL = 27,                       /* SHL  */
  YYSYMBOL_SHR = 28,                       /* SHR  */
  YYSYMBOL_BAND = 29,                      /* BAND  */
  YYSYMBOL_BOR = 30,                       /* BOR  */
  YYSYMBOL_BXOR = 31,                      /* BXOR  */
  YYSYMBOL_BNOT = 32,                      /* BNOT  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_GPI0 = 34,                      /* GPI0  */
  YYSYMBOL_GPI1 = 35,                      /* GPI1  */
  YYSYMBOL_GPO0 = 36,                      /* GPO0  */
  YYSYMBOL_GPO1 = 37,                      /* GPO1  */
  YYSYMBOL_SPI = 38,                       /* SPI  */
  YYSYMBOL_CONFSPI = 39,                   /* CONFSPI  */
  YYSYMBOL_UART = 40,                      /* UART  */
  YYSYMBOL_BAUDL = 41,                     /* BAUDL  */
  YYSYMBOL_BAUDH = 42,                     /* BAUDH  */
  YYSYMBOL_STATUS = 43,                    /* STATUS  */
  YYSYMBOL_CONFINT = 44,                   /* CONFINT  */
  YYSYMBOL_LPAREN = 45,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 46,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 47,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 48,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 49,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 50,                     /* COMMA  */
  YYSYMBOL_LCOMMENT = 51,                  /* LCOMMENT  */
  YYSYMBOL_RCOMMENT = 52,                  /* RCOMMENT  */
  YYSYMBOL_LBRACKET = 53,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 54,                  /* RBRACKET  */
  YYSYMBOL_QUOTE = 55,                     /* QUOTE  */
  YYSYMBOL_U = 56,                         /* U  */
  YYSYMBOL_L = 57,                         /* L  */
  YYSYMBOL_S = 58,                         /* S  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_op = 60,                        /* op  */
  YYSYMBOL_op_symetrical = 61,             /* op_symetrical  */
  YYSYMBOL_var_type_list = 62,             /* var_type_list  */
  YYSYMBOL_var_type_var = 63,              /* var_type_var  */
  YYSYMBOL_var_type_ptr = 64,              /* var_type_ptr  */
  YYSYMBOL_var_type = 65,                  /* var_type  */
  YYSYMBOL_arg_type_ptr = 66,              /* arg_type_ptr  */
  YYSYMBOL_arg_type_var = 67,              /* arg_type_var  */
  YYSYMBOL_arg_type = 68,                  /* arg_type  */
  YYSYMBOL_program = 69,                   /* program  */
  YYSYMBOL_element = 70,                   /* element  */
  YYSYMBOL_statement_list = 71,            /* statement_list  */
  YYSYMBOL_arguments_declaration = 72,     /* arguments_declaration  */
  YYSYMBOL_arguments = 73,                 /* arguments  */
  YYSYMBOL_func_set = 74,                  /* func_set  */
  YYSYMBOL_funcdeclaration = 75,           /* funcdeclaration  */
  YYSYMBOL_func_call = 76,                 /* func_call  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_const_list = 78,                /* const_list  */
  YYSYMBOL_declaration = 79,               /* declaration  */
  YYSYMBOL_assignment = 80,                /* assignment  */
  YYSYMBOL_expression = 81,                /* expression  */
  YYSYMBOL_comparable_expression = 82,     /* comparable_expression  */
  YYSYMBOL_simple_expression = 83,         /* simple_expression  */
  YYSYMBOL_condition = 84,                 /* condition  */
  YYSYMBOL_Else = 85,                      /* Else  */
  YYSYMBOL_If = 86,                        /* If  */
  YYSYMBOL_if_statement = 87,              /* if_statement  */
  YYSYMBOL_While = 88,                     /* While  */
  YYSYMBOL_while_statement = 89,           /* while_statement  */
  YYSYMBOL_Semicolon = 90,                 /* Semicolon  */
  YYSYMBOL_for_statement = 91,             /* for_statement  */
  YYSYMBOL_varname = 92,                   /* varname  */
  YYSYMBOL_funcname = 93                   /* funcname  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1066

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  261

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   338,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   350,   351,   352,   353,   354,   358,   362,   366,   370,
     374,   378,   384,   388,   392,   396,   400,   404,   410,   414,
     420,   421,   422,   426,   427,   430,   431,   432,   433,   434,
     435,   438,   439,   444,   446,   449,   450,   453,   455,   459,
     471,   488,   501,   521,   535,   558,   564,   570,   576,   582,
     591,   593,   598,   612,   633,   634,   635,   636,   637,   638,
     639,   640,   644,   650,   656,   666,   700,   715,   721,   730,
     741,   755,   797,   843,   881,   925,   942,   959,   979,  1003,
    1004,  1007,  1013,  1019,  1026,  1032,  1038,  1044,  1050,  1060,
    1061,  1088,  1116,  1139,  1147,  1157,  1164,  1168,  1177,  1187,
    1196,  1205,  1214,  1224,  1234,  1242,  1254,  1262,  1269,  1273,
    1280,  1289,  1298,  1307,  1316,  1317,  1318,  1319,  1320,  1321,
    1322,  1323,  1324,  1325,  1326,  1327,  1332
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "IDENT",
  "STRING", "VOID", "SHORT", "CHAR", "LONG", "USIGN", "SIGN", "IF", "ELSE",
  "WHILE", "FOR", "RETURN", "EQ", "NE", "LE", "GE", "LT", "GT", "PLUS",
  "MINUS", "MUL", "DIV", "SHL", "SHR", "BAND", "BOR", "BXOR", "BNOT",
  "ASSIGN", "GPI0", "GPI1", "GPO0", "GPO1", "SPI", "CONFSPI", "UART",
  "BAUDL", "BAUDH", "STATUS", "CONFINT", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "SEMICOLON", "COMMA", "LCOMMENT", "RCOMMENT", "LBRACKET",
  "RBRACKET", "QUOTE", "U", "L", "S", "$accept", "op", "op_symetrical",
  "var_type_list", "var_type_var", "var_type_ptr", "var_type",
  "arg_type_ptr", "arg_type_var", "arg_type", "program", "element",
  "statement_list", "arguments_declaration", "arguments", "func_set",
  "funcdeclaration", "func_call", "statement", "const_list", "declaration",
  "assignment", "expression", "comparable_expression", "simple_expression",
  "condition", "Else", "If", "if_statement", "While", "while_statement",
  "Semicolon", "for_statement", "varname", "funcname", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-184)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-137)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -184,   262,  -184,   -32,    32,    84,   128,    60,    82,  -184,
    -184,   -26,   286,   884,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,    16,  -184,  -184,    39,
    -184,    40,  -184,    35,  -184,    41,    48,    62,  -184,    63,
    -184,  -184,   928,    68,  -184,  -184,   906,    76,  -184,   906,
      89,  -184,   884,   884,   884,   884,    55,   114,   529,   884,
     884,   552,   575,  -184,  -184,   939,  -184,  -184,    93,  -184,
    1014,   417,    -4,   575,    15,  -184,  -184,  -184,   575,   575,
     132,   130,  -184,  -184,  -184,  -184,  -184,  -184,  -184,   575,
     598,   118,   483,  -184,  -184,   156,  -184,  -184,   171,   120,
     133,   134,   142,   781,   801,   135,  -184,  -184,  -184,  -184,
    -184,   575,   114,    30,  -184,  -184,   621,  -184,   948,  -184,
    -184,  -184,   644,   667,   575,   152,  -184,  -184,  -184,   206,
     907,   823,   843,   131,   170,   163,  -184,  -184,  -184,   -15,
    1035,   -16,    22,   165,   166,  -184,  -184,   907,     9,    51,
     690,  -184,  -184,     0,   907,   167,   169,   216,   217,   221,
     224,   884,   884,  -184,   575,   907,   127,   972,  -184,   114,
     907,    81,   177,   907,   713,  -184,   -30,   884,  -184,   884,
    -184,   884,   884,   884,   884,  -184,   182,   181,   575,   575,
     575,   575,   575,   575,   459,   459,   195,   200,    -2,   907,
    -184,   506,  -184,  -184,   185,   186,   188,   189,   196,   736,
     759,  -184,  -184,   207,   907,  -184,   241,  -184,  -184,  -184,
    -184,  -184,  -184,   330,  -184,  -184,   907,   907,   907,   907,
     907,   907,   233,  -184,   575,   575,  -184,   907,  -184,  -184,
    -184,  -184,   865,   981,    70,  1005,  -184,  -184,   375,  -184,
     459,   907,   907,   202,  -184,  -184,  -184,  -184,  -184,   459,
    -184
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      43,     0,     1,   124,     0,     0,     0,     0,     0,   117,
     120,     0,     0,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    47,    31,    30,    32,    78,
      44,     0,    45,     0,    46,     0,     0,     0,    65,     0,
      66,    67,     0,     0,   136,    55,     0,    22,    56,     0,
      23,    57,     0,     0,     0,     0,     0,   107,     0,     0,
       0,     0,     0,    72,    99,     0,    89,    90,   102,   124,
       0,     0,     0,     0,     0,    70,    68,    69,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,     0,    28,    59,     0,    29,    58,     0,    26,
      27,    24,    25,     0,     0,     0,    11,    12,    13,    14,
      15,     0,   105,    98,   104,   103,     0,    97,     0,     2,
       3,    71,     0,     0,     0,     0,    64,    48,    76,     0,
      77,     0,     0,     0,     0,     0,    42,    41,    49,     0,
       0,    89,    90,     0,     0,    85,    86,    79,   107,     0,
       0,    52,    62,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,   122,     0,    92,   107,     0,   106,    91,
      93,   107,     0,    80,     0,    73,     0,     0,    35,     0,
      36,     0,     0,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,    81,
      63,     0,    16,    17,     0,     0,     0,     0,     0,    13,
       8,   100,   101,   107,    82,    75,     0,    33,    34,    39,
      40,    37,    38,     0,    43,    50,   108,   109,   110,   111,
     112,   113,   119,   121,     0,     0,    54,    53,    20,    21,
      18,    19,     0,     0,   107,     0,    74,    60,     0,   116,
       0,    87,    88,     0,    95,    94,    96,    61,   118,     0,
     123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -184,   -28,  -184,  -184,  -184,  -184,  -184,  -184,  -184,    64,
    -183,  -184,  -184,  -184,  -184,  -184,  -184,     2,   -61,  -184,
     198,    13,    25,   -72,   -70,   -68,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,    -1,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,   122,   111,    26,    27,    28,    29,   136,   137,   138,
       1,    30,    71,   139,   153,    31,    32,    64,    34,   176,
      35,    36,   140,    66,    67,   143,   250,    37,    38,    39,
      40,   164,    41,    68,    43
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,   128,   223,    33,    47,    50,   141,   141,   142,   142,
     127,   144,    70,  -136,    91,    45,    48,    51,   215,    56,
     216,   106,   131,   107,   132,   133,   134,   108,   109,   110,
    -114,   186,   106,  -114,   107,   187,    44,    65,   108,   109,
     110,   248,   125,   129,   -83,    93,   200,   -83,    96,    72,
     201,    99,   100,   101,   102,    82,    83,    94,   114,   115,
      97,   135,   103,   196,   104,     7,     8,    52,  -115,    53,
      42,  -115,    73,    33,   119,   120,    82,    83,    84,    85,
      86,    87,    88,   113,    75,    74,   117,   118,     3,    54,
      76,    55,   141,   106,   142,   107,   208,    77,   130,   108,
     109,   110,    47,    50,   106,   197,   107,    78,    79,    46,
     108,   109,   110,    92,   147,   149,   255,   154,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    95,
     178,   180,     3,   232,   233,   211,   165,   106,   181,   107,
     182,   167,    98,   108,   109,   110,   123,   170,   172,   173,
     106,   150,   107,    49,   146,   145,   209,   109,   110,   155,
      93,    96,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,   157,   156,   199,   217,   183,   218,   184,
     219,   220,   221,   222,   163,   174,   158,   159,   131,   258,
     132,   133,   134,    42,    42,   160,    33,    33,   260,   214,
     119,   120,    82,    83,    84,    85,    86,    87,    88,   175,
     185,   194,   195,   226,   227,   228,   229,   230,   231,   204,
     205,   202,    42,   203,   206,    33,   237,   207,   234,   224,
     106,   212,   107,   235,   243,   245,   108,   109,   110,   238,
     239,    42,   240,   241,   246,   242,   249,    42,   259,    42,
      33,   225,    33,   -84,   105,   253,   -84,     0,    42,   251,
     252,    33,     2,     0,     0,     0,     3,     0,     4,     5,
       0,     6,     7,     8,     9,     0,    10,    11,    12,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    57,
       3,     0,     0,     0,     0,     0,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,    25,
      58,    59,     0,     0,     0,    60,     0,     0,    61,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    62,     0,     0,     3,    63,     4,     5,     0,     6,
       7,     8,     9,     0,    10,    11,    12,     0,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,    25,   247,     3,
       0,     4,     5,     0,     6,     7,     8,     9,     0,    10,
      11,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     3,    25,   257,   103,     0,   104,     7,     8,     9,
       0,    10,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,     3,    25,   126,   103,     0,   104,     7,
       8,     9,     0,    10,    11,    12,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,    57,     3,   151,     0,
       0,     0,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,    25,    58,    59,    57,
       3,   236,    60,     0,     0,    61,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    62,   152,
      58,    59,   112,     3,     0,    60,     0,     0,    61,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    62,     0,    58,    59,    57,     3,     0,    60,     0,
       0,    61,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    62,     0,    58,    59,    57,     3,
       0,    60,     0,     0,    61,     0,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   116,     0,    58,
      59,   148,     3,     0,    60,     0,     0,    61,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      62,     0,    58,    59,   166,     3,     0,    60,     0,     0,
      61,     0,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    62,     0,    58,    59,   169,     3,     0,
      60,     0,     0,    61,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    62,     0,    58,    59,
     171,     3,     0,    60,     0,     0,    61,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    62,
       0,    58,    59,   198,     3,     0,    60,     0,     0,    61,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    62,     0,    58,    59,   213,     3,     0,    60,
       0,     0,    61,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    62,     0,    58,    59,    57,
       3,     0,    60,     0,     0,    61,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    62,     0,
      58,    59,   244,     3,     0,     0,     0,     0,    61,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    62,     0,    58,    59,    69,     0,     0,     0,     0,
       0,    61,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    62,    69,   161,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   162,    69,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    69,   177,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   179,    69,
       0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    69,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       3,     0,     0,     0,     0,     0,     0,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
     119,   120,    82,    83,    84,    85,    86,    87,    88,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    80,    81,    82,    83,    84,    85,    86,    87,    88,
       0,    89,   119,   120,    82,    83,    84,    85,    86,    87,
      88,   119,   120,    82,    83,    84,    85,    86,    87,    88,
       0,    90,     0,     0,     0,     0,     0,     0,   121,     0,
       0,     0,     0,     0,   168,   119,   120,    82,    83,    84,
      85,   210,    87,    88,   119,   120,    82,    83,    84,    85,
      86,    87,    88,     0,     0,     0,     0,     0,   168,     0,
       0,     0,     0,     0,     0,     0,     0,   254,   119,   120,
      82,    83,    84,    85,    86,    87,    88,   119,   120,    82,
      83,    84,    85,    86,    87,    88,     0,   124,     0,     0,
       0,   256,   188,   189,   190,   191,   192,   193,   119,   120,
      82,    83,    84,    85,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
       1,     5,   185,     1,     5,     6,    78,    79,    78,    79,
      71,    79,    13,    45,    42,     4,     5,     6,    48,    45,
      50,    23,     7,    25,     9,    10,    11,    29,    30,    31,
      46,    46,    23,    49,    25,    50,     4,    12,    29,    30,
      31,   224,    70,    47,    46,    46,    46,    49,    49,    33,
      50,    52,    53,    54,    55,    25,    26,    46,    59,    60,
      49,    46,     7,    54,     9,    10,    11,     7,    46,     9,
      71,    49,    33,    71,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    58,    49,    45,    61,    62,     4,     7,
      49,     9,   164,    23,   164,    25,   164,    49,    73,    29,
      30,    31,   103,   104,    23,    54,    25,    45,    45,    25,
      29,    30,    31,    45,    89,    90,    46,    92,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    53,
     131,   132,     4,   194,   195,    54,   111,    23,     7,    25,
       9,   116,    53,    29,    30,    31,    53,   122,   123,   124,
      23,    33,    25,    25,    24,    23,    29,    30,    31,     3,
     161,   162,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    53,     3,   150,   177,     7,   179,     9,
     181,   182,   183,   184,    49,    33,    53,    53,     7,   250,
       9,    10,    11,   194,   195,    53,   194,   195,   259,   174,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     3,
      47,    46,    46,   188,   189,   190,   191,   192,   193,     3,
       3,    54,   223,    54,     3,   223,   201,     3,    33,    47,
      23,    54,    25,    33,   209,   210,    29,    30,    31,    54,
      54,   242,    54,    54,     3,    49,    13,   248,    46,   250,
     248,   187,   250,    46,    56,   242,    49,    -1,   259,   234,
     235,   259,     0,    -1,    -1,    -1,     4,    -1,     6,     7,
      -1,     9,    10,    11,    12,    -1,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,     3,
       4,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      24,    25,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,     4,    49,     6,     7,    -1,     9,
      10,    11,    12,    -1,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,     4,
      -1,     6,     7,    -1,     9,    10,    11,    12,    -1,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,     4,    47,    48,     7,    -1,     9,    10,    11,    12,
      -1,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,     4,    47,    48,     7,    -1,     9,    10,
      11,    12,    -1,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,     3,     4,     5,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    24,    25,     3,
       4,     5,    29,    -1,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      24,    25,     3,     4,    -1,    29,    -1,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    24,    25,     3,     4,    -1,    29,    -1,
      -1,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    24,    25,     3,     4,
      -1,    29,    -1,    -1,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    24,
      25,     3,     4,    -1,    29,    -1,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    24,    25,     3,     4,    -1,    29,    -1,    -1,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    24,    25,     3,     4,    -1,
      29,    -1,    -1,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    24,    25,
       3,     4,    -1,    29,    -1,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    24,    25,     3,     4,    -1,    29,    -1,    -1,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    24,    25,     3,     4,    -1,    29,
      -1,    -1,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    24,    25,     3,
       4,    -1,    29,    -1,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      24,    25,     3,     4,    -1,    -1,    -1,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    24,    25,     4,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     4,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    25,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,     4,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    25,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,     4,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    46,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      -1,    46,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    69,     0,     4,     6,     7,     9,    10,    11,    12,
      14,    15,    16,    25,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    47,    62,    63,    64,    65,
      70,    74,    75,    76,    77,    79,    80,    86,    87,    88,
      89,    91,    92,    93,     4,    93,    25,    92,    93,    25,
      92,    93,     7,     9,     7,     9,    45,     3,    24,    25,
      29,    32,    45,    49,    76,    81,    82,    83,    92,     4,
      92,    71,    33,    33,    45,    49,    49,    49,    45,    45,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    33,
      53,    60,    45,    92,    93,    53,    92,    93,    53,    92,
      92,    92,    92,     7,     9,    79,    23,    25,    29,    30,
      31,    61,     3,    81,    92,    92,    45,    81,    81,    23,
      24,    49,    60,    53,    33,    60,    48,    77,     5,    47,
      81,     7,     9,    10,    11,    46,    66,    67,    68,    72,
      81,    82,    83,    84,    84,    23,    24,    81,     3,    81,
      33,     5,    46,    73,    81,     3,     3,    53,    53,    53,
      53,    25,    25,    49,    90,    81,     3,    81,    46,     3,
      81,     3,    81,    81,    33,     3,    78,    25,    92,    25,
      92,     7,     9,     7,     9,    47,    46,    50,    17,    18,
      19,    20,    21,    22,    46,    46,    54,    54,     3,    81,
      46,    50,    54,    54,     3,     3,     3,     3,    84,    29,
      29,    54,    54,     3,    81,    48,    50,    92,    92,    92,
      92,    92,    92,    69,    47,    68,    81,    81,    81,    81,
      81,    81,    77,    77,    33,    33,     5,    81,    54,    54,
      54,    54,    49,    81,     3,    81,     3,    48,    69,    13,
      85,    81,    81,    80,    46,    46,    46,    48,    77,    46,
      77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    78,    78,    79,    79,    79,    79,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    86,    87,    87,
      88,    89,    90,    91,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     6,     6,
       6,     6,     2,     2,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     3,     3,     2,     2,     3,     3,     3,
       3,     1,     1,     0,     2,     1,     1,     0,     2,     1,
       3,     1,     1,     3,     3,     2,     2,     2,     3,     3,
       6,     7,     3,     4,     3,     1,     1,     1,     2,     2,
       2,     3,     2,     1,     3,     5,     3,     3,     1,     3,
       4,     4,     5,     4,     5,     3,     3,     6,     6,     1,
       1,     3,     3,     3,     6,     6,     6,     2,     2,     1,
       4,     4,     1,     2,     2,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     7,     5,
       1,     5,     1,     9,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* op: PLUS  */
#line 338 "parser.y"
         { (yyval.str) = "ADD"; }
#line 1774 "parser.tab.c"
    break;

  case 3: /* op: MINUS  */
#line 339 "parser.y"
            { (yyval.str) = "SUB"; }
#line 1780 "parser.tab.c"
    break;

  case 4: /* op: MUL  */
#line 340 "parser.y"
          { yyerror("Mult not implemented");(yyval.str) = "MUL"; }
#line 1786 "parser.tab.c"
    break;

  case 5: /* op: DIV  */
#line 341 "parser.y"
          { yyerror("Div not implemented");(yyval.str) = "DIV"; }
#line 1792 "parser.tab.c"
    break;

  case 6: /* op: SHL  */
#line 342 "parser.y"
          { (yyval.str) = "SHL"; }
#line 1798 "parser.tab.c"
    break;

  case 7: /* op: SHR  */
#line 343 "parser.y"
          { (yyval.str) = "SHR"; }
#line 1804 "parser.tab.c"
    break;

  case 8: /* op: BAND  */
#line 344 "parser.y"
           { (yyval.str) = "AND"; }
#line 1810 "parser.tab.c"
    break;

  case 9: /* op: BOR  */
#line 345 "parser.y"
          { (yyval.str) = "OR"; }
#line 1816 "parser.tab.c"
    break;

  case 10: /* op: BXOR  */
#line 346 "parser.y"
           { (yyval.str) = "XOR"; }
#line 1822 "parser.tab.c"
    break;

  case 11: /* op_symetrical: PLUS  */
#line 350 "parser.y"
         { (yyval.str) = "ADD"; }
#line 1828 "parser.tab.c"
    break;

  case 12: /* op_symetrical: MUL  */
#line 351 "parser.y"
          { yyerror("Mult not implemented");(yyval.str) = "MUL"; }
#line 1834 "parser.tab.c"
    break;

  case 13: /* op_symetrical: BAND  */
#line 352 "parser.y"
           { (yyval.str) = "AND"; }
#line 1840 "parser.tab.c"
    break;

  case 14: /* op_symetrical: BOR  */
#line 353 "parser.y"
          { (yyval.str) = "OR"; }
#line 1846 "parser.tab.c"
    break;

  case 15: /* op_symetrical: BXOR  */
#line 354 "parser.y"
           { (yyval.str) = "XOR"; }
#line 1852 "parser.tab.c"
    break;

  case 16: /* var_type_list: SHORT varname LBRACKET NUMBER RBRACKET  */
#line 358 "parser.y"
                                           { 
        create_var_reg((yyvsp[-3].str),SHORT_PTR_TYPE,(yyvsp[-1].num));
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1861 "parser.tab.c"
    break;

  case 17: /* var_type_list: LONG varname LBRACKET NUMBER RBRACKET  */
#line 362 "parser.y"
                                            { 
        create_var_reg((yyvsp[-3].str),LONG_PTR_TYPE,(yyvsp[-1].num)*2); 
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1870 "parser.tab.c"
    break;

  case 18: /* var_type_list: SIGN SHORT varname LBRACKET NUMBER RBRACKET  */
#line 366 "parser.y"
                                                  { 
        create_var_reg((yyvsp[-3].str),SHORT_PTR_TYPE,(yyvsp[-1].num));
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1879 "parser.tab.c"
    break;

  case 19: /* var_type_list: SIGN LONG varname LBRACKET NUMBER RBRACKET  */
#line 370 "parser.y"
                                                 { 
        create_var_reg((yyvsp[-3].str),LONG_PTR_TYPE,(yyvsp[-1].num)*2); 
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1888 "parser.tab.c"
    break;

  case 20: /* var_type_list: USIGN SHORT varname LBRACKET NUMBER RBRACKET  */
#line 374 "parser.y"
                                                   { 
        create_var_reg((yyvsp[-3].str),UNSIGNED_SHORT_PTR_TYPE,(yyvsp[-1].num));
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1897 "parser.tab.c"
    break;

  case 21: /* var_type_list: USIGN LONG varname LBRACKET NUMBER RBRACKET  */
#line 378 "parser.y"
                                                  { 
        create_var_reg((yyvsp[-3].str),UNSIGNED_LONG_PTR_TYPE,(yyvsp[-1].num)*2); 
        (yyval.str) = (yyvsp[-3].str);
    }
#line 1906 "parser.tab.c"
    break;

  case 22: /* var_type_var: SHORT varname  */
#line 384 "parser.y"
                 {
        create_var_reg((yyvsp[0].str),SHORT_TYPE,1); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1915 "parser.tab.c"
    break;

  case 23: /* var_type_var: LONG varname  */
#line 388 "parser.y"
                  { 
        create_var_reg((yyvsp[0].str),LONG_TYPE,2); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1924 "parser.tab.c"
    break;

  case 24: /* var_type_var: SIGN SHORT varname  */
#line 392 "parser.y"
                        { 
        create_var_reg((yyvsp[0].str),SHORT_TYPE,1); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1933 "parser.tab.c"
    break;

  case 25: /* var_type_var: SIGN LONG varname  */
#line 396 "parser.y"
                       { 
        create_var_reg((yyvsp[0].str),LONG_TYPE,2); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1942 "parser.tab.c"
    break;

  case 26: /* var_type_var: USIGN SHORT varname  */
#line 400 "parser.y"
                         { 
        create_var_reg((yyvsp[0].str),UNSIGNED_SHORT_TYPE,1); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1951 "parser.tab.c"
    break;

  case 27: /* var_type_var: USIGN LONG varname  */
#line 404 "parser.y"
                        { 
        create_var_reg((yyvsp[0].str),UNSIGNED_LONG_TYPE,2); 
        (yyval.str) = (yyvsp[0].str);
    }
#line 1960 "parser.tab.c"
    break;

  case 28: /* var_type_ptr: SHORT MUL varname  */
#line 410 "parser.y"
                     { 
        create_var_reg((yyvsp[0].str),SHORT_PTR_TYPE,1);
        (yyval.str) = (yyvsp[0].str); 
    }
#line 1969 "parser.tab.c"
    break;

  case 29: /* var_type_ptr: LONG MUL varname  */
#line 414 "parser.y"
                      { 
        create_var_reg((yyvsp[0].str),LONG_PTR_TYPE,2);
        (yyval.str) = (yyvsp[0].str); 
    }
#line 1978 "parser.tab.c"
    break;

  case 30: /* var_type: var_type_var  */
#line 420 "parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1984 "parser.tab.c"
    break;

  case 31: /* var_type: var_type_list  */
#line 421 "parser.y"
                   { (yyval.str) = (yyvsp[0].str); }
#line 1990 "parser.tab.c"
    break;

  case 32: /* var_type: var_type_ptr  */
#line 422 "parser.y"
                  { (yyval.str) = (yyvsp[0].str); }
#line 1996 "parser.tab.c"
    break;

  case 33: /* arg_type_ptr: SHORT MUL varname  */
#line 426 "parser.y"
                     { (yyval.num) = create_arg_reg((yyvsp[0].str),SHORT_PTR_TYPE,func_pipe); }
#line 2002 "parser.tab.c"
    break;

  case 34: /* arg_type_ptr: LONG MUL varname  */
#line 427 "parser.y"
                      { (yyval.num) = create_arg_reg((yyvsp[0].str),LONG_PTR_TYPE,func_pipe); }
#line 2008 "parser.tab.c"
    break;

  case 35: /* arg_type_var: SHORT varname  */
#line 430 "parser.y"
                 { (yyval.num) = create_arg_reg((yyvsp[0].str),SHORT_TYPE,func_pipe); }
#line 2014 "parser.tab.c"
    break;

  case 36: /* arg_type_var: LONG varname  */
#line 431 "parser.y"
                  { (yyval.num) = create_arg_reg((yyvsp[0].str),LONG_TYPE,func_pipe); }
#line 2020 "parser.tab.c"
    break;

  case 37: /* arg_type_var: SIGN SHORT varname  */
#line 432 "parser.y"
                        { (yyval.num) = create_arg_reg((yyvsp[0].str),SHORT_TYPE,func_pipe); }
#line 2026 "parser.tab.c"
    break;

  case 38: /* arg_type_var: SIGN LONG varname  */
#line 433 "parser.y"
                       { (yyval.num) = create_arg_reg((yyvsp[0].str),LONG_TYPE,func_pipe); }
#line 2032 "parser.tab.c"
    break;

  case 39: /* arg_type_var: USIGN SHORT varname  */
#line 434 "parser.y"
                         { (yyval.num) = create_arg_reg((yyvsp[0].str),UNSIGNED_SHORT_TYPE,func_pipe); }
#line 2038 "parser.tab.c"
    break;

  case 40: /* arg_type_var: USIGN LONG varname  */
#line 435 "parser.y"
                        { (yyval.num) = create_arg_reg((yyvsp[0].str),UNSIGNED_LONG_TYPE,func_pipe); }
#line 2044 "parser.tab.c"
    break;

  case 41: /* arg_type: arg_type_var  */
#line 438 "parser.y"
                { (yyval.num) = (yyvsp[0].num); }
#line 2050 "parser.tab.c"
    break;

  case 42: /* arg_type: arg_type_ptr  */
#line 439 "parser.y"
                  { (yyval.num) = (yyvsp[0].num); }
#line 2056 "parser.tab.c"
    break;

  case 45: /* element: funcdeclaration  */
#line 449 "parser.y"
                    { LineCount++;}
#line 2062 "parser.tab.c"
    break;

  case 49: /* arguments_declaration: arg_type  */
#line 459 "parser.y"
            {
        int r = (yyvsp[0].num);
        int tmp = get_func(func_pipe);
        int type = func[tmp].arg[r].type;
        if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
            fprintf(out, " ; argument (%dL) %s addr=0x%04x\n", func[tmp].arg[r].type,func[tmp].arg[r].name, func[tmp].arg[r].addr);
            fprintf(out, " ; argument (%dH) %s addr=0x%04x\n", func[tmp].arg[r].type,func[tmp].arg[r].name, func[tmp].arg[r].addr+1);
        }else{
            fprintf(out, " ; argument (%d) %s addr=0x%04x\n", func[tmp].arg[r].type,func[tmp].arg[r].name, func[tmp].arg[r].addr);
        }
        (yyval.num) = 1;
    }
#line 2079 "parser.tab.c"
    break;

  case 50: /* arguments_declaration: arguments_declaration COMMA arg_type  */
#line 472 "parser.y"
    {
        int r = (yyvsp[0].num);
        int tmp = get_func(func_pipe);
        int type = func[tmp].arg[r].type;
        if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
            fprintf(out, " ; argument (%dL) %s addr=0x%04x\n", func[tmp].arg[r].type,func[tmp].arg[r].name, func[tmp].arg[r].addr);
            fprintf(out, " ; argument (%dH) %s addr=0x%04x\n", func[tmp].arg[r].type,func[tmp].arg[r].name, func[tmp].arg[r].addr+1);
            (yyval.num) = (yyvsp[0].num)+2;
        }else{
            fprintf(out, " ; argument (%d) %s addr=0x%04x\n", func[tmp].arg[r].type, func[tmp].arg[r].name, func[tmp].arg[r].addr);
            (yyval.num) = (yyvsp[0].num)+1;
        }
    }
#line 2097 "parser.tab.c"
    break;

  case 51: /* arguments: expression  */
#line 488 "parser.y"
               {
        int tmp = get_func(func_expr_pipe);
        int type = func[tmp].arg[(yyvsp[0].reg)].type;
        int r2=next_tmp((yyvsp[0].reg)); 
        if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",(yyvsp[0].reg) ,func[tmp].arg[Arg_set].addr, Arg_set);
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",r2 ,func[tmp].arg[Arg_set].addr+1, Arg_set);
            Arg_set=2;
        }else{
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",(yyvsp[0].reg) ,func[tmp].arg[Arg_set].addr, Arg_set);
            Arg_set=1;
        }
    }
#line 2115 "parser.tab.c"
    break;

  case 52: /* arguments: STRING  */
#line 502 "parser.y"
    {
        int tmp = get_func(func_expr_pipe);
        char c_name[strlen((yyvsp[0].str))+16];
        sprintf(c_name, "const_string_%d", var_count);
        create_var_reg(c_name, SHORT_PTR_TYPE, strlen((yyvsp[0].str))+1);
        int varindex = get_var_index(c_name, func_expr_pipe);
        int ad = vars[varindex].addr;
        int r = new_tmp();
        int i=0;
        for(i=0; i<strlen((yyvsp[0].str)); i++) {
            fprintf(out, "LOAD R%d %d ; %s[%d] <- %c\n", r,(yyvsp[0].str)[i], vars[varindex].name, i, (yyvsp[0].str)[i]);
            fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i);
        }
        fprintf(out, "LOAD R%d 0 ; %s end\n", r, c_name);
        fprintf(out, "OUTI R%d 0x%04x\n", r, ad+i);
        fprintf(out, "LOAD R%d 0x%04x ; loading %s\n", r, ad, vars[varindex].name);
        fprintf(out, "OUTI R%d 0x%04x ; argument %d\n", r, func[tmp].arg[Arg_set].addr, Arg_set);
        Arg_set=1;
    }
#line 2139 "parser.tab.c"
    break;

  case 53: /* arguments: arguments COMMA expression  */
#line 522 "parser.y"
    {
        int tmp = get_func(func_expr_pipe);
        int type = func[tmp].arg[(yyvsp[0].reg)].type;
        int r2=next_tmp((yyvsp[0].reg));
        if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",(yyvsp[0].reg) ,func[tmp].arg[Arg_set].addr, Arg_set);
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",r2 ,func[tmp].arg[Arg_set].addr+1, Arg_set);
            Arg_set+=2;
        }else{
            fprintf(out, "OUTI R%d 0x%04x ; argument %d\n",(yyvsp[0].reg) ,func[tmp].arg[Arg_set].addr, Arg_set);
            Arg_set+=1;
        }
    }
#line 2157 "parser.tab.c"
    break;

  case 54: /* arguments: arguments COMMA STRING  */
#line 536 "parser.y"
    {
        int tmp = get_func(func_expr_pipe);
        char c_name[strlen((yyvsp[0].str))+16];
        sprintf(c_name, "const_string_%d", arg_count);
        create_var_reg(c_name, SHORT_PTR_TYPE, strlen((yyvsp[0].str))+1);
        int varindex = get_var_index(c_name, func_expr_pipe);
        int ad = vars[varindex].addr;
        int r = new_tmp();
        int i=0;
        for(i=0; i<strlen((yyvsp[0].str)); i++) {
            fprintf(out, "LOAD R%d %d ; %s[%d] <- %c\n", r,(yyvsp[0].str)[i], vars[varindex].name, i, (yyvsp[0].str)[i]);
            fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i);
        }
        fprintf(out, "LOAD R%d 0 ; %s end\n", r, c_name);
        fprintf(out, "OUTI R%d 0x%04x\n", r, ad+i);
        fprintf(out, "LOAD R%d 0x%04x ; loading %s\n", r, ad, vars[varindex].name);
        fprintf(out, "OUTI R%d 0x%04x ; argument %d\n", r, func[tmp].arg[Arg_set].addr, Arg_set);
        Arg_set+=1;
    }
#line 2181 "parser.tab.c"
    break;

  case 55: /* func_set: VOID funcname  */
#line 558 "parser.y"
                 {
        strcpy(func_pipe,(yyvsp[0].str));
        fprintf(out, "%s :\n", (yyvsp[0].str));
        create_func((yyvsp[0].str));
        (yyval.str) = (yyvsp[0].str);
    }
#line 2192 "parser.tab.c"
    break;

  case 56: /* func_set: SHORT funcname  */
#line 564 "parser.y"
                    {
        strcpy(func_pipe,(yyvsp[0].str));
        fprintf(out, "%s :\n", (yyvsp[0].str));
        create_func((yyvsp[0].str));
        (yyval.str) = (yyvsp[0].str);
    }
#line 2203 "parser.tab.c"
    break;

  case 57: /* func_set: LONG funcname  */
#line 570 "parser.y"
                   {
        strcpy(func_pipe,(yyvsp[0].str));
        fprintf(out, "%s :\n", (yyvsp[0].str));
        create_func((yyvsp[0].str));
        (yyval.str) = (yyvsp[0].str);
    }
#line 2214 "parser.tab.c"
    break;

  case 58: /* func_set: LONG MUL funcname  */
#line 576 "parser.y"
                       {
        strcpy(func_pipe,(yyvsp[0].str));
        fprintf(out, "%s :\n", (yyvsp[0].str));
        create_func((yyvsp[0].str));
        (yyval.str) = (yyvsp[0].str);
    }
#line 2225 "parser.tab.c"
    break;

  case 59: /* func_set: SHORT MUL funcname  */
#line 582 "parser.y"
                        {
        strcpy(func_pipe,(yyvsp[0].str));
        fprintf(out, "%s :\n", (yyvsp[0].str));
        create_func((yyvsp[0].str));
        (yyval.str) = (yyvsp[0].str);
    }
#line 2236 "parser.tab.c"
    break;

  case 60: /* funcdeclaration: func_set LPAREN RPAREN LBRACE program RBRACE  */
#line 591 "parser.y"
                                                {
    }
#line 2243 "parser.tab.c"
    break;

  case 61: /* funcdeclaration: func_set LPAREN arguments_declaration RPAREN LBRACE program RBRACE  */
#line 593 "parser.y"
                                                                        {
    }
#line 2250 "parser.tab.c"
    break;

  case 62: /* func_call: funcname LPAREN RPAREN  */
#line 598 "parser.y"
                          {
        if(get_func((yyvsp[-2].str))==-1)yyerror("Function called but not declared");
        int r = new_tmp();
        fprintf(out, "CALL ; appel de %s\n", (yyvsp[-2].str));
        fprintf(out, "SUBI SP SP 1\n");
        fprintf(out, "JMP %s\n", (yyvsp[-2].str));
        fprintf(out, "INI R%d 0x%x\n",r,ArgLoc-2);
        if(Arg_set != 0){
            yyerror("Function called with wrong number of arguments");
        }
        Arg_set = 0;
        free((yyvsp[-2].str));
        (yyval.reg) = r;
    }
#line 2269 "parser.tab.c"
    break;

  case 63: /* func_call: funcname LPAREN arguments RPAREN  */
#line 612 "parser.y"
                                      {
        int tmp = get_func((yyvsp[-3].str));
        if(tmp==-1)yyerror("Function called but not declared");
        int num_arg = func[tmp].num_arg;
        int r = new_tmp();
        int r2 = new_tmp();
        fprintf(out, "CALL ; appel de %s\n", (yyvsp[-3].str));
        fprintf(out, "SUBI SP SP 1\n");
        fprintf(out, "JMP %s\n", (yyvsp[-3].str));
        fprintf(out, "INI R%d 0x%x\n",r,ArgLoc-2);
        if(Arg_set != num_arg){
            printf("Func=%s Arg_set=%d num_arg=%d\n",(yyvsp[-3].str) ,Arg_set,num_arg);
            yyerror("Function called with wrong number of arguments");
        }
        Arg_set = 0;
        free((yyvsp[-3].str));
        (yyval.reg) = r;
    }
#line 2292 "parser.tab.c"
    break;

  case 71: /* statement: RETURN expression SEMICOLON  */
#line 640 "parser.y"
                                 {
        fprintf(out, "OUTI R%d 0x%04x\n",(yyvsp[-1].reg),ArgLoc-2);
        fprintf(out, "ADDI SP SP 1 ;return\nRET\n\n");
    }
#line 2301 "parser.tab.c"
    break;

  case 72: /* statement: RETURN SEMICOLON  */
#line 644 "parser.y"
                      {
        fprintf(out, "ADDI SP SP 1 ;return\nRET\n\n");
    }
#line 2309 "parser.tab.c"
    break;

  case 73: /* const_list: NUMBER  */
#line 650 "parser.y"
           {
        int len = snprintf(NULL, 0, "%d", (yyvsp[0].num));
        char *str = malloc(len + 1);
        sprintf(str, "%d", (yyvsp[0].num));
        (yyval.str) = str;
    }
#line 2320 "parser.tab.c"
    break;

  case 74: /* const_list: const_list COMMA NUMBER  */
#line 656 "parser.y"
                              {
        int len = snprintf(NULL, 0, "%d", (yyvsp[0].num));
        char *str = malloc(strlen((yyvsp[-2].str)) + 2 + len);
        sprintf(str, "%s,%d", (yyvsp[-2].str), (yyvsp[0].num));
        free((yyvsp[-2].str)); 
        (yyval.str) = str;
    }
#line 2332 "parser.tab.c"
    break;

  case 75: /* declaration: var_type_list ASSIGN LBRACE const_list RBRACE  */
#line 667 "parser.y"
    {
        int varindex = get_var_index((yyvsp[-4].str),func_pipe);
        int ad = vars[varindex].addr;
        int type = vars[varindex].type;
        int r = new_tmp();
        int r2 = new_tmp();
        int *num_list = malloc(sizeof(int)*VarSpace);
        int len_list;
        len_list = convert_str_intlist((yyvsp[-1].str), num_list);
        if(type==LONG_PTR_TYPE || type==LONG_TYPE || type==UNSIGNED_LONG_PTR_TYPE || type==UNSIGNED_LONG_TYPE){
            if(len_list>vars[varindex].reg){
                yyerror("Array size mismatch");
                printf("Array size=%d Reg size=%d\n",len_list, vars[varindex].reg);
            }
            for(int i=0; i<len_list*2; i+=2) {
                fprintf(out, "LOAD R%d %d ; %s[%d] <- %d\n", r,num_list[i>>1]&0xffff, vars[varindex].name, i, num_list[i>>1]);
                fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i);
                fprintf(out, "LOAD R%d %d", r,(num_list[i]>>16)&0xffff);
                fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i+1);
            }
        }else{
            if(len_list>vars[varindex].reg){
                printf("Array size=%d Reg size=%d\n",len_list, vars[varindex].reg);
                yyerror("Array size mismatch");
            }
            for(int i=0; i<len_list; i++) {
                fprintf(out, "LOAD R%d %d ; %s[%d] <- %d\n", r,num_list[i]&0xffff, vars[varindex].name, i, num_list[i]);
                fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i);
            }
        }
        free((yyvsp[-1].str));
        free(num_list);
    }
#line 2370 "parser.tab.c"
    break;

  case 76: /* declaration: var_type_list ASSIGN STRING  */
#line 701 "parser.y"
    {
        int varindex = get_var_index((yyvsp[-2].str),func_pipe);
        int ad = vars[varindex].addr;
        int r = new_tmp();
        if(strlen((yyvsp[0].str))>vars[varindex].reg)yyerror("Array size mismatch");
        int i=0;
        for(i=0; i<strlen((yyvsp[0].str)); i++) {
            fprintf(out, "LOAD R%d %d ; %s[%d] <- %d\n", r,(yyvsp[0].str)[i], vars[varindex].name, i, (yyvsp[0].str)[i]);
            fprintf(out, "OUTI R%d 0x%04x\n",r, ad+i);
        }
        int abs_max_adr = (i>(vars[varindex].reg-1))?(vars[varindex].reg-1+ad):(ad+i);
        fprintf(out, "LOAD R%d 0 ; %s[%d] <- 0\n", r, vars[varindex].name, abs_max_adr-ad);
        fprintf(out, "OUTI R%d 0x%04x\n", r, abs_max_adr);
    }
#line 2389 "parser.tab.c"
    break;

  case 77: /* declaration: var_type ASSIGN expression  */
#line 716 "parser.y"
    {
        int varindex = get_var_index((yyvsp[-2].str),func_pipe);
        int ad = vars[varindex].addr;
        fprintf(out, "OUTI R%d 0x%04x ; déclaration %s addr=0x%04x\n", (yyvsp[0].reg), ad, vars[varindex].name, ad);
    }
#line 2399 "parser.tab.c"
    break;

  case 78: /* declaration: var_type  */
#line 722 "parser.y"
    {
        int varindex = get_var_index((yyvsp[0].str),func_pipe);
        int ad = vars[varindex].addr;
        fprintf(out, ";  déclaration %s addr=0x%04x\n", vars[varindex].name, ad);
    }
#line 2409 "parser.tab.c"
    break;

  case 79: /* assignment: varname ASSIGN expression  */
#line 731 "parser.y"
    {
        int tmp = get_reg_addr((yyvsp[-2].str));
        if (tmp != -1) {
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", (yyvsp[0].reg), tmp, (yyvsp[-2].str), (yyvsp[0].reg));
        } else {
            int ad = get_var_addr((yyvsp[-2].str),func_pipe);
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", (yyvsp[0].reg), ad, (yyvsp[-2].str), (yyvsp[0].reg));
        }
        free((yyvsp[-2].str));
    }
#line 2424 "parser.tab.c"
    break;

  case 80: /* assignment: MUL varname ASSIGN expression  */
#line 742 "parser.y"
    {
        int tmp = get_reg_addr((yyvsp[-2].str));
        int r = new_tmp();
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r, tmp, (yyvsp[-2].str), (yyvsp[0].reg));
            fprintf(out, "OUT R%d R%d \n", (yyvsp[0].reg),r );
        } else {
            int ad = get_var_addr((yyvsp[-2].str),func_pipe);
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r, ad, (yyvsp[-2].str), (yyvsp[0].reg));
            fprintf(out, "OUT R%d R%d \n", (yyvsp[0].reg),r );
        }
        free((yyvsp[-2].str));
    }
#line 2442 "parser.tab.c"
    break;

  case 81: /* assignment: varname op ASSIGN expression  */
#line 756 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int tmp = get_reg_addr((yyvsp[-3].str));
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, tmp, (yyvsp[-3].str), r);
            fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r, r, (yyvsp[0].reg));
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", r, tmp, (yyvsp[-3].str), r); 
        }else{
            int ad = get_var_addr((yyvsp[-3].str),func_pipe);
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
            }
            fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r, r, (yyvsp[0].reg));

            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                int res_reg = next_tmp((yyvsp[0].reg));
                if(!strcmp((yyvsp[-2].str),"ADD") || !strcmp((yyvsp[-2].str),"SUB")){
                    fprintf(out, "%sC R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, res_reg);
                }
                if(!strcmp((yyvsp[-2].str),"AND") || !strcmp((yyvsp[-2].str),"OR") || !strcmp((yyvsp[-2].str),"XOR"))fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, res_reg);
                if(!strcmp((yyvsp[-2].str),"SHL")){
                    fprintf(out, "SHL R%d R%d R%d\n", r2, r2, res_reg);
                    fprintf(out, "SHR R%d R%d R%d\n", r3, r, res_reg);
                    fprintf(out, "OR R%d R%d R%d\n", r2, r2, r3);
                }
                if(!strcmp((yyvsp[-2].str),"SHR")){
                    fprintf(out, "SHL R%d R%d R%d\n", r3, r2, res_reg);
                    fprintf(out, "OR R%d R%d R%d\n", r, r, r3);
                    fprintf(out, "SHR R%d R%d R%d\n", r2, r2, res_reg);
                }
            }
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                fprintf(out, "OUTI R%d 0x%04x\n", r2, ad+1);
            }
        }
        free((yyvsp[-3].str));
    }
#line 2488 "parser.tab.c"
    break;

  case 82: /* assignment: MUL varname op ASSIGN expression  */
#line 798 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int tmp = get_reg_addr((yyvsp[-3].str));
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, tmp, (yyvsp[-3].str), r);
            fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r, r, (yyvsp[0].reg));
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r2, tmp, (yyvsp[-3].str), (yyvsp[0].reg));
            fprintf(out, "OUT R%d R%d \n", r, r2);

        }else{
            int ad = get_var_addr((yyvsp[-3].str),func_pipe);
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
            }
            fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r, r, (yyvsp[0].reg));

            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                int res_reg = next_tmp((yyvsp[0].reg));
                if(!strcmp((yyvsp[-2].str),"ADD") || !strcmp((yyvsp[-2].str),"SUB")){
                    fprintf(out, "%sC R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, res_reg);
                }
                if(!strcmp((yyvsp[-2].str),"AND") || !strcmp((yyvsp[-2].str),"OR") || !strcmp((yyvsp[-2].str),"XOR"))fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, res_reg);
                if(!strcmp((yyvsp[-2].str),"SHL")){
                    fprintf(out, "SHL R%d R%d R%d\n", r2, r2, res_reg);
                    fprintf(out, "SHR R%d R%d R%d\n", r3, r, res_reg);
                    fprintf(out, "OR R%d R%d R%d\n", r2, r2, r3);
                }
                if(!strcmp((yyvsp[-2].str),"SHR")){
                    fprintf(out, "SHL R%d R%d R%d\n", r3, r2, res_reg);
                    fprintf(out, "OR R%d R%d R%d\n", r, r, r3);
                    fprintf(out, "SHR R%d R%d R%d\n" , r2, r2, res_reg);
                }
            }
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r3, ad, (yyvsp[-3].str), r);
            fprintf(out, "OUT R%d R%d \n", r, r3);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r3, ad+1, (yyvsp[-3].str), r2);
                fprintf(out, "OUT R%d R%d \n", r2, r3);
            }
        }
        free((yyvsp[-3].str));
    }
#line 2538 "parser.tab.c"
    break;

  case 83: /* assignment: varname op ASSIGN NUMBER  */
#line 844 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int tmp = get_reg_addr((yyvsp[-3].str));
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, tmp, (yyvsp[-3].str), r);
            fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r, r, (unsigned short)(yyvsp[0].num));
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", r, tmp, (yyvsp[-3].str), r); 
        } else {
            int ad = get_var_addr((yyvsp[-3].str),func_pipe);
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
            fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r, r, (unsigned short)(yyvsp[0].num));
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                
                if(!strcmp((yyvsp[-2].str),"ADD") || !strcmp((yyvsp[-2].str),"SUB")){
                    fprintf(out, "LOAD R%d %d\n",r3, (unsigned short)((yyvsp[0].num)>>16));
                    fprintf(out, "%sC R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, r3);
                }
                if(!strcmp((yyvsp[-2].str),"AND") || !strcmp((yyvsp[-2].str),"OR") || !strcmp((yyvsp[-2].str),"XOR"))fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)>>16));
                if(!strcmp((yyvsp[-2].str),"SHL")){
                    fprintf(out, "SHLI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)));
                    fprintf(out, "SHRI R%d R%d %d\n",(yyvsp[-2].str) , r3, r, (unsigned short)(16-(yyvsp[0].num)));
                    fprintf(out, "OR R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, r3);
                }
                if(!strcmp((yyvsp[-2].str),"SHR")){
                    fprintf(out, "SHLI R%d R%d %d\n",(yyvsp[-2].str) , r3, r2, (unsigned short)(16-(yyvsp[0].num)));
                    fprintf(out, "OR R%d R%d R%d\n",(yyvsp[-2].str) , r, r, r3);
                    fprintf(out, "SHRI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)));
                }
            }
            fprintf(out, "OUTI R%d 0x%04x ; %s <- R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "OUTI R%d 0x%04x\n", r2, ad+1);
        }
        free((yyvsp[-3].str));
    }
#line 2580 "parser.tab.c"
    break;

  case 84: /* assignment: MUL varname op ASSIGN NUMBER  */
#line 882 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int tmp = get_reg_addr((yyvsp[-3].str));
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, tmp, (yyvsp[-3].str), r);
            fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r, r, (unsigned short)(yyvsp[0].num));
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r2, tmp, (yyvsp[-3].str), r);
            fprintf(out, "OUT R%d R%d \n", r, r2);
        } else {
            int ad = get_var_addr((yyvsp[-3].str),func_pipe);
            fprintf(out, "INI R%d 0x%04x ; %s -> R%d\n", r, ad, (yyvsp[-3].str), r);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
            fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r, r, (unsigned short)(yyvsp[0].num));
            
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                
                if(!strcmp((yyvsp[-2].str),"ADD") || !strcmp((yyvsp[-2].str),"SUB")){
                    fprintf(out, "LOAD R%d %d\n",r3, (unsigned short)((yyvsp[0].num)>>16));
                    fprintf(out, "%sC R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, r3);
                }
                if(!strcmp((yyvsp[-2].str),"AND") || !strcmp((yyvsp[-2].str),"OR") || !strcmp((yyvsp[-2].str),"XOR"))fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)>>16));
                if(!strcmp((yyvsp[-2].str),"SHL")){
                    fprintf(out, "SHLI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)));
                    fprintf(out, "SHRI R%d R%d %d\n",(yyvsp[-2].str) , r3, r, (unsigned short)(16-(yyvsp[0].num)));
                    fprintf(out, "OR R%d R%d R%d\n",(yyvsp[-2].str) , r2, r2, r3);
                }
                if(!strcmp((yyvsp[-3].str),"SHR")){
                    fprintf(out, "SHLI R%d R%d %d\n",(yyvsp[-2].str) , r3, r2, (unsigned short)(16-(yyvsp[0].num)));
                    fprintf(out, "OR R%d R%d R%d\n",(yyvsp[-2].str) , r, r, r3);
                    fprintf(out, "SHRI R%d R%d %d\n",(yyvsp[-2].str) , r2, r2, (unsigned short)((yyvsp[0].num)));
                }
            }
            fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r3, ad, (yyvsp[-3].str), r);
            fprintf(out, "OUT R%d R%d \n", r, r3);
            if(get_var_type((yyvsp[-3].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-3].str),func_pipe)==UNSIGNED_LONG_TYPE){
                fprintf(out, "INI R%d 0x%04x ; *%s <- R%d\n", r3, ad+1, (yyvsp[-3].str), r);
                fprintf(out, "OUT R%d R%d \n", r2, r3);
            }
        }
        free((yyvsp[-3].str));
    }
#line 2628 "parser.tab.c"
    break;

  case 85: /* assignment: varname PLUS PLUS  */
#line 926 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int ad = get_var_addr((yyvsp[-2].str),func_pipe);
        fprintf(out, "INI R%d 0x%04x ; lecture %s -> R%d\n", r, ad, (yyvsp[-2].str), r);
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
        fprintf(out, "ADDI R%d R%d 1\n", r, r);
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE){
            fprintf(out, "LOAD R%d 0\n", r3);
            fprintf(out, "ADDC R%d R%d R%d\n", r2, r2, r3);
        }
        fprintf(out, "OUTI R%d 0x%04x ; %s <- %s+1\n", r, ad, (yyvsp[-2].str), (yyvsp[-2].str));
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "OUTI R%d 0x%04x\n", r2, ad+1);
        free((yyvsp[-2].str));
    }
#line 2649 "parser.tab.c"
    break;

  case 86: /* assignment: varname MINUS MINUS  */
#line 943 "parser.y"
    {
        int r = new_tmp();
        int r2 = new_tmp();
        int r3 = new_tmp();
        int ad = get_var_addr((yyvsp[-2].str),func_pipe);
        fprintf(out, "INI R%d 0x%04x ; lecture %s -> R%d\n", r, ad, (yyvsp[-2].str), r);
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "INI R%d 0x%04x\n", r2, ad+1);
        fprintf(out, "SUBI R%d R%d 1\n", r, r);
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE){
            fprintf(out, "LOAD R%d 0\n", r3);
            fprintf(out, "SUBC R%d R%d R%d\n", r2, r2, r3);
        }
        fprintf(out, "OUTI R%d 0x%04x ; %s <- %s-1\n", r, ad, (yyvsp[-2].str), (yyvsp[-2].str));
        if(get_var_type((yyvsp[-2].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_PTR_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==LONG_TYPE || get_var_type((yyvsp[-2].str),func_pipe)==UNSIGNED_LONG_TYPE)fprintf(out, "OUTI R%d 0x%04x\n", r2, ad+1);
        free((yyvsp[-2].str));
    }
#line 2670 "parser.tab.c"
    break;

  case 87: /* assignment: varname LBRACKET NUMBER RBRACKET ASSIGN expression  */
#line 960 "parser.y"
    {
        char* var_name = malloc(strlen((yyvsp[-5].str))+50);
        int tmp = get_reg_addr((yyvsp[-5].str));
        if (tmp != -1) {
            sprintf(var_name," Register %s already exists with this name",(yyvsp[-5].str));
            yyerror(var_name);
        }else {
            int ad = get_var_addr((yyvsp[-5].str),func_pipe);
            if(ad>=ArgLoc && ad<=ArgLocMax){
                int r = new_tmp();
                fprintf(out, "INI R%d 0x%04x ; %s[%d] <- R%d\n", r, ad, (yyvsp[-5].str), (yyvsp[-3].num), (yyvsp[0].reg));
                fprintf(out, "ADDI R%d R%d %d\n", r, r, (yyvsp[-3].num));
                fprintf(out, "OUT R%d R%d\n", (yyvsp[0].reg), r);
            }else{
                fprintf(out, "OUTI R%d 0x%04x ; %s[%d] <- R%d\n",(yyvsp[0].reg), ad+(yyvsp[-3].num), (yyvsp[-5].str), (yyvsp[-3].num), (yyvsp[0].reg));
            }
        }
        free((yyvsp[-5].str));
    }
#line 2694 "parser.tab.c"
    break;

  case 88: /* assignment: varname LBRACKET expression RBRACKET ASSIGN expression  */
#line 980 "parser.y"
    {
        char *var_name;
        int tmp = get_reg_addr((yyvsp[-5].str));
        if (tmp != -1) {
            sprintf(var_name," Register %s already exists with this name",(yyvsp[-5].str));
            yyerror(var_name);
        } else {
            int ad = get_var_addr((yyvsp[-5].str),func_pipe);
            int r = new_tmp();
            if(!(get_var_type((yyvsp[-5].str),func_pipe)==LONG_PTR_TYPE || get_var_type((yyvsp[-5].str),func_pipe)==SHORT_PTR_TYPE))yyerror("variable not of type ptr/array");
            if(ad>=ArgLoc && ad<=ArgLocMax){
                fprintf(out, "INI R%d 0x%04x ; %s[R%d] <- R%d\n", r, ad, (yyvsp[-5].str), (yyvsp[-3].reg), (yyvsp[0].reg));
                fprintf(out, "ADD R%d R%d R%d\n", r, r, (yyvsp[-3].reg));
                fprintf(out, "OUT R%d R%d\n", (yyvsp[0].reg), r);
            }else{
                fprintf(out, "ADDI R%d R%d 0x%04x\n",r, (yyvsp[-3].reg), ad);
                fprintf(out, "OUT R%d R%d ; %s[R%d] <- R%d\n",(yyvsp[0].reg), r, (yyvsp[-5].str), (yyvsp[-3].reg), (yyvsp[0].reg));
            }
        }
        free((yyvsp[-5].str));
    }
#line 2720 "parser.tab.c"
    break;

  case 89: /* expression: comparable_expression  */
#line 1003 "parser.y"
                          { (yyval.reg) = (yyvsp[0].reg); }
#line 2726 "parser.tab.c"
    break;

  case 90: /* expression: simple_expression  */
#line 1004 "parser.y"
                        { (yyval.reg) = (yyvsp[0].reg); }
#line 2732 "parser.tab.c"
    break;

  case 91: /* comparable_expression: expression op NUMBER  */
#line 1008 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-1].str) , r, (yyvsp[-2].reg), (yyvsp[0].num));
        (yyval.reg) = r;
    }
#line 2742 "parser.tab.c"
    break;

  case 92: /* comparable_expression: NUMBER op_symetrical expression  */
#line 1014 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "%sI R%d R%d %d\n",(yyvsp[-1].str) , r, (yyvsp[0].reg), (yyvsp[-2].num));
        (yyval.reg) = r;
    }
#line 2752 "parser.tab.c"
    break;

  case 93: /* comparable_expression: expression op expression  */
#line 1020 "parser.y"
    {
        int r = new_tmp();
        int r2 = -48;
        fprintf(out, "%s R%d R%d R%d\n",(yyvsp[-1].str) , r, (yyvsp[-2].reg), (yyvsp[0].reg));
        (yyval.reg) = r;
    }
#line 2763 "parser.tab.c"
    break;

  case 94: /* comparable_expression: BNOT LPAREN expression BAND NUMBER RPAREN  */
#line 1027 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "NANDI R%d R%d %d\n", r, (yyvsp[-3].reg), (yyvsp[-1].num)&0xffff);
        (yyval.reg) = r;
    }
#line 2773 "parser.tab.c"
    break;

  case 95: /* comparable_expression: BNOT LPAREN NUMBER BAND expression RPAREN  */
#line 1033 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "NANDI R%d R%d %d\n", r, (yyvsp[-1].reg), (yyvsp[-3].num)&0xffff);
        (yyval.reg) = r;
    }
#line 2783 "parser.tab.c"
    break;

  case 96: /* comparable_expression: BNOT LPAREN expression BAND expression RPAREN  */
#line 1039 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "NAND R%d R%d R%d\n", r, (yyvsp[-1].reg), (yyvsp[-3].reg));
        (yyval.reg) = r;
    }
#line 2793 "parser.tab.c"
    break;

  case 97: /* comparable_expression: BNOT expression  */
#line 1045 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "NAND R%d R%d R%d\n", r, (yyvsp[0].reg), (yyvsp[0].reg));
        (yyval.reg) = r;
    }
#line 2803 "parser.tab.c"
    break;

  case 98: /* comparable_expression: MINUS expression  */
#line 1051 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "LOAD R%d 0\n", r);
        fprintf(out, "SUB R%d R%d R%d\n", r, r, (yyvsp[0].reg));
        (yyval.reg) = r;
    }
#line 2814 "parser.tab.c"
    break;

  case 100: /* simple_expression: varname LBRACKET NUMBER RBRACKET  */
#line 1062 "parser.y"
    {
        int r = new_tmp();
        int ad = get_var_addr((yyvsp[-3].str),func_pipe);
        int type = get_var_type((yyvsp[-3].str),func_pipe);
        if(!(type==LONG_PTR_TYPE || type==SHORT_PTR_TYPE))yyerror("variable not of type ptr/array");    //Attention erreur
        if(type==LONG_PTR_TYPE){
            if(ad>=ArgLoc && ad<=ArgLocMax){
                fprintf(out, "INI R%d 0x%04x\n", r, ad);
                fprintf(out, "ADDI R%d R%d %d\n", r, r, (yyvsp[-1].num)*2);
                fprintf(out, "IN R%d R%d ; lecture %s[%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].num), r);
            }else{
                fprintf(out, "INI R%d 0x%04x ; lecture %s[%d] -> R%d\n", r, ad+((yyvsp[-1].num)*2), (yyvsp[-3].str), (yyvsp[-1].num), r);
                fprintf(out, "INI R%d 0x%04x", r, ad+((yyvsp[-1].num)*2)+1);
            }
        }else{
            if(ad>=ArgLoc && ad<=ArgLocMax){
                fprintf(out, "INI R%d 0x%04x\n", r, ad);
                fprintf(out, "ADDI R%d R%d %d\n", r, r, (yyvsp[-1].num));
                fprintf(out, "IN R%d R%d ; lecture %s[%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].num), r);
            }else{
                fprintf(out, "INI R%d 0x%04x ; lecture %s[%d] -> R%d\n", r, ad+(yyvsp[-1].num), (yyvsp[-3].str), (yyvsp[-1].num), r);
            }
        }
        (yyval.reg) = r;
        free((yyvsp[-3].str));
    }
#line 2845 "parser.tab.c"
    break;

  case 101: /* simple_expression: varname LBRACKET expression RBRACKET  */
#line 1089 "parser.y"
    {
        int r = new_tmp();
        int ad = get_var_addr((yyvsp[-3].str),func_pipe);
        int type = get_var_type((yyvsp[-3].str),func_pipe);
        if(!(type==LONG_PTR_TYPE || type==SHORT_PTR_TYPE))yyerror("variable not of type ptr/array");
        if(type==LONG_PTR_TYPE){
            if(ad>=ArgLoc && ad<=ArgLocMax){
                fprintf(out, "INI R%d 0x%04x\n", r, ad);
                fprintf(out, "ADD R%d R%d R%d\n", r, r, (yyvsp[-1].reg));
                fprintf(out, "IN R%d R%d ; lecture %s[R%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].reg), r);
            }else{
                fprintf(out, "ADDI R%d R%d 0x%04x\n", r, (yyvsp[-1].reg), ad);
                fprintf(out, "IN R%d R%d ; lecture %s[R%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].reg), r);
            }
        }else{
           if(ad>=ArgLoc && ad<=ArgLocMax){
                fprintf(out, "INI R%d 0x%04x\n", r, ad);
                fprintf(out, "ADD R%d R%d R%d\n", r, r, (yyvsp[-1].reg));
                fprintf(out, "IN R%d R%d ; lecture %s[R%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].reg), r);
            }else{
                fprintf(out, "ADDI R%d R%d 0x%04x\n", r, (yyvsp[-1].reg), ad);
                fprintf(out, "IN R%d R%d ; lecture %s[R%d] -> R%d\n", r, r, (yyvsp[-3].str), (yyvsp[-1].reg), r);
            }
        }
        (yyval.reg) = r;
        free((yyvsp[-3].str));
    }
#line 2877 "parser.tab.c"
    break;

  case 102: /* simple_expression: varname  */
#line 1117 "parser.y"
    {
        int tmp = get_reg_addr((yyvsp[0].str));
        int r = new_tmp();
        if (tmp != -1) {
            fprintf(out, "INI R%d 0x%04x ; lecture %s -> R%d\n", r, tmp, (yyvsp[0].str), r);
            (yyval.reg) = r;
        } else {
            int ad = get_var_addr((yyvsp[0].str),func_pipe);
            int vartype = get_var_type((yyvsp[0].str),func_pipe);
            if(vartype == UNSIGNED_LONG_PTR_TYPE || vartype == LONG_PTR_TYPE){
                fprintf(out, "INI R%d 0x%04x ; lecture &%s -> R%d\n", r, ad, (yyvsp[0].str), r);
            }else if(vartype == UNSIGNED_LONG_TYPE || vartype == LONG_TYPE){
                fprintf(out, "INI R%d 0x%04x ; lecture %s -> R%d\n", r, ad, (yyvsp[0].str), r);
            }else if(vartype == UNSIGNED_SHORT_PTR_TYPE || vartype == SHORT_PTR_TYPE){
                fprintf(out, "INI R%d 0x%04x ; lecture &%s -> R%d\n", r, ad, (yyvsp[0].str), r);
            }else{
                fprintf(out, "INI R%d 0x%04x ; lecture %s -> R%d\n", r, ad, (yyvsp[0].str), r);
            }
            (yyval.reg) = r;
        }
        free((yyvsp[0].str));
    }
#line 2904 "parser.tab.c"
    break;

  case 103: /* simple_expression: BAND varname  */
#line 1140 "parser.y"
    {
        int r = new_tmp();
        int ad = get_var_addr((yyvsp[0].str),func_pipe);
        fprintf(out, "LOAD R%d 0x%04x ; lecture &%s -> R%d\n", r, ad, (yyvsp[0].str), r);
        (yyval.reg) = r;
        free((yyvsp[0].str));
    }
#line 2916 "parser.tab.c"
    break;

  case 104: /* simple_expression: MUL varname  */
#line 1148 "parser.y"
    {
        int r = new_tmp();
        int r1 = new_tmp();
        int ad = get_var_addr((yyvsp[0].str),func_pipe);
        fprintf(out, "INI R%d 0x%04x ; lecture *%s -> R%d\n", r, ad, (yyvsp[0].str), r1);
        fprintf(out, "IN R%d R%d \n",r1, r);
        (yyval.reg) = r1;
        free((yyvsp[0].str));
    }
#line 2930 "parser.tab.c"
    break;

  case 105: /* simple_expression: MINUS NUMBER  */
#line 1158 "parser.y"
    {
        unsigned short tmp = -(yyvsp[0].num);
        int r = new_tmp();
        fprintf(out, "LOAD R%d %d\n", r, tmp);
        (yyval.reg) = r;
    }
#line 2941 "parser.tab.c"
    break;

  case 106: /* simple_expression: LPAREN expression RPAREN  */
#line 1165 "parser.y"
    {
        (yyval.reg) = (yyvsp[-1].reg);
    }
#line 2949 "parser.tab.c"
    break;

  case 107: /* simple_expression: NUMBER  */
#line 1169 "parser.y"
    {
        int r = new_tmp();
        fprintf(out, "LOAD R%d %d\n", r, (yyvsp[0].num)&0xffff);
        (yyval.reg) = r;
    }
#line 2959 "parser.tab.c"
    break;

  case 108: /* condition: expression EQ expression  */
#line 1178 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe =  read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition ==\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));
        fprintf(out,"JM0 if_%04d\n", TMP_pipe);      // Si égal (0), aller à if
        fprintf(out,"JMP else_if_%04d\n", TMP_pipe);   // Sinon, aller à end_if
        fprintf(out,"if_%04d :\n", TMP_pipe);
        (yyval.num) = TMP_pipe;
    }
#line 2973 "parser.tab.c"
    break;

  case 109: /* condition: expression NE expression  */
#line 1188 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition !=\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));
        fprintf(out,"JM0 else_if_%04d\n", TMP_pipe);   // Si égal (0), aller à end_if
        fprintf(out,"if_%04d :\n", TMP_pipe);       // Sinon, aller à if
        (yyval.num) = TMP_pipe;
    }
#line 2986 "parser.tab.c"
    break;

  case 110: /* condition: expression LE expression  */
#line 1197 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition <=\n", r, (yyvsp[0].reg), (yyvsp[-2].reg));
        fprintf(out,"JMN else_if_%04d\n", TMP_pipe);       // Si négatif, aller à if
        fprintf(out,"if_%04d :\n", TMP_pipe);   // Si positif, aller à end_if
        (yyval.num) = TMP_pipe;
    }
#line 2999 "parser.tab.c"
    break;

  case 111: /* condition: expression GE expression  */
#line 1206 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition >=\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));  // CORRIGÉ: $1 - $3
        fprintf(out,"JMN else_if_%04d\n", TMP_pipe);   // Si négatif, aller à end_if
        fprintf(out,"if_%04d :\n", TMP_pipe);       // Si positif, aller à if
        (yyval.num) = TMP_pipe;
    }
#line 3012 "parser.tab.c"
    break;

  case 112: /* condition: expression LT expression  */
#line 1215 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition <\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));
        fprintf(out,"JMN if_%04d\n", TMP_pipe);       // Si négatif, aller à if
        fprintf(out,"JMP else_if_%04d\n", TMP_pipe);   // Sinon (>=0), aller à end_if
        fprintf(out,"if_%04d :\n", TMP_pipe);
        (yyval.num) = TMP_pipe;
    }
#line 3026 "parser.tab.c"
    break;

  case 113: /* condition: expression GT expression  */
#line 1225 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUB R%d R%d R%d ; condition >\n", r, (yyvsp[0].reg), (yyvsp[-2].reg));   // CORRIGÉ: $1 - $3
        fprintf(out,"JMN if_%04d\n", TMP_pipe);   // Si négatif, aller à end_if
        fprintf(out,"JMP else_if_%04d\n", TMP_pipe);       // Si positif, aller à if
        fprintf(out,"if_%04d :\n", TMP_pipe);
        (yyval.num) = TMP_pipe;
    }
#line 3040 "parser.tab.c"
    break;

  case 114: /* condition: comparable_expression  */
#line 1235 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"JM0 else_if_%04d ; condition != 0\n", TMP_pipe);      // Si égal (0), aller à if
        fprintf(out,"if_%04d :\n", TMP_pipe);           // Sinon, aller à end_if
        (yyval.num) = TMP_pipe;
    }
#line 3052 "parser.tab.c"
    break;

  case 115: /* condition: simple_expression  */
#line 1243 "parser.y"
    {
        int r = new_tmp();
        TMP_pipe = read_label();
        fprintf(out,"SUBI R%d R%d 0 ; condition != 0\n", r, (yyvsp[0].reg));
        fprintf(out,"JM0 else_if_%04d\n", TMP_pipe);      // Si égal (0), aller à if
        fprintf(out,"if_%04d :\n", TMP_pipe);           // Sinon, aller à end_if
        (yyval.num) = TMP_pipe;
    }
#line 3065 "parser.tab.c"
    break;

  case 116: /* Else: ELSE  */
#line 1255 "parser.y"
    {
        fprintf(out,"JMP end_if_%04d\n", read_label());
        fprintf(out,"else_if_%04d :\n", read_label());
    }
#line 3074 "parser.tab.c"
    break;

  case 117: /* If: IF  */
#line 1263 "parser.y"
    {
        push_label();
    }
#line 3082 "parser.tab.c"
    break;

  case 118: /* if_statement: If LPAREN condition RPAREN statement Else statement  */
#line 1270 "parser.y"
    {
        fprintf(out,"end_if_%04d :\n", pop_label());
    }
#line 3090 "parser.tab.c"
    break;

  case 119: /* if_statement: If LPAREN condition RPAREN statement  */
#line 1274 "parser.y"
    {
        fprintf(out,"else_if_%04d :\n", pop_label());
    }
#line 3098 "parser.tab.c"
    break;

  case 120: /* While: WHILE  */
#line 1281 "parser.y"
    {
        int tmp = push_label();
        fprintf(out,"while_%04d :\n", tmp);
        (yyval.num) = tmp;
    }
#line 3108 "parser.tab.c"
    break;

  case 121: /* while_statement: While LPAREN condition RPAREN statement  */
#line 1290 "parser.y"
    {
        int tmp = pop_label();
        fprintf(out,"JMP while_%04d\n", tmp);
        fprintf(out,"else_if_%04d :\n", tmp);
    }
#line 3118 "parser.tab.c"
    break;

  case 122: /* Semicolon: SEMICOLON  */
#line 1299 "parser.y"
    {
        int tmp = push_label();
        fprintf(out,"for_%04d :\n", tmp);
        (yyval.num) = tmp;
    }
#line 3128 "parser.tab.c"
    break;

  case 123: /* for_statement: FOR LPAREN declaration Semicolon condition SEMICOLON assignment RPAREN statement  */
#line 1308 "parser.y"
    {
        int tmp = pop_label();
        fprintf(out,"JMP for_%04d\n", tmp);
        fprintf(out,"else_if_%04d :\n", tmp);
    }
#line 3138 "parser.tab.c"
    break;

  case 124: /* varname: IDENT  */
#line 1316 "parser.y"
                   { (yyval.str) = strdup((yyvsp[0].str)); }
#line 3144 "parser.tab.c"
    break;

  case 125: /* varname: GPI0  */
#line 1317 "parser.y"
                   { (yyval.str) = strdup("GPI0"); }
#line 3150 "parser.tab.c"
    break;

  case 126: /* varname: GPI1  */
#line 1318 "parser.y"
                   { (yyval.str) = strdup("GPI1"); }
#line 3156 "parser.tab.c"
    break;

  case 127: /* varname: GPO0  */
#line 1319 "parser.y"
                   { (yyval.str) = strdup("GPO0"); }
#line 3162 "parser.tab.c"
    break;

  case 128: /* varname: GPO1  */
#line 1320 "parser.y"
                   { (yyval.str) = strdup("GPO1"); }
#line 3168 "parser.tab.c"
    break;

  case 129: /* varname: SPI  */
#line 1321 "parser.y"
                   { (yyval.str) = strdup("SPI"); }
#line 3174 "parser.tab.c"
    break;

  case 130: /* varname: CONFSPI  */
#line 1322 "parser.y"
                   { (yyval.str) = strdup("CONFSPI"); }
#line 3180 "parser.tab.c"
    break;

  case 131: /* varname: UART  */
#line 1323 "parser.y"
                   { (yyval.str) = strdup("UART"); }
#line 3186 "parser.tab.c"
    break;

  case 132: /* varname: BAUDL  */
#line 1324 "parser.y"
                   { (yyval.str) = strdup("BAUDL"); }
#line 3192 "parser.tab.c"
    break;

  case 133: /* varname: BAUDH  */
#line 1325 "parser.y"
                   { (yyval.str) = strdup("BAUDH"); }
#line 3198 "parser.tab.c"
    break;

  case 134: /* varname: STATUS  */
#line 1326 "parser.y"
                   { (yyval.str) = strdup("STATUS"); }
#line 3204 "parser.tab.c"
    break;

  case 135: /* varname: CONFINT  */
#line 1327 "parser.y"
                   { (yyval.str) = strdup("CONFINT"); }
#line 3210 "parser.tab.c"
    break;

  case 136: /* funcname: IDENT  */
#line 1332 "parser.y"
          {
        strcpy(func_expr_pipe,(yyvsp[0].str));
        (yyval.str) = strdup((yyvsp[0].str)); 
    }
#line 3219 "parser.tab.c"
    break;


#line 3223 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1338 "parser.y"


int main(int argc, char *argv[]) {
    char *outfile = "main.asm"; // valeur par défaut
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Erreur ouverture input");
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outfile = argv[i + 1];
            i++;
        }
    }
    out = fopen(outfile, "w");
    if (!out) { perror("../main.asm"); exit(1); }
    fprintf(out, ";   -- Code generated by CPU5.9 custom Compiler --\n");
    fprintf(out, "LOAD SP 0x%4x\n", SP0);
    fprintf(out, "JMP main\n");
    yyparse();
    printf("\n\"%s\" successfully compiled to \"%s\"\n",argv[1],argv[3]);
    printf("\nRam utilisation : %d/%d (%.2f%%) Half Words\n",var_count,VarSpace,((float)var_count*100/VarSpace));
    fclose(out);
    fclose(yyin);
    return 0;
}

void yyerror(const char* const message) {
    fprintf(stderr, "Parse error:%s\n", message);
    fprintf(stderr, "Line %d\n", LineCount);
    exit(1);
}

int yywrap(void) {
    return 1;
}
