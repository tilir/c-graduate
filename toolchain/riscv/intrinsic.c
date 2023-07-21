#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <riscv_vector.h>

void *memcpy_vec(unsigned char *dst, unsigned char *src, unsigned n) {
  void *save = dst;
  // copy data byte by byte
  for (size_t vl; n > 0; n -= vl, src += vl, dst += vl) {
    vl = __riscv_vsetvl_e8m8(n);
    vuint8m8_t vec_src = __riscv_vle8_v_u8m8(src, vl);
    __riscv_vse8_v_u8m8(dst, vec_src, vl);
  }
  return save;
}

void test_arr(int size) {
  int i;
  unsigned char *arr;
  unsigned char *dst;
  arr = malloc(size);
  dst = malloc(size);
  if (!arr || !dst) abort();
  
  for (i = 0; i < size; ++i)
    arr[i] = rand() % size;

  memcpy_vec(dst, arr, size);

  for (i = 0; i < size; ++i)
    if (arr[i] != dst[i]) {
      fprintf(stderr, "Error at %d: %d != %d\n", i, (int)arr[i], (int)dst[i]);
      abort();
    }

  free(arr);
  free(dst);
}

int main() {
  srand(time(NULL));
  test_arr(127); // prime number
  test_arr(128); // power of 2
}

