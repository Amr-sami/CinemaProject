
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<ctime>
using namespace std;


struct timer
{
    int hours;       // 24-hours
    int minutes;
};
struct theatre
{
    int capacity = 64;
    bool seats[8][8];
};
struct screeinginfo
{
    timer timer;
    theatre theatre;
};
struct movie
{
    string title;
    string director;
    string actors;
    float rating;
    timer ti;
    screeinginfo screeningInfo[2]; //two screening shows
};

movie movies[4];// object from movie -- number of films that cinema have .. we mention that we have 4 movies 

bool validtimeformovie(timer movie_time); // validate current time with movie time

void reservationdata(int movie_number, int screen); // takes movie and number of screen

void menu();   // show options to user

void getdatafromsource(); // import data from file and disblay 

void choosemovie();  // select movie , select  Available time and seats

void display(); //display data



int main()
{
    getdatafromsource();
    menu();
}
bool validtimeformovie(timer movie_time) //function to validate current time with movie time
{
    //get current time 
    time_t ttime = time(0);
    char* dt = ctime(&ttime);
    string dt1(dt);
    int current_hours = stoi(dt1.substr(11, 2)), current_minutes = stoi(dt1.substr(14, 2));

    //compare with movie time
    if (current_hours < movie_time.hours) //away long before movie time
        return true;
    else if (current_hours > movie_time.hours) //after hours of movie time
        return false;
    else {
        movie_time.minutes += 15;
        if (movie_time.minutes > 60)
            movie_time.minutes -= 60;

        if (current_minutes <= movie_time.minutes) //minutes away before movie
            return true;
    }

    return false;
}

void menu()
{
    cout << "\t \t \t \t \t  WELCOME TO ECOWEST CINEMA" << endl;
    cout << endl << endl;
    cout << " 1- press 1 to search movies " << endl;
    cout << " 2- press 2 to exit          " << endl;
    int n;
choose:
    cin >> n;
    if (n == 1)
    {
        system("CLS");
        
        display();
    }

    else if (n == 2)
        exit(0);
    else {
        cout << "Enter valid value :";
        goto choose;
    }


}

void choosemovie()  //select from movie's list ,
{

select_movie:
    
    int movie_number;
    cout << " Select Movie : ";

    cin >> movie_number;

    int movies_size = sizeof(movies) / sizeof(movies[0]); //size of movie list

    if (movie_number > movies_size) //if invalid movie number
    {
        cout << "insert valid movie :";
        goto select_movie;
    }
    system("cls"); // clean screen
    //select movie time
    int timer_selection;
    cout << "insert movie time:-" << endl;
    cout << "1- " << movies[movie_number - 1].screeningInfo[0].timer.hours << ":" << movies[movie_number - 1].screeningInfo[0].timer.minutes << endl;
    cout << "2- " << movies[movie_number - 1].screeningInfo[1].timer.hours << ":" << movies[movie_number - 1].screeningInfo[1].timer.minutes << endl;
po:
    cin >> timer_selection;
    if (timer_selection > 3 && timer_selection <= 0)
    {
        cout << "Enter Valid value : ";
        goto po;
    }

    //validate movie time with current time
    if (validtimeformovie(movies[movie_number - 1].screeningInfo[timer_selection - 1].timer) == false) {
        cout << "Movie already started, available times for the movie:-" << endl;
        cout << movies[movie_number - 1].screeningInfo[0].timer.hours << ":" << movies[movie_number - 1].screeningInfo[0].timer.minutes << endl;
        cout << movies[movie_number - 1].screeningInfo[1].timer.hours << ":" << movies[movie_number - 1].screeningInfo[1].timer.minutes << endl;
        int c;
        cout << "Insert 1 to back to movielist :"; cin >> c;
        if (c == 1)
            display();
        //TODO: show all available times or show all avaialble movies or cancel
        goto select_movie;
    }


    reservationdata(movie_number - 1, timer_selection); //pass choosen movie with selected show time
}

void reservationdata(int movie_number, int screen) // takes movie and number of screen 
{

    //if all seats reserved
    if (movies[movie_number].screeningInfo[screen - 1].theatre.capacity == 0) {  // now all seates available if theatre.capacity == 64 would be reserved
        cout << "All seates reserved" << endl;
        cout << endl << endl;
        cout << "select 1 to back to chooseing movie or 2 to back to main menu " << endl;
        int e;
    backpoint:
        cin >> e;
        if (e == 1)
        {
            system("cls");
            display();
        }
        else if (e == 2)
        {
            system("cls");
            menu();
        }
        else
        {
            cout << "Enter Valid Value " << endl;
            goto backpoint;
        }
        return;
    }

select_number_of_seats:

    //enter number of needed seats
    int number_of_seats;
    system("cls");
    cout << "Please insert number of seats : " << endl;
    cin >> number_of_seats;
    system("cls");

    //if number of needed seats more than current capacity, choose from available ones or cancel
    if (number_of_seats > movies[movie_number].screeningInfo[screen - 1].theatre.capacity) // لو عدد الكراسي اللي هو عايزها اكبر من عدد الكراسي الموجودة
    {
        cout << "no seats available for this number, only available " << movies[movie_number].screeningInfo[screen - 1].theatre.capacity << " seat" << endl; // عدد الكراسي الموجودة 
        int m;
        cout << "insert 1 to back to main menu or 2 to search movie " << endl;
        cin >> m;
        if (m == 1)
        {
            system("cls");
            menu();
        }
        else if (m == 2)
        {
            system("cls");
            display();
        }
        else 
        goto select_number_of_seats;
    }

    //show screening seats
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) {
            if (movies[movie_number].screeningInfo[screen - 1].theatre.seats[i][j])
                cout << "[X]";
            else
                cout << "[ ]";
            cout << " ";
        }
        cout << endl;
    }

    //choosing seats by indexes
    cout << "choose your seats by row and col" << endl;
    int row, col;
    for (int i = 0; i < number_of_seats; i++) {

    select_row_col:

        cout << "enter row" << endl;
        cin >> row;
        cout << "enter column" << endl;
        cin >> col;
        if (row > 8 || col > 8)
        {
            cout << "insert valid value" << endl;
            goto select_row_col;
        }

        //if already reserved
        if (movies[movie_number].screeningInfo[screen - 1].theatre.seats[row - 1][col - 1]) // لو الكرسي اتعلم عليه او دخلت علي نفس الكرسي مرتين
        {
            cout << "seat already reserved" << endl;
            goto select_row_col;                  // هيرجع يختار تاني
        }

        //reserve seat
        movies[movie_number].screeningInfo[screen - 1].theatre.seats[row - 1][col - 1] = true;     // غير كدة هيعلم الكرسي 
    }

    //update capacity of screening show
    movies[movie_number].screeningInfo[screen - 1].theatre.capacity -= number_of_seats;  // هنحدث عدد الكراسي اللي موجوة دلوقتي


    cout << "seats reserved successfully:-" << endl;
    cout << "------------------------------------" << endl;
    system("cls");
    for (int i = 0; i < 8; i++)     /// هنعرض هنا عدد الكراسي المحجوزة 
    {
        for (int j = 0; j < 8; j++) {
            if (movies[movie_number].screeningInfo[screen - 1].theatre.seats[i][j])       
                cout << "[X]";
            else
                cout << "[ ]";
            cout << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------" << endl;
    cout << "Succesfuly booked :) " << endl;
    cout << endl << endl;
    int b;
    cout << "select 1 to back to main menu ";
point:
    cin >> b;
    if (b == 1)

    {
        system("cls");
        menu();
    }
    else
    {
        cout << "Insert Valid value " << endl;
        goto point;
    }




}

void getdatafromsource()
{
    fstream myData;   //declare object << 1-declare object -- 2-open -- 3-read -- 4-close  // if
    myData.open("E:/Mymovies/Data.txt", ios::in); // ios::in   open file
    if (myData.is_open()) {   //checking whether the file is open
        string myMovies;
        int i = 0, movie_i = 0; // movie[0] movie [1] movie [2]
        while (getline(myData, myMovies)) { //read data from file object and put it into string line by line.
            if (movie_i > 3) // false until we increase movie_i ++ //0 1 2 3
                break;
            if (i == 0)
                movies[movie_i].title = myMovies;
            else if (i == 1)
                movies[movie_i].director = myMovies;
            else if (i == 2)
                movies[movie_i].actors = myMovies;
            else if (i == 3)
                movies[movie_i].rating = stof(myMovies); // convert from string to float (stof)
            else if (i == 4)
            {
                timer t1, t2;
                t1.hours = stoi(myMovies.substr(0, 2));  // stoi to convert to inteager (stoi)
                t1.minutes = stoi(myMovies.substr(3, 4));
                t2.hours = stoi(myMovies.substr(8, 9));
                t2.minutes = stoi(myMovies.substr(11, 12));

                movies[movie_i].screeningInfo[0].timer = t1;
                movies[movie_i].screeningInfo[1].timer = t2;
            }
            else
            {
                i = 0;
                movie_i++;
                continue;
            }
            i++;
        }
        myData.close(); //close the file object.

    }
}

void display() {

    for (int i = 0; i < 4; i++)
    {
        cout << movies[i].title << endl;
        cout << "----------------------" << endl;
        cout << "Director : " << movies[i].director << endl;
        cout << "Actors   : " << movies[i].actors << endl;
        cout << "Rating   : " << movies[i].rating << endl;
        cout << "Show Times :- " << endl;
        cout << "Screen 1: " <<movies[i].screeningInfo[0].timer.hours << ":" << movies[i].screeningInfo[0].timer.minutes;
        cout << " - Available Capacity: " << movies[i].screeningInfo[0].theatre.capacity << endl;
        cout << "Screen 2: " <<movies[i].screeningInfo[1].timer.hours << ":" << movies[i].screeningInfo[1].timer.minutes;
        cout << " - Avaialabe Capacity: " << movies[i].screeningInfo[1].theatre.capacity << endl;
        cout << endl;

    }
    choosemovie();
}