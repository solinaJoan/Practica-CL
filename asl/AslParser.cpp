
// Generated from Asl.g4 by ANTLR 4.13.2


#include "AslVisitor.h"

#include "AslParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct AslParserStaticData final {
  AslParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AslParserStaticData(const AslParserStaticData&) = delete;
  AslParserStaticData(AslParserStaticData&&) = delete;
  AslParserStaticData& operator=(const AslParserStaticData&) = delete;
  AslParserStaticData& operator=(AslParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag aslParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<AslParserStaticData> aslParserStaticData = nullptr;

void aslParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (aslParserStaticData != nullptr) {
    return;
  }
#else
  assert(aslParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<AslParserStaticData>(
    std::vector<std::string>{
      "program", "function", "declarations", "variable_decl", "type", "statements", 
      "statement", "left_expr", "expr", "ident", "params"
    },
    std::vector<std::string>{
      "", "'('", "')'", "':'", "','", "';'", "'not'", "'and'", "'or'", "'='", 
      "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", "'+'", "'-'", "'*'", 
      "'/'", "'var'", "'int'", "'float'", "'bool'", "'char'", "'if'", "'then'", 
      "'else'", "'endif'", "'while'", "'do'", "'endwhile'", "'func'", "'endfunc'", 
      "'read'", "'write'", "'return'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "NOT", "AND", "OR", "ASSIGN", "EQ", "NE", 
      "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MUL", "DIV", "VAR", "INT", 
      "FLOAT", "BOOL", "CHAR", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO", 
      "ENDWHILE", "FUNC", "ENDFUNC", "READ", "WRITE", "RETURN", "BOOLVAL", 
      "INTVAL", "FLOATVAL", "CHARVAL", "ID", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,44,168,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,4,0,24,8,0,11,0,12,0,25,1,0,1,0,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,37,8,1,1,1,1,1,1,1,1,1,1,2,5,2,44,8,2,10,
  	2,12,2,47,9,2,1,3,1,3,1,3,1,3,5,3,53,8,3,10,3,12,3,56,9,3,1,3,1,3,1,3,
  	1,4,1,4,1,5,5,5,64,8,5,10,5,12,5,67,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,3,6,80,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,109,
  	8,6,1,6,3,6,112,8,6,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,3,8,130,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,5,8,144,8,8,10,8,12,8,147,9,8,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,10,5,10,158,8,10,10,10,12,10,161,9,10,5,10,163,8,10,10,10,12,10,
  	166,9,10,1,10,0,1,16,11,0,2,4,6,8,10,12,14,16,18,20,0,5,1,0,21,24,1,0,
  	18,19,1,0,16,17,1,0,10,15,1,0,7,8,183,0,23,1,0,0,0,2,29,1,0,0,0,4,45,
  	1,0,0,0,6,48,1,0,0,0,8,60,1,0,0,0,10,65,1,0,0,0,12,111,1,0,0,0,14,113,
  	1,0,0,0,16,129,1,0,0,0,18,148,1,0,0,0,20,164,1,0,0,0,22,24,3,2,1,0,23,
  	22,1,0,0,0,24,25,1,0,0,0,25,23,1,0,0,0,25,26,1,0,0,0,26,27,1,0,0,0,27,
  	28,5,0,0,1,28,1,1,0,0,0,29,30,5,32,0,0,30,31,5,41,0,0,31,32,5,1,0,0,32,
  	33,3,20,10,0,33,36,5,2,0,0,34,35,5,3,0,0,35,37,3,8,4,0,36,34,1,0,0,0,
  	36,37,1,0,0,0,37,38,1,0,0,0,38,39,3,4,2,0,39,40,3,10,5,0,40,41,5,33,0,
  	0,41,3,1,0,0,0,42,44,3,6,3,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,
  	0,45,46,1,0,0,0,46,5,1,0,0,0,47,45,1,0,0,0,48,49,5,20,0,0,49,54,5,41,
  	0,0,50,51,5,4,0,0,51,53,5,41,0,0,52,50,1,0,0,0,53,56,1,0,0,0,54,52,1,
  	0,0,0,54,55,1,0,0,0,55,57,1,0,0,0,56,54,1,0,0,0,57,58,5,3,0,0,58,59,3,
  	8,4,0,59,7,1,0,0,0,60,61,7,0,0,0,61,9,1,0,0,0,62,64,3,12,6,0,63,62,1,
  	0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,11,1,0,0,0,67,65,1,
  	0,0,0,68,69,3,14,7,0,69,70,5,9,0,0,70,71,3,16,8,0,71,72,5,5,0,0,72,112,
  	1,0,0,0,73,74,5,25,0,0,74,75,3,16,8,0,75,76,5,26,0,0,76,79,3,10,5,0,77,
  	78,5,27,0,0,78,80,3,10,5,0,79,77,1,0,0,0,79,80,1,0,0,0,80,81,1,0,0,0,
  	81,82,5,28,0,0,82,112,1,0,0,0,83,84,5,29,0,0,84,85,3,16,8,0,85,86,5,30,
  	0,0,86,87,3,10,5,0,87,88,5,31,0,0,88,112,1,0,0,0,89,90,3,18,9,0,90,91,
  	5,1,0,0,91,92,3,20,10,0,92,93,5,2,0,0,93,94,5,5,0,0,94,112,1,0,0,0,95,
  	96,5,34,0,0,96,97,3,14,7,0,97,98,5,5,0,0,98,112,1,0,0,0,99,100,5,35,0,
  	0,100,101,3,16,8,0,101,102,5,5,0,0,102,112,1,0,0,0,103,104,5,35,0,0,104,
  	105,5,42,0,0,105,112,5,5,0,0,106,108,5,36,0,0,107,109,3,16,8,0,108,107,
  	1,0,0,0,108,109,1,0,0,0,109,110,1,0,0,0,110,112,5,5,0,0,111,68,1,0,0,
  	0,111,73,1,0,0,0,111,83,1,0,0,0,111,89,1,0,0,0,111,95,1,0,0,0,111,99,
  	1,0,0,0,111,103,1,0,0,0,111,106,1,0,0,0,112,13,1,0,0,0,113,114,3,18,9,
  	0,114,15,1,0,0,0,115,116,6,8,-1,0,116,117,5,1,0,0,117,118,3,16,8,0,118,
  	119,5,2,0,0,119,130,1,0,0,0,120,121,5,17,0,0,121,130,3,16,8,11,122,123,
  	5,6,0,0,123,130,3,16,8,7,124,130,5,38,0,0,125,130,5,39,0,0,126,130,5,
  	37,0,0,127,130,5,40,0,0,128,130,3,18,9,0,129,115,1,0,0,0,129,120,1,0,
  	0,0,129,122,1,0,0,0,129,124,1,0,0,0,129,125,1,0,0,0,129,126,1,0,0,0,129,
  	127,1,0,0,0,129,128,1,0,0,0,130,145,1,0,0,0,131,132,10,10,0,0,132,133,
  	7,1,0,0,133,144,3,16,8,11,134,135,10,9,0,0,135,136,7,2,0,0,136,144,3,
  	16,8,10,137,138,10,8,0,0,138,139,7,3,0,0,139,144,3,16,8,9,140,141,10,
  	6,0,0,141,142,7,4,0,0,142,144,3,16,8,7,143,131,1,0,0,0,143,134,1,0,0,
  	0,143,137,1,0,0,0,143,140,1,0,0,0,144,147,1,0,0,0,145,143,1,0,0,0,145,
  	146,1,0,0,0,146,17,1,0,0,0,147,145,1,0,0,0,148,149,5,41,0,0,149,19,1,
  	0,0,0,150,151,5,41,0,0,151,152,5,3,0,0,152,159,3,8,4,0,153,154,5,4,0,
  	0,154,155,5,41,0,0,155,156,5,3,0,0,156,158,3,8,4,0,157,153,1,0,0,0,158,
  	161,1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,163,1,0,0,0,161,159,1,
  	0,0,0,162,150,1,0,0,0,163,166,1,0,0,0,164,162,1,0,0,0,164,165,1,0,0,0,
  	165,21,1,0,0,0,166,164,1,0,0,0,13,25,36,45,54,65,79,108,111,129,143,145,
  	159,164
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  aslParserStaticData = std::move(staticData);
}

}

AslParser::AslParser(TokenStream *input) : AslParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

AslParser::AslParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  AslParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *aslParserStaticData->atn, aslParserStaticData->decisionToDFA, aslParserStaticData->sharedContextCache, options);
}

AslParser::~AslParser() {
  delete _interpreter;
}

const atn::ATN& AslParser::getATN() const {
  return *aslParserStaticData->atn;
}

std::string AslParser::getGrammarFileName() const {
  return "Asl.g4";
}

const std::vector<std::string>& AslParser::getRuleNames() const {
  return aslParserStaticData->ruleNames;
}

const dfa::Vocabulary& AslParser::getVocabulary() const {
  return aslParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView AslParser::getSerializedATN() const {
  return aslParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

AslParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::ProgramContext::EOF() {
  return getToken(AslParser::EOF, 0);
}

std::vector<AslParser::FunctionContext *> AslParser::ProgramContext::function() {
  return getRuleContexts<AslParser::FunctionContext>();
}

AslParser::FunctionContext* AslParser::ProgramContext::function(size_t i) {
  return getRuleContext<AslParser::FunctionContext>(i);
}


size_t AslParser::ProgramContext::getRuleIndex() const {
  return AslParser::RuleProgram;
}


std::any AslParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ProgramContext* AslParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, AslParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(22);
      function();
      setState(25); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == AslParser::FUNC);
    setState(27);
    match(AslParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

AslParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::FunctionContext::FUNC() {
  return getToken(AslParser::FUNC, 0);
}

tree::TerminalNode* AslParser::FunctionContext::ID() {
  return getToken(AslParser::ID, 0);
}

AslParser::ParamsContext* AslParser::FunctionContext::params() {
  return getRuleContext<AslParser::ParamsContext>(0);
}

AslParser::DeclarationsContext* AslParser::FunctionContext::declarations() {
  return getRuleContext<AslParser::DeclarationsContext>(0);
}

AslParser::StatementsContext* AslParser::FunctionContext::statements() {
  return getRuleContext<AslParser::StatementsContext>(0);
}

tree::TerminalNode* AslParser::FunctionContext::ENDFUNC() {
  return getToken(AslParser::ENDFUNC, 0);
}

AslParser::TypeContext* AslParser::FunctionContext::type() {
  return getRuleContext<AslParser::TypeContext>(0);
}


size_t AslParser::FunctionContext::getRuleIndex() const {
  return AslParser::RuleFunction;
}


std::any AslParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

AslParser::FunctionContext* AslParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 2, AslParser::RuleFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(AslParser::FUNC);
    setState(30);
    match(AslParser::ID);
    setState(31);
    match(AslParser::T__0);
    setState(32);
    params();
    setState(33);
    match(AslParser::T__1);
    setState(36);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AslParser::T__2) {
      setState(34);
      match(AslParser::T__2);
      setState(35);
      type();
    }
    setState(38);
    declarations();
    setState(39);
    statements();
    setState(40);
    match(AslParser::ENDFUNC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationsContext ------------------------------------------------------------------

AslParser::DeclarationsContext::DeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AslParser::Variable_declContext *> AslParser::DeclarationsContext::variable_decl() {
  return getRuleContexts<AslParser::Variable_declContext>();
}

AslParser::Variable_declContext* AslParser::DeclarationsContext::variable_decl(size_t i) {
  return getRuleContext<AslParser::Variable_declContext>(i);
}


size_t AslParser::DeclarationsContext::getRuleIndex() const {
  return AslParser::RuleDeclarations;
}


std::any AslParser::DeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitDeclarations(this);
  else
    return visitor->visitChildren(this);
}

AslParser::DeclarationsContext* AslParser::declarations() {
  DeclarationsContext *_localctx = _tracker.createInstance<DeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 4, AslParser::RuleDeclarations);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::VAR) {
      setState(42);
      variable_decl();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

AslParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::Variable_declContext::VAR() {
  return getToken(AslParser::VAR, 0);
}

std::vector<tree::TerminalNode *> AslParser::Variable_declContext::ID() {
  return getTokens(AslParser::ID);
}

tree::TerminalNode* AslParser::Variable_declContext::ID(size_t i) {
  return getToken(AslParser::ID, i);
}

AslParser::TypeContext* AslParser::Variable_declContext::type() {
  return getRuleContext<AslParser::TypeContext>(0);
}


size_t AslParser::Variable_declContext::getRuleIndex() const {
  return AslParser::RuleVariable_decl;
}


std::any AslParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

AslParser::Variable_declContext* AslParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 6, AslParser::RuleVariable_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    match(AslParser::VAR);
    setState(49);
    match(AslParser::ID);
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::T__3) {
      setState(50);
      match(AslParser::T__3);
      setState(51);
      match(AslParser::ID);
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    match(AslParser::T__2);
    setState(58);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

AslParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::TypeContext::INT() {
  return getToken(AslParser::INT, 0);
}

tree::TerminalNode* AslParser::TypeContext::FLOAT() {
  return getToken(AslParser::FLOAT, 0);
}

tree::TerminalNode* AslParser::TypeContext::BOOL() {
  return getToken(AslParser::BOOL, 0);
}

tree::TerminalNode* AslParser::TypeContext::CHAR() {
  return getToken(AslParser::CHAR, 0);
}


size_t AslParser::TypeContext::getRuleIndex() const {
  return AslParser::RuleType;
}


std::any AslParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

AslParser::TypeContext* AslParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 8, AslParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 31457280) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

AslParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AslParser::StatementContext *> AslParser::StatementsContext::statement() {
  return getRuleContexts<AslParser::StatementContext>();
}

AslParser::StatementContext* AslParser::StatementsContext::statement(size_t i) {
  return getRuleContext<AslParser::StatementContext>(i);
}


size_t AslParser::StatementsContext::getRuleIndex() const {
  return AslParser::RuleStatements;
}


std::any AslParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

AslParser::StatementsContext* AslParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 10, AslParser::RuleStatements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2319852765184) != 0)) {
      setState(62);
      statement();
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

AslParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t AslParser::StatementContext::getRuleIndex() const {
  return AslParser::RuleStatement;
}

void AslParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ProcCallContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ProcCallContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

AslParser::ParamsContext* AslParser::ProcCallContext::params() {
  return getRuleContext<AslParser::ParamsContext>(0);
}

AslParser::ProcCallContext::ProcCallContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::ProcCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitProcCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WriteExprContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::WriteExprContext::WRITE() {
  return getToken(AslParser::WRITE, 0);
}

AslParser::ExprContext* AslParser::WriteExprContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::WriteExprContext::WriteExprContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::WriteExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitWriteExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStmtContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::WhileStmtContext::WHILE() {
  return getToken(AslParser::WHILE, 0);
}

AslParser::ExprContext* AslParser::WhileStmtContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::WhileStmtContext::DO() {
  return getToken(AslParser::DO, 0);
}

AslParser::StatementsContext* AslParser::WhileStmtContext::statements() {
  return getRuleContext<AslParser::StatementsContext>(0);
}

tree::TerminalNode* AslParser::WhileStmtContext::ENDWHILE() {
  return getToken(AslParser::ENDWHILE, 0);
}

AslParser::WhileStmtContext::WhileStmtContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::IfStmtContext::IF() {
  return getToken(AslParser::IF, 0);
}

AslParser::ExprContext* AslParser::IfStmtContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::IfStmtContext::THEN() {
  return getToken(AslParser::THEN, 0);
}

std::vector<AslParser::StatementsContext *> AslParser::IfStmtContext::statements() {
  return getRuleContexts<AslParser::StatementsContext>();
}

AslParser::StatementsContext* AslParser::IfStmtContext::statements(size_t i) {
  return getRuleContext<AslParser::StatementsContext>(i);
}

tree::TerminalNode* AslParser::IfStmtContext::ENDIF() {
  return getToken(AslParser::ENDIF, 0);
}

tree::TerminalNode* AslParser::IfStmtContext::ELSE() {
  return getToken(AslParser::ELSE, 0);
}

AslParser::IfStmtContext::IfStmtContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReadStmtContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::ReadStmtContext::READ() {
  return getToken(AslParser::READ, 0);
}

AslParser::Left_exprContext* AslParser::ReadStmtContext::left_expr() {
  return getRuleContext<AslParser::Left_exprContext>(0);
}

AslParser::ReadStmtContext::ReadStmtContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::ReadStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitReadStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

AslParser::Left_exprContext* AslParser::AssignStmtContext::left_expr() {
  return getRuleContext<AslParser::Left_exprContext>(0);
}

tree::TerminalNode* AslParser::AssignStmtContext::ASSIGN() {
  return getToken(AslParser::ASSIGN, 0);
}

AslParser::ExprContext* AslParser::AssignStmtContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::AssignStmtContext::AssignStmtContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WriteStringContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::WriteStringContext::WRITE() {
  return getToken(AslParser::WRITE, 0);
}

tree::TerminalNode* AslParser::WriteStringContext::STRING() {
  return getToken(AslParser::STRING, 0);
}

AslParser::WriteStringContext::WriteStringContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::WriteStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitWriteString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::ReturnContext::RETURN() {
  return getToken(AslParser::RETURN, 0);
}

AslParser::ExprContext* AslParser::ReturnContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::ReturnContext::ReturnContext(StatementContext *ctx) { copyFrom(ctx); }


std::any AslParser::ReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitReturn(this);
  else
    return visitor->visitChildren(this);
}
AslParser::StatementContext* AslParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, AslParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(111);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<AslParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(68);
      left_expr();
      setState(69);
      match(AslParser::ASSIGN);
      setState(70);
      expr(0);
      setState(71);
      match(AslParser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AslParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(73);
      match(AslParser::IF);
      setState(74);
      expr(0);
      setState(75);
      match(AslParser::THEN);
      setState(76);
      statements();
      setState(79);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AslParser::ELSE) {
        setState(77);
        match(AslParser::ELSE);
        setState(78);
        statements();
      }
      setState(81);
      match(AslParser::ENDIF);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<AslParser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(83);
      match(AslParser::WHILE);
      setState(84);
      expr(0);
      setState(85);
      match(AslParser::DO);
      setState(86);
      statements();
      setState(87);
      match(AslParser::ENDWHILE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AslParser::ProcCallContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(89);
      ident();
      setState(90);
      match(AslParser::T__0);
      setState(91);
      params();
      setState(92);
      match(AslParser::T__1);
      setState(93);
      match(AslParser::T__4);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<AslParser::ReadStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(95);
      match(AslParser::READ);
      setState(96);
      left_expr();
      setState(97);
      match(AslParser::T__4);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<AslParser::WriteExprContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(99);
      match(AslParser::WRITE);
      setState(100);
      expr(0);
      setState(101);
      match(AslParser::T__4);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<AslParser::WriteStringContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(103);
      match(AslParser::WRITE);
      setState(104);
      match(AslParser::STRING);
      setState(105);
      match(AslParser::T__4);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<AslParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(106);
      match(AslParser::RETURN);
      setState(108);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4260607688770) != 0)) {
        setState(107);
        expr(0);
      }
      setState(110);
      match(AslParser::T__4);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Left_exprContext ------------------------------------------------------------------

AslParser::Left_exprContext::Left_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AslParser::IdentContext* AslParser::Left_exprContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}


size_t AslParser::Left_exprContext::getRuleIndex() const {
  return AslParser::RuleLeft_expr;
}


std::any AslParser::Left_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitLeft_expr(this);
  else
    return visitor->visitChildren(this);
}

AslParser::Left_exprContext* AslParser::left_expr() {
  Left_exprContext *_localctx = _tracker.createInstance<Left_exprContext>(_ctx, getState());
  enterRule(_localctx, 14, AslParser::RuleLeft_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

AslParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t AslParser::ExprContext::getRuleIndex() const {
  return AslParser::RuleExpr;
}

void AslParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::NotContext::NOT() {
  return getToken(AslParser::NOT, 0);
}

AslParser::ExprContext* AslParser::NotContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::NotContext::NotContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntValContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::IntValContext::INTVAL() {
  return getToken(AslParser::INTVAL, 0);
}

AslParser::IntValContext::IntValContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::IntValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitIntVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CharValContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::CharValContext::CHARVAL() {
  return getToken(AslParser::CHARVAL, 0);
}

AslParser::CharValContext::CharValContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::CharValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitCharVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIdentContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ExprIdentContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

AslParser::ExprIdentContext::ExprIdentContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::ExprIdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprIdent(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArithmeticContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::ArithmeticContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::ArithmeticContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::ArithmeticContext::MUL() {
  return getToken(AslParser::MUL, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::DIV() {
  return getToken(AslParser::DIV, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::PLUS() {
  return getToken(AslParser::PLUS, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::MINUS() {
  return getToken(AslParser::MINUS, 0);
}

AslParser::ArithmeticContext::ArithmeticContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::ArithmeticContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArithmetic(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatValContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::FloatValContext::FLOATVAL() {
  return getToken(AslParser::FLOATVAL, 0);
}

AslParser::FloatValContext::FloatValContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::FloatValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitFloatVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationalContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::RelationalContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::RelationalContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::RelationalContext::EQ() {
  return getToken(AslParser::EQ, 0);
}

tree::TerminalNode* AslParser::RelationalContext::NE() {
  return getToken(AslParser::NE, 0);
}

tree::TerminalNode* AslParser::RelationalContext::LT() {
  return getToken(AslParser::LT, 0);
}

tree::TerminalNode* AslParser::RelationalContext::LE() {
  return getToken(AslParser::LE, 0);
}

tree::TerminalNode* AslParser::RelationalContext::GT() {
  return getToken(AslParser::GT, 0);
}

tree::TerminalNode* AslParser::RelationalContext::GE() {
  return getToken(AslParser::GE, 0);
}

AslParser::RelationalContext::RelationalContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::RelationalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitRelational(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::UnaryContext::MINUS() {
  return getToken(AslParser::MINUS, 0);
}

AslParser::ExprContext* AslParser::UnaryContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::UnaryContext::UnaryContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::UnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::LogicContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::LogicContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::LogicContext::AND() {
  return getToken(AslParser::AND, 0);
}

tree::TerminalNode* AslParser::LogicContext::OR() {
  return getToken(AslParser::OR, 0);
}

AslParser::LogicContext::LogicContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::LogicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitLogic(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolValContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::BoolValContext::BOOLVAL() {
  return getToken(AslParser::BOOLVAL, 0);
}

AslParser::BoolValContext::BoolValContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::BoolValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitBoolVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesisContext ------------------------------------------------------------------

AslParser::ExprContext* AslParser::ParenthesisContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::ParenthesisContext::ParenthesisContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::ParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitParenthesis(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ExprContext* AslParser::expr() {
   return expr(0);
}

AslParser::ExprContext* AslParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  AslParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  AslParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, AslParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AslParser::T__0: {
        _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(116);
        match(AslParser::T__0);
        setState(117);
        expr(0);
        setState(118);
        match(AslParser::T__1);
        break;
      }

      case AslParser::MINUS: {
        _localctx = _tracker.createInstance<UnaryContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(120);
        match(AslParser::MINUS);
        setState(121);
        expr(11);
        break;
      }

      case AslParser::NOT: {
        _localctx = _tracker.createInstance<NotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(122);
        match(AslParser::NOT);
        setState(123);
        expr(7);
        break;
      }

      case AslParser::INTVAL: {
        _localctx = _tracker.createInstance<IntValContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(124);
        match(AslParser::INTVAL);
        break;
      }

      case AslParser::FLOATVAL: {
        _localctx = _tracker.createInstance<FloatValContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(125);
        match(AslParser::FLOATVAL);
        break;
      }

      case AslParser::BOOLVAL: {
        _localctx = _tracker.createInstance<BoolValContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(126);
        match(AslParser::BOOLVAL);
        break;
      }

      case AslParser::CHARVAL: {
        _localctx = _tracker.createInstance<CharValContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(127);
        match(AslParser::CHARVAL);
        break;
      }

      case AslParser::ID: {
        _localctx = _tracker.createInstance<ExprIdentContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(128);
        ident();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(145);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(143);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(131);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(132);
          antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == AslParser::MUL

          || _la == AslParser::DIV)) {
            antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(133);
          expr(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(134);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(135);
          antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == AslParser::PLUS

          || _la == AslParser::MINUS)) {
            antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(136);
          expr(10);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(137);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(138);
          antlrcpp::downCast<RelationalContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 64512) != 0))) {
            antlrcpp::downCast<RelationalContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(139);
          expr(9);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(140);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(141);
          antlrcpp::downCast<LogicContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == AslParser::AND

          || _la == AslParser::OR)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(142);
          expr(7);
          break;
        }

        default:
          break;
        } 
      }
      setState(147);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IdentContext ------------------------------------------------------------------

AslParser::IdentContext::IdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::IdentContext::ID() {
  return getToken(AslParser::ID, 0);
}


size_t AslParser::IdentContext::getRuleIndex() const {
  return AslParser::RuleIdent;
}


std::any AslParser::IdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitIdent(this);
  else
    return visitor->visitChildren(this);
}

AslParser::IdentContext* AslParser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 18, AslParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(AslParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

AslParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> AslParser::ParamsContext::ID() {
  return getTokens(AslParser::ID);
}

tree::TerminalNode* AslParser::ParamsContext::ID(size_t i) {
  return getToken(AslParser::ID, i);
}

std::vector<AslParser::TypeContext *> AslParser::ParamsContext::type() {
  return getRuleContexts<AslParser::TypeContext>();
}

AslParser::TypeContext* AslParser::ParamsContext::type(size_t i) {
  return getRuleContext<AslParser::TypeContext>(i);
}


size_t AslParser::ParamsContext::getRuleIndex() const {
  return AslParser::RuleParams;
}


std::any AslParser::ParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitParams(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ParamsContext* AslParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 20, AslParser::RuleParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::ID) {
      setState(150);
      match(AslParser::ID);
      setState(151);
      match(AslParser::T__2);
      setState(152);
      type();
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == AslParser::T__3) {
        setState(153);
        match(AslParser::T__3);
        setState(154);
        match(AslParser::ID);
        setState(155);
        match(AslParser::T__2);
        setState(156);
        type();
        setState(161);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool AslParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 8: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool AslParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 10);
    case 1: return precpred(_ctx, 9);
    case 2: return precpred(_ctx, 8);
    case 3: return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

void AslParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  aslParserInitialize();
#else
  ::antlr4::internal::call_once(aslParserOnceFlag, aslParserInitialize);
#endif
}
