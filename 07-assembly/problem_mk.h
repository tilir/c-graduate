// problem mk common types

#pragma once

enum reg_t {
  A = 0, B, C, D, RLAST
};

enum opcode_t {
  MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT, OPLAST
};

union operand_t {
  struct { int rd, rs; } ops;
  int rop;
  int imm;
};

struct instr_t {
  enum opcode_t opcode;
  union operand_t opnd;
};

struct reg_state_t {
  unsigned char data;
  unsigned char init;
  // ???
};
