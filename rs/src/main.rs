use std::fmt::Write;
use std::io::{stdin, Read};

fn main() {
    let mut dp = [[false; 2001]; 2001];
    let mut nums: [usize; 2001] = [0; 2001];
    let mut output = String::new();
    let mut input = String::new();
    
    stdin().read_to_string(&mut input).unwrap();
    let mut input_nums = input.split_ascii_whitespace().flat_map(str::parse::<usize>);

    let n: usize = input_nums.next().unwrap();
    for i in 0..n {
        nums[i] = input_nums.next().unwrap();
    }
    
    for i in 0..n {
        for j in 0..i+1 {
            dp[i][j] = 
                if i == j { true }
                else if i-1 == j { nums[i] == nums[j] }
                else { dp[i-1][j+1] && nums[i]==nums[j] }
        }
    }

    let m = input_nums.next().unwrap();
    for _ in 0..m {
        let s = input_nums.next().unwrap();
        let e: usize = input_nums.next().unwrap();
        let result = if dp[e-1][s-1] {"1"} else {"0"};
        writeln!(output, "{}", result).unwrap();
    }
    print!("{}", output);
}