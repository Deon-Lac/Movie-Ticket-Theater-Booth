/*
Name:Diego lacambacal, NSHE: 5005247606, Section: 135-1002, Assignment 10
Description: Cosmo and wanda world
Input: File name, seat wanted and continue
Output: seats, price, and prompts
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

//Structures required
//Venues
const int VENUES = 8;
//Seats
const int SEATS = 5;

//structs
struct venueType
{
    string name;
    bool available[SEATS];
    double cost[SEATS];
};

//Functions Needed
//puts in ifile data into the arrays
void populateLists(ifstream &infile, venueType v[]);
//Outputs the data
void outputShows(const venueType v[]);
//Checks to see if there are any seats available still
bool anyAvailableSeats(const venueType v[]);
//Checks if input actually exists in the venue
int validateChoice(const venueType v[], string s);
//Returns the price of seat wanted
double bookSeat(venueType v[], int venueIndex, char seatNumber);
//Checks to see if user wants to keep going
bool keepGoing(string prompt);
//Converts string to all caps
string allCaps(string str);

int main()
{
    //Input File
    ifstream iFile;
    string fileName = "";

    //Array
    venueType venue[VENUES];

    //Checker to break out of loop
    bool check = true;

    //User choice for seat
    string choice = "";

    //Character for seatnumber
    char seatNumber = ' ';

    //Sees if user wants to continue
    bool contChecker = true;

    //Total
    double totalCost = 0.0;

    //Greets user
    cout << "\nWelcome To The Grand Opening\n";

    //Do while to get to open file
    do
    {
        //Asks for filename
        cout << "Enter data file: ";
        cin >> fileName;

        //Tries to open file
        iFile.open(fileName);

        //Clears if failed
        if (!iFile.is_open())
        {
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (!iFile.is_open());

    //Puts in file data into arrays
    populateLists(iFile, venue);

    do
    {
        //Checks to see if there are seats available
        check = anyAvailableSeats(venue);

        //Breaks out if sold out
        if (check == false)
        {
            cout << "Sold Out\n";
            break;
        }
        else
        {

            //Prints out Greeting
            cout << "\nWelcome Patron, please choose a show\n"
                 << "Here are our available shows, they fill up quickly so act fast\n\n";

            //Prints out the list
            outputShows(venue);
            cout << endl;

            int foundIndex = 0;
            //Asks user for seat they want
            do
            {
                cout << "Make your selection: ";
                cin >> choice;

                //Checks choice
                foundIndex = validateChoice(venue, choice);
            } while (foundIndex == -1);

            //Prints out venue
            cout << endl << venue[foundIndex].name 
            << " is an excellent choice!\n\n";

            //Asks for seat
            double costOfOneShow = 0;
            do
            {
                //Asks user for what seat they want
                cout << "Any particular seat or do you want to go with the cheapest seat? ";

                cin >> seatNumber;

                costOfOneShow = bookSeat(venue, foundIndex, seatNumber);
            } while (costOfOneShow == 0.0);

            //Adds ticket to running total
            totalCost += costOfOneShow;

            cout << "Seat booked\n\n";

            //String for asking if the user wants to continue
            string wannaCon = "Wish to continue? (Y/N): ";

            contChecker = keepGoing(wannaCon);
        }
        
    }while (contChecker == true);

    //Prints out Total
    cout << "\nMoney made $ " << fixed 
    << setprecision(2) << totalCost << endl;
    //prints ending
    cout << "Now it\'s time to leave before Mr. Crocker finds out!\n";

    //Terminate the program
    iFile.close();
    return 0;
}
//puts in ifile data into the arrays
void populateLists(ifstream &infile, venueType v[])
{
    //Puts everything into arrays
    for (int i = 0; i < 8; i++)
    {
        infile >> v[i].name;

        for (int j = 0; j < SEATS; j++)
        {
            infile >> v[i].cost[j];

            //Sets all the seats to available
            v[i].available[j] = true;
        }
    }
}

void outputShows(const venueType v[])
{
    //prints Header
    cout << left << setw(30) << "VENUES";
    //Prints number
    for (int i = 0; i < SEATS; i++)
    {
        cout << right << setw(7) << i + 1;
    }
    cout << endl;

    for (int j = 0; j < VENUES; j++)
    {
        //Checker for if all in a row is true
        bool oneTrue = false;

        for (int k = 0; k < SEATS; k++)
        {
            //Checks to see if anything in that row is true
            if (v[j].available[k] == true)
            {
                oneTrue = true;
            }
        }

        //Prints out venue if at least one is true
        if (oneTrue == true)
        {
            //Prints name of venue
            cout << left << setw(30) << v[j].name;

            for (int l = 0; l < SEATS; l++)
            {
                //Prints out seats
                if (v[j].available[l] == true)
                {
                    cout << right << fixed << setprecision(2) 
                    << setw(7) << v[j].cost[l];
                }
                else
                {
                    cout << right << setw(7) << "X";
                }
            }
            cout << endl;
        }
    }
}

//Checks to see if there are any seats available still
bool anyAvailableSeats(const venueType v[])
{
    bool checker = false;
    for (int i = 0; i < VENUES; i++)
    {
        for (int j = 0; j < SEATS; j++)
        {
            if (v[i].available[j] == true)
            {
                checker = true;
            }
        }
    }
    //Returns false if no seat was found
    return checker;
}

//Converts to all caps to compare
string allCaps(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
int validateChoice(const venueType v[], string s)
{
    for (int i = 0; i < 8; i++)
    {
        //Checks to see if s and a venue name are the same
        if (allCaps(v[i].name) == allCaps(s))
        {
            //Checks to see if there is an available seat in the venue
            bool oneTrue = false;
            for (int j = 0; j < SEATS; j++)
            {
                //Checks to see if anything in that row is true
                if (v[i].available[j] == true)
                {
                    oneTrue = true;
                }
            }
            //Returns index if a seat is available
            if (oneTrue == true)
            {
                return i;
            }
            //Returns -1 if no seat available
            else
            {
                return -1;
            }
        }
    }
    //If nothing was found
    return -1;
}

double bookSeat(venueType v[], int venueIndex, char seatNumber)
{
    //Look to see what the cheapest seat is
    if (seatNumber == 'C' || seatNumber == 'c')
    {
        cout << "Ok looking for cheapest available seat\n";
        //Temp to return lest expensive ticket
        double temp = 100000;
        //Index for where the least expensive ticket was
        int index = 0;

        //Compares the seat values
        for (int i = 0; i < SEATS; i++)
        {
            if (v[venueIndex].cost[i] < temp 
            && v[venueIndex].available[i] == true)
            {
                temp = v[venueIndex].cost[i];
                index = i;
            }
        }
        //For setting the ticket sold to not available
        v[venueIndex].available[index] = false;

        //Returns the least expesive ticket in the venue
        return temp;
    }

    //If the character was a digit
    int column = 0;
    if (isdigit(seatNumber))
    {
        //Converts
        column = seatNumber - '0' - 1;
    }
    //If the character was anything else besides a digit c/C
    else
    {
        return 0.0;
    }

    //Checks to see if column is in bounds
    if (column >=0 && column <= 4)
    {
        if (v[venueIndex].available[column] == true)
        {
            //Takes the seat if it was available
            v[venueIndex].available[column] = false;
            return v[venueIndex].cost[column];
        }
        //Returns 0 if seat wasn't available
        else
        {
            return 0.0;
        }
        
    }
    //If out of bounds
    else
    {
        return 0.0;
    }
    
    

    //If nothing was found 
    return 0.0;
}

bool keepGoing(string prompt)
{
    //Checker for input
    char checker = ' ';

    //checks user input for validness
    do
    {
        //Prints prompt
        cout << prompt;

        cin >> checker;

        //Yes
        if (checker == 'y' || checker == 'Y')
        {
            return true;
        }
        //No
        else if (checker == 'n' || checker == 'N')
        {
            return false;
        }
        //Fails
        else if (cin.fail() || checker != 'y' || checker != 'Y' || checker == 'n' || checker == 'N')
        {
            cin.clear();
            cin.ignore(100, '\n');
            //cout << prompt;
        }

    } while (cin.fail() || checker != 'y' || checker != 'Y' || checker == 'n' || checker == 'N');

    return false;
}