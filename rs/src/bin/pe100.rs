fn main() {
    let sqrt2: f64 = f64::sqrt(2.0);
    let mut num_blue = (1_000_000_000_000.0 / sqrt2).ceil() as u128;
    let res = loop {
        let num_total = ((num_blue as f64) * sqrt2).floor() as u128;

        if num_blue * (num_blue - 1) * 2 == num_total * (num_total - 1)
            || num_blue * (num_blue - 1) * 2 == num_total * (num_total + 1)
            || num_blue * (num_blue - 1) * 2 == (num_total + 2) * (num_total + 1)
        {
            println!("{}", num_blue);
            break num_blue;
        }
        num_blue += 1;

        //        if num_total % 1_000_000 == 0 {
        //            println!("{} {} {}",
        //                num_total,
        //                2 * (num_blue * (num_blue - 1)) as i128 - (num_total * (num_total - 1)) as i128,
        //                2 * (num_blue * (num_blue - 1)) as i128 - ((num_total + 1) * (num_total + 2)) as i128,
        //            );
        //        }
    };

    println!("{}", res);
}
