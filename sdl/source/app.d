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
    string name = result[2].name();
    writeln(name);
    SDLValue val = result[2].getAttribute("email");
    writeln(val.to!string);
    writeln(result[2].values[0].to!string);
    writeln(result[2].values[0].isText);
    writeln(result[2].values[0].textValue);
    string qname = result[6].qualifiedName();
    writeln(qname);
    writeln(result[6].name());
    /*final*/ switch (result[2].values[0].kind)
    {
    case SDLValue.Kind.null_:
        writeln("case SDLValue.Kind.null_:");
        break;

    case SDLValue.Kind.text:
        writeln("case SDLValue.Kind.text:");
        break;

    case SDLValue.Kind.binary:
        writeln("case SDLValue.Kind.binary:");
        break;
    default:
        writeln("default:");
        break;
    }
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
