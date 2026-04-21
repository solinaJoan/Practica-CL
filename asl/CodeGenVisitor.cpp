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
  code my_code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) {
    subroutine subr = std::any_cast<subroutine>(visit(ctxFunc));
    my_code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return my_code;
}

std::any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();
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

  std::vector<var> && lvars = std::any_cast<std::vector<var>>(visit(ctx->declarations()));
  for (auto & onevar : lvars) {
    subr.add_var(onevar);
  }
  instructionList && code = std::any_cast<instructionList>(visit(ctx->statements()));
  // Sempre afegim un push perque sempre fem un pop
  code = code || instruction::PUSH() || instruction(instruction::RETURN());
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
    TypesMgr::TypeId   t1 = getTypeDecor(ctx->type());
    // Hem d'incloure 
    if (Types.isArrayTy(t1)) {
      TypesMgr::TypeId tElem = Types.getArrayElemType(t1);
      std::size_t      sizeElems = Types.getSizeOfType(tElem);
      std::size_t      size = Types.getArraySize(t1)*sizeElems;
      // std::cout << "Mida elements: " << sizeElems << " Mida array: " << Types.getArraySize(t1) << " Mida final: " << size << std::endl; 
      var onevar = var{varID->getText(), Types.to_string(Types.getArrayElemType(t1)), size};
      lvars.push_back(onevar);
    }
    else {
      std::size_t      size = Types.getSizeOfType(t1);
      var onevar = var{varID->getText(), Types.to_string(t1), size};
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
  
  CodeAttribs     && codAtsE1 =  std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  // TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
  CodeAttribs     && codAtsE2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string           addr2 = codAtsE2.addr;
  // std::string           offs2 = codAtsE2.offs;
  instructionList &     code2 = codAtsE2.code;
  // TypesMgr::TypeId tid2 = getTypeDecor(ctx->expr());
  // Si l'offset és diferent a nul, vol dir que teniem una array. Provar si així tambe funcionaria
  //  if (dynamic_cast<AslParser::ArrayLeftExprContext*>(ctx->left_expr())) {
  if (offs1 != "") {
    code = code1 || code2 || instruction::XLOAD(addr1, offs1, addr2);
  } else {
    code = code1 || code2 || instruction::LOAD(addr1, addr2);
  }
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   codeIf = std::any_cast<instructionList>(visit(ctx->statements(0)));
  instructionList &&   codeElse = instructionList();
  if (ctx->ELSE()) {
    codeElse = std::any_cast<instructionList>(visit(ctx->statements(1)));
  }
  std::string label = codeCounters.newLabelIF();
  std::string  labelElse = "else"+label;
  std::string labelEndIf = "endif"+label;
  code = code1 || 
        instruction::FJUMP(addr1, labelElse) || codeIf || instruction::UJUMP(labelEndIf) || 
        instruction::LABEL(labelElse) || codeElse || instruction::LABEL(labelEndIf);
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx){
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;

  instructionList &&   codeStmt = std::any_cast<instructionList>(visit(ctx->statements()));
  std::string label = codeCounters.newLabelWHILE();
  std::string    labelWhile = "while"+label;
  std::string labelEndWhile = "endwhile"+label;
  code = instruction::LABEL(labelWhile) || code1 || instruction::FJUMP(addr1, labelEndWhile) ||
         codeStmt || instruction::UJUMP(labelWhile) || instruction::LABEL(labelEndWhile);
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
  std::string name = ctx->ident()->getText();
  TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());
  for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
    CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr(i)));
    std::string          addr1 = codAtsE.addr;
    instructionList &    codeExpr = codAtsE.code;
    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr(i));
    TypesMgr::TypeId tParam = Types.getParameterType(tFunc, i);

    // Nomes entra a copyable types si tExpr és Integer i tParam és Float
    if (Types.isArrayTy(tParam)) {
      std::string temp = "%" + codeCounters.newTEMP();
      code = code || codeExpr || instruction::ALOAD(temp, addr1);
      push = push || instruction::PUSH(temp);
    } else if (Types.isFloatTy(tParam) and Types.isIntegerTy(tExpr)) {
      std::string tFloat = "%"+codeCounters.newTEMP();
      code = code || codeExpr || instruction::FLOAT(tFloat,addr1); 
      push = push || instruction::PUSH(tFloat);
    } else {
      code = code || codeExpr;
      push = push || instruction::PUSH(addr1);
    }
  }
  code = code || push || instruction::CALL(name);
  // Recuperem el return
  std::string temp = "%"+codeCounters.newTEMP();
  code = code || instruction::POP(temp); 
  
  for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
    code = code || instruction::POP();
  }
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string          addr1 = codAtsE.addr;
  std::string          offs1 = codAtsE.offs;
  instructionList &    code1 = codAtsE.code;
  instructionList &     code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
  if (offs1 != "") {
    std::string temp = "%" + codeCounters.newTEMP();
    if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)) {
      code = code1 || instruction::READI(temp) || instruction::XLOAD(addr1, offs1, temp);
    } else if (Types.isFloatTy(tid1)) {
      code = code1 || instruction::READF(temp) || instruction::XLOAD(addr1, offs1, temp);
    } else if (Types.isCharacterTy(tid1)) {
      code = code1 || instruction::READC(temp) || instruction::XLOAD(addr1, offs1, temp);
    }
  } else {
    if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)) code = code1 || instruction::READI(addr1);
    else if (Types.isFloatTy(tid1)) code = code1 || instruction::READF(addr1);
    else if (Types.isCharacterTy(tid1)) code = code1 || instruction::READC(addr1);
  }
  DEBUG_EXIT();
  return code;
}

std::any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr1 = codAt1.addr;
  // std::string         offs1 = codAt1.offs;
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
  if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)) code = code1 || instruction::WRITEI(addr1);
  else if (Types.isFloatTy(tid1)) code = code1 || instruction::WRITEF(addr1);
  else if (Types.isCharacterTy(tid1)) code = code1 || instruction::WRITEC(addr1);
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
    CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string          addr1 = codAtsE.addr;
    instructionList &    code1 = codAtsE.code;
    code = code1 || instruction::PUSH(addr1);
  }
  std::string temp = "%"+codeCounters.newTEMP();
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
  CodeAttribs     && codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr = codAt.addr;
  instructionList &   code = codAt.code;
  std::string temp = "%"+codeCounters.newTEMP();
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());

  if (Types.isFloatTy(t)) {
    code = code || instruction::FNEG(temp, addr);
  } else {
    code = code || instruction::NEG(temp, addr);
  }
  CodeAttribs codAts(temp, "", code);
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
  // TypesMgr::TypeId  t = getTypeDecor(ctx);
  std::string temp = "%"+codeCounters.newTEMP();
  // Si hi ha algun float, fem la conversió del que no ho sigui
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

    if (ctx->MUL()) {
      code = code || instruction::FMUL(temp, addr1_f, addr2_f);
    } else if (ctx->PLUS()) {
      code = code || instruction::FADD(temp, addr1_f, addr2_f);
    } else if (ctx->DIV()) {
      code = code || instruction::FDIV(temp, addr1_f, addr2_f);
    } else if (ctx->MINUS()) {
      code = code || instruction::FSUB(temp, addr1_f, addr2_f);
    } else if (ctx->MOD()) {
      // Todo
    }
  } else {
    if (ctx->MUL()) {
      code = code || instruction::MUL(temp, addr1, addr2);
    } else if(ctx->PLUS()) {
      code = code || instruction::ADD(temp, addr1, addr2);
    } else if (ctx->DIV()) {
      code = code || instruction::DIV(temp, addr1, addr2);
    } else if (ctx->MINUS()) {
      code = code || instruction::SUB(temp, addr1, addr2);
    } else if (ctx->MOD()) {
      // Todo
    }
  }
  CodeAttribs codAts(temp, "", code);
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
  // TypesMgr::TypeId  t = getTypeDecor(ctx);
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
  code = instruction::CHLOAD(temp, ctx->getText());
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
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
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
  std::string       addrExpr = codAtsExpr.addr;
  instructionList & codeExpr = codAtsExpr.code;

  code = codeIdent || codeExpr;

  TypesMgr::TypeId tIdent = getTypeDecor(ctx->ident());
  if (Types.isArrayTy(tIdent) and Symbols.isParameterClass(addrIdent)) {
    std::string ptr  = "%" + codeCounters.newTEMP();
    code = code || instruction::LOAD(ptr, addrIdent);   
    addrIdent = ptr;
  }

  // Retornem només addr=nom_array, offs=index
  CodeAttribs codAts(addrIdent, addrExpr, code);
  DEBUG_EXIT();
  return codAts;
}

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
