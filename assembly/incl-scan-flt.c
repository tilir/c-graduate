float foo(float *arr, int n) {
  int i;
  float tmp = 0;
  for (i = 0; i < n; ++i) {
    tmp += arr[i];
    arr[i] = tmp;
  }
  return tmp;
}
