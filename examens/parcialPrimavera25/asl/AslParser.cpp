
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
      "statement", "left_expr", "expr", "array", "ident", "params", "lParams"
    },
    std::vector<std::string>{
      "", "'('", "')'", "':'", "','", "'['", "']'", "';'", "'not'", "'and'", 
      "'or'", "'='", "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", "'+'", 
      "'-'", "'*'", "'/'", "'%'", "'var'", "'int'", "'float'", "'bool'", 
      "'char'", "'any'", "'anycast'", "'if'", "'then'", "'else'", "'endif'", 
      "'while'", "'do'", "'endwhile'", "'func'", "'endfunc'", "'read'", 
      "'write'", "'return'", "'array'", "'of'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "NOT", "AND", "OR", "ASSIGN", "EQ", 
      "NE", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MUL", "DIV", "MOD", 
      "VAR", "INT", "FLOAT", "BOOL", "CHAR", "ANY", "ANYCAST", "IF", "THEN", 
      "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE", "FUNC", "ENDFUNC", "READ", 
      "WRITE", "RETURN", "ARRAY", "OF", "BOOLVAL", "INTVAL", "FLOATVAL", 
      "CHARVAL", "ID", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,244,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,4,0,28,8,0,11,
  	0,12,0,29,1,0,1,0,1,1,1,1,1,1,1,1,3,1,38,8,1,1,1,1,1,1,1,3,1,43,8,1,1,
  	1,1,1,1,1,1,1,1,2,5,2,50,8,2,10,2,12,2,53,9,2,1,3,1,3,1,3,1,3,5,3,59,
  	8,3,10,3,12,3,62,9,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,5,4,78,8,4,10,4,12,4,81,9,4,1,4,1,4,1,4,3,4,86,8,4,1,5,5,5,89,
  	8,5,10,5,12,5,92,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,
  	105,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,118,8,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,136,8,6,
  	1,6,3,6,139,8,6,1,7,1,7,3,7,143,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,161,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,3,8,175,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,5,8,192,8,8,10,8,12,8,195,9,8,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,210,8,9,1,9,1,9,1,9,1,9,1,9,5,9,
  	217,8,9,10,9,12,9,220,9,9,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	5,11,231,8,11,10,11,12,11,234,9,11,1,12,1,12,1,12,5,12,239,8,12,10,12,
  	12,12,242,9,12,1,12,0,2,16,18,13,0,2,4,6,8,10,12,14,16,18,20,22,24,0,
  	3,1,0,20,22,1,0,18,19,1,0,12,17,273,0,27,1,0,0,0,2,33,1,0,0,0,4,51,1,
  	0,0,0,6,54,1,0,0,0,8,85,1,0,0,0,10,90,1,0,0,0,12,138,1,0,0,0,14,142,1,
  	0,0,0,16,174,1,0,0,0,18,209,1,0,0,0,20,221,1,0,0,0,22,223,1,0,0,0,24,
  	235,1,0,0,0,26,28,3,2,1,0,27,26,1,0,0,0,28,29,1,0,0,0,29,27,1,0,0,0,29,
  	30,1,0,0,0,30,31,1,0,0,0,31,32,5,0,0,1,32,1,1,0,0,0,33,34,5,37,0,0,34,
  	35,5,48,0,0,35,37,5,1,0,0,36,38,3,22,11,0,37,36,1,0,0,0,37,38,1,0,0,0,
  	38,39,1,0,0,0,39,42,5,2,0,0,40,41,5,3,0,0,41,43,3,8,4,0,42,40,1,0,0,0,
  	42,43,1,0,0,0,43,44,1,0,0,0,44,45,3,4,2,0,45,46,3,10,5,0,46,47,5,38,0,
  	0,47,3,1,0,0,0,48,50,3,6,3,0,49,48,1,0,0,0,50,53,1,0,0,0,51,49,1,0,0,
  	0,51,52,1,0,0,0,52,5,1,0,0,0,53,51,1,0,0,0,54,55,5,23,0,0,55,60,5,48,
  	0,0,56,57,5,4,0,0,57,59,5,48,0,0,58,56,1,0,0,0,59,62,1,0,0,0,60,58,1,
  	0,0,0,60,61,1,0,0,0,61,63,1,0,0,0,62,60,1,0,0,0,63,64,5,3,0,0,64,65,3,
  	8,4,0,65,7,1,0,0,0,66,86,5,24,0,0,67,86,5,25,0,0,68,86,5,26,0,0,69,86,
  	5,27,0,0,70,71,5,42,0,0,71,72,5,5,0,0,72,73,5,45,0,0,73,79,5,6,0,0,74,
  	75,5,5,0,0,75,76,5,45,0,0,76,78,5,6,0,0,77,74,1,0,0,0,78,81,1,0,0,0,79,
  	77,1,0,0,0,79,80,1,0,0,0,80,82,1,0,0,0,81,79,1,0,0,0,82,83,5,43,0,0,83,
  	86,3,8,4,0,84,86,5,28,0,0,85,66,1,0,0,0,85,67,1,0,0,0,85,68,1,0,0,0,85,
  	69,1,0,0,0,85,70,1,0,0,0,85,84,1,0,0,0,86,9,1,0,0,0,87,89,3,12,6,0,88,
  	87,1,0,0,0,89,92,1,0,0,0,90,88,1,0,0,0,90,91,1,0,0,0,91,11,1,0,0,0,92,
  	90,1,0,0,0,93,94,3,14,7,0,94,95,5,11,0,0,95,96,3,16,8,0,96,97,5,7,0,0,
  	97,139,1,0,0,0,98,99,5,30,0,0,99,100,3,16,8,0,100,101,5,31,0,0,101,104,
  	3,10,5,0,102,103,5,32,0,0,103,105,3,10,5,0,104,102,1,0,0,0,104,105,1,
  	0,0,0,105,106,1,0,0,0,106,107,5,33,0,0,107,139,1,0,0,0,108,109,5,34,0,
  	0,109,110,3,16,8,0,110,111,5,35,0,0,111,112,3,10,5,0,112,113,5,36,0,0,
  	113,139,1,0,0,0,114,115,3,20,10,0,115,117,5,1,0,0,116,118,3,24,12,0,117,
  	116,1,0,0,0,117,118,1,0,0,0,118,119,1,0,0,0,119,120,5,2,0,0,120,121,5,
  	7,0,0,121,139,1,0,0,0,122,123,5,39,0,0,123,124,3,14,7,0,124,125,5,7,0,
  	0,125,139,1,0,0,0,126,127,5,40,0,0,127,128,3,16,8,0,128,129,5,7,0,0,129,
  	139,1,0,0,0,130,131,5,40,0,0,131,132,5,49,0,0,132,139,5,7,0,0,133,135,
  	5,41,0,0,134,136,3,16,8,0,135,134,1,0,0,0,135,136,1,0,0,0,136,137,1,0,
  	0,0,137,139,5,7,0,0,138,93,1,0,0,0,138,98,1,0,0,0,138,108,1,0,0,0,138,
  	114,1,0,0,0,138,122,1,0,0,0,138,126,1,0,0,0,138,130,1,0,0,0,138,133,1,
  	0,0,0,139,13,1,0,0,0,140,143,3,18,9,0,141,143,3,20,10,0,142,140,1,0,0,
  	0,142,141,1,0,0,0,143,15,1,0,0,0,144,145,6,8,-1,0,145,146,5,1,0,0,146,
  	147,3,16,8,0,147,148,5,2,0,0,148,175,1,0,0,0,149,150,5,29,0,0,150,151,
  	5,14,0,0,151,152,3,8,4,0,152,153,5,16,0,0,153,154,5,1,0,0,154,155,3,16,
  	8,0,155,156,5,2,0,0,156,175,1,0,0,0,157,158,3,20,10,0,158,160,5,1,0,0,
  	159,161,3,24,12,0,160,159,1,0,0,0,160,161,1,0,0,0,161,162,1,0,0,0,162,
  	163,5,2,0,0,163,175,1,0,0,0,164,175,3,18,9,0,165,166,5,19,0,0,166,175,
  	3,16,8,12,167,168,5,8,0,0,168,175,3,16,8,8,169,175,5,45,0,0,170,175,5,
  	46,0,0,171,175,5,44,0,0,172,175,5,47,0,0,173,175,3,20,10,0,174,144,1,
  	0,0,0,174,149,1,0,0,0,174,157,1,0,0,0,174,164,1,0,0,0,174,165,1,0,0,0,
  	174,167,1,0,0,0,174,169,1,0,0,0,174,170,1,0,0,0,174,171,1,0,0,0,174,172,
  	1,0,0,0,174,173,1,0,0,0,175,193,1,0,0,0,176,177,10,11,0,0,177,178,7,0,
  	0,0,178,192,3,16,8,12,179,180,10,10,0,0,180,181,7,1,0,0,181,192,3,16,
  	8,11,182,183,10,9,0,0,183,184,7,2,0,0,184,192,3,16,8,10,185,186,10,7,
  	0,0,186,187,5,9,0,0,187,192,3,16,8,8,188,189,10,6,0,0,189,190,5,10,0,
  	0,190,192,3,16,8,7,191,176,1,0,0,0,191,179,1,0,0,0,191,182,1,0,0,0,191,
  	185,1,0,0,0,191,188,1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,193,194,1,
  	0,0,0,194,17,1,0,0,0,195,193,1,0,0,0,196,197,6,9,-1,0,197,198,3,20,10,
  	0,198,199,5,5,0,0,199,200,3,16,8,0,200,201,5,6,0,0,201,210,1,0,0,0,202,
  	203,3,20,10,0,203,204,5,5,0,0,204,205,5,45,0,0,205,206,5,3,0,0,206,207,
  	5,45,0,0,207,208,5,6,0,0,208,210,1,0,0,0,209,196,1,0,0,0,209,202,1,0,
  	0,0,210,218,1,0,0,0,211,212,10,1,0,0,212,213,5,5,0,0,213,214,3,16,8,0,
  	214,215,5,6,0,0,215,217,1,0,0,0,216,211,1,0,0,0,217,220,1,0,0,0,218,216,
  	1,0,0,0,218,219,1,0,0,0,219,19,1,0,0,0,220,218,1,0,0,0,221,222,5,48,0,
  	0,222,21,1,0,0,0,223,224,5,48,0,0,224,225,5,3,0,0,225,232,3,8,4,0,226,
  	227,5,4,0,0,227,228,5,48,0,0,228,229,5,3,0,0,229,231,3,8,4,0,230,226,
  	1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,1,0,0,0,233,23,1,0,0,
  	0,234,232,1,0,0,0,235,240,3,16,8,0,236,237,5,4,0,0,237,239,3,16,8,0,238,
  	236,1,0,0,0,239,242,1,0,0,0,240,238,1,0,0,0,240,241,1,0,0,0,241,25,1,
  	0,0,0,242,240,1,0,0,0,21,29,37,42,51,60,79,85,90,104,117,135,138,142,
  	160,174,191,193,209,218,232,240
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
    setState(27); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(26);
      function();
      setState(29); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == AslParser::FUNC);
    setState(31);
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

AslParser::DeclarationsContext* AslParser::FunctionContext::declarations() {
  return getRuleContext<AslParser::DeclarationsContext>(0);
}

AslParser::StatementsContext* AslParser::FunctionContext::statements() {
  return getRuleContext<AslParser::StatementsContext>(0);
}

tree::TerminalNode* AslParser::FunctionContext::ENDFUNC() {
  return getToken(AslParser::ENDFUNC, 0);
}

AslParser::ParamsContext* AslParser::FunctionContext::params() {
  return getRuleContext<AslParser::ParamsContext>(0);
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
    setState(33);
    match(AslParser::FUNC);
    setState(34);
    match(AslParser::ID);
    setState(35);
    match(AslParser::T__0);
    setState(37);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AslParser::ID) {
      setState(36);
      params();
    }
    setState(39);
    match(AslParser::T__1);
    setState(42);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AslParser::T__2) {
      setState(40);
      match(AslParser::T__2);
      setState(41);
      type();
    }
    setState(44);
    declarations();
    setState(45);
    statements();
    setState(46);
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
    setState(51);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::VAR) {
      setState(48);
      variable_decl();
      setState(53);
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
    setState(54);
    match(AslParser::VAR);
    setState(55);
    match(AslParser::ID);
    setState(60);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::T__3) {
      setState(56);
      match(AslParser::T__3);
      setState(57);
      match(AslParser::ID);
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
    match(AslParser::T__2);
    setState(64);
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

tree::TerminalNode* AslParser::TypeContext::ARRAY() {
  return getToken(AslParser::ARRAY, 0);
}

std::vector<tree::TerminalNode *> AslParser::TypeContext::INTVAL() {
  return getTokens(AslParser::INTVAL);
}

tree::TerminalNode* AslParser::TypeContext::INTVAL(size_t i) {
  return getToken(AslParser::INTVAL, i);
}

tree::TerminalNode* AslParser::TypeContext::OF() {
  return getToken(AslParser::OF, 0);
}

AslParser::TypeContext* AslParser::TypeContext::type() {
  return getRuleContext<AslParser::TypeContext>(0);
}

tree::TerminalNode* AslParser::TypeContext::ANY() {
  return getToken(AslParser::ANY, 0);
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
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AslParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(66);
        match(AslParser::INT);
        break;
      }

      case AslParser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(67);
        match(AslParser::FLOAT);
        break;
      }

      case AslParser::BOOL: {
        enterOuterAlt(_localctx, 3);
        setState(68);
        match(AslParser::BOOL);
        break;
      }

      case AslParser::CHAR: {
        enterOuterAlt(_localctx, 4);
        setState(69);
        match(AslParser::CHAR);
        break;
      }

      case AslParser::ARRAY: {
        enterOuterAlt(_localctx, 5);
        setState(70);
        match(AslParser::ARRAY);
        setState(71);
        match(AslParser::T__4);
        setState(72);
        match(AslParser::INTVAL);
        setState(73);
        match(AslParser::T__5);
        setState(79);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == AslParser::T__4) {
          setState(74);
          match(AslParser::T__4);
          setState(75);
          match(AslParser::INTVAL);
          setState(76);
          match(AslParser::T__5);
          setState(81);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(82);
        match(AslParser::OF);
        setState(83);
        type();
        break;
      }

      case AslParser::ANY: {
        enterOuterAlt(_localctx, 6);
        setState(84);
        match(AslParser::ANY);
        break;
      }

    default:
      throw NoViableAltException(this);
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
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 285341521018880) != 0)) {
      setState(87);
      statement();
      setState(92);
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

AslParser::LParamsContext* AslParser::ProcCallContext::lParams() {
  return getRuleContext<AslParser::LParamsContext>(0);
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
    setState(138);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<AslParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(93);
      left_expr();
      setState(94);
      match(AslParser::ASSIGN);
      setState(95);
      expr(0);
      setState(96);
      match(AslParser::T__6);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AslParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(98);
      match(AslParser::IF);
      setState(99);
      expr(0);
      setState(100);
      match(AslParser::THEN);
      setState(101);
      statements();
      setState(104);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AslParser::ELSE) {
        setState(102);
        match(AslParser::ELSE);
        setState(103);
        statements();
      }
      setState(106);
      match(AslParser::ENDIF);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<AslParser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(108);
      match(AslParser::WHILE);
      setState(109);
      expr(0);
      setState(110);
      match(AslParser::DO);
      setState(111);
      statements();
      setState(112);
      match(AslParser::ENDWHILE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AslParser::ProcCallContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(114);
      ident();
      setState(115);
      match(AslParser::T__0);
      setState(117);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 545358304772354) != 0)) {
        setState(116);
        lParams();
      }
      setState(119);
      match(AslParser::T__1);
      setState(120);
      match(AslParser::T__6);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<AslParser::ReadStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(122);
      match(AslParser::READ);
      setState(123);
      left_expr();
      setState(124);
      match(AslParser::T__6);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<AslParser::WriteExprContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(126);
      match(AslParser::WRITE);
      setState(127);
      expr(0);
      setState(128);
      match(AslParser::T__6);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<AslParser::WriteStringContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(130);
      match(AslParser::WRITE);
      setState(131);
      match(AslParser::STRING);
      setState(132);
      match(AslParser::T__6);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<AslParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(133);
      match(AslParser::RETURN);
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 545358304772354) != 0)) {
        setState(134);
        expr(0);
      }
      setState(137);
      match(AslParser::T__6);
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

AslParser::ArrayContext* AslParser::Left_exprContext::array() {
  return getRuleContext<AslParser::ArrayContext>(0);
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
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(140);
      array(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(141);
      ident();
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

//----------------- AnycastContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::AnycastContext::ANYCAST() {
  return getToken(AslParser::ANYCAST, 0);
}

tree::TerminalNode* AslParser::AnycastContext::LT() {
  return getToken(AslParser::LT, 0);
}

AslParser::TypeContext* AslParser::AnycastContext::type() {
  return getRuleContext<AslParser::TypeContext>(0);
}

tree::TerminalNode* AslParser::AnycastContext::GT() {
  return getToken(AslParser::GT, 0);
}

AslParser::ExprContext* AslParser::AnycastContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::AnycastContext::AnycastContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::AnycastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitAnycast(this);
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

tree::TerminalNode* AslParser::ArithmeticContext::MOD() {
  return getToken(AslParser::MOD, 0);
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
//----------------- UnaryContext ------------------------------------------------------------------

AslParser::ExprContext* AslParser::UnaryContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::UnaryContext::MINUS() {
  return getToken(AslParser::MINUS, 0);
}

AslParser::UnaryContext::UnaryContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::UnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitUnary(this);
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
//----------------- NotContext ------------------------------------------------------------------

AslParser::ExprContext* AslParser::NotContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::NotContext::NOT() {
  return getToken(AslParser::NOT, 0);
}

AslParser::NotContext::NotContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::FunctionCallContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

AslParser::LParamsContext* AslParser::FunctionCallContext::lParams() {
  return getRuleContext<AslParser::LParamsContext>(0);
}

AslParser::FunctionCallContext::FunctionCallContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
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
//----------------- ArrayAccessContext ------------------------------------------------------------------

AslParser::ArrayContext* AslParser::ArrayAccessContext::array() {
  return getRuleContext<AslParser::ArrayContext>(0);
}

AslParser::ArrayAccessContext::ArrayAccessContext(ExprContext *ctx) { copyFrom(ctx); }


std::any AslParser::ArrayAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArrayAccess(this);
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
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(145);
      match(AslParser::T__0);
      setState(146);
      expr(0);
      setState(147);
      match(AslParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AnycastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(149);
      match(AslParser::ANYCAST);
      setState(150);
      match(AslParser::LT);
      setState(151);
      type();
      setState(152);
      match(AslParser::GT);
      setState(153);
      match(AslParser::T__0);
      setState(154);
      expr(0);
      setState(155);
      match(AslParser::T__1);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(157);
      ident();
      setState(158);
      match(AslParser::T__0);
      setState(160);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 545358304772354) != 0)) {
        setState(159);
        lParams();
      }
      setState(162);
      match(AslParser::T__1);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ArrayAccessContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(164);
      array(0);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(165);
      antlrcpp::downCast<UnaryContext *>(_localctx)->op = match(AslParser::MINUS);
      setState(166);
      expr(12);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(167);
      antlrcpp::downCast<NotContext *>(_localctx)->op = match(AslParser::NOT);
      setState(168);
      expr(8);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<IntValContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(169);
      match(AslParser::INTVAL);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<FloatValContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(170);
      match(AslParser::FLOATVAL);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BoolValContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(171);
      match(AslParser::BOOLVAL);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<CharValContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(172);
      match(AslParser::CHARVAL);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<ExprIdentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(173);
      ident();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(193);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(191);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(176);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(177);
          antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
            antlrcpp::downCast<ArithmeticContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(178);
          expr(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(179);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(180);
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
          setState(181);
          expr(11);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(182);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(183);
          antlrcpp::downCast<RelationalContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 258048) != 0))) {
            antlrcpp::downCast<RelationalContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(184);
          expr(10);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(185);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(186);
          antlrcpp::downCast<LogicContext *>(_localctx)->op = match(AslParser::AND);
          setState(187);
          expr(8);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(188);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(189);
          antlrcpp::downCast<LogicContext *>(_localctx)->op = match(AslParser::OR);
          setState(190);
          expr(7);
          break;
        }

        default:
          break;
        } 
      }
      setState(195);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

AslParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t AslParser::ArrayContext::getRuleIndex() const {
  return AslParser::RuleArray;
}

void AslParser::ArrayContext::copyFrom(ArrayContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArrayNormalContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ArrayNormalContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

AslParser::ExprContext* AslParser::ArrayNormalContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::ArrayNormalContext::ArrayNormalContext(ArrayContext *ctx) { copyFrom(ctx); }


std::any AslParser::ArrayNormalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArrayNormal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArraySliceContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ArraySliceContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

std::vector<tree::TerminalNode *> AslParser::ArraySliceContext::INTVAL() {
  return getTokens(AslParser::INTVAL);
}

tree::TerminalNode* AslParser::ArraySliceContext::INTVAL(size_t i) {
  return getToken(AslParser::INTVAL, i);
}

AslParser::ArraySliceContext::ArraySliceContext(ArrayContext *ctx) { copyFrom(ctx); }


std::any AslParser::ArraySliceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArraySlice(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayMultiDimContext ------------------------------------------------------------------

AslParser::ArrayContext* AslParser::ArrayMultiDimContext::array() {
  return getRuleContext<AslParser::ArrayContext>(0);
}

AslParser::ExprContext* AslParser::ArrayMultiDimContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

AslParser::ArrayMultiDimContext::ArrayMultiDimContext(ArrayContext *ctx) { copyFrom(ctx); }


std::any AslParser::ArrayMultiDimContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArrayMultiDim(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ArrayContext* AslParser::array() {
   return array(0);
}

AslParser::ArrayContext* AslParser::array(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  AslParser::ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, parentState);
  AslParser::ArrayContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, AslParser::RuleArray, precedence);

    

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
    setState(209);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ArrayNormalContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(197);
      ident();
      setState(198);
      match(AslParser::T__4);
      setState(199);
      expr(0);
      setState(200);
      match(AslParser::T__5);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArraySliceContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(202);
      ident();
      setState(203);
      match(AslParser::T__4);
      setState(204);
      match(AslParser::INTVAL);
      setState(205);
      match(AslParser::T__2);
      setState(206);
      match(AslParser::INTVAL);
      setState(207);
      match(AslParser::T__5);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(218);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayMultiDimContext>(_tracker.createInstance<ArrayContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleArray);
        setState(211);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(212);
        match(AslParser::T__4);
        setState(213);
        expr(0);
        setState(214);
        match(AslParser::T__5); 
      }
      setState(220);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
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
  enterRule(_localctx, 20, AslParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
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
  enterRule(_localctx, 22, AslParser::RuleParams);
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
    setState(223);
    match(AslParser::ID);
    setState(224);
    match(AslParser::T__2);
    setState(225);
    type();
    setState(232);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::T__3) {
      setState(226);
      match(AslParser::T__3);
      setState(227);
      match(AslParser::ID);
      setState(228);
      match(AslParser::T__2);
      setState(229);
      type();
      setState(234);
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

//----------------- LParamsContext ------------------------------------------------------------------

AslParser::LParamsContext::LParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AslParser::ExprContext *> AslParser::LParamsContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::LParamsContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}


size_t AslParser::LParamsContext::getRuleIndex() const {
  return AslParser::RuleLParams;
}


std::any AslParser::LParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitLParams(this);
  else
    return visitor->visitChildren(this);
}

AslParser::LParamsContext* AslParser::lParams() {
  LParamsContext *_localctx = _tracker.createInstance<LParamsContext>(_ctx, getState());
  enterRule(_localctx, 24, AslParser::RuleLParams);
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
    setState(235);
    expr(0);
    setState(240);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::T__3) {
      setState(236);
      match(AslParser::T__3);
      setState(237);
      expr(0);
      setState(242);
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
    case 9: return arraySempred(antlrcpp::downCast<ArrayContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool AslParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);
    case 2: return precpred(_ctx, 9);
    case 3: return precpred(_ctx, 7);
    case 4: return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

bool AslParser::arraySempred(ArrayContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

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
