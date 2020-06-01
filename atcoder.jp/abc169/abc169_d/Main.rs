#[allow(unused_imports)]
use std::cmp;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let fac = factor(n);
    let mut ans = 0;
    for (f, count) in fac.into_iter() {
        let mut x = count;
        for i in 1..=count {
            if x >= i {
                x -= i;
                ans += 1;
            } else {
                break;
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

/// Returns all primes less than `n`
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

#[test]
fn primes_test() {
    assert_eq!(primes(20), &[2, 3, 5, 7, 11, 13, 17, 19]);
}

/// Prime factorization
pub fn factor(n: usize) -> Vec<(usize, usize)> {
    let mut n = n;
    let mut ret = vec![];
    let ps = primes((n as f64).sqrt() as usize + 2);
    for p in ps {
        let mut cnt = 0;
        while n % p == 0 {
            n /= p;
            cnt += 1;
        }
        if cnt > 0 {
            ret.push((p, cnt));
        }
    }
    if n > 1 {
        ret.push((n, 1));
    }
    ret
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
