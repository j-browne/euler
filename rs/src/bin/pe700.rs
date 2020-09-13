// Eulercoins are generated with A * n % B
const A: u64 = 1504170715041707;
const B: u64 = 4503599627370517;

fn main() {
    let mut curr = A;
    let mut min = A;
    let mut sum = A;

    while A != 0 {
        let next = (curr + A) % B;
        if curr == next {
            break;
        }
        curr = next;
        if curr < min {
            min = curr;
            sum += curr;
            println!("{}\t{}", curr, sum);
        }
    }

    println!("{}", sum);
}
