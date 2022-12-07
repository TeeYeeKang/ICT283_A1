

//--------------------------------------------------------

//2. dataFile.eof() not work, will always have 1 read file issue
//3. infile use break this time round
//4. Remember to explain how you use the bst to check for duplicate filename

//--------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //convert string to numerical value
#include <iomanip> //decimal point
#include <map>
#include "Date.h"
#include "Time.h"
#include "Vector.h"
#include "WindLogInfo.h"
#include "bst.h"

using namespace std;

typedef struct
{
    Date d;
    Time t;
    WindLogInfo w;
} WindLogType;

//function & operator prototype
ostream & operator <<( ostream &os, const WindLogType & W);
istream & operator >>( istream &input, WindLogType & W);

int menu();
void controller(const Vector<WindLogType> &windlog);
void readDataFromFile(Vector<WindLogType> &windlog);
float GetAverageSpeed(const Vector<WindLogType> &windlog, int year, int month);
float GetAverageAir(const Vector<WindLogType> &windlog, int year, int month);
float GetTotalSolar(const Vector<WindLogType> &windlog, int year, int month);
void option1(const Vector<WindLogType> &windlog);
void option2(const Vector<WindLogType> &windlog);
void option3(const Vector<WindLogType> &windlog);
void option4(const Vector<WindLogType> &windlog);
int yearToFind();
int monthToFind();
bool isNumeric(string input);


int main()
{
    Vector<WindLogType> windlogVec;
    readDataFromFile(windlogVec);

    cout<<fixed<<showpoint<<setprecision(1)<<endl; //set to only one decimal point

    controller(windlogVec);

    return 0;
}

//All functions & operators

ostream & operator <<( ostream & os, const WindLogType & W)
{
    os << W.d << W.t << W.w <<endl;
    return os;
}

istream & operator >>(istream & input, WindLogType & W)
{
    input >> W.d >> W.t >> W.w;
    return input;
}

int menu()
{
    string input;
    int choice;
    bool numeric;

    do
    {
        cout << "\n------------------ Task to perform ------------------\n" << endl;
        cout << "[1]: The average wind speed and average ambient air temperature for a specified month and year" << endl;
        cout << "[2]: Average wind speed and average ambient air temperature for each month of a specified year" << endl;
        cout << "[3]: Total solar radiation in kWh/m2 for each month of a specified year" << endl;
        cout << "[4]: Output avg wind speed, avg ambient air temperature and total solar radiation for each month of year to a file" << endl;
        cout << "[5]: Exit the program " << endl;
        cout << "\nEnter the option you want to perform: ";
        cin >> input ;

        if(!isNumeric(input))
        {
            cout << "\nPlease enter a numerical value !" << endl;
            numeric = false;
        }
        else
        {
            numeric = true;
        }
    }
    while(!numeric);

    choice = atoi(input.c_str()); //convert to int
    return choice;
}

bool isNumeric(string input)
{
    bool valid = true;
    for(int idx=0; idx<input.length(); idx++)
    {
        if(!isdigit(input[idx]))
        {
            valid = false;
        }
        return valid;
    }
}

void controller(const Vector<WindLogType> &windlog)
{
    int userChoice = 0;

    do
    {
        userChoice = menu(); //get user's choice

        switch (userChoice)
        {
        case 1:
            option1(windlog);
            break;
        case 2:
            option2(windlog);
            break;
        case 3:
            option3(windlog);
            break;
        case 4:
            option4(windlog);
            break;
        case 5:
            cout<<"\nThank you bye ~"<<endl;
            break;
        default:
            printf("\nInvalid option !\n");
            break;
        }
    }
    while (userChoice != 5);
}

void readDataFromFile(Vector<WindLogType> &windlog)
{
    //working variables
    float theSpeed, theSolar, theAir;
    string name, day, month, year, hour, minute, speedInString, solarInString, airInString, dummy, fileToRead, fileName;
    bool endOfFile = false;
    int invalidFile = 0;
    string NA = "N/A";
    bool err;

    WindLogType wObject; //struct object
    binaryTreePointer<string> fileTree;

    ifstream dataFile("data/met_index.txt");

    while(!dataFile.eof())
    {
        getline(dataFile,fileToRead,'\n');
        fileName="data/"+fileToRead;

        ifstream infile(fileName);

        if(infile.is_open())
        {
            if(!fileTree.search(fileName))
            {
                fileTree.insert(fileName);
                //----------------------------------------------------------------
                infile.ignore(1000,'\n'); //skip the header line

                while(true)
                {
                    //read Date and Time
                    getline(infile, day, '/');
                    getline(infile, month, '/');
                    getline(infile, year, ' ');
                    getline(infile, hour, ':');
                    getline(infile, minute, ',');

                    //convert string to int value
                    int d = atoi(day.c_str());
                    int m = atoi(month.c_str());
                    int y = atoi(year.c_str());
                    int h = atoi(hour.c_str());
                    int mi = atoi(minute.c_str());

                    //set Date and Time objects
                    wObject.d.SetDate(d, m, y);
                    wObject.t.SetHour(h);
                    wObject.t.SetMinute(mi);

                    //read speed
                    for(int idx=0; idx<10; idx++)
                    {
                        getline(infile, speedInString, ',');
                    }

                    //read solar radiation
                    getline(infile, solarInString, ',');

                    //read unused date
                    for(int idx=0; idx<5; idx++)
                    {
                        infile.ignore(1000,',');  //skip unused data
                    }

                    getline(infile, airInString); //read air

                    if(infile.eof())  //check if reach the end of line
                    {
                        break;
                    }
                    else
                    {
                        //convert speedInString and solarInString to float
                        if(!speedInString.compare(NA)==0)
                            theSpeed = stof(speedInString.c_str());
                        else
                            theSpeed = 0;
                        if(!solarInString.compare(NA)==0)
                            theSolar = stof(solarInString.c_str());
                        else
                            theSolar = 0;
                        if(!airInString.compare(NA)==0)
                            theAir = stof (airInString.c_str());
                        else
                            theAir = 0;

                        //set speed, solar and air
                        wObject.w.SetSpeed(theSpeed);
                        wObject.w.SetSolar(theSolar);
                        wObject.w.SetAir(theAir);

                        windlog.PushBack(wObject);
                    }
                }
//----------------------------------------------------------------
            }

        }
        else
        {
            err++;
        }

        infile.close();
    }
    cout<<"Error "<<err<<endl;
    dataFile.close();
}

int yearToFind()
{
    int year;
    cout<<"Enter the year to search: ";
    cin>>year;

    return year;
}
int monthToFind()
{
    int month;
    cout<<"Enter the month to search: ";
    cin>>month;

    return month;
}

float GetAverageSpeed(const Vector<WindLogType> &windlog, int year, int month)
{
    //working variables
    float sumOfSpeed = 0;
    float speedAvg = 0;
    int counter = 0;

    for(int idx=0; idx<windlog.GetCounter(); idx++)
    {
        WindLogType w = windlog.Get(idx); //retrieve WindLogType object
        if((w.d.GetYear() == year) && (w.d.GetMonth() == month))
        {
            sumOfSpeed += w.w.GetSpeed()*3.6;
            counter++;
        }
    }

    speedAvg = sumOfSpeed/counter; //calculation of average

    return speedAvg;
}

float GetAverageAir(const Vector<WindLogType> &windlog, int year, int month)
{
    //working variables
    float sumOfAir = 0;
    float airAvg = 0;
    int counter = 0;

    for(int idx=0; idx<windlog.GetCounter(); idx++)
    {
        WindLogType w = windlog.Get(idx);
        if((w.d.GetYear() == year) && (w.d.GetMonth() == month))
        {
            sumOfAir += w.w.GetAir();
            counter++;
        }
    }

    airAvg = sumOfAir/counter;

    return airAvg;
}

float GetTotalSolar(const Vector<WindLogType> &windlog, int year, int month)
{
    //working variables
    float sumOfSolarRadiation=0;
    float hourlySolarRadiation=0;
    float finalSolarRadiation=0;
    int counter=0;

    for(int idx=0; idx<windlog.GetCounter(); idx++)
    {
        WindLogType w = windlog.Get(idx);
        if(w.d.GetYear()==year && w.d.GetMonth()==month)
        {
            if(w.w.GetSolar()>=100)
            {
                sumOfSolarRadiation+=w.w.GetSolar();
                counter++;
            }
        }
    }

    hourlySolarRadiation = sumOfSolarRadiation/6;
    finalSolarRadiation = hourlySolarRadiation/1000;

    return finalSolarRadiation;
}

void option1(const Vector<WindLogType> &windlog)
{
    //working variables
    int year = yearToFind();    //get year from user
    int month = monthToFind();  //get month from user
    float speedAvg = GetAverageSpeed(windlog, year, month);
    float airAvg = GetAverageAir(windlog, year, month);
    Date dateToDisplay;
    dateToDisplay.SetMonth(month);

    //display output
    cout<<endl;
    if((speedAvg >0) && (airAvg >0))
    {
        cout << dateToDisplay.GetMonthInString() << " " << year << ": "
             << speedAvg << " km/h, " << airAvg << " degrees C" << endl;
    }
    else
    {
        cout << dateToDisplay.GetMonthInString() << " " << year << ": No Data" << endl;
    }
}

void option2(const Vector<WindLogType> &windlog)
{
    int year = yearToFind(); //get year from user
    Date dateToDisplay;
    int month;

    cout << "\n" << year << endl;

    for(month=1; month<13; month++)
    {
        float speedAvg = GetAverageSpeed(windlog, year, month);
        float airAvg = GetAverageAir(windlog, year, month);
        dateToDisplay.SetMonth(month);

        if((speedAvg >0) && (airAvg >0))
        {
            cout << dateToDisplay.GetMonthInString() << ": " << speedAvg
                 << " km/h, " << airAvg << " degrees C" << endl;
        }
        else
        {
            cout << dateToDisplay.GetMonthInString() << ": No Data" << endl;
        }
    }
}

void option3(const Vector<WindLogType> &windlog)
{
    int year = yearToFind(); //get year from user
    Date dateToDisplay;
    int month;
    map<string, float> solarRadiationMap;

    cout << "\n" << year << endl;

    for(month=1; month<13; month++)
    {
        float solarRadiation = GetTotalSolar(windlog, year, month);
        dateToDisplay.SetMonth(month);

        if(solarRadiation>0)
        {
            cout << dateToDisplay.GetMonthInString() << ": " << solarRadiation << " kWh/m^2" << endl;
        }
        else
        {
            cout << dateToDisplay.GetMonthInString() << ": No Data" << endl;
        }
    }
}

void option4(const Vector<WindLogType> &windlog)
{
    ofstream ofile("WindTempSolar.csv");
    ofile<<fixed<<showpoint<<setprecision(1); //set to only one decimal point

    int year = yearToFind(); //get year from user
    Date dateToDisplay;
    int month;
    bool hasData = false;

    ofile << year << endl;

    for(int idx=0; idx<windlog.GetCounter(); idx++)
    {
        WindLogType w = windlog.Get(idx);
        if(w.d.GetYear()==year)
        {
            hasData = true;
        }
    }

    if(hasData)
    {
        for(month=1; month<13; month++)
        {
            float speedAvg = GetAverageSpeed(windlog, year, month);
            float airAvg = GetAverageAir(windlog, year, month);
            float solarRadiation = GetTotalSolar(windlog, year, month);
            dateToDisplay.SetMonth(month);

            if(speedAvg > 0 && airAvg > 0 && solarRadiation > 0)
            {
                ofile << dateToDisplay.GetMonthInString() << "," << speedAvg
                      << "," << airAvg << "," << solarRadiation <<endl;
            }
        }
    }
    else
    {
        ofile << "No data" << endl;
    }

    ofile.close();
    cout << "\nAll data has been successfully output to the csv file" << endl;
}


