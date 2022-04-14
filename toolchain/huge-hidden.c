unsigned helper1(unsigned x) { return 0; }
unsigned helper2(unsigned x) { return 1; }

unsigned __attribute__((visibility("default"))) myfunc(unsigned n) {
  return helper1(n) + helper2(n);
}
