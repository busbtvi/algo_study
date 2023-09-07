use std::io;

fn main() {
    let mut dp = [[false; 2001]; 2001];
    let mut buffer = String::new();

    io::stdin()
        .read_line(&mut buffer)
        .expect("read n fail");
    let n = buffer.trim().parse().expect("parsing fail");
    
    buffer.clear();
    io::stdin()
        .read_line(&mut buffer)
        .expect("read numbers failed");
    let nums = buffer.trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>())
        .collect::<Result<Vec<i32>, _>>()
        .unwrap();
    
    for i in 0..n {
        for j in 0..i+1 {
            dp[i][j] = 
                if i == j { true }
                else if i-1 == j { nums[i] == nums[j] }
                else { dp[i-1][j+1] && nums[i]==nums[j] }
        }
    }

    // for i in 0..n {
    //     for j in 0..n {
    //         print!("{} ", dp[i][j]);
    //     }
    //     println!();
    // }

    buffer.clear();
    io::stdin()
        .read_line(&mut buffer)
        .expect("read n fail");
    let m:usize = buffer.trim().parse().expect("parsing fail");

    let mut i = 0;
    while i < m {
        buffer.clear();
        io::stdin()
            .read_line(&mut buffer)
            .expect("s,e read failed");
        let se = buffer.trim()
            .split_whitespace()
            .map(|x| x.parse::<usize>())
            .collect::<Result<Vec<usize>, _>>()
            .unwrap();

        println!("{}", if dp[se[1]-1][se[0]-1] {"1"} else {"0"} );
        i += 1;
    }

    // for i in 0..n {
    //     println!("{}", nums[i]);
    // }
}