use std::collections::HashMap;

fn main() {
    let mut max_factors = HashMap::<u32, u32>::new();

    for i in 2..=20 {
        for (factor, count) in get_factors(i) {
            let max_count = max_factors.entry(factor).or_insert(count);
            if count > *max_count {
                *max_count = count;
            }
        }
    }

    let mut res = 1;
    for (factor, count) in max_factors {
        let a = u32::checked_pow(factor, count).unwrap();
        res = u32::checked_mul(res, a).unwrap();
    }
    println!("{}", res);
}

fn get_factors(i: u32) -> HashMap<u32, u32> {
    let mut factors = HashMap::new();
    let mut curr = i;

    for j in 2..=(i / 2) {
        if curr == 1 {
            break;
        }

        while curr % j == 0 {
            *factors.entry(j).or_insert(0) += 1;
            curr /= j;
        }
    }

    if curr != 1 {
        *factors.entry(curr).or_insert(0) += 1;
    }

    factors
}
