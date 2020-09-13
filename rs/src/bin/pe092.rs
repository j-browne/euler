use std::collections::HashMap;

fn next(mut curr: u32) -> u32 {
    let mut sum = 0;
    while curr != 0 {
        sum += u32::pow(curr % 10, 2);
        curr /= 10;
    }
    sum
}

fn main() {
    let mut map = HashMap::<u32, u8>::new();
    map.insert(1, 1);
    map.insert(10, 1);
    map.insert(13, 1);
    map.insert(32, 1);
    map.insert(44, 1);
    map.insert(89, 89);
    map.insert(58, 89);
    map.insert(37, 89);
    map.insert(16, 89);
    map.insert(4, 89);
    map.insert(20, 89);
    map.insert(42, 89);
    map.insert(145, 89);
    map.insert(85, 89);

    let mut to_add = Vec::<u32>::new();
    for i in 1..10_000_000 {
        let mut curr = i;
        while !map.contains_key(&curr) {
            to_add.push(curr);
            curr = next(curr);
        }
        if let Some(val) = map.get(&curr) {
            let val = val.clone();
            for key in &to_add {
                map.insert(*key, val);
            }
        } else {
            unreachable!();
        }
        to_add.clear();
    }

    println!("{}", map.iter().filter(|(_, x)| **x == 89).count());
}
