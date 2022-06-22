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

//------------------------------------------------------------------------------
//
// Mixed-mode tuples
//
//------------------------------------------------------------------------------

// input: array of tuple, array of borders N0, N1, ... Nj
// modifies: tuple [first, last)
// returns: 0 if results dropped back to orig, 1 if next tuple generated
int next_mm_tuple_of(int *first, int *last, const int *bfirst);

// state for loopless generation
struct loopless_state;

// create and free state
struct loopless_state *create_loopless_state(int n);
void free_loopless_state(struct loopless_state *state);

// input: array of tuple, array of borders N0, N1, ... Nj, state
// modifies: tuple [first, last)
// returns: 0 if results dropped back to orig, 1 if next tuple generated
int loopless_next_mm_tuple_of(int *first, int *last, const int *bfirst,
                              struct loopless_state *ls);

//------------------------------------------------------------------------------
//
// Gray codes
//
//------------------------------------------------------------------------------

// modifies: sequence [first, last) to get next binary gray code
// ainf is integer state (parity of call)
int next_gray(int *first, int *last, int *ainf);

// modifies: sequence [first, last) to get next binary gray code
// ainf is integer state (number of step)
int next_gray_rho(int *first, int *last, int *n);

//------------------------------------------------------------------------------
//
// Partitions
//
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//
// Permutations
//
//------------------------------------------------------------------------------

// modifies: sequence [first, last) to get next permutation
// like 1 2 3 4 -> 1 2 4 3
int next_perm_of(int *first, int *last);
