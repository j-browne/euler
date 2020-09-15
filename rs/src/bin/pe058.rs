//use euler::primes::is_prime;
use prime_tools::is_u32_prime;

fn main() {
    let mut prime_tot = 0;
    let mut nonprime_tot = 1; // 1 because we're counting the middle, too
    let mut curr = 1;

    for side_len in (3..).step_by(2) {
        for _ in 0..4 {
            curr += side_len - 1;
            if is_u32_prime(curr) {
                prime_tot += 1;
            } else {
                nonprime_tot += 1;
            }
        }
        if (prime_tot as f64) / ((prime_tot + nonprime_tot) as f64) < 0.1 {
            println!("{}", side_len);
            break;
        }
    }
}
