typedef struct _show
{
    char time[10];
    char screen[10];
} show;

typedef struct _movie
{
    show shows[4];
    int show_count;
    char name[30];
    char lang[10];
} movie;

typedef struct _ticket
{
    movie t_movie;
    show t_show;
    int nos;
    int seats[10];
}ticket;