fn main() {
    let max: u32 = 100;
    let square_of_sums = (0..=max)
        .try_fold(0u32, |acc, x| acc.checked_add(x))
        .unwrap()
        .checked_pow(2)
        .unwrap();
    let sum_of_squares = (0..=max)
        .map(|x| x.checked_pow(2).unwrap())
        .try_fold(0u32, |acc, x| acc.checked_add(x))
        .unwrap();
    let res = square_of_sums - sum_of_squares;

    println!("{}", res);
}
