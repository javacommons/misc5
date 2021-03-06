import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.Trees;
import org.json.JSONArray;
import org.json.JSONObject;

import net.arnx.jsonic.JSON;

class Antlr4Trees {

	Parser parser;

	public Antlr4Trees(Parser parser) {
		this.parser = parser;
	}

	public String getText(ParseTree t) {
		if (t.getChildCount() == 0) {
			return t.getText();
		}
		StringBuilder builder = new StringBuilder();
		for (int i = 0; i < t.getChildCount(); i++) {
			if(i>0) builder.append(" ");
			builder.append(getText(t.getChild(i)));
		}
		return builder.toString();

	}

	public List getList(ParseTree t) {
		List result = new ArrayList();
		if (t.getChildCount() == 0) {
			result.add(t.getText());
			return result;
		}
		//StringBuilder builder = new StringBuilder();
		for (int i = 0; i < t.getChildCount(); i++) {
			result.addAll(getList(t.getChild(i)));
		}
		return result;

	}

}

class EvalVisitor extends Java9BaseVisitor<Object> {

	Parser parser;
	Antlr4Trees trees;
	Deque<Map<String, Object>> deque = new ArrayDeque<>();

	public EvalVisitor(Parser parser) {
		this.parser = parser;
		this.trees = new Antlr4Trees(this.parser);
	}

	@Override public Object visitCompilationUnit(Java9Parser.CompilationUnitContext ctx) {
		Map<String, Object> result = new LinkedHashMap<>();
		String me = Trees.getNodeText(ctx, this.parser);
		result.put("rule", Trees.getNodeText(ctx, this.parser));
		result.put("imports", new ArrayList());
		result.put("types", new ArrayList());
		deque.push(result);
		visitChildren(ctx);
		deque.pop();
		return result;
	}

	@Override
	public Object visitImportDeclaration(Java9Parser.ImportDeclarationContext ctx) {
		Map<String, Object> result = new LinkedHashMap<>();
		result.put("rule", Trees.getNodeText(ctx, this.parser));
		result.put("tokens", trees.getList(ctx));
		((List)deque.peek().get("imports")).add(result);
		return null;
	}

	@Override public Object visitTypeDeclaration(Java9Parser.TypeDeclarationContext ctx) {
		Map<String, Object> result = new LinkedHashMap<>();
		((List)deque.peek().get("types")).add(result);
		deque.push(result);
		visitChildren(ctx);
		deque.pop();
		return null;
	}

	@Override public Object visitNormalClassDeclaration(Java9Parser.NormalClassDeclarationContext ctx) {
		deque.peek().put("rule", Trees.getNodeText(ctx, this.parser));
		for(int i=0; i<ctx.children.size(); i++)
		{
			String child = Trees.getNodeText(ctx.children.get(i), this.parser);
			//System.out.printf("child: %s\n",  child);
			if(child.equals("identifier"))
			{
				System.out.println(ctx.children.get(i).getText());
				deque.peek().put("idintifier", ctx.children.get(i).getText());
			}
		}
		deque.peek().put("methods", new ArrayList());
		visitChildren(ctx);
		return null;
	}

	@Override public Object visitMethodDeclaration(Java9Parser.MethodDeclarationContext ctx) {
		Map<String, Object> result = new LinkedHashMap<>();
		result.put("rule", Trees.getNodeText(ctx, this.parser));
		result.put("modifiers", new ArrayList());
		//result.put("tokens", trees.getList(ctx));
		((List)deque.peek().get("methods")).add(result);
		deque.push(result);
		visitChildren(ctx);
		deque.pop();
		return null;
	}

	@Override public Object visitMethodDeclarator(Java9Parser.MethodDeclaratorContext ctx) {
		deque.peek().put("rule", Trees.getNodeText(ctx, this.parser));
		for(int i=0; i<ctx.children.size(); i++)
		{
			String child = Trees.getNodeText(ctx.children.get(i), this.parser);
			//System.out.printf("child: %s\n",  child);
			if(child.equals("identifier"))
			{
				System.out.println(ctx.children.get(i).getText());
				deque.peek().put("idintifier", ctx.children.get(i).getText());
			}
		}
		visitChildren(ctx);
		return null;
	}

	@Override public Object visitMethodModifier(Java9Parser.MethodModifierContext ctx) {
		for(int i=0; i<ctx.children.size(); i++)
		{
			//String child = Trees.getNodeText(ctx.children.get(i), this.parser);
			//System.out.printf("child: %s\n",  child);
			//System.out.println(ctx.children.get(i).getText());
			((List)deque.peek().get("modifiers")).add(ctx.children.get(i).getText());
		}
		visitChildren(ctx);
		return null;
	}

	@Override public Object visitMethodHeader(Java9Parser.MethodHeaderContext ctx) {
		deque.peek().put("header", trees.getList(ctx));
		visitChildren(ctx);
		return null;
	}


}

public class Main {
	public static void main(String[] args) throws Exception {
		//CharStream charStream = CharStreams.fromString("test");
		CharStream charStream = CharStreams.fromFileName("Test.java");
		Java9Lexer lexer = new Java9Lexer(charStream);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		Java9Parser parser = new Java9Parser(tokens);
		ParserRuleContext root = parser.compilationUnit();
		AntlrCutter cutter = new AntlrCutter(parser, root);
		/*
		cutter.cut(Arrays.asList(
				"singleTypeImportDeclaration",
				"packageOrTypeName",
				"typeDeclaration"));
				*/
		System.out.println("tree: " + root.toStringTree(parser));
		List<String> ruleNamesList = Arrays.asList(parser.getRuleNames());
		String prettyTree = TreeUtils.toPrettyTree(root, ruleNamesList);
		System.out.println(prettyTree);
		Object result = new EvalVisitor(parser).visit(root);
		System.out.println(result);
		String resultJson = JSON.encode(result, true);
		System.out.println(resultJson);

		JSONObject obj = new JSONObject();
        obj.put("name", "Taro Tanaka");
        obj.put("age", 30);
        System.out.println(obj);

        String script = "[ \"Taro\", \"Tanaka\"]";
        JSONArray arr = new JSONArray(script);
        List<String> list = new ArrayList<>();
        for(Object str : arr) {
            list.add((String) str);
        }
        System.out.println(list);

        script = "{ \"name\":\"Taro Tanaka\", \"age\":30}";
        JSONObject obj2 = new JSONObject(script);
        Map<String, Object> map = new HashMap<>();
        for(Object key : obj2.keySet()) {
            map.put((String) key, obj2.get((String) key));
        }
        System.out.println(map);

        List list2 = (List)JSON.decode("[1, \"a\", {\"x\": 123.4}, false]");
        System.out.println(list2);
        String text = JSON.encode(list2, true);
        System.out.println(text);

        Map map2 = (Map)JSON.decode("{\"x\": 123.4}");
        System.out.println(map2);
        String text2 = JSON.encode(map2, true);
        System.out.println(text2);

	}
}