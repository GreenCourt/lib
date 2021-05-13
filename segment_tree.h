template <class S, S (*op)(S, S), S (*e)()> struct segment_tree {
  int n, leafs;
  vector<S> node;

  segment_tree(int n=0) : segment_tree(vector<S>(n, e())) {}
  segment_tree(const vector<S>& initial) : n(int(initial.size())) {
    /* O(n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<S>(2 * leafs - 1, e());
    for(int i=0; i<n; i++) node[i+leafs-1] = initial[i];
    for(int i=leafs-2; i>=0; --i) node[i] = op(node[l_child(i)], node[r_child(i)]);
  }

  inline int r_child(int v) { return v*2+2; }
  inline int l_child(int v) { return v*2+1; }
  inline int parent(int v) { return (v+1)/2-1; }

  S product(int l, int r, int v=0, int vl=0, int vr=-1) { /* [l, r) */
    /* O(log n) */
    assert(l >=0 && l <= n);
    assert(r >=0 && r <= n);
    vr = (vr==-1) ? leafs : vr;
    if(l <= vl && vr <= r) return node[v];
    S ret = e(); int mid=(vl+vr)/2;
    if(l < mid) ret = op(product(l, r, l_child(v), vl, mid),ret);
    if(r > mid) ret = op(ret,product(l, r, r_child(v), mid, vr));
    return ret;
  }

  void set(int index, S s) {
    /* O(log n) */
    int v = index + (leafs-1);
    node[v] = s;
    while((v=parent(v)) != -1) node[v] = op(node[l_child(v)], node[r_child(v)]);
  }
  S get(int index) { return node[index + (leafs-1)]; }
};

#if 0 /* Range Min */
using S = int;
S op(S a, S b) { return min(a, b); }
S e() { return 1e9; }
#endif

#if 0 /* Range Sum */
using S = int;
S op(S a, S b) { return a + b; }
S e() { return 0; }
#endif
