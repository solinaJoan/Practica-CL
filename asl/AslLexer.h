
// Generated from Asl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, NOT = 6, AND = 7, 
    OR = 8, ASSIGN = 9, EQ = 10, NE = 11, LT = 12, LE = 13, GT = 14, GE = 15, 
    PLUS = 16, MINUS = 17, MUL = 18, DIV = 19, VAR = 20, INT = 21, FLOAT = 22, 
    BOOL = 23, CHAR = 24, IF = 25, THEN = 26, ELSE = 27, ENDIF = 28, WHILE = 29, 
    DO = 30, ENDWHILE = 31, FUNC = 32, ENDFUNC = 33, READ = 34, WRITE = 35, 
    RETURN = 36, BOOLVAL = 37, INTVAL = 38, FLOATVAL = 39, CHARVAL = 40, 
    ID = 41, STRING = 42, COMMENT = 43, WS = 44
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

