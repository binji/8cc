// Copyright 2012 Rui Ueyama <rui314@gmail.com>
// This program is free software licensed under the MIT license.

#include "test.h"

static void test_char(void) {
    expect(65, 'A');
    expect(97, 'a');
    expect(7, '\a');
    expect(8, '\b');
    expect(12, '\f');
    expect(10, '\n');
    expect(13, '\r');
    expect(9, '\t');
    expect(11, '\v');
    expect(27, '\e');

    expect(0, '\0');
    expect(7, '\7');
    expect(15, '\17');
    expect(-99, '\235');

    expect(0, '\x0');
    expect(-1, '\xff');
    expect(15, '\xF');
    expect(18, '\x012');
}

static void test_string(void) {
    expect_string("abc", "abc");
    expect('a', "abc"[0]);
    expect(0, "abc"[3]);
    expect_string("abcd", "ab" "cd");
    expect_string("abcdef", "ab" "cd" "ef");

    char expected[] = { 65, 97, 7, 8, 12, 10, 13, 9, 11, 27, 7, 15, -99, -1, 18, 0 };
    expect_string(expected, "Aa\a\b\f\n\r\t\v\e\7\17\235\xff\x012");

    expect('c', L'c');
    expect_string("asdf", L"asdf");

    // make sure we can handle an identifier starting with "L"
    int L = 7;
    expect(7, L);
    int L123 = 123;
    expect(123, L123);
}

int g1 = (int){ 80 };
int *g2 = &(int){ 81 };
struct g3 { int x; } *g3 = &(struct g3){ 82 };
struct g4 { char x; struct g4a { int y[2]; } *z; } *g4 = &(struct g4){ 83, &(struct g4a){ 84, 85 } };

static void test_compound(void) {
    expect(1, (int){ 1 });
    expect(3, (int[]){ 1, 2, 3 }[2]);
    expect(12, sizeof((int[]){ 1, 2, 3 }));
    expect(6, (struct { int x[3]; }){ 5, 6, 7 }.x[1]);

    expect(80, g1);
    expect(81, *g2);
    expect(82, g3->x);
    expect(83, g4->x);
    expect(84, g4->z->y[0]);
    expect(85, g4->z->y[1]);
}

void testmain(void) {
    print("literal");
    test_char();
    test_string();
    test_compound();
}
