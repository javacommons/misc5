module json_parser;

import pegged.grammar;
import std.algorithm, std.array, std.conv, std.string, std.typecons, std.variant;

alias JSON = Algebraic!(This[string], This[], string, double, int, bool, typeof(null));

mixin(grammar(`
JSONParser:
    Value < Object / Array / String / Float / Integer / True / False / Null
    Pair < String ":" Value
    Object < :"{" (Pair (:"," Pair)*)* :"}"
    Array < :"[" (Value (:"," Value)*)* "]"
    String < :doublequote (!doublequote .)* :doublequote
    Float <- Integer "." [0-9]+
    Integer <- ("+" / "-")? ("0" / [1-9] [0-9]*)
    True <- "true"
    False <- "false"
    Null <- "null"
`));

JSON convert(ParseTree tree) {
    switch (tree.name) {
        case "JSONParser":
            return convert(tree.children.front);

        case "JSONParser.Value":
            return convert(tree.children.front);

        case "JSONParser.Object":
            JSON[string] object = null;
            foreach (pair; tree.children) {
                import std.stdio: writeln;
                writeln(pair.children[0].matches);
                object[pair.children[0].matches.join] = convert(pair.children[1]);
            }
            return JSON(object);

        case "JSONParser.Array":
            return JSON(tree.children.map!convert.array);

        case "JSONParser.String":
            return JSON(tree.matches.join); 

        case "JSONParser.Integer":
            return JSON(tree.matches.join.to!int);

        case "JSONParser.Float":
            return JSON(tree.matches.join.to!double);

        case "JSONParser.True":
            return JSON(true);

        case "JSONParser.False":
            return JSON(false);

        case "JSONParser.Null":
            return JSON(null);

        default:
            throw new Exception(tree.name ~ " is not implemented yet");
    }
}
