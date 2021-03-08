struct S {int x; char y;};

union U {int x; char y;};

int foo(struct S *s, union U *u) { return s->x + u->x; }

int main() {
  struct S s = {1, 'a'};
  union U u = {56};
  foo(&s, &u);
}
