#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <limits>

#include "customer.h"
#include "repositories.h"
#include "services.h"

using namespace std;

void manageCustomerDetails(CrmService& crmService, const int customerId) {

    if (!crmService.findCustomerById(customerId)) {
        cout << "Customer with ID " << customerId << " not found.\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- Customer ID: " << customerId << " ---\n";
        cout << "1. View interactions\n";
        cout << "2. Add appointment\n";
        cout << "3. Add contract\n";
        cout << "4. Delete Customer\n";
        cout << "5. Edit Customer\n";
        cout << "0. Back\n";
        cout << "Select: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: crmService.viewInteractions(customerId); break;
            case 2: crmService.addAppointmentToCustomer(customerId); break;
            case 3: crmService.addContractToCustomer(customerId); break;
            case 4: crmService.deleteCustomer(customerId); return;
            case 5: crmService.modifyCustomer(customerId); break;
            case 0: break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

void showMenu() {
    cout << "\n=== EASY CRM ===\n";
    cout << "1. Add Customer\n";
    cout << "2. View All Customers\n";
    cout << "3. Search a customer (full-text)\n";
    cout << "4. Search a customer (by id)\n";
    cout << "5. Exit\n";
    cout << "Select: ";
}

int main() {

    // Create the CrmService that embeds the business logic and handles the interaction with the underlying customers' repository:
    CrmService crmService(make_shared<FlatCustomerRepository>("customers.txt"));

    // Main loop:
    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            // Add customer:
            case 1: {
                const string firstName = readString("First Name");
                const string lastName = readString("Last Name");
                const string email = readString("E-mail");
                crmService.addCustomer(firstName, lastName, email);
                break;
            }

            // Display all the customers:
            case 2:
                crmService.displayAll();
                break;

            // Search a customer (full-text):
            case 3: {
                const string query = readString("Search customer (by first name/last name/e-mail)");
                if (crmService.searchCustomer(query)) {
                    int idToManage;
                    cout << "Enter the ID of customer to manage (0 to skip): ";
                    if (!(cin >> idToManage) || idToManage == 0) break;

                    if (cin.fail()) {
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid ID entered.\n";
                        break;
                    }
                    manageCustomerDetails(crmService, idToManage);
                }
                if (cin.good()) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // Search a customer (id):
            case 4: {
                cout << "Search customer by ID (0 to skip): ";
                int idToManage;
                if (!(cin >> idToManage) || idToManage == 0) break;

                if (cin.fail()) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID entered.\n";
                    break;
                }
                manageCustomerDetails(crmService, idToManage);
                if (cin.good()) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // Quit:
            case 5: cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}