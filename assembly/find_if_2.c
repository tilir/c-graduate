double *foo(double *arr, int n, int val) {
  int i;
  for (i = 0; i < n; ++i)
    if ((int)arr[i] == val)
      return arr + i; 
  return arr + n;
}
