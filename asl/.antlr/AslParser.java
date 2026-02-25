// Generated from /home/joan/UPC/CL/CL-lab/practica/asl/Asl.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class AslParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, NOT=8, AND=9, 
		OR=10, ASSIGN=11, EQ=12, NE=13, LT=14, LE=15, GT=16, GE=17, PLUS=18, MINUS=19, 
		MUL=20, DIV=21, VAR=22, INT=23, FLOAT=24, BOOL=25, CHAR=26, IF=27, THEN=28, 
		ELSE=29, ENDIF=30, WHILE=31, DO=32, ENDWHILE=33, FUNC=34, ENDFUNC=35, 
		READ=36, WRITE=37, RETURN=38, ARRAY=39, OF=40, BOOLVAL=41, INTVAL=42, 
		FLOATVAL=43, CHARVAL=44, ID=45, STRING=46, COMMENT=47, WS=48;
	public static final int
		RULE_program = 0, RULE_function = 1, RULE_declarations = 2, RULE_variable_decl = 3, 
		RULE_type = 4, RULE_statements = 5, RULE_statement = 6, RULE_left_expr = 7, 
		RULE_expr = 8, RULE_ident = 9, RULE_params = 10;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "function", "declarations", "variable_decl", "type", "statements", 
			"statement", "left_expr", "expr", "ident", "params"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "':'", "','", "'['", "']'", "';'", "'not'", "'and'", 
			"'or'", "'='", "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", "'+'", "'-'", 
			"'*'", "'/'", "'var'", "'int'", "'float'", "'bool'", "'char'", "'if'", 
			"'then'", "'else'", "'endif'", "'while'", "'do'", "'endwhile'", "'func'", 
			"'endfunc'", "'read'", "'write'", "'return'", "'array'", "'of'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, "NOT", "AND", "OR", "ASSIGN", 
			"EQ", "NE", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MUL", "DIV", "VAR", 
			"INT", "FLOAT", "BOOL", "CHAR", "IF", "THEN", "ELSE", "ENDIF", "WHILE", 
			"DO", "ENDWHILE", "FUNC", "ENDFUNC", "READ", "WRITE", "RETURN", "ARRAY", 
			"OF", "BOOLVAL", "INTVAL", "FLOATVAL", "CHARVAL", "ID", "STRING", "COMMENT", 
			"WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Asl.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public AslParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(AslParser.EOF, 0); }
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(23); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(22);
				function();
				}
				}
				setState(25); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==FUNC );
			setState(27);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionContext extends ParserRuleContext {
		public TerminalNode FUNC() { return getToken(AslParser.FUNC, 0); }
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public DeclarationsContext declarations() {
			return getRuleContext(DeclarationsContext.class,0);
		}
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode ENDFUNC() { return getToken(AslParser.ENDFUNC, 0); }
		public ParamsContext params() {
			return getRuleContext(ParamsContext.class,0);
		}
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_function);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(29);
			match(FUNC);
			setState(30);
			match(ID);
			setState(31);
			match(T__0);
			setState(33);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ID) {
				{
				setState(32);
				params();
				}
			}

			setState(35);
			match(T__1);
			setState(38);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__2) {
				{
				setState(36);
				match(T__2);
				setState(37);
				type();
				}
			}

			setState(40);
			declarations();
			setState(41);
			statements();
			setState(42);
			match(ENDFUNC);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeclarationsContext extends ParserRuleContext {
		public List<Variable_declContext> variable_decl() {
			return getRuleContexts(Variable_declContext.class);
		}
		public Variable_declContext variable_decl(int i) {
			return getRuleContext(Variable_declContext.class,i);
		}
		public DeclarationsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declarations; }
	}

	public final DeclarationsContext declarations() throws RecognitionException {
		DeclarationsContext _localctx = new DeclarationsContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_declarations);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(47);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VAR) {
				{
				{
				setState(44);
				variable_decl();
				}
				}
				setState(49);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Variable_declContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(AslParser.VAR, 0); }
		public List<TerminalNode> ID() { return getTokens(AslParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(AslParser.ID, i);
		}
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public Variable_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variable_decl; }
	}

	public final Variable_declContext variable_decl() throws RecognitionException {
		Variable_declContext _localctx = new Variable_declContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_variable_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(50);
			match(VAR);
			setState(51);
			match(ID);
			setState(56);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__3) {
				{
				{
				setState(52);
				match(T__3);
				setState(53);
				match(ID);
				}
				}
				setState(58);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(59);
			match(T__2);
			setState(60);
			type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeContext extends ParserRuleContext {
		public TerminalNode INT() { return getToken(AslParser.INT, 0); }
		public TerminalNode FLOAT() { return getToken(AslParser.FLOAT, 0); }
		public TerminalNode BOOL() { return getToken(AslParser.BOOL, 0); }
		public TerminalNode CHAR() { return getToken(AslParser.CHAR, 0); }
		public TerminalNode ARRAY() { return getToken(AslParser.ARRAY, 0); }
		public TerminalNode INTVAL() { return getToken(AslParser.INTVAL, 0); }
		public TerminalNode OF() { return getToken(AslParser.OF, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_type);
		try {
			setState(72);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INT:
				enterOuterAlt(_localctx, 1);
				{
				setState(62);
				match(INT);
				}
				break;
			case FLOAT:
				enterOuterAlt(_localctx, 2);
				{
				setState(63);
				match(FLOAT);
				}
				break;
			case BOOL:
				enterOuterAlt(_localctx, 3);
				{
				setState(64);
				match(BOOL);
				}
				break;
			case CHAR:
				enterOuterAlt(_localctx, 4);
				{
				setState(65);
				match(CHAR);
				}
				break;
			case ARRAY:
				enterOuterAlt(_localctx, 5);
				{
				setState(66);
				match(ARRAY);
				setState(67);
				match(T__4);
				setState(68);
				match(INTVAL);
				setState(69);
				match(T__5);
				setState(70);
				match(OF);
				setState(71);
				type();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementsContext extends ParserRuleContext {
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public StatementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statements; }
	}

	public final StatementsContext statements() throws RecognitionException {
		StatementsContext _localctx = new StatementsContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_statements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(77);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 35667690127360L) != 0)) {
				{
				{
				setState(74);
				statement();
				}
				}
				setState(79);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	 
		public StatementContext() { }
		public void copyFrom(StatementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ProcCallContext extends StatementContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public ParamsContext params() {
			return getRuleContext(ParamsContext.class,0);
		}
		public ProcCallContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class WriteExprContext extends StatementContext {
		public TerminalNode WRITE() { return getToken(AslParser.WRITE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public WriteExprContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class WhileStmtContext extends StatementContext {
		public TerminalNode WHILE() { return getToken(AslParser.WHILE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode DO() { return getToken(AslParser.DO, 0); }
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode ENDWHILE() { return getToken(AslParser.ENDWHILE, 0); }
		public WhileStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IfStmtContext extends StatementContext {
		public TerminalNode IF() { return getToken(AslParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode THEN() { return getToken(AslParser.THEN, 0); }
		public List<StatementsContext> statements() {
			return getRuleContexts(StatementsContext.class);
		}
		public StatementsContext statements(int i) {
			return getRuleContext(StatementsContext.class,i);
		}
		public TerminalNode ENDIF() { return getToken(AslParser.ENDIF, 0); }
		public TerminalNode ELSE() { return getToken(AslParser.ELSE, 0); }
		public IfStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ReadStmtContext extends StatementContext {
		public TerminalNode READ() { return getToken(AslParser.READ, 0); }
		public Left_exprContext left_expr() {
			return getRuleContext(Left_exprContext.class,0);
		}
		public ReadStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AssignStmtContext extends StatementContext {
		public Left_exprContext left_expr() {
			return getRuleContext(Left_exprContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(AslParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AssignStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class WriteStringContext extends StatementContext {
		public TerminalNode WRITE() { return getToken(AslParser.WRITE, 0); }
		public TerminalNode STRING() { return getToken(AslParser.STRING, 0); }
		public WriteStringContext(StatementContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ReturnContext extends StatementContext {
		public TerminalNode RETURN() { return getToken(AslParser.RETURN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ReturnContext(StatementContext ctx) { copyFrom(ctx); }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_statement);
		int _la;
		try {
			setState(125);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				_localctx = new AssignStmtContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(80);
				left_expr();
				setState(81);
				match(ASSIGN);
				setState(82);
				expr(0);
				setState(83);
				match(T__6);
				}
				break;
			case 2:
				_localctx = new IfStmtContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(85);
				match(IF);
				setState(86);
				expr(0);
				setState(87);
				match(THEN);
				setState(88);
				statements();
				setState(91);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==ELSE) {
					{
					setState(89);
					match(ELSE);
					setState(90);
					statements();
					}
				}

				setState(93);
				match(ENDIF);
				}
				break;
			case 3:
				_localctx = new WhileStmtContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(95);
				match(WHILE);
				setState(96);
				expr(0);
				setState(97);
				match(DO);
				setState(98);
				statements();
				setState(99);
				match(ENDWHILE);
				}
				break;
			case 4:
				_localctx = new ProcCallContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(101);
				ident();
				setState(102);
				match(T__0);
				setState(104);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==ID) {
					{
					setState(103);
					params();
					}
				}

				setState(106);
				match(T__1);
				setState(107);
				match(T__6);
				}
				break;
			case 5:
				_localctx = new ReadStmtContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(109);
				match(READ);
				setState(110);
				left_expr();
				setState(111);
				match(T__6);
				}
				break;
			case 6:
				_localctx = new WriteExprContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(113);
				match(WRITE);
				setState(114);
				expr(0);
				setState(115);
				match(T__6);
				}
				break;
			case 7:
				_localctx = new WriteStringContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(117);
				match(WRITE);
				setState(118);
				match(STRING);
				setState(119);
				match(T__6);
				}
				break;
			case 8:
				_localctx = new ReturnContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(120);
				match(RETURN);
				setState(122);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 68169721446658L) != 0)) {
					{
					setState(121);
					expr(0);
					}
				}

				setState(124);
				match(T__6);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Left_exprContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public Left_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_left_expr; }
	}

	public final Left_exprContext left_expr() throws RecognitionException {
		Left_exprContext _localctx = new Left_exprContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_left_expr);
		try {
			setState(133);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(127);
				match(ID);
				setState(128);
				match(T__4);
				setState(129);
				expr(0);
				setState(130);
				match(T__5);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(132);
				ident();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NotContext extends ExprContext {
		public TerminalNode NOT() { return getToken(AslParser.NOT, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public NotContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IntValContext extends ExprContext {
		public TerminalNode INTVAL() { return getToken(AslParser.INTVAL, 0); }
		public IntValContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CharValContext extends ExprContext {
		public TerminalNode CHARVAL() { return getToken(AslParser.CHARVAL, 0); }
		public CharValContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExprIdentContext extends ExprContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public ExprIdentContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArithmeticContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode MUL() { return getToken(AslParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(AslParser.DIV, 0); }
		public TerminalNode PLUS() { return getToken(AslParser.PLUS, 0); }
		public TerminalNode MINUS() { return getToken(AslParser.MINUS, 0); }
		public ArithmeticContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FloatValContext extends ExprContext {
		public TerminalNode FLOATVAL() { return getToken(AslParser.FLOATVAL, 0); }
		public FloatValContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RelationalContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode EQ() { return getToken(AslParser.EQ, 0); }
		public TerminalNode NE() { return getToken(AslParser.NE, 0); }
		public TerminalNode LT() { return getToken(AslParser.LT, 0); }
		public TerminalNode LE() { return getToken(AslParser.LE, 0); }
		public TerminalNode GT() { return getToken(AslParser.GT, 0); }
		public TerminalNode GE() { return getToken(AslParser.GE, 0); }
		public RelationalContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArrayAccessContext extends ExprContext {
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ArrayAccessContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryContext extends ExprContext {
		public TerminalNode MINUS() { return getToken(AslParser.MINUS, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public UnaryContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode AND() { return getToken(AslParser.AND, 0); }
		public TerminalNode OR() { return getToken(AslParser.OR, 0); }
		public LogicContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BoolValContext extends ExprContext {
		public TerminalNode BOOLVAL() { return getToken(AslParser.BOOLVAL, 0); }
		public BoolValContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParenthesisContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ParenthesisContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 16;
		enterRecursionRule(_localctx, 16, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(154);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				{
				_localctx = new ParenthesisContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(136);
				match(T__0);
				setState(137);
				expr(0);
				setState(138);
				match(T__1);
				}
				break;
			case 2:
				{
				_localctx = new ArrayAccessContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(140);
				match(ID);
				setState(141);
				match(T__4);
				setState(142);
				expr(0);
				setState(143);
				match(T__5);
				}
				break;
			case 3:
				{
				_localctx = new UnaryContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(145);
				match(MINUS);
				setState(146);
				expr(11);
				}
				break;
			case 4:
				{
				_localctx = new NotContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(147);
				match(NOT);
				setState(148);
				expr(7);
				}
				break;
			case 5:
				{
				_localctx = new IntValContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(149);
				match(INTVAL);
				}
				break;
			case 6:
				{
				_localctx = new FloatValContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(150);
				match(FLOATVAL);
				}
				break;
			case 7:
				{
				_localctx = new BoolValContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(151);
				match(BOOLVAL);
				}
				break;
			case 8:
				{
				_localctx = new CharValContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(152);
				match(CHARVAL);
				}
				break;
			case 9:
				{
				_localctx = new ExprIdentContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(153);
				ident();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(170);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(168);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
					case 1:
						{
						_localctx = new ArithmeticContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(156);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(157);
						((ArithmeticContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==MUL || _la==DIV) ) {
							((ArithmeticContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(158);
						expr(11);
						}
						break;
					case 2:
						{
						_localctx = new ArithmeticContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(159);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(160);
						((ArithmeticContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==PLUS || _la==MINUS) ) {
							((ArithmeticContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(161);
						expr(10);
						}
						break;
					case 3:
						{
						_localctx = new RelationalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(162);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(163);
						((RelationalContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 258048L) != 0)) ) {
							((RelationalContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(164);
						expr(9);
						}
						break;
					case 4:
						{
						_localctx = new LogicContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(165);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(166);
						((LogicContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==AND || _la==OR) ) {
							((LogicContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(167);
						expr(7);
						}
						break;
					}
					} 
				}
				setState(172);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IdentContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public IdentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ident; }
	}

	public final IdentContext ident() throws RecognitionException {
		IdentContext _localctx = new IdentContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_ident);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(173);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParamsContext extends ParserRuleContext {
		public List<TerminalNode> ID() { return getTokens(AslParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(AslParser.ID, i);
		}
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public ParamsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_params; }
	}

	public final ParamsContext params() throws RecognitionException {
		ParamsContext _localctx = new ParamsContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_params);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(175);
			match(ID);
			setState(176);
			match(T__2);
			setState(177);
			type();
			setState(184);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__3) {
				{
				{
				setState(178);
				match(T__3);
				setState(179);
				match(ID);
				setState(180);
				match(T__2);
				setState(181);
				type();
				}
				}
				setState(186);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 8:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 10);
		case 1:
			return precpred(_ctx, 9);
		case 2:
			return precpred(_ctx, 8);
		case 3:
			return precpred(_ctx, 6);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u00010\u00bc\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0001\u0000\u0004\u0000\u0018"+
		"\b\u0000\u000b\u0000\f\u0000\u0019\u0001\u0000\u0001\u0000\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001\"\b\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0003\u0001\'\b\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0005\u0002.\b\u0002\n\u0002\f\u0002"+
		"1\t\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003"+
		"7\b\u0003\n\u0003\f\u0003:\t\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0003\u0004I\b\u0004"+
		"\u0001\u0005\u0005\u0005L\b\u0005\n\u0005\f\u0005O\t\u0005\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006\\\b\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006"+
		"i\b\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006"+
		"{\b\u0006\u0001\u0006\u0003\u0006~\b\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0003\u0007\u0086\b\u0007\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0003\b\u009b\b\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0005\b\u00a9\b\b\n\b\f\b\u00ac"+
		"\t\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\n\u0005\n\u00b7\b\n\n\n\f\n\u00ba\t\n\u0001\n\u0000\u0001\u0010\u000b"+
		"\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0000\u0004\u0001"+
		"\u0000\u0014\u0015\u0001\u0000\u0012\u0013\u0001\u0000\f\u0011\u0001\u0000"+
		"\t\n\u00d2\u0000\u0017\u0001\u0000\u0000\u0000\u0002\u001d\u0001\u0000"+
		"\u0000\u0000\u0004/\u0001\u0000\u0000\u0000\u00062\u0001\u0000\u0000\u0000"+
		"\bH\u0001\u0000\u0000\u0000\nM\u0001\u0000\u0000\u0000\f}\u0001\u0000"+
		"\u0000\u0000\u000e\u0085\u0001\u0000\u0000\u0000\u0010\u009a\u0001\u0000"+
		"\u0000\u0000\u0012\u00ad\u0001\u0000\u0000\u0000\u0014\u00af\u0001\u0000"+
		"\u0000\u0000\u0016\u0018\u0003\u0002\u0001\u0000\u0017\u0016\u0001\u0000"+
		"\u0000\u0000\u0018\u0019\u0001\u0000\u0000\u0000\u0019\u0017\u0001\u0000"+
		"\u0000\u0000\u0019\u001a\u0001\u0000\u0000\u0000\u001a\u001b\u0001\u0000"+
		"\u0000\u0000\u001b\u001c\u0005\u0000\u0000\u0001\u001c\u0001\u0001\u0000"+
		"\u0000\u0000\u001d\u001e\u0005\"\u0000\u0000\u001e\u001f\u0005-\u0000"+
		"\u0000\u001f!\u0005\u0001\u0000\u0000 \"\u0003\u0014\n\u0000! \u0001\u0000"+
		"\u0000\u0000!\"\u0001\u0000\u0000\u0000\"#\u0001\u0000\u0000\u0000#&\u0005"+
		"\u0002\u0000\u0000$%\u0005\u0003\u0000\u0000%\'\u0003\b\u0004\u0000&$"+
		"\u0001\u0000\u0000\u0000&\'\u0001\u0000\u0000\u0000\'(\u0001\u0000\u0000"+
		"\u0000()\u0003\u0004\u0002\u0000)*\u0003\n\u0005\u0000*+\u0005#\u0000"+
		"\u0000+\u0003\u0001\u0000\u0000\u0000,.\u0003\u0006\u0003\u0000-,\u0001"+
		"\u0000\u0000\u0000.1\u0001\u0000\u0000\u0000/-\u0001\u0000\u0000\u0000"+
		"/0\u0001\u0000\u0000\u00000\u0005\u0001\u0000\u0000\u00001/\u0001\u0000"+
		"\u0000\u000023\u0005\u0016\u0000\u000038\u0005-\u0000\u000045\u0005\u0004"+
		"\u0000\u000057\u0005-\u0000\u000064\u0001\u0000\u0000\u00007:\u0001\u0000"+
		"\u0000\u000086\u0001\u0000\u0000\u000089\u0001\u0000\u0000\u00009;\u0001"+
		"\u0000\u0000\u0000:8\u0001\u0000\u0000\u0000;<\u0005\u0003\u0000\u0000"+
		"<=\u0003\b\u0004\u0000=\u0007\u0001\u0000\u0000\u0000>I\u0005\u0017\u0000"+
		"\u0000?I\u0005\u0018\u0000\u0000@I\u0005\u0019\u0000\u0000AI\u0005\u001a"+
		"\u0000\u0000BC\u0005\'\u0000\u0000CD\u0005\u0005\u0000\u0000DE\u0005*"+
		"\u0000\u0000EF\u0005\u0006\u0000\u0000FG\u0005(\u0000\u0000GI\u0003\b"+
		"\u0004\u0000H>\u0001\u0000\u0000\u0000H?\u0001\u0000\u0000\u0000H@\u0001"+
		"\u0000\u0000\u0000HA\u0001\u0000\u0000\u0000HB\u0001\u0000\u0000\u0000"+
		"I\t\u0001\u0000\u0000\u0000JL\u0003\f\u0006\u0000KJ\u0001\u0000\u0000"+
		"\u0000LO\u0001\u0000\u0000\u0000MK\u0001\u0000\u0000\u0000MN\u0001\u0000"+
		"\u0000\u0000N\u000b\u0001\u0000\u0000\u0000OM\u0001\u0000\u0000\u0000"+
		"PQ\u0003\u000e\u0007\u0000QR\u0005\u000b\u0000\u0000RS\u0003\u0010\b\u0000"+
		"ST\u0005\u0007\u0000\u0000T~\u0001\u0000\u0000\u0000UV\u0005\u001b\u0000"+
		"\u0000VW\u0003\u0010\b\u0000WX\u0005\u001c\u0000\u0000X[\u0003\n\u0005"+
		"\u0000YZ\u0005\u001d\u0000\u0000Z\\\u0003\n\u0005\u0000[Y\u0001\u0000"+
		"\u0000\u0000[\\\u0001\u0000\u0000\u0000\\]\u0001\u0000\u0000\u0000]^\u0005"+
		"\u001e\u0000\u0000^~\u0001\u0000\u0000\u0000_`\u0005\u001f\u0000\u0000"+
		"`a\u0003\u0010\b\u0000ab\u0005 \u0000\u0000bc\u0003\n\u0005\u0000cd\u0005"+
		"!\u0000\u0000d~\u0001\u0000\u0000\u0000ef\u0003\u0012\t\u0000fh\u0005"+
		"\u0001\u0000\u0000gi\u0003\u0014\n\u0000hg\u0001\u0000\u0000\u0000hi\u0001"+
		"\u0000\u0000\u0000ij\u0001\u0000\u0000\u0000jk\u0005\u0002\u0000\u0000"+
		"kl\u0005\u0007\u0000\u0000l~\u0001\u0000\u0000\u0000mn\u0005$\u0000\u0000"+
		"no\u0003\u000e\u0007\u0000op\u0005\u0007\u0000\u0000p~\u0001\u0000\u0000"+
		"\u0000qr\u0005%\u0000\u0000rs\u0003\u0010\b\u0000st\u0005\u0007\u0000"+
		"\u0000t~\u0001\u0000\u0000\u0000uv\u0005%\u0000\u0000vw\u0005.\u0000\u0000"+
		"w~\u0005\u0007\u0000\u0000xz\u0005&\u0000\u0000y{\u0003\u0010\b\u0000"+
		"zy\u0001\u0000\u0000\u0000z{\u0001\u0000\u0000\u0000{|\u0001\u0000\u0000"+
		"\u0000|~\u0005\u0007\u0000\u0000}P\u0001\u0000\u0000\u0000}U\u0001\u0000"+
		"\u0000\u0000}_\u0001\u0000\u0000\u0000}e\u0001\u0000\u0000\u0000}m\u0001"+
		"\u0000\u0000\u0000}q\u0001\u0000\u0000\u0000}u\u0001\u0000\u0000\u0000"+
		"}x\u0001\u0000\u0000\u0000~\r\u0001\u0000\u0000\u0000\u007f\u0080\u0005"+
		"-\u0000\u0000\u0080\u0081\u0005\u0005\u0000\u0000\u0081\u0082\u0003\u0010"+
		"\b\u0000\u0082\u0083\u0005\u0006\u0000\u0000\u0083\u0086\u0001\u0000\u0000"+
		"\u0000\u0084\u0086\u0003\u0012\t\u0000\u0085\u007f\u0001\u0000\u0000\u0000"+
		"\u0085\u0084\u0001\u0000\u0000\u0000\u0086\u000f\u0001\u0000\u0000\u0000"+
		"\u0087\u0088\u0006\b\uffff\uffff\u0000\u0088\u0089\u0005\u0001\u0000\u0000"+
		"\u0089\u008a\u0003\u0010\b\u0000\u008a\u008b\u0005\u0002\u0000\u0000\u008b"+
		"\u009b\u0001\u0000\u0000\u0000\u008c\u008d\u0005-\u0000\u0000\u008d\u008e"+
		"\u0005\u0005\u0000\u0000\u008e\u008f\u0003\u0010\b\u0000\u008f\u0090\u0005"+
		"\u0006\u0000\u0000\u0090\u009b\u0001\u0000\u0000\u0000\u0091\u0092\u0005"+
		"\u0013\u0000\u0000\u0092\u009b\u0003\u0010\b\u000b\u0093\u0094\u0005\b"+
		"\u0000\u0000\u0094\u009b\u0003\u0010\b\u0007\u0095\u009b\u0005*\u0000"+
		"\u0000\u0096\u009b\u0005+\u0000\u0000\u0097\u009b\u0005)\u0000\u0000\u0098"+
		"\u009b\u0005,\u0000\u0000\u0099\u009b\u0003\u0012\t\u0000\u009a\u0087"+
		"\u0001\u0000\u0000\u0000\u009a\u008c\u0001\u0000\u0000\u0000\u009a\u0091"+
		"\u0001\u0000\u0000\u0000\u009a\u0093\u0001\u0000\u0000\u0000\u009a\u0095"+
		"\u0001\u0000\u0000\u0000\u009a\u0096\u0001\u0000\u0000\u0000\u009a\u0097"+
		"\u0001\u0000\u0000\u0000\u009a\u0098\u0001\u0000\u0000\u0000\u009a\u0099"+
		"\u0001\u0000\u0000\u0000\u009b\u00aa\u0001\u0000\u0000\u0000\u009c\u009d"+
		"\n\n\u0000\u0000\u009d\u009e\u0007\u0000\u0000\u0000\u009e\u00a9\u0003"+
		"\u0010\b\u000b\u009f\u00a0\n\t\u0000\u0000\u00a0\u00a1\u0007\u0001\u0000"+
		"\u0000\u00a1\u00a9\u0003\u0010\b\n\u00a2\u00a3\n\b\u0000\u0000\u00a3\u00a4"+
		"\u0007\u0002\u0000\u0000\u00a4\u00a9\u0003\u0010\b\t\u00a5\u00a6\n\u0006"+
		"\u0000\u0000\u00a6\u00a7\u0007\u0003\u0000\u0000\u00a7\u00a9\u0003\u0010"+
		"\b\u0007\u00a8\u009c\u0001\u0000\u0000\u0000\u00a8\u009f\u0001\u0000\u0000"+
		"\u0000\u00a8\u00a2\u0001\u0000\u0000\u0000\u00a8\u00a5\u0001\u0000\u0000"+
		"\u0000\u00a9\u00ac\u0001\u0000\u0000\u0000\u00aa\u00a8\u0001\u0000\u0000"+
		"\u0000\u00aa\u00ab\u0001\u0000\u0000\u0000\u00ab\u0011\u0001\u0000\u0000"+
		"\u0000\u00ac\u00aa\u0001\u0000\u0000\u0000\u00ad\u00ae\u0005-\u0000\u0000"+
		"\u00ae\u0013\u0001\u0000\u0000\u0000\u00af\u00b0\u0005-\u0000\u0000\u00b0"+
		"\u00b1\u0005\u0003\u0000\u0000\u00b1\u00b8\u0003\b\u0004\u0000\u00b2\u00b3"+
		"\u0005\u0004\u0000\u0000\u00b3\u00b4\u0005-\u0000\u0000\u00b4\u00b5\u0005"+
		"\u0003\u0000\u0000\u00b5\u00b7\u0003\b\u0004\u0000\u00b6\u00b2\u0001\u0000"+
		"\u0000\u0000\u00b7\u00ba\u0001\u0000\u0000\u0000\u00b8\u00b6\u0001\u0000"+
		"\u0000\u0000\u00b8\u00b9\u0001\u0000\u0000\u0000\u00b9\u0015\u0001\u0000"+
		"\u0000\u0000\u00ba\u00b8\u0001\u0000\u0000\u0000\u0010\u0019!&/8HM[hz"+
		"}\u0085\u009a\u00a8\u00aa\u00b8";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}