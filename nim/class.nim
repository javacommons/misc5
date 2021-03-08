import strformat

type
  Person = object of RootObj #Javaの`Object`相当である、RootObjを継承しておく
    name:string
    age:int
proc hello(p:Person)=
  echo fmt"I am {p.name}. I am Person!"
proc howOld(p:Person)=
  echo fmt"I am {p.age} years old."

type
  Student = object of Person #Personを継承
    grade:int
proc hello(s:Student)=
  echo fmt" am {s.name}. I am {$s.grade} grade Student!"

let p = Person(name:"Bob",age:20)
let s = Student(name:"Julia",age:18,grade:4)

p.hello #=> 親のhelloプロシージャ 
s.hello #=> 子のhelloプロシージャ
s.howOld #=> 子に定義はない。親のhowOldプロシージャが呼ばれる
