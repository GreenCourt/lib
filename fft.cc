void fft(vector<complex<double>> &seq /* will be modified */, bool inverse = false) {
  /* O(n log n) */
  int n = seq.size();
  int ln = 0; // log2(n)
  while(1<<ln < n) ln++;
  assert(n == 1<<ln);
  for(int i=0; i<n; i++) {
    int j = 0;
    for(int k=0; k<ln; k++) j |= (i >> k & 1) << (ln - 1 - k);
    if(i<j) swap(seq[i], seq[j]);
  }
  constexpr double tau = 2 * acos(-1);
  for(int b=1; b<n; b <<= 1) {
    for(int j = 0; j < b; j++) {
      complex<double> zeta = polar(1.0, tau / (2 * b) * j * (inverse ? 1 : -1));
      for(int k = 0; k < n; k += b * 2) {
        int l=j+k, r=j+k+b;
        complex<double> sl = seq[l], sr = seq[r] * zeta;
        seq[l] = sl + sr, seq[r] = sl - sr;
      }
    }
  }
  if(inverse) for(int i=0; i<n; i++) seq[i] /= n;
}

vector<complex<double>> fft(const vector<double> &input, bool inverse=false) {
  /* O(n log n) */
  int n = input.size();
  vector<complex<double>> c(n);
  for(int i=0; i<n; ++i) c[i] = complex<double>(input[i], 0);
  fft(c, inverse);
  return c;
}

vector<double> convolution(const vector<double> &a, const vector<double> &b) {
  /* O(n log n) */
  assert(a.size() && b.size());
  int n = a.size() + b.size() - 1;
  int p2 = 1;
  while(p2 < n) p2 <<= 1;
  vector<complex<double>> A(p2), B(p2);
  for(int i=0; i<a.size(); ++i) A[i] = complex<double>(a[i], 0);
  for(int i=0; i<b.size(); ++i) B[i] = complex<double>(b[i], 0);
  fft(A), fft(B);
  for(int i=0; i<p2; i++) A[i] *= B[i];
  fft(A, true);
  vector<double> c(n);
  for(int i=0; i<n; i++) c[i] = A[i].real();
  return c;
}