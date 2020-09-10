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
    E: Clone + Copy,
{
    pub fn new(n: usize, edges: &[(usize, E)], init: E) -> Self {
        let mut csr = Csr {
            start: vec![0usize; n + 1],
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

    pub fn scc_ids(&self) -> (usize, Vec<usize>) {
        let g = Csr::new(self.n, &self.edges, _Edge { to: 0 });
        let mut now_ord = 0usize;
        let mut group_num = 0usize;
        let mut visited = Vec::with_capacity(self.n);
        let mut low = vec![0; self.n];
        let mut ord = vec![None; self.n];
        let mut ids = vec![0; self.n];

        fn dfs(
            v: usize,
            n: usize,
            g: &Csr<_Edge>,
            now_ord: &mut usize,
            group_num: &mut usize,
            visited: &mut Vec<usize>,
            low: &mut Vec<usize>,
            ord: &mut Vec<Option<usize>>,
            ids: &mut Vec<usize>,
        ) {
            low[v] = *now_ord;
            ord[v] = Some(*now_ord);
            *now_ord += 1;
            visited.push(v);

            for i in g.start[v]..g.start[v + 1] {
                let to = g.elist[i].to;
                if ord[to].is_none() {
                    dfs(to, n, g, now_ord, group_num, visited, low, ord, ids);
                    low[v] = std::cmp::min(low[v], low[to]);
                } else {
                    low[v] = std::cmp::min(low[v], ord[to].unwrap());
                }
            }
            if low[v] == ord[v].unwrap() {
                loop {
                    let u = *visited.last().unwrap();
                    visited.pop();
                    ord[u] = Some(n);
                    ids[u] = *group_num;
                    if u == v {
                        break;
                    }
                }
                *group_num += 1;
            }
        }

        for i in 0..self.n {
            if ord[i].is_none() {
                dfs(
                    i,
                    self.n,
                    &g,
                    &mut now_ord,
                    &mut group_num,
                    &mut visited,
                    &mut low,
                    &mut ord,
                    &mut ids,
                );
            }
        }

        for x in ids.iter_mut() {
            *x = group_num - 1 - *x;
        }

        (group_num, ids)
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

#[derive(Copy, Clone)]
struct _Edge {
    to: usize,
}

struct SccGraphO {
    internal: SccGraph,
}

impl SccGraphO {
    pub fn new(n: usize) -> Self {
        SccGraphO {
            internal: SccGraph::new(n),
        }
    }

    pub fn add_edge(&mut self, from: usize, to: usize) {
        let n = self.internal.num_vertices();
        assert!(from < n);
        assert!(to < n);
        self.internal.add_edge(from, to);
    }

    pub fn scc(&self) -> Vec<Vec<usize>> {
        self.internal.scc()
    }
}

#[fastout]
fn main() {
    input! {
        n: usize,
        m: usize,
        edges: [(usize, usize); m],
    }

    let mut g = SccGraphO::new(n);
    for (u, v) in edges.into_iter() {
        g.add_edge(u, v);
    }

    let scc = g.scc();
    println!("{}", scc.len());
    for c in scc.into_iter() {
        print!("{}", c.len());
        for v in c.into_iter() {
            print!(" {}", v);
        }
        println!("");
    }
}
