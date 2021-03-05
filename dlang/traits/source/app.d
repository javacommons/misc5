import json_parser;
import std.stdio;

void main() {
    enum tree = JSONParser(`[{"foo": 42, "xyz": 777}, ["bar", -42, true], 4.2, false, null]`);
    writeln(tree);

    auto result = convert(tree);
    writeln(result);
}
