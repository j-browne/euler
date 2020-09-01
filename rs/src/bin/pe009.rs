const SUM: u32 = 1000;

fn main() {
    for c in 2..=SUM {
        let (a1, a2) = roots(c);
        let b1 = SUM - c - a1;
        let b2 = SUM - c - a2;

        if a1 * a1 + b1 * b1 == c * c {
            println!("{} {} {}", a1, b1, c);
        }
        if a2 * a2 + b2 * b2 == c * c {
            println!("{} {} {}", a2, b2, c);
        }
    }
}

fn roots(c: u32) -> (u32, u32) {
    let c = c as f64;
    let sum = SUM as f64;

    let x1 = (sum - c) / 2.0;
    let x2 = f64::sqrt(-sum * sum + c * c - 6.0 * sum * c) / 2.0;

    ((x1 + x2).round() as u32, (x1 - x2).round() as u32)
}
