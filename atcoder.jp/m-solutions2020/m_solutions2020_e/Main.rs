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

    let n: usize = sc.read();
    let mut x = vec![];
    let mut y = vec![];
    let mut p = vec![];
    for _ in 0..n {
        x.push(sc.read::<i64>());
        y.push(sc.read::<i64>());
        p.push(sc.read::<i64>());
    }

    let mut xsel = vec![vec![0; n]; 1 << n];
    let mut ysel = vec![vec![0; n]; 1 << n];
    for i in 0..(1 << n) {
        for j in 0..n {
            xsel[i][j] = x[j].abs();
            ysel[i][j] = y[j].abs();
            for k in 0..n {
                if (i >> k) & 1 > 0 {
                    xsel[i][j] = cmp::min(xsel[i][j], (x[j] - x[k]).abs());
                    ysel[i][j] = cmp::min(ysel[i][j], (y[j] - y[k]).abs());
                }
            }
        }
    }

    let mut ans = vec![std::i64::MAX; n + 1];
    for i in 0..((1_usize) << n) {
        let count = i.count_ones() as usize;
        let mut j = i;
        loop {
            j = j & i;
            let mut cost = 0;
            for k in 0..n {
                if (i >> k) & 1 == 0 {
                    cost += cmp::min(xsel[j][k], ysel[i - j][k]) * p[k];
                }
            }
            ans[count] = cmp::min(ans[count], cost);
            if j > 0 {
                j -= 1;
            } else {
                break;
            }
        }
    }

    for i in 0..=n {
        println!("{}", ans[i]);
    }
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
