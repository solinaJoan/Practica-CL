
// Generated from Asl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, TRY = 11, THROW = 12, CATCH = 13, ENDTRY = 14, 
    NOT = 15, AND = 16, OR = 17, ASSIGN = 18, EQ = 19, NE = 20, LT = 21, 
    LE = 22, GT = 23, GE = 24, PLUS = 25, MINUS = 26, MUL = 27, DIV = 28, 
    MOD = 29, VAR = 30, INT = 31, FLOAT = 32, BOOL = 33, CHAR = 34, IF = 35, 
    THEN = 36, ELSE = 37, ENDIF = 38, WHILE = 39, DO = 40, ENDWHILE = 41, 
    FUNC = 42, ENDFUNC = 43, READ = 44, WRITE = 45, RETURN = 46, ARRAY = 47, 
    OF = 48, BOOLVAL = 49, INTVAL = 50, FLOATVAL = 51, CHARVAL = 52, ID = 53, 
    STRING = 54, COMMENT = 55, WS = 56
  };

  explicit AslLexer(antlr4::CharStream *input);

  ~AslLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

