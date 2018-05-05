#include "basic_func.h"

unsigned int getkey()
{
    unsigned int key;

    key = getch();
    if (key == 224)
    {
        key = getch();
        return key;
    }

    return key;
}

unsigned int get_key()
{
    unsigned int key;
    struct position_detail size = {0};

    get_console_size(&size);
    gotoxy(size.row - 1, size.col - 1);

    key = getkey();

    return key;
}

//Console functions
void gotoxy(const uint8_t row, const uint8_t col)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {col,row};
    SetConsoleCursorPosition(h, position);
}

void get_console_size(struct position_detail *size)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    size->col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size->row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void adjust_console_size(const struct position_detail size)
{
    SMALL_RECT windowSize = {0, 0 ,size.col - 1, size.row - 1};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

//Dynamic memory handling function
char **get_2D_char_array(const int m, const int n)
{
    short unsigned int i;
    char **data = NULL;

    data = (char **)malloc(m * sizeof(char *));
    for (i = 0; i < m; i++)
        data[i] = (char *)calloc(n, sizeof(char));

    return data;
}

char **change_2D_char_array_size(char **data, const int old_size, const int new_size, const int oneD_size)
{
    short unsigned int i;
    char **new_array = NULL;

    if ((old_size != new_size) || ((old_size > 0) && (new_size == 0)))
    {
        if ((data == NULL) || ((old_size == 0) && (new_size > 0)))
            new_array = get_2D_char_array(new_size, oneD_size);
        else if (old_size < new_size)
        {
            new_array = get_2D_char_array(new_size, oneD_size);

            for (i = 0; i < old_size; i++)
                strcpy(new_array[i], data[i]);
        }
        else if (old_size > new_size)
        {
            new_array = get_2D_char_array(new_size, oneD_size);

            for (i = 0; i < new_size; i++)
                strcpy(new_array[i], data[i]);
        }
    }

    for (i = 0; i < old_size; i++)
        free(data[i]);
    free(data);

    return new_array;
}

//Front-end function
void print_box(const unsigned short int box_type, const unsigned short int line_no1, const unsigned short int line_no2, const unsigned short int line_type)
{
    struct box_type_ASCII_codes
    {
        unsigned char tl, tr, bl, br, ver, hor;
    }box;
    struct line_type_ASCII_codes
    {
        unsigned char left, right, hor;
    }line;

    short unsigned int i, j;

    switch (box_type)
    {
    case 1:     //single horizontal and single vertical
        box.tl = 218;
        box.tr = 191;
        box.bl = 192;
        box.br = 217;
        box.ver = 179;
        box.hor = 196;
        break;
    case 2:     //double horizontal and double vertical
        box.tl = 201;
        box.tr = 187;
        box.bl = 200;
        box.br = 188;
        box.ver = 186;
        box.hor = 205;
        break;
    case 3:     //double horizontal and single vertical
        box.tl = 213;
        box.tr = 184;
        box.bl = 212;
        box.br = 190;
        box.ver = 179;
        box.hor = 205;
        break;
    case 4:     //single horizontal and double vertical
        box.tl = 214;
        box.tr = 183;
        box.bl = 211;
        box.br = 189;
        box.ver = 186;
        box.hor = 196;
        break;
    default:
        box.tl = (unsigned char)box_type;
        box.tr = (unsigned char)box_type;
        box.bl = (unsigned char)box_type;
        box.br = (unsigned char)box_type;
        box.ver = (unsigned char)box_type;
        box.hor = (unsigned char)box_type;
    }

    switch (line_type)
    {
    case 1:     //single horizontal and double vertical
        line.left = 195;
        line.right = 180;
        line.hor = 196;
        break;
    case 2:     //double horizontal and double vertical
        line.left = 204;
        line.right = 185;
        line.hor = 205;
        break;
    case 3:     //double horizontal and single vertical
        line.left = 198;
        line.right = 181;
        line.hor = 205;
        break;
    case 4:     //single horizontal and double vertical
        line.left = 199;
        line.right = 182;
        line.hor = 196;
        break;
    default:
        line.left = (unsigned char)box_type;
        line.right = (unsigned char)box_type;
        line.hor = (unsigned char)box_type;
    }

    for (i = top.col ; i <= bot.col; i++)
    {
        gotoxy(top.row, i);
        printf("%c", box.hor);
        gotoxy(bot.row, i);
        printf("%c", box.hor);
    }

    for (i = top.row; i <= bot.row; i++)
    {
        gotoxy(i, top.col);
        printf("%c", box.ver);
        gotoxy(i, bot.col);
        printf("%c", box.ver);

        if ((i == (line_no1 + top.row - 1)) || (i == (line_no2 + top.row - 1)))
        {
            for (j = top.col ; j <= bot.col; j++)
            {
                gotoxy(i, j);
                printf("%c", line.hor);
            }
            gotoxy(i, top.col);
            printf("%c", line.left);
            gotoxy(i, bot.col);
            printf("%c", line.right);
        }
    }
    gotoxy(top.row, top.col);
    printf("%c", box.tl);
    gotoxy(top.row, bot.col);
    printf("%c", box.tr);
    gotoxy(bot.row, top.col);
    printf("%c", box.bl);
    gotoxy(bot.row, bot.col);
    printf("%c", box.br);
}

void print_detail(const char *data1, const char *data2)
{
    short unsigned int len, length, breadth;
    struct position_detail size = {0, 0};

    get_console_size(&size);

    length = 2;
    breadth = 4;
    if (data2 == NULL)
    {
        length += 1;
        breadth += strlen(data1);
    }
    else
    {
        length += 2;
        if (strlen(data2) > strlen(data1))
            breadth += strlen(data2);
        else
            breadth += strlen(data1);
    }

    system("cls || clear");

    top.row = (size.row - length)/2;
    top.col = (size.col - breadth)/2;
    bot.row = top.row + length - 1;
    bot.col = top.col + breadth - 1;

    if (data2 == NULL)
        print_box(2, 0, 0, 0);
    else
        print_box(2, 0, 0, 0);

    len = strlen(data1);
    gotoxy(top.row + 1, ((size.col - len)/2));
    printf("%s", data1);

    if (data2 != NULL)
    {
        top.row++;
        gotoxy(top.row + 1, top.col + 2);
        printf("%s", data2);
    }

    (void)get_key();
}

unsigned short int display_menu(char **menu_items, const unsigned short int n, unsigned short int choice)
{
    //"menu_items" must be DYNAMICALLY created array....I don't know why
    //This function doesn't free() "menu_items"...it must be done manually
    //Press ESC return the last option i.e. "n - 1" option
    short unsigned int i, len, length, breadth;
    unsigned int key;
    struct position_detail size = {0, 0};

    get_console_size(&size);

    length = n + 2 + 2 +1;

    len = strlen(menu_items[0]);
    for (i = 1; i < n; i++)
        if (len < strlen(menu_items[i]))
            len = strlen(menu_items[i]);

    if (len <= 24)
        breadth = 30;
    else
        breadth = len + 6;

    while (1)
    {
        system("cls || clear");

        top.row = (size.row - length)/2;
        top.col = (size.col - breadth)/2;
        bot.row = top.row + length - 1;
        bot.col = top.col + breadth - 1;
        print_box(2, 3, 0, 2);

        len = strlen(menu_items[0]);
        gotoxy(top.row + 1, ((size.col - len)/2));
        printf("%s", menu_items[0]);

        top.row += 3;
        top.col += 1;
        bot.row = top.row + 2;
        bot.col -= 1;

        for (i = 1; i < n; i++)
        {
            if (choice == i)
            {
                print_box(3, 0, 0, 0);

                len = strlen(menu_items[i]);
                gotoxy(top.row + 1, ((size.col - len)/2));
                printf("%s", menu_items[i]);

                top.row += 3;
            }
            else
            {
                gotoxy(top.row, top.col + 2);
                printf("%s", menu_items[i]);

                top.row += 1;
            }
            bot.row = top.row + 2;
        }

        key = get_key();
        switch (key)
        {
        case UP:
            if (choice > 1)
                choice--;
            else
                choice = n - 1;
            break;
        case DOWN:
            if (choice < (n - 1))
                choice++;
            else
                choice = 1;
            break;
        case ESC:
            choice = n - 1;
            if (strcmpi(menu_items[choice], "Exit") != 0)
                return choice;
        case ENTER:
            return choice;
        }
    }
}
