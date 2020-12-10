// https://doc.rust-lang.org/std/ffi/struct.CStr.html
// https://moshg.github.io/rust-std-ja/std/ffi/struct.CString.html
use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_char;

#[link(name = "foo", kind = "static")]
extern "C" {
    fn foo();
    fn my_printer(s: *const c_char);
    fn my_string() -> *const c_char;
}

fn my_string_safe() -> String {
    unsafe {
        CStr::from_ptr(my_string()).to_string_lossy().into_owned()
    }
}

fn main() {
    unsafe {
        foo();
    };
    // We are certain that our string doesn't have 0 bytes in the middle,
    // so we can .unwrap()
    let c_to_print = CString::new("Hello, world!").unwrap();
    unsafe {
        my_printer(c_to_print.as_ptr());
    }
    unsafe {
        let slice = CStr::from_ptr(my_string());
        println!(
            "string buffer size without nul terminator: {}",
            slice.to_bytes().len()
        );
    }
    println!("string: {}", my_string_safe());
}
