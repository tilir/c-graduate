//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Builtin demonstration
// 
// clang-15 --target=riscv64 -march=rv64gcv_zknd aes.c -O2 -emit-llvm -S
// clang-15 --target=riscv64 -march=rv64gcv_zknd aes.c -O2 -mllvm -print-after-all -c
//
//-----------------------------------------------------------------------------

long long final_decrypt_round(long long x, long long y) {
  return __builtin_riscv_aes64ds_64(x, y);
}
