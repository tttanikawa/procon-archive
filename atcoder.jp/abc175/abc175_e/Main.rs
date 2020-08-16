#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use std::cmp;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let r: usize = sc.read();
    let c: usize = sc.read();
    let k: usize = sc.read();
    let rcv = sc.read_matrix::<usize>(k, 3);
    const MAX_ITEMS: usize = 3;

    let mut items = vec![vec![0; c]; r];
    for rcv in rcv.into_iter() {
        items[rcv[0] - 1][rcv[1] - 1] = rcv[2];
    }

    let mut dp = vec![vec![vec![0usize; MAX_ITEMS + 1]; c]; r];
    if items[0][0] > 0 {
        dp[0][0][1] = items[0][0];
        dp[0][0][2] = items[0][0];
        dp[0][0][3] = items[0][0];
    }
    for i in 0..r {
        for j in 0..c {
            if i == 0 && j == 0 {
                continue;
            }
            for k in 0..=MAX_ITEMS {
                if items[i][j] > 0 {
                    if i > 0 {
                        dp[i][j][k] = cmp::max(dp[i][j][k], dp[i - 1][j][MAX_ITEMS]);
                        if k > 0 {
                            dp[i][j][k] =
                                cmp::max(dp[i][j][k], dp[i - 1][j][MAX_ITEMS] + items[i][j]);
                        }
                    }
                    if j > 0 {
                        dp[i][j][k] = cmp::max(dp[i][j][k], dp[i][j - 1][k]);
                        if k > 0 {
                            dp[i][j][k] = cmp::max(dp[i][j][k], dp[i][j - 1][k - 1] + items[i][j]);
                        }
                    }
                } else {
                    if i > 0 {
                        dp[i][j][k] = cmp::max(dp[i][j][k], dp[i - 1][j][MAX_ITEMS]);
                    }
                    if j > 0 {
                        dp[i][j][k] = cmp::max(dp[i][j][k], dp[i][j - 1][k]);
                    }
                }
            }
        }
    }
    let ans = dp[r - 1][c - 1][MAX_ITEMS];
    println!("{}", ans);
}

fn main() {
    std::thread::Builder::new()
        .name("run".into())
        .stack_size(256 * 1024 * 1024)
        .spawn(run)
        .unwrap()
        .join()
        .unwrap();
}

pub struct IO<R, W: std::io::Write>(R, std::io::BufWriter<W>);

impl<R: std::io::Read, W: std::io::Write> IO<R, W> {
    pub fn new(r: R, w: W) -> IO<R, W> {
        IO(r, std::io::BufWriter::new(w))
    }
    pub fn write<S: std::ops::Deref<Target = str>>(&mut self, s: S) {
        use std::io::Write;
        self.1.write(s.as_bytes()).unwrap();
    }
    pub fn read<T: std::str::FromStr>(&mut self) -> T {
        use std::io::Read;
        let buf = self
            .0
            .by_ref()
            .bytes()
            .map(|b| b.unwrap())
            .skip_while(|&b| b == b' ' || b == b'\n' || b == b'\r' || b == b'\t')
            .take_while(|&b| b != b' ' && b != b'\n' && b != b'\r' && b != b'\t')
            .collect::<Vec<_>>();
        unsafe { std::str::from_utf8_unchecked(&buf) }
            .parse()
            .ok()
            .expect("Parse error.")
    }
    pub fn read_vec<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.read()).collect()
    }
    pub fn read_pairs<T: std::str::FromStr>(&mut self, n: usize) -> Vec<(T, T)> {
        (0..n).map(|_| (self.read(), self.read())).collect()
    }
    pub fn read_pairs_1_indexed(&mut self, n: usize) -> Vec<(usize, usize)> {
        (0..n)
            .map(|_| (self.read::<usize>() - 1, self.read::<usize>() - 1))
            .collect()
    }
    pub fn read_chars(&mut self) -> Vec<char> {
        self.read::<String>().chars().collect()
    }
    pub fn read_char_grid(&mut self, n: usize) -> Vec<Vec<char>> {
        (0..n).map(|_| self.read_chars()).collect()
    }
    pub fn read_matrix<T: std::str::FromStr>(&mut self, n: usize, m: usize) -> Vec<Vec<T>> {
        (0..n)
            .map(|_| (0..m).map(|_| self.read()).collect())
            .collect()
    }
}
