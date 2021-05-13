struct UnionFind {
  vector<int> data;
  UnionFind(int size=0) : data(size, -1) { }
  bool unite(int x, int y) {
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return x != y;
  }
  bool find(int x, int y) { return root(x) == root(y); }
  int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  int size(int x) { return -data[root(x)]; }
  vector<vector<int>> groups() {
    int n = data.size();
    vector<int> r(n), group_size(n);
    for (int i = 0; i < n; i++) { r[i] = root(i); group_size[r[i]]++; }
    vector<vector<int>> result(n);
    for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
    for (int i = 0; i < n; i++) result[r[i]].push_back(i);
    result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
    return result;
  }
};
