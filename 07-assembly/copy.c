enum { size = 1024 };

void copy(const int *from, int *to) {
  int i;
  for (i = 0; i < size; ++i)
	  to[i] = from[i];
}
