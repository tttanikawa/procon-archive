#[allow(unused_imports)]
use itertools::Itertools;
#[allow(unused_imports)]
use itertools_num::ItertoolsNum;
use proconio::*;
#[allow(unused_imports)]
use std::cmp;
#[allow(unused_imports)]
use std::iter;
#[allow(unused_imports)]
use superslice::*;

pub struct Csr<E> {
    start: Vec<usize>,
    elist: Vec<E>,
}

impl<E> Csr<E>
where
    E: Copy + Clone,
{
    pub fn new(n: usize, edges: &[(usize, E)], init: E) -> Self {
        let mut csr = Csr {
            start: vec![0; n + 1],
            elist: vec![init; edges.len()],
        };
        for e in edges.iter() {
            csr.start[e.0 + 1] += 1;
        }
        for i in 1..=n {
            csr.start[i] += csr.start[i - 1];
        }
        let mut counter = csr.start.clone();
        for e in edges.iter() {
            csr.elist[counter[e.0]] = e.1;
            counter[e.0] += 1;
        }
        csr
    }
}

#[derive(Copy, Clone)]
struct _Edge {
    to: usize,
}

/// Reference:
/// R. Tarjan,
/// Depth-First Search and Linear Graph Algorithms
pub struct SccGraph {
    n: usize,
    edges: Vec<(usize, _Edge)>,
}

impl SccGraph {
    pub fn new(n: usize) -> Self {
        SccGraph { n, edges: vec![] }
    }

    pub fn num_vertices(&self) -> usize {
        self.n
    }

    pub fn add_edge(&mut self, from: usize, to: usize) {
        self.edges.push((from, _Edge { to }));
    }

    /// return pair of (# of scc, scc id)
    pub fn scc_ids(&self) -> (usize, Vec<usize>) {
        // In C++ ac-library, this function is implemented by using recursive lambda functions.
        // Instead, we use fn and struct for capturing environments.
        struct _Env {
            g: Csr<_Edge>,
            now_ord: usize,
            group_num: usize,
            visited: Vec<usize>,
            low: Vec<usize>,
            ord: Vec<Option<usize>>,
            ids: Vec<usize>,
        }
        let mut env = _Env {
            g: Csr::new(self.n, &self.edges, _Edge { to: 0 }),
            now_ord: 0,
            group_num: 0,
            visited: Vec::with_capacity(self.n),
            low: vec![0; self.n],
            ord: vec![None; self.n],
            ids: vec![0; self.n],
        };

        fn dfs(v: usize, n: usize, env: &mut _Env) {
            env.low[v] = env.now_ord;
            env.ord[v] = Some(env.now_ord);
            env.now_ord += 1;
            env.visited.push(v);

            for i in env.g.start[v]..env.g.start[v + 1] {
                let to = env.g.elist[i].to;
                if let Some(x) = env.ord[to] {
                    env.low[v] = std::cmp::min(env.low[v], x);
                } else {
                    dfs(to, n, env);
                    env.low[v] = std::cmp::min(env.low[v], env.low[to]);
                }
            }
            if env.low[v] == env.ord[v].unwrap() {
                loop {
                    let u = *env.visited.last().unwrap();
                    env.visited.pop();
                    env.ord[u] = Some(n);
                    env.ids[u] = env.group_num;
                    if u == v {
                        break;
                    }
                }
                env.group_num += 1;
            }
        }
        for i in 0..self.n {
            if env.ord[i].is_none() {
                dfs(i, self.n, &mut env);
            }
        }
        for x in env.ids.iter_mut() {
            *x = env.group_num - 1 - *x;
        }
        (env.group_num, env.ids)
    }

    pub fn scc(&self) -> Vec<Vec<usize>> {
        let ids = self.scc_ids();
        let group_num = ids.0;
        let mut counts = vec![0usize; group_num];
        for &x in ids.1.iter() {
            counts[x] += 1;
        }
        let mut groups: Vec<Vec<usize>> = (0..ids.0).map(|_| vec![]).collect();
        for i in 0..group_num {
            groups[i].reserve(counts[i]);
        }
        for i in 0..self.n {
            groups[ids.1[i]].push(i);
        }
        groups
    }
}

pub struct TwoSat {
    n: usize,
    answer: Vec<bool>,
    scc: SccGraph,
}

impl TwoSat {
    pub fn new(n: usize) -> Self {
        TwoSat {
            n,
            answer: vec![false; n],
            scc: SccGraph::new(2 * n),
        }
    }

    pub fn add_clause(&mut self, i: usize, f: bool, j: usize, g: bool) {
        assert!(i < self.n);
        assert!(j < self.n);
        self.scc
            .add_edge(2 * i + if f { 0 } else { 1 }, 2 * j + if g { 1 } else { 0 });
        self.scc
            .add_edge(2 * j + if g { 0 } else { 1 }, 2 * i + if f { 1 } else { 0 });
    }

    pub fn satisfiable(&mut self) -> bool {
        let id = self.scc.scc_ids().1;
        for i in 0..self.n {
            if id[2 * i] == id[2 * i + 1] {
                return false;
            }
            self.answer[i] = id[2 * i] < id[2 * i + 1];
        }
        true
    }
}

#[fastout]
fn main() {
    input! {
        n: usize,
        d: i64,
        xy: [(i64, i64); n]
    }

    let mut ts = TwoSat::new(n);

    for i in 0..n {
        for j in i + 1..n {
            if (xy[i].0 - xy[j].0).abs() < d {
                ts.add_clause(i, false, j, false);
            }
            if (xy[i].0 - xy[j].1).abs() < d {
                ts.add_clause(i, false, j, true);
            }
            if (xy[i].1 - xy[j].0).abs() < d {
                ts.add_clause(i, true, j, false);
            }
            if (xy[i].1 - xy[j].1).abs() < d {
                ts.add_clause(i, true, j, true);
            }
        }
    }

    if !ts.satisfiable() {
        println!("No");
        return;
    }

    println!("Yes");
    let answer = ts.answer;
    for i in 0..n {
        if answer[i] {
            println!("{}", xy[i].0);
        } else {
            println!("{}", xy[i].1);
        }
    }
}
