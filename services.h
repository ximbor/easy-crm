#pragma once

#include <vector>
#include <algorithm>
#include "utils.h"

class CrmService {
private:
    vector<Customer> customers;
    int nextId;
    shared_ptr<ICustomerRepository> repository;

public:
    CrmService(shared_ptr<ICustomerRepository> repo): repository(repo), nextId(1) {
        repository->load(customers, nextId);
        cout << ">> Data loaded on startup. Auto-save is active.\n";
    }

    Customer* findCustomerById(int id) {
        for (auto& c : customers) {
            if (c.getId() == id) return &c;
        }
        return nullptr;
    }

    void addCustomer(string firstName, string lastName, string email) {
        Customer newCustomer(nextId++, firstName, lastName, email);
        customers.push_back(newCustomer);
        cout << ">> Customer added.\n";
        repository->save(customers, nextId);
    }

    void displayAll() const {
        cout << "\n--- Customer List ---\n";
        if (customers.empty()) {
            cout << ">> No customers found.\n";
            return;
        }
        for (const auto& c : customers) {
            c.printDetails();
        }
        cout << "---------------------\n";
    }

    void modifyCustomer(int id) {
        Customer* c = findCustomerById(id);
        if (!c) { cout << ">> Not found.\n"; return; }

        string input;
        cout << "\n--- Modifying Customer ID: " << id << " ---\n";
        cout << "Leave empty to keep current value.\n";
        clearBuffer();
        cout << "New First Name (" << c->getFirstName() << "): ";
        getline(cin, input);
        if (!input.empty()) c->setFirstName(input);

        cout << "New Last Name (" << c->getLastName() << "): ";
        getline(cin, input);
        if (!input.empty()) c->setLastName(input);

        cout << "New Email (" << c->getEmail() << "): ";
        getline(cin, input);
        if (!input.empty()) c->setEmail(input);

        cout << ">> Customer updated.\n";
        repository->save(customers, nextId);
    }

    void deleteCustomer(int id) {
        auto it = remove_if(customers.begin(), customers.end(),
                            [id](const Customer& c) { return c.getId() == id; });

        if (it != customers.end()) {
            customers.erase(it, customers.end());
            cout << ">> Customer deleted.\n";
            repository->save(customers, nextId);
        } else {
            cout << ">> Not found.\n";
        }
    }

    bool searchCustomer(string query) const {
        bool found = false;
        cout << "\n--- Search Results ---\n";
        for (const auto& c : customers) {
            query = toLowerString(query);
            if (toLowerString(c.getFirstName()).find(query) != string::npos ||
            toLowerString(c.getLastName()).find(query) != string::npos ||
            toLowerString(c.getEmail()).find(query) != string::npos) {
                c.printDetails();
                found = true;
            }
        }
        if (!found) cout << "No results found.\n";
        return found;
    }

    void addAppointmentToCustomer(int id) {
        Customer* c = findCustomerById(id);
        if (!c) { cout << ">> Not found.\n"; return; }

        string date, note;
        clearBuffer();

        do {
            cout << "Date (DD/MM/YYYY): ";
            getline(cin, date);
            if (isValidDateFormat(date)) {
                break;
            }
            cout << "Invalid date format. Please use DD/MM/YYYY.\n";
        } while (true);

        cout << "Note for Appointment: "; getline(cin, note);

        c->addAppointment(Appointment(date, note));
        cout << ">> Appointment added.\n";
        repository->save(customers, nextId);
    }

    void addContractToCustomer(int id) {
        Customer* c = findCustomerById(id);
        if (!c) { cout << ">> Not found.\n"; return; }

        string date, note, valStr;
        double val;
        clearBuffer();

        do {
            cout << "Date (DD/MM/YYYY): ";
            getline(cin, date);
            if (isValidDateFormat(date)) {
                break;
            }
            cout << "Invalid date format. Please use DD/MM/YYYY.\n";
        } while (true);

        cout << "Note for Contract: ";
        getline(cin, note);

        do {
            cout << "Contract Value (€): ";
            getline(cin, valStr);

            if (isValidNumericInput(valStr)) {
                val = std::stod(valStr);

                if (val > 0) {
                    break;
                }
            } else {
                cout << "Invalid input. Please enter a valid positive number.\n";
            }
        } while (true);

        c->addContract(Contract(date, note, val));
        cout << ">> Contract added successfully.\n";
        repository->save(customers, nextId);
    }

    void viewInteractions(int id) {
        Customer* customer = findCustomerById(id);
        if (!customer) { cout << ">> Not found.\n"; return; }

        cout << "\n--- Interactions for " << customer->getFirstName() << " " << customer->getLastName() << " ---\n";

        cout << "--- Appointments (" << customer->getAppointments().size() << ") ---\n";
        for (const auto& a : customer->getAppointments()) {
            a.print();
        }

        cout << "--- Contracts (" << customer->getContracts().size() << ") ---\n";
        for (const auto& k : customer->getContracts()) {
            k.print();
        }
    }
};