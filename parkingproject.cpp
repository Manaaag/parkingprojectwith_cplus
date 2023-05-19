#include <iostream>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;
struct node
{
    int  Vehicle_Registration_Number;
    string Driver_Name;
    string Vehicle_Make;    //jeep or other type like truck or whatever
    int Vehicle_Model;
    string Vehicle_Color;   //select only from White, Black, Red, Grey
    int Vehicle_Entry_Time;
    node* nptr;
};
node* fptr = NULL;
int i = 1;
int collected = 0;
void mainmenu();
void entry();
void exitt();
void  feecollect();
void  parkingstatistic();
void restoring();
int main()
{
    int j;
    cout << endl << "press 1 if Fisrt Time Entry if not then any key ";
    cin >> j;
    if (j == 1)
    {
        mainmenu();
    }
    else
    {
        restoring();
        mainmenu();
    }
    return 0;
}
void mainmenu()
{
    int op;
    cout << "press 1 for  Vehicle Entry" <<
        endl << " press 2  for  Vehicle Exit" <<
        endl << " press 3 for Parking Fee Collected"
        << endl << " press 4 for  Parking Statistics";
    cout << endl << "Enter Your Option:" << endl << "press 5 for exit the programme:" << endl;
    cin >> op;
    if (op == 1)
    {
        entry();
        cout << endl << "YOU ARE AGAIN RETURNED TO MAINMENU:" << endl;
        mainmenu();
    }
    else if (op == 2)
    {
        exitt();
        cout << endl << "YOU ARE AGAIN RETURNED TO MAINMENU:" << endl;
        mainmenu();
    }
    else if (op == 3)
    {
        feecollect();
        cout << endl << "YOU ARE AGAIN RETURNED TO MAINMENU:" << endl;
        mainmenu();
    }
    else if (op == 4)
    {
        parkingstatistic();
        cout << endl << "YOU ARE AGAIN RETURNED TO MAINMENU:" << endl;
        mainmenu();
    }
    else if (op == 5)
    {
        fstream file;
        file.open("Parking_data.txt", ios::app);
        if (!file)
        {
            cout << endl << "File has Not Created May be some problem." << endl;
        }
        else
        {
            node* currentptr = fptr;
            while (currentptr != NULL)
            {
                string registration_num = to_string(currentptr->Vehicle_Registration_Number);
                string entrytime = to_string(currentptr->Vehicle_Entry_Time);
                string model = to_string(currentptr->Vehicle_Model);
                file << registration_num << endl << currentptr->Driver_Name << endl << currentptr->Vehicle_Make << endl;
                file << model << endl << currentptr->Vehicle_Color << endl << entrytime << endl << endl;
                currentptr = currentptr->nptr;
            }
        }
        file.close();
        cout << endl << "Your Data Stored" << endl;
        exit(0);
    }
}
void entry()
{
    node* ptr;
    ptr = new node;
    if (fptr == NULL)
    {
        cout << endl << "Enter data for " << i << " vehicle:";
        i++;
        cout << endl << "Enter Vehicle Registration Number:";
        cin >> ptr->Vehicle_Registration_Number;
        cout << endl << "Enter Vehicle Driver Name :";
        cin >> ptr->Driver_Name;
        cout << endl << "Enter Vehicle Make:";
        cin >> ptr->Vehicle_Make;
        cout << endl << "Enter Vehicle Model:";
        cin >> ptr->Vehicle_Model;
        cout << endl << "Enter Vehicle Colour:";
        cin >> ptr->Vehicle_Color;
        cout << endl << "Vehicle Entry Time Auotu save And Time Unix" << endl;
        time_t entrytime = time(0);
        ptr->Vehicle_Entry_Time = entrytime;
        ptr->nptr = NULL;
        fptr = ptr;
    }
    else
    {
        node* currentptr = fptr;
        while (currentptr->nptr != NULL)
        {
            currentptr = currentptr->nptr;
        }
        cout << endl << "Enter data for " << i << " vehicle:";
        i++;
        cout << endl << "Enter Vehicle Registration Number:";
        cin >> ptr->Vehicle_Registration_Number;
        cout << endl << "Enter Vehicle Driver Name :";
        cin >> ptr->Driver_Name;
        cout << endl << "Enter Vehicle Make:";
        cin >> ptr->Vehicle_Make;
        cout << endl << "Enter Vehicle Model:";
        cin >> ptr->Vehicle_Model;
        cout << endl << "Enter Vehicle Colour:";
        cin >> ptr->Vehicle_Color;
        cout << endl << " Vehicle Entry Time Auto Save in System:";
        time_t entrytime = time(0);
        ptr->Vehicle_Entry_Time = entrytime;     //time in seconds
        currentptr->nptr = ptr;
        ptr->nptr = NULL;
    }
}
void exitt()
{
    node* currentptrr = fptr;
    int j = 1;
    int rnum;
    cout << endl << "Enter Vehicle Registreation Number:";
    cin >> rnum;
    while (currentptrr != NULL)
    {
        if (currentptrr->Vehicle_Registration_Number == rnum)
        {
            cout << endl << "__________Your Vehicle Has been Exit From System___________" << endl;
            if (j == 1)    /////this means that the first vehicle should be delete
            {
                fptr = fptr->nptr;
                time_t exittime = time(0);
                int timediffrence = exittime - (currentptrr->Vehicle_Entry_Time);
                if (timediffrence < 60)
                {
                    collected = collected + 50;
                    cout << endl << "50 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                else
                {
                    collected = collected + 70;
                    cout << endl << "70 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                i = i - 1;
                delete currentptrr;
                mainmenu();
            }
            else if (j > 1 && j < i)
            {
                node* currentptrr = fptr;
                node* previous = fptr;
                while (currentptrr->Vehicle_Registration_Number != rnum)
                {
                    previous = currentptrr;
                    currentptrr = currentptrr->nptr;
                }
                time_t exittime = time(0);
                int timediffrence = exittime - (currentptrr->Vehicle_Entry_Time);
                if (timediffrence < 60)
                {
                    collected = collected + 50;
                    cout << endl << "50 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                else
                {
                    collected = collected + 70;
                    cout << endl << "70 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                previous->nptr = currentptrr->nptr;
                i = i - 1;
                delete currentptrr;
                mainmenu();
            }
            else if (j == i)
            {
                node* currentptrr = fptr;
                node* previous = fptr;
                while (currentptrr->nptr != NULL)
                {
                    previous = currentptrr;
                    currentptrr = currentptrr->nptr;
                }
                time_t exittime = time(0);
                int timediffrence = exittime - (currentptrr->Vehicle_Entry_Time);
                if (timediffrence < 60)
                {
                    collected = collected + 50;
                    cout << endl << "50 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                else
                {
                    collected = collected + 70;
                    cout << endl << "70 Rupees collected from Car Registration Number:" << rnum << endl;
                    cout << endl << "Time Difference between Entry And Exit is:" << timediffrence << " seconds" << endl;
                }
                previous->nptr = NULL;
                i = i - 1;
                delete currentptrr;
                mainmenu();
            }
        }
        else
        {
            currentptrr = currentptrr->nptr;
            j++;
        }
    }
    if (currentptrr == NULL)
    {
        cout << endl << "No Registration Number Matched Try Again" << endl;
    }

}
void feecollect()
{
    cout << endl << " All VEHICLE Which Are Parked  There Fee Collection IS:" << collected << endl;
}
void  parkingstatistic()
{
    cout << endl << "Below Is All Vehicle Registration Numbers Which Are Currently Parked:" << endl;
    node* currentptr = fptr;
    while (currentptr != NULL)
    {
        cout << currentptr->Vehicle_Registration_Number << endl;
        currentptr = currentptr->nptr;
    }
}
void restoring()
{
    fstream file;
    file.open("Parking_data.txt", ios::in);
    if (!file)
    {
        cout << endl << "File does not exist or cannot be opened." << endl;
        return;
    }
    int count = 0;
    node* ptr = NULL;
    while (!file.eof())
    {
        if (ptr == NULL)
        {
            ptr = new node;
            fptr = ptr;
        }
        else
        {
            ptr->nptr = new node;
            ptr = ptr->nptr;
        }
        string line;
        getline(file, line);
        if (line.empty())  // skip empty lines
        {
            continue;
        }
        ptr->Vehicle_Registration_Number = stoi(line);
        getline(file, line);
        ptr->Driver_Name = line;
        getline(file, line);
        ptr->Vehicle_Make = line;
        getline(file, line);
        ptr->Vehicle_Model = stoi(line);
        getline(file, line);
        ptr->Vehicle_Color = line;
        getline(file, line);
        ptr->Vehicle_Entry_Time = stoi(line);
        ptr->nptr = NULL;
        count++;
    }
    file.close();
    cout << "Restored " << count << " entries from file." << endl;
}
