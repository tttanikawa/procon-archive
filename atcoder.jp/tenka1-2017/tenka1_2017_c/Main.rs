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

fn check_gt(n: i64, h: i64, m: i64, w: i64) -> bool {
    4 * h * m * w - n * m * w - n * h * w - n * h * m > 0
}

fn check_eq(n: i64, h: i64, m: i64, w: i64) -> bool {
    4 * h * m * w - n * m * w - n * h * w - n * h * m == 0
}

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: i64 = sc.read();

    // 4 * h * m * w = n * m * w + n * h * w + n * h * m
    for h in 1..=3500 {
        for m in 1..=3500 {
            if 4 * h * m - n * m - n * h > 0 {
                let mut l = 1;
                let mut r = 3501;
                while l + 1 < r {
                    let w = (l + r) / 2;
                    if check_gt(n, h, m, w) {
                        r = w;
                    } else {
                        l = w;
                    }
                }
                if check_eq(n, h, m, l) {
                    println!("{} {} {}", h, m, l);
                    return;
                }
                if check_eq(n, h, m, r) {
                    println!("{} {} {}", h, m, r);
                    return;
                }
            } else {
                let mut l = 1;
                let mut r = 3501;
                while l + 1 < r {
                    let w = (l + r) / 2;
                    if check_gt(n, h, m, w) {
                        l = w;
                    } else {
                        r = w;
                    }
                }
                if check_eq(n, h, m, l) {
                    println!("{} {} {}", h, m, l);
                    return;
                }
                if check_eq(n, h, m, r) {
                    println!("{} {} {}", h, m, r);
                    return;
                }
            }
        }
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
