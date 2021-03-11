module app;

import std.conv;
import std.stdio;
import std.file;
import sdlite;

int main(string[] args)
{
    writeln("hello!");
    SDLNode[] result;
    string content = readText("sample.sdl");
    parseSDLDocument!((n) { result ~= n; })(content, "test-input");
    writeln(result.to!string);
    writeln(result.length);
    string name = result[1].name();
    writeln(name);
    string qname = result[1].qualifiedName();
    writeln(qname);
    SDLValue val = result[1].getAttribute(qname);
    writeln(val.to!string);
    writeln(result[1].values[0].to!string);
    writeln(result[1].values[0].isText);
    writeln(result[1].values[0].textValue);
    return 0;
}

/+++++
/** A single SDLang value
*/
alias SDLValue = TaggedUnion!SDLValueFields;

struct SDLValueFields {
	Void null_;
	string text;
	immutable(ubyte)[] binary;
	int int_;
	long long_;
	long[2] decimal;
	float float_;
	double double_;
	bool bool_;
	SysTime dateTime;
	Date date;
	Duration duration;
}
+++++/