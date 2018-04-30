#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include <QBASIC_func_C.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 27
#define SPACE 32
#define ENTER 13

struct position_detail
{
    uint8_t row, col;
}top, bot;

unsigned int getkey();
unsigned int get_key();         //goes to bottom right corner of screen and asks for input

//Console functions
void gotoxy(const uint8_t, const uint8_t);
void get_console_size(struct position_detail *);
void adjust_console_size(const struct position_detail);

//Dynamic memory handling functions
char **get_2D_char_array(const int, const int);
char **change_2D_char_array_size(char **, const int, const int, const int);

//Front-end functions
void print_box(const unsigned short int, const unsigned short int, const unsigned short int, const unsigned short int);
void print_detail(const char *, const char*);
unsigned short int display_menu(char **, const unsigned short int, unsigned short int);
