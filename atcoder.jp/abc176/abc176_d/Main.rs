#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
#[allow(unused_imports)]
use std::cmp;
use std::collections::VecDeque;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let h: usize = sc.read();
    let w: usize = sc.read();
    let ch: usize = sc.read::<usize>() - 1;
    let cw: usize = sc.read::<usize>() - 1;
    let dh: usize = sc.read::<usize>() - 1;
    let dw: usize = sc.read::<usize>() - 1;
    let s = sc.read_char_grid(h);

    let mut queue = VecDeque::new();
    let mut dist = vec![vec![1usize << 50; w]; h];
    dist[ch][cw] = 0;
    queue.push_back((ch, cw, 0usize));
    while let Some((cur_h, cur_w, warp)) = queue.pop_front() {
        if cur_h > 0 {
            if s[cur_h - 1][cur_w] == '.' && dist[cur_h - 1][cur_w] > warp {
                dist[cur_h - 1][cur_w] = warp;
                queue.push_front((cur_h - 1, cur_w, warp));
            }
        }
        if cur_w > 0 {
            if s[cur_h][cur_w - 1] == '.' && dist[cur_h][cur_w - 1] > warp {
                dist[cur_h][cur_w - 1] = warp;
                queue.push_front((cur_h, cur_w - 1, warp));
            }
        }
        if cur_h < h - 1 {
            if s[cur_h + 1][cur_w] == '.' && dist[cur_h + 1][cur_w] > warp {
                dist[cur_h + 1][cur_w] = warp;
                queue.push_front((cur_h + 1, cur_w, warp));
            }
        }
        if cur_w < w - 1 {
            if s[cur_h][cur_w + 1] == '.' && dist[cur_h][cur_w + 1] > warp {
                dist[cur_h][cur_w + 1] = warp;
                queue.push_front((cur_h, cur_w + 1, warp));
            }
        }

        for i in cmp::max(cur_h as i64 - 2, 0) as usize..=cmp::min(cur_h + 2, h - 1) {
            for j in cmp::max(cur_w as i64 - 2, 0) as usize..=cmp::min(cur_w + 2, w - 1) {
                if s[i][j] == '.' && dist[i][j] > warp + 1 {
                    dist[i][j] = warp + 1;
                    queue.push_back((i, j, warp + 1));
                }
            }
        }
    }
    let ans = dist[dh][dw];
    if ans == 1 << 50 {
        println!("-1");
    } else {
        println!("{}", ans);
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
