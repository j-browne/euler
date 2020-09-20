use num_integer::nth_root;
use prime_tools::get_primes_less_than_x;
use std::collections::HashSet;

const MAX: u32 = 50_000_000;

fn main() {
    let primes = get_primes_less_than_x(nth_root(MAX, 2) + 1);

    let mut nums = HashSet::new();
    for i in primes.iter().take_while(|x| **x <= nth_root(MAX, 4)) {
        let rem = MAX - u32::pow(*i, 4);
        for j in primes.iter().take_while(|x| **x <= nth_root(rem, 3)) {
            let rem = rem - u32::pow(*j, 3);
            for k in primes.iter().take_while(|x| **x <= nth_root(rem, 2)) {
                let rem = rem - u32::pow(*k, 2);
                nums.insert(rem);
            }
        }
    }

    println!("{}", nums.len());
}
