use lazy_static::lazy_static;
use std::{cell::RefCell, collections::HashSet, sync::Mutex};

lazy_static! {
    static ref SIEVE: Mutex<Sieve> = Mutex::new(Sieve::new());
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum PrimeStatus {
    Prime,
    NonPrime,
    Unknown,
}

#[derive(Debug)]
struct Sieve {
    status: RefCell<Vec<PrimeStatus>>,
    primes: HashSet<usize>,
}

impl Sieve {
    fn new() -> Self {
        use PrimeStatus::*;
        let status = RefCell::new(vec![NonPrime, NonPrime]);
        Self {
            status,
            primes: HashSet::new(),
        }
    }

    fn populate_to(&mut self, max: usize) {
        use PrimeStatus::*;

        let len = self.status.borrow().len();

        if max >= len {
            // This is a way of batching the sieve, piggybacking on the way Vec
            // batches allocations
            self.status
                .borrow_mut()
                .resize(max + 1, PrimeStatus::Unknown);
            let cap = self.status.borrow().capacity();
            println!("new cap: {}", cap);
            self.status.borrow_mut().resize(cap, PrimeStatus::Unknown);

            // mark multiples of already known primes
            for p in self.primes() {
                self.mark_nonprime(len, p.clone());
            }

            // look for new primes
            loop {
                let mut prime = None;
                if let Some((prime_num, _)) = self
                    .status
                    .borrow()
                    .iter()
                    .enumerate()
                    .skip(len)
                    .filter(|(_, x)| **x == Unknown)
                    .next()
                {
                    prime = Some(prime_num);
                }

                if let Some(prime) = prime {
                    self.status.borrow_mut()[prime] = Prime;
                    self.mark_nonprime(len, prime);
                    self.primes.insert(prime);
                } else {
                    break;
                }
            }
        }
    }

    fn mark_nonprime(&self, first: usize, prime: usize) {
        use PrimeStatus::*;

        let mut s = self.status.borrow_mut();
        let start = (first / prime + 1) * prime;

        for i in (start..s.len()).step_by(prime) {
            s[i] = NonPrime;
        }
    }

    fn primes(&self) -> &HashSet<usize> {
        &self.primes
    }
}

pub fn is_prime(val: usize) -> bool {
    let mut sieve = SIEVE.lock().expect("unable to lock SIEVE");
    sieve.populate_to(val);
    sieve.primes().contains(&val)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sieve() {
        use PrimeStatus::*;

        let status = vec![
            NonPrime, NonPrime, Prime, Prime, NonPrime, Prime, NonPrime, Prime,
        ];

        let mut primes = HashSet::new();
        primes.insert(2);
        primes.insert(3);
        primes.insert(5);
        primes.insert(7);

        let mut sieve = Sieve {
            status: RefCell::new(status),
            primes,
        };

        sieve.populate_to(25);
    }

    #[test]
    fn test_is_prime() {
        assert!(is_prime(29));
        assert!(!is_prime(33));
        assert!(is_prime(7));
        assert!(!is_prime(9));
        assert!(!is_prime(52));
        assert!(is_prime(53));
        assert!(is_prime(1009));
    }
}
