# 🚗 Smart Parking Management System in C++

A **console-based Smart Parking Management System** developed using C++ and Object-Oriented Programming (OOP). The project manages vehicle parking, assigns parking slots, maintains a waiting queue, calculates parking fees, and stores parking history using file handling.

## 📌 Project Overview

Managing a parking lot manually can be time-consuming, especially when handling multiple vehicle types and limited parking spaces.

This project provides a simple solution by automating the basic operations of a parking lot, including vehicle entry, slot allocation, vehicle exit, fee calculation, and waiting queue management.

## ✨ Features

- **Vehicle Management:** Supports cars, bikes, and trucks.
- **Automatic Slot Allocation:** Assigns the first available parking slot.
- **Vehicle Search:** Finds parked vehicles using their registration numbers.
- **Waiting Queue:** Adds vehicles to a FIFO queue when the parking lot is full.
- **Automatic Parking:** Parks the next waiting vehicle when a slot becomes available.
- **Parking Fee Calculation:** Calculates fees according to vehicle type and parking duration.
- **Parking History:** Saves vehicle exit records in a text file.
- **Revenue Tracking:** Displays the total parking fees collected during the current session.
- **Parking Availability:** Displays the number of available parking spaces.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Concepts:** Object-Oriented Programming (OOP)
- **STL Containers:** Vector, Queue, Map
- **File Handling:** `ifstream`, `fstream`
- **Memory Management:** `unique_ptr`
- **Other Concepts:** Inheritance, Abstraction, Polymorphism, Function Overloading, Operator Overloading, and Templates

## 🧠 OOP Concepts Implemented

| Concept | Implementation |
|---|---|
| Classes and Objects | `Vehicle`, `Car`, `Bike`, `Truck`, and `ParkingLot` |
| Encapsulation | Vehicle registration data is protected within the class hierarchy. |
| Abstraction | `Vehicle` is an abstract base class with pure virtual functions. |
| Inheritance | `Car`, `Bike`, and `Truck` inherit from `Vehicle`. |
| Polymorphism | Each vehicle type implements its own fee calculation. |
| Function Overloading | Two versions of `showAvailability()` are provided. |
| Operator Overloading | `operator<<` displays vehicle information. |
| Templates | `showMessage()` is a template function. |
| Constructors | Initialize vehicle and parking lot objects. |

## 💰 Parking Fee Structure

The parking fee is calculated according to the vehicle type and the number of parking hours.

| Vehicle Type | Fee Per Hour |
|---|---:|
| Car | ₹50 |
| Bike | ₹20 |
| Truck | ₹100 |

**Formula:**

`Parking Fee = Parking Duration × Hourly Rate`

For example, parking a car for 3 hours costs ₹150.

## 📂 Project Structure

```text
Smart-Parking-Management/
│
├── parking.cpp
├── parking_history.txt   # Created/appended when records are saved
└── README.md
```

The `parking_history.txt` file is created or updated when a vehicle exits and its parking record is saved successfully.


## 🖥️ Available Operations

When you run the program, the following menu is displayed:

1. Park a vehicle
2. Display parked vehicles
3. Search vehicle
4. Vehicle exit and fee calculation
5. Show available slots
6. Display waiting queue
7. View parking history
8. Show session revenue
0. Exit

Select an option by entering its corresponding number.

## 📚 Learning Outcomes

- Gained practical experience implementing OOP concepts in C++.
- Learned to use STL containers for managing parking data and waiting vehicles.
- Implemented file handling to maintain parking exit records.
- Practiced object-oriented design through a real-world management application.

## 🔮 Future Improvements

- Store active parking details permanently across program restarts.
- Add an improved graphical user interface.
- Generate daily and monthly revenue reports.
- Add date and time-based parking records.
- Improve input validation and duplicate registration handling.

## 👨‍💻 Author

**Hanan**

BCA (Honours) — Data Science

## 📄 License

This project was developed for educational and academic purposes.
