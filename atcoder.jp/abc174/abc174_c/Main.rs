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

    let k: usize = sc.read();

    let mut cur = 7 % k;
    let mut checked = vec![false; k];
    for i in 1.. {
        if cur == 0 {
            println!("{}", i);
            return;
        } else if checked[cur] {
            println!("-1");
            return;
        } else {
            checked[cur] = true;
            cur = (cur * 10 + 7) % k;
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
