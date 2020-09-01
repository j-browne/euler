pub fn main() {
    let mut res = 0;
    let mut new = 1;
    let mut old = 0;
    loop {
        let tmp = old;
        old = new;
        new = old + tmp;
        if new > 4000000 {
            break;
        }
        if new % 2 == 0 {
            res = res + new;
        }
    }
    println!("{}", res);
}
