#[allow(unused_imports)]
use std::cmp;
use std::f64;

fn run1() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let a: f64 = sc.read();
    let b: f64 = sc.read();
    let h: f64 = sc.read();
    let m: f64 = sc.read();

    let rad_h = 360.0 * (h + m / 60.0) / 12.0 * f64::consts::PI / 180.0;
    let rad_m = 360.0 * m / 60.0 * f64::consts::PI / 180.0;

    let ax = a * rad_h.cos();
    let ay = a * rad_h.sin();
    let bx = b * rad_m.cos();
    let by = b * rad_m.sin();

    let dx = ax - bx;
    let dy = ay - by;
    let ans = (dx * dx + dy * dy).sqrt();
    println!("{}", ans);
}

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let a: f64 = sc.read();
    let b: f64 = sc.read();
    let h: f64 = sc.read();
    let m: f64 = sc.read();

    let rad_h = 360.0 * (h + m / 60.0) / 12.0 * f64::consts::PI / 180.0;
    let rad_m = 360.0 * m / 60.0 * f64::consts::PI / 180.0;

    let ans = (a * a + b * b - 2.0 * a * b * (rad_h - rad_m).cos()).sqrt();
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

#[test]
fn binary_search_test() {
    let v = [1, 2, 3, 4, 5];
    assert_eq!(3, binary_search(v.len() as _, -1, |i| v[i as usize] > 3));
    assert_eq!(5, binary_search(v.len() as _, -1, |i| v[i as usize] > 100));
    assert_eq!(0, binary_search(v.len() as _, -1, |i| v[i as usize] > 0));
}

/// Returns index to the first element in `v` which does not compare less than `val`.
pub fn lower_bound<T: PartialOrd>(v: &[T], val: &T) -> usize {
    (binary_search(-1, v.len() as i64, |i: i64| v[i as usize] < *val) + 1) as usize
}

#[test]
fn lower_bound_test() {
    let v = vec![1, 3, 3, 4, 5];
    assert_eq!(lower_bound(&v, &0), 0);
    assert_eq!(lower_bound(&v, &1), 0);
    assert_eq!(lower_bound(&v, &2), 1);
    assert_eq!(lower_bound(&v, &3), 1);
    assert_eq!(lower_bound(&v, &4), 3);
    assert_eq!(lower_bound(&v, &5), 4);
    assert_eq!(lower_bound(&v, &999), 5);
}

/// Returns index to the first element in `v` which compares greater than `val`.
pub fn upper_bound<T: PartialOrd>(v: &[T], val: &T) -> usize {
    (binary_search(-1, v.len() as i64, |i: i64| v[i as usize] <= *val) + 1) as usize
}

#[test]
fn upper_bound_test() {
    let v: &[i32] = &[1, 3, 3, 4, 5];
    assert_eq!(upper_bound(v, &0), 0);
    assert_eq!(upper_bound(v, &1), 1);
    assert_eq!(upper_bound(v, &2), 1);
    assert_eq!(upper_bound(v, &3), 3);
    assert_eq!(upper_bound(v, &4), 4);
    assert_eq!(upper_bound(v, &5), 5);
    assert_eq!(upper_bound(v, &999), 5);
}

/// Returns `(lower_bound(v, val), upper_bound(v, val))`
pub fn equal_range<T: PartialOrd>(v: &[T], val: &T) -> (usize, usize) {
    (lower_bound(v, val), upper_bound(v, val))
}

pub fn gcd(a: usize, b: usize) -> usize {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}
