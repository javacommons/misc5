import java.util.Arrays;
import java.util.List;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.ParserRuleContext;

public class Main {
	public static void main(String[] args) throws Exception {
		//CharStream charStream = CharStreams.fromString("test");
		CharStream charStream = CharStreams.fromFileName("Test.java");
		Java9Lexer lexer = new Java9Lexer(charStream);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		Java9Parser parser = new Java9Parser(tokens);
		ParserRuleContext root = parser.compilationUnit();
		AntlrCutter cutter = new AntlrCutter(parser, root);
		cutter.cut(Arrays.asList(
				"singleTypeImportDeclaration",
				"packageOrTypeName",
				"typeDeclaration"));
		System.out.println("tree: " + root.toStringTree(parser));
		List<String> ruleNamesList = Arrays.asList(parser.getRuleNames());
		String prettyTree = TreeUtils.toPrettyTree(root, ruleNamesList);
		System.out.println(prettyTree);
	}
}