use euler::playing_cards::poker::Hand;
use std::str::FromStr;

fn main() {
    let input = include_str!("input/pe054/p054_poker.txt");

    let p1_wins = input
        .lines()
        .filter(|line| {
            Hand::from_str(&line[0..14]).unwrap() > Hand::from_str(&line[15..29]).unwrap()
        })
        .count();

    println!("{}", p1_wins);
}
