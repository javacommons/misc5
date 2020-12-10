#[link(name="foo", kind="static")]
extern{
    fn foo();
}

fn main() {
    unsafe {foo();};
}
