// Some playing around with ragel.
// Install ragel (e.g. `brew install ragel`)
// Compile with `ragel -Z json.rl`
package main

import (
	"fmt"
)

// Ragel expects these variables to be declared in the host program
var (
	// Index of the current state.
	cs int
	// Pointer to the input. In Go it is an offset.
	p int
	// Pointer to the end of the input. In Go it is the length.
	pe int
	// eof must be set to pe if we reached end of file, -1 otherwise.
	// The distinction between eof and pe is, that our input
	// might be split into blocks (think network) and pe marks
	// end of a block, eof marks when a block is the last block.
	eof int = -1
	// data is the input, Go only.
	data []byte
	// Stack for stack-based machines (optional). Resizing must be
	// taken care of by the user.
	stack []int
	// Pointer to the top of the sack (optional).
	top int
	// ???
	act int
	// ???
	ts int
	// ???
	te int
)

func main() {
	data = []byte(`{"abc":"def","hij": 123}`)
	pe = len(data)
	eof = pe
	machine()
	fmt.Printf("Done\n")
}

%% machine json;

%%{

	# '=' => Pattern definition
	# ':=' => Machine instantiation

	Quote = '"';
	StringStart = Quote;
	String = [^"]+ Quote @{fmt.Println("Found string")};
	StringParser := String @{fret;};

	FloatStart = [+\-0-9];
	Float = (([0-9]* '.')? [0-9]+ ([eE][+\-]?[0-9]+)?)@{fmt.Println("Found float")};
	FloatParser := Float @{fret;};

	# 'fcall' puts the current state on the stack
	# and jumps to the given machine.
	ArrayStart = '[';
	Array = []@{fcall JSON;} (',' @{fcall JSON;})* ']' @{fmt.Println("Found array")};
	ArrayParser := Array @{fret;};

	ObjectStart = '{';
	ObjectItem = StringStart String ':' @{fcall JSON;};
	Object = (ObjectItem (',' ObjectItem)*)? '}' @{fmt.Println("Found object")};
	ObjectParser := Object @{fret;};

	# 'fret' jumps back to the last machine state on the stack.

	JSON := (
		StringStart > {fcall StringParser;} |
		FloatStart > {fcall FloatParser;} |
		ArrayStart > {fcall ArrayParser;} |
		ObjectStart > {fcall ObjectParser;}
		) @{fret;};

	main := (
		StringStart > {fcall StringParser;} |
		FloatStart > {fcall FloatParser;} |
		ArrayStart > {fcall ArrayParser;} |
		ObjectStart > {fcall ObjectParser;}
		);

}%%

%%{
 	# Handle stack growth
	prepush {
		fmt.Printf("PUSH!\n")
		if stack == nil || len(stack) == cap(stack) {
			new_stack := make([]int, len(stack), cap(stack)*2)
			copy(new_stack, stack)
			stack = new_stack
		}
		// Append new element
		stack = append(stack, 0)
	}

 	# Handle stack shrinking
	postpop {
		fmt.Printf("POP!\n")
		stack = stack[0:len(stack)-1]
	}
}%%

%% write data;

func machine() {
	// Put initialization code here
	%% write init;
	// Put execution code here
	%% write exec;
}