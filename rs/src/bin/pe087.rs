use num_integer::nth_root;
use prime_tools::get_primes_less_than_x;
use std::collections::HashSet;

const MAX: u32 = 50_000_000;

fn main() {
    let primes = get_primes_less_than_x(nth_root(MAX, 2) + 1);

    let mut nums = HashSet::new();
    for i in primes
        .iter()
        .map(|x| x * x * x * x)
        .take_while(|x| *x <= MAX)
    {
        for j in primes
            .iter()
            .map(|x| x * x * x)
            .take_while(|x| *x <= MAX - i)
        {
            for k in primes
                .iter()
                .map(|x| x * x)
                .take_while(|x| *x <= MAX - i - j)
            {
                nums.insert(i + j + k);
            }
        }
    }

    println!("{}", nums.len());
}
