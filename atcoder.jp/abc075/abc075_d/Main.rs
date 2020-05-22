#[allow(unused_imports)]
use std::cmp;

fn run() {
    let (r, w) = (std::io::stdin(), std::io::stdout());
    let mut sc = IO::new(r.lock(), w.lock());

    let n: usize = sc.read();
    let K: usize = sc.read();
    let xy = sc.read_pairs::<i64>(n);

    let mut ans = i64::max_value();
    match K {
        2 => {
            for i in 0..n {
                for j in i + 1..n {
                    let x1 = cmp::min(xy[i].0, xy[j].0);
                    let x2 = cmp::max(xy[i].0, xy[j].0);
                    let y1 = cmp::min(xy[i].1, xy[j].1);
                    let y2 = cmp::max(xy[i].1, xy[j].1);

                    let mut count = 0;
                    for m in 0..n {
                        let mx = xy[m].0;
                        let my = xy[m].1;
                        if mx >= x1 && mx <= x2 && my >= y1 && my <= y2 {
                            count += 1;
                        }
                    }

                    if count >= K {
                        ans = cmp::min(ans, (x2 - x1) * (y2 - y1));
                    }
                }
            }
        }
        3 => {
            for i in 0..n {
                for j in i + 1..n {
                    for k in j + 1..n {
                        let x1 = cmp::min(cmp::min(xy[i].0, xy[j].0), xy[k].0);
                        let x2 = cmp::max(cmp::max(xy[i].0, xy[j].0), xy[k].0);
                        let y1 = cmp::min(cmp::min(xy[i].1, xy[j].1), xy[k].1);
                        let y2 = cmp::max(cmp::max(xy[i].1, xy[j].1), xy[k].1);

                        let mut count = 0;
                        for m in 0..n {
                            let mx = xy[m].0;
                            let my = xy[m].1;
                            if mx >= x1 && mx <= x2 && my >= y1 && my <= y2 {
                                count += 1;
                            }
                        }

                        if count >= K {
                            ans = cmp::min(ans, (x2 - x1) * (y2 - y1));
                        }
                    }
                }
            }
        }
        _ => {
            for i in 0..n {
                for j in i + 1..n {
                    for k in j + 1..n {
                        for l in k + 1..n {
                            let x1 =
                                cmp::min(cmp::min(xy[i].0, xy[j].0), cmp::min(xy[k].0, xy[l].0));
                            let x2 =
                                cmp::max(cmp::max(xy[i].0, xy[j].0), cmp::max(xy[k].0, xy[l].0));
                            let y1 =
                                cmp::min(cmp::min(xy[i].1, xy[j].1), cmp::min(xy[k].1, xy[l].1));
                            let y2 =
                                cmp::max(cmp::max(xy[i].1, xy[j].1), cmp::max(xy[k].1, xy[l].1));

                            let mut count = 0;
                            for m in 0..n {
                                let mx = xy[m].0;
                                let my = xy[m].1;
                                if mx >= x1 && mx <= x2 && my >= y1 && my <= y2 {
                                    count += 1;
                                }
                            }

                            if count >= K {
                                ans = cmp::min(ans, (x2 - x1) * (y2 - y1));
                            }
                        }
                    }
                }
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
