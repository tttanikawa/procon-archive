#[allow(unused_macros)]
macro_rules! debug {
	($($a:expr),*) => {
		println!(concat!($(stringify!($a), " = {:?}, "),*), $($a),*);
	}
}

#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(dead_code)]
const MOD: usize = 1e9 as usize + 7;

fn main() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let a = sc.read_vec::<i64>(n);

    if a[0] != 0 {
        println!("-1");
        return;
    }

    let mut ans = 0_i64;
    for i in 1..n {
        if a[i] - a[i - 1] > 1 {
            println!("-1");
            return;
        }

        if a[i] == a[i - 1] + 1 {
            ans += 1;
        } else {
            ans += a[i];
        }
    }
    println!("{}", ans);
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

#[allow(dead_code)]
fn yn(flag: bool) {
    if flag {
        println!("Yes");
    } else {
        println!("No");
    }
}
