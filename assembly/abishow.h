// Header for abishow abicallsite and abimain

#pragma once

struct S { int x; int y; int z; };

int foo(int x, int y);
int callfoo(int a, int b);
long long bar(char a, short b, int c, long d, long long e);
long long callbar();
long long sums(struct S s1, struct S s2, int a);
long long call_sums(int x, int y);