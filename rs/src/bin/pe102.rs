pub fn contains(verts: &[(f64, f64)], (x, y): (f64, f64)) -> bool {
    let mut inside = false;

    let mut j = verts.len() - 1;

    for i in 0..verts.len() {
        let x1 = verts[j].0;
        let x2 = verts[i].0;
        let y1 = verts[j].1;
        let y2 = verts[i].1;

        if (((y2 < y) && (y1 >= y)) || ((y1 < y) && (y2 >= y)))
            && ((x2 + (y - y2) * (x1 - x2) / (y1 - y2)) < x)
        {
            inside = !inside;
        }

        j = i;
    }

    inside
}

fn main() {
    let input = include_str!("input/pe102/p102_triangles.txt");

    let res = input
        .lines()
        .filter(|line| {
            let nums = line
                .split(',')
                .map(|x| x.parse::<f64>().unwrap())
                .collect::<Vec<_>>();
            let pairs = [(nums[0], nums[1]), (nums[2], nums[3]), (nums[4], nums[5])];
            contains(&pairs, (0.0, 0.0))
        })
        .count();

    println!("{}", res);
}
