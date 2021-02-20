import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.Trees;

public class AntlrCutter { // ParserRuleContext

	Parser parser;
	ParseTree root;
	List<String> ruleNames;

	public AntlrCutter(Parser parser, ParserRuleContext root) {
		this.parser = parser;
		this.root = root;
		this.ruleNames = Arrays.asList(parser.getRuleNames());
	}

	public void cut(List<String> targets) {
		process(root, targets);
	}

	private List<ParseTree> process(ParseTree t, List<String> targets) {
		List<ParseTree> result = new ArrayList<>();
		String label = Trees.getNodeText(t, ruleNames);
		if (t.getChildCount() == 0) {
			//System.out.printf("LEAF: %s\n", label);
			result.add(t);
			return result;
		} //else
			//System.out.printf("TREE: %s\n", label);
		ParserRuleContext context = (ParserRuleContext) t;
		List<ParseTree> children = context.children;
		List<ParseTree> altered = new ArrayList<>();
		for (int i = 0; i < children.size(); i++) {
			List<ParseTree> list = process(children.get(i), targets);
			altered.addAll(list);
		}
		context.children = altered;
		if (targets.contains(label)) {
			return altered;
		}
		result.add(t);
		return result;
	}

}
