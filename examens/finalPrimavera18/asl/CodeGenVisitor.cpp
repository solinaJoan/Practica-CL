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
#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations} {
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId CodeGenVisitor::getCurrentFunctionTy() const {
  return currFunctionType;
}

void CodeGenVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
  currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  code code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) {
    subroutine subr = std::any_cast<subroutine>(visit(ctxFunc));
    code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();
  // Si es d'algun tipus afegim un paràmetre de retorn
  TypesMgr::TypeId tRet = ctx->type() ? getTypeDecor(ctx->type()) : Types.createVoidTy();
  if (!Types.isVoidTy(tRet)) {
      subr.add_param("_result", Types.to_string(tRet), false);
  }
  setCurrentFunctionTy(tRet);
  // Afegim els paràmetres de la funció
  if (ctx->params()) {
    for (std::size_t i = 0; i < ctx->params()->ID().size(); ++i) {
      std::string name = ctx->params()->ID(i)->getText();
      TypesMgr::TypeId   tParam = getTypeDecor(ctx->params()->type(i));
      bool isArray = Types.isArrayTy(tParam);
      if (isArray) {
        subr.add_param(name, Types.to_string(Types.getArrayElemType(tParam)), isArray);
      } else {
        subr.add_param(name, Types.to_string(tParam), isArray);
      }
    }
  }
  // Visitem les declaracions i els statements
  std::vector<var> && lvars = std::any_cast<std::vector<var>>(visit(ctx->declarations()));
  for (auto & onevar : lvars) subr.add_var(onevar);
  instructionList && code = std::any_cast<instructionList>(visit(ctx->statements()));
  // Retorn al final per defecte
  code = code || instruction::RETURN();
  subr.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
  return subr;
}

std::any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  for (auto & varDeclCtx : ctx->variable_decl()) {
    std::vector<var> vars = std::any_cast<std::vector<var>>(visit(varDeclCtx));
    for (auto & var : vars) {
      lvars.push_back(var);
    }
  }
  DEBUG_EXIT();
  return lvars;
}

std::any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  for (auto & varID : ctx->ID()) {
    TypesMgr::TypeId   t = getTypeDecor(ctx->type());
    if (Types.isArrayTy(t)) {
      TypesMgr::TypeId tElem = Types.getArrayElemType(t);
      std::size_t      sizeElems = Types.getSizeOfType(tElem);
      std::size_t      sizeArray = Types.getArraySize(t)*sizeElems;
      var onevar = var{varID->getText(), Types.to_string(Types.getArrayElemType(t)), sizeArray};
      lvars.push_back(onevar);
    } else {
      std::size_t      size = Types.getSizeOfType(t);
      var onevar = var{varID->getText(), Types.to_string(t), size};
      lvars.push_back(onevar);
    }
  }
  DEBUG_EXIT();
  return lvars;
}

std::any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  for (auto stCtx : ctx->statement()) {
    instructionList && codeS =  std::any_cast<instructionList>(visit(stCtx));
    code = code || codeS;
  }
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  
  CodeAttribs     && codAtsLeft =  std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string           addrLeft = codAtsLeft.addr;
  std::string           offsLeft = codAtsLeft.offs;
  instructionList &     codeLeft = codAtsLeft.code;

  CodeAttribs     && codAtsRight = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string           addrRight = codAtsRight.addr;
  instructionList &     codeRight = codAtsRight.code;
  code = codeLeft || codeRight;

  TypesMgr::TypeId tLeft = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId tRight = getTypeDecor(ctx->expr());

  std::string addrRight_c = "%" + codeCounters.newTEMP();

  // Fem el type coercion int-float si cal
  if (Types.isFloatTy(tLeft) and Types.isIntegerTy(tRight)) {
    code = code || instruction::FLOAT(addrRight_c, addrRight);
  } else {
    addrRight_c = addrRight;
  }

  if (Types.isArrayTy(tLeft) and Types.isArrayTy(tRight)) {
    size_t size = Types.getArraySize(tLeft);
    std::string idx = "%" + codeCounters.newTEMP();
    std::string tVal = "%" + codeCounters.newTEMP();
    for (size_t i = 0; i < size; ++i) {
      code = code || instruction::ILOAD(idx, std::to_string(i));
      code = code || instruction::LOADX(tVal, addrRight_c, idx);
      code = code || instruction::XLOAD(addrLeft, idx, tVal);
    }
  } else if (offsLeft == "") {
    code = code || instruction::LOAD(addrLeft, addrRight_c);
  } else {
    code = code || instruction::XLOAD(addrLeft, offsLeft, addrRight_c);
  }
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addrExpr = codAtsExpr.addr;
  instructionList &    codeExpr = codAtsExpr.code;
  instructionList &&   statementsIf = std::any_cast<instructionList>(visit(ctx->statements(0)));
  instructionList &&   statementsElse = instructionList();
  if (ctx->ELSE()) {
    statementsElse = std::any_cast<instructionList>(visit(ctx->statements(1)));
  }
  code = codeExpr;

  std::string label = codeCounters.newLabelIF();
  std::string  labelElse = "else"+label;
  std::string labelEndIf = "endif"+label;
  code = code || instruction::FJUMP(addrExpr, labelElse);
  code = code || statementsIf;
  code = code || instruction::UJUMP(labelEndIf);
  code = code || instruction::LABEL(labelElse);
  code = code || statementsElse;
  code = code || instruction::LABEL(labelEndIf);
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx){
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addrExpr = codAtsExpr.addr;
  instructionList &    codeExpr = codAtsExpr.code;
  instructionList &&   codeStmt = std::any_cast<instructionList>(visit(ctx->statements()));

  std::string label = codeCounters.newLabelWHILE();
  std::string    labelWhile = "while"+label;
  std::string labelEndWhile = "endwhile"+label;

  code = code || instruction::LABEL(labelWhile);
  code = code || codeExpr;
  code = code || instruction::FJUMP(addrExpr, labelEndWhile);
  code = code || codeStmt;
  code = code || instruction::UJUMP(labelWhile);
  code = code || instruction::LABEL(labelEndWhile);
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitFunctionCallStmt(AslParser::FunctionCallStmtContext *ctx){
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->functionCall()));
  instructionList code = codAts.code;
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitFunctionCallExpr(AslParser::FunctionCallExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->functionCall()));
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitFunctionCall(AslParser::FunctionCallContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  instructionList push;
  std::string funcName   = ctx->ident()->getText();
  TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());
  // Fem un push per reservar el retorn de la funcio
  push = instruction::PUSH();  

  // Iterem els paràmetres i els apilem
  for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
    std::string temp = "%" + codeCounters.newTEMP();
    CodeAttribs     && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->expr(i)));
    std::string          addrExpr = codAtsExpr.addr;
    instructionList &    codeExpr = codAtsExpr.code;

    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr(i));
    TypesMgr::TypeId tParam = Types.getParameterType(tFunc, i);
    code = code || codeExpr;
    
    // Push del paràmetre
    if (Types.isArrayTy(tParam) and Symbols.findInCurrentScope(addrExpr)) {
      // Si estem passant una array per paràmetre
      code = code || instruction::ALOAD(temp, addrExpr);
    } else if (Types.isFloatTy(tParam) and Types.isIntegerTy(tExpr)) {
      code = code || instruction::FLOAT(temp, addrExpr); 
    } else {
      temp = addrExpr;
    } 
    push = push || instruction::PUSH(temp);
  }
  // Cridem la funció
  code = code || push || instruction::CALL(funcName);
  // Desapilem els parametres
  for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
    code = code || instruction::POP();
  }
  // Recuperem el valor de retorn
  std::string result = "%"+codeCounters.newTEMP();
  code = code || instruction::POP(result);
  CodeAttribs codAts(result, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string          addrExpr = codAtsExpr.addr;
  std::string          offsExpr = codAtsExpr.offs;
  instructionList &    codeExpr = codAtsExpr.code;
  instructionList &     code = codeExpr;
  TypesMgr::TypeId tExpr = getTypeDecor(ctx->left_expr());
  if (offsExpr != "") {
    std::string temp = "%" + codeCounters.newTEMP();
    if (Types.isIntegerTy(tExpr) or Types.isBooleanTy(tExpr)) {
      code = code || instruction::READI(temp) || instruction::XLOAD(addrExpr, offsExpr, temp);
    } else if (Types.isFloatTy(tExpr)) {
      code = code || instruction::READF(temp) || instruction::XLOAD(addrExpr, offsExpr, temp);
    } else if (Types.isCharacterTy(tExpr)) {
      code = code || instruction::READC(temp) || instruction::XLOAD(addrExpr, offsExpr, temp);
    }
  } else {
    if (Types.isIntegerTy(tExpr) or Types.isBooleanTy(tExpr)) code = code || instruction::READI(addrExpr);
    else if (Types.isFloatTy(tExpr)) code = code || instruction::READF(addrExpr);
    else if (Types.isCharacterTy(tExpr)) code = code || instruction::READC(addrExpr);
  }
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtExpr = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addrExpr = codAtExpr.addr;
  instructionList &   codeExpr = codAtExpr.code;
  instructionList &    code = codeExpr;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
  if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)) code = code || instruction::WRITEI(addrExpr);
  else if (Types.isFloatTy(tid1)) code = code || instruction::WRITEF(addrExpr);
  else if (Types.isCharacterTy(tid1)) code = code || instruction::WRITEC(addrExpr);
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string s = ctx->STRING()->getText();
  code = code || instruction::WRITES(s);
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitReturn(AslParser::ReturnContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  if (ctx->expr()) {
    CodeAttribs && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string   addrExpr = codAtsExpr.addr;
    instructionList & codeExpr = codAtsExpr.code;
    // Hem de fer type coercion int-float si cal
    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr());
    TypesMgr::TypeId tFunc = getCurrentFunctionTy();
    std::string addrExpr_c = "%" + codeCounters.newTEMP();
    code = codeExpr;
    if (Types.isFloatTy(tFunc) and Types.isIntegerTy(tExpr)) {
      code = code || instruction::FLOAT(addrExpr_c, addrExpr);
    } else {
      addrExpr_c = addrExpr;
    }
    code = code || instruction::LOAD("_result", addrExpr_c);
  }
  code = code || instruction::RETURN();
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();

  CodeAttribs && codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string addr = codAt.addr;
  instructionList & code = codAt.code;

  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  std::string result = "%" + codeCounters.newTEMP();

  if (ctx->MINUS()) {
    if (Types.isFloatTy(t)) {
      code = code || instruction::FNEG(result, addr);
    } else {
      code = code || instruction::NEG(result, addr);
    }
  } else {
    result = addr;
  }

  CodeAttribs codAts(result, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitNot(AslParser::NotContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr = codAt.addr;
  instructionList &   code = codAt.code;
  std::string temp = "%"+codeCounters.newTEMP();
  code = code || instruction::NOT(temp, addr);
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  std::string result = "%"+codeCounters.newTEMP();
  std::string tZero = "%"+codeCounters.newTEMP();
  if (Types.isArrayTy(t1) and Types.isArrayTy(t2)) {
    int size = Types.getArraySize(t1);
    std::string idx = "%"+codeCounters.newTEMP();
    std::string tA_i = "%"+codeCounters.newTEMP();
    std::string tB_i = "%"+codeCounters.newTEMP();
    std::string temp = "%"+codeCounters.newTEMP();
    if (Types.isIntegerTy(Types.getArrayElemType(t1))) code = code || instruction::ILOAD(result, "0");
    else code = code || instruction::FLOAD(result, "0.0");
    for (int i = 0; i < size; ++i) {
      code = code || instruction::ILOAD(idx, std::to_string(i));
      code = code || instruction::LOADX(tA_i, addr1, idx);
      code = code || instruction::LOADX(tB_i, addr2, idx);
      if (Types.isIntegerTy(Types.getArrayElemType(t1))) {
        code = code || instruction::MUL(temp, tA_i, tB_i);
        code = code || instruction::ADD(result, result, temp);
      } else {
        code = code || instruction::FMUL(temp, tA_i, tB_i);
        code = code || instruction::FADD(result, result, temp);
      } 
    }
  } else {
    // Si hi ha algun float, fem la conversió del que no ho sigui
    if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) {
      std::string tZero_f = "%"+codeCounters.newTEMP();
      std::string addr1_f = addr1;
      std::string addr2_f = addr2;
      if (!Types.isFloatTy(t1)) {
          addr1_f = "%" + codeCounters.newTEMP();
          code = code || instruction::FLOAT(addr1_f, addr1);
      }
      if (!Types.isFloatTy(t2)) {
          addr2_f = "%" + codeCounters.newTEMP();
          code = code || instruction::FLOAT(addr2_f, addr2);
      }

      if (ctx->MUL()) {
        code = code || instruction::FMUL(result, addr1_f, addr2_f);
      } else if (ctx->PLUS()) {
        code = code || instruction::FADD(result, addr1_f, addr2_f);
      } else if (ctx->DIV()) {
        std::string div_by_zero_OK = "div_0_OK_label" + codeCounters.newLabelIF();
        code = code || instruction::FLOAD(tZero_f, "0.0");
        code = code || instruction::FEQ(result, addr2_f, tZero_f);
        code = code || instruction::FJUMP(result, div_by_zero_OK);
        code = code || instruction::HALT(code::INVALID_FLOAT_OPERAND);
        code = code || instruction::LABEL(div_by_zero_OK);
        code = code || instruction::FDIV(result, addr1_f, addr2_f);
      } else if (ctx->MINUS()) {
        code = code || instruction::FSUB(result, addr1_f, addr2_f);
      } 
    } else {
      if (ctx->MUL()) {
        code = code || instruction::MUL(result, addr1, addr2);
      } else if(ctx->PLUS()) {
        code = code || instruction::ADD(result, addr1, addr2);
      } else if (ctx->DIV()) {
        std::string div_by_zero_OK = "div_0_OK_label" + codeCounters.newLabelIF();
        code = code || instruction::ILOAD(tZero, "0");
        code = code || instruction::EQ(result, addr2, tZero);
        code = code || instruction::FJUMP(result, div_by_zero_OK);
        code = code || instruction::HALT(code::INVALID_INTEGER_OPERAND);
        code = code || instruction::LABEL(div_by_zero_OK);
        code = code || instruction::DIV(result, addr1, addr2);
      } else if (ctx->MINUS()) {
        code = code || instruction::SUB(result, addr1, addr2);
      } else if (ctx->MOD()) {
        // x%y
        //                result = x/y                                   result = y*result                    result = x-result
        std::string div_by_zero_OK = "div_0_OK_label" + codeCounters.newLabelIF();
        // Si es zero donem error
        code = code || instruction::ILOAD(tZero, "0");
        code = code || instruction::EQ(result, addr2, tZero);
        code = code || instruction::FJUMP(result, div_by_zero_OK);
        code = code || instruction::HALT(code::INVALID_INTEGER_OPERAND);
        code = code || instruction::LABEL(div_by_zero_OK);
        code = code || instruction::DIV(result, addr1, addr2); 
        code = code || instruction::MUL(result, addr2, result);
        code = code || instruction::SUB(result,addr1,result);
      }
    }
  }
  CodeAttribs codAts(result, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  
  std::string temp = "%"+codeCounters.newTEMP();
  if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) {
    std::string addr1_f = addr1;
    std::string addr2_f = addr2;
    if (!Types.isFloatTy(t1)) {
        addr1_f = "%" + codeCounters.newTEMP();
        code = code || instruction::FLOAT(addr1_f, addr1);
    }
    if (!Types.isFloatTy(t2)) {
        addr2_f = "%" + codeCounters.newTEMP();
        code = code || instruction::FLOAT(addr2_f, addr2);
    }

    if (ctx->EQ()) {
      code = code || instruction::FEQ(temp, addr1_f, addr2_f);
    } else if (ctx->NE()) {
      code = code || instruction::FEQ(temp, addr1_f, addr2_f) || instruction::NOT(temp, temp);
    } else if (ctx->LT()) {
      code = code || instruction::FLT(temp, addr1_f, addr2_f);
    } else if (ctx->LE()) {
      code = code || instruction::FLE(temp, addr1_f, addr2_f);
    } else if (ctx->GT()) {
      code = code || instruction::FLE(temp, addr1_f, addr2_f) || instruction::NOT(temp, temp);
    } else if (ctx->GE()) {
      code = code || instruction::FLT(temp, addr1_f, addr2_f) || instruction::NOT(temp, temp);
    }
  }
  else {
    if (ctx->EQ()) {
      code = code || instruction::EQ(temp, addr1, addr2);
    } else if (ctx->NE()) {
      code = code || instruction::EQ(temp, addr1, addr2) || instruction::NOT(temp, temp);
    } else if (ctx->LT()) {
      code = code || instruction::LT(temp, addr1, addr2);
    } else if (ctx->LE()) {
      code = code || instruction::LE(temp, addr1, addr2);
    } else if (ctx->GT()) {
      code = code || instruction::LE(temp, addr1, addr2) || instruction::NOT(temp, temp);
    } else if (ctx->GE()) {
      code = code || instruction::LT(temp, addr1, addr2) || instruction::NOT(temp, temp);
    }
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitLogic(AslParser::LogicContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->AND()) {
    code = code || instruction::AND(temp, addr1, addr2);
  } else if (ctx->OR()) {
    code = code || instruction::OR(temp, addr1, addr2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitIntVal(AslParser::IntValContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  code = instruction::ILOAD(temp, ctx->getText());
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitFloatVal(AslParser::FloatValContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  code = instruction::FLOAD(temp, ctx->getText());
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitBoolVal(AslParser::BoolValContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  std::string value = (ctx->getText() == "true") ? "1" : "0";
  code = instruction::ILOAD(temp, value);
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitCharVal(AslParser::CharValContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  std::string text = ctx->CHARVAL()->getText();
  std::string strVal = text.substr(1, text.size() - 2);
  code = instruction::CHLOAD(temp, strVal);
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->children[0]));
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  std::string addrIdent = ctx->ID()->getText();
  instructionList code;
  TypesMgr::TypeId tIdent = getTypeDecor(ctx);
  if (Types.isArrayTy(tIdent) and Symbols.isParameterClass(addrIdent)) {
    std::string temp  = "%" + codeCounters.newTEMP();
    code = instruction::LOAD(temp, addrIdent);   
    addrIdent = temp;
  }
  CodeAttribs codAts(addrIdent, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->array()));
  DEBUG_EXIT();
  return codAts; 
}

std::any CodeGenVisitor::visitArrayAccessExpr(AslParser::ArrayAccessExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->array()));
  std::string addrArray = codAts.addr;
  std::string addrIndex = codAts.offs;
  instructionList code = codAts.code;
  std::string temp = "%" + codeCounters.newTEMP();
  code = code || instruction::LOADX(temp, addrArray, addrIndex);

  CodeAttribs codAtsResult(temp, "", code);
  DEBUG_EXIT();
  return codAtsResult;
}

std::any CodeGenVisitor::visitArray(AslParser::ArrayContext *ctx) {
  DEBUG_ENTER();
  instructionList code;

  CodeAttribs && codAtsIdent = std::any_cast<CodeAttribs>(visit(ctx->ident()));
  std::string       addrIdent = codAtsIdent.addr;
  instructionList & codeIdent = codAtsIdent.code;

  CodeAttribs && codAtsExpr = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string       addrIdx = codAtsExpr.addr;
  instructionList & codeExpr = codAtsExpr.code;
  code = codeIdent || codeExpr;

  TypesMgr::TypeId tArray = getTypeDecor(ctx->ident());
  std::size_t arraySize = Types.getArraySize(tArray);

  std::string tArraySize = "%" + codeCounters.newTEMP();
  std::string tZero = "%" + codeCounters.newTEMP();
  std::string LT_size = "%" + codeCounters.newTEMP();
  std::string GT_0 = "%" + codeCounters.newTEMP();
  std::string jumpCondition = "%" + codeCounters.newTEMP();
  std::string label = codeCounters.newLabelIF();
  std::string LTSizeLabel = "LTSize"+label;
  std::string GTZeroLabel = "GTZero"+label;

  code = code || instruction::ILOAD(tArraySize, std::to_string(arraySize));
  code = code || instruction::ILOAD(tZero, "0");
  code = code || instruction::LT(LT_size, addrIdx, tArraySize);
  code = code || instruction::NOT(LT_size, LT_size);
  code = code || instruction::FJUMP(LT_size, LTSizeLabel);
  code = code || instruction::HALT(code::INDEX_OUT_OF_RANGE);
  code = code || instruction::LABEL(LTSizeLabel);
  code = code || instruction::LE(GT_0, tZero, addrIdx);
  code = code || instruction::NOT(GT_0, GT_0);
  code = code || instruction::FJUMP(GT_0, GTZeroLabel);
  code = code || instruction::HALT(code::INDEX_OUT_OF_RANGE);
  code = code || instruction::LABEL(GTZeroLabel);

  // Retornem només addr=nom_array, offs=index
  CodeAttribs codAts(addrIdent, addrIdx, code);
  DEBUG_EXIT();
  return codAts;
}

// std::any CodeGenVisitor::visitXXX(AslParser::XXXContext *ctx) {
//   DEBUG_ENTER();
//   instructionList code;
//   CodeAttribs     && codAtsE =  std::any_cast<CodeAttribs>(visit(ctx->expr()));
//   std::string           addrE = codAtsE.addr;
//   std::string           offsE = codAtsE.offs;
//   instructionList &     codeE = codAtsE.code;
//   code = code || codeE;

//   instructionList && codeStatements =  std::any_cast<instructionList>(visit(ctx->statements()));

//   TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr());
//   std::string temp = "%" + codeCounters.newTEMP();

//   // std::string label = codeCounters.newLabelIF();
//   // std::string  labelElse = "else"+label;
//   // std::string labelEndIf = "endif"+label;

//   // std::string label = codeCounters.newLabelWHILE();
//   // std::string    labelWhile = "while"+label;
//   // std::string labelEndWhile = "endwhile"+label;
//   DEBUG_EXIT();
//   return code;
// }


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getType(ctx);
}


// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList & code) :
  addr{addr}, offs{offs}, code{code} {
}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList && code) :
  addr{addr}, offs{offs}, code{code} {
}
