#include <iostream>
#include <cstring>
#include <cstdlib>
#include "struct.cpp"
using namespace std;
movie g_movies[10];
int movie_size = 4;
int showcount = 3;
ticket g_ticket[10];
int ticket_count = 0;
/* Function Declaration */
void book_ticket();
void clear_console();
void show_ticket();
void display_welcome_screen();
class Movie
{
    public:
    void init_data();
};
void display_welcome_screen()
{
  clear_console();
  int choice;
  cout<<"\t\t\t\tWelcome To SRM Cinemas\n\n";
  do
  {
    cout<<"1-Ticket Booking\n2-Show Tickets\n3-Log out\n";
    cout<<"Enter you choice:"<<endl;
    cin>>choice;
    switch (choice)
    {
    case 3:
      clear_console();
      cout<<"\t\t\t\tThank you!!!\n";
      exit(1);
      break;
    case 1:
      book_ticket();
      break;
    case 2:
      show_ticket();
      break;
    default:
    cout<<"**Enter a number among the given numbers**"<<endl;
    }
  } while (choice != 3);
}
void Movie::init_data()
{
  FILE *fp = fopen("movies.txt", "r+");
  char buffer[1024] = "";
  int buffer_index = 0;
  int choice = 0;
  int show_size = 0;
  movie_size=0;
  for (char ch = fgetc(fp); !feof(fp); ch = fgetc(fp))
  {
    switch (ch)
    {
    case '$':
      switch (choice)
      {
      case 0:
        strcpy(g_movies[movie_size].name, buffer);
        break;

      case 1:
        strcpy(g_movies[movie_size].lang, buffer);
        break;

      case 2:
        strcpy(g_movies[movie_size].shows[show_size].time, buffer);
        break;

      case 3:
        strcpy(g_movies[movie_size].shows[show_size].screen, buffer);
        g_movies[movie_size].show_count = show_size + 1;
        show_size = 0;
        movie_size++;
        break;
      }
      choice += 1;
      choice %= 4;
      strncpy(buffer, "", strlen(buffer));
      buffer_index = 0;
      break;

    case '&':
      strcpy(g_movies[movie_size].shows[show_size].screen, buffer);
      show_size++;
      choice -= 1;
      strncpy(buffer, "", strlen(buffer));
      buffer_index = 0;
      break;

    default:
      buffer[buffer_index++] = ch;
      break;
    }
  }
}
int get_movie()
{
  clear_console();
  int movie_choice;
  int is_valid;
  do
  {
    cout<<"Movies:"<<movie_size<<endl;
    for (int itr = 0; itr < movie_size; itr++)
    {
      cout<< itr+1<<" - "<<g_movies[itr].name<<" "<<g_movies[itr].lang<<endl;
    }
    cout<<movie_size+1<<" - "<<"Main-Manu"<<endl;
    cout<<"Enter your choice: ";
    cin>>movie_choice;
    is_valid = (movie_choice > 0) && (movie_choice <= movie_size + 1);

    if (!is_valid)
    {
      cout<<"Enter a number among the given numbers"<<endl;
    }

    if (movie_choice == (movie_size + 1))
      display_welcome_screen();

  } while (!is_valid);

  return movie_choice - 1;
}
int get_show(movie chosen_movie)
{
  clear_console();
  int is_valid, choice;
  do
  {
    cout<<chosen_movie.name<<" - "<<"Show timings"<<endl;
    for (int itr = 0; itr < showcount; itr++)
    {
      cout<<itr+1<<" - "<<chosen_movie.shows[itr].time<<" "<<chosen_movie.shows[itr].screen<<endl;
    }
    cout<<showcount+1<<" - Back"<<endl;
    cout<<"Enter your choice";
    cin>>choice;
    is_valid = (choice > 0) && (choice <= movie_size + 1);
    if (!is_valid)
    {
      cout<<"Enter among the given numbers"<<endl;
    }

    if (choice == showcount + 1)
      book_ticket();

  } while (!is_valid);

  return choice - 1;
}
void show_seat_layout(movie chosen_movie, show m_show, int seat_arr[])
{
  clear_console();
  cout<<chosen_movie.name<<"-"<<m_show.time<<" ("<<m_show.screen<<")"<<endl;
  for (int itr = 0; itr < ticket_count; itr++)
  {
    ticket temp_ticket = g_ticket[itr];
    if ((strcmp(temp_ticket.t_movie.name, chosen_movie.name) == 0) && (strcmp(temp_ticket.t_show.time, m_show.time) == 0))
    {
      for (int itr_2 = 0; itr_2 < temp_ticket.nos; itr_2++)
      {
        seat_arr[temp_ticket.seats[itr_2] - 1] = 1;
      }
    }
  }

  for (int itr = 0; itr < 100; itr++)
  {
    if (seat_arr[itr] != 0)
      cout<<"*\t";
    else
      cout<<itr+1<<"\t";

    if ((itr + 1) % 10 == 0)
      cout<<endl;
  }
  cout<<"\n\t\t\tS   C   R   E   E   N\n";
  cout<<"Press 0 to cancel booking\n";
}
int get_no_of_tickets()
{
  int nop, is_valid;
  do
  {
    is_valid = 1;

    cout<<"Enter the number of persons: ";
    cin>>nop;
    if (nop == 0)
    {
      clear_console();
      cout<<"\t \t \tTicking Booking cancelled!\n\n";
      return -1;
    }
    if (nop > 10)
    {
      cout<<"Only 10 tickets can be booked at a time\n";
      is_valid = 0;
    }
    else if (nop < 0)
    {
      cout<<"Enter a Valid number"<<endl;
      is_valid = 0;
    }

  } while (!is_valid);

  return nop;
}
void get_seats(int nos, int seat_arr[], int seat_no[])
{
  int is_valid, temp;

  for (int itr = 0; itr < nos; itr++)
  {
    do
    {
      is_valid = 1;

    
      cout<<"Enter the seat number for person "<<itr+1<<":";
      cin>>temp;
      if (temp > 100 || temp < 1)
      {
        cout<<"Enter seat number within the given limit\n";
        is_valid = 0;
      }
      if (seat_arr[temp - 1] != 0)
      {
        cout<<"Already Booked!"<<endl;
        is_valid = 0;
      }
      for (int itr_2 = itr - 1; itr_2 >= 0; itr_2--)
        if (seat_no[itr_2] == temp)
        {
          cout<<"Already Selected"<<endl;
          is_valid = 0;
        }
    } while (!is_valid);

    seat_no[itr] = temp;
  }

  return;
}
void book_ticket()
{
  int seat_arr[100] = {0};

  int m_movie = get_movie();
  if (m_movie == -1)
    return;

  movie chosen_movie = g_movies[m_movie];

  int m_show = get_show(chosen_movie);
  if (m_show == -1)
    return;

  show chosen_show = chosen_movie.shows[m_show];

  show_seat_layout(chosen_movie, chosen_show, seat_arr);

  int nos = get_no_of_tickets();

  if (nos == -1)
    return;

  int seats[nos];
  get_seats(nos, seat_arr, seats);
  ticket temp_tick;
  for (int itr = 0; itr < nos; itr++)
  {
    temp_tick.seats[itr] = seats[itr];
  }
  temp_tick.t_movie = chosen_movie;
  temp_tick.t_show = chosen_show;
  temp_tick.nos = nos;
  g_ticket[ticket_count++] = temp_tick;
  clear_console();
  cout<<"\t\t\tTicket booked successfully!\n\n";
  FILE *fp = fopen("ticket.txt", "w+");
  fwrite(g_ticket, sizeof(ticket), ticket_count, fp);
  fclose(fp);
}
void show_ticket()
{
  clear_console();
  int x;
  if (ticket_count == 0)
  {
    cout<<"No tickets Booked\n";
    cout<<"Press 0 to go back";
    cin>>x;
    if (x == 0)
      display_welcome_screen();
  }
  else
  {
    cout<<"\t \t \tLast Booked ticket\n";
     FILE *ft = fopen("ticket.txt", "r");
    fread(g_ticket, sizeof(ticket), ticket_count, ft);
    cout<<g_ticket[ticket_count-1].t_movie.name<<" ("<<g_ticket[ticket_count-1].t_movie.lang<<") - "<<g_ticket[ticket_count-1].t_show.time<<" "<<g_ticket[ticket_count-1].t_show.screen<<endl;
    cout<<"Seats\n";
    for (int j = 0; j < g_ticket[ticket_count-1].nos; j++)
      cout<<g_ticket[ticket_count-1].seats[j]<<" ";
    cout<<endl;
    fclose(ft);
    cout<<"1-Show all tickets"<<endl;
    cout<<"2-Go back"<<endl;
    cin>>x;
    if (x == 2)
      display_welcome_screen();
    else if (x == 1)
    {
      clear_console();
      FILE *ft = fopen("ticket.txt", "r");
      fread(g_ticket, sizeof(ticket), ticket_count, ft);
      for (int i = 0; i < ticket_count; i++)
      {
        cout<<g_ticket[i].t_movie.name<<" ("<<g_ticket[i].t_movie.lang<<") - "<<g_ticket[i].t_show.time<<" "<<g_ticket[i].t_show.screen<<endl;
        cout<<"Seats:\n";
        for (int j = 0; j < g_ticket[i].nos; j++)
          cout<<g_ticket[i].seats[j]<<" ";
        cout<<"\n"<<endl;
      }
      fclose(ft);
    }
  }
}
void clear_console()
{
  system("cls");
}
int main()
{
    Movie m;
  clear_console();
  m.init_data();
  display_welcome_screen();
  return 0;
}