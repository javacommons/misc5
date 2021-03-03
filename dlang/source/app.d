private string toSjis(string s)
{
	import std.conv : to;
	import std.windows.charset : toMBSz;

	return (to!string(toMBSz(s)));
}

void main()
{
	import std.stdio: writeln;

	writeln("Ｄ言語の世界へようこそ".toSjis);
}
