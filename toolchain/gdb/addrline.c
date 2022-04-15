//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Dwarf info invstigation
//
// for historical reasons I use it for readelf demo first
// gcc addrline.c -g -O0
// readelf --debug-dump=decodedline ./a.out
//
// try the same for factorial with O2
//
// then try:
//
// > gcc -O0 -g -fno-PIE -fno-PIC -static addrline.c
// > ./a.out
// > dmesg | tail -10 ---> ip value
// > addr2line -e a.out <ip value>
//
// -fno-PIE required (show without it)
//
//-----------------------------------------------------------------------------

int *p = (int *)0xDEADBEEF;

int main() {
  *p = 5; // BOOM
}
