#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;
// Fixed-size record for binary file storage
struct ApplianceRecord
{
    int applianceID;
    char applianceName[50];
    char applianceType[50];
    float powerRating;
    char status[10];
};

class Appliance
{
private:
    int applianceID;
    string applianceName;
    string applianceType;
    float powerRating;
    string status;

public:
static int applianceCount;// Default Constructor
Appliance()
{
    applianceID = 0;
    applianceName = "Unknown";
    applianceType = "Unknown";
    powerRating = 0;
    status = "OFF";
    }
    // Parameterized Constructor
Appliance(int id, string name, string type, float power, string applianceStatus)
{
  applianceID = id;
  applianceName = name;
  applianceType = type;
  powerRating = power;
  status = applianceStatus;
}
// Copy Constructor
Appliance(const Appliance &a)
{
  applianceID = a.applianceID;
  applianceName = a.applianceName;
  applianceType = a.applianceType;
  powerRating = a.powerRating;
  status = a.status;
}
// Destructor
~Appliance()
{
}

// Convert Appliance object into a fixed-size record
ApplianceRecord toRecord() const
{
  ApplianceRecord record{};
  record.applianceID = applianceID;
  strncpy(record.applianceName, applianceName.c_str(), 49);
  strncpy(record.applianceType, applianceType.c_str(), 49);
  record.powerRating = powerRating;
  strncpy(record.status, status.c_str(), 9);
return record;
}
// Load details from a fixed-size record
void loadFromRecord(const ApplianceRecord &record)
{
    applianceID = record.applianceID;
    applianceName = record.applianceName;
    applianceType = record.applianceType;
    powerRating = record.powerRating;
    status = record.status;
}
int getID()
{
    return applianceID;
}
    void setStatus(string status)
{
    this->status = status;
}
// inline function
inline float calculateEnergy(float hours)
{
    return (powerRating * hours) / 1000;
}
void input()
{
    do
{
    cout << "\nEnter Appliance ID: ";
    cin >> applianceID;

    if (applianceID <= 0)
    {
        cout << "Appliance ID must be positive.\n";
    }

} while (applianceID <= 0);

    cout << "Enter Appliance Name: ";
    cin >> applianceName;

    cout << "Enter Appliance Type: ";
    cin >> applianceType;

    do
{
    cout << "Enter Power Rating (Watts): ";
    cin >> powerRating;

    if (powerRating <= 0)
    {
        cout << "Power rating must be greater than zero.\n";
    }

} while (powerRating <= 0);


string applianceStatus;

do
{
    cout << "Enter Status (ON/OFF): ";
    cin >> applianceStatus;

    if (applianceStatus != "ON" && applianceStatus != "OFF" &&
        applianceStatus != "on" && applianceStatus != "off")
    {
        cout << "Invalid status. Enter ON or OFF.\n";
    }
} while (applianceStatus != "ON" && applianceStatus != "OFF" &&
         applianceStatus != "on" && applianceStatus != "off");

setStatus(applianceStatus);
}
// Display function
void display()
{
   cout << "\nAppliance ID: " << applianceID;
   cout << "\nAppliance Name: " << applianceName;
   cout << "\nAppliance Type: " << applianceType;
   cout << "\nPower Rating: " << powerRating << " W";
   cout << "\nStatus: " << status;
}
//Friend function declaration
friend void showApplianceDetails(Appliance a);
};
int Appliance::applianceCount = 0;
// Save appliance details in binary file
bool saveApplianceToFile(Appliance a)
{
    fstream file("appliances.dat", ios::out | ios::binary | ios::app);

    if (!file)
    {
        cout << "\nUnable to open file!";
        return false;
    }
ApplianceRecord record = a.toRecord();
file.write(reinterpret_cast<char*>(&record), sizeof(record));
if (!file)
    {
        cout << "\nError while saving appliance!";
        file.close();
        return false;
    }

file.close();
return true;
}
// Load appliance details from binary file
void loadAppliancesFromFile(Appliance appliances[], int &n)
{
    fstream file("appliances.dat", ios::in | ios::binary);

    if (!file)
    {
        return;
    }

    ApplianceRecord record;

    while (n < 5 && file.read(reinterpret_cast<char*>(&record), sizeof(record)))
    {
        appliances[n].loadFromRecord(record);
        n++;
    }

    file.close();

    Appliance::applianceCount = n;
}
// Search appliance in binary file using seekg()
bool searchApplianceInFile(int searchID)
{
    fstream file("appliances.dat", ios::in | ios::binary);

    if (!file)
    {
        cout << "\nFile not found.";
        return false;
    }

    ApplianceRecord record;
    int position = 0;

    while (true)
    {
        file.seekg(position * sizeof(ApplianceRecord), ios::beg);

        if (!file.read(reinterpret_cast<char*>(&record), sizeof(record)))
        {
            break;
        }

        if (record.applianceID == searchID)
        {
            cout << "\nAppliance Found!";
            cout << "\nAppliance ID: " << record.applianceID;
            cout << "\nAppliance Name: " << record.applianceName;
            cout << "\nAppliance Type: " << record.applianceType;
            cout << "\nPower Rating: " << record.powerRating << " W";
            cout << "\nStatus: " << record.status;

            file.close();
            return true;
        }

        position++;
    }

    file.close();
    return false;
}
// Update appliance status using seekp()
bool updateApplianceStatus(int searchID, string newStatus)
{
    fstream file("appliances.dat", ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "\nFile not found.";
        return false;
    }

    ApplianceRecord record;
    int position = 0;

    while (file.read(reinterpret_cast<char*>(&record), sizeof(record)))
    {
        if (record.applianceID == searchID)
        {
            strncpy(record.status, newStatus.c_str(), 9);

            file.seekp(position * sizeof(ApplianceRecord), ios::beg);

            file.write(reinterpret_cast<char*>(&record), sizeof(record));

            file.close();
            return true;
        }

        position++;
    }

    file.close();
    return false;
}
void showApplianceDetails(Appliance a)
{
    cout << "\nAppliance Summary Details:";
    cout << "\nAppliance ID: " << a.applianceID;
    cout << "\nAppliance Name: " << a.applianceName;
    cout << "\nPower Rating: " << a.powerRating << " W";
}

int main()
{
    Appliance a1(101, "Fan", "Cooling", 75, "ON");
    Appliance a2(a1);

a2.display();
    Appliance appliances[5];

    int n = 0;
    loadAppliancesFromFile(appliances, n);
    int choice;

    do
    {
        cout << "\n\n===== SMART HOME ENERGY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Appliance";
        cout << "\n2. Display All Appliances";
        cout << "\n3. Calculate Energy Consumption";
        cout << "\n4. Search Appliance by ID";
        cout << "\n5. Update Appliance Status";
        cout << "\n6. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                if (n >= 5)
                {
                    cout << "Maximum 5 appliances allowed.";
                    break;
                }

                cout << "\nEnter details for Appliance " << n + 1 << endl;

                appliances[n].input();

                bool duplicate = false;

                for (int j = 0; j < n; j++)
                {
                    if (appliances[n].getID() == appliances[j].getID())
                    {
                        duplicate = true;
                        break;
                    }
                }

                while (duplicate)
                {
                    cout << "\nDuplicate ID! Please enter again.\n";
                    appliances[n].input();
                    duplicate = false;
                    for (int j = 0; j < n; j++)
                    {
                        if (appliances[n].getID() == appliances[j].getID())
                        {
                            duplicate = true;
                            break;
                        }
                    }
                }
                 if (saveApplianceToFile(appliances[n]))
{
    n++;
    Appliance::applianceCount++;

    cout << "\nAppliance added successfully!";
}
else
{
    cout << "\nAppliance could not be saved!";
}
                break;
            }
            case 2:
            {
                if (n == 0)
                {
                    cout << "\nNo appliances available.";
                }
                else
                {
                    for (int i = 0; i < n; i++)
                    {
                        appliances[i].display();
                        showApplianceDetails(appliances[i]);
                        cout << endl;
                    }
                    cout << "\nTotal Appliances: "
                         << Appliance::applianceCount;
                }
                break;
            }
            case 3:
            {
                if (n == 0)
                {
                    cout << "\nPlease add an appliance first.";
                    break;
                }
                for (int i = 0; i < n; i++)
                {
                    float hours;
                    cout << "\nAppliance: " << i + 1;
                    appliances[i].display();
                    cout << "\nEnter operating hours (0-24): ";
                    cin >> hours;
                    if (hours >= 0 && hours <= 24)
                    {
                        cout << "\nEnergy Consumption: "
                             << appliances[i].calculateEnergy(hours)
                             << " kWh";
                    }
                    else
                    {
                        cout << "\nInvalid operating hours.";
                    }
                }
                break;
            }
            case 4:
{
    int searchID;
    cout << "\nEnter Appliance ID to search: ";
    cin >> searchID;
    bool found = searchApplianceInFile(searchID);
    if (!found)
    {
        cout << "\nAppliance not found.";
    }
    break;
}
            case 5:
{
    int searchID;
    string newStatus;
    cout << "\nEnter Appliance ID to update: ";
    cin >> searchID;
    cout << "Enter new Status (ON/OFF): ";
    cin >> newStatus;
    if (newStatus != "ON" && newStatus != "OFF" &&
        newStatus != "on" && newStatus != "off")
    {
        cout << "\nInvalid status!";
    }
    else if (updateApplianceStatus(searchID, newStatus))
{
    for (int i = 0; i < n; i++)
    {
        if (appliances[i].getID() == searchID)
        {
            appliances[i].setStatus(newStatus);
            break;
        }
    }
    cout << "\nAppliance status updated successfully!";
}
    else
    {
        cout << "\nAppliance not found.";
    }
    break;
}
case 6:
    cout << "\nThank you for using Smart Home Energy Management System!";
    break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }
    } while (choice != 6);

    return 0;
}

