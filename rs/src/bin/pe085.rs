const GOAL: i64 = 2_000_000;

fn main() {
    let tri = (1..)
        .scan(0, |state, x| {
            *state = *state + x;

            if *state > GOAL {
                None
            } else {
                Some(*state)
            }
        })
        .collect::<Vec<i64>>();

    let mut closest: Option<(usize, usize, i64)> = None;
    for (i, tri_i) in tri.iter().enumerate() {
        for (j, tri_j) in tri.iter().enumerate() {
            if let Some((_, _, x)) = closest {
                if (tri_i * tri_j - GOAL).abs() < (x - GOAL).abs() {
                    closest = Some((i + 1, j + 1, tri_i * tri_j));
                }
            } else {
                closest = Some((i + 1, j + 1, tri_i * tri_j));
            }
        }
    }

    if let Some((i, j, _)) = closest {
        println!("{}", i * j);
    }
}
