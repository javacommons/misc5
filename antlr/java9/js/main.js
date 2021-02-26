//const antlr4 = require('antlr4/index');
import { antlr4 } from "./antlr4/index.js";
//const Java8Lexer = require('./Java8Lexer').ChatLexer;
import { Java8Lexer } from "./Java8Lexer.js";
//const Java8Parser = require('./Java8Parser').ChatParser;
import { Java8Parser } from "./Java8Parser.js";
//const HtmlJava8Listener = require('./HtmlJava8Listener').HtmlChatListener;

const input = 'peter SAYS: hello :-) \npaul SHOUTS: ayo :)\n';

const chars = new antlr4.InputStream(input);
const lexer = new Java8exer(chars);
const tokens = new antlr4.CommonTokenStream(lexer);
const parser = new Java8Parser(tokens);
parser.buildParseTrees = true;

/**
 * We set the root node of the tree as a chat rule. 
 * You want to invoke the parser specifying a rule which typically is the first rule. 
 * However you can actually invoke any rule directly.
 */
const tree = parser.chat();

//const htmlChat = new HtmlChatListener(res);
//antlr4.tree.ParseTreeWalker.DEFAULT.walk(htmlChat, tree);
