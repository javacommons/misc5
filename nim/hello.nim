# https://qiita.com/nunulk/items/e3679ce256b8071e5255

echo "helloハロー한자";

# int -> string
var n = 1
echo "n=" & $n

# sequence
var members = @["John", "Paul"]
add(members, "George")
echo "members=" & $members
# or
echo "members=" & repr(members)

var nn = 1
nn = 2
echo "nn=" & $nn

proc getAlphabet(): string =
  var accm = ""
  for letter in 'a'..'z':  # see iterators
    accm.add(letter)
  return accm

# Computed at compilation time
const alphabet = getAlphabet()

echo alphabet
# >> abcdefghijklmnopqrstuvwxyz

proc getAlphabet2(): string =
  result = ""
  for letter in 'a'..'z':
    result.add(letter)

echo getAlphabet2()

let nnn = 10
if nnn == 0:
  echo "zero"
elif nnn mod 2 == 0:
  echo "even"
else:
  echo "odd"

let nnnn = 0
let s = if nnnn == 0: "zero"
        elif nnnn mod 2 == 0: "even"
        else: "odd"

echo s
