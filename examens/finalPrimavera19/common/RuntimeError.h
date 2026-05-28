
///////////////////////////////////////////////////////////////////////////
// Given an array access node ctx (not the index node) returns the t-code
// that, when executed, writes the runtime error message and halts the tVM.
///////////////////////////////////////////////////////////////////////////
instructionList throwRuntimeErrorTCode(antlr4::ParserRuleContext *ctx) {
  instructionList code;
  std::string line = std::to_string(ctx->getStart()->getLine());
  std::string coln = std::to_string(ctx->getStart()->getCharPositionInLine());
  std::string text = "Runtime Error: Line " + line + ":" + coln + ". Access out of range: " + ctx->getText();

  std::string temp = "%99";  // we can overwrite any temporal, since we are aborting the program  
  for (auto & c : text) 
    code = code || instruction::CHLOAD(temp, std::string(1, c)) ||
                   instruction::WRITEC(temp);
  
  code = code || instruction::WRITELN()
              || instruction::HALT(); 
  return code;
}
