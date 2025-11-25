#pragma once

#include <vector>
using namespace std;

/**
 * Customer appointment.
 */
class Appointment {
private:
    string date;
    string notes;
public:
    Appointment(const string &date, const string &notes) : date(date), notes(notes) {}

    string getDate() { return date;}
    string getNotes() { return notes;}

    void print() const {
        cout << "   [Appointment] Date: " << date << " | Note: " << notes << endl;
    }
};

/**
 * Customer contract.
 */
class Contract {

private:
    string date;
    string notes;
    double value;
    string currency = "€";

public:
    Contract(const string &date, const string &notes, const double value) : date(date), notes(notes), value(value) {}

    string getDate() { return date;}
    string getNotes() { return notes;}
    double getValue() { return value;}

    void print() const {
        cout << "   [Contract] Date: " << date << " | Value: " << currency << " " << value << " | Note: " << notes << endl;
    }
};

/**
 * Customer class.
 */
class Customer {

private:

    int id;
    string firstName;
    string lastName;
    string email;
    vector<Appointment> appointments;
    vector<Contract> contracts;

public:

    Customer(int _id, string _firstName, string _lastName, string _email)
        : id(_id), firstName(_firstName), lastName(_lastName), email(_email) {}

    int getId() const { return id; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }

    void setFirstName(const string& fn) { firstName = fn; }
    void setLastName(const string& ln) { lastName = ln; }
    void setEmail(const string& e) { email = e; }

    void addAppointment(const Appointment& appointment) {
        appointments.push_back(appointment);
    }
    void addContract(const Contract& contract) {
        contracts.push_back(contract);
    }

    const vector<Appointment>& getAppointments() const {
        return appointments;
    }
    const vector<Contract>& getContracts() const {
        return contracts;
    }

    void printDetails() const {
        cout << "ID: " << id << " | " << firstName << " " << lastName << " | " << email << endl;
    }
};