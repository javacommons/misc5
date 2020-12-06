#! node
class Rectangle0 {
    constructor(width, height) {
        this.width = width;
        this.height = height;
    }
    area() {
        return this.width * this.height;
    }
}

class Rectangle1 extends Rectangle0 {
    constructor(width, height, bonus=0) {
        super(width, height);
        this.bonus = bonus;
    }
    area() {
        return super.area() + this.bonus;
    }
}

const rect0 = new Rectangle0(20, 10);
console.log(rect0.area());

const rect1 = new Rectangle1(20, 10, 23);
console.log(rect1.area());
