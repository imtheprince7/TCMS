#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

FILE *file;

class VehicleRecord {
private:
    VehicleRecord() = default;
    VehicleRecord(const VehicleRecord&) = delete;
    VehicleRecord& operator=(const VehicleRecord&) = delete;
    void gotoxy(int x, int y);

public:
    int vehicle_type, seater, times, fine;
    long long int phone;
    char vehicle_no[10];
    char temp_vehicle_no[10];
    char owner_name[30];
    char fuel_type[10];
    char RTO_no[15];
    char address[50];
    char violated[10];
    bool found = false;

// Implementing singleton class
     static VehicleRecord &getInstance() {
        static VehicleRecord instance;
        return instance;
    }

    void insertRecord();
    void updateRecord();
    void searchRecord();
    void deleteRecord();
    void displayRecord();

    void helpline();
    void challanDetails();
    void speedLimitDetails();
    void trafficRules();
    void trafficControlBooth();

};

void VehicleRecord::gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void VehicleRecord::insertRecord(){
    cout << "================= ADD VEHICLE RECORD =================" << endl;
    cout << "Enter vehicle number : \t";
    cin.ignore();
    cin.getline(vehicle_no, 10);

    cout << "Wheeler Type: 2/3/4 : ";
    cin >> vehicle_type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Owner name : ";
    cin.getline(owner_name, 30);

    cout << "Enter mobile number : ";
    cin >> phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter seater : ";
    cin >> seater;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Mention fuel type( CNG / PETROL) : ";
    cin.getline(fuel_type, 10);

    cout << "Enter RTO number : ";
    cin.getline(RTO_no, 15);

    cout << "Enter Address : ";
    cin.getline(address, 50);

    cout << "violated Traffic Rules (yes / no) : ";
    cin.getline(violated, 10);

    if (strcmp(violated, "yes") == 0){
        cout << "No. of Times violated : ";
        cin >> times;

        cout << "Enter amount paid : ";
        cin >> fine;
    }
    else{
        times = 0;
        fine = 0;
    }

    ofstream outfile("database.txt", ios::app | ios::binary);
    if (!outfile.is_open()){
        cout << "Error opening file." << endl;
        return;
    }
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();

    cout << "==================================================" << endl;
    cout << "vehicle record successfully added" << endl;
    cout << "==================================================" << endl;
}

void VehicleRecord::updateRecord(){

    VehicleRecord &v = getInstance();
    cout << "=============== UPDATE VEHICLE RECORD ==================" << endl;

    ifstream file("database.txt", ios::binary);
    if (!file){
        cout << "*** ERROR OPENING FILE ***" << endl;
        return;
    }

    ofstream tempFile("temp.txt", ios::binary);
    if (!tempFile){
        cout << "*** ERROR CREATING TEMPORARY FILE ***" << endl;
        file.close();
        return;
    }

    while (file.read(reinterpret_cast<char *>(&v), sizeof(v)))
    {
        if (!strcmp(v.vehicle_no, temp_vehicle_no)){
            found = true;
            cout << "\n We have found matching Vehicle Number in our database:" << endl;

            cout << "Wheeler Type: 2/3/4 : ";
            cin >> v.vehicle_type;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Owner name : ";
            cin.getline(v.owner_name, 30);

            cout << "Enter mobile number : ";
            cin >> v.phone;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter seater : ";
            cin >> v.seater;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Mention fuel type( CNG / PETROL) : ";
            cin.getline(v.fuel_type, 10);

            cout << "Enter RTO number : ";
            cin.getline(v.RTO_no, 15);

            cout << "Enter Address : ";
            cin.getline(v.address, 50);

            cout << "Violated Traffic Rules (yes / no) : ";
            cin.getline(v.violated, 10);

            if (!strcmp(v.violated, "yes")){
                cout << "No. of Times violated : ";
                cin >> v.times;

                cout << "Enter amount paid : ";
                cin >> v.fine;
            }
            else{
                v.times = 0;
                v.fine = 0;
            }

            cout << "\n ***** VEHICLE RECORD SUCCESSFULLY UPDATED *****" << endl;
        }
        tempFile.write(reinterpret_cast<char *>(&v), sizeof(v));
    }

    file.close();
    tempFile.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (!found){
        cout << "***** VEHICLE RECORD NOT FOUND *****" << endl;
    }
}

void VehicleRecord::searchRecord(){

    VehicleRecord &v = getInstance();
    cout << "================= SEARCH VEHICLE RECORD ====================" << endl;

    ifstream file("database.txt", ios::binary);
    if (!file){
        cout << "*** ERROR OPENING FILE ***" << endl;
        return;
    }

    cout << "Enter Vehicle number : ";
    cin.getline(temp_vehicle_no, 10);

    while (file.read(reinterpret_cast<char *>(&v), sizeof(v)))
    {
        if (!strcmp(v.vehicle_no, temp_vehicle_no)){
            found = true;
            cout << "Vehicle number : " << v.vehicle_no << endl;
            cout << "Vehicle type : " << v.vehicle_type << endl;
            cout << "Vehicle owner : " << v.owner_name << endl;
            cout << "Owner mobile number : " << v.phone << endl;
            cout << "Seater : " << v.seater << "-seater" << endl;
            cout << "Fuel type : " << v.fuel_type << endl;
            cout << "RTO number : " << v.RTO_no << endl;
            cout << "Address : " << v.address << endl;
            cout << "Ever violated traffic rules ? : " << v.violated << endl;
            cout << "No. of times violated : " << v.times << endl;
            cout << "Total fine paid till now : " << v.fine << endl;
            break;
        }
    }

    if (!found){
        cout << "***** VEHICLE RECORD NOT FOUND *****" << endl;
    }

    file.close();
}

void VehicleRecord::displayRecord() {
    system("cls"); // Clear the console screen before showing the record from DB

    ifstream file("database.txt", ios::binary);
    if (!file) {
        cout << "*** ERROR OPENING FILE ***" << endl;
        return;
    }

    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        cout << "***** EMPTY FILE *****" << endl;
        file.close();
        return;
    }
    file.seekg(0, ios::beg);

    cout << "\n Vehicle no    vehicle type  owner name    Mobile number   Seater   Fuel type   RTO Number         Address               Ever violated    No.of times violated   Fine paid till Now" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    int j = 2;
    while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        printf("%-15s%d-wheeler    %-15s  %-13lld %d-seater   %-11s  %-14s  %-30s %-16s  %-16d %-19d\n", vehicle_no, vehicle_type, owner_name, phone, seater, fuel_type, RTO_no, address, violated, times, fine);
        j++;
    }

    file.close();
}

void VehicleRecord:: deleteRecord(){
    
    VehicleRecord &v = getInstance();
    cout << "==================== DELETE VEHICLE RECORD ====================" << endl;

    ifstream inFile("database.txt", ios::binary);
    if (!inFile){
        cout << "*** ERROR OPENING FILE ***" << endl;
        return;
    }

    ofstream tempFile("temporary.txt", ios::binary);
    if (!tempFile){
        cout << "*** ERROR CREATING TEMPORARY FILE ***" << endl;
        inFile.close();
        return;
    }

    cout << "Enter vehicle no : ";
    cin.ignore();
    cin.getline(temp_vehicle_no, 10);

    while (inFile.read(reinterpret_cast<char*>(&v), sizeof(v)))
    {
        if (strcmp(v.vehicle_no, temp_vehicle_no) == 0){
            found = true;
        }
        else{
            tempFile.write(reinterpret_cast<char*>(&v), sizeof(v));
        }
    }
    inFile.close();
    tempFile.close();

    remove("database.txt");
    rename("temporary.txt", "database.txt");

    if (!found){
        cout << "**** RECORD NOT FOUND ****" << endl;
        return;
    }
    else{
        cout << "*** VEHICLE RECORD DELETED SUCCESSFULLY ***" << endl;
    }
}

void displayFileContents(const string& filename, const string& errorMessage) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << errorMessage << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    cout << "\n\n\n\t\t\t\t\t";
}


void VehicleRecord:: helpline() {
    displayFileContents("helplines.txt", "****** ERROR SHOWING HELPLINE NUMBERS *******");
}

void VehicleRecord:: trafficRules() {
    displayFileContents("control.txt", "****** ERROR SHOWING TRAFFIC RULES *******");
}

void VehicleRecord:: trafficControlBooth() {
    displayFileContents("control_booth.txt", "****** ERROR SHOWING CONTROL BOOTH DETAILS *******");
}

void VehicleRecord:: challanDetails() {
    displayFileContents("challan_Details.txt", "****** NO CHALLAN DETAILS DETAILS AVAILABLE IN OUR DATABASE  *******");
}

void VehicleRecord:: speedLimitDetails() {
    displayFileContents("speed_details.txt", "****** ERROR SHOWING SPEED LIMIT DETAILS *******");
}


int main(){
    int choice;
    VehicleRecord &vehicleRecord = VehicleRecord::getInstance();

    // Array_pointer for all the void return_type functions in the VehicleRecord class

    void (VehicleRecord::*vehicle_record[])() = {VehicleRecord::insertRecord, VehicleRecord::updateRecord, VehicleRecord::searchRecord, VehicleRecord::displayRecord,
                                                 VehicleRecord::deleteRecord, VehicleRecord::helpline, VehicleRecord::trafficRules, VehicleRecord::challanDetails,
                                                 VehicleRecord::speedLimitDetails, VehicleRecord::trafficControlBooth};
    do{
        cout << "=============================================\n";
        cout << "Traffic control Management System\n";
        cout << "=============================================\n";
        cout << " 1.  Add Vehicle Record \n 2.  Update Vehicle Record \n 3.  Search Vehicle Record\n";
        cout << " 4.  Display Vehicle Records\n 5.  Delete Vehicle Record \n 6.  Helpline Information\n";
        cout << " 7.  Traffic Rules\n 8.  Traffic Challan Details \n 9.  Speed Limit Details\n";
        cout << " 10. Traffic Scheduling and Management\n 11. Exit the Application\n";
        cout << "\n Enter your choice : \t";
        cin >> choice;

        if (choice >= 1 && choice <= 10){
            (vehicleRecord.*vehicle_record[choice - 1])();
            cout << "\n\n Enter any key to return to main menu : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            system("cls");
        }
        else if (choice == 11){
            cout << "Exiting...\n";
            break;
        }
        else{
            cout << "\n Invalid choice. Please enter a number between 1 and 11.\n";
        }

    } while (true);

    return 0;
}


// Implemented singleton design pattern to avoid multiple object creation for offered operations. 