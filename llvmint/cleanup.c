//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// cleanup example: compiler does its best to clean things up
//
// try:
// > clang -O2 -emit-llvm -S cleanup.c
//
//-----------------------------------------------------------------------------

unsigned foo0(unsigned x) { return (2 * x + 1) * (3 * x + 1); }