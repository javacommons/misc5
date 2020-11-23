#! node
var hooclass = class {
    constructor(z) {
        this.z = z
    }
    get getZ() {
        return this.z
    }
    set setZ(z) {
        /* set構文 */
        this.z = z
    }
}
/* hooclassの継承 */
var taaclass = class extends hooclass {
    constructor(z, num) {
        super(z) /* 親クラスのコンストラクタ */
        this.num = num
    }
    calc() {
        return this.z * this.num
    }
}

var taa = new taaclass(20, 3)
console.log(taa.calc()) /* 300が出力される */
taa.setZ = 100 /* 親クラスのメソッドでプロパティに値を設定する */
console.log(taa.calc()) /* 300が出力される */
