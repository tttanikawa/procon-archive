#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use proconio::{fastout, input, marker::Bytes, marker::Chars, marker::Isize1, marker::Usize1};
#[allow(unused_imports)]
use std::cmp;
use std::collections::BTreeMap;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let h: usize = sc.read();
    let w: usize = sc.read();
    let a = sc.read_char_grid(h);

    let mut counts = vec![0; 26];
    for row in a.iter() {
        for &c in row.iter() {
            counts[c as usize - 'a' as usize] += 1;
        }
    }

    let h = h as i64;
    let w = w as i64;
    let mut req = vec![0; 5];
    if h % 2 == 1 {
        req[2] += w / 2;
    }
    if w % 2 == 1 {
        req[2] += h / 2;
    }
    if h % 2 == 1 && w % 2 == 1 {
        req[1] = 1;
    }
    req[4] = (h * w - req[2] * 2 - req[1]) / 4;

    for c in counts.iter_mut() {
        if *c % 2 == 1 {
            req[1] -= 1;
            *c -= 1;
        }
        if *c % 4 == 2 {
            req[2] -= 1;
            *c -= 2;
        }
        if *c % 4 == 0 {
            if *c / 4 >= req[4] {
                *c -= req[4] * 4;
                req[4] = 0;
            } else {
                req[4] -= *c / 4;
                *c = 0;
            }
        }
        if *c > 0 && *c % 2 == 0 {
            req[2] -= *c / 2;
            *c = 0;
        }
    }

    let ans = if req[1] == 0 && req[2] == 0 && req[4] == 0 {
        "Yes"
    } else {
        "No"
    };
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
