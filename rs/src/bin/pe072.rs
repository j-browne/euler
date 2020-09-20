use num_integer::gcd;
use rayon::prelude::*;
use pbr::ProgressBar;
use std::sync::Mutex;

const MAX_DENOM: u64 = 1_000_000;
//const MAX_DENOM: usize = 8;

fn main() {
    //let pb = Mutex::new(ProgressBar::on(stderr(), (MAX_DENOM + 1) * (MAX_DENOM / 2)));
    let pb = Mutex::new(ProgressBar::new((MAX_DENOM + 1) * (MAX_DENOM / 2)));
    let res: u64 = (1..=MAX_DENOM)
        .into_par_iter()
//        .inspect(|x| {
//            if x % 10000 == 0 {
//                println!("{}", x);
//            }
//        })
        .map(|d| {
            pb.lock().unwrap().add(d);
            (1..d)
                .map(|n| if gcd(n, d) == 1 { 1 } else { 0 })
                .sum::<u64>()
        })
        .sum();

    pb.into_inner().unwrap().finish();
    println!("{}", res);
}
