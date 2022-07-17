//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// inline example: test inline params
//
// try:
// > clang -O2 -emit-llvm -S inline.c
// > clang -O2 -mllvm -inline-threshold=1000 -emit-llvm -S inline.c
// > clang -O2 -Rpass-missed=inline -emit-llvm -S inline.c
//
//-----------------------------------------------------------------------------

unsigned foo8(unsigned x);

static unsigned foo7(unsigned x) { return foo8(47 * x + 1) + foo8(53 * x + 1); }

static unsigned foo6(unsigned x) { return foo7(41 * x + 1) + foo7(43 * x + 1); }

static unsigned foo5(unsigned x) { return foo6(31 * x + 1) + foo6(37 * x + 1); }

static unsigned foo4(unsigned x) { return foo5(23 * x + 1) + foo5(29 * x + 1); }

static unsigned foo3(unsigned x) { return foo4(17 * x + 1) + foo4(19 * x + 1); }

static unsigned foo2(unsigned x) { return foo3(11 * x + 1) + foo3(13 * x + 1); }

static unsigned foo1(unsigned x) { return foo2(5 * x + 1) + foo2(7 * x + 1); }

unsigned foo0(unsigned x) { return foo1(2 * x + 1) + foo1(3 * x + 1); }
