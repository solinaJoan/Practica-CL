// Generated from /home/joan/UPC/CL/CL-lab/practica/asl/Asl.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link AslParser}.
 */
public interface AslListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link AslParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(AslParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(AslParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(AslParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(AslParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#declarations}.
	 * @param ctx the parse tree
	 */
	void enterDeclarations(AslParser.DeclarationsContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#declarations}.
	 * @param ctx the parse tree
	 */
	void exitDeclarations(AslParser.DeclarationsContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#variable_decl}.
	 * @param ctx the parse tree
	 */
	void enterVariable_decl(AslParser.Variable_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#variable_decl}.
	 * @param ctx the parse tree
	 */
	void exitVariable_decl(AslParser.Variable_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(AslParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(AslParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStatements(AslParser.StatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStatements(AslParser.StatementsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code assignStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterAssignStmt(AslParser.AssignStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code assignStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitAssignStmt(AslParser.AssignStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ifStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(AslParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ifStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(AslParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code whileStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(AslParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code whileStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(AslParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code procCall}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterProcCall(AslParser.ProcCallContext ctx);
	/**
	 * Exit a parse tree produced by the {@code procCall}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitProcCall(AslParser.ProcCallContext ctx);
	/**
	 * Enter a parse tree produced by the {@code readStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterReadStmt(AslParser.ReadStmtContext ctx);
	/**
	 * Exit a parse tree produced by the {@code readStmt}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitReadStmt(AslParser.ReadStmtContext ctx);
	/**
	 * Enter a parse tree produced by the {@code writeExpr}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWriteExpr(AslParser.WriteExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code writeExpr}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWriteExpr(AslParser.WriteExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code writeString}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWriteString(AslParser.WriteStringContext ctx);
	/**
	 * Exit a parse tree produced by the {@code writeString}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWriteString(AslParser.WriteStringContext ctx);
	/**
	 * Enter a parse tree produced by the {@code return}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterReturn(AslParser.ReturnContext ctx);
	/**
	 * Exit a parse tree produced by the {@code return}
	 * labeled alternative in {@link AslParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitReturn(AslParser.ReturnContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#left_expr}.
	 * @param ctx the parse tree
	 */
	void enterLeft_expr(AslParser.Left_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#left_expr}.
	 * @param ctx the parse tree
	 */
	void exitLeft_expr(AslParser.Left_exprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code intVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterIntVal(AslParser.IntValContext ctx);
	/**
	 * Exit a parse tree produced by the {@code intVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitIntVal(AslParser.IntValContext ctx);
	/**
	 * Enter a parse tree produced by the {@code charVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterCharVal(AslParser.CharValContext ctx);
	/**
	 * Exit a parse tree produced by the {@code charVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitCharVal(AslParser.CharValContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arithmetic}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterArithmetic(AslParser.ArithmeticContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arithmetic}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitArithmetic(AslParser.ArithmeticContext ctx);
	/**
	 * Enter a parse tree produced by the {@code floatVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterFloatVal(AslParser.FloatValContext ctx);
	/**
	 * Exit a parse tree produced by the {@code floatVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitFloatVal(AslParser.FloatValContext ctx);
	/**
	 * Enter a parse tree produced by the {@code unary}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterUnary(AslParser.UnaryContext ctx);
	/**
	 * Exit a parse tree produced by the {@code unary}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitUnary(AslParser.UnaryContext ctx);
	/**
	 * Enter a parse tree produced by the {@code boolVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterBoolVal(AslParser.BoolValContext ctx);
	/**
	 * Exit a parse tree produced by the {@code boolVal}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitBoolVal(AslParser.BoolValContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenthesis}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterParenthesis(AslParser.ParenthesisContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenthesis}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitParenthesis(AslParser.ParenthesisContext ctx);
	/**
	 * Enter a parse tree produced by the {@code not}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNot(AslParser.NotContext ctx);
	/**
	 * Exit a parse tree produced by the {@code not}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNot(AslParser.NotContext ctx);
	/**
	 * Enter a parse tree produced by the {@code functionCall}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterFunctionCall(AslParser.FunctionCallContext ctx);
	/**
	 * Exit a parse tree produced by the {@code functionCall}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitFunctionCall(AslParser.FunctionCallContext ctx);
	/**
	 * Enter a parse tree produced by the {@code exprIdent}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExprIdent(AslParser.ExprIdentContext ctx);
	/**
	 * Exit a parse tree produced by the {@code exprIdent}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExprIdent(AslParser.ExprIdentContext ctx);
	/**
	 * Enter a parse tree produced by the {@code relational}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterRelational(AslParser.RelationalContext ctx);
	/**
	 * Exit a parse tree produced by the {@code relational}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitRelational(AslParser.RelationalContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arrayAccess}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterArrayAccess(AslParser.ArrayAccessContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arrayAccess}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitArrayAccess(AslParser.ArrayAccessContext ctx);
	/**
	 * Enter a parse tree produced by the {@code logic}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterLogic(AslParser.LogicContext ctx);
	/**
	 * Exit a parse tree produced by the {@code logic}
	 * labeled alternative in {@link AslParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitLogic(AslParser.LogicContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#array}.
	 * @param ctx the parse tree
	 */
	void enterArray(AslParser.ArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#array}.
	 * @param ctx the parse tree
	 */
	void exitArray(AslParser.ArrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#ident}.
	 * @param ctx the parse tree
	 */
	void enterIdent(AslParser.IdentContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#ident}.
	 * @param ctx the parse tree
	 */
	void exitIdent(AslParser.IdentContext ctx);
	/**
	 * Enter a parse tree produced by {@link AslParser#params}.
	 * @param ctx the parse tree
	 */
	void enterParams(AslParser.ParamsContext ctx);
	/**
	 * Exit a parse tree produced by {@link AslParser#params}.
	 * @param ctx the parse tree
	 */
	void exitParams(AslParser.ParamsContext ctx);
}