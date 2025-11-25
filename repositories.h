#pragma once

#include <vector>

/**
 * Customer repository interface.
 */
class ICustomerRepository {

public:

    virtual ~ICustomerRepository() = default;
    virtual void save(const vector<Customer>& customers, int nextId) = 0;
    virtual void load(vector<Customer>& customers, int& nextId) = 0;
};

/**
 * Customer repository.
 * Saves the customers and their contracts and appointments into a txt file.
 */
class FlatCustomerRepository final : public ICustomerRepository {

private:

    const string filename;

    const signed short IDX_RECORD_TYPE = 0;
    const signed short IDX_ID = 1;
    const signed short IDX_FIRST_NAME = 2;
    const signed short IDX_LAST_NAME = 3;
    const signed short IDX_MAIL = 4;
    const signed short PARTS_COUNT = IDX_MAIL + 1;


    static vector<string> split(string s, const string &delimiter = "|") {
        vector<string> list;
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != string::npos) {
            list.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        list.push_back(s);
        return list;
    }

    static string serializeAppointment(Appointment appointment) {
        return "APP|" + appointment.getDate() + "|" + appointment.getNotes();
    }

    static string serializeContract(Contract contract) {
        return "CON|" + contract.getDate() + "|" + contract.getNotes() + "|" + to_string(contract.getValue());
    }

public:

    FlatCustomerRepository(const string &filename) : filename(filename) {}

    void save(const vector<Customer>& customers, int nextId) override {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not save the customer." << endl;
            return;
        }

        file << nextId << endl;

        for (const auto& customer : customers) {
            // C|ID|Name|Surname|Email
            file << "C|" << customer.getId() << "|" << customer.getFirstName() << "|" << customer.getLastName() << "|" << customer.getEmail() << endl;

            // Save Appointments
            for (const auto& appointment : customer.getAppointments()) {
                file << serializeAppointment(appointment) << endl;
            }

            // Save Contracts
            for (const auto& contract : customer.getContracts()) {
                file << serializeContract(contract) << endl;
            }
        }
        file.close();
    }

    void load(vector<Customer>& customers, int& nextId) override {
        ifstream file(filename);
        if (!file.is_open()) return;

        customers.clear();
        string line;

        if (getline(file,line)) {
            try {
                nextId = stoi(line);
            }
            catch (...)
                { nextId = 1; }
        }

        Customer* currentCustomer = nullptr;

        while (getline(file, line)) {
            vector<string> parts = split(line);
            if (parts.empty()) continue;

            // CORREZIONE BUG 1: Usiamo IDX_RECORD_TYPE (0) invece di IDX_ID (1)
            string type = parts[IDX_RECORD_TYPE];

            if (type == "C" && parts.size() >= PARTS_COUNT) {
                int id = stoi(parts[IDX_ID]);
                customers.emplace_back(id, parts[IDX_FIRST_NAME], parts[IDX_LAST_NAME], parts[IDX_MAIL]);
                currentCustomer = &customers.back();
            }
            else if (currentCustomer != nullptr) {
                if (type == "APP" && parts.size() >= 3) {
                    // APP|Date|Notes
                    currentCustomer->addAppointment(Appointment(parts[1], parts[2]));
                }
                else if (type == "CON" && parts.size() >= 4) {
                    // CON|Date|Notes|Value
                    try {
                        double val = stod(parts[3]);
                        currentCustomer->addContract(Contract(parts[1], parts[2], val));
                    } catch (...) {
                        cerr << "Warning: Corrupt contract value found and skipped." << endl;
                    }
                }
            }
        }
        file.close();
        cout << ">> Load complete. " << customers.size() << " customers found.\n";
    }
};