#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use std::cmp;
use std::collections::BTreeMap;
use std::collections::BTreeSet;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let h: usize = sc.read();
    let w: usize = sc.read();
    let m: usize = sc.read();

    let mut targets_h = BTreeMap::new();
    let mut targets_w = BTreeMap::new();
    let mut targets_hw = BTreeSet::new();
    for _ in 0..m {
        let i = sc.read::<usize>() - 1;
        let j = sc.read::<usize>() - 1;
        targets_h.entry(i).and_modify(|x| *x += 1).or_insert(1usize);
        targets_w.entry(j).and_modify(|x| *x += 1).or_insert(1usize);
        targets_hw.insert((i, j));
    }

    let mut cands_h = vec![];
    let mut cands_w = vec![];
    let max_h = *targets_h.iter().map(|(k, v)| v).max().unwrap();
    let max_w = *targets_w.iter().map(|(k, v)| v).max().unwrap();
    for (&k, &v) in targets_h.iter() {
        if v == max_h {
            cands_h.push(k);
        }
    }
    for (&k, &v) in targets_w.iter() {
        if v == max_w {
            cands_w.push(k);
        }
    }

    let mut ans = 0;
    'outer: for &ch in cands_h.iter() {
        for &cw in cands_w.iter() {
            if targets_hw.contains(&(ch, cw)) && max_h + max_w > 1 {
                ans = max_h + max_w - 1;
            } else {
                ans = max_h + max_w;
                break 'outer;
            }
        }
    }
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
