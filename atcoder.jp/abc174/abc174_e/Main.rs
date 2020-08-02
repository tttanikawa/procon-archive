#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
use ordered_float::NotNan;
#[allow(unused_imports)]
use std::cmp;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

use std::ops::{Add, Div};

/// Generic binary search
///
/// # Arguments
///
/// * `l` - the value assumes to `pred(l) = true`
/// * `r` - the value assumes to `pred(r) = false`
/// * `pred` - predicate for binary search
///
/// # Returns
///
/// * `ret` where `pred(ret) = true` && `pred(ret + delta) = false`
///
/// # Note
///
/// `pred(l)` and `pred(r)` are not called. `pred` is called only values in the range `(l, r)`.
///
pub fn binary_search<T: Add<Output = T> + Div<Output = T> + PartialEq + From<u8> + Copy>(
    l: T,
    r: T,
    pred: impl Fn(T) -> bool,
) -> T {
    let mut l = l;
    let mut r = r;
    let two = T::from(2_u8);
    loop {
        let m = (l + r) / two;
        if l == m || r == m {
            break l;
        }
        if pred(m) {
            l = m;
        } else {
            r = m;
        }
    }
}

fn solve(a: &Vec<usize>, k: usize, x: f64) -> bool {
    let mut cut = 0;
    for &a in a.iter() {
        cut += (a as f64 / x - 1.0).ceil() as usize;
    }
    k >= cut
}

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let k: usize = sc.read();
    let a = sc.read_vec::<usize>(n);

    // let mut ng = 0.0;
    // let mut ok = 1e10;
    // for _ in 0..100 {
    //     let x = (ng + ok) / 2.0;
    //     if solve(&a, k, x) {
    //         ok = x;
    //     } else {
    //         ng = x;
    //     }
    // }
    // println!("{}", ((ok + ng) / 2.0).ceil() as usize);
    let ans = binary_search(1e10 as usize, 0, |m| {
        let t = a
            .iter()
            .map(|&x| if x % m == 0 { x / m - 1 } else { x / m })
            .sum::<usize>();
        t <= k
    });
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
