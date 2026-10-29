#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
 
using namespace std;
 
// TEMPLATE FUNCTION
template <typename T>
void showMessage(T message) {
    cout << message << endl;
}
 
// ABSTRACT BASE CLASS
class Vehicle {
protected:
    string registrationNumber;
 
public:
    Vehicle(string reg) {
        registrationNumber = reg;
    }
 
    virtual ~Vehicle() {}
 
    string getRegistrationNumber() const {
        return registrationNumber;
    }
 
    virtual string getType() const = 0;
    virtual double calculateFee(double hours) const = 0;
 
    virtual void display(ostream& out) const {
        out << "Registration: " << registrationNumber
            << ", Type: " << getType();
    }
 
    // OPERATOR OVERLOADING
    friend ostream& operator<<(ostream& out, const Vehicle& v) {
        v.display(out);
        return out;
    }
};
 
// INHERITANCE
class Car : public Vehicle {
public:
    Car(string reg) : Vehicle(reg) {}
 
    string getType() const override {
        return "Car";
    }
 
    double calculateFee(double hours) const override {
        return hours * 50;
    }
};
 
class Bike : public Vehicle {
public:
    Bike(string reg) : Vehicle(reg) {}
 
    string getType() const override {
        return "Bike";
    }
 
    double calculateFee(double hours) const override {
        return hours * 20;
    }
};
 
class Truck : public Vehicle {
public:
    Truck(string reg) : Vehicle(reg) {}
 
    string getType() const override {
        return "Truck";
    }
 
    double calculateFee(double hours) const override {
        return hours * 100;
    }
};
 
// WAITING VEHICLE DETAILS
struct WaitingVehicle {
    string registration;
    string type;
};
 
// MAIN PARKING CLASS
class ParkingLot {
private:
    int capacity;
 
    // STL VECTOR
    vector<unique_ptr<Vehicle>> parkedVehicles;
 
    // STL QUEUE
    queue<WaitingVehicle> waitingQueue;
 
    // STL MAP
    map<string, int> parkingSlots;
 
    double totalRevenue = 0;
 
    // CREATE A VEHICLE OBJECT
    unique_ptr<Vehicle> createVehicle(string type, string reg) {
        if (type == "car" || type == "Car")
            return make_unique<Car>(reg);
 
        if (type == "bike" || type == "Bike")
            return make_unique<Bike>(reg);
 
        if (type == "truck" || type == "Truck")
            return make_unique<Truck>(reg);
 
        return nullptr;
    }
 
    int findFreeSlot() const {
        for (int slot = 1; slot <= capacity; slot++) {
            bool occupied = false;
 
            for (const auto& entry : parkingSlots) {
                if (entry.second == slot) {
                    occupied = true;
                    break;
                }
            }
 
            if (!occupied)
                return slot;
        }
 
        return -1;
    }
 
    void parkVehicle(unique_ptr<Vehicle> vehicle) {
        string reg = vehicle->getRegistrationNumber();
        int slot = findFreeSlot();
 
        if (slot == -1) {
            showMessage("No parking slot available.");
            return;
        }
 
        parkingSlots[reg] = slot;
        parkedVehicles.push_back(move(vehicle));
 
        cout << "Vehicle parked successfully in slot "
             << slot << ".\n";
    }
 
    // SAVE EXIT RECORD USING FILE STREAMS
    void saveRecord(string reg, string type,
                    int slot, double hours, double fee) {
        fstream file("parking_history.txt",
                     ios::out | ios::app);
 
        if (file.is_open()) {
            file << reg << " | " << type
                 << " | Slot " << slot
                 << " | Hours: " << hours
                 << " | Fee: Rs. " << fee << '\n';
 
            file.close();
        } else {
            cout << "Error saving parking record.\n";
        }
    }
 
public:
    // CONSTRUCTOR
    ParkingLot(int cap) {
        capacity = cap;
    }
 
    // FUNCTION OVERLOADING
    void showAvailability() const {
        cout << "Available slots: "
             << capacity - parkedVehicles.size()
             << "/" << capacity << '\n';
    }
 
    void showAvailability(string message) const {
        cout << message << ": "
             << capacity - parkedVehicles.size()
             << " slot(s)\n";
    }
 
    // PARK A VEHICLE
    void addVehicle() {
        string type, reg;
 
        cout << "Enter vehicle type (Car/Bike/Truck): ";
        cin >> type;
 
        cout << "Enter registration number: ";
        cin >> reg;
 
        if (parkingSlots.count(reg)) {
            cout << "This vehicle is already parked.\n";
            return;
        }
 
        unique_ptr<Vehicle> vehicle = createVehicle(type, reg);
 
        if (!vehicle) {
            cout << "Invalid vehicle type.\n";
            return;
        }
 
        if (parkedVehicles.size() < capacity) {
            parkVehicle(move(vehicle));
        } else {
            waitingQueue.push({reg, type});
            cout << "Parking full. Vehicle added to waiting queue.\n";
        }
    }
 
    // DISPLAY PARKED VEHICLES
    void displayVehicles() const {
        if (parkedVehicles.empty()) {
            cout << "No vehicles are currently parked.\n";
            return;
        }
 
        cout << "\n--- PARKED VEHICLES ---\n";
 
        for (const auto& vehicle : parkedVehicles) {
            cout << *vehicle
                 << ", Slot: "
                 << parkingSlots.at(
                        vehicle->getRegistrationNumber())
                 << '\n';
        }
    }
 
    // SEARCH USING MAP
    void searchVehicle() const {
        string reg;
 
        cout << "Enter registration number: ";
        cin >> reg;
 
        auto it = parkingSlots.find(reg);
 
        if (it != parkingSlots.end()) {
            cout << "Vehicle found in slot "
                 << it->second << ".\n";
        } else {
            cout << "Vehicle not found in parking area.\n";
        }
    }
 
    // VEHICLE EXIT
    void removeVehicle() {
        string reg;
 
        cout << "Enter registration number to exit: ";
        cin >> reg;
 
        auto slotIt = parkingSlots.find(reg);
 
        if (slotIt == parkingSlots.end()) {
            cout << "Vehicle not found.\n";
            return;
        }
 
        int slot = slotIt->second;
        double hours;
 
        cout << "Enter parking duration in hours: ";
        cin >> hours;
 
        if (cin.fail() || hours <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid duration.\n";
            return;
        }
 
        for (auto it = parkedVehicles.begin();
             it != parkedVehicles.end(); ++it) {
 
            if ((*it)->getRegistrationNumber() == reg) {
                string type = (*it)->getType();
                double fee = (*it)->calculateFee(hours);
 
                cout << fixed << setprecision(2);
                cout << "Vehicle type: " << type << '\n';
                cout << "Parking fee: Rs. " << fee << '\n';
 
                totalRevenue += fee;
 
                saveRecord(reg, type, slot, hours, fee);
 
                parkedVehicles.erase(it);
                parkingSlots.erase(slotIt);
                break;
            }
        }
 
        // AUTOMATICALLY PARK THE NEXT WAITING VEHICLE
        if (!waitingQueue.empty()) {
            WaitingVehicle next = waitingQueue.front();
            waitingQueue.pop();
 
            unique_ptr<Vehicle> vehicle =
                createVehicle(next.type, next.registration);
 
            if (vehicle) {
                cout << "Next waiting vehicle: "
                     << next.registration << '\n';
 
                parkVehicle(move(vehicle));
            }
        }
    }
 
    // DISPLAY WAITING QUEUE
    void displayWaitingQueue() const {
        if (waitingQueue.empty()) {
            cout << "No vehicles in waiting queue.\n";
            return;
        }
 
        queue<WaitingVehicle> temp = waitingQueue;
 
        cout << "\n--- WAITING QUEUE ---\n";
 
        while (!temp.empty()) {
            cout << temp.front().registration
                 << " (" << temp.front().type << ")\n";
            temp.pop();
        }
    }
 
    // READ FILE USING IFSTREAM
    void showHistory() const {
        ifstream file("parking_history.txt");
 
        if (!file.is_open()) {
            cout << "No parking history found yet.\n";
            return;
        }
 
        string line;
 
        cout << "\n--- PARKING HISTORY ---\n";
 
        while (getline(file, line)) {
            cout << line << '\n';
        }
 
        file.close();
    }
 
    void showRevenue() const {
        cout << fixed << setprecision(2);
        cout << "Revenue this session: Rs. "
             << totalRevenue << '\n';
    }
};
 
// MAIN FUNCTION
int main() {
    int capacity;
 
    cout << "Enter total parking slots: ";
    cin >> capacity;
 
    if (cin.fail() || capacity <= 0) {
        cout << "Invalid parking capacity.\n";
        return 1;
    }
 
    ParkingLot parking(capacity);
 
    int choice;
 
    do {
        cout << "\n===== SMART PARKING MANAGEMENT =====\n";
        cout << "1. Park a vehicle\n";
        cout << "2. Display parked vehicles\n";
        cout << "3. Search vehicle\n";
        cout << "4. Vehicle exit and fee calculation\n";
        cout << "5. Show available slots\n";
        cout << "6. Display waiting queue\n";
        cout << "7. View parking history\n";
        cout << "8. Show session revenue\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch (choice) {
            case 1:
                parking.addVehicle();
                break;
 
            case 2:
                parking.displayVehicles();
                break;
 
            case 3:
                parking.searchVehicle();
                break;
 
            case 4:
                parking.removeVehicle();
                break;
 
            case 5:
                parking.showAvailability();
                parking.showAvailability("Free spaces");
                break;
 
            case 6:
                parking.displayWaitingQueue();
                break;
 
            case 7:
                parking.showHistory();
                break;
 
            case 8:
                parking.showRevenue();
                break;
 
            case 0:
                cout << "Thank you for using the system!\n";
                break;
 
            default:
                cout << "Invalid choice. Try again.\n";
        }
 
    } while (choice != 0);
 
    return 0;
}
