/*
use std::collections::HashSet;
use std::io::Write;

fn is_palindrome(n: u32) -> bool {
    let mut res = true;
    let mut v = Vec::<u8>::new();
    let _ = write!(&mut v, "{}", n);
    let s = String::from_utf8(v).unwrap();
    for i in 0..(s.len() / 2) {
        if s[i] == s[s.len() - i - 1] {
            res = false;
            break;
        }
    }
    res
}
*/

fn main() {
    /*
        let mut s = HashSet::<u32>::new();
        for i in 10..100 {
            for j in i..100 {
                if is_palindrome(i * j) {
                    s.insert(i * j);
                }
            }
        }
        println!("{}", s.iter().max().unwrap());
    */
}
