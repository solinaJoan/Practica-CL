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

    if (Types.isVoidTy(tRight)) {
        Errors.isNotFunction(ctx->expr());
    } 
    // Si no son compatibles i no son errors (tractant els arrays correctament), error
    else if (not Types.isErrorTy(tLeft) and not Types.isErrorTy(tRight) and
             not Types.copyableTypes(tLeft, tRight)) { 
        Errors.incompatibleAssignment(ctx->ASSIGN());
    }

    if ((not Types.isErrorTy(tLeft)) and (not getIsLValueDecor(ctx->left_expr()))) {
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
    putTypeDecor(ctx,t);
    putIsLValueDecor(ctx,false);
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
    if (ctx->expr()) {
        visit(ctx->expr());
        TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
        // Hem de comprovar que sigui del mateix tipus que la funció
        if (not Types.isErrorTy(t1) and not Types.isErrorTy(t2) and not Types.copyableTypes(t1, t2))
            Errors.incompatibleReturn(ctx->RETURN());
    } else {
        // Si no hi ha expressió i no es void, també donem error
        if (not Types.isErrorTy(t1) and not Types.isVoidTy(t1))
            Errors.incompatibleReturn(ctx->RETURN());
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArrayLeftExpr(AslParser::ArrayLeftExprContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->array());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->array());
    putTypeDecor(ctx, t1);
    putIsLValueDecor(ctx, true);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIdentLeftExpr(AslParser::IdentLeftExprContext *ctx) {
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
    if (not Types.isErrorTy(t1)) {
        if (not Types.isFunctionTy(t1)) {
            Errors.isNotCallable(ctx->ident());
        } else {
            TypesMgr::TypeId tRet = Types.getFuncReturnType(t1);
            putTypeDecor(ctx, tRet);
            putIsLValueDecor(ctx, false);
        }
    }

    // Si no tenen la mateixa quantitat de paràmetres, error
    std::size_t nParamsFunction = Types.isFunctionTy(t1) ? Types.getNumOfParameters(t1) : 0;
    std::size_t nParamsCall = ctx->expr().size();
    if (Types.isFunctionTy(t1) and nParamsFunction != nParamsCall) {
        Errors.numberOfParameters(ctx->ident());
    }

    // I visitem igualment els paràmetres
    if (ctx->expr().size()) {
        for (std::size_t i = 0; i < nParamsCall; ++i) {
            visit(ctx->expr(i));
            if (i < nParamsFunction) {
                TypesMgr::TypeId tParamFunction = getTypeDecor(ctx->expr(i));
                TypesMgr::TypeId tParamCall = Types.getParameterType(t1, i);
                
                if (not Types.isErrorTy(tParamFunction) and not Types.copyableTypes(tParamCall, tParamFunction)){
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
    if ((not Types.isErrorTy(t)) and (not Types.isNumericTy(t))) {
        Errors.incompatibleOperator(ctx->op);
    } else {
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
    if (ctx->op->getText() == "%") {
        // El mòdul exigeix estrictament enters
        if (((not Types.isErrorTy(t1)) and (not Types.isIntegerTy(t1))) or
            ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2)))) {
                Errors.incompatibleOperator(ctx->op);
        }
        tRes = Types.createIntegerTy();
    }
    else {
        // Multiplicació i divisió permeten qualsevol numèric
        if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or
            ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2)))) {
                Errors.incompatibleOperator(ctx->op);
        }
        if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) {
            tRes = Types.createFloatTy();
        } else {
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

std::any TypeCheckVisitor::visitArrayAccessExpr(AslParser::ArrayAccessExprContext *ctx)
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
    
    if (not Types.isErrorTy(tArray)) {
        if (not Types.isArrayTy(tArray)) {
            Errors.nonArrayInArrayAccess(ctx->ident());
        } else {
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
    if (Symbols.findInStack(ident) == -1) {
        Errors.undeclaredIdent(ctx->ID());
        TypesMgr::TypeId te = Types.createErrorTy();
        putTypeDecor(ctx, te);
        putIsLValueDecor(ctx, true);
    } else {
        TypesMgr::TypeId t1 = Symbols.getType(ident);
        putTypeDecor(ctx, t1);
        if (Symbols.isFunctionClass(ident)) {
            putIsLValueDecor(ctx, false);
        } else {
            putIsLValueDecor(ctx, true);
        }
    }
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitFactorialExpr(AslParser::FactorialExprContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr());
    if (not Types.isIntegerTy(tExpr)) {
        Errors.incompatibleOperator(ctx->op);
    }
    putTypeDecor(ctx, Types.createIntegerTy());
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


bool TypeCheckVisitor::allPrimitiveType(const std::vector<TypesMgr::TypeId> & types) const {
  for (unsigned int i = 0; i < types.size(); ++i) {
    if (not Types.isErrorTy(types[i]) and not Types.isPrimitiveTy(types[i]))
      return false;
  }
  return true;
}

bool TypeCheckVisitor::allSameType(const std::vector<TypesMgr::TypeId> & types) const {
  int firstNonErrorPos = -1;
  for (unsigned int i = 0; i < types.size(); ++i) {
    if (not Types.isErrorTy(types[i])) {
      firstNonErrorPos = i;
      break;
    }
  }
  if (firstNonErrorPos != -1) {
    for (unsigned int i = firstNonErrorPos+1; i < types.size(); ++i) {
      if (not Types.isErrorTy(types[i]) and not Types.equalTypes(types[firstNonErrorPos], types[i]))
        return false;
    }
    return true;
  }
  return true;
}

bool TypeCheckVisitor::allNumericType(const std::vector<TypesMgr::TypeId> & types) const {
  for (unsigned int i = 0; i < types.size(); ++i) {
    if (not Types.isNumericTy(types[i]) and not Types.isErrorTy(types[i]))
      return false;
  }
  return true;
}

TypesMgr::TypeId TypeCheckVisitor::getTypeCoercion (const std::vector<TypesMgr::TypeId> &types) const {
    if (allPrimitiveType(types)) {
        if (allSameType(types)) {
            return types[0];
        } else if (allNumericType(types)) {
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
