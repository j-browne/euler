pub fn main() {
    let mut i: i64 = 600851475143;
    let mut n = 2;
    loop {
        while i % n == 0 {
            i = i / n;
        }
        if i == 1 {
            break;
        }
        n = n + 1;
    }

    println!("{}", n);
}
