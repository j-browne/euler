use std::collections::HashSet;
use std::io::Write;

fn is_palindrome(n: u32) -> bool {
    let mut res = true;
    let mut v = Vec::<u8>::new();
    let _ = write!(&mut v, "{}", n);
    let s = String::from_utf8(v).unwrap();
    for (forward, backward) in s.chars().zip(s.chars().rev()) {
        if forward != backward {
            res = false;
            break;
        }
    }
    res
}

fn main() {
    let mut s = HashSet::<u32>::new();
    for i in 100..1000 {
        for j in i..1000 {
            if is_palindrome(i * j) {
                s.insert(i * j);
            }
        }
    }
    println!("{}", s.iter().max().unwrap());
}
