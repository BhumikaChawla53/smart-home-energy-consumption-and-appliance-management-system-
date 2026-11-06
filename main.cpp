#include <iostream>
#include <string>

using namespace std;

class Appliance
{
private:
    int applianceID;
    string applianceName;
    string applianceType;
    float powerRating;
    string status;

public:
static int applianceCount;

    // Constructor
    Appliance()
    {
        applianceID = 0;
        applianceName = "Unknown";
        applianceType = "Unknown";
        powerRating = 0;
        status = "OFF";
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
void showApplianceDetails(Appliance a)
{
    cout << "\nAppliance Summary Details:";
    cout << "\nAppliance ID: " << a.applianceID;
    cout << "\nAppliance Name: " << a.applianceName;
    cout << "\nPower Rating: " << a.powerRating << " W";
}

int main()
{
    Appliance appliances[5];

    int n = 0;
    int choice;

    do
    {
        cout << "\n\n===== SMART HOME ENERGY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Appliance";
        cout << "\n2. Display All Appliances";
        cout << "\n3. Calculate Energy Consumption";
        cout << "\n4. Search Appliance by ID";
        cout << "\n5. Exit";

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

                n++;
                Appliance::applianceCount++;

                cout << "\nAppliance added successfully!";
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
                bool found = false;

                cout << "\nEnter Appliance ID to search: ";
                cin >> searchID;

                for (int i = 0; i < n; i++)
                {
                    if (appliances[i].getID() == searchID)
                    {
                        appliances[i].display();
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nAppliance not found.";
                }

                break;
            }

            case 5:
                cout << "\nThank you for using Smart Home Energy Management System!";
                break;

            default:
                cout << "\nInvalid choice. Please try again.";
        }

    } while (choice != 5);

    return 0;
}

