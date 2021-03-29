//------------------------------------------------------------------------------
//
// C interface for abstract drawer
//
//------------------------------------------------------------------------------
//
// Main usage idea: you are defining callback
//
// myfunc(const struct sufrace *s, void *data) {
//
//    /* Here draw using surface interface */
//
// }
//
// Then you are querying viewport:
//
// query_viewport(w, h, &myfunc, r, &mydata);
// 
//------------------------------------------------------------------------------

#pragma once

#include <assert.h>
#include <stdbool.h>

enum pollres { PROCEED, STOP };

_Static_assert(sizeof(unsigned) == 4, "unsigned must be 4 bytes");

// build color from parts
enum Offset { AOFF = 24, ROFF = 16, GOFF = 8, BOFF = 0 };

static inline unsigned buildcolor(unsigned r, unsigned g, unsigned b, unsigned a) {
  return ((a << AOFF) | (r << ROFF) | (g << GOFF) | (b << BOFF));
}

static inline unsigned cpart(unsigned c, unsigned o) {
  return (c >> o) & 0xF;
}

struct surface_t;

unsigned surface_width(const struct surface_t *);
unsigned surface_height(const struct surface_t *);
void surface_putpixel(const struct surface_t *, int x, int y, unsigned color);
void surface_putlogpixel(const struct surface_t *, double x, double y, unsigned color);
void surface_fillwith(const struct surface_t *, unsigned color);

enum keyspecial_t { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

struct keypressed_t {
  bool is_special;
  union {
    enum keyspecial_t k;
    char s;
  } u;
};

static inline struct keypressed_t key_special(enum keyspecial_t k) {
  struct keypressed_t kp = {.is_special = true, .u.k = k };
  return kp; 
}

static inline struct keypressed_t key_regular(char s) {
  struct keypressed_t kp = {.is_special = false, .u.s = s };
  return kp; 
}

static inline bool is_special(const struct keypressed_t *pk) {
  return pk->is_special;
}

static inline char special(const struct keypressed_t *pk) {
  assert(pk->is_special);
  return pk->u.k;
}

static inline char regular(const struct keypressed_t *pk) {
  assert(!pk->is_special);
  return pk->u.s;
}

typedef void (*vp_surf_cb_t)(struct surface_t*, void *);
typedef void (*vp_key_cb_t)(struct keypressed_t, void *);

struct viewport_t;

enum pollres viewport_poll(struct viewport_t *);
void dump(struct viewport_t *, const char *name);
void bindkeys(struct viewport_t *, vp_key_cb_t k, void *data);

struct viewport_t *query_viewport(int w, int h, vp_surf_cb_t c, void *data);
void free_viewport();


