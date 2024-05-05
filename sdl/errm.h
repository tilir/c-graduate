//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Smart error macros
//
//-----------------------------------------------------------------------------

#pragma once

#define ERR_1(S)                                                               \
  fprintf(stderr, "[%s:%d] %s error: %s\n", __FILE__, __LINE__, #S,            \
          SDL_GetError());

#define ERR_2(S, SEVTY)                                                        \
  do {                                                                         \
    ERR_1(S)                                                                   \
    if (SEVTY)                                                                 \
      abort();                                                                 \
  } while (0)

#define GET_3RD_ARG(A1, A2, A3, ...) A3
#define ERR_MACRO_CHOOSER(...) GET_3RD_ARG(__VA_ARGS__, ERR_2, ERR_1)
#define ERR(...)                                                               \
  do {                                                                         \
    ERR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__);                               \
  } while (0)
