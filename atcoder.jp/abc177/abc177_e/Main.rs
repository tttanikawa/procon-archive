#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use std::cmp;
use std::collections::HashSet;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

fn gcd(a: usize, b: usize) -> usize {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}

fn lcm(a: usize, b: usize) -> usize {
    a / gcd(a, b) * b
}

pub fn sieve(n: usize) -> Vec<bool> {
    let mut tbl = vec![true; n];
    tbl[0] = false;
    tbl[1] = false;
    for i in 2..n {
        if tbl[i] {
            let mut j = i + i;
            while j < n {
                tbl[j] = false;
                j += i;
            }
        }
    }
    tbl
}

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let a = sc.read_vec::<usize>(n);

    let max = *a.iter().max().unwrap();
    let mut tbl = (0..=max).collect_vec();
    for prime in 2.. {
        if prime * prime > max {
            break;
        }
        if tbl[prime] == prime {
            for mul in (2 * prime..=max).step_by(prime) {
                if tbl[mul] == mul {
                    tbl[mul] = prime;
                }
            }
        }
    }

    let mut pairwise = true;
    let mut set = HashSet::new();
    'outer: for &a in a.iter() {
        let mut t = a;
        let mut factors = HashSet::new();
        while t > 1 {
            factors.insert(tbl[t]);
            t /= tbl[t];
        }

        for fac in factors.into_iter() {
            if !set.insert(fac) {
                pairwise = false;
                break 'outer;
            }
        }
    }

    let setwise = a.iter().fold(a[0], |acc, x| gcd(acc, *x)) == 1;
    if pairwise && setwise {
        println!("pairwise coprime");
    } else if setwise {
        println!("setwise coprime");
    } else {
        println!("not coprime");
    }
}

fn run2() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let a = sc.read_vec::<usize>(n);

    let max = *a.iter().max().unwrap();
    let mut tbl = vec![0; max + 1];
    for &a in &a {
        tbl[a] = 1;
    }

    let mut pairwise = true;
    let ps = primes(max + 1);
    for &p in &ps {
        let mut cur = p;
        let mut count = 0;
        while cur <= max {
            count += tbl[cur];
            cur += p;
        }
        if count >= 2 {
            pairwise = false;
        }
    }

    let setwise = a.iter().fold(a[0], |acc, x| gcd(acc, *x)) == 1;
    if pairwise && setwise {
        println!("pairwise coprime");
    } else if setwise {
        println!("setwise coprime");
    } else {
        println!("not coprime");
    }
}

pub fn primes(n: usize) -> Vec<usize> {
    let mut tbl = vec![true; n];
    let mut ps = vec![];
    tbl[0] = false;
    tbl[1] = false;
    for i in 2..n {
        if tbl[i] {
            ps.push(i);
            let mut j = i + i;
            while j < n {
                tbl[j] = false;
                j += i;
            }
        }
    }
    ps
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
