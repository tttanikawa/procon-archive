#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
use mod_int::ModInt;
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
    let k: usize = sc.read();
    let mut a = sc.read_vec::<i64>(n);

    let mut x = vec![];
    let mut y = vec![];
    let mut z = 0;
    for a in a {
        if a == 0 {
            z += 1;
        } else if a > 0 {
            x.push(a);
        } else {
            y.push(a);
        }
    }
    if k > n - z {
        println!("0");
        return;
    }
    const MOD: i64 = 1_000_000_007;
    if k == n - z {
        if y.len() % 2 == 1 && z > 0 {
            println!("0");
            return;
        }
        let mut ans = 1;
        for x in x.iter().chain(y.iter()) {
            ans = ans * (*x + MOD) % MOD;
        }
        println!("{}", ans);
        return;
    }
    x.sort();
    y.sort();
    if k % 2 == 1 && x.is_empty() {
        if z > 0 {
            println!("0");
            return;
        }
        let mut ans = 1;
        for y in y.iter().rev().take(k) {
            ans = ans * (*y + MOD) % MOD;
        }
        println!("{}", ans);
        return;
    }
    // +
    let (mul, k) = if k % 2 == 1 {
        (x.pop().unwrap(), (k - 1) / 2)
    } else {
        (1, k / 2)
    };
    x.reverse();
    let mut x = x.chunks_exact(2).map(|x| x[1] * x[0]).collect::<Vec<_>>();
    let mut y = y.chunks_exact(2).map(|y| y[1] * y[0]).collect::<Vec<_>>();
    while x.len() < k {
        x.push(0);
    }
    while y.len() < k {
        y.push(0);
    }
    let mut i = 0;
    let mut j = 0;
    let mut ans = mul;
    while i + j < k {
        if x[i] > y[j] {
            ans = ans * (x[i] % MOD) % MOD;
            i += 1;
        } else {
            ans = ans * (y[j] % MOD) % MOD;
            j += 1;
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

pub mod mod_int {
    use std::ops::{
        Add, AddAssign, BitAnd, Div, DivAssign, Mul, MulAssign, RemAssign, ShrAssign, Sub,
        SubAssign,
    };

    pub struct ModInt<T> {
        v: T,
        m: T,
    }

    impl<T> ModInt<T>
    where
        T: Copy,
    {
        pub fn value(&self) -> T {
            self.v
        }
        pub fn modulo(&self) -> T {
            self.m
        }
    }

    impl<T> ModInt<T> {
        fn new_unchecked(v: T, modulo: T) -> Self {
            Self { v, m: modulo }
        }
    }

    impl<T> ModInt<T>
    where
        T: Copy + RemAssign + PartialOrd,
    {
        pub fn new(mut v: T, modulo: T) -> Self {
            if v >= modulo {
                v %= modulo;
            }
            Self::new_unchecked(v, modulo)
        }
    }

    impl<T> ModInt<T>
    where
        T: Copy
            + Sub<Output = T>
            + ShrAssign
            + BitAnd<Output = T>
            + PartialEq
            + PartialOrd
            + Div<Output = T>
            + RemAssign,
        ModInt<T>: MulAssign,
    {
        pub fn pow(self, e: T) -> Self {
            let zero = self.modulo() - self.modulo();
            let one = self.modulo() / self.modulo();
            let mut e = e;
            let mut result = Self::new_unchecked(one, self.modulo());
            let mut cur = self;
            while e > zero {
                if e & one == one {
                    result *= cur;
                }
                e >>= one;
                cur *= cur;
            }
            result
        }
    }

    impl<T> Copy for ModInt<T> where T: Copy {}
    impl<T> Clone for ModInt<T>
    where
        T: Copy,
    {
        fn clone(&self) -> Self {
            Self::new_unchecked(self.value(), self.modulo())
        }
    }

    impl<T> Add<T> for ModInt<T>
    where
        T: AddAssign + SubAssign + RemAssign + Copy + PartialOrd,
    {
        type Output = Self;
        fn add(self, mut rhs: T) -> Self::Output {
            if rhs >= self.modulo() {
                rhs %= self.modulo();
            }
            rhs += self.value();
            if rhs >= self.modulo() {
                rhs -= self.modulo();
            }
            Self::new_unchecked(rhs, self.modulo())
        }
    }

    impl<T> Sub<T> for ModInt<T>
    where
        T: AddAssign + SubAssign + RemAssign + Copy + PartialOrd,
    {
        type Output = Self;
        fn sub(self, mut rhs: T) -> Self::Output {
            if rhs >= self.modulo() {
                rhs %= self.modulo();
            }

            let mut result = self.value();
            result += self.modulo();
            result -= rhs;

            if result >= self.modulo() {
                result -= self.modulo();
            }
            Self::new_unchecked(result, self.modulo())
        }
    }

    impl<T> Mul<T> for ModInt<T>
    where
        T: MulAssign + RemAssign + Copy + PartialOrd,
    {
        type Output = Self;
        fn mul(self, mut rhs: T) -> Self::Output {
            if rhs >= self.modulo() {
                rhs %= self.modulo();
            }
            rhs *= self.value();
            rhs %= self.modulo();
            Self::new_unchecked(rhs, self.modulo())
        }
    }

    impl<T> Add<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Add<T, Output = ModInt<T>>,
    {
        type Output = Self;
        fn add(self, rhs: ModInt<T>) -> Self::Output {
            self + rhs.value()
        }
    }
    impl<T> Sub<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Sub<T, Output = ModInt<T>>,
    {
        type Output = Self;
        fn sub(self, rhs: ModInt<T>) -> Self::Output {
            self - rhs.value()
        }
    }
    impl<T> Mul<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Mul<T, Output = ModInt<T>>,
    {
        type Output = Self;
        fn mul(self, rhs: ModInt<T>) -> Self::Output {
            self * rhs.value()
        }
    }
    impl<T> Div<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Div<T, Output = ModInt<T>>,
    {
        type Output = Self;
        fn div(self, rhs: ModInt<T>) -> Self::Output {
            self / rhs.value()
        }
    }

    impl<T> AddAssign<T> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Add<T, Output = ModInt<T>>,
    {
        fn add_assign(&mut self, other: T) {
            *self = *self + other;
        }
    }
    impl<T> AddAssign<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Add<ModInt<T>, Output = ModInt<T>>,
    {
        fn add_assign(&mut self, other: ModInt<T>) {
            *self = *self + other;
        }
    }

    impl<T> SubAssign<T> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Sub<T, Output = ModInt<T>>,
    {
        fn sub_assign(&mut self, other: T) {
            *self = *self - other;
        }
    }

    impl<T> SubAssign<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Sub<ModInt<T>, Output = ModInt<T>>,
    {
        fn sub_assign(&mut self, other: ModInt<T>) {
            *self = *self - other;
        }
    }

    impl<T> DivAssign<T> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Div<T, Output = ModInt<T>>,
    {
        fn div_assign(&mut self, rhs: T) {
            *self = *self / rhs
        }
    }
    impl<T> DivAssign<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Div<ModInt<T>, Output = ModInt<T>>,
    {
        fn div_assign(&mut self, rhs: ModInt<T>) {
            *self = *self / rhs
        }
    }

    impl<T> MulAssign<T> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Mul<T, Output = ModInt<T>>,
    {
        fn mul_assign(&mut self, rhs: T) {
            *self = *self * rhs;
        }
    }

    impl<T> MulAssign<ModInt<T>> for ModInt<T>
    where
        T: Copy,
        ModInt<T>: Mul<ModInt<T>, Output = ModInt<T>>,
    {
        fn mul_assign(&mut self, rhs: ModInt<T>) {
            *self = *self * rhs;
        }
    }

    impl<T> Div<T> for ModInt<T>
    where
        T: Copy
            + Add<Output = T>
            + Sub<Output = T>
            + Div<Output = T>
            + BitAnd<Output = T>
            + PartialEq
            + PartialOrd
            + ShrAssign
            + RemAssign
            + MulAssign,
    {
        type Output = Self;
        fn div(self, mut rhs: T) -> Self::Output {
            if rhs >= self.modulo() {
                rhs %= self.modulo();
            }
            let one = self.modulo() / self.modulo();
            let two = one + one;
            self * Self::new_unchecked(rhs, self.modulo()).pow(self.modulo() - two)
        }
    }
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
