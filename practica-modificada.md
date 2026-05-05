# Pràctica CL - ASL - Codis originals


Els fitxers de codi estàn organitzats de la següent manera:

```
asl/
    Asl.g4
    check-examples.sh
    checkLLVM.sh
    CodeGenVisitor.cpp
    CodeGenVisitor.h
    main.cpp
    Makefile
    SymbolsVisitor.cpp
    SymbolsVisitor.h
    TypeCheckVisitor.cpp
    TypeCheckVisitor.h

common/
    code.cpp
    code.h
    debug.h
    LLVMCodeGen.cpp
    LLVMCodeGen.h
    SemErrors.cpp
    SemErrors.h
    SymTable.cpp
    SymTable.h
    TreeDecoration.cpp
    TreeDecoration.h
    TypesMgr.cpp
    TypesMgr.h
```


### asl

#### asl/Asl.g4

```antlr
//////////////////////////////////////////////////////////////////////
//
//    Asl - Another simple language (grammar)
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program : function+ EOF
        ;

// A function has a name, a list of parameters and a list of statements
function
        : FUNC ID '(' params? ')' (':' type)? declarations statements ENDFUNC
        ;

declarations
        : (variable_decl)*
        ;

variable_decl
        : VAR ID (',' ID)* ':' type
        ;

basicType
        : INT
        | FLOAT
        | BOOL
        | CHAR
        ;

type    : basicType                             # basicTypeLabel
        | ARRAY '[' INTVAL ']' OF basicType     # arrayType
        ;
        
statements
        : (statement)*
        ;

// The different types of instructions
statement
          // Assignment
        : left_expr ASSIGN expr ';'                                     # assignStmt
        | IF expr THEN statements (ELSE statements)? ENDIF              # ifStmt
        | WHILE expr DO statements ENDWHILE                             # whileStmt
        | functionCall ';'                                              # functionCallStmt
        | READ left_expr ';'                                            # readStmt
        | WRITE expr ';'                                                # writeExpr
        | WRITE STRING ';'                                              # writeString
        | RETURN expr? ';'                                              # return
        ;

// Grammar for left expressions (l-values in C++)
left_expr 
        : array                                          # arrayLeftExpr                              
        | ident                                          # identLeftExpr  
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    : '(' expr ')'                                   # parenthesis
        | functionCall                                   # functionCallExpr
        | array                                          # arrayAccess
        | op=MINUS expr                                  # unary
        | op=NOT expr                                    # not
        | expr op=(MUL|DIV|MOD) expr                     # arithmetic
        | expr op=(PLUS|MINUS) expr                      # arithmetic
        | expr op=(EQ|NE|LT|LE|GT|GE) expr               # relational
        | expr op=AND expr                               # logic
        | expr op=OR expr                                # logic
        | INTVAL                                         # intVal
        | FLOATVAL                                       # floatVal
        | BOOLVAL                                        # boolVal
        | CHARVAL                                        # charVal
        | ident                                          # exprIdent
        ;

// Array
array   : ident '[' expr ']'
        ;

// Identifiers
ident   : ID
        ;

// Parameters
params  : ID ':' type (',' ID ':' type)*             
        ;

functionCall 
        : ident '(' (expr (',' expr)*)? ')'
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

NOT       : 'not' ;
AND       : 'and' ;
OR        : 'or' ;       
ASSIGN    : '=' ;
EQ        : '==' ;
NE        : '!=' ;
LT        : '<' ;
LE        : '<=' ;
GT        : '>' ;
GE        : '>=' ;
PLUS      : '+' ;
MINUS     : '-';
MUL       : '*';
DIV       : '/';
MOD       : '%';
VAR       : 'var';
INT       : 'int';
FLOAT     : 'float';
BOOL      : 'bool';
CHAR      : 'char';
IF        : 'if' ;
THEN      : 'then' ;
ELSE      : 'else' ;
ENDIF     : 'endif' ;
WHILE     : 'while' ;
DO        : 'do' ;
ENDWHILE  : 'endwhile' ;
FUNC      : 'func' ;
ENDFUNC   : 'endfunc' ;
READ      : 'read' ;
WRITE     : 'write' ;
RETURN    : 'return' ;
ARRAY     : 'array' ;
OF        : 'of' ;
BOOLVAL   : ('true'|'false') ;
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : ('0'..'9')+ '.' ('0'..'9')+ ;
CHARVAL   : '\'' ( ESC_SEQ | SAFE_CHAR ) '\'';
ID        : ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;

fragment 
SAFE_CHAR  : ~['\\\r\n] ;

// Strings (in quotes) with escape sequences
STRING    : '"' ( ESC_SEQ | ~('\\'|'"') )* '"' ;

fragment
ESC_SEQ   : '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\') ;

// Comments (inline C++-style and multiline C-style)
COMMENT   : ( '//' ~('\n'|'\r')* '\r'? '\n'
            | '/*' .*? '*/'
            ) -> skip
          ;

// White spaces
WS        : (' '|'\t'|'\r'|'\n')+ -> skip ;
// Alternative description
// WS        : [ \t\r\n]+ -> skip ;
```


#### asl/check-examples.sh

```bash
#!/bin/bash

export LD_LIBRARY_PATH=/assig/$USER/cl/runtime/lib:$HOME/assig/cl/runtime/lib:/usr/local/lib

#--------------------------------------------
function check_chkt_example() {
    expected=$1
    produced=$2
    
    diff $expected $produced >tmp.diff
    if (test $? == 0); then
	echo "OK"
    else
	echo "Wrong output"
	cat tmp.diff
	echo ""
    fi
    rm -f tmp.diff
}

#--------------------------------------------
function check_genc_example() {	
    expected=$1
    produced=$2
    
    diff $expected $produced >tmp.diff
    if (test $? == 0); then
   	echo "OK"
    else
	echo "Wrong output"
	cat tmp.diff
 	echo ""
    fi
    rm -f tmp.diff
}

########### check 'jpbasic_chkt' examples
echo "======================================================="
echo "=== BEGIN examples/jpbasic_chkt typecheck ============="
for f in ../examples/jpbasic_chkt_*.asl; do
    echo -n "****" $(basename "$f") "...." 
    ./asl "$f" 2>&1 | grep -E '^Line [0-9]+:[0-9]+ error:' >tmp.err
    check_chkt_example "${f/asl/err}" tmp.err 
    rm -f tmp.err
done
echo "=== END examples/jpbasic_chkt typecheck ==============="
echo "======================================================="

########### check all 'jp_chkt' examples
echo ""
echo "======================================================="
echo "=== BEGIN examples/jp_chkt_* typecheck ================"
for f in ../examples/jp_chkt_*.asl; do
    echo -n "****" $(basename "$f") "...." 
    ./asl "$f" 2>&1 | grep -E '^Line [0-9]+:[0-9]+ error:' >tmp.err
    check_chkt_example "${f/asl/err}" tmp.err 
    rm -f tmp.err
done
echo "=== END examples/jp_chkt_* typecheck =================="
echo "======================================================="

########### check all 'jpbasic_genc' examples
echo ""
echo "======================================================="
echo "=== BEGIN examples/jpbasic_genc_* codegen ============="
for f in ../examples/jpbasic_genc_*.asl; do
    echo -n "****" $(basename "$f") "...." 
    ./asl "$f" >tmp.t 2>&1 
    if (test $? != 0); then
       echo "Compilation errors"
    else
       ../tvm/tvm tmp.t < "${f/asl/in}" >tmp.out
       check_genc_example "${f/asl/out}" tmp.out
    fi
    rm -f tmp.t tmp.out tmp.diff
done
echo "=== END examples/jpbasic_genc_* codegen ==============="
echo "======================================================="

########### check all 'jp_genc' examples
echo ""
echo "======================================================="
echo "=== BEGIN examples/jp_genc_* codegen =================="
for f in ../examples/jp_genc_*.asl; do
    echo -n "****" $(basename "$f") "...." 
    ./asl "$f" >tmp.t 2>&1 
    if (test $? != 0); then
       echo "Compilation errors"
    else
       ../tvm/tvm tmp.t < "${f/asl/in}" >tmp.out
       check_genc_example "${f/asl/out}" tmp.out
    fi
    rm -f tmp.t tmp.out tmp.diff
done
echo "=== END examples/jp_genc_* codegen ===================="
echo "======================================================="
```


#### asl/checkLLVM.sh

```bash
#!/bin/bash

ASLFILE=$(basename -- ${1})
LLFILE=${ASLFILE/.asl/.ll}
rm -f ${LLFILE} a.out
./asl ${1} && clang -Wno-override-module ${LLFILE} && ./a.out < ${1/asl/in} | diff -y -  ${1/asl/out}
```


#### asl/CodeGenVisitor.cpp

```cpp
//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>
#include <cstddef> // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;

// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr &Types,
                               SymTable &Symbols,
                               TreeDecoration &Decorations) : Types{Types},
                                                              Symbols{Symbols},
                                                              Decorations{Decorations}
{
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId CodeGenVisitor::getCurrentFunctionTy() const
{
    return currFunctionType;
}

void CodeGenVisitor::setCurrentFunctionTy(TypesMgr::TypeId type)
{
    currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx)
{
    DEBUG_ENTER();
    code my_code;
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    for (auto ctxFunc : ctx->function())
    {
        subroutine subr = std::any_cast<subroutine>(visit(ctxFunc));
        my_code.add_subroutine(subr);
    }
    Symbols.popScope();
    DEBUG_EXIT();
    return my_code;
}

std::any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx)
{
    DEBUG_ENTER();
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    subroutine subr(ctx->ID()->getText());
    codeCounters.reset();
    std::vector<var> &&lvars = std::any_cast<std::vector<var>>(visit(ctx->declarations()));
    for (auto &onevar : lvars)
    {
        subr.add_var(onevar);
    }
    instructionList &&code = std::any_cast<instructionList>(visit(ctx->statements()));
    code = code || instruction(instruction::RETURN());
    subr.set_instructions(code);
    Symbols.popScope();
    DEBUG_EXIT();
    return subr;
}

std::any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx)
{
    DEBUG_ENTER();
    std::vector<var> lvars;
    for (auto &varDeclCtx : ctx->variable_decl())
    {
        var onevar = std::any_cast<var>(visit(varDeclCtx));
        lvars.push_back(onevar);
    }
    DEBUG_EXIT();
    return lvars;
}

std::any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t1 = getTypeDecor(ctx->type());
    std::size_t size = Types.getSizeOfType(t1);
    DEBUG_EXIT();
    // TODO: canviar el ID(0) per un bucle amb tots els ID
    return var{ctx->ID(0)->getText(), Types.to_string(t1), size};
}

std::any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    for (auto stCtx : ctx->statement())
    {
        instructionList &&codeS = std::any_cast<instructionList>(visit(stCtx));
        code = code || codeS;
    }
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    CodeAttribs &&codAtsE1 = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
    std::string addr1 = codAtsE1.addr;
    // std::string           offs1 = codAtsE1.offs;
    instructionList &code1 = codAtsE1.code;
    // TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
    CodeAttribs &&codAtsE2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr2 = codAtsE2.addr;
    // std::string           offs2 = codAtsE2.offs;
    instructionList &code2 = codAtsE2.code;
    // TypesMgr::TypeId tid2 = getTypeDecor(ctx->expr());
    code = code1 || code2 || instruction::LOAD(addr1, addr2);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    CodeAttribs &&codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr1 = codAtsE.addr;
    instructionList &code1 = codAtsE.code;
    // TODO: Actualitzar el zero qu ehe posat aqui només perque no peti
    instructionList &&code2 = std::any_cast<instructionList>(visit(ctx->statements(0)));
    std::string label = codeCounters.newLabelIF();
    std::string labelEndIf = "endif" + label;
    code = code1 || instruction::FJUMP(addr1, labelEndIf) ||
           code2 || instruction::LABEL(labelEndIf);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitFunctionCallStmt(AslParser::FunctionCallStmtContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    // std::string name = ctx->ident()->ID()->getSymbol()->getText();
    std::string name = ctx->functionCall()->ident()->getText();
    code = instruction::CALL(name);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAtsE = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
    std::string addr1 = codAtsE.addr;
    // std::string          offs1 = codAtsE.offs;
    instructionList &code1 = codAtsE.code;
    instructionList &code = code1;
    // TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
    code = code1 || instruction::READI(addr1);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr1 = codAt1.addr;
    // std::string         offs1 = codAt1.offs;
    instructionList &code1 = codAt1.code;
    instructionList &code = code1;
    // TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
    code = code1 || instruction::WRITEI(addr1);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    std::string s = ctx->STRING()->getText();
    code = code || instruction::WRITES(s);
    DEBUG_EXIT();
    return code;
}

// std::any CodeGenVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
//   DEBUG_ENTER();
//   CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
//   DEBUG_EXIT();
//   return codAts;
// }

std::any CodeGenVisitor::visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAts = std::any_cast<CodeAttribs>(visit(ctx->children[0]));
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAts = std::any_cast<CodeAttribs>(visit(ctx->children[0]));
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    std::string addr1 = codAt1.addr;
    instructionList &code1 = codAt1.code;
    CodeAttribs &&codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
    std::string addr2 = codAt2.addr;
    instructionList &code2 = codAt2.code;
    instructionList &&code = code1 || code2;
    // TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    // TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    // TypesMgr::TypeId  t = getTypeDecor(ctx);
    std::string temp = "%" + codeCounters.newTEMP();
    if (ctx->MUL())
        code = code || instruction::MUL(temp, addr1, addr2);
    else // (ctx->PLUS())
        code = code || instruction::ADD(temp, addr1, addr2);
    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    std::string addr1 = codAt1.addr;
    instructionList &code1 = codAt1.code;
    CodeAttribs &&codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
    std::string addr2 = codAt2.addr;
    instructionList &code2 = codAt2.code;
    instructionList &&code = code1 || code2;
    // TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    // TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    // TypesMgr::TypeId  t = getTypeDecor(ctx);
    std::string temp = "%" + codeCounters.newTEMP();
    code = code || instruction::EQ(temp, addr1, addr2);
    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitIntVal(AslParser::IntValContext *ctx)
{
    DEBUG_ENTER();
    instructionList code;
    std::string temp = "%" + codeCounters.newTEMP();
    code = instruction::ILOAD(temp, ctx->getText());
    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitFloatVal(AslParser::FloatValContext *ctx)
{
    DEBUG_ENTER();
    // TODO
    DEBUG_EXIT();
    return 0;
}

std::any CodeGenVisitor::visitBoolVal(AslParser::BoolValContext *ctx)
{
    DEBUG_ENTER();
    // TODO
    DEBUG_EXIT();
    return 0;
}

std::any CodeGenVisitor::visitCharVal(AslParser::CharValContext *ctx)
{
    DEBUG_ENTER();
    // TODO
    DEBUG_EXIT();
    return 0;
}

std::any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs &&codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx)
{
    DEBUG_ENTER();
    CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
    DEBUG_EXIT();
    return codAts;
}

// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const
{
    return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const
{
    return Decorations.getType(ctx);
}

// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string &addr,
                                         const std::string &offs,
                                         instructionList &code) : addr{addr}, offs{offs}, code{code}
{
}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string &addr,
                                         const std::string &offs,
                                         instructionList &&code) : addr{addr}, offs{offs}, code{code}
{
}
```


#### asl/CodeGenVisitor.h

```cpp
//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"
#include "AslBaseVisitor.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>

// using namespace std;

//////////////////////////////////////////////////////////////////////
// Class CodeGenVisitor: derived from AslBaseVisitor.
// The tree visitor go through the parser tree and call the methods of
// this class to generate the code of the program. This is done
// once the SymbolsVisitor and TypeCheckVisitor have finish with no
// semantic error. So all the symbols of the program has been added to
// their respective scope and the type of each expresion has also be
// computed and decorate the parse tree. In this visit, if some node/method
// does not have an associated task, it does not have to be visited/called
// so no redefinition is needed.

class CodeGenVisitor final : public AslBaseVisitor
{

public:
    // Constructor
    CodeGenVisitor(TypesMgr &Types,
                   SymTable &Symbols,
                   TreeDecoration &Decorations);

    // Methods to visit each kind of node:
    std::any visitProgram(AslParser::ProgramContext *ctx);
    std::any visitFunction(AslParser::FunctionContext *ctx);
    std::any visitDeclarations(AslParser::DeclarationsContext *ctx);
    std::any visitVariable_decl(AslParser::Variable_declContext *ctx);
    // std::any visitType(AslParser::TypeContext *ctx);
    std::any visitStatements(AslParser::StatementsContext *ctx);
    std::any visitAssignStmt(AslParser::AssignStmtContext *ctx);
    std::any visitIfStmt(AslParser::IfStmtContext *ctx);
    std::any visitFunctionCallStmt(AslParser::FunctionCallStmtContext *ctx);
    std::any visitReadStmt(AslParser::ReadStmtContext *ctx);
    std::any visitWriteExpr(AslParser::WriteExprContext *ctx);
    std::any visitWriteString(AslParser::WriteStringContext *ctx);
    // std::any visitLeft_expr(AslParser::Left_exprContext *ctx);
    std::any visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx);
    std::any visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx);
    std::any visitExprIdent(AslParser::ExprIdentContext *ctx);
    std::any visitArithmetic(AslParser::ArithmeticContext *ctx);
    std::any visitRelational(AslParser::RelationalContext *ctx);
    std::any visitIntVal(AslParser::IntValContext *ctx);
    std::any visitFloatVal(AslParser::FloatValContext *ctx);
    std::any visitBoolVal(AslParser::BoolValContext *ctx);
    std::any visitCharVal(AslParser::CharValContext *ctx);
    std::any visitIdent(AslParser::IdentContext *ctx);

private:
    // Attributes
    TypesMgr &Types;
    SymTable &Symbols;
    TreeDecoration &Decorations;
    counters codeCounters;
    // Current function type (assigned before visit its instructions)
    TypesMgr::TypeId currFunctionType;

    // Accessor/Mutator to the type (TypeId) of the current function
    TypesMgr::TypeId getCurrentFunctionTy() const;
    void setCurrentFunctionTy(TypesMgr::TypeId type);

    // Getters for the necessary tree node atributes:
    //   Scope and Type
    SymTable::ScopeId getScopeDecor(antlr4::ParserRuleContext *ctx) const;
    TypesMgr::TypeId getTypeDecor(antlr4::ParserRuleContext *ctx) const;

    //////////////////////////////////////////////////////////////////
    // Class CodeAttribs: is declared inside CodeGenVisitor as an
    // auxiliary class to group the three attributes necessaries for
    // code generation (address, offset, instructions list).
    // Some language constructions, for example expressions, can
    // generate the three attributes. Others, like statements, only
    // generate the instruction list.
    class CodeAttribs
    {

    public:
        // Constructors
        CodeAttribs(const std::string &addr,
                    const std::string &offs,
                    instructionList &code);
        CodeAttribs(const std::string &addr,
                    const std::string &offs,
                    instructionList &&code);

        // Attributes (publics):
        //   - the address that will hold the value of an expression
        std::string addr;
        //   - the offset applied to the address (for array access)
        std::string offs;
        //   - the three-address code associated to an statement/expression
        instructionList code;

    }; // class CodeAttribs

}; // class CodeGenVisitor
```


#### asl/main.cpp

```cpp
/////////////////////////////////////////////////////////////////
//
//    Main program - Front-end for the Asl programming language.
//                   It performs the translation and
//                   writes the generated code
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: Lluís Padró (padro@cs.upc.edu)
//             José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include "antlr4-runtime.h"
#include "AslLexer.h"
#include "AslParser.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"
#include "SymbolsVisitor.h"
#include "TypeCheckVisitor.h"
#include "../common/code.h"
#include "CodeGenVisitor.h"

#include <iostream>
#include <fstream> // ifstream

#include <cstdio>  // fopen
#include <cstdlib> // EXIT_FAILURE, EXIT_SUCCESS
#include <cstring> // strcmp

// using namespace std;
// using namespace antlr4;

int main(int argc, const char *argv[])
{

    bool doTypeCheck = true, doCodeGen = true, doLLVM = false;
    std::string filename;
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--noTypecheck")
            doTypeCheck = false;
        else if (std::string(argv[i]) == "--noCodegen")
            doCodeGen = false;
        else if (std::string(argv[i]) == "--genLLVM")
            doLLVM = true;
        else if (filename == "")
        {
            // it is not a valid option, must be the file name, make sure it is the first one
            filename = std::string(argv[i]);
        }
        else
        { // something unexpected came: Not a valid option, and a second filename
            std::cout << "Usage: ./asl [--noTypecheck|--noCodegen|--genLLVM] [<file.asl>]" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // open input file (or std::cin) and create a character stream
    antlr4::ANTLRInputStream input;
    if (filename != "")
    {
        std::ifstream stream;
        stream.open(filename);
        if (stream.fail())
        {
            std::cout << "Could not open file: " << filename << std::endl;
            return EXIT_FAILURE;
        }
        input = antlr4::ANTLRInputStream(stream);
    }
    else
    { // read fron std::cin
        input = antlr4::ANTLRInputStream(std::cin);
    }

    // create a lexer that consumes the character stream and produces a token stream
    AslLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    // create a parser that consumes the token stream, and parses it.
    AslParser parser(&tokens);

    // call the parser and get the parse tree
    antlr4::tree::ParseTree *tree = parser.program();

    // check for lexical or syntactical errors
    if (lexer.getNumberOfSyntaxErrors() > 0 or
        parser.getNumberOfSyntaxErrors() > 0)
    {
        std::cout << "Lexical and/or syntactical errors have been found." << std::endl;
        return EXIT_FAILURE;
    }

    // print the parse tree (for debugging purposes)
    // std::cout << tree->toStringTree(&parser) << std::endl;

    if (not doTypeCheck)
    {
        std::cout << "-- Early stop: no typecheck has been made." << std::endl;
        return EXIT_SUCCESS;
    }

    // auxililary classes we are going to need to store information while
    // traversing the tree. They are described below in this document
    TypesMgr types;
    SymTable symbols(types);
    TreeDecoration decorations;
    SemErrors errors;

    // create a visitor that looks for variables and function declarations
    // in the tree and stores required information
    SymbolsVisitor symboldecl(types, symbols, decorations, errors);
    symboldecl.visit(tree);

    // create another visitor that will perform type checkings wherever
    // it is needed (on expressions, assignments, parameter passing, etc)
    TypeCheckVisitor typecheck(types, symbols, decorations, errors);
    typecheck.visit(tree);

    if (errors.getNumberOfSemanticErrors() > 0)
    {
        std::cout << "There are semantic errors: no code generated." << std::endl;
        return EXIT_FAILURE;
    }

    if (not doCodeGen)
    {
        std::cout << "-- Early stop: no code generated." << std::endl;
        return EXIT_SUCCESS;
    }

    // create a third visitor that will return the generated code
    // for each part of the tree, and will store it in 'mycode'
    CodeGenVisitor codegenerator(types, symbols, decorations);
    code mycode = std::any_cast<code>(codegenerator.visit(tree));

    // print generated code as output
    std::cout << mycode.dump() << std::endl;

    if (doLLVM)
    {
        std::string llvmStr = mycode.dumpLLVM(types, symbols);
        std::string llvmFileName;
        if (filename == "")
            llvmFileName = "output.ll";
        else
        {
            std::size_t slashPos = filename.rfind("/");
            std::size_t dotPos = filename.rfind(".");
            llvmFileName = filename.substr(slashPos + 1, dotPos - slashPos - 1) + ".ll";
        }
        std::ofstream myLLVMFile(llvmFileName, std::ofstream::out);
        myLLVMFile << llvmStr << std::endl;
        myLLVMFile.close();
    }

    return EXIT_SUCCESS;
}
```


#### asl/Makefile

```Makefile
# =================================================
#	@(#)makefile	1.3		AKK/ACT		20170507
#	@(#)makefile	1.2		AKK/ACT		20170329
# =================================================
#    This makefile assumes all files in this
#  directory belong to the one and only program.
# It also assumes you only have one grammar file.
# =================================================

# ----------
# VARIABLES
# ----------

# Adjust these lines according to your project

# The name to give to the program, e.g. main
PROGRAM		:= asl

# If you want the generated files to be in
# for instance the 'gen' subdirectory, then
# define the name of the additional directory here
#GENDIR		:= gen
# otherwise, put a '#' character in front of the
# line to turn it into comment.

# If you want your own sources to be in
# for instance the 'src' subdirectory, then
# define the name of the additional directory here
#SRCDIR		:= src
SRCDIR		:= ../common
# otherwise, put a '#' character in front of the
# line to turn it into comment.

# Define the name of your grammar.
# Can be done in two ways:
# 1a. Let 'make' figure out the name of the file
GRAMMAR.g4	:= $(wildcard *.g4)
# 1b. Or tell it yourself if there are more of them
#GRAMMAR.g4	:= Shell.g4

# The target language is C++
ANTLR4FLAGS := -Dlanguage=Cpp
# Note: By default the language would be Java

# Some more antlr4 options:
# Add or remove a leading '#' to disable or enable.
# Do not generate Visitor classes
#ANTLR4FLAGS += -no-visitor
# Do generate Visitor classes
ANTLR4FLAGS += -visitor
# Do not generate Listener classes
ANTLR4FLAGS += -no-listener
# Do generate Listener classes
#ANTLR4FLAGS += -listener


# The default target to make is:
#  1) give some help
#DEFAULT 	:= help
#  2) or make your program
DEFAULT 	:= $(PROGRAM)
# Select either alternative above


# ---------------------------------------------------------------
# Changes below this line are rarely needed.
# ---------------------------------------------------------------

# ==== ANTLR4 stuff ====

# This lets 'make' derive the base name of that grammar
GRAMMAR 	:= $(GRAMMAR.g4:.g4=)

# If GENDIR was defined then this tells antlr4 that
# it should place the generated files there.
ifneq ($(strip $(GENDIR) ),)
ANTLR4FLAGS += -o $(GENDIR)
endif

# The root directory of your antlr4 runtime is ...
ANTLR_ROOT := /assig/$(USER)/cl/runtime
#ANTLR_ROOT := /usr/local
#ANTLR_ROOT := /usr

# Where to find various parts of the runtime files
INCDIR		:= $(ANTLR_ROOT)/include/antlr4-runtime/
LIBDIR		:= $(ANTLR_ROOT)/lib/
BINDIR		:= $(ANTLR_ROOT)/bin
ANTLR4		:= $(BINDIR)/antlr4

# The minimal set of generated files needed for any grammar.
ifneq ($(strip $(GENDIR) ),)	# if GENDIR was defined
NEEDED.h	:= $(GENDIR)/$(GRAMMAR)Lexer.h   $(GENDIR)/$(GRAMMAR)Parser.h
NEEDED.cpp	:= $(GENDIR)/$(GRAMMAR)Lexer.cpp $(GENDIR)/$(GRAMMAR)Parser.cpp
else
NEEDED.h	:= $(GRAMMAR)Lexer.h   $(GRAMMAR)Parser.h
NEEDED.cpp	:= $(GRAMMAR)Lexer.cpp $(GRAMMAR)Parser.cpp
endif

# Make a list of all the needed source files
NEEDED		:= $(NEEDED.h) $(NEEDED.cpp)
# And all the object files generated from them
NEEDED.o	:= $(NEEDED.cpp:.cpp=.o)

# ==== MAKE stuff ====

# Wildcard definitions to generate lists of file names
# existing in this directory

# Available source files here are ...
ifneq ($(strip $(SRCDIR) ),)	# if SRCDIR was defined
HEADERS		= $(wildcard $(SRCDIR)/*.h ./*.h)
SOURCE.c	= $(wildcard $(SRCDIR)/*.c ./*.c)
SOURCE.cc	= $(wildcard $(SRCDIR)/*.cc ./*.cc)
SOURCE.cpp	= $(wildcard $(SRCDIR)/*.cpp ./*.cpp)
else
HEADERS		= $(wildcard *.h)
SOURCE.c	= $(wildcard *.c)
SOURCE.cc	= $(wildcard *.cc)
SOURCE.cpp	= $(wildcard *.cpp)
endif

ifneq ($(strip $(GENDIR) ),)	# if GENDIR was defined
# also add those in that subdirectory
HEADERS		+= $(wildcard $(GENDIR)/*.h)
SOURCE.cpp	+= $(wildcard $(GENDIR)/*.cpp)
endif

# List of all the currently available source files
SOURCES		= $(SOURCE.c) $(SOURCE.cc) $(SOURCE.cpp)
# And all the object files generated from them
OBJECTS		= $(SOURCE.c:.c=.o) $(SOURCE.cc:.cc=.o) $(SOURCE.cpp:.cpp=.o)

# ==== C++ stuff ====

# Which compiler we are going to use
CCC	= g++
CXX	= g++
CC 	= g++

# Tell compiler:
# ... where to search for additional header files ...
ifneq ($(strip $(SRCDIR) ),)	# if SRCDIR was defined
#  ... our own headers files
CPPFLAGS += -I. -I$(SRCDIR)
endif
ifneq ($(strip $(GENDIR) ),)
#  ... antlr4 generated header files
CPPFLAGS += -I$(GENDIR)
endif
#  ... the antlr4 runtime files
CPPFLAGS += -I$(INCDIR)
# ... select the C++ version desired,
CPPFLAGS += --std=c++17
# ... enable various warnings,
CPPFLAGS += -Wall -Wextra
# ... but disable these ones,
CPPFLAGS += -Wno-unused-parameter -Wno-attributes -Woverloaded-virtual=0
# ... always add extra debugging information for gdb.
#CPPFLAGS += -g


# Tell the compiler to link the antlr4 runtime library to the program
LDLIBS	+= -L$(LIBDIR) -lantlr4-runtime


# Which generated files really *do* exist (e.g. for clean-up)
ifneq ($(strip $(GENDIR) ),)	# if GENDIR was defined
GENERATED	:= $(wildcard $(GENDIR)/$(GRAMMAR)*.h) \
			   $(wildcard $(GENDIR)/$(GRAMMAR)*.cpp) \
			   $(wildcard $(GENDIR)/$(GRAMMAR)*.interp) \
			   $(wildcard $(GENDIR)/$(GRAMMAR)*.tokens)
TOKENS		:= $(wildcard $(GENDIR)/$(GRAMMAR)*.tokens)
else
GENERATED	:= $(wildcard $(GRAMMAR)*.h) \
			   $(wildcard $(GRAMMAR)*.cpp) \
			   $(wildcard $(GRAMMAR)*.interp) \
			   $(wildcard $(GRAMMAR)*.tokens)
TOKENS		:= $(wildcard $(GRAMMAR)*.tokens)
endif

# ---------------------------------------------------------------
# MAKE TARGETS
# ---------------------------------------------------------------

# list of 'targets' that are not real files at all
.PHONY:	DEFAULT help antlr clean realclean pristine

# The default target tells the user about the available targets.
DEFAULT		: $(DEFAULT)

# Give some help
help		:
	@echo "The targets to make are:"
	@echo "  make antlr		: the files generated by antlr"
	@echo "  make $(PROGRAM)		: the desired program"
#	@echo "  make debug		: a version of the program with"
#	@echo "			  extra information for the debugger"
	@echo "	Note: The 'make' tool can not know what files will"
	@echo "	be generated by antlr, therefore you must do"
	@echo "	    make antlr"
	@echo "	at least once before trying to make your program"
	@echo "For clean-up there are three more targets:"
	@echo "  make clean		: remove .o files"
	@echo "  make realclean	: also remove the generated files"
	@echo "  make pristine		: also remove the program"


# A pseudo target to force generating needed files
antlr		: $(NEEDED)


# How to make the 'main' program.
$(PROGRAM)	: $(TOKENS) $(OBJECTS)
	$(LINK.cc) -o $@ $(OBJECTS) $(LDLIBS)

# Special 'debug' target
debug		: $(OBJECTS) $(PROGRAM)
debug		: CPPFLAGS += -g


# Various pseudo-targets to clean up things.
clean		:
	-rm -f $(OBJECTS)
realclean	: clean				# if there are any generated files
ifneq ($(strip $(GENERATED) ),)
	-rm -rf $(GENERATED)
endif
pristine	: realclean
	-rm -rf $(PROGRAM) _antlr
#	-rm -rf $(PROGRAM) _antlr _deps

# -------------------------------------------

# How to make or update the generated files
$(NEEDED)		 	: $(GRAMMAR).g4
	@echo "## Creating the antlr generated files"
	$(ANTLR4) $(ANTLR4FLAGS) $(GRAMMAR).g4
$(TOKENS)			:
	@echo "## You should first do: make antlr"; exit 1

# ----------------------------------------------------

# Generate dependencies for all generated antlr4 files
_antlr		: $(GRAMMAR).g4
	@echo "## Updating the list of grammar dependent files"
	$(ANTLR4) -depend $(ANTLR4FLAGS) $(GRAMMAR).g4 > _antlr

# IFF we have any, then ...
ifneq ($(strip $(GENERATED) ),)
-include _antlr
endif

# CL: comemtem la inclusió de les dependències en antlr4-runtime
# # IFF we have some generated files then also ...
# ifneq ($(strip $(GENERATED) ),)
# # Determine dependencies between all sources files
# _deps		: $(HEADERS) $(SOURCES)
# 	@echo "## Updating the _deps dependency file"
# 	$(CXX) -MM $(CPPFLAGS) $(SOURCES) > _deps
# -include _deps
# endif

# =================================================
# Changelog:
# 2017707	- now supports having the userss source
#			  files in a separate 'src' subdirectory
# 20170329	- now supports having the generated
#			  antlr4 files in a subdirectory
#			- now 'include' is silent
#		  	- move some comments more verbose
#			- added an experimental 'debug' target
# =================================================
```


#### asl/SymbolsVisitor.cpp

```cpp
//////////////////////////////////////////////////////////////////////
//
//    SymbolsVisitor - Walk the parser tree to register symbols
//                     for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "SymbolsVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>
#include <vector>

#include <cstddef> // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;

// Constructor
SymbolsVisitor::SymbolsVisitor(TypesMgr &Types,
                               SymTable &Symbols,
                               TreeDecoration &Decorations,
                               SemErrors &Errors) : Types{Types},
                                                    Symbols{Symbols},
                                                    Decorations{Decorations},
                                                    Errors{Errors}
{
}

// Methods to visit each kind of node:
//
std::any SymbolsVisitor::visitProgram(AslParser::ProgramContext *ctx)
{
    DEBUG_ENTER();
    SymTable::ScopeId sc = Symbols.pushNewScope(SymTable::GLOBAL_SCOPE_NAME);
    putScopeDecor(ctx, sc);
    for (auto ctxFunc : ctx->function())
    {
        visit(ctxFunc);
    }
    // Symbols.print();
    Symbols.popScope();
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitFunction(AslParser::FunctionContext *ctx)
{
    DEBUG_ENTER();
    std::string funcName = ctx->ID()->getText();
    SymTable::ScopeId sc = Symbols.pushNewScope(funcName);
    putScopeDecor(ctx, sc);
    // Visitem els paràmetres i el tipus de la funció
    if (ctx->params())
        visit(ctx->params());
    if (ctx->type())
        visit(ctx->type());
    visit(ctx->declarations());
    Symbols.popScope();
    std::string ident = ctx->ID()->getText();
    if (Symbols.findInCurrentScope(ident))
    {
        Errors.declaredIdent(ctx->ID());
    }
    else
    {
        std::vector<TypesMgr::TypeId> lParamsTy;
        if (ctx->params())
        {
            for (std::size_t i = 0; i < ctx->params()->ID().size(); ++i)
            {
                TypesMgr::TypeId t1 = getTypeDecor(ctx->params()->type(i));
                lParamsTy.push_back(t1);
            }
        }
        TypesMgr::TypeId tRet;
        if (ctx->type())
            tRet = getTypeDecor(ctx->type());
        else
            tRet = Types.createVoidTy();
        TypesMgr::TypeId tFunc = Types.createFunctionTy(lParamsTy, tRet);
        Symbols.addFunction(ident, tFunc);
    }
    // Symbols.print();
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx)
{
    DEBUG_ENTER();
    visitChildren(ctx);
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->type());
    for (auto ident : ctx->ID())
    {
        if (Symbols.findInCurrentScope(ident->getText()))
        {
            // Error si redeclarem variables
            Errors.declaredIdent(ident);
        }
        else
        {
            // Mira el tipus de la declaració
            TypesMgr::TypeId t1 = getTypeDecor(ctx->type());
            // I afegim la variable a la taula de símbols local
            Symbols.addLocalVar(ident->getText(), t1);
        }
    }
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitBasicType(AslParser::BasicTypeContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t;
    if (ctx->INT())
        t = Types.createIntegerTy();
    else if (ctx->FLOAT())
        t = Types.createFloatTy();
    else if (ctx->BOOL())
        t = Types.createBooleanTy();
    else if (ctx->CHAR())
        t = Types.createCharacterTy();
    putTypeDecor(ctx, t);
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitBasicTypeLabel(AslParser::BasicTypeLabelContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->basicType());
    TypesMgr::TypeId t = getTypeDecor(ctx->basicType());
    putTypeDecor(ctx, t);
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitArrayType(AslParser::ArrayTypeContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->basicType());
    TypesMgr::TypeId t = getTypeDecor(ctx->basicType());
    int size = std::stoi(ctx->INTVAL()->getText());
    TypesMgr::TypeId tRet = Types.createArrayTy(size, t);
    putTypeDecor(ctx, tRet);
    DEBUG_EXIT();
    return 0;
}

// std::any SymbolsVisitor::visitStatements(AslParser::StatementsContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitRelational(AslParser::RelationalContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitValue(AslParser::ValueContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIdent(AslParser::IdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any SymbolsVisitor::visitParams(AslParser::ParamsContext *ctx)
{
    DEBUG_ENTER();
    // Recorrem els paràmetres i el seu tipus
    for (std::size_t i = 0; i < ctx->ID().size(); ++i)
    {
        auto ident = ctx->ID(i);
        visit(ctx->ID(i));
        visit(ctx->type(i));
        if (Symbols.findInCurrentScope(ident->getText()))
        {
            // Error si redeclarem variables
            Errors.declaredIdent(ident);
        }
        else
        {
            // Mira el tipus de la declaració
            TypesMgr::TypeId t1 = getTypeDecor(ctx->type(i));
            // I afegim la variable a la taula de símbols
            Symbols.addParameter(ident->getText(), t1);
        }
    }
    DEBUG_EXIT();
    return 0;
}

// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId SymbolsVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx)
{
    return Decorations.getScope(ctx);
}
TypesMgr::TypeId SymbolsVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx)
{
    return Decorations.getType(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope and Type
void SymbolsVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s)
{
    Decorations.putScope(ctx, s);
}
void SymbolsVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t)
{
    Decorations.putType(ctx, t);
}
```


#### asl/SymbolsVisitor.h

```cpp
//////////////////////////////////////////////////////////////////////
//
//    SymbolsVisitor - Walk the parser tree to register symbols
//                     for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"
#include "AslBaseVisitor.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

// using namespace std;

//////////////////////////////////////////////////////////////////////
// Class SymbolVisitor:  derived from AslBaseVisitor.
// The tree visitor go through the parse tree and call the methods of
// this class to register the symbols of the program in the symbol
// table. In this visit, if some node/method does not have an
// associated task, it does not have to be visited/called so
// no redefinition is needed.

class SymbolsVisitor final : public AslBaseVisitor
{

public:
    // Constructor
    SymbolsVisitor(TypesMgr &Types,
                   SymTable &Symbols,
                   TreeDecoration &Decorations,
                   SemErrors &Errors);

    // Methods to visit each kind of node.
    // Non visited nodes have been commented out:
    std::any visitProgram(AslParser::ProgramContext *ctx);
    std::any visitFunction(AslParser::FunctionContext *ctx);
    std::any visitDeclarations(AslParser::DeclarationsContext *ctx);
    std::any visitVariable_decl(AslParser::Variable_declContext *ctx);
    std::any visitBasicType(AslParser::BasicTypeContext *ctx);
    std::any visitBasicTypeLabel(AslParser::BasicTypeLabelContext *ctx);
    std::any visitArrayType(AslParser::ArrayTypeContext *ctx);
    // std::any visitStatements(AslParser::StatementsContext *ctx);
    // std::any visitAssignStmt(AslParser::AssignStmtContext *ctx);
    // std::any visitIfStmt(AslParser::IfStmtContext *ctx);
    // std::any visitProcCall(AslParser::ProcCallContext *ctx);
    // std::any visitReadStmt(AslParser::ReadStmtContext *ctx);
    // std::any visitWriteExpr(AslParser::WriteExprContext *ctx);
    // std::any visitWriteString(AslParser::WriteStringContext *ctx);
    // std::any visitLeft_expr(AslParser::Left_exprContext *ctx);
    // std::any visitExprIdent(AslParser::ExprIdentContext *ctx);
    // std::any visitArithmetic(AslParser::ArithmeticContext *ctx);
    // std::any visitRelational(AslParser::RelationalContext *ctx);
    // std::any visitValue(AslParser::ValueContext *ctx);
    // std::any visitIdent(AslParser::IdentContext *ctx);
    std::any visitParams(AslParser::ParamsContext *ctx);

private:
    // Attributes:
    TypesMgr &Types;
    SymTable &Symbols;
    TreeDecoration &Decorations;
    SemErrors &Errors;

    // Getters for the necessary tree node atributes:
    //   Scope and Type
    SymTable::ScopeId getScopeDecor(antlr4::ParserRuleContext *ctx);
    TypesMgr::TypeId getTypeDecor(antlr4::ParserRuleContext *ctx);

    // Setters for the necessary tree node attributes:
    //   Scope and Type
    void putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s);
    void putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t);

}; // class SymbolsVisitor
```


#### asl/TypeCheckVisitor.cpp

```cpp
//////////////////////////////////////////////////////////////////////
//
//    TypeCheckVisitor - Walk the parser tree to do the semantic
//                       typecheck for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "TypeCheckVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;

// Constructor
TypeCheckVisitor::TypeCheckVisitor(TypesMgr &Types,
                                   SymTable &Symbols,
                                   TreeDecoration &Decorations,
                                   SemErrors &Errors) : Types{Types},
                                                        Symbols{Symbols},
                                                        Decorations{Decorations},
                                                        Errors{Errors}
{
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId TypeCheckVisitor::getCurrentFunctionTy() const
{
    return currFunctionType;
}

void TypeCheckVisitor::setCurrentFunctionTy(TypesMgr::TypeId type)
{
    currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any TypeCheckVisitor::visitProgram(AslParser::ProgramContext *ctx)
{
    DEBUG_ENTER();
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    for (auto ctxFunc : ctx->function())
    {
        visit(ctxFunc);
    }
    if (Symbols.noMainProperlyDeclared())
        Errors.noMainProperlyDeclared(ctx);
    Symbols.popScope();
    Errors.print();
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitFunction(AslParser::FunctionContext *ctx)
{
    DEBUG_ENTER();
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    TypesMgr::TypeId t;
    if (ctx->type())
        t = getTypeDecor(ctx->type());
    else
        t = Types.createVoidTy();
    setCurrentFunctionTy(t);
    visit(ctx->statements());
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    Symbols.popScope();
    DEBUG_EXIT();
    return 0;
}

// std::any TypeCheckVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitType(AslParser::TypeContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitStatements(AslParser::StatementsContext *ctx)
// {
//     DEBUG_ENTER();
//     visitChildren(ctx);
//     DEBUG_EXIT();
//     return 0;
// }

std::any TypeCheckVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->left_expr());
    visit(ctx->expr());
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->left_expr());
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr());

    if (Types.isVoidTy(tRight))
    {
        Errors.isNotFunction(ctx->expr());
    }
    // Si no son compatibles i no son errors (tractant els arrays correctament), error
    else if (not Types.isErrorTy(tLeft) and not Types.isErrorTy(tRight) and
             not Types.copyableTypes(tLeft, tRight))
    {
        Errors.incompatibleAssignment(ctx->ASSIGN());
    }

    if ((not Types.isErrorTy(tLeft)) and (not getIsLValueDecor(ctx->left_expr())))
    {
        Errors.nonReferenceableLeftExpr(ctx->left_expr());
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
        Errors.booleanRequired(ctx);
    visit(ctx->statements(0));
    if (ctx->statements().size() > 1)
        visit(ctx->statements(1));
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
        Errors.booleanRequired(ctx);
    visit(ctx->statements());
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitFunctionCallExpr(AslParser::FunctionCallExprContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->functionCall());
    TypesMgr::TypeId t = getTypeDecor(ctx->functionCall());
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->left_expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
    if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)) and
        (not Types.isFunctionTy(t1)))
        Errors.readWriteRequireBasic(ctx);
    if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
        Errors.nonReferenceableExpression(ctx);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)))
        Errors.readWriteRequireBasic(ctx);
    DEBUG_EXIT();
    return 0;
}

// std::any TypeCheckVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any TypeCheckVisitor::visitReturn(AslParser::ReturnContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t1 = getCurrentFunctionTy();
    if (ctx->expr())
    {
        visit(ctx->expr());
        TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
        // Hem de comprovar que sigui del mateix tipus que la funció
        if (not Types.isErrorTy(t1) and not Types.isErrorTy(t2) and not Types.copyableTypes(t1, t2))
            Errors.incompatibleReturn(ctx->RETURN());
    }
    else
    {
        // Si no hi ha expressió i no es void, també donem error
        if (not Types.isErrorTy(t1) and not Types.isVoidTy(t1))
            Errors.incompatibleReturn(ctx->RETURN());
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->array());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->array());
    putTypeDecor(ctx, t1);
    putIsLValueDecor(ctx, true);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->ident());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
    putTypeDecor(ctx, t1);
    bool b = getIsLValueDecor(ctx->ident());
    putIsLValueDecor(ctx, b);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t = getTypeDecor(ctx->expr());
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitFunctionCall(AslParser::FunctionCallContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->ident());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());

    // Si no es funció error
    if (not Types.isErrorTy(t1))
    {
        if (not Types.isFunctionTy(t1))
        {
            Errors.isNotCallable(ctx->ident());
        }
        else
        {
            TypesMgr::TypeId tRet = Types.getFuncReturnType(t1);
            putTypeDecor(ctx, tRet);
            putIsLValueDecor(ctx, false);
        }
    }

    // Si no tenen la mateixa quantitat de paràmetres, error
    std::size_t nParamsFunction = Types.isFunctionTy(t1) ? Types.getNumOfParameters(t1) : 0;
    std::size_t nParamsCall = ctx->expr().size();
    if (Types.isFunctionTy(t1) and nParamsFunction != nParamsCall)
    {
        Errors.numberOfParameters(ctx->ident());
    }

    // I visitem igualment els paràmetres
    if (ctx->expr().size())
    {
        for (std::size_t i = 0; i < nParamsCall; ++i)
        {
            visit(ctx->expr(i));
            if (i < nParamsFunction)
            {
                TypesMgr::TypeId tParamFunction = getTypeDecor(ctx->expr(i));
                TypesMgr::TypeId tParamCall = Types.getParameterType(t1, i);

                if (not Types.isErrorTy(tParamFunction) and not Types.copyableTypes(tParamCall, tParamFunction))
                {
                    Errors.incompatibleParameter(ctx->expr(i), i + 1, ctx->ident());
                }
            }
        }
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitUnary(AslParser::UnaryContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t)) and (not Types.isNumericTy(t)))
    {
        Errors.incompatibleOperator(ctx->op);
    }
    else
    {
        putTypeDecor(ctx, t);
        putIsLValueDecor(ctx, false);
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

    TypesMgr::TypeId tRes;
    if (ctx->op->getText() == "%")
    {
        // El mòdul exigeix estrictament enters
        if (((not Types.isErrorTy(t1)) and (not Types.isIntegerTy(t1))) or
            ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2))))
        {
            Errors.incompatibleOperator(ctx->op);
        }
        tRes = Types.createIntegerTy();
    }
    else
    {
        // Multiplicació i divisió permeten qualsevol numèric
        if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or
            ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2))))
        {
            Errors.incompatibleOperator(ctx->op);
        }
        if (Types.isFloatTy(t1) or Types.isFloatTy(t2))
        {
            tRes = Types.createFloatTy();
        }
        else
        {
            tRes = Types.createIntegerTy();
        }
    }

    // Assignem el tipus resultant
    putTypeDecor(ctx, tRes);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr(0));
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    std::string oper = ctx->op->getText();
    // Si no son errors i no son comparables, afegeix un error
    if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
        (not Types.comparableTypes(t1, t2, oper)))
        Errors.incompatibleOperator(ctx->op);
    TypesMgr::TypeId t = Types.createBooleanTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitNot(AslParser::NotContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
        Errors.incompatibleOperator(ctx->op);
    TypesMgr::TypeId t = Types.createBooleanTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitLogic(AslParser::LogicContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->expr(0));
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    if (((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1))) or
        ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2))))
        Errors.incompatibleOperator(ctx->op);

    TypesMgr::TypeId t = Types.createBooleanTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIntVal(AslParser::IntValContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t = Types.createIntegerTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitFloatVal(AslParser::FloatValContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t = Types.createFloatTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitBoolVal(AslParser::BoolValContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t = Types.createBooleanTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitCharVal(AslParser::CharValContext *ctx)
{
    DEBUG_ENTER();
    TypesMgr::TypeId t = Types.createCharacterTy();
    putTypeDecor(ctx, t);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->ident());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
    putTypeDecor(ctx, t1);
    bool b = getIsLValueDecor(ctx->ident());
    putIsLValueDecor(ctx, b);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArrayAccess(AslParser::ArrayAccessContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->array());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->array());
    putTypeDecor(ctx, t1);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArray(AslParser::ArrayContext *ctx)
{
    DEBUG_ENTER();
    visit(ctx->ident());
    visit(ctx->expr());
    TypesMgr::TypeId tArray = getTypeDecor(ctx->ident());
    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr());

    if (not Types.isErrorTy(tArray))
    {
        if (not Types.isArrayTy(tArray))
        {
            Errors.nonArrayInArrayAccess(ctx->ident());
        }
        else
        {
            TypesMgr::TypeId tElemArray = Types.getArrayElemType(tArray);
            putTypeDecor(ctx, tElemArray);
        }
    }

    if (not Types.isErrorTy(tExpr) and not Types.isIntegerTy(tExpr))
        Errors.nonIntegerIndexInArrayAccess(ctx->expr());

    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx)
{
    DEBUG_ENTER();
    std::string ident = ctx->getText();
    // Si no esta declarada, posem un error
    if (Symbols.findInStack(ident) == -1)
    {
        Errors.undeclaredIdent(ctx->ID());
        TypesMgr::TypeId te = Types.createErrorTy();
        putTypeDecor(ctx, te);
        putIsLValueDecor(ctx, true);
    }
    else
    {
        TypesMgr::TypeId t1 = Symbols.getType(ident);
        putTypeDecor(ctx, t1);
        if (Symbols.isFunctionClass(ident))
        {
            putIsLValueDecor(ctx, false);
        }
        else
        {
            putIsLValueDecor(ctx, true);
        }
    }
    DEBUG_EXIT();
    return 0;
}

// std::any TypeCheckVisitor::visitXXX(AslParser::XXXContext *ctx){
//     DEBUG_ENTER();
//     visitChildren(ctx);
//     visit(ctx->YYY());
//     TypesMgr::TypeId t = getTypeDecor(ctx->YYY());
//     putTypeDecor(ctx, t);
//     DEBUG_EXIT();
//     return 0;
// }

bool TypeCheckVisitor::allPrimitiveType(const std::vector<TypesMgr::TypeId> &types) const
{
    for (unsigned int i = 0; i < types.size(); ++i)
    {
        if (not Types.isErrorTy(types[i]) and not Types.isPrimitiveTy(types[i]))
            return false;
    }
    return true;
}

bool TypeCheckVisitor::allSameType(const std::vector<TypesMgr::TypeId> &types) const
{
    int firstNonErrorPos = -1;
    for (unsigned int i = 0; i < types.size(); ++i)
    {
        if (not Types.isErrorTy(types[i]))
        {
            firstNonErrorPos = i;
            break;
        }
    }
    if (firstNonErrorPos != -1)
    {
        for (unsigned int i = firstNonErrorPos + 1; i < types.size(); ++i)
        {
            if (not Types.isErrorTy(types[i]) and not Types.equalTypes(types[firstNonErrorPos], types[i]))
                return false;
        }
        return true;
    }
    return true;
}

bool TypeCheckVisitor::allNumericType(const std::vector<TypesMgr::TypeId> &types) const
{
    for (unsigned int i = 0; i < types.size(); ++i)
    {
        if (not Types.isNumericTy(types[i]) and not Types.isErrorTy(types[i]))
            return false;
    }
    return true;
}

TypesMgr::TypeId TypeCheckVisitor::getTypeCoercion(const std::vector<TypesMgr::TypeId> &types) const
{
    if (allPrimitiveType(types))
    {
        if (allSameType(types))
        {
            return types[0];
        }
        else if (allNumericType(types))
        {
            return Types.createFloatTy();
        }
    }
    // O perque no tots son primitius o perque no son ni tots numerics ni tots iguals
    return Types.createErrorTy();
}

// Getters for the necessary tree node atributes:
//   Scope, Type ans IsLValue
SymTable::ScopeId TypeCheckVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx)
{
    return Decorations.getScope(ctx);
}

TypesMgr::TypeId TypeCheckVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx)
{
    return Decorations.getType(ctx);
}

bool TypeCheckVisitor::getIsLValueDecor(antlr4::ParserRuleContext *ctx)
{
    return Decorations.getIsLValue(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope, Type ans IsLValue
void TypeCheckVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s)
{
    Decorations.putScope(ctx, s);
}

void TypeCheckVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t)
{
    Decorations.putType(ctx, t);
}

void TypeCheckVisitor::putIsLValueDecor(antlr4::ParserRuleContext *ctx, bool b)
{
    Decorations.putIsLValue(ctx, b);
}
```


#### asl/TypeCheckVisitor.h

```cpp
//////////////////////////////////////////////////////////////////////
//
//    TypeCheckVisitor - Walk the parser tree to do the semantic
//                       typecheck for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"
#include "AslBaseVisitor.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

// using namespace std;

//////////////////////////////////////////////////////////////////////
// Class TypeCheckVisitor: derived from AslBaseVisitor.
// The tree visitor go through the parser tree and call the methods of
// this class to do the semantic typecheck of the program. This is
// done once the SymbolsVisitor has finish and all the symbols of the
// program has been added to their respective scope. In this visit,
// if some node/method does not have an associated task, it does not
// have to be visited/called so no redefinition is needed.

class TypeCheckVisitor final : public AslBaseVisitor
{

public:
    // Constructor
    TypeCheckVisitor(TypesMgr &Types,
                     SymTable &Symbols,
                     TreeDecoration &Decorations,
                     SemErrors &Errors);

    // Methods to visit each kind of node.
    // Non visited nodes have been commented out:
    std::any visitProgram(AslParser::ProgramContext *ctx);
    std::any visitFunction(AslParser::FunctionContext *ctx);
    // std::any visitDeclarations(AslParser::DeclarationsContext *ctx);
    // std::any visitVariable_decl(AslParser::Variable_declContext *ctx);
    // std::any visitType(AslParser::TypeContext *ctx);
    // std::any visitStatements(AslParser::StatementsContext *ctx);
    std::any visitAssignStmt(AslParser::AssignStmtContext *ctx);
    std::any visitIfStmt(AslParser::IfStmtContext *ctx);
    std::any visitWhileStmt(AslParser::WhileStmtContext *ctx);
    std::any visitReadStmt(AslParser::ReadStmtContext *ctx);
    std::any visitWriteExpr(AslParser::WriteExprContext *ctx);
    std::any visitReturn(AslParser::ReturnContext *ctx);
    // std::any visitWriteString(AslParser::WriteStringContext *ctx);
    // std::any visitLeft_expr(AslParser::Left_exprContext *ctx);
    std::any visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx);
    std::any visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx);
    std::any visitParenthesis(AslParser::ParenthesisContext *ctx);
    std::any visitFunctionCallExpr(AslParser::FunctionCallExprContext *ctx);
    std::any visitFunctionCall(AslParser::FunctionCallContext *ctx);
    std::any visitUnary(AslParser::UnaryContext *ctx);
    std::any visitArithmetic(AslParser::ArithmeticContext *ctx);
    std::any visitRelational(AslParser::RelationalContext *ctx);
    std::any visitNot(AslParser::NotContext *ctx);
    std::any visitLogic(AslParser::LogicContext *ctx);
    std::any visitIntVal(AslParser::IntValContext *ctx);
    std::any visitFloatVal(AslParser::FloatValContext *ctx);
    std::any visitBoolVal(AslParser::BoolValContext *ctx);
    std::any visitCharVal(AslParser::CharValContext *ctx);
    std::any visitExprIdent(AslParser::ExprIdentContext *ctx);
    std::any visitArrayAccess(AslParser::ArrayAccessContext *ctx);
    std::any visitArray(AslParser::ArrayContext *ctx);
    std::any visitIdent(AslParser::IdentContext *ctx);

private:
    // Attributes
    TypesMgr &Types;
    SymTable &Symbols;
    TreeDecoration &Decorations;
    SemErrors &Errors;
    // Current function type (assigned before visit its instructions)
    TypesMgr::TypeId currFunctionType;

    // Accessor/Mutator to the type (TypeId) of the current function
    TypesMgr::TypeId getCurrentFunctionTy() const;
    void setCurrentFunctionTy(TypesMgr::TypeId type);

    // Getters for the necessary tree node atributes:
    //   Scope, Type ans IsLValue
    SymTable::ScopeId getScopeDecor(antlr4::ParserRuleContext *ctx);
    TypesMgr::TypeId getTypeDecor(antlr4::ParserRuleContext *ctx);
    bool getIsLValueDecor(antlr4::ParserRuleContext *ctx);

    // Auxiliary methods to check the properties of types
    bool allPrimitiveType(const std::vector<TypesMgr::TypeId> &types) const;
    bool allSameType(const std::vector<TypesMgr::TypeId> &types) const;
    bool allNumericType(const std::vector<TypesMgr::TypeId> &types) const;
    TypesMgr::TypeId getTypeCoercion(const std::vector<TypesMgr::TypeId> &types) const;

    // Setters for the necessary tree node attributes:
    //   Scope, Type ans IsLValue
    void putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s);
    void putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t);
    void putIsLValueDecor(antlr4::ParserRuleContext *ctx, bool b);

}; // class TypeCheckVisitor
```


### common

#### common/code.cpp

```cpp
/////////////////////////////////////////////////////////////////
//
//    TVM - t-Code Virtual Machine
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: Lluis Padro (padro@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.320 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "code.h"
#include "LLVMCodeGen.h"

using namespace std;

////////////////////////////////////////////////////////////////////
/// Implementation for class 'instruction'

/// Constructor
instruction::instruction(Operation op,
                         const std::string &a1, const std::string &a2, const std::string &a3)
{
    oper = op;
    arg1 = a1;
    arg2 = a2;
    arg3 = a3;
}

instruction instruction::LABEL(const std::string &a1) { return instruction(_LABEL, a1); }
instruction instruction::UJUMP(const std::string &a1) { return instruction(_UJUMP, a1); }
instruction instruction::FJUMP(const std::string &a1, const std::string &a2) { return instruction(_FJUMP, a1, a2); }
instruction instruction::HALT(const std::string &a1) { return instruction(_HALT, a1); }
instruction instruction::PUSH(const std::string &a1) { return instruction(_PUSH, a1); }
instruction instruction::POP(const std::string &a1) { return instruction(_POP, a1); }
instruction instruction::CALL(const std::string &a1) { return instruction(_CALL, a1); }
instruction instruction::RETURN() { return instruction(_RETURN); }
instruction instruction::ADD(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_ADD, a1, a2, a3); }
instruction instruction::SUB(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_SUB, a1, a2, a3); }
instruction instruction::MUL(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_MUL, a1, a2, a3); }
instruction instruction::DIV(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_DIV, a1, a2, a3); }
instruction instruction::EQ(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_EQ, a1, a2, a3); }
instruction instruction::LT(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_LT, a1, a2, a3); }
instruction instruction::LE(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_LE, a1, a2, a3); }
instruction instruction::AND(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_AND, a1, a2, a3); }
instruction instruction::OR(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_OR, a1, a2, a3); }
instruction instruction::FADD(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FADD, a1, a2, a3); }
instruction instruction::FSUB(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FSUB, a1, a2, a3); }
instruction instruction::FMUL(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FMUL, a1, a2, a3); }
instruction instruction::FDIV(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FDIV, a1, a2, a3); }
instruction instruction::FEQ(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FEQ, a1, a2, a3); }
instruction instruction::FLT(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FLT, a1, a2, a3); }
instruction instruction::FLE(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_FLE, a1, a2, a3); }
instruction instruction::NOT(const std::string &a1, const std::string &a2) { return instruction(_NOT, a1, a2); }
instruction instruction::NEG(const std::string &a1, const std::string &a2) { return instruction(_NEG, a1, a2); }
instruction instruction::FNEG(const std::string &a1, const std::string &a2) { return instruction(_FNEG, a1, a2); }
instruction instruction::FLOAT(const std::string &a1, const std::string &a2) { return instruction(_FLOAT, a1, a2); }
instruction instruction::LOAD(const std::string &a1, const std::string &a2) { return instruction(_LOAD, a1, a2); }
instruction instruction::ILOAD(const std::string &a1, const std::string &a2) { return instruction(_ILOAD, a1, a2); }
instruction instruction::CHLOAD(const std::string &a1, const std::string &a2) { return instruction(_CHLOAD, a1, a2); }
instruction instruction::FLOAD(const std::string &a1, const std::string &a2) { return instruction(_FLOAD, a1, a2); }
instruction instruction::XLOAD(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_XLOAD, a1, a2, a3); }
instruction instruction::LOADX(const std::string &a1, const std::string &a2, const std::string &a3) { return instruction(_LOADX, a1, a2, a3); }
instruction instruction::ALOAD(const std::string &a1, const std::string &a2) { return instruction(_ALOAD, a1, a2); }
instruction instruction::LOADC(const std::string &a1, const std::string &a2) { return instruction(_LOADC, a1, a2); }
instruction instruction::CLOAD(const std::string &a1, const std::string &a2) { return instruction(_CLOAD, a1, a2); }
instruction instruction::READI(const std::string &a1) { return instruction(_READI, a1); }
instruction instruction::READF(const std::string &a1) { return instruction(_READF, a1); }
instruction instruction::READC(const std::string &a1) { return instruction(_READC, a1); }
instruction instruction::WRITEI(const std::string &a1) { return instruction(_WRITEI, a1); }
instruction instruction::WRITEF(const std::string &a1) { return instruction(_WRITEF, a1); }
instruction instruction::WRITEC(const std::string &a1) { return instruction(_WRITEC, a1); }
instruction instruction::WRITES(const std::string &a1) { return instruction(_WRITES, a1); }
instruction instruction::WRITELN() { return instruction(_WRITELN); }
instruction instruction::NOOP() { return instruction(_NOOP); }

/// Destructor
instruction::~instruction() {}

string instruction::dump() const
{
    string s;
    string ind = "   ";
    switch (oper)
    {
    case instruction::_LABEL:
    {
        s = "label " + arg1 + " :";
        ind = "";
        break;
    }
    case instruction::_UJUMP:
    {
        s = "goto " + arg1;
        break;
    }
    case instruction::_FJUMP:
    {
        s = "ifFalse " + arg1 + " goto " + arg2;
        break;
    }
    case instruction::_HALT:
    {
        s = "halt \"" + arg1 + "\"";
        break;
    }
    case instruction::_LOAD:
    case instruction::_FLOAD:
    case instruction::_ILOAD:
    {
        s = arg1 + " = " + arg2;
        break;
    }
    case instruction::_CHLOAD:
    {
        s = arg1 + " = '" + arg2 + "'";
        break;
    }
    case instruction::_PUSH:
    {
        s = "pushparam " + (arg1.empty() ? "" : arg1);
        break;
    }
    case instruction::_POP:
    {
        s = "popparam " + (arg1.empty() ? "" : arg1);
        break;
    }
    case instruction::_CALL:
    {
        s = "call " + arg1;
        break;
    }
    case instruction::_RETURN:
    {
        s = "return";
        break;
    }
    case instruction::_XLOAD:
    {
        s = arg1 + "[" + arg2 + "] = " + arg3;
        break;
    }
    case instruction::_LOADX:
    {
        s = arg1 + " = " + arg2 + "[" + arg3 + "]";
        break;
    }
    case instruction::_ALOAD:
    {
        s = arg1 + " = &" + arg2;
        break;
    }
    case instruction::_LOADC:
    {
        s = arg1 + " = *" + arg2;
        break;
    }
    case instruction::_CLOAD:
    {
        s = "*" + arg1 + " = " + arg2;
        break;
    }
    case instruction::_READI:
    {
        s = "readi " + arg1;
        break;
    }
    case instruction::_READF:
    {
        s = "readf " + arg1;
        break;
    }
    case instruction::_READC:
    {
        s = "readc " + arg1;
        break;
    }
    case instruction::_WRITEI:
    {
        s = "writei " + arg1;
        break;
    }
    case instruction::_WRITEF:
    {
        s = "writef " + arg1;
        break;
    }
    case instruction::_WRITEC:
    {
        s = "writec " + arg1;
        break;
    }
    case instruction::_WRITES:
    {
        s = "writes " + arg1;
        break;
    }
    case instruction::_WRITELN:
    {
        s = "writeln";
        break;
    }
    case instruction::_ADD:
    {
        s = arg1 + " = " + arg2 + " + " + arg3;
        break;
    }
    case instruction::_SUB:
    {
        s = arg1 + " = " + arg2 + " - " + arg3;
        break;
    }
    case instruction::_MUL:
    {
        s = arg1 + " = " + arg2 + " * " + arg3;
        break;
    }
    case instruction::_DIV:
    {
        s = arg1 + " = " + arg2 + " / " + arg3;
        break;
    }
    case instruction::_AND:
    {
        s = arg1 + " = " + arg2 + " and " + arg3;
        break;
    }
    case instruction::_OR:
    {
        s = arg1 + " = " + arg2 + " or " + arg3;
        break;
    }
    case instruction::_EQ:
    {
        s = arg1 + " = " + arg2 + " == " + arg3;
        break;
    }
    case instruction::_LT:
    {
        s = arg1 + " = " + arg2 + " < " + arg3;
        break;
    }
    case instruction::_LE:
    {
        s = arg1 + " = " + arg2 + " <= " + arg3;
        break;
    }
    case instruction::_NOT:
    {
        s = arg1 + " = not " + arg2;
        break;
    }
    case instruction::_NEG:
    {
        s = arg1 + " = - " + arg2;
        break;
    }
    case instruction::_FADD:
    {
        s = arg1 + " = " + arg2 + " +. " + arg3;
        break;
    }
    case instruction::_FSUB:
    {
        s = arg1 + " = " + arg2 + " -. " + arg3;
        break;
    }
    case instruction::_FMUL:
    {
        s = arg1 + " = " + arg2 + " *. " + arg3;
        break;
    }
    case instruction::_FDIV:
    {
        s = arg1 + " = " + arg2 + " /. " + arg3;
        break;
    }
    case instruction::_FEQ:
    {
        s = arg1 + " = " + arg2 + " ==. " + arg3;
        break;
    }
    case instruction::_FLT:
    {
        s = arg1 + " = " + arg2 + " <. " + arg3;
        break;
    }
    case instruction::_FLE:
    {
        s = arg1 + " = " + arg2 + " <=. " + arg3;
        break;
    }
    case instruction::_FNEG:
    {
        s = arg1 + " = -. " + arg2;
        break;
    }
    case instruction::_FLOAT:
    {
        s = arg1 + " = float " + arg2;
        break;
    }
    case instruction::_NOOP:
    {
        s = "noop";
        break;
    }
    default:
    {
        s = "????";
        break;
    }
    }

    return ind + s;
}

////////////////////////////////////////////////////////////////////
// concatenation of instruction+list (or instruction+instruction, via automatic coertion)

instructionList instruction::operator||(const instructionList &lst) const
{
    return instructionList(*this) || lst;
}

////////////////////////////////////////////////////////////////////
/// Implementation for class 'instructionList'

// constructor
instructionList::instructionList() {}
// constructor from a single instruction
instructionList::instructionList(const instruction &inst) { this->push_back(inst); }
// destructor
instructionList::~instructionList() {}

// concatenation of lists (or list+instruction, via automatic coertion)
instructionList instructionList::operator||(const instructionList &lst) const
{
    instructionList newlist = (*this);
    newlist.insert(newlist.end(), lst.begin(), lst.end());
    return newlist;
}

// print instructionList (for debugging)
string instructionList::dump() const
{
    string s;
    for (auto i : *this)
        s += i.dump() + "\n";
    return s;
}

////////////////////////////////////////////////////////////////////
/// Implementation for class 'var'

/// constructor
var::var(const std::string &n, const std::string &t, size_t ne)
{
    name = n;
    type = t;
    nelem = ne;
}

/// destructor
var::~var() {}

/// print (for debugging)
string var::dump() const
{

    if (nelem == 0) // if it is a parameter, name and type (unless LLVM wants it differnt)
        return name + " " + type;
    else
    {
        // local var: name + type (plus size for arrays)
        string s = name + " " + type;
        if (nelem > 1)
            s += " " + std::to_string(nelem);
        return s;
    }
}

////////////////////////////////////////////////////////////////////
/// Implementation for class 'subroutine'

/// constructor
subroutine::subroutine(const string &sname) { name = sname; }
/// destructor
subroutine::~subroutine() {}
/// get subroutine name
string subroutine::get_name() const { return name; };
/// add new variable
void subroutine::add_var(const var &v) { vars.push_back(v); }
/// add new variable
void subroutine::add_var(const std::string &name, const std::string &type, size_t sz) { vars.push_back(var(name, type, sz)); }
/// add new parameter
void subroutine::add_param(const std::string &name, const std::string &type, bool isarray)
{
    std::string t1 = (not isarray ? type : type + " array");
    params.push_back(var(name, t1, 0));
}
/// add new instruction
void subroutine::add_instruction(const instruction &inst)
{
    if (inst.oper == instruction::_LABEL)
        labels.insert(make_pair(inst.arg1, instructions.size()));
    instructions.push_back(inst);
}
/// add instruction list to current instructions
void subroutine::add_instructions(const instructionList &lins)
{
    for (auto i : lins)
        this->add_instruction(i);
}
/// set instruction list (overwritting current instructions)
void subroutine::set_instructions(const instructionList &lins)
{
    instructions.clear();
    this->add_instructions(lins);
}
/// get instruction at given program counter
instruction subroutine::get_instruction_at(size_t pc) const
{
    if (pc >= instructions.size())
        return instruction(instruction::_INVALID);
    return instructions[pc];
}
/// get program counter for given label
size_t subroutine::get_label_pc(std::string &lab) const { return labels.find(lab)->second; }
/// get the list of instructions (needed only in LLVMCodeGen)
instructionList subroutine::get_instructions() const
{
    return instructions;
}
/// print (for debugging)
string subroutine::dump() const
{
    string s;
    s = "function " + name + "\n";
    if (not params.empty())
    {
        s += "  params\n";
        for (auto p : params)
            s += "    " + p.dump() + "\n";
        s += "  endparams\n\n";
    }
    if (not vars.empty())
    {
        s += "  vars\n";
        for (auto v : vars)
            s += "    " + v.dump() + "\n";
        s += "  endvars\n\n";
    }

    string ind = "  ";
    if (labels.empty())
        ind = "";
    for (auto i : instructions)
        s += ind + i.dump() + "\n";
    s += "endfunction\n\n";
    return s;
}

////////////////////////////////////////////////////////////////////
/// Implementation for class 'code'

// Error codes for "HALT" instruction
const string code::INDEX_OUT_OF_RANGE = "Container index out of range.";
const string code::INVALID_INTEGER_OPERAND = "Invalid integer value in math operation.";
const string code::INVALID_FLOAT_OPERAND = "Invalid float value in math operation.";

/// constructor
code::code() {};
/// destructor
code::~code() {};

/// get most recently added subroutine
subroutine &code::get_last_subroutine() { return subs[subs.size() - 1]; }
/// get subroutine by name
const subroutine &code::get_subroutine(const string &name) const
{
    size_t p = names.find(name)->second;
    return subs[p];
}
/// add subroutine
void code::add_subroutine(const subroutine &s)
{
    subs.push_back(s);
    names.insert(make_pair(s.get_name(), subs.size() - 1));
}
/// get the list of subroutine's (needed only in LLVMCodeGen)
const std::vector<subroutine> &code::get_subroutine_list() const
{
    return subs;
}
/// print (for debugging)
string code::dump() const
{
    string c;
    for (auto s : subs)
        c += s.dump();
    return c;
}
/// print the code in LLVM IR
std::string code::dumpLLVM(const TypesMgr &Types, const SymTable &Symbols) const
{
    LLVMCodeGen llvmCode(Types, Symbols, *this);
    std::string llvmStr = llvmCode.dumpLLVM();
    return llvmStr;
}

////////////////////////////////////////////////////////////////////
/// Static methods to manage counters
int counters::countIF = 0;
int counters::countWHILE = 0;
int counters::countTEMP = 0;

string counters::newLabelIF() { return std::to_string(++countIF); }
string counters::newLabelWHILE() { return std::to_string(++countWHILE); }
string counters::newTEMP() { return std::to_string(++countTEMP); }

void counters::resetLabelIF() { countIF = 0; }
void counters::resetLabelWHILE() { countWHILE = 0; }
void counters::resetTEMP() { countTEMP = 0; }

void counters::resetLabels()
{
    resetLabelIF();
    resetLabelWHILE();
}
void counters::reset()
{
    resetLabels();
    resetTEMP();
}
```


#### common/code.h

```cpp
/////////////////////////////////////////////////////////////////
//
//    TVM - t-Code Virtual Machine
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: Lluis Padro (padro@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.320 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include <map>
#include <list>
#include <vector>
#include "TypesMgr.h"
#include "SymTable.h"

/// predeclaration
class instructionList;
class LLVMCodeGen;

////////////////////////////////////////////////////////////////////
/// Class instruction stores a VM instruction code with its operands

class instruction
{
public:
    /// instruction codes
    typedef enum
    {
        _LABEL,
        _UJUMP,
        _FJUMP,
        _HALT,
        _PUSH,
        _POP,
        _CALL,
        _RETURN,
        _ADD,
        _SUB,
        _MUL,
        _DIV,
        _EQ,
        _LT,
        _LE,
        _NEG,
        _NOT,
        _AND,
        _OR,
        _FLOAT,
        _FADD,
        _FSUB,
        _FMUL,
        _FDIV,
        _FEQ,
        _FLT,
        _FLE,
        _FNEG,
        _LOAD,
        _ILOAD,
        _CHLOAD,
        _FLOAD,
        _XLOAD,
        _LOADX,
        _ALOAD,
        _LOADC,
        _CLOAD,
        _READI,
        _READF,
        _READC,
        _WRITEI,
        _WRITEF,
        _WRITEC,
        _WRITES,
        _WRITELN,
        _NOOP,
        _INVALID
    } Operation;

    /// instruction code
    Operation oper;
    /// arguments
    std::string arg1, arg2, arg3;

    /// constructor
    instruction(Operation op,
                const std::string &a1 = "", const std::string &a2 = "", const std::string &a3 = "");

    /// destructor
    ~instruction();

    // concatenation of instruction+list (or instruction+instruction, via automatic coertion)
    instructionList operator||(const instructionList &lst) const;

    /// ------ specific constructors for each instruction -------

    // create new instruction "a1 :"
    static instruction LABEL(const std::string &a1);
    // create new instruction "goto a1"
    static instruction UJUMP(const std::string &a1);
    // create new instruction "ifFalse a1 goto a2"
    static instruction FJUMP(const std::string &a1, const std::string &a2);
    // create new instruction "halt"
    static instruction HALT(const std::string &a1 = "");
    // create new instruction "pushparam a1"
    static instruction PUSH(const std::string &a1 = "");
    // create new instruction "popparam a1"
    static instruction POP(const std::string &a1 = "");
    // create new instruction "call a1"
    static instruction CALL(const std::string &a1);
    // create new instruction "return"
    static instruction RETURN();
    // create new instruction "a1 = a2 + a3"
    static instruction ADD(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 - a3"
    static instruction SUB(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 * a3"
    static instruction MUL(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 / a3"
    static instruction DIV(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 == a3"
    static instruction EQ(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 < a3"
    static instruction LT(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 <= a3"
    static instruction LE(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 and a3"
    static instruction AND(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 or a3"
    static instruction OR(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 +. a3"
    static instruction FADD(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 -. a3"
    static instruction FSUB(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 *. a3"
    static instruction FMUL(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 /. a3"
    static instruction FDIV(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 ==. a3"
    static instruction FEQ(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 <. a3"
    static instruction FLT(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2 <=. a3"
    static instruction FLE(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = not a2"
    static instruction NOT(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = - a2"
    static instruction NEG(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = -. a2"
    static instruction FNEG(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = float a2"
    static instruction FLOAT(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = a2"
    static instruction LOAD(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = a2" (where a2 is an integer constant)
    static instruction ILOAD(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = a2" (where a2 is a character constant)
    static instruction CHLOAD(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = a2" (where a2 is a float constant)
    static instruction FLOAD(const std::string &a1, const std::string &a2);
    // create new instruction "a1[a2] = a3"
    static instruction XLOAD(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = a2[a3]"
    static instruction LOADX(const std::string &a1, const std::string &a2, const std::string &a3);
    // create new instruction "a1 = &a2"
    static instruction ALOAD(const std::string &a1, const std::string &a2);
    // create new instruction "a1 = *a2"
    static instruction LOADC(const std::string &a1, const std::string &a2);
    // create new instruction "*a1 = a2"
    static instruction CLOAD(const std::string &a1, const std::string &a2);
    // create new instruction "readi a1"
    static instruction READI(const std::string &a1);
    // create new instruction "readf a1"
    static instruction READF(const std::string &a1);
    // create new instruction "readc a1"
    static instruction READC(const std::string &a1);
    // create new instruction "writei a1"
    static instruction WRITEI(const std::string &a1);
    // create new instruction "writef a1"
    static instruction WRITEF(const std::string &a1);
    // create new instruction "writec a1"
    static instruction WRITEC(const std::string &a1);
    // create new instruction "writes 'string constant'"
    static instruction WRITES(const std::string &a1);
    // create new instruction "writeln"
    static instruction WRITELN();
    // create new instruction "noop" (not really needed)
    static instruction NOOP();

    // print instruction
    std::string dump() const;
};

////////////////////////////////////////////////////////////////////
/// Class instructionList stores a list of instructions

class instructionList : public std::vector<instruction>
{
public:
    // constructor
    instructionList();
    // constructor from a single instruction
    instructionList(const instruction &);
    // destructor
    ~instructionList();

    // concatenation of lists (or list+instruction, via automatic coertion)
    instructionList operator||(const instructionList &lst) const;

    // print instructionList
    std::string dump() const;
};

////////////////////////////////////////////////////////////////////
/// Class var stores a variable name and size

class var
{
public:
    std::string name;
    std::string type;
    size_t nelem;

    var(const std::string &name, const std::string &type, size_t nelem = 1);
    ~var();

    // print var
    std::string dump() const;
};

////////////////////////////////////////////////////////////////////
/// Class subroutine stores information about a subroutine (local
/// vars, parametres, instructions, declared/used labels...)

class subroutine
{
private:
    /// name of the subroutine
    std::string name;
    /// instructions
    instructionList instructions;
    /// map label name -> position in instructions
    std::map<std::string, size_t> labels;

public:
    /// list of local variables
    std::list<var> vars;
    /// list of params
    std::list<var> params;

    /// constructor and destructor
    subroutine(const std::string &sname);
    ~subroutine();

    /// get subroutine name
    std::string get_name() const;
    /// add a local var to subroutine
    void add_var(const var &v);
    /// add a local var to subroutine
    void add_var(const std::string &name, const std::string &type, size_t numelem = 1);
    /// add a parameter (size is always 1, since arrays are references)
    void add_param(const std::string &name, const std::string &type, bool isarray = false);
    /// add an instruction
    void add_instruction(const instruction &inst);
    /// add instruction list to current instructions
    void add_instructions(const instructionList &lins);
    /// set instruction list (overwritting current instructions)
    void set_instructions(const instructionList &lins);

    /// get instruction at given program counter in subroutine
    instruction get_instruction_at(size_t pc) const;
    /// get program counter in subroutine for given label
    size_t get_label_pc(std::string &lab) const;
    /// get the list of instructions (needed only in LLVMCodeGen)
    instructionList get_instructions() const;

    // print subroutine (params, vars, and instructions)
    std::string dump() const;
};

////////////////////////////////////////////////////////////////////
/// Class code stores a whole program (main plus subroutines)

class code
{
private:
    /// subroutines (including main progam)
    std::vector<subroutine> subs;
    /// index to access subroutines by name
    std::map<std::string, size_t> names;

public:
    /// constructor and destructor
    code();
    ~code();

    /// get most recently added subroutine (i.e. the one currently being processed)
    subroutine &get_last_subroutine();
    /// get subroutine by name
    const subroutine &get_subroutine(const std::string &name) const;
    /// add new subroutine
    void add_subroutine(const subroutine &s);
    /// get the list of subroutines (needed only in LLVMCodeGen)
    const std::vector<subroutine> &get_subroutine_list() const;

    // print code (all info for all subroutines)
    std::string dump() const;
    /// print the code in LLVM IR
    std::string dumpLLVM(const TypesMgr &Types, const SymTable &Symbols) const;

    // Error codes for "HALT" instruction
    static const std::string INDEX_OUT_OF_RANGE;
    static const std::string INVALID_INTEGER_OPERAND;
    static const std::string INVALID_FLOAT_OPERAND;
};

////////////////////////////////////////////////////////////////////
/// Class counters manages temporal and labels counters

class counters
{
private:
    static int countIF;
    static int countWHILE;
    static int countTEMP;

public:
    // return id for new label or temp (id is a number, but returned as string
    // to ease concatenation with other literals (e.g. "labelIF" + "4" -> "LabelIF4")
    static std::string newLabelIF();
    static std::string newLabelWHILE();
    static std::string newTEMP();

    // reset individual counters
    static void resetLabelIF();
    static void resetLabelWHILE();
    static void resetTEMP();

    // reset label counters (IF and WHILE)
    static void resetLabels();
    // reset all counters (IF, WHILE, and TEMP)
    static void reset();
};
```


#### common/debug.h

```cpp
//////////////////////////////////////////////////////////////////////
//
//    debug - define some optional macros useful in debugging
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"

#include <iostream>
#include <string>

// using namespace std;

//////////////////////////////////////////////////////////////////////
// This file contains 3 DEBUG macros to be used in the visitors:
//   DEBUG(x)          : with a 'message' x (to use anywhere):
//                       DEBUG("a:" << a << " b:" << b);
//   DEBUG_ENTER()     : for the enter message in a rule method, and
//   DEBUG_EXIT()      : for the exit message in a rule method
//
// These messages can be enabled in a specific module/visitor
// defining the variable DEBUG_BUILD *before* the inclusion
// of this file

#ifdef DEBUG_BUILD
static int _i_ = 0;
static int _delta_i_ = 2;
std::string _incr_indent_()
{
    std::string s = std::string(_i_, ' ');
    _i_ += _delta_i_;
    return s;
}
std::string _decr_indent_()
{
    _i_ -= _delta_i_;
    std::string s = std::string(_i_, ' ');
    return s;
}
#define DEBUG(x)                     \
    do                               \
    {                                \
        std::cout << x << std::endl; \
    } while (0)
#define DEBUG_ENTER() DEBUG(_incr_indent_() << ">>> enter " << std::string(__func__).substr(5) << " [source pos " << ctx->getStart()->getLine() << ":" << ctx->getStart()->getCharPositionInLine() << "] [module: " << std::string(typeid(*this).name()).substr(2, std::string(typeid(*this).name()).find("Visitor") - 2) << "]")
#define DEBUG_EXIT() DEBUG(_decr_indent_() << ">>> exit " << std::string(__func__).substr(5) << " [source pos " << ctx->getStart()->getLine() << ":" << ctx->getStart()->getCharPositionInLine() << "] [module: " << std::string(typeid(*this).name()).substr(2, std::string(typeid(*this).name()).find("Visitor") - 2) << "]")
#else
#define DEBUG(x)
#define DEBUG_ENTER()
#define DEBUG_EXIT()
#endif
```


#### common/LLVMCodeGen.cpp


```cpp
/////////////////////////////////////////////////////////////////
//
//    LLVMCodeGen - LLVM IR generation for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include "LLVMCodeGen.h"
#include "SymTable.h"
#include "TypesMgr.h"
#include "code.h"

#include <string>
#include <cctype>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <algorithm> // find

// using namespace std;

const bool LLVMCodeGen::COMMENTS_ENABLED = false;

const std::string LLVMCodeGen::INDENT_INSTR = "    ";
const std::string LLVMCodeGen::INDENT_LABEL = "  ";

const std::string LLVMCodeGen::LLVM_INT = "i32";
const std::string LLVMCodeGen::LLVM_FLOAT = "float";
const std::string LLVMCodeGen::LLVM_CHAR = "i8";
const std::string LLVMCodeGen::LLVM_BOOL = "i1";
const std::string LLVMCodeGen::LLVM_VOID = "void";
const std::string LLVMCodeGen::LLVM_LABEL = "label";
const std::string LLVMCodeGen::LLVM_TYERR = "tErr";
const std::string LLVMCodeGen::LLVM_TYMISS = "tMiss";
const std::string LLVMCodeGen::LLVM_INT_BOOL = "tIntBool";

const std::string LLVMCodeGen::LLVM_INT_PTR = "i32*";
const std::string LLVMCodeGen::LLVM_FLOAT_PTR = "float*";
const std::string LLVMCodeGen::LLVM_CHAR_PTR = "i8*";
const std::string LLVMCodeGen::LLVM_BOOL_PTR = "i1*";

const std::string LLVMCodeGen::LLVM_INT1 = "i1";
const std::string LLVMCodeGen::LLVM_INT8 = "i8";
const std::string LLVMCodeGen::LLVM_INT32 = "i32";
const std::string LLVMCodeGen::LLVM_INT64 = "i64";
const std::string LLVMCodeGen::LLVM_DOUBLE = "double";

const std::string LLVMCodeGen::LLVM_GLOBAL_INT_ADDR = "@.global.i.addr";
const std::string LLVMCodeGen::LLVM_GLOBAL_FLOAT_ADDR = "@.global.f.addr";
const std::string LLVMCodeGen::LLVM_GLOBAL_CHAR_ADDR = "@.global.c.addr";

const std::string LLVMCodeGen::LLVM_ZERO_INT = "0";
const std::string LLVMCodeGen::LLVM_ZERO_FLOAT = "0.0";
const std::string LLVMCodeGen::LLVM_ONE_INT = "1";

const std::string LLVMCodeGen::LLVM_ENTRY = ".entry";

const std::string LLVMCodeGen::LLVM_ZEXT = "zext";
const std::string LLVMCodeGen::LLVM_FPEXT = "fpext";
const std::string LLVMCodeGen::LLVM_TRUNC = "trunc";
const std::string LLVMCodeGen::LLVM_FPTRUNC = "fptrunc";
const std::string LLVMCodeGen::LLVM_SEXT = "sext";

const std::map<instruction::Operation, std::string> LLVMCodeGen::tcode2llvmInstrMap = {
    {instruction::_ADD, "add"},
    {instruction::_SUB, "sub"},
    {instruction::_MUL, "mul"},
    {instruction::_DIV, "sdiv"},
    {instruction::_FADD, "fadd"},
    {instruction::_FSUB, "fsub"},
    {instruction::_FMUL, "fmul"},
    {instruction::_FDIV, "fdiv"},
    {instruction::_EQ, "icmp eq"},
    {instruction::_LT, "icmp slt"},
    {instruction::_LE, "icmp sle"},
    {instruction::_FEQ, "fcmp oeq"},
    {instruction::_FLT, "fcmp olt"},
    {instruction::_FLE, "fcmp ole"},
    {instruction::_AND, "and"},
    {instruction::_OR, "or"},
};

LLVMCodeGen::LLVMCodeGen(const TypesMgr &Types, const SymTable &Symbols, const code &tCode)
    : Types{Types}, Symbols{Symbols}, tCode{tCode},
      writeI(false), writeF(false), writeC(false), writeLN(false),
      readI(false), readF(false), readC(false),
      haltAndExit(false),
      globalI(false), globalF(false), globalC(false)
{
    std::string failFunc, failTempVar;
    check_SSA_tCode(failFunc, failTempVar);
    if (failFunc != "")
    {
        std::cerr << std::endl;
        std::cerr << ";;; *****************************************************************************" << std::endl;
        std::cerr << ";;; WARNING: in order to generate LLVM code, this emitter impose the following" << std::endl;
        std::cerr << ";;;          restriction: the temporal variables in the t-code cannot be multiply" << std::endl;
        std::cerr << ";;;          defined inside a function." << std::endl;
        std::cerr << ";;;          For example, this happens in function '";
        std::cerr << failFunc << "' with temporal '" << failTempVar << "'" << std::endl;
        std::cerr << ";;; *****************************************************************************" << std::endl;
        std::cerr << std::endl;
        std::exit(EXIT_SUCCESS);
    }
}

void LLVMCodeGen::check_SSA_tCode(std::string &failFunc, std::string &failTempVar) const
{
    failFunc = "";
    failTempVar = "";
    for (auto &subr : tCode.get_subroutine_list())
    {
        std::map<std::string, int> modTempCounts;
        for (auto &instr : subr.get_instructions())
        {
            switch (instr.oper)
            {
            case instruction::_LABEL:
            case instruction::_UJUMP:
            case instruction::_FJUMP:
            case instruction::_HALT:
            case instruction::_PUSH:
            case instruction::_RETURN:
            case instruction::_XLOAD:
            case instruction::_CLOAD:
            case instruction::_WRITEI:
            case instruction::_WRITEF:
            case instruction::_WRITEC:
            case instruction::_WRITES:
            case instruction::_WRITELN:
            case instruction::_NOOP:
            case instruction::_INVALID:
                break;
            default: // Except in instruction::_POP, where is optional (arg1 may be ""),
                     // the argument arg1 always does exist.
                std::string arg1 = getTCodeArg(instr, 1);
                if (isTCodeTemporal(arg1))
                {
                    modTempCounts[arg1] += 1;
                }
                break;
            }
        }
        for (auto &pair : modTempCounts)
        {
            if (pair.second > 1)
            {
                failFunc = subr.get_name();
                failTempVar = pair.first;
                return;
            }
        }
    }
}

bool LLVMCodeGen::isTCodeTemporal(const std::string &tcodeArg) const
{
    if (tcodeArg.size() < 2)
        return false;
    if (tcodeArg[0] != '%')
        return false;
    if (not std::isdigit(tcodeArg[1]))
        return false;
    return true;
}

bool LLVMCodeGen::isTCodeIdentifier(const std::string &tcodeArg) const
{
    // IMPORTANT:
    // tcodeArg can not be the arg2 argument of a CHLOAD instruction:
    // %7 = 'a' where oper = _CHLOAD, arg1 = "%7", arg2 = "a"
    if (tcodeArg.size() < 1)
        return false;
    if (tcodeArg[0] == '%')
        return false;
    if (std::isdigit(tcodeArg[0]))
        return false;
    return true;
}

void LLVMCodeGen::computeReadWriteHaltInfo()
{
    for (auto &subr : tCode.get_subroutine_list())
    {
        for (auto &instr : subr.get_instructions())
        {
            std::string arg1 = getTCodeArg(instr, 1);
            std::string arg2 = getTCodeArg(instr, 2);
            std::string arg3 = getTCodeArg(instr, 3);
            switch (instr.oper)
            {
            case instruction::_WRITEI:
                writeI = true;
                break;
            case instruction::_WRITEF:
                writeF = true;
                break;
            case instruction::_WRITEC:
                writeC = true;
                break;
            case instruction::_WRITES:
                if (std::find(writeSAslStrVec.begin(), writeSAslStrVec.end(), arg1) == writeSAslStrVec.end())
                {
                    writeSAslStrVec.push_back(arg1);
                }
                writeS = true;
                break;
            case instruction::_WRITELN:
                writeLN = true;
                break;
            case instruction::_READI:
                readI = true;
                if (isTCodeTemporal(arg1))
                    globalI = true;
                break;
            case instruction::_READF:
                readF = true;
                if (isTCodeTemporal(arg1))
                    globalF = true;
                break;
            case instruction::_READC:
                readC = true;
                if (isTCodeTemporal(arg1))
                    globalC = true;
                break;
            case instruction::_HALT:
                haltAndExit = true;
                break;
            default:
                break;
            }
        }
    }
}

void LLVMCodeGen::startNewFunction(const subroutine &subr)
{
    currentFunctionName = subr.get_name();
    isMain = (currentFunctionName == "main");
    prevInstrIsTerminator = false;
}

void LLVMCodeGen::bindTCodeLocalSymbolsToLLVMTypes(const subroutine &subr)
{
    llvmLocalValueVec.clear();
    llvmLocalValueTypeMap.clear();
    llvmLocalValueCountMap.clear();
    std::string funcName = subr.get_name();
    for (auto param : subr.params)
    {
        std::string llvmType;
        if (param.name == "_result")
            llvmType = getFuncReturnLLVMType(funcName);
        else
            llvmType = getLocalSymbolLLVMType(funcName, param.name, true);
        bindTCodeLocalValueWithType(param.name, llvmType);
    }
    for (auto varlocal : subr.vars)
    {
        std::string llvmType = getLocalSymbolLLVMType(funcName, varlocal.name);
        bindTCodeLocalValueWithType(varlocal.name, llvmType);
    }
    for (auto instr : subr.get_instructions())
    {
        std::string arg1 = getTCodeArg(instr, 1);
        std::string arg2 = getTCodeArg(instr, 2);
        std::string arg3 = getTCodeArg(instr, 3);
        switch (instr.oper)
        {
        case instruction::_LABEL:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_LABEL);
            break;
        }
        case instruction::_UJUMP:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_LABEL);
            break;
        }
        case instruction::_FJUMP:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_BOOL);
            bindTCodeLocalValueWithType(arg2, LLVM_LABEL);
            break;
        }
        case instruction::_HALT:
        {
            break;
        }
        case instruction::_LOAD:
        {
            if (isTCodeIdentifier(arg1) and isTCodeTemporal(arg2))
            { //  a = %4
                std::string llvmValue1 = getLLVMValue(arg1);
                std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
                bindTCodeLocalValueWithType(arg2, llvmType1);
            }
            else if (isTCodeTemporal(arg1) and isTCodeIdentifier(arg2))
            { // %4 = a
                std::string llvmValue2 = getLLVMValue(arg2);
                std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
                bindTCodeLocalValueWithType(arg1, llvmType2);
            }
            else if (isTCodeTemporal(arg1) and isTCodeTemporal(arg2))
            { // %4 = %6
                std::string llvmValue2 = getLLVMValue(arg2);
                std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
                bindTCodeLocalValueWithType(arg1, llvmType2);
            }
            break;
        }
        case instruction::_ILOAD:
        {
            int n = std::stoi(arg2);
            if (n != 0 and n != 1)
                bindTCodeLocalValueWithType(arg1, LLVM_INT);
            else
                bindTCodeLocalValueWithType(arg1, LLVM_INT_BOOL);
            break;
        }
        case instruction::_FLOAD:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            break;
        }
        case instruction::_CHLOAD:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_CHAR);
            break;
        }
        case instruction::_PUSH:
        {
            if (arg1 != "")
            {
                bindTCodeLocalValueWithType(arg1, LLVM_TYMISS);
                pushTCodeParamCallStack(arg1);
            }
            break;
        }
        case instruction::_POP:
        {
            if (arg1 != "")
                bindTCodeLocalValueWithType(arg1, pendingCallLLVMRetType);
            break;
        }
        case instruction::_CALL:
        {
            std::vector<std::string> llvmParamTypes = getFuncParamsLLVMTypes(arg1);
            int nParams = getFuncNumberOfParams(arg1);
            for (int i = nParams - 1; i >= 0; --i)
            {
                std::string tcodeParam = topPopTCodeParamCallStack();
                std::string llvmParamType = llvmParamTypes[i];
                bindTCodeLocalValueWithType(tcodeParam, llvmParamType);
            }
            std::string retType = getFuncReturnLLVMType(arg1);
            if (retType != "void")
                pendingCallLLVMRetType = retType;
            break;
        }
        case instruction::_RETURN:
        {
            break;
        }
        case instruction::_ALOAD:
        {
            std::string llvmValue2 = getLLVMValue(arg2);
            std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
            std::string llvmType2Ptr;
            if (isLLVMArrayType(llvmType2))
                llvmType2Ptr = getLLVMArrayTypeAsPointerType(llvmType2);
            else
                llvmType2Ptr = llvmType2; // getPointerToType(llvmType2);
            bindTCodeLocalValueWithType(arg1, llvmType2Ptr);
            break;
        }
        case instruction::_XLOAD:
        {
            std::string llvmValue1 = getLLVMValue(arg1);
            std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
            std::string llvmElemType;
            if (isLLVMArrayType(llvmType1))
                llvmElemType = getLLVMElementOfArrayType(llvmType1);
            else if (isPointerType(llvmType1))
                llvmElemType = getPointedType(llvmType1);
            else
                llvmElemType = LLVM_TYERR;
            bindTCodeLocalValueWithType(arg2, LLVM_INT);
            bindTCodeLocalValueWithType(arg3, llvmElemType);
            break;
        }
        case instruction::_LOADX:
        {
            std::string llvmValue2 = getLLVMValue(arg2);
            std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
            std::string llvmElemType;
            if (isLLVMArrayType(llvmType2))
                llvmElemType = getLLVMElementOfArrayType(llvmType2);
            else if (isPointerType(llvmType2))
                llvmElemType = getPointedType(llvmType2);
            else
                llvmElemType = LLVM_TYERR;
            bindTCodeLocalValueWithType(arg1, llvmElemType);
            bindTCodeLocalValueWithType(arg3, LLVM_INT);
            break;
        }
        case instruction::_LOADC:
        {
            // only: address ASSIG MUL TEMP   (x = *t1)
            std::string llvmValue1 = getLLVMValue(arg1);
            std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
            std::string llvmTypePtr = getPointerToType(llvmType1);
            bindTCodeLocalValueWithType(arg2, llvmTypePtr);
            break;
        }
        case instruction::_CLOAD:
        {
            // only: MUL TEMP ASSIG address   (*t1 = x)
            std::string llvmValue2 = getLLVMValue(arg2);
            std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
            std::string llvmTypePtr = getPointerToType(llvmType2);
            bindTCodeLocalValueWithType(arg1, llvmTypePtr);
            break;
        }
        case instruction::_WRITEI:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_INT_BOOL);
            break;
        }
        case instruction::_WRITEF:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            break;
        }
        case instruction::_WRITEC:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_CHAR);
            break;
        }
        case instruction::_WRITES:
        {
            break;
        }
        case instruction::_WRITELN:
        {
            break;
        }
        case instruction::_READI:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_INT_BOOL);
            break;
        }
        case instruction::_READF:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            break;
        }
        case instruction::_READC:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_CHAR);
            break;
        }
        case instruction::_ADD:
        case instruction::_SUB:
        case instruction::_MUL:
        case instruction::_DIV:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_INT);
            bindTCodeLocalValueWithType(arg2, LLVM_INT);
            bindTCodeLocalValueWithType(arg3, LLVM_INT);
            break;
        }
        case instruction::_EQ:
        case instruction::_LT:
        case instruction::_LE:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_BOOL);
            if (isTCodeIdentifier(arg2) and isTCodeTemporal(arg3))
            {
                std::string llvmValue2 = getLLVMValue(arg2);
                std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
                bindTCodeLocalValueWithType(arg3, llvmType2);
            }
            else if (isTCodeTemporal(arg2) and isTCodeIdentifier(arg3))
            {
                std::string llvmValue3 = getLLVMValue(arg3);
                std::string llvmType3 = getLLVMTypeOfValue(llvmValue3);
                bindTCodeLocalValueWithType(arg2, llvmType3);
            }
            else if (isTCodeTemporal(arg2) and isTCodeTemporal(arg3))
            {
                bindPairOfTCodeLocalValuesWithTypes(arg2, arg3);
            }
            break;
        }
        case instruction::_FEQ:
        case instruction::_FLT:
        case instruction::_FLE:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_BOOL);
            bindTCodeLocalValueWithType(arg2, LLVM_FLOAT);
            bindTCodeLocalValueWithType(arg3, LLVM_FLOAT);
            break;
        }
        case instruction::_NEG:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_INT);
            bindTCodeLocalValueWithType(arg2, LLVM_INT);
            break;
        }
        case instruction::_FADD:
        case instruction::_FSUB:
        case instruction::_FMUL:
        case instruction::_FDIV:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            bindTCodeLocalValueWithType(arg2, LLVM_FLOAT);
            bindTCodeLocalValueWithType(arg3, LLVM_FLOAT);
            break;
        }
        case instruction::_FNEG:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            bindTCodeLocalValueWithType(arg2, LLVM_FLOAT);
            break;
        }
        case instruction::_FLOAT:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_FLOAT);
            bindTCodeLocalValueWithType(arg2, LLVM_INT);
            break;
        }
        case instruction::_AND:
        case instruction::_OR:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_BOOL);
            bindTCodeLocalValueWithType(arg2, LLVM_BOOL);
            bindTCodeLocalValueWithType(arg3, LLVM_BOOL);
            break;
        }
        case instruction::_NOT:
        {
            bindTCodeLocalValueWithType(arg1, LLVM_BOOL);
            bindTCodeLocalValueWithType(arg2, LLVM_BOOL);
            break;
        }
        case instruction::_NOOP:
        {
            break;
        }
        default:
        {
            break;
        }
        }
    }
    bool errors = false;
    for (auto &llvmValue : llvmLocalValueVec)
    {
        std::string llvmType = llvmLocalValueTypeMap.at(llvmValue);
        if (llvmType == LLVM_TYERR or llvmType == LLVM_TYMISS)
        {
            errors = true;
            break;
        }
    }
    if (errors)
    {
        std::cerr << "ERROR: some local values of this function can not been binded to a valid type:" << std::endl;
        std::cerr << "++++++++++++++++++++++++++++++++ function: " << funcName << std::endl;
        for (auto &value : llvmLocalValueVec)
        {
            std::cerr << value << ": \t" << llvmLocalValueTypeMap.at(value) << std::endl;
        }
        std::cerr << "--------------------------------" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (auto &llvmValue : llvmLocalValueVec)
    {
        std::string llvmType = llvmLocalValueTypeMap.at(llvmValue);
        if (llvmType == LLVM_INT_BOOL)
            llvmLocalValueTypeMap[llvmValue] = LLVM_INT;
    }
}

std::string LLVMCodeGen::getFuncReturnLLVMType(const std::string &tcodeFuncIdent) const
{
    TypesMgr::TypeId tid = Symbols.getGlobalFunctionType(tcodeFuncIdent);
    TypesMgr::TypeId tr = Types.getFuncReturnType(tid);
    return TypeIdToLLVMType(tr);
}

int LLVMCodeGen::getFuncNumberOfParams(const std::string &tcodeFuncIdent) const
{
    TypesMgr::TypeId tid = Symbols.getGlobalFunctionType(tcodeFuncIdent);
    return Types.getNumOfParameters(tid);
}

std::string LLVMCodeGen::getFuncParamLLVMType(const std::string &tcodeFuncIdent, int i) const
{
    TypesMgr::TypeId tid = Symbols.getGlobalFunctionType(tcodeFuncIdent);
    TypesMgr::TypeId tParam = Types.getParameterType(tid, i);
    std::string llvmType = TypeIdToLLVMType(tParam, true);
    return llvmType;
}

std::vector<std::string> LLVMCodeGen::getFuncParamsLLVMTypes(const std::string &tcodeFuncIdent) const
{
    TypesMgr::TypeId tid = Symbols.getGlobalFunctionType(tcodeFuncIdent);
    std::size_t n = Types.getNumOfParameters(tid);
    std::vector<std::string> typesVec(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        TypesMgr::TypeId tParam = Types.getParameterType(tid, i);
        typesVec[i] = TypeIdToLLVMType(tParam, true);
    }
    return typesVec;
}

std::string LLVMCodeGen::getLocalSymbolLLVMType(const std::string &tcodeFuncIdent,
                                                const std::string &tcodeSymbolIdent,
                                                bool isParameter) const
{
    TypesMgr::TypeId tid = Symbols.getLocalSymbolType(tcodeFuncIdent, tcodeSymbolIdent);
    return TypeIdToLLVMType(tid, isParameter);
}

std::string LLVMCodeGen::TypeIdToLLVMType(TypesMgr::TypeId tid, bool isParameter) const
{
    if (Types.isIntegerTy(tid))
        return LLVM_INT;
    else if (Types.isFloatTy(tid))
        return LLVM_FLOAT;
    else if (Types.isBooleanTy(tid))
        return LLVM_BOOL;
    else if (Types.isCharacterTy(tid))
        return LLVM_CHAR;
    else if (Types.isVoidTy(tid))
        return LLVM_VOID;
    else if (Types.isArrayTy(tid))
    {
        TypesMgr::TypeId te = Types.getArrayElemType(tid);
        std::string teLLVM = TypeIdToLLVMType(te);
        if (not isParameter)
        {
            std::size_t n = Types.getArraySize(tid);
            return "[" + std::to_string(n) + " x " + teLLVM + "]";
        }
        else
        {
            return getPointerToType(teLLVM); // teLLVM + "*"
        }
    }
    return LLVM_TYERR;
}

void LLVMCodeGen::getLLVMStringFromAslString(const std::string &aslString,
                                             std::string &llvmString,
                                             std::string::size_type &llvmStringSize)
{
    llvmString = aslString.substr(1, aslString.size() - 2);
    llvmStringSize = llvmString.size();
    for (const auto &from_to : std::map<std::string, std::string>{{"\\n", "\\0A"}, {"\\t", "\\09"}, {"\\\\", "\\\\"}})
    {
        std::string from = from_to.first;
        std::string to = from_to.second;
        std::string::size_type pos = 0;
        while ((pos = llvmString.find(from, pos)) != std::string::npos)
        {
            llvmString.replace(pos, from.length(), to);
            llvmStringSize = llvmStringSize - from.size() + 1;
            pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    }
}

void LLVMCodeGen::generateReadWriteHaltBeginEndCode(std::string &begin, std::string &end)
{
    begin = end = "";
    computeReadWriteHaltInfo();
    if (writeI or writeF or writeC or writeS or writeLN or readI or readF or readC)
        begin += "\n";
    if (writeI or readI)
        begin += "@.str.i = constant [3 x i8] c\"%d\\00\"\n";
    if (writeF or readF)
        begin += "@.str.f = constant [3 x i8] c\"%g\\00\"\n";
    if (writeC or readC)
        begin += "@.str.c = constant [3 x i8] c\"%c\\00\"\n";
    std::string::size_type n = writeSAslStrVec.size();
    writeSLLVMStrSizeVec = std::vector<std::string::size_type>(n);
    for (std::string::size_type i = 0; i < n; ++i)
    {
        std::string llvmStr;
        std::string::size_type llvmStrSize;
        getLLVMStringFromAslString(writeSAslStrVec[i], llvmStr, llvmStrSize);
        begin += "@.str.s." + std::to_string(i + 1) + " = constant [" + std::to_string(llvmStrSize + 1) + " x i8] c\"" + llvmStr + "\\00\"\n";
        writeSLLVMStrSizeVec[i] = llvmStrSize + 1;
    }
    if (writeI or readI or writeF or readF or writeC or readC)
        begin += "\n\n";
    if (globalI)
        begin += "@.global.i.addr = common dso_local global i32 0\n";
    if (globalF)
        begin += "@.global.f.addr = common dso_local global float 0.000000e+00\n";
    if (globalC)
        begin += "@.global.c.addr = common dso_local global i8 0\n";
    if (writeI or readI or writeF or readF or writeC or readC)
        begin += "\n\n";
    if (writeI or writeF or writeC or writeLN or readI or readF or readC or haltAndExit)
        end += "\n";
    if (writeI or writeF or writeC or writeS or writeLN)
    {
        if (writeI or writeF or writeS)
            end += "declare dso_local i32 @printf(i8*, ...)\n";
        if (writeC or writeLN)
            end += "declare dso_local i32 @putchar(i32)\n";
    }
    if (readI or readF or readC)
    {
        end += "declare dso_local i32 @__isoc99_scanf(i8*, ...)\n";
    }
    if (haltAndExit)
    {
        end += "declare dso_local void @exit(i32) noreturn nounwind\n";
    }
    if (writeI or writeF or writeC or writeS or writeLN or readI or readF or readC or haltAndExit)
        end += "\n";
}

std::string LLVMCodeGen::dumpLLVM()
{
    std::string llvmCode, llvmBegin, llvmEnd;
    generateReadWriteHaltBeginEndCode(llvmBegin, llvmEnd);
    bindGlobalValuesWithTypes();
    for (auto &subr : tCode.get_subroutine_list())
    {
        bindTCodeLocalSymbolsToLLVMTypes(subr);
        startNewFunction(subr);
        llvmCode += dumpSubroutine(subr);
    }
    llvmCode = llvmBegin + llvmCode + llvmEnd;
    return llvmCode;
}

std::string LLVMCodeGen::dumpSubroutine(const subroutine &subr)
{
    std::string llvmCode;
    llvmCode += dumpHeader(subr);
    llvmCode += "{\n";
    llvmCode += llvmComment("   ENTRY label:");
    bindLLVMLocalValueWithType(LLVM_ENTRY, LLVM_LABEL);
    llvmCode += createLABEL(LLVM_ENTRY);
    llvmCode += llvmComment("   --------------------- alloca params:");
    llvmCode += dumpAllocaParams(subr);
    llvmCode += llvmComment("   --------------------- alloca local vars:");
    llvmCode += dumpAllocaLocalVars(subr);
    llvmCode += llvmComment("   --------------------- store params:");
    llvmCode += dumpStoreParams(subr);
    llvmCode += llvmComment("   --------------------- instructions:");
    llvmCode += dumpInstructionList(subr);
    llvmCode += "}\n\n";
    return llvmCode;
}

std::string LLVMCodeGen::dumpHeader(const subroutine &subr)
{
    std::string llvmCode;
    llvmCode += "define dso_local ";
    std::string funcName = subr.get_name();
    if (funcName == "main")
    {
        llvmCode += LLVM_INT + " @" + "main" + "() ";
    }
    else
    {
        llvmCode += getFuncReturnLLVMType(funcName) + " @" + funcName + "(";
        bool firstParam = true;
        for (auto p : subr.params)
        {
            if (p.name != "_result")
            {
                std::string llvmValue = getLLVMValue(p.name);
                std::string llvmType = getLocalSymbolLLVMType(funcName, p.name, true);
                if (not firstParam)
                    llvmCode += ", ";
                else
                    firstParam = false;
                llvmCode += llvmType + " " + llvmValue;
            }
        }
        llvmCode += ") ";
    }
    return llvmCode;
}

std::string LLVMCodeGen::dumpAllocaParams(const subroutine &subr)
{
    std::string llvmCode;
    std::string funcName = subr.get_name();
    for (auto p : subr.params)
    {
        std::string llvmValue = getLLVMValue(p.name);
        std::string llvmType;
        if (p.name == "_result")
            llvmType = getFuncReturnLLVMType(funcName);
        else
            llvmType = getLocalSymbolLLVMType(funcName, p.name, true);
        std::string llvmValueAddr = getLLVMValueAddr(llvmValue);
        std::string llvmTypePtr = getPointerToType(llvmType);
        bindLLVMLocalValueWithType(llvmValueAddr, llvmTypePtr);
        llvmCode += llvmComment("   param " + p.name + " " + llvmType);
        llvmCode += createALLOCA(llvmValueAddr, llvmType);
    }
    return llvmCode;
}

std::string LLVMCodeGen::dumpAllocaLocalVars(const subroutine &subr)
{
    std::string llvmCode;
    std::string funcName = subr.get_name();
    for (auto v : subr.vars)
    {
        std::string llvmValue = getLLVMValue(v.name);
        std::string llvmType = getLocalSymbolLLVMType(funcName, v.name);
        std::string llvmValueAddr = getLLVMValueAddr(llvmValue);
        std::string llvmTypePtr = getPointerToType(llvmType);
        bindLLVMLocalValueWithType(llvmValueAddr, llvmTypePtr);
        llvmCode += llvmComment("   localVar " + v.name + " " + llvmType);
        llvmCode += createALLOCA(llvmValueAddr, llvmType);
    }
    return llvmCode;
}

std::string LLVMCodeGen::dumpStoreParams(const subroutine &subr)
{
    std::string llvmCode;
    std::string funcName = subr.get_name();
    if (funcName == "main")
    {
        // std::string llvmValue     = getLLVMValue("_result");
        // // std::string llvmType      = LLVM_INT;
        // std::string llvmValueAddr = getLLVMValueAddr(llvmValue);
        // // std::string llvmTypePtr   = getPointerToType(llvmType);
        // // bindLLVMLocalValueWithType(llvmValue, llvmType);         // DONE IN dumpAllocaParams
        // // bindLLVMLocalValueWithType(llvmValueAddr, llvmTypePtr);  // DONE IN dumpAllocaParams
        // llvmCode += createStore(LLVM_ZERO_INT, llvmValueAddr);    // "store i32 0, i32* %_result.addr";
    }
    if (subr.params.size() > 0)
    {
        llvmCode += llvmComment("params initialization:");
    }
    for (auto p : subr.params)
    {
        if (p.name != "_result")
        {
            std::string llvmValue = getLLVMValue(p.name);
            std::string llvmValueAddr = getLLVMValueAddr(llvmValue);
            llvmCode += createSTORE(llvmValue, llvmValueAddr);
        }
    }
    return llvmCode;
}

std::string LLVMCodeGen::dumpInstructionList(const subroutine &subr)
{
    std::string llvmCode;
    int n = subr.get_instructions().size();
    instructionList instrList = subr.get_instructions();
    for (int i = 0; i < n - 1; ++i)
    {
        llvmCode += llvmComment(instrList[i].dump());
        llvmCode += dumpInstruction(instrList[i], instrList[i + 1]);
    }
    llvmCode += llvmComment(instrList[n - 1].dump());
    llvmCode += dumpInstruction(instrList[n - 1], instruction::NOOP());
    return llvmCode;
}

std::string LLVMCodeGen::dumpInstruction(const instruction &instr,
                                         const instruction &next)
{
    std::string llvmCode;

    std::string llvmValue1, llvmValue2, llvmValue3;
    std::string llvmMemCodeValue1, llvmMemCodeValue2, llvmMemCodeValue3;

    std::string tcodeArg1 = getTCodeArg(instr, 1);
    std::string tcodeArg2 = getTCodeArg(instr, 2);
    std::string tcodeArg3 = getTCodeArg(instr, 3);

    switch (instr.oper)
    {
    case instruction::_LABEL:
    {
        std::string label = tcodeArg1;
        std::string llvmLabel = getLLVMValue(label);
        if (not prevInstrIsTerminator)
            llvmCode += createBR(llvmLabel);
        llvmCode += createLABEL(label);
        break;
    }
    case instruction::_UJUMP:
    {
        std::string label = tcodeArg1;
        std::string llvmLabel = getLLVMValue(label);
        llvmCode += createBR(llvmLabel);
        if (next.oper != instruction::_LABEL and next.oper != instruction::_NOOP)
        {
            std::string labelDead = createNewPrefixedValueWithType("%.dead.cont", LLVM_LABEL);
            std::string labelDeadName = labelDead.substr(1);
            llvmCode += createLABEL(labelDeadName);
        }
        break;
    }
    case instruction::_FJUMP:
    {
        accessValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        llvmCode += llvmMemCodeValue1;
        std::string labelJump = getLLVMValue(tcodeArg2);
        if (next.oper != instruction::_LABEL and next.oper != instruction::_NOOP)
        {
            std::string labelCont = createNewPrefixedValueWithType("%.br.cont", LLVM_LABEL);
            std::string labelContName = labelCont.substr(1);
            llvmCode += createBR(llvmValue1, labelCont, labelJump);
            llvmCode += createLABEL(labelContName);
        }
        else
        {
            std::string labelCont = getLLVMValue(next.arg1);
            llvmCode += createBR(llvmValue1, labelCont, labelJump);
        }
        break;
    }
    case instruction::_HALT:
    {
        llvmCode += createHALT();
        break;
    }
    case instruction::_LOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        llvmValue2 = getLLVMValue(tcodeArg2);
        if (isTCodeIdentifier(tcodeArg1))
        { //  a = %4   or   a = b
            accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += llvmMemCodeValue2;
            llvmCode += createSTORE(llvmValue2, llvmValue1Addr);
        }
        else if (isTCodeIdentifier(tcodeArg2))
        { // %4 = a
            std::string llvmValue2Addr = getLLVMValueAddr(llvmValue2);
            llvmCode += createLOAD(llvmValue1, llvmValue2Addr);
        }
        else
        { // %4 = %6
            std::string llvmType = getLLVMTypeOfValue(llvmValue2);
            if (isLLVMAnyIntegerType(llvmType))
            {
                std::string llvmTypeOneIntUp = getLLVMTypeOneIntUp(llvmType);
                std::string newValuePrefix = "%.temp." + tcodeArg1.substr(1) + "." + llvmTypeOneIntUp;
                std::string llvmValue2Extended = createNewPrefixedValueWithType(newValuePrefix, llvmTypeOneIntUp);
                llvmCode += createCONVERSION(LLVM_ZEXT, llvmValue2Extended, llvmValue2, llvmTypeOneIntUp);
                llvmCode += createCONVERSION(LLVM_TRUNC, llvmValue1, llvmValue2Extended, llvmType);
            }
            else
            { // llvmType == LLVM_FLOAT
                std::string newValuePrefix = "%.temp." + tcodeArg1.substr(1) + ".double";
                std::string llvmValue2FPDouble = createNewPrefixedValueWithType(newValuePrefix, LLVM_DOUBLE);
                llvmCode += createCONVERSION(LLVM_FPEXT, llvmValue2FPDouble, llvmValue2, LLVM_DOUBLE);
                llvmCode += createCONVERSION(LLVM_FPTRUNC, llvmValue1, llvmValue2FPDouble, llvmType);
            }
        }
        break;
    }
    case instruction::_ILOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        llvmValue2 = getLLVMValue(tcodeArg2);
        if (isTCodeTemporal(tcodeArg1))
            llvmCode += createCONVERSION(LLVM_TRUNC, llvmValue1, llvmValue2, LLVM_INT64);
        else
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += createSTORE(llvmValue2, llvmValue1Addr);
        }
        break;
    }
    case instruction::_FLOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        llvmValue2 = getLLVMValue(tcodeArg2);
        if (isTCodeTemporal(tcodeArg1))
            llvmCode += createCONVERSION(LLVM_FPTRUNC, llvmValue1, llvmValue2, LLVM_DOUBLE);
        else
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += createSTORE(llvmValue2, llvmValue1Addr);
        }
        break;
    }
    case instruction::_CHLOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        int asciiCode = getAsciiCode(tcodeArg2);
        llvmValue2 = std::to_string(asciiCode);
        if (isTCodeTemporal(tcodeArg1))
            llvmCode += createCONVERSION(LLVM_TRUNC, llvmValue1, llvmValue2, LLVM_INT32);
        else
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += createSTORE(llvmValue2, llvmValue1Addr);
        }
        break;
    }
    case instruction::_PUSH:
    {
        if (tcodeArg1 != "")
        {
            accessValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
            std::string llvmType = getLLVMTypeOfValue(llvmValue1);
            llvmCode += llvmMemCodeValue1;
            pushLLVMParamCallStack(llvmValue1);
        }
        else
        {
            pushLLVMParamCallStack("");
        }
        break;
    }
    case instruction::_POP:
    {
        std::string param = topPopLLVMParamCallStack();
        if (param != "")
            pendingCallArgs.push_back(param);
        if (tcodeArg1 != "")
        {
            modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
            llvmCode += createCALL(pendingCallFunc, llvmValue1, pendingCallArgs);
            llvmCode += llvmMemCodeValue1;
        }
        else if (isEmptyLLVMParamCallStack())
        {
            llvmCode += createCALL(pendingCallFunc, pendingCallArgs);
        }
        break;
    }
    case instruction::_CALL:
    {
        pendingCallFunc = tcodeArg1;
        pendingCallArgs.clear();
        if (isEmptyLLVMParamCallStack())
            llvmCode += createCALL(pendingCallFunc, pendingCallArgs);
        break;
    }
    case instruction::_RETURN:
    {
        std::string retType = getFuncReturnLLVMType(currentFunctionName);
        if (retType == LLVM_VOID)
        {
            if (isMain)
                llvmCode += createRET(LLVM_ZERO_INT, LLVM_INT);
            else
                llvmCode += createRET();
        }
        else
        {
            accessValueOfArgument("_result", llvmValue1, llvmMemCodeValue1);
            llvmCode += llvmMemCodeValue1;
            llvmCode += createRET(llvmValue1);
        }
        if (next.oper != instruction::_LABEL and next.oper != instruction::_NOOP)
        {
            std::string labelDead = createNewPrefixedValueWithType("%.dead.code", LLVM_LABEL);
            std::string labelDeadName = labelDead.substr(1);
            llvmCode += createLABEL(labelDeadName);
        }
        break;
    }
    case instruction::_XLOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        std::string llvmType = getLLVMTypeOfValue(llvmValue1); // it can  be "array of" or "pointer to"
        std::string llvmElemType;
        if (isLLVMArrayType(llvmType))
            llvmElemType = getLLVMElementOfArrayType(llvmType);
        else if (isPointerType(llvmType))
            llvmElemType = getPointedType(llvmType);
        std::string llvmElemTypePtr = getPointerToType(llvmElemType);
        std::string arrayIndex64 = createNewPrefixedValueWithType("%.idx64", LLVM_INT64);
        std::string arrayPointer = createNewPrefixedValueWithType("%.arrPtr", llvmElemTypePtr);
        std::string llvmValue1Addr;
        if (isTCodeIdentifier(tcodeArg1))
            llvmValue1Addr = getLLVMValueAddr(llvmValue1);
        else
            llvmValue1Addr = llvmValue1;
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createCONVERSION(LLVM_SEXT, arrayIndex64, llvmValue2, LLVM_INT);
        llvmCode += createGETELEMENTPTR(arrayPointer, llvmValue1Addr, arrayIndex64);
        llvmCode += createSTORE(llvmValue3, arrayPointer);
        break;
    }
    case instruction::_LOADX:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        llvmValue2 = getLLVMValue(tcodeArg2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        std::string llvmType = getLLVMTypeOfValue(llvmValue2); // it can  be "array of" or "pointer to"
        std::string llvmElemType;
        if (isLLVMArrayType(llvmType))
            llvmElemType = getLLVMElementOfArrayType(llvmType);
        else if (isPointerType(llvmType))
            llvmElemType = getPointedType(llvmType);
        std::string llvmElemTypePtr = getPointerToType(llvmElemType);
        std::string arrayIndex64 = createNewPrefixedValueWithType("%.idx64", LLVM_INT64);
        std::string arrayPointer = createNewPrefixedValueWithType("%.arrPtr", llvmElemTypePtr);
        std::string llvmValue2Addr;
        if (isTCodeIdentifier(tcodeArg2))
            llvmValue2Addr = getLLVMValueAddr(llvmValue2);
        else
            llvmValue2Addr = llvmValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createCONVERSION(LLVM_SEXT, arrayIndex64, llvmValue3, LLVM_INT);
        llvmCode += createGETELEMENTPTR(arrayPointer, llvmValue2Addr, arrayIndex64);
        llvmCode += createLOAD(llvmValue1, arrayPointer);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_ALOAD:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        llvmValue2 = getLLVMValue(tcodeArg2);
        std::string llvmType2 = getLLVMTypeOfValue(llvmValue2);
        std::string llvmValue2Addr = getLLVMValueAddr(llvmValue2);
        if (isLLVMArrayType(llvmType2))
            llvmCode += createGETELEMENTPTR(llvmValue1, llvmValue2Addr, LLVM_ZERO_INT);
        else if (isPointerType(llvmType2))
            llvmCode += createLOAD(llvmValue1, llvmValue2Addr);
        break;
    }
        /*
      case instruction::_LOADC:
        {
          llvmCode += ind + arg1 + " = *" + arg2 + "\n";
          break;
        }
      case instruction::_CLOAD:
        {
          llvmCode += ind + "*" + arg1 + " = " + arg2 + "\n";
          break;
        }
        */
    case instruction::_WRITEI:
    {
        accessValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
        llvmCode += llvmMemCodeValue1;
        std::string printIntValue = llvmValue1;
        if (llvmType1 == LLVM_INT1)
        {
            printIntValue = createNewPrefixedValueWithType("%.wrti.i32", LLVM_INT32);
            llvmCode += createCONVERSION(LLVM_ZEXT, printIntValue, llvmValue1, LLVM_INT1);
        }
        llvmCode += createPRINTF(printIntValue, LLVM_INT);
        break;
    }
    case instruction::_WRITEF:
    {
        accessValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        llvmCode += llvmMemCodeValue1;
        std::string fpextValue = createNewPrefixedValueWithType("%.wrtf.double", LLVM_DOUBLE);
        llvmCode += createCONVERSION(LLVM_FPEXT, fpextValue, llvmValue1, LLVM_FLOAT);
        llvmCode += createPRINTF(fpextValue, LLVM_DOUBLE);
        break;
    }
    case instruction::_WRITEC:
    {
        accessValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        llvmCode += llvmMemCodeValue1;
        std::string zextValue = createNewPrefixedValueWithType("%.wrtc.i32", LLVM_INT32);
        llvmCode += createCONVERSION(LLVM_ZEXT, zextValue, llvmValue1, LLVM_INT8);
        llvmCode += createPUTCHAR(zextValue);
        break;
    }
    case instruction::_WRITES:
    {
        auto it = std::find(writeSAslStrVec.begin(), writeSAslStrVec.end(), tcodeArg1);
        std::size_t i = std::distance(writeSAslStrVec.begin(), it);
        std::string strFormat = "@.str.s." + std::to_string(i + 1);
        std::string::size_type llvmStrSize = writeSLLVMStrSizeVec[i];
        llvmCode += createPRINTS(strFormat, llvmStrSize);
        break;
    }
    case instruction::_WRITELN:
    {
        int asciiNL = int('\n');
        llvmCode += createPUTCHAR(std::to_string(asciiNL)); // "10"
        break;
    }
    case instruction::_READI:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
        if (not isTCodeTemporal(tcodeArg1))
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            if (llvmType1 == LLVM_INT1)
            {
                std::string globalInt = createNewPrefixedValueWithType("%.readi.global.i", LLVM_INT32);
                std::string compare0 = createNewPrefixedValueWithType("%.readi.i1.cmp1", LLVM_INT1);
                std::string notCompare0 = createNewPrefixedValueWithType("%.readi.i1.not", LLVM_INT1);
                llvmCode += createSCANF(LLVM_GLOBAL_INT_ADDR);
                llvmCode += createLOAD(globalInt, LLVM_GLOBAL_INT_ADDR);
                llvmCode += createCOMPARISON(instruction::_EQ, compare0, globalInt, LLVM_ZERO_INT, LLVM_INT);
                llvmCode += createNOT(notCompare0, compare0);
                llvmCode += createSTORE(notCompare0, llvmValue1Addr);
            }
            else
            {
                llvmCode += createSCANF(llvmValue1Addr);
            }
        }
        else
        {
            if (llvmType1 == LLVM_INT1)
            {
                std::string globalInt = createNewPrefixedValueWithType("%.readi.global.i", LLVM_INT32);
                std::string compare0 = createNewPrefixedValueWithType("%.readi.i1.cmp1", LLVM_INT1);
                std::string notCompare0 = createNewPrefixedValueWithType("%.readi.i1.not", LLVM_INT1);
                llvmCode += createSCANF(LLVM_GLOBAL_INT_ADDR);
                llvmCode += createLOAD(globalInt, LLVM_GLOBAL_INT_ADDR);
                llvmCode += createCOMPARISON(instruction::_EQ, compare0, globalInt, LLVM_ZERO_INT, LLVM_INT);
                llvmCode += createNOT(llvmValue1, compare0);
            }
            else
            {
                llvmCode += createSCANF(LLVM_GLOBAL_INT_ADDR);
                llvmCode += createLOAD(llvmValue1, LLVM_GLOBAL_INT_ADDR);
            }
        }
        break;
    }
    case instruction::_READF:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        if (not isTCodeTemporal(tcodeArg1))
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += createSCANF(llvmValue1Addr);
        }
        else
        {
            llvmCode += createSCANF(LLVM_GLOBAL_FLOAT_ADDR);
            llvmCode += createLOAD(llvmValue1, LLVM_GLOBAL_FLOAT_ADDR);
        }
        break;
    }
    case instruction::_READC:
    {
        llvmValue1 = getLLVMValue(tcodeArg1);
        if (not isTCodeTemporal(tcodeArg1))
        {
            std::string llvmValue1Addr = getLLVMValueAddr(llvmValue1);
            llvmCode += createSCANF(llvmValue1Addr);
        }
        else
        {
            llvmCode += createSCANF(LLVM_GLOBAL_CHAR_ADDR);
            llvmCode += createLOAD(llvmValue1, LLVM_GLOBAL_CHAR_ADDR);
        }
        break;
    }
    case instruction::_ADD:
    case instruction::_SUB:
    case instruction::_MUL:
    case instruction::_DIV:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createARITHMETIC(instr.oper, llvmValue1, llvmValue2, llvmValue3, LLVM_INT);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_EQ:
    case instruction::_LT:
    case instruction::_LE:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        std::string llvmType23 = LLVM_INT;
        if (isTCodeIdentifier(tcodeArg2) or isTCodeTemporal(tcodeArg2))
        {
            std::string llvmValue2 = getLLVMValue(tcodeArg2);
            llvmType23 = getLLVMTypeOfValue(llvmValue2);
        }
        else if (isTCodeIdentifier(tcodeArg3) or isTCodeTemporal(tcodeArg3))
        {
            std::string llvmValue3 = getLLVMValue(tcodeArg3);
            llvmType23 = getLLVMTypeOfValue(llvmValue3);
        }
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createCOMPARISON(instr.oper, llvmValue1, llvmValue2, llvmValue3, llvmType23);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_FEQ:
    case instruction::_FLT:
    case instruction::_FLE:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createCOMPARISON(instr.oper, llvmValue1, llvmValue2, llvmValue3, LLVM_FLOAT);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_NEG:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        llvmCode += llvmMemCodeValue2;
        llvmCode += createARITHMETIC(instruction::_SUB, llvmValue1, LLVM_ZERO_INT, llvmValue2, LLVM_INT);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_FADD:
    case instruction::_FSUB:
    case instruction::_FMUL:
    case instruction::_FDIV:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createARITHMETIC(instr.oper, llvmValue1, llvmValue2, llvmValue3, LLVM_FLOAT);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_FNEG:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        if (isTCodeTemporal(tcodeArg1))
            bindLLVMLocalValueWithType(llvmValue1, LLVM_FLOAT);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        llvmCode += llvmMemCodeValue2;
        llvmCode += createFNEG(llvmValue1, llvmValue2);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_FLOAT:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        llvmCode += llvmMemCodeValue2;
        llvmCode += createSITOFP(llvmValue1, llvmValue2, LLVM_INT);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_AND:
    case instruction::_OR:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        accessValueOfArgument(tcodeArg3, llvmValue3, llvmMemCodeValue3);
        llvmCode += llvmMemCodeValue2;
        llvmCode += llvmMemCodeValue3;
        llvmCode += createLOGICAL(instr.oper, llvmValue1, llvmValue2, llvmValue3);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_NOT:
    {
        modifyValueOfArgument(tcodeArg1, llvmValue1, llvmMemCodeValue1);
        accessValueOfArgument(tcodeArg2, llvmValue2, llvmMemCodeValue2);
        llvmCode += llvmMemCodeValue2;
        llvmCode += createNOT(llvmValue1, llvmValue2);
        llvmCode += llvmMemCodeValue1;
        break;
    }
    case instruction::_NOOP:
    {
        llvmCode += ";   noop\n";
        break;
    }
    default:
    {
        llvmCode += ";   UNKNOWN\n";
        break;
    }
    }

    prevInstrIsTerminator = (instr.oper == instruction::_UJUMP or
                             instr.oper == instruction::_FJUMP or
                             instr.oper == instruction::_RETURN);

    return llvmCode;
}

std::string LLVMCodeGen::getTCodeArg(const instruction &instr, int i) const
{
    std::string arg;
    if (i == 1)
        arg = instr.arg1;
    else if (i == 2)
        arg = instr.arg2;
    else // i == 3
        arg = instr.arg3;
    return arg;
}

std::string LLVMCodeGen::getLLVMValue(const std::string &tcodeIdent) const
{
    if (tcodeIdent.size() == 0)
        return "";
    if (tcodeIdent[0] == '%')
        return "%.temp." + tcodeIdent.substr(1);
    if (std::isdigit(tcodeIdent[0]))
        return tcodeIdent;
    return "%" + tcodeIdent;
}

std::string LLVMCodeGen::getLLVMValueAddr(const std::string &llvmValue) const
{
    return llvmValue + ".addr";
}

std::string LLVMCodeGen::createALLOCA(const std::string &llvmValueAddr, const std::string &llvmType) const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + llvmValueAddr + " = alloca " + llvmType + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createSTORE(const std::string &llvmValue1,
                                     const std::string &llvmValue2Addr) const
{
    std::string llvmCode;
    std::string llvmType2Ptr = getLLVMTypeOfValue(llvmValue2Addr);
    std::string llvmType2 = getPointedType(llvmType2Ptr);
    llvmCode += INDENT_INSTR + "store " + llvmType2 + " " + llvmValue1 + ", " + llvmType2Ptr + " " + llvmValue2Addr + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createLABEL(const std::string &label) const
{
    std::string llvmCode;
    llvmCode += INDENT_LABEL + label + ":\n";
    return llvmCode;
}

std::string LLVMCodeGen::createCONVERSION(const std::string &llvmInstr, const std::string &llvmValue1,
                                          const std::string &llvmValue2, const std::string &llvmType2) const
{
    std::string llvmCode;
    std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
    llvmCode += INDENT_INSTR + llvmValue1 + " = " + llvmInstr + " " + llvmType2 + " " + llvmValue2 + " to " + llvmType1 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createLOAD(const std::string &llvmValue1, const std::string &llvmValue2Addr) const
{
    std::string llvmCode;
    std::string llvmTypePtr = getLLVMTypeOfValue(llvmValue2Addr);
    std::string llvmType = getPointedType(llvmTypePtr);
    llvmCode += INDENT_INSTR + llvmValue1 + " = load " + llvmType + ", " + llvmTypePtr + " " + llvmValue2Addr + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createARITHMETIC(instruction::Operation oper, const std::string &llvmValue1,
                                          const std::string &llvmValue2, const std::string &llvmValue3,
                                          const std::string &llvmType23) const
{
    std::string llvmCode;
    std::string llvmInstr = tcode2llvmInstrMap.at(oper);
    llvmCode = INDENT_INSTR + llvmValue1 + " = " + llvmInstr + " " + llvmType23 + " " + llvmValue2 + ", " + llvmValue3 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createCOMPARISON(instruction::Operation oper, const std::string &llvmValue1,
                                          const std::string &llvmValue2, const std::string &llvmValue3,
                                          const std::string &llvmType23) const
{
    std::string llvmCode;
    std::string llvmInstr = tcode2llvmInstrMap.at(oper);
    llvmCode = INDENT_INSTR + llvmValue1 + " = " + llvmInstr + " " + llvmType23 + " " + llvmValue2 + ", " + llvmValue3 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createLOGICAL(instruction::Operation oper, const std::string &llvmValue1,
                                       const std::string &llvmValue2, const std::string &llvmValue3) const
{
    std::string llvmCode;
    std::string llvmInstr = tcode2llvmInstrMap.at(oper);
    llvmCode = INDENT_INSTR + llvmValue1 + " = " + llvmInstr + " " + LLVM_BOOL + " " + llvmValue2 + ", " + llvmValue3 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createNOT(const std::string &llvmValue1, const std::string &llvmValue2) const
{
    std::string llvmCode;
    llvmCode = INDENT_INSTR + llvmValue1 + " = xor " + LLVM_BOOL + " " + llvmValue2 + ", " + LLVM_ONE_INT + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createFNEG(const std::string &llvmValue1, const std::string &llvmValue2) const
{
    std::string llvmCode;
    // <result> = fneg [fast-math flags]* <ty> <op1>    ; yields ty:result
    llvmCode += INDENT_INSTR + llvmValue1 + " = fneg " + LLVM_FLOAT + " " + llvmValue2 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createSITOFP(const std::string &llvmValue1, const std::string &llvmValue2,
                                      const std::string &llvmType2) const
{
    std::string llvmCode;
    // <result> = sitofp <ty> <value> to <ty2>    ; yields ty2
    std::string llvmType1 = getLLVMTypeOfValue(llvmValue1);
    llvmCode += INDENT_INSTR + llvmValue1 + " = sitofp " + llvmType2 + " " + llvmValue2 + " to " + llvmType1 + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createPRINTF(const std::string &llvmValue, const std::string &llvmType) const
{
    std::string llvmCode;
    std::string format;
    if (llvmType == LLVM_INT)
        format = "@.str.i";
    else if (llvmType == LLVM_DOUBLE)
        format = "@.str.f";
    llvmCode += INDENT_INSTR + "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* " + format + ", i64 0, i64 0), " + llvmType + " " + llvmValue + ")\n";
    return llvmCode;
}

std::string LLVMCodeGen::createPRINTS(const std::string &strFormat, const int strSize) const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([" + std::to_string(strSize) + " x i8], [" + std::to_string(strSize) + " x i8]* " + strFormat + ", i64 0, i64 0))\n";
    return llvmCode;
}

std::string LLVMCodeGen::createPUTCHAR(const std::string &llvmValue) const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "call i32 @putchar(i32 " + llvmValue + ")\n";
    return llvmCode;
}

std::string LLVMCodeGen::createSCANF(const std::string &llvmValueAddr) const
{
    std::string llvmCode;
    std::string format;
    std::string llvmTypePtr = getLLVMTypeOfValue(llvmValueAddr);
    std::string llvmType = getPointedType(llvmTypePtr);
    if (llvmType == LLVM_INT)
        format = "@.str.i";
    else if (llvmType == LLVM_FLOAT)
        format = "@.str.f";
    else // LLVM_CHAR
        format = "@.str.c";
    llvmCode += INDENT_INSTR + "call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* " + format + ", i64 0, i64 0), " + llvmTypePtr + " " + llvmValueAddr + ")\n";
    return llvmCode;
}

std::string LLVMCodeGen::createHALT() const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "call void @exit(i32 1)" + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createBR(const std::string &llvmValue) const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "br label " + llvmValue + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createBR(const std::string &llvmValue,
                                  const std::string &labelCont, const std::string &labelJump) const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "br i1 " + llvmValue + ", label " + labelCont + ", label " + labelJump + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createRET(const std::string &llvmValue, const std::string &llvmType) const
{
    std::string llvmCode;
    llvmCode = INDENT_INSTR + "ret " + llvmType + " " + llvmValue + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createRET(const std::string &llvmValue) const
{
    std::string llvmCode;
    std::string llvmType = getLLVMTypeOfValue(llvmValue);
    llvmCode += INDENT_INSTR + "ret " + llvmType + " " + llvmValue + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createRET() const
{
    std::string llvmCode;
    llvmCode += INDENT_INSTR + "ret void" + "\n";
    return llvmCode;
}

std::string LLVMCodeGen::createCALL(const std::string &tcodeFunc, const std::string &llvmValue1,
                                    const std::vector<std::string> &llvmArgs) const
{
    std::string llvmCode;
    std::string llvmRetType = getFuncReturnLLVMType(tcodeFunc);
    int n = llvmArgs.size();
    std::string llvmCodeArgs;
    for (int i = n - 1; i >= 0; --i)
    {
        std::string param = llvmArgs[i];
        std::string paramType = getLLVMTypeOfValue(param);
        if (i == n - 1)
            llvmCodeArgs += paramType + " " + param;
        else
            llvmCodeArgs += ", " + paramType + " " + param;
    }
    llvmCode += INDENT_INSTR + llvmValue1 + " = call " + llvmRetType + " @" + tcodeFunc + "(" + llvmCodeArgs + ")\n";
    return llvmCode;
}

std::string LLVMCodeGen::createCALL(const std::string &tcodeFunc,
                                    const std::vector<std::string> &llvmArgs) const
{
    std::string llvmCode;
    std::string llvmRetType = getFuncReturnLLVMType(tcodeFunc);
    int n = llvmArgs.size();
    std::string llvmCodeArgs;
    for (int i = n - 1; i >= 0; --i)
    {
        std::string param = llvmArgs[i];
        std::string paramType = getLLVMTypeOfValue(param);
        if (i == n - 1)
            llvmCodeArgs += paramType + " " + param;
        else
            llvmCodeArgs += ", " + paramType + " " + param;
    }
    llvmCode += INDENT_INSTR + "call " + llvmRetType + " @" + tcodeFunc + "(" + llvmCodeArgs + ")\n";
    return llvmCode;
}

std::string LLVMCodeGen::createGETELEMENTPTR(const std::string &llvmArrayPointerValue,
                                             const std::string &llvmArrayBaseValue,
                                             const std::string &llvmArrayIndexValue) const
{
    std::string llvmCode;
    std::string llvmArrayPtrType = getLLVMTypeOfValue(llvmArrayBaseValue);
    std::string llvmPointedType = getPointedType(llvmArrayPtrType);
    if (isLLVMArrayType(llvmPointedType))
    {
        // %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* %A, i64 0, i64 %idxprom
        llvmCode += INDENT_INSTR + llvmArrayPointerValue + " = getelementptr inbounds " + llvmPointedType + ", " + llvmArrayPtrType + " " + llvmArrayBaseValue + ", i64 0, i64 " + llvmArrayIndexValue + "\n";
    }
    else
    {
        // %arrayidx = getelementptr inbounds i32, i32* %1, i64 %idxprom
        llvmCode += INDENT_INSTR + llvmArrayPointerValue + " = getelementptr inbounds " + llvmPointedType + ", " + llvmArrayPtrType + " " + llvmArrayBaseValue + ", i64 " + llvmArrayIndexValue + "\n";
    }
    return llvmCode;
}

void LLVMCodeGen::accessValueOfArgument(const std::string &tcodeArgIn,
                                        std::string &llvmValueOut, std::string &llvmAccInstr)
{
    // Pre:  if tcodeArgIn is a tcode identifiier then:
    //          * the llvmValueIn corresponding to tcodeArgIn
    //            has been previously typed (using llvmValueTypeMap's)
    //       if tcodeArgIn is a tcode temporal or a constant then:
    //          * -
    // Post: if tcodeArgIn is a tcode identifiier then:
    //          * the new created llvmValueOut uses llvmValueIn as a prefix
    //          * the new created llvmValueOut has been binded to the same type of llvmValueIn
    //          * a new llvmAccInstr is created: a LOAD from the value of llvmValueIn
    //            (in llvmValueInAddr) to the new created value llvmValueOut
    //       if tcodeArgIn is a tcode temporal or a constant then:
    //          * llmValueOut is the llvm value corresponding to tcodeArgIn
    //          * no additional instruction is needed (llvmAccInstr is equal to "")
    if (isTCodeIdentifier(tcodeArgIn))
    {
        std::string llvmValueIn = getLLVMValue(tcodeArgIn);
        std::string llvmType = getLLVMTypeOfValue(llvmValueIn);
        std::string llvmValueInAddr = getLLVMValueAddr(llvmValueIn);
        llvmValueOut = createNewPrefixedValueWithType(llvmValueIn, llvmType);
        llvmAccInstr = createLOAD(llvmValueOut, llvmValueInAddr);
    }
    else
    {
        llvmValueOut = getLLVMValue(tcodeArgIn); // = tcodeArgIn;
        llvmAccInstr = "";
    }
}

void LLVMCodeGen::modifyValueOfArgument(const std::string &tcodeArgIn,
                                        std::string &llvmValueOut, std::string &llvmModInstr)
{
    // Pre:  if tcodeArgIn is a tcode identifiier then:
    //          * the llvmValueIn corresponding to tcodeArgIn
    //            has been previously typed (using llvmValueTypeMap's)
    //       if tcodeArgIn is a tcode temporal or a constant then:
    //          * -
    // Post: if tcodeArgIn is a tcode identifiier then:
    //          * the new created llvmValueOut uses llvmValueIn as a prefix
    //          * the new created llvmValueOut is binded to the same type of llvmValueIn
    //          * a new llvmModInstr is created: a STORE of the new created value llvmValueOut
    //            into the memory address of llvmValueIn (llvmValueInAddr)
    //       if tcodeArgIn is a tcode temporal or a constant then:
    //          * llmValueOut is the llvm value corresponding to tcodeArgIn
    //          * no additional instruction is needed (llvmModInstr is equal to "")
    if (isTCodeIdentifier(tcodeArgIn))
    {
        std::string llvmValueIn = getLLVMValue(tcodeArgIn);
        std::string llvmType = getLLVMTypeOfValue(llvmValueIn);
        std::string llvmValueInAddr = getLLVMValueAddr(llvmValueIn);
        llvmValueOut = createNewPrefixedValueWithType(llvmValueIn, llvmType);
        llvmModInstr = createSTORE(llvmValueOut, llvmValueInAddr);
    }
    else
    {
        llvmValueOut = getLLVMValue(tcodeArgIn); // = tcodeArgIn;
        llvmModInstr = "";
    }
}

std::string LLVMCodeGen::createNewPrefixedValueWithType(const std::string &llvmValuePrefix,
                                                        const std::string &llvmType)
{
    // This method creates a new llvm value using the llvmLocalValueCountMap to generate  different
    // llvm identifiers.
    // Pre:  * llvmValuePrefix can be a llvm value of a tcode variable or parameter (for example, "%a"),
    //         or a especial prefix used in the tcode to llvm translation (for example, "%.cont").
    // Post: * a completely new llvmValue is generated formed by the prefix, followed by a character '.',
    //         followed by the (integer) value of the counter in the llvmLocalValueCountMap.
    //         The value of llvmLocalValueCountMap is incremented for future uses.
    //       * The new llvm value generated is binded to th type llvmType, using the method
    //         bindLLVMLocalValueWithType
    llvmLocalValueCountMap[llvmValuePrefix] += 1;
    std::string llvmNewValue = llvmValuePrefix + "." + std::to_string(llvmLocalValueCountMap[llvmValuePrefix]);
    bindLLVMLocalValueWithType(llvmNewValue, llvmType);
    return llvmNewValue;
}

void LLVMCodeGen::bindGlobalValuesWithTypes()
{
    if (globalI)
    {
        llvmGlobalValueVec.push_back(LLVM_GLOBAL_INT_ADDR);
        llvmGlobalValueTypeMap[LLVM_GLOBAL_INT_ADDR] = LLVM_INT_PTR;
    }
    if (globalF)
    {
        llvmGlobalValueVec.push_back(LLVM_GLOBAL_FLOAT_ADDR);
        llvmGlobalValueTypeMap[LLVM_GLOBAL_FLOAT_ADDR] = LLVM_FLOAT_PTR;
    }
    if (globalC)
    {
        llvmGlobalValueVec.push_back(LLVM_GLOBAL_CHAR_ADDR);
        llvmGlobalValueTypeMap[LLVM_GLOBAL_CHAR_ADDR] = LLVM_CHAR_PTR;
    }
}

void LLVMCodeGen::bindTCodeLocalValueWithType(const std::string &tcodeArg,
                                              const std::string &llvmType)
{
    if (isTCodeIdentifier(tcodeArg) or isTCodeTemporal(tcodeArg))
    {
        std::string llvmValue = getLLVMValue(tcodeArg);
        if (llvmLocalValueTypeMap.find(llvmValue) == llvmLocalValueTypeMap.end())
        {
            llvmLocalValueVec.push_back(llvmValue);
            llvmLocalValueTypeMap[llvmValue] = llvmType;
            llvmLocalValueCountMap[llvmValue] = 0;
        }
        else
        {
            std::string llvmCurrentType = llvmLocalValueTypeMap.at(llvmValue);
            if (llvmCurrentType != LLVM_TYERR and llvmType != LLVM_TYMISS)
            {
                if (llvmCurrentType == LLVM_INT_BOOL)
                {
                    if (llvmType == LLVM_INT or llvmType == LLVM_BOOL or llvmType == LLVM_INT_BOOL)
                        llvmLocalValueTypeMap[llvmValue] = llvmType;
                    else
                        llvmLocalValueTypeMap[llvmValue] = LLVM_TYERR;
                }
                else if (llvmType == LLVM_INT_BOOL)
                {
                    if (llvmCurrentType == LLVM_TYMISS)
                        llvmLocalValueTypeMap[llvmValue] = llvmType;
                    else if (llvmCurrentType != LLVM_INT and llvmCurrentType != LLVM_BOOL and
                             llvmCurrentType != LLVM_INT_BOOL)
                        llvmLocalValueTypeMap[llvmValue] = LLVM_TYERR;
                }
                else if (llvmCurrentType != LLVM_TYMISS and llvmCurrentType != llvmType)
                    llvmLocalValueTypeMap[llvmValue] = LLVM_TYERR;
            }
        }
    }
}

void LLVMCodeGen::bindPairOfTCodeLocalValuesWithTypes(const std::string &tcodeArg1,
                                                      const std::string &tcodeArg2)
{
    std::string llvmValue1 = getLLVMValue(tcodeArg1);
    std::string llvmValue2 = getLLVMValue(tcodeArg2);
    auto search1 = llvmLocalValueTypeMap.find(tcodeArg1);
    auto search2 = llvmLocalValueTypeMap.find(tcodeArg2);
    if (search1 == llvmLocalValueTypeMap.end() and search2 == llvmLocalValueTypeMap.end())
    {
        llvmLocalValueTypeMap[tcodeArg1] = LLVM_TYMISS;
        llvmLocalValueTypeMap[tcodeArg2] = LLVM_TYMISS;
    }
    else if (search2 == llvmLocalValueTypeMap.end())
    {
        std::string llvmType1 = llvmLocalValueTypeMap.at(llvmValue1);
        if (llvmType1 == LLVM_TYERR)
            llvmLocalValueTypeMap[tcodeArg2] = LLVM_TYMISS;
        else
            llvmLocalValueTypeMap[tcodeArg2] = llvmType1;
    }
    else if (search1 == llvmLocalValueTypeMap.end())
    {
        std::string llvmType2 = llvmLocalValueTypeMap.at(llvmValue2);
        if (llvmType2 == LLVM_TYERR)
            llvmLocalValueTypeMap[tcodeArg1] = LLVM_TYMISS;
        else
            llvmLocalValueTypeMap[tcodeArg1] = llvmType2;
    }
    else
    {
        std::string llvmType1 = llvmLocalValueTypeMap.at(llvmValue1);
        std::string llvmType2 = llvmLocalValueTypeMap.at(llvmValue2);
        if (llvmType1 != LLVM_TYERR and llvmType2 != LLVM_TYERR)
        {
            if (llvmType1 != LLVM_TYMISS and llvmType2 == LLVM_TYMISS)
                llvmLocalValueTypeMap[tcodeArg2] = llvmType1;
            else if (llvmType1 == LLVM_TYMISS and llvmType2 != LLVM_TYMISS)
                llvmLocalValueTypeMap[tcodeArg1] = llvmType2;
            else if ((llvmType1 == LLVM_INT or llvmType1 == LLVM_BOOL) and
                     llvmType2 == LLVM_INT_BOOL)
                llvmLocalValueTypeMap[tcodeArg2] = llvmType1;
            else if (llvmType1 == LLVM_INT_BOOL and
                     (llvmType2 == LLVM_INT or llvmType2 == LLVM_BOOL))
                llvmLocalValueTypeMap[tcodeArg1] = llvmType2;
            else if (llvmType1 != LLVM_TYMISS and llvmType2 != LLVM_TYMISS and
                     llvmType1 != llvmType2)
            {
                llvmLocalValueTypeMap[tcodeArg1] = LLVM_TYERR;
                llvmLocalValueTypeMap[tcodeArg2] = LLVM_TYERR;
            }
        }
    }
}

void LLVMCodeGen::bindLLVMLocalValueWithType(const std::string &llvmValue,
                                             const std::string &llvmType)
{
    llvmLocalValueVec.push_back(llvmValue);
    llvmLocalValueTypeMap[llvmValue] = llvmType;
    llvmLocalValueCountMap[llvmValue] = 0;
}

// void LLVMCodeGen::bindTempWithType(const std::string & tcodeArg,
//                                    const std::string & llvmType) {
//   if (isTCodeTemporal(tcodeArg)) {
//     std::string llvmValue = getLLVMValue(tcodeArg);
//     llvmValueVec.push_back(llvmValue);
//     llvmValueTypeMap[llvmValue]  = llvmType;
//     llvmLocalValueCountMap[llvmValue] = 0;
//   }
// }

std::string LLVMCodeGen::getLLVMTypeOfValue(const std::string &llvmValue) const
{
    if (llvmValue[0] == '%') // local var
        return llvmLocalValueTypeMap.at(llvmValue);
    else // llvmValue[0] == '@'  // global var
        return llvmGlobalValueTypeMap.at(llvmValue);
}

bool LLVMCodeGen::isLLVMAnyIntegerType(const std::string &llvmType) const
{
    return (llvmType == LLVM_INT or llvmType == LLVM_INT8 or llvmType == LLVM_INT1);
}

std::string LLVMCodeGen::getLLVMTypeOneIntUp(const std::string &llvmIntType) const
{
    if (llvmIntType == LLVM_INT) // LLVM_INT == LLVM_INT32
        return LLVM_INT64;
    else if (llvmIntType == LLVM_INT8)
        return LLVM_INT32;
    else if (llvmIntType == LLVM_INT1)
        return LLVM_INT8;
    else
        return LLVM_TYERR;
}

bool LLVMCodeGen::isLLVMArrayType(const std::string &llvmType) const
{
    std::string::size_type xpos = llvmType.find(" x ");
    return xpos != std::string::npos;
}

std::string LLVMCodeGen::getLLVMElementOfArrayType(const std::string &llvmArrayType) const
{
    std::string::size_type xpos = llvmArrayType.find(" x ");
    assert(xpos != std::string::npos);
    std::string::size_type len = llvmArrayType.size();
    std::string elemType = llvmArrayType.substr(xpos + 3, len - xpos - 4);
    return elemType;
}

std::string LLVMCodeGen::getLLVMArrayTypeAsPointerType(const std::string &llvmArrayType) const
{
    std::string elemType = getLLVMElementOfArrayType(llvmArrayType);
    return getPointerToType(elemType);
}

bool LLVMCodeGen::isPointerType(const std::string &llvmType) const
{
    std::size_t n = llvmType.size();
    return llvmType[n - 1] == '*';
}

std::string LLVMCodeGen::getPointerToType(const std::string &llvmType) const
{
    return llvmType + "*";
}

std::string LLVMCodeGen::getPointedType(const std::string &llvmTypePtr) const
{
    std::size_t n = llvmTypePtr.size();
    return llvmTypePtr.substr(0, n - 1);
}

void LLVMCodeGen::pushTCodeParamCallStack(const std::string &tcodeParam)
{
    paramCallsStack.push(tcodeParam);
}

std::string LLVMCodeGen::topPopTCodeParamCallStack()
{
    assert(paramCallsStack.size() > 0);
    std::string tcodeParam = paramCallsStack.top();
    paramCallsStack.pop();
    return tcodeParam;
}

void LLVMCodeGen::pushLLVMParamCallStack(const std::string &llvmParam)
{
    paramCallsStack.push(llvmParam);
}

std::string LLVMCodeGen::topPopLLVMParamCallStack()
{
    assert(paramCallsStack.size() > 0);
    std::string llvmParam = paramCallsStack.top();
    paramCallsStack.pop();
    return llvmParam;
}

bool LLVMCodeGen::isEmptyLLVMParamCallStack() const
{
    return paramCallsStack.empty();
}

int LLVMCodeGen::getAsciiCode(const std::string &s) const
{
    if (s.size() == 1)
        return int(s[0]);
    else if (s == "\\n")
        return int('\n');
    else if (s == "\\t")
        return int('\t');
    else if (s == "\\\\")
        return int('\\');
    else if (s == "\\\"")
        return int('\"');
    else if (s == "\\\'")
        return int('\'');
    else
        return int(s[1]);
}

std::string LLVMCodeGen::llvmComment(const std::string &comm) const
{
    if (COMMENTS_ENABLED)
        return ";   " + comm + "\n";
    return "";
}
```


#### common/LLVMCodeGen.h


```cpp
/////////////////////////////////////////////////////////////////
//
//    LLVMCodeGen - LLVM IR generation for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include "TypesMgr.h"
#include "SymTable.h"
#include "code.h"

#include <string>
#include <vector>
#include <map>
#include <stack>

// using namespace std;

class code;
class subroutine;
class instruction;

class LLVMCodeGen
{
private:
    const TypesMgr &Types;
    const SymTable &Symbols;
    const code &tCode;

    static const bool COMMENTS_ENABLED;
    static const std::string INDENT_INSTR;
    static const std::string INDENT_LABEL;
    static const std::string LLVM_INT;
    static const std::string LLVM_FLOAT;
    static const std::string LLVM_CHAR;
    static const std::string LLVM_BOOL;
    static const std::string LLVM_VOID;
    static const std::string LLVM_LABEL;
    static const std::string LLVM_TYERR;
    static const std::string LLVM_TYMISS;
    static const std::string LLVM_INT_BOOL;
    static const std::string LLVM_INT_PTR;
    static const std::string LLVM_FLOAT_PTR;
    static const std::string LLVM_CHAR_PTR;
    static const std::string LLVM_BOOL_PTR;
    static const std::string LLVM_INT1;
    static const std::string LLVM_INT8;
    static const std::string LLVM_INT32;
    static const std::string LLVM_INT64;
    static const std::string LLVM_DOUBLE;
    static const std::string LLVM_GLOBAL_INT_ADDR;
    static const std::string LLVM_GLOBAL_FLOAT_ADDR;
    static const std::string LLVM_GLOBAL_CHAR_ADDR;
    static const std::string LLVM_ZERO_INT;
    static const std::string LLVM_ZERO_FLOAT;
    static const std::string LLVM_ONE_INT;
    static const std::string LLVM_ENTRY;
    static const std::string LLVM_ZEXT;
    static const std::string LLVM_FPEXT;
    static const std::string LLVM_TRUNC;
    static const std::string LLVM_FPTRUNC;
    static const std::string LLVM_SEXT;
    static const std::map<instruction::Operation, std::string> tcode2llvmInstrMap;

    bool writeI, writeF, writeC, writeS, writeLN;
    bool readI, readF, readC;
    bool haltAndExit;
    bool globalI, globalF, globalC, globalS;
    std::vector<std::string> writeSAslStrVec;
    std::vector<std::string::size_type> writeSLLVMStrSizeVec;
    std::string currentFunctionName;
    bool isMain;
    bool prevInstrIsTerminator;
    std::vector<std::string> llvmLocalValueVec;
    std::map<std::string, std::string> llvmLocalValueTypeMap;
    std::vector<std::string> llvmGlobalValueVec;
    std::map<std::string, std::string> llvmGlobalValueTypeMap;
    std::map<std::string, int> llvmLocalValueCountMap;
    std::stack<std::string> paramCallsStack;
    std::string pendingCallLLVMRetType;
    std::string pendingCallFunc;
    std::vector<std::string> pendingCallArgs;

    void check_SSA_tCode(std::string &failFunc, std::string &failTempVar) const;
    bool isTCodeTemporal(const std::string &tcodeArg) const;
    bool isTCodeIdentifier(const std::string &tcodeArg) const;

    void computeReadWriteHaltInfo();
    std::string getFuncReturnLLVMType(const std::string &tcodeFuncIdent) const;
    int getFuncNumberOfParams(const std::string &tcodeFuncIdent) const;
    std::string getFuncParamLLVMType(const std::string &tcodeFuncIdent, int n) const;
    std::vector<std::string> getFuncParamsLLVMTypes(const std::string &tcodeFuncIdent) const;

    std::string getLocalSymbolLLVMType(const std::string &tcodeFuncIdent,
                                       const std::string &tcodeSymbolIdent,
                                       bool isParameter = false) const;
    std::string TypeIdToLLVMType(TypesMgr::TypeId tid, bool isParameter = false) const;

    void getLLVMStringFromAslString(const std::string &aslString,
                                    std::string &llvmString,
                                    std::string::size_type &llvmStringSize);
    void generateReadWriteHaltBeginEndCode(std::string &begin, std::string &end);
    void startNewFunction(const subroutine &subr);
    void bindTCodeLocalSymbolsToLLVMTypes(const subroutine &subr);
    std::string dumpSubroutine(const subroutine &subr);
    std::string dumpHeader(const subroutine &subr);
    std::string dumpAllocaParams(const subroutine &subr);
    std::string dumpAllocaLocalVars(const subroutine &subr);
    std::string dumpStoreParams(const subroutine &subr);
    std::string dumpInstructionList(const subroutine &subr);
    std::string dumpInstruction(const instruction &instr,
                                const instruction &next);
    std::string getTCodeArg(const instruction &intr, int i) const;
    std::string getLLVMValue(const std::string &tcodeIdent) const;
    std::string getLLVMValueAddr(const std::string &llvmValue) const;

    std::string createALLOCA(const std::string &llvmValueAddr, const std::string &llvmType) const;
    std::string createSTORE(const std::string &llvmValue1, const std::string &llvmValue2) const;
    std::string createLABEL(const std::string &label) const;
    std::string createCONVERSION(const std::string &llvmInstr, const std::string &llvmValue1,
                                 const std::string &llvmValue2, const std::string &llvmType2) const;
    std::string createLOAD(const std::string &llvmValue1, const std::string &llvmValue2) const;
    std::string createARITHMETIC(instruction::Operation oper, const std::string &llvmValue1,
                                 const std::string &llvmValue2, const std::string &llvmValue3,
                                 const std::string &llvmType23) const;
    std::string createCOMPARISON(instruction::Operation oper, const std::string &llvmValue1,
                                 const std::string &llvmValue2, const std::string &llvmValue3,
                                 const std::string &llvmType23) const;
    std::string createLOGICAL(instruction::Operation oper, const std::string &llvmValue1,
                              const std::string &llvmValue2, const std::string &llvmValue3) const;
    std::string createNOT(const std::string &llvmValue1, const std::string &llvmValue2) const;
    std::string createFNEG(const std::string &llvmValue1, const std::string &llvmValue2) const;
    std::string createSITOFP(const std::string &llvmValue1,
                             const std::string &llvmValue2, const std::string &llvmType2) const;
    std::string createPRINTF(const std::string &llvmValue, const std::string &llvmType) const;
    std::string createPRINTS(const std::string &str, const int sz) const;
    std::string createPUTCHAR(const std::string &llvmValue) const;
    std::string createSCANF(const std::string &llvmValueAddr) const;
    std::string createHALT() const;
    std::string createBR(const std::string &llvmValue) const;
    std::string createBR(const std::string &llvmValue,
                         const std::string &labelCont, const std::string &labelJump) const;
    std::string createRET(const std::string &llvmValue, const std::string &llvmType) const;
    std::string createRET(const std::string &llvmValue) const;
    std::string createRET() const;
    std::string createCALL(const std::string &tcodeFunc, const std::string &llvmValue1,
                           const std::vector<std::string> &llvmArgs) const;
    std::string createCALL(const std::string &tcodeFunc,
                           const std::vector<std::string> &llvmArgs) const;
    std::string createGETELEMENTPTR(const std::string &llvmArrayPointerValue,
                                    const std::string &llvmArrayBaseValue,
                                    const std::string &llvmArrayIndexValue) const;

    void accessValueOfArgument(const std::string &tcodeArgIn,
                               std::string &llvmArgOut, std::string &llvmAccInstr);
    void modifyValueOfArgument(const std::string &tCodeArgIn,
                               std::string &llvmValueOut, std::string &llvmModInstr);

    std::string createNewPrefixedValueWithType(const std::string &llvmValuePrefix,
                                               const std::string &llvmType);
    void bindGlobalValuesWithTypes();
    void bindTCodeLocalValueWithType(const std::string &tcodeArg, const std::string &llvmType);
    void bindPairOfTCodeLocalValuesWithTypes(const std::string &tcodeArg1,
                                             const std::string &tcodeArg2);
    void bindLLVMLocalValueWithType(const std::string &llvmValue, const std::string &llvmType);
    std::string getLLVMTypeOfValue(const std::string &llvmValue) const;

    bool isLLVMAnyIntegerType(const std::string &llvmType) const;
    std::string getLLVMTypeOneIntUp(const std::string &llvmIntType) const;
    bool isLLVMArrayType(const std::string &llvmType) const;
    std::string getLLVMElementOfArrayType(const std::string &llvmArrayType) const;
    std::string getLLVMArrayTypeAsPointerType(const std::string &llvmArrayType) const;
    bool isPointerType(const std::string &llvmType) const;
    std::string getPointerToType(const std::string &llvmType) const;
    std::string getPointedType(const std::string &llvmTypePtr) const;

    void pushTCodeParamCallStack(const std::string &tcodeParam);
    std::string topPopTCodeParamCallStack();
    void pushLLVMParamCallStack(const std::string &llvmParam);
    std::string topPopLLVMParamCallStack();
    bool isEmptyLLVMParamCallStack() const;

    int getAsciiCode(const std::string &s) const;

    std::string llvmComment(const std::string &comm) const;

public:
    LLVMCodeGen(const TypesMgr &Types, const SymTable &Symbols, const code &tCode);
    std::string dumpLLVM();
};
```


#### common/SemErrors.cpp


```cpp
/////////////////////////////////////////////////////////////////
//
//    SemErrors - Semantic errors for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include "SemErrors.h"

#include "antlr4-runtime.h"

#include <iostream>
#include <string>
#include <algorithm>

// using namespace std;

void SemErrors::print()
{
    std::sort(ErrorList.begin(), ErrorList.end(), less);
    for (auto &error : ErrorList)
        error.print();
}

bool SemErrors::less(const ErrorInfo &e1, const ErrorInfo &e2)
{
    if (e1.getLine() != e2.getLine())
        return e1.getLine() < e2.getLine();
    else if (e1.getColumnInLine() != e2.getColumnInLine())
        return e1.getColumnInLine() < e2.getColumnInLine();
    else
        return e1.getMessage() < e2.getMessage();
}

std::size_t SemErrors::getNumberOfSemanticErrors() const
{
    return ErrorList.size();
}

void SemErrors::declaredIdent(antlr4::tree::TerminalNode *node)
{
    ErrorInfo error(node->getSymbol()->getLine(), node->getSymbol()->getCharPositionInLine(), "Identifier '" + node->getSymbol()->getText() + "' already declared.");
    ErrorList.push_back(error);
}

void SemErrors::undeclaredIdent(antlr4::tree::TerminalNode *node)
{
    ErrorInfo error(node->getSymbol()->getLine(), node->getSymbol()->getCharPositionInLine(), "Identifier '" + node->getSymbol()->getText() + "' is undeclared.");
    ErrorList.push_back(error);
}

void SemErrors::incompatibleAssignment(antlr4::tree::TerminalNode *node)
{
    ErrorInfo error(node->getSymbol()->getLine(), node->getSymbol()->getCharPositionInLine(), "Assignment with incompatible types.");
    ErrorList.push_back(error);
}

void SemErrors::nonReferenceableLeftExpr(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Left expression of assignment is not referenceable.");
    ErrorList.push_back(error);
}

void SemErrors::incompatibleOperator(antlr4::Token *tok)
{
    ErrorInfo error(tok->getLine(), tok->getCharPositionInLine(), "Operator '" + tok->getText() + "' with incompatible types.");
    ErrorList.push_back(error);
}

void SemErrors::nonArrayInArrayAccess(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Array access to a non array operand.");
    ErrorList.push_back(error);
}

void SemErrors::nonIntegerIndexInArrayAccess(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Array access with non integer index.");
    ErrorList.push_back(error);
}

void SemErrors::booleanRequired(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Instruction '" + ctx->getStart()->getText() + "' requires a boolean condition.");
    ErrorList.push_back(error);
}

void SemErrors::isNotCallable(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Identifier '" + ctx->getStart()->getText() + "' is not a callable function.");
    ErrorList.push_back(error);
}

void SemErrors::isNotProcedure(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Identifier '" + ctx->getStart()->getText() + "' is not a procedure.");
    ErrorList.push_back(error);
}

void SemErrors::isNotFunction(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Identifier '" + ctx->getStart()->getText() + "' is a void returning function.");
    ErrorList.push_back(error);
}

void SemErrors::numberOfParameters(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "The number of parameters in the call to '" + ctx->getStart()->getText() + "' does not match.");
    ErrorList.push_back(error);
}

void SemErrors::incompatibleParameter(antlr4::ParserRuleContext *pCtx,
                                      unsigned int n,
                                      antlr4::ParserRuleContext *cCtx)
{
    ErrorInfo error(pCtx->getStart()->getLine(), pCtx->getStart()->getCharPositionInLine(), "Parameter #" + std::to_string(n) + " with incompatible types in call to '" + cCtx->getStart()->getText() + "'.");
    ErrorList.push_back(error);
}

void SemErrors::referenceableParameter(antlr4::ParserRuleContext *pCtx,
                                       unsigned int n,
                                       antlr4::ParserRuleContext *cCtx)
{
    ErrorInfo error(pCtx->getStart()->getLine(), pCtx->getStart()->getCharPositionInLine(), "Parameter #" + std::to_string(n) + " is expected to be referenceable in call to '" + cCtx->getStart()->getText() + "'.");
    ErrorList.push_back(error);
}

void SemErrors::incompatibleReturn(antlr4::tree::TerminalNode *node)
{
    ErrorInfo error(node->getSymbol()->getLine(), node->getSymbol()->getCharPositionInLine(), "Return with incompatible type.");
    ErrorList.push_back(error);
}

void SemErrors::readWriteRequireBasic(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Basic type required in '" + ctx->getStart()->getText() + "'.");
    ErrorList.push_back(error);
}

void SemErrors::nonReferenceableExpression(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Referenceable expression required in '" + ctx->getStart()->getText() + "'.");
    ErrorList.push_back(error);
}

void SemErrors::noMainProperlyDeclared(antlr4::ParserRuleContext *ctx)
{
    ErrorInfo error(ctx->getStop()->getLine(), ctx->getStop()->getCharPositionInLine(), "There is no 'main' function properly declared.");
    ErrorList.push_back(error);
}

SemErrors::ErrorInfo::ErrorInfo(std::size_t line, std::size_t coln, std::string message)
    : line{line}, coln{coln}, message{message}
{
}

void SemErrors::ErrorInfo::print() const
{
    std::cout << "Line " << line << ":" << coln << " error: " << message << std::endl;
}

std::size_t SemErrors::ErrorInfo::getLine() const
{
    return line;
}

std::size_t SemErrors::ErrorInfo::getColumnInLine() const
{
    return coln;
}

std::string SemErrors::ErrorInfo::getMessage() const
{
    return message;
}
```


#### common/SemErrors.h


```cpp
/////////////////////////////////////////////////////////////////
//
//    SemErrors - Semantic errors for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"

#include <string>
#include <vector>

// using namespace std;

////////////////////////////////////////////////////////////////
// Class SemErrors: this class contains methods that emit
// semantic error messages with their localization.
// It is used by the semantic visitors:
//   - SymbolsVisitor
//   - TypeCheckVisitor
// Semantic errors emitted are kept in a vector and when the
// typecheck finishes they will be printed (sorted by line/column number)

class SemErrors
{

public:
    // Constructor
    SemErrors() = default;

    // Write the semantic errors ordered by line number
    void print();

    // Accessor to get the number of semantic errors
    std::size_t getNumberOfSemanticErrors() const;

    // Methods that store the error messages
    //   node is the terminal node correspondig to the token IDENT in a declaration
    void declaredIdent(antlr4::tree::TerminalNode *node);
    //   node is the terminal node correspondig to the token IDENT in an expression
    void undeclaredIdent(antlr4::tree::TerminalNode *node);
    //   node is the terminal node correspondig to the token ASSIG
    void incompatibleAssignment(antlr4::tree::TerminalNode *node);
    //   ctx is the node corresponding to the left expression
    void nonReferenceableLeftExpr(antlr4::ParserRuleContext *ctx);
    //   node is the labeled operator token (referenced by op in the grammar)
    void incompatibleOperator(antlr4::Token *node);
    //   ctx is the node corresponding to an array access
    void nonArrayInArrayAccess(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the index expression in an array access
    void nonIntegerIndexInArrayAccess(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the expression
    void booleanRequired(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the function identifier
    void isNotCallable(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the function identifier
    //   This error will not be emitted (productive functions can be called as procedures)
    void isNotProcedure(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the identifier
    void isNotFunction(antlr4::ParserRuleContext *ctx);
    //   ctx is the node corresponding to the function identifier
    void numberOfParameters(antlr4::ParserRuleContext *ctx);
    //   pCtx is actual parameter node
    //   n is the number of argument starting from 1
    //   cCtc is the call node
    void incompatibleParameter(antlr4::ParserRuleContext *pCtx,
                               unsigned int n,
                               antlr4::ParserRuleContext *cCtx);
    //   pCtx is actual parameter node
    //   n is the number of argument starting from 1
    //   cCtc is the call node
    void referenceableParameter(antlr4::ParserRuleContext *pCtx,
                                unsigned int n,
                                antlr4::ParserRuleContext *cCtx);
    //   node is the terminal node correspondig to the token RETURN
    void incompatibleReturn(antlr4::tree::TerminalNode *node);
    //   ctx is the read or write instruction
    void readWriteRequireBasic(antlr4::ParserRuleContext *ctx);
    //   ctx is the instruction that needs a referenceable expression
    void nonReferenceableExpression(antlr4::ParserRuleContext *ctx);
    //   ctx is the program node (grammar start symbol)
    void noMainProperlyDeclared(antlr4::ParserRuleContext *ctx);

private:
    class ErrorInfo
    {
    public:
        ErrorInfo() = delete;
        ErrorInfo(std::size_t line, std::size_t coln, std::string message);
        std::size_t getLine() const;
        std::size_t getColumnInLine() const;
        std::string getMessage() const;
        void print() const;

    private:
        std::size_t line, coln;
        std::string message;
    };

    // List of semantic errors
    std::vector<ErrorInfo> ErrorList;

    // Compare two errors to determine the order (needed in print)
    static bool less(const ErrorInfo &e1, const ErrorInfo &e2);

}; // class SemErrors
```


#### common/SymTable.cpp


```cpp
/////////////////////////////////////////////////////////////////
//
//    SymTable - Symbol table for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include "TypesMgr.h"
#include "SymTable.h"

#include <string>
#include <iostream>

#include <cstddef> // std::size_t
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

// using namespace std;

// Name of the Global Scope
const std::string SymTable::GLOBAL_SCOPE_NAME = "$global$";

// Constructor
SymTable::SymTable(TypesMgr &Types) : Types{Types}
{
}

// Creates a new scope, push its ScopeId in the stack
// and returns this ScopeId.
SymTable::ScopeId SymTable::pushNewScope(const std::string &name)
{
  ScopeId currScope = ScopesVec.size();
  ScopesVec.push_back(ScopeInfo(name));
  ScopeIdsStack.push_back(currScope);
  return currScope;
}

// Pop the stack of scopes
void SymTable::popScope()
{
  assert(not ScopeIdsStack.empty());
  ScopeIdsStack.pop_back();
}

// Push a previously created scope sc and set it as current scope
void SymTable::pushThisScope(ScopeId scope)
{
  assert(scope < ScopesVec.size());
  ScopeIdsStack.push_back(scope);
}

// Returns the current scope.
SymTable::ScopeId SymTable::topScope() const
{
  assert(not ScopeIdsStack.empty());
  return ScopeIdsStack.back();
}

// Returns true if ident occurs in the current scope (top of the stack)
bool SymTable::findInCurrentScope(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  return (ScopesVec[currScope].findSymbol(ident));
}

// Returns an integer >= 0 if ident occurs in some of the scopes
// of the stack. If it it occurs at the top (current scope) returns 0.
// If it occurs in the scope below the top returns 1, and so on.
// Returns -1 if te symbol is not found.
int SymTable::findInStack(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  int d = 0;
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    if (ScopesVec[sc].findSymbol(ident))
      return d;
    ++d;
  }
  return -1;
}

// Adds a new symbol in the current scope.
void SymTable::addLocalVar(const std::string &ident, TypesMgr::TypeId type)
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  ScopesVec[currScope].addLocalVar(ident, type);
}
void SymTable::addParameter(const std::string &ident, TypesMgr::TypeId type)
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  ScopesVec[currScope].addParameter(ident, type);
}

void SymTable::addFunction(const std::string &ident, TypesMgr::TypeId type)
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  ScopesVec[currScope].addFunction(ident, type);
}

// Check the class of a symbol. If not found return false
bool SymTable::isLocalVarClass(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    if (ScopesVec[sc].findSymbol(ident))
      return ScopesVec[sc].isLocalVarClass(ident);
  }
  return false;
}

bool SymTable::isParameterClass(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    if (ScopesVec[sc].findSymbol(ident))
      return ScopesVec[sc].isParameterClass(ident);
  }
  return false;
}

bool SymTable::isFunctionClass(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    if (ScopesVec[sc].findSymbol(ident))
      return ScopesVec[sc].isFunctionClass(ident);
  }
  return false;
}

// Get the TypeId of a symbol. If not found return type 'error'
TypesMgr::TypeId SymTable::getType(const std::string &ident) const
{
  assert(not ScopeIdsStack.empty());
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    if (ScopesVec[sc].findSymbol(ident))
      return ScopesVec[sc].getType(ident);
  }
  return Types.createErrorTy();
}

bool SymTable::noMainProperlyDeclared() const
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  if ((not ScopesVec[currScope].findSymbol("main")) or
      (not ScopesVec[currScope].isFunctionClass("main")))
    return true;
  TypesMgr::TypeId tid = ScopesVec[currScope].getType("main");
  if (Types.isFunctionTy(tid) and
      (Types.getNumOfParameters(tid) == 0) and
      Types.isVoidFunction(tid))
    return false;
  return true;
}

// Given the name of a function, returns its TypeId
TypesMgr::TypeId SymTable::getGlobalFunctionType(const std::string &ident) const
{
  assert(not ScopesVec.empty());
  TypesMgr::TypeId tid = ScopesVec[0].getType(ident);
  return tid;
}

// Given the names of a function and a local symbol, returns its TypeId
TypesMgr::TypeId SymTable::getLocalSymbolType(const std::string &funcName,
                                              const std::string &ident) const
{
  for (std::size_t i = 1; i < ScopesVec.size(); ++i)
  {
    if (ScopesVec[i].getName() == funcName)
    {
      TypesMgr::TypeId tid = ScopesVec[i].getType(ident);
      return tid;
    }
  }
  return Types.createErrorTy();
}

// Writes the contents of the current scope (top of the stack)
// on the standard output.
void SymTable::printCurrentScope() const
{
  assert(not ScopeIdsStack.empty());
  ScopeId currScope = ScopeIdsStack.back();
  assert(currScope < ScopesVec.size());
  ScopesVec[currScope].print(Types);
}

// Write the contents of the symbol table on the standard output
void SymTable::print() const
{
  std::cout << "Contents of symbol table:" << std::endl;
  for (int i = ScopeIdsStack.size() - 1; i >= 0; --i)
  {
    ScopeId sc = ScopeIdsStack[i];
    assert(sc < ScopesVec.size());
    ScopesVec[sc].print(Types);
  }
  std::cout << "----------------" << std::endl;
}

// class SymTable::ScopeInfo ==============================================================

// Constructor
SymTable::ScopeInfo::ScopeInfo(const std::string &name)
    : name{name} {}

// Accessors to work with the attributes: name, SymbolsMap, IdentsList
std::string SymTable::ScopeInfo::getName() const
{
  return name;
}

// Mutators to add symbols to the scope
void SymTable::ScopeInfo::addLocalVar(const std::string &ident, TypesMgr::TypeId type)
{
  assert(SymbolsMap.find(ident) == SymbolsMap.end());
  SymbolsMap[ident] = SymbolInfo::createLocalVar(type);
  IdentsList.push_back(ident);
}
void SymTable::ScopeInfo::addParameter(const std::string &ident, TypesMgr::TypeId type)
{
  assert(SymbolsMap.find(ident) == SymbolsMap.end());
  SymbolsMap[ident] = SymbolInfo::createParameter(type);
  IdentsList.push_back(ident);
}
void SymTable::ScopeInfo::addFunction(const std::string &ident, TypesMgr::TypeId type)
{
  assert(SymbolsMap.find(ident) == SymbolsMap.end());
  SymbolsMap[ident] = SymbolInfo::createFunction(type);
  IdentsList.push_back(ident);
}

// Accessor to check the existence of a symbol
bool SymTable::ScopeInfo::findSymbol(const std::string &ident) const
{
  return (SymbolsMap.find(ident) != SymbolsMap.end());
}

// Accessors to check the class of the symbol. If not found return false
bool SymTable::ScopeInfo::isLocalVarClass(const std::string &ident) const
{
  auto const &it = SymbolsMap.find(ident);
  if (it == SymbolsMap.end())
    return false;
  return it->second.isLocalVarClass();
}
bool SymTable::ScopeInfo::isParameterClass(const std::string &ident) const
{
  auto const &it = SymbolsMap.find(ident);
  if (it == SymbolsMap.end())
    return false;
  return it->second.isParameterClass();
}
bool SymTable::ScopeInfo::isFunctionClass(const std::string &ident) const
{
  auto const &it = SymbolsMap.find(ident);
  if (it == SymbolsMap.end())
    return false;
  return it->second.isFunctionClass();
}

// Accessor to get the TypeId of a symbol. The symbol MUST exist.
TypesMgr::TypeId SymTable::ScopeInfo::getType(const std::string &ident) const
{
  assert(SymbolsMap.find(ident) != SymbolsMap.end());
  auto const &it = SymbolsMap.find(ident);
  return it->second.getType();
}

// Writes the contents of the scope to the standard output.
void SymTable::ScopeInfo::print(TypesMgr &Types) const
{
  std::cout << "---------------- scope name: " << name << std::endl;
  for (auto &id : IdentsList)
  {
    auto const &it = SymbolsMap.find(id);
    std::cout << id << ":" << it->second.class2string();
    if (not it->second.isErrorClass())
    {
      std::cout << "," << Types.to_string(it->second.getType());
    }
    std::cout << std::endl;
  }
}

// class SymTable::ScopeInfo::SymbolInfo ==========================================================

// Constructors
SymTable::ScopeInfo::SymbolInfo::SymbolInfo()
    : classId{ErrorClassId}
{
}
SymTable::ScopeInfo::SymbolInfo::SymbolInfo(SymClassId c, TypesMgr::TypeId tid)
    : classId{c}, type{tid}
{
  assert(FirstSymClassId < c and c < LastSymClassId);
}

// Accessors for working with the attributes: class and type
bool SymTable::ScopeInfo::SymbolInfo::isLocalVarClass() const
{
  return classId == LocalVarId;
}
bool SymTable::ScopeInfo::SymbolInfo::isParameterClass() const
{
  return classId == ParameterId;
}
bool SymTable::ScopeInfo::SymbolInfo::isFunctionClass() const
{
  return classId == FunctionId;
}
bool SymTable::ScopeInfo::SymbolInfo::isErrorClass() const
{
  return classId == ErrorClassId;
}
TypesMgr::TypeId SymTable::ScopeInfo::SymbolInfo::getType() const
{
  return type;
}

// Convert the symbol class to string
std::string SymTable::ScopeInfo::SymbolInfo::class2string() const
{
  switch (classId)
  {
  case LocalVarId:
    return "localVar";
  case ParameterId:
    return "parameter";
  case FunctionId:
    return "function";
  default:
    return "errorClass";
  }
}

// Static methods to create SymbolInfo objects
SymTable::ScopeInfo::SymbolInfo SymTable::ScopeInfo::SymbolInfo::createLocalVar(TypesMgr::TypeId type)
{
  return SymbolInfo(SymClassId::LocalVarId, type);
}
SymTable::ScopeInfo::SymbolInfo SymTable::ScopeInfo::SymbolInfo::createParameter(TypesMgr::TypeId type)
{
  return SymbolInfo(SymClassId::ParameterId, type);
}
SymTable::ScopeInfo::SymbolInfo SymTable::ScopeInfo::SymbolInfo::createFunction(TypesMgr::TypeId type)
{
  return SymbolInfo(SymClassId::FunctionId, type);
}
```


#### common/SymTable.h


```cpp
/////////////////////////////////////////////////////////////////
//
//    SymTable - Symbol table for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include "TypesMgr.h"

#include <string>
#include <map>
#include <vector>

#include <cstddef> // std::size_t
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

// using namespace std;

////////////////////////////////////////////////////////////////
// Class SymTable: stores the symbols declared in the program
// along with the information associated with each one:
//   - its class (the symbol can be a function, a parameter or
//     a local variable)
//   - its type (the TypeId returned by the TypesMgr)
// The symbols are grouped in scopes. In the current version
// of Asl there are two level of scopes: the global and the
// local. The former for the symbols of function names, and
// the latter for symbols declared inside a function:
// parameters and local variables.
// The SymTable uses a 'stack' to keep the current available
// scopes that determines which symbols are visible and
// which are not. Entering in a function will push a new
// scope to the stack and exiting will pop the stack.

class SymTable
{

public:
    // The ScopeId is an index in a vector
    typedef std::size_t ScopeId;

    // Name of the Global Scope
    static const std::string GLOBAL_SCOPE_NAME;

    // Constructor
    SymTable(TypesMgr &Types);
    // Destructor
    ~SymTable() = default;

    // Manage the stack of scopes
    //   - create a new empty scope and push its ScopeId in the stack
    ScopeId pushNewScope(const std::string &name);
    //   - pop the stack of scopes
    void popScope();
    //   - push a previously created scope sc and set it as current scope
    void pushThisScope(ScopeId sc);
    //   - returns the current scope
    ScopeId topScope() const;

    // Methods to find an ident
    //   - in the current scope (top of the stack)
    bool findInCurrentScope(const std::string &ident) const;
    //   - in the whole stack. Returns the number of scopes skipped to
    // find the symbol, or -1 if it is not found
    int findInStack(const std::string &ident) const;

    // Adds a new symbol in the current scope
    void addLocalVar(const std::string &ident, TypesMgr::TypeId type);
    void addParameter(const std::string &ident, TypesMgr::TypeId type);
    void addFunction(const std::string &ident, TypesMgr::TypeId type);

    // Accessors to check the class of the symbol. If not found return false
    bool isLocalVarClass(const std::string &ident) const;
    bool isParameterClass(const std::string &ident) const;
    bool isFunctionClass(const std::string &ident) const;

    // Accessor to get the TypeId of a symbol. If not found return type 'error'
    TypesMgr::TypeId getType(const std::string &ident) const;

    // Check the existence of the "main" function
    bool noMainProperlyDeclared() const;

    // Given the name of a function, returns its TypeId
    TypesMgr::TypeId getGlobalFunctionType(const std::string &ident) const;
    // Given the names of a function and a local symbol, returns its TypeId
    TypesMgr::TypeId getLocalSymbolType(const std::string &funcName,
                                        const std::string &ident) const;

    // Print the symbols of a scope on the standard output
    //   - the symbols of the current scope (top of the stack)
    void printCurrentScope() const;
    //   - the symbols of the whole stack
    void print() const;

private:
    // Forward declaration of class ScopeInfo
    class ScopeInfo;

    // Attributes:
    TypesMgr &Types;
    std::vector<ScopeInfo> ScopesVec;
    std::vector<ScopeId> ScopeIdsStack;

    //////////////////////////////////////////////////////////////////
    // Class ScopeInfo: is declared inside SymTable and is private,
    // so only the SymTable can operate with Scope objects.
    // It keeps the information of the symbols declared is one scope.

    class ScopeInfo
    {
    public:
        // Constructor
        ScopeInfo() = delete;
        ScopeInfo(const std::string &name);

        // Accessor to get the name of the scope
        std::string getName() const;

        // Mutators to add symbols to the scope
        void addLocalVar(const std::string &ident, TypesMgr::TypeId type);
        void addParameter(const std::string &ident, TypesMgr::TypeId type);
        void addFunction(const std::string &ident, TypesMgr::TypeId type);

        // Accessor to check the existence of a symbol
        bool findSymbol(const std::string &ident) const;

        // Accessors to check the class of the symbol. If not found return false
        bool isLocalVarClass(const std::string &ident) const;
        bool isParameterClass(const std::string &ident) const;
        bool isFunctionClass(const std::string &ident) const;

        // Accessor to get the TypeId of a symbol. The symbol MUST exist
        TypesMgr::TypeId getType(const std::string &ident) const;

        // Writes the contents of the scope to the standard output
        void print(TypesMgr &Types) const;

    private:
        // Formard decration of class SymbolInfo
        class SymbolInfo;

        // For the name of the scope
        std::string name;
        // The information associated to each identifier declared in this scope.
        std::map<std::string, SymbolInfo> SymbolsMap;
        // For remember the order in which the Ids where introduced.
        std::vector<std::string> IdentsList;

        //////////////////////////////////////////////////////////////////
        // Class SymbolInfo: is declared inside ScopeInfo and is private,
        // so only the ScopeInfo can operate with SymbolInfo objects.
        // It keeps the information of one symbol: its symbol class
        // (function, parameter or local variable) and its type (TypeId)

        class SymbolInfo
        {
        public:
            enum SymClassId
            {
                FirstSymClassId = -2,
                ErrorClassId = -1, // "error" symbol class
                // Normal symbol classes:
                LocalVarId = 0, // local variables
                ParameterId,    // parameters
                FunctionId,     // functions
                LastSymClassId,
            };

            // Constructors
            SymbolInfo();
            SymbolInfo(SymClassId c, TypesMgr::TypeId tid);

            // Accessors for working with the symbol attributes: class and type
            bool isLocalVarClass() const;
            bool isParameterClass() const;
            bool isFunctionClass() const;
            bool isErrorClass() const;
            TypesMgr::TypeId getType() const;

            // Method to convert a symbol class to its string representation
            std::string class2string() const;

            // Static methods to create SymbolInfo objects
            static SymbolInfo createLocalVar(TypesMgr::TypeId type);
            static SymbolInfo createParameter(TypesMgr::TypeId type);
            static SymbolInfo createFunction(TypesMgr::TypeId type);

        private:
            SymClassId classId;
            TypesMgr::TypeId type;

        }; // class SymbolInfo

    }; // class ScopeInfo

}; // class SymTable
```


#### common/TreeDecoration.cpp


```cpp
//////////////////////////////////////////////////////////////////////
//
//    TreeDecoration - Tree node attributes for
//                     the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "TreeDecoration.h"

#include "TypesMgr.h"
#include "SymTable.h"

#include "antlr4-runtime.h"

#include <string>

// Getters:
SymTable::ScopeId TreeDecoration::getScope(antlr4::ParserRuleContext *ctx)
{
    return ScopeDecor.get(ctx);
}

TypesMgr::TypeId TreeDecoration::getType(antlr4::ParserRuleContext *ctx)
{
    return TypeDecor.get(ctx);
}

bool TreeDecoration::getIsLValue(antlr4::ParserRuleContext *ctx)
{
    return IsLValueDecor.get(ctx);
}

// Setters:
void TreeDecoration::putScope(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s)
{
    ScopeDecor.put(ctx, s);
}

void TreeDecoration::putType(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t)
{
    TypeDecor.put(ctx, t);
}

void TreeDecoration::putIsLValue(antlr4::ParserRuleContext *ctx, bool b)
{
    IsLValueDecor.put(ctx, b);
}
```


#### common/TreeDecoration.h


```cpp
//////////////////////////////////////////////////////////////////////
//
//    TreeDecoration - Tree node attributes for
//                     the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "TypesMgr.h"
#include "SymTable.h"

#include "antlr4-runtime.h"
#include "tree/ParseTreeProperty.h"

// using namespace std;

//////////////////////////////////////////////////////////////////////
// Class TreeDecoration: the nodes of the parser tree generated
// by the antlr4 parser, whose base type is
// antlr4::ParserRuleContext *, can have different attributes.
// TreeDecoration groups all of them, and uses different
// ParseTreeProperty to save this information.
// Currently three kinds of attributes may be present:
//   - scope, for nodes like the program, or functions
//   - type, for expressions or type especification
//   - isLValue, for expressions
// Different visitors set and access these attributes:
//   - SymbolsVisitor     [TypeCheck phase 1]
//       * set and access the scope attribute
//       * set and access the type attribute (in type declarations)
//   - TypeCheckVisitor   [TypeCheck phase 2]
//       * access the scope attribute
//       * set and access the type attribute (in expressions)
//       * set and access the isLValue attribute (in expressions)
//   - CodeGenVisitor     [Code Generation]
//       * access the scope attribute
//       * access the type attribute

class TreeDecoration
{

public:
    TreeDecoration() = default;

    // Getters:
    SymTable::ScopeId getScope(antlr4::ParserRuleContext *ctx);
    TypesMgr::TypeId getType(antlr4::ParserRuleContext *ctx);
    bool getIsLValue(antlr4::ParserRuleContext *ctx);

    // Setters:
    void putScope(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s);
    void putType(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t);
    void putIsLValue(antlr4::ParserRuleContext *ctx, bool b);

private:
    antlr4::tree::ParseTreeProperty<SymTable::ScopeId> ScopeDecor;
    antlr4::tree::ParseTreeProperty<TypesMgr::TypeId> TypeDecor;
    antlr4::tree::ParseTreeProperty<bool> IsLValueDecor;

}; // class TreeDecoration
```


#### common/TypesMgr.cpp


```cpp
/////////////////////////////////////////////////////////////////
//
//    TypesMgr - Type System for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#include "TypesMgr.h"

#include <vector>
#include <string>
#include <iostream>

#include <cstddef> // std::size_t
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

// using namespace std;

// ======================================================================
// class TypesMgr

// ----------------------------------------------------------------------
// constructor

TypesMgr::TypesMgr()
{
    // Prebuilt and insert in TypesVec the Type's of the primitive types
    TypesVec = std::vector<Type>(NumPrimitiveAndErrorTypes);
    TypesVec[ErrorTyId] = Type(TypeKind::ErrorKind);
    TypesVec[IntegerTyId] = Type(TypeKind::IntegerKind);
    TypesVec[FloatTyId] = Type(TypeKind::FloatKind);
    TypesVec[BooleanTyId] = Type(TypeKind::BooleanKind);
    TypesVec[CharacterTyId] = Type(TypeKind::CharacterKind);
    TypesVec[VoidTyId] = Type(TypeKind::VoidKind);
}

// ----------------------------------------------------------------------
// methods to create a Type and return its TypeId

TypesMgr::TypeId TypesMgr::createErrorTy()
{
    return ErrorTyId;
}

TypesMgr::TypeId TypesMgr::createIntegerTy()
{
    return IntegerTyId;
}

TypesMgr::TypeId TypesMgr::createFloatTy()
{
    return FloatTyId;
}

TypesMgr::TypeId TypesMgr::createBooleanTy()
{
    return BooleanTyId;
}

TypesMgr::TypeId TypesMgr::createCharacterTy()
{
    return CharacterTyId;
}

TypesMgr::TypeId TypesMgr::createVoidTy()
{
    return VoidTyId;
}

TypesMgr::TypeId TypesMgr::createFunctionTy(const std::vector<TypeId> &paramsTypes,
                                            TypeId returnType)
{
    TypesVec.push_back(Type(paramsTypes, returnType));
    return TypesVec.size() - 1;
}

TypesMgr::TypeId TypesMgr::createArrayTy(unsigned int size,
                                         TypeId elemType)
{
    TypesVec.push_back(Type{size, elemType});
    return TypesVec.size() - 1;
}

// ----------------------------------------------------------------------
// accessors for working with primitive types

bool TypesMgr::isErrorTy(TypeId tid) const
{
    return tid == ErrorTyId;
}

bool TypesMgr::isIntegerTy(TypeId tid) const
{
    return tid == IntegerTyId;
}

bool TypesMgr::isFloatTy(TypeId tid) const
{
    return tid == FloatTyId;
}

bool TypesMgr::isBooleanTy(TypeId tid) const
{
    return tid == BooleanTyId;
}

bool TypesMgr::isCharacterTy(TypeId tid) const
{
    return tid == CharacterTyId;
}

bool TypesMgr::isVoidTy(TypeId tid) const
{
    return tid == VoidTyId;
}

bool TypesMgr::isNumericTy(TypeId tid) const
{
    return (tid == IntegerTyId or tid == FloatTyId);
}

bool TypesMgr::isPrimitiveTy(TypeId tid) const
{
    return (tid == IntegerTyId or tid == FloatTyId or
            tid == BooleanTyId or tid == CharacterTyId or
            tid == VoidTyId);
}

bool TypesMgr::isPrimitiveNonVoidTy(TypeId tid) const
{
    return (isPrimitiveTy(tid) and not isVoidTy(tid));
}

bool TypesMgr::isCompoundTy(TypeId tid) const
{
    return (isFunctionTy(tid) or isArrayTy(tid));
}

// ----------------------------------------------------------------------
// accessors for working with function types

bool TypesMgr::isFunctionTy(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    return t.isFunctionTy();
}

const std::vector<TypesMgr::TypeId> &TypesMgr::getFuncParamsTypes(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isFunctionTy());
    return t.getFuncParamsTypes();
}

TypesMgr::TypeId TypesMgr::getFuncReturnType(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isFunctionTy());
    return t.getFuncReturnType();
}

std::size_t TypesMgr::getNumOfParameters(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isFunctionTy());
    return t.getNumOfParameters();
}

TypesMgr::TypeId TypesMgr::getParameterType(TypeId tid, unsigned int i) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isFunctionTy() and i < t.getNumOfParameters());
    return t.getParameterType(i);
}

bool TypesMgr::isVoidFunction(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isFunctionTy());
    TypeId tr = t.getFuncReturnType();
    return isVoidTy(tr);
}

// ----------------------------------------------------------------------
// accessors for working with array types

bool TypesMgr::isArrayTy(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    return t.isArrayTy();
}

unsigned int TypesMgr::getArraySize(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isArrayTy());
    return t.getArraySize();
}

TypesMgr::TypeId TypesMgr::getArrayElemType(TypeId tid) const
{
    const Type &t = TypesVec.at(tid);
    assert(t.isArrayTy());
    return t.getArrayElemType();
}

// ----------------------------------------------------------------------
// methods for checking different compatibilities of Types

bool TypesMgr::equalTypes(TypeId tid1, TypeId tid2) const
{
    if (tid1 == tid2)
        return true;
    const Type &t1 = TypesVec.at(tid1);
    const Type &t2 = TypesVec.at(tid2);
    if (t1.getTypeKind() != t2.getTypeKind())
        return false;
    if (t1.isPrimitiveTy() and t2.isPrimitiveTy())
        return true;
    if (t1.isFunctionTy())
    { // or: if (t2.isFunctionTy()) {
        if (t1.getNumOfParameters() != t2.getNumOfParameters())
            return false;
        TypeId tid1_aux;
        TypeId tid2_aux;
        for (unsigned int i = 0; i < t1.getNumOfParameters(); ++i)
        {
            tid1_aux = t1.getParameterType(i);
            tid2_aux = t2.getParameterType(i);
            if (not equalTypes(tid1_aux, tid2_aux))
                return false;
        }
        tid1_aux = t1.getFuncReturnType();
        tid2_aux = t2.getFuncReturnType();
        return equalTypes(tid1_aux, tid2_aux);
    }
    if (t1.isArrayTy())
    { // or: if (t2.isArrayTy()) {
        if (t1.getArraySize() != t2.getArraySize())
        {
            return false;
        }
        TypeId tid1_aux = t1.getArrayElemType();
        TypeId tid2_aux = t2.getArrayElemType();
        return equalTypes(tid1_aux, tid2_aux);
    }
    return false;
}

bool TypesMgr::comparableTypes(TypeId tid1, TypeId tid2,
                               const std::string &op) const
{
    if ((not isPrimitiveTy(tid1)) or (not isPrimitiveTy(tid2)))
        return false;
    if (isNumericTy(tid1) and isNumericTy(tid2))
        return true;
    if (isCharacterTy(tid1) and isCharacterTy(tid2))
        return true;
    if (isBooleanTy(tid1) and isBooleanTy(tid2) and
        (op == "==" or op == "!="))
        return true;
    return false;
}

bool TypesMgr::copyableTypes(TypeId tid1, TypeId tid2) const
{
    if (equalTypes(tid1, tid2))
        return true;
    if (isFloatTy(tid1) and isIntegerTy(tid2))
        return true;
    return false;
}

// ----------------------------------------------------------------------
// method to compute the size of a type (primitive type size = 1)
std::size_t TypesMgr::getSizeOfType(TypeId tid) const
{
    if (isPrimitiveNonVoidTy(tid))
        return 1;
    if (isArrayTy(tid))
    {
        const Type &tArr = TypesVec.at(tid);
        std::size_t nElems = tArr.getArraySize();
        TypeId tElem = tArr.getArrayElemType();
        return nElems * getSizeOfType(tElem);
    }
    return 0;
}

// ----------------------------------------------------------------------
// methods to convert to string and print types

std::string TypesMgr::to_string(TypeId tid) const
{
    if (isPrimitiveTy(tid) or isErrorTy(tid))
    {
        switch (tid)
        {
        case ErrorTyId:
            return "error";
        case IntegerTyId:
            return "integer";
        case FloatTyId:
            return "float";
        case BooleanTyId:
            return "boolean";
        case CharacterTyId:
            return "character";
        case VoidTyId:
            return "void";
        }
    }
    const Type &t = TypesVec.at(tid);
    if (t.isFunctionTy())
    {
        TypeId tid1;
        std::string s = "function<";
        if (t.getNumOfParameters() > 0)
        {
            tid1 = t.getParameterType(0);
            s = s + to_string(tid1);
        }
        for (unsigned int i = 1; i < t.getNumOfParameters(); ++i)
        {
            tid1 = t.getParameterType(i);
            s = s + "," + to_string(tid1);
        }
        tid1 = t.getFuncReturnType();
        s = s + ">:" + to_string(tid1);
        return s;
    }
    else if (t.isArrayTy())
    {
        TypeId tid1;
        std::string s = "array<" + std::to_string(t.getArraySize()) + ",";
        tid1 = t.getArrayElemType();
        s = s + to_string(tid1) + ">";
        return s;
    }
    else
    {
        return "none";
    }
}

void TypesMgr::dump(TypeId tid, std::ostream &os) const
{
    os << to_string(tid);
}

std::string TypesMgr::to_string_basic(TypeId tid) const
{
    if (isPrimitiveTy(tid) or isErrorTy(tid))
    {
        switch (tid)
        {
        case ErrorTyId:
            return "error";
        case IntegerTyId:
            return "integer";
        case FloatTyId:
            return "float";
        case BooleanTyId:
            return "boolean";
        case CharacterTyId:
            return "character";
        case VoidTyId:
            return "void";
        }
    }
    const Type &t = TypesVec.at(tid);
    if (t.isArrayTy())
    {
        TypeId tid1 = t.getArrayElemType();
        return to_string(tid1);
    }
    else
    {
        return "none";
    }
}

// ======================================================================
// class TypesMgr::Type

// ----------------------------------------------------------------------
// constructors

TypesMgr::Type::Type(TypeKind tid) : ID{tid}
{
    assert(TypeKind::FirstPrimitiveKind < ID and
           ID < TypeKind::LastPrimitiveKind);
}

TypesMgr::Type::Type(const std::vector<TypeId> &paramsTypes, TypeId returnType) : ID{TypesMgr::TypeKind::FunctionKind},
                                                                                  funcParamsTy{paramsTypes},
                                                                                  funcReturnTy{returnType}
{
}

TypesMgr::Type::Type(unsigned int arraySize, TypeId arrayElemType) : ID{TypesMgr::TypeKind::ArrayKind},
                                                                     arraySize{arraySize},
                                                                     arrayElemTy{arrayElemType}
{
}

// ----------------------------------------------------------------------
// accesor to get the kind

TypesMgr::TypeKind TypesMgr::Type::getTypeKind() const
{
    return ID;
}

// ----------------------------------------------------------------------
// accessors for working with primitive types

bool TypesMgr::Type::isErrorTy() const
{
    return ID == TypeKind::ErrorKind;
}

bool TypesMgr::Type::isIntegerTy() const
{
    return ID == TypeKind::IntegerKind;
}

bool TypesMgr::Type::isFloatTy() const
{
    return ID == TypeKind::FloatKind;
}

bool TypesMgr::Type::isBooleanTy() const
{
    return ID == TypeKind::BooleanKind;
}

bool TypesMgr::Type::isCharacterTy() const
{
    return ID == TypeKind::CharacterKind;
}

bool TypesMgr::Type::isVoidTy() const
{
    return ID == TypeKind::VoidKind;
}

bool TypesMgr::Type::isNumericTy() const
{
    return (ID == TypeKind::IntegerKind or
            ID == TypeKind::FloatKind);
}

bool TypesMgr::Type::isPrimitiveTy() const
{
    return (ID == TypeKind::IntegerKind or
            ID == TypeKind::FloatKind or
            ID == TypeKind::BooleanKind or
            ID == TypeKind::CharacterKind or
            ID == TypeKind::VoidKind);
}

bool TypesMgr::Type::isPrimitiveNonVoidTy() const
{
    return (isPrimitiveTy() and not isVoidTy());
}

// ----------------------------------------------------------------------
// accessors for working with function types

bool TypesMgr::Type::isFunctionTy() const
{
    return ID == TypeKind::FunctionKind;
}

const std::vector<TypesMgr::TypeId> &TypesMgr::Type::getFuncParamsTypes() const
{
    return funcParamsTy;
}

TypesMgr::TypeId TypesMgr::Type::getFuncReturnType() const
{
    return funcReturnTy;
}

std::size_t TypesMgr::Type::getNumOfParameters() const
{
    return getFuncParamsTypes().size();
}

TypesMgr::TypeId TypesMgr::Type::getParameterType(unsigned int i) const
{
    assert(i < getNumOfParameters());
    return getFuncParamsTypes()[i];
}

bool TypesMgr::Type::isVoidFunction() const
{
    return getFuncReturnType() == TypeKind::VoidKind;
}

// ----------------------------------------------------------------------
// accessors for working with array types

bool TypesMgr::Type::isArrayTy() const
{
    return ID == TypeKind::ArrayKind;
}

unsigned int TypesMgr::Type::getArraySize() const
{
    return arraySize;
}

TypesMgr::TypeId TypesMgr::Type::getArrayElemType() const
{
    return arrayElemTy;
}
```


#### common/TypesMgr.h


```cpp
/////////////////////////////////////////////////////////////////
//
//    TypesMgr - Type System for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <cstddef> // std::size_t

// using namespace std;

////////////////////////////////////////////////////////////////
// Class TypesMgr: creates and stores types, and give access
// to type information.
// When a type is created the TypesMgr returns its TypeId.
// The TypeId is the public way to work with types.
// This TypeMgr works with five kinds of primitive types:
// integer, float, boolean, character and void. Also it
// recognizes two compound types: functions and fixed-size
// arrays. Finally there exist a special type 'error'.

class TypesMgr
{

public:
    // The TypeId is an index in a vector
    typedef std::size_t TypeId;

    // Constructor
    TypesMgr();

    // Methods to create a Type and return its TypeId
    //   - Primitive and error types
    TypeId createErrorTy();
    TypeId createIntegerTy();
    TypeId createFloatTy();
    TypeId createBooleanTy();
    TypeId createCharacterTy();
    TypeId createVoidTy();
    //   - Compound types
    TypeId createFunctionTy(const std::vector<TypeId> &paramsTypes,
                            TypeId returnType);
    TypeId createArrayTy(unsigned int size,
                         TypeId elemType);

    // Accessors to work with primitive and error types
    bool isErrorTy(TypeId tid) const;
    bool isIntegerTy(TypeId tid) const;
    bool isFloatTy(TypeId tid) const;
    bool isBooleanTy(TypeId tid) const;
    bool isCharacterTy(TypeId tid) const;
    bool isVoidTy(TypeId tid) const;
    bool isNumericTy(TypeId tid) const;
    bool isPrimitiveTy(TypeId tid) const;
    bool isPrimitiveNonVoidTy(TypeId tid) const;
    bool isCompoundTy(TypeId tid) const;

    // Accessors to work with function types
    bool isFunctionTy(TypeId tid) const;
    const std::vector<TypeId> &getFuncParamsTypes(TypeId tid) const;
    TypeId getFuncReturnType(TypeId tid) const;
    std::size_t getNumOfParameters(TypeId tid) const;
    TypeId getParameterType(TypeId tid,
                            unsigned int i) const;
    bool isVoidFunction(TypeId tid) const;

    // Accessors to work with array types
    bool isArrayTy(TypeId tid) const;
    unsigned int getArraySize(TypeId tid) const;
    TypeId getArrayElemType(TypeId tid) const;

    // Methods to check different compatibilities of types
    //   - structurally equal?
    bool equalTypes(TypeId tid1, TypeId tid2) const;
    //   - comparable with the relational operator op?
    bool comparableTypes(TypeId tid1, TypeId tid2,
                         const std::string &op) const;
    //   - tidFrom values can be copied to tidTo?
    bool copyableTypes(TypeId tidTo, TypeId tidFrom) const;

    // Method to compute the size of a type (primitive type size = 1)
    std::size_t getSizeOfType(TypeId tid) const;

    // Methods to convert to string and print types.
    std::string to_string(TypeId tidm) const;
    void dump(TypeId tid,
              std::ostream &os = std::cout) const;
    // will return type name for basic types, element type name for arrays, 'none' for functions.
    // useful for GenCode add_var and add_param
    std::string to_string_basic(TypeId tidm) const;

private:
    // Forward declaration of class Type
    class Type;

    // Attributes:
    //   - vector to save the Types
    std::vector<Type> TypesVec;

    // There are eight kinds of types:
    //   - an especial kind error,
    //   - five primitive kinds: integer, float, boolean, character and void
    //   - two compound kinds: function and array
    enum TypeKind
    {
        FirstPrimitiveKind = -1,
        // Primitive/fundamental data types ("error" type is included):
        ErrorKind = 0, // "error" type. MUST BE THE FIRST AND MUST BE ZERO
        IntegerKind,   // integer type
        FloatKind,     // floating point type
        BooleanKind,   // boolean type
        CharacterKind, // char type
        VoidKind,      // void type with no size
        LastPrimitiveKind,
        // Compound data types:
        FunctionKind, // function types
        ArrayKind,    // array types
    };

    // Static attributes:
    //   - the TypeId of ALL the integers created (IntegerTyId) will be
    //     the same (and it is equal to TypeKind::IntegerKind).
    //     Exactly the same for the rest of primitive and error types.
    static const TypeId ErrorTyId = TypeKind::ErrorKind;
    static const TypeId IntegerTyId = TypeKind::IntegerKind;
    static const TypeId FloatTyId = TypeKind::FloatKind;
    static const TypeId BooleanTyId = TypeKind::BooleanKind;
    static const TypeId CharacterTyId = TypeKind::CharacterKind;
    static const TypeId VoidTyId = TypeKind::VoidKind;

    //   - number of primitive and 'error' types
    static const unsigned int NumPrimitiveAndErrorTypes = LastPrimitiveKind - FirstPrimitiveKind - 1;

    //////////////////////////////////////////////////////////////////
    // Class Type: is declared inside TypeMgr and is private,
    // so only the TypeMgr can operate with Type objects.
    // It keeps the information of any type. When a type is
    // compound, the subtypes (for example the types of the parameters
    // of a function, or the type of the elements of an array) are
    // referenced by their respective TypeId's.
    class Type
    {

    public:
        // Constructors for primitive, function and array Types
        Type(TypeKind tid = TypeKind::VoidKind);
        Type(const std::vector<TypeId> &paramsTypes,
             TypeId returnType);
        Type(unsigned int arraySize,
             TypeId arrayElemType);

        // Destructor
        ~Type() = default;

        // Accesor to get the kind
        TypeKind getTypeKind() const;

        // Accessors to work with primitive and 'error' types
        bool isErrorTy() const;
        bool isIntegerTy() const;
        bool isFloatTy() const;
        bool isBooleanTy() const;
        bool isCharacterTy() const;
        bool isVoidTy() const;
        bool isNumericTy() const;
        bool isPrimitiveTy() const;
        bool isPrimitiveNonVoidTy() const;

        // Accessors to work with function types
        bool isFunctionTy() const;
        const std::vector<TypeId> &getFuncParamsTypes() const;
        TypeId getFuncReturnType() const;
        std::size_t getNumOfParameters() const;
        TypeId getParameterType(unsigned int i) const;
        bool isVoidFunction() const;

        // Accessors to work with array types
        bool isArrayTy() const;
        unsigned int getArraySize() const;
        TypeId getArrayElemType() const;

    private:
        // Atributes:
        //   - the kind of type
        TypeKind ID;
        //   - to represent the type of a function:
        std::vector<TypeId> funcParamsTy;
        TypeId funcReturnTy;
        //   - to represent the type of an array:
        unsigned int arraySize;
        TypeId arrayElemTy;

    }; // class Type

}; // class TypesMgr
```
