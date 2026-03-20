
// Generated from Asl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    NOT = 8, AND = 9, OR = 10, ASSIGN = 11, EQ = 12, NE = 13, LT = 14, LE = 15, 
    GT = 16, GE = 17, PLUS = 18, MINUS = 19, MUL = 20, DIV = 21, MOD = 22, 
    VAR = 23, INT = 24, FLOAT = 25, BOOL = 26, CHAR = 27, ANY = 28, ANYCAST = 29, 
    IF = 30, THEN = 31, ELSE = 32, ENDIF = 33, WHILE = 34, DO = 35, ENDWHILE = 36, 
    FUNC = 37, ENDFUNC = 38, READ = 39, WRITE = 40, RETURN = 41, ARRAY = 42, 
    OF = 43, BOOLVAL = 44, INTVAL = 45, FLOATVAL = 46, CHARVAL = 47, ID = 48, 
    STRING = 49, COMMENT = 50, WS = 51
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

