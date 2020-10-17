#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use proconio::{fastout, input, marker::Bytes, marker::Chars, marker::Isize1, marker::Usize1};
#[allow(unused_imports)]
use std::cmp;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

#[fastout]
fn main() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let xyz = sc.read_matrix::<i64>(n, 3);

    let mut graph = vec![vec![0; n]; n];
    for i in 0..n {
        for j in 0..n {
            graph[i][j] = (xyz[j][0] - xyz[i][0]).abs()
                + (xyz[j][1] - xyz[i][1]).abs()
                + cmp::max(xyz[j][2] - xyz[i][2], 0);
        }
    }
    let mut dp = vec![vec![std::i64::MAX; n]; 1 << n + 1];
    dp[0][0] = 0;
    dp[1][0] = 0;
    for bit in 0..(1 << n) {
        for dst in 0..n {
            for src in 0..n {
                if bit & (1 << dst) == 0 {
                    if src != dst {
                        dp[bit | (1 << dst)][dst] = cmp::min(
                            dp[bit | (1 << dst)][dst],
                            dp[bit][src].saturating_add(graph[src][dst]),
                        );
                    }
                }
            }
        }
    }
    // dbg!(&dp);

    let idx = (0..n).map(|x| 1 << x).sum::<usize>();
    println!(
        "{}",
        dp[idx]
            .iter()
            .enumerate()
            .skip(1)
            .map(|(i, x)| x.saturating_add(graph[i][0]))
            .min()
            .unwrap()
    );
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
