fn main() {
    //println!("cargo:rustc-link-search=native=.");
    println!("cargo:rustc-flags=-L ../cpp2");
}
