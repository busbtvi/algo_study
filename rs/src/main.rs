use std::io::{self, Read};
// use scanf::scanf;

fn main() {
    let mut buffer = String::new();
    // // match io::stdin().read_line(&mut buffer)
    // // {
    // //     Ok(n) => {
    // //         println!("{} bytes read", n);
    // //         println!("{}", buffer);
    // //     }
    // //     Err(error) => println!("error: {}", error),
    // // }

    // let stdin = io::stdin()
    //     .read_line(&mut buffer)
    //     .expect("error");
    // println!("hello, {}", buffer);

    // println!("Price of {} is {:.2}", integer, float);

    let mut n = 0;
    // let mut m = 0;

    // let mut nums: [i32; 2001] = [0; 2001];
    io::stdin()
        .read_line(&mut buffer)
        .expect("read n fail");
    n = buffer.trim().parse().expect("parsing fail");

    let mut nums = vec![0; n];
    io::stdin()
        .read_line(&mut buffer)
        .expect("read numbers failed");
    let nums = buffer.trim()
        .split_whitespace()
        .map(|x| x.parse().expect("parse error"));
    
    for i in 1..n+1 {
        // io::stdin().
    }
}