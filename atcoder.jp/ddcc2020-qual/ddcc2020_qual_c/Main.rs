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

fn solve(
    cur: &mut usize,
    cl: usize,
    cr: usize,
    h: usize,
    w: usize,
    s: &Vec<Vec<char>>,
    g: &mut Vec<Vec<usize>>,
) {
    let mut p = vec![];
    for i in cl..=cr {
        for j in 0..w {
            if s[i][j] == '#' {
                p.push(j);
            }
        }
    }
    p.sort();
    for i in 0..p.len() {
        let mut v1 = 0;
        let mut v2 = w - 1;
        if i >= 1 {
            v1 = p[i - 1] + 1;
        }
        if i < p.len() - 1 {
            v2 = p[i];
        }

        *cur += 1;
        for j in cl..=cr {
            for k in v1..=v2 {
                g[j][k] = *cur;
            }
        }
    }
}

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let h: usize = sc.read();
    let w: usize = sc.read();
    let k: usize = sc.read();
    let s = sc.read_char_grid(h);

    let mut count = vec![0; h];
    for i in 0..h {
        for j in 0..w {
            if s[i][j] == '#' {
                count[i] += 1;
            }
        }
    }

    let mut v = vec![];
    for i in 0..h {
        if count[i] >= 1 {
            v.push(i);
        }
    }

    let mut cur = 0;
    let mut ans = vec![vec![0; w]; h];
    for i in 0..v.len() {
        let mut v1 = 0;
        let mut v2 = h - 1;
        if i >= 1 {
            v1 = v[i - 1] + 1;
        }
        if i < v.len() - 1 {
            v2 = v[i];
        }
        solve(&mut cur, v1, v2, h, w, &s, &mut ans);
    }

    for i in 0..h {
        for j in 0..w {
            print!("{}", ans[i][j]);
            if j == w - 1 {
                println!("");
            } else {
                print!(" ");
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
