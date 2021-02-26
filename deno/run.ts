// Copyright 2018-2020 the Deno authors. All rights reserved. MIT license.
console.log("Welcome to Deno 🦕");

// 変数に型を与えて宣言。
var onigiri: string = 'onigiri', // String型
    calories: number = 200;  // Number型

// 関数の仮引数にも受け入れる型を定義。
// {}の前にあるstringは関数の返す値の型を定義している。
function todaysMeal(food: string, energy: number): string {
    return `My ${food} has ${energy} calories`
}

console.log(todaysMeal(onigiri, calories));

// Personインターフェースをとその要素を型と共に定義。
interface Person {
    name: string;
    age: number;
}

// 関数はPersonインターフェースの構造を満たすオブジェクトを受け取る。
function intro(person: Person): string {
    return `My name is ${person.name}. I am ${person.age}!`
}

// Personインターフェースの構造に従う変数を定義します。
var ken = {
    name: 'Ken',
    age: 20
}

// 関数を実行します。
console.log(intro(ken)) //=> My name is Ken. I am 20!
