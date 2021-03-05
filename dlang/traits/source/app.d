import json_parser;
import std.stdio;
import std.array;

//import std.typecons: tuple;
import pegged.grammar;

/** */
class JSONVisitor
{
    /** */
    JSON visit(ParseTree tree)
    {
        visitChildren(tree);
        return JSON(null);
    }

    protected void visitChildren(ParseTree tree)
    {
        foreach (ref child; tree.children)
        {
            writeln(child.name);
            string childName = child.name.split(".")[$ - 1];
            writeln(childName);
            string methodName = "visit_" ~ childName;
            writeln(methodName);
            callMethod(methodName, child);
        }
    }

    protected void callMethod(string methodName, ParseTree node)
    {
        import std.traits;

        writeln(methodName);
        auto members = __traits(allMembers, typeof(this));
        writeln(members);
        foreach (member; members)
        {
            writefln("member=%s", member);
        }
    method_switch:
        switch (methodName)
        {
            // but inside, we use a static foreach - a compile-time loop -
            // over the __traits(allMembers) magic, which gives a list of all member names
            static foreach (inspecting; __traits(allMembers, typeof(this)))
            {
        case inspecting:
                { // you can create switch cases inside these static loops
                    // for this example, I only want to use callable methods, so this
                    // static if - a compile time if statement - will filter out anything else.
                    //
                    // It is possible to do more, like plain data members, child classes, and more,
                    // but that will add a lot more code. Same basic ideas with each of them though.
                    static if (isCallable!(__traits(getMember, this, inspecting)))
                    {
                        // after we confirm it is callable, we can get a delegate of it
                        // (same as normally doing `&member.method`) to call later.
                        auto callable = &__traits(getMember, this, inspecting);

                        // next is building the argument list. Parameters comes from the std.traits
                        // module in the standard library and gives an object representing the function's
                        // parameters. We can loop over these and set them!
                        Parameters!callable arguments;
                        foreach (i, ref arg; arguments)
                        { // ref loop cuz we setting the arg members..
                            // so for the runtime bridge here, I took everything as strings and
                            // want to convert them to the actual method arguments. In many cases,
                            // that automatic conversion will not be possible. The next bit of magic,
                            // __traits(compiles), will take some code and return true if it successfully
                            // compiles. Using the static if block, I can turn what would be compile time
                            // errors into a runtime exception instead.
                            static if (__traits(compiles, to!(typeof(arg))(args[i]))) // note that to is from the stdlib again: std.conv. It converts
                                // a thing from one type to another. Here, I ask it to convert our
                                // string (args is the runtime array of strings the user passed) to
                                // whatever the type is that the method expects.
                                //
                                // Note that this might throw an exception if the string is wrong.
                                // For example, passing "lol" to a method expecting an int will throw
                                // an exception saying cannot convert string "lol" to int.
                                arg = to!(typeof(arg))(args[i]);
                            else // or if the conversion didn't compile at all, it will always throw.
                                throw new Exception("method " ~ methodName
                                        ~ " not callable with this reflection code because of incompatible argument type");
                        }

                        // now that we have the arguments, time to tackle the return value.
                        // the main special case here is a void return - that is not a value
                        // and thus cannot be converted. So we do it separately.

                        // Otherwise, though, inside we just call our callable from above with
                        // the arguments from above and return the value converted to string!

                        callable(arguments);
                        return;
                    }
                }
                break method_switch;
            }
        default:
            throw new Exception("no such method " ~ methodName);
        }
        assert(0); // not reached
    }

    protected void visit_Value(ParseTree node)
    {

    }
}

void main()
{
    enum tree = JSONParser(`[{"foo": 42, "xyz": 777}, ["bar", -42, true], 4.2, false, null]`);
    writeln(tree);

    auto visitor = new JSONVisitor();
    auto json = visitor.visit(tree);
    writeln(json);

    auto result = convert(tree);
    writeln(result);
}
