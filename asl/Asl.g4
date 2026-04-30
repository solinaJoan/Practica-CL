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
        | array                                          # arrayAccessExpr
        | op=(PLUS|MINUS) expr                           # unary
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
