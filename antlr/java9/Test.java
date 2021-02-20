import java.util.*;
import org.antlr.runtime.tree.CommonTreeNodeStream;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

public class Main {
	public static void main(String[] args) throws Exception {
		//CharStream charStream = CharStreams.fromString("test");
		CharStream charStream = CharStreams.fromFileName("Test.java");
		Java9Lexer lexer = new Java9Lexer(charStream);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		Java9Parser parser = new Java9Parser(tokens);
		CompilationUnitContext root = parser.compilationUnit();
		CommonTreeNodeStream ast = new CommonTreeNodeStream(root);
		//ExprTraverse traverser = new ExprTraverse(ast);

		System.out.println("tree: " + root.toStringTree());
		//System.out.println("eval: " + traverser.expr());
	}
}
