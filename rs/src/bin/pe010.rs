pub fn main() {
    let mut i = 3;
    let mut res = 2;
    let mut primes = vec![2];

    while i < 2000000 {
        let mut p = true;
        for j in primes.iter() {
            if i % *j == 0 {
                p = false;
                break;
            }
        }
        if p {
            res = res + i;
            primes.push(i);
        }
        i = i + 2;
    }

    println!("{}", res);
}
