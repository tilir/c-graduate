//------------------------------------------------------------------------------
//
// Combinatorial algorithms joint header
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#pragma once

// n -- number to partition
// m -- number of parts
// start -- pointer to the beginning of m-element array
// fills array with first partition like 1118
void initial_partition(int n, int m, int *start);

// n -- number to partition
// m -- number of parts
// start -- pointer to the beginning of m-element array
// modifies array, going to next partition, like 1118 -> 1127
// returns: 0 if results dropped back to orig, 1 if next partition generated
int next_partition(int n, int m, int *start);

// input: array of tuple, array of borders N0, N1, ... Nj
// modifies: tuple [first, last)
// returns: 0 if results dropped back to orig, 1 if next tuple generated
int next_mm_tuple_of(int *first, int *last, const int *bfirst);

// modifies: sequence [first, last) to get next permutation
// like 1 2 3 4 -> 1 2 4 3
int next_perm_of(int *first, int *last);