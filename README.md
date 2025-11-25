Easy-CRM

🚀 Project Overview

This project implements a Customer Relationship Management (CRM) system developed entirely in C++17. The main goal is to provide a console application that demonstrates robust software architecture, utilizing fundamental Object-Oriented Programming (OOP) concepts and C++ best practices.

The code is organized into well-defined layers to ensure maintainability and scalability.




⚙️ Build and Requirements

Requirements

Compiler: G++ (C++17 version or newer)

Operating System: Any modern operating system (Linux, macOS, Windows/WSL).

Manual Compilation

To compile the project, use the following G++ command in the repository's root directory:

g++ -std=c++17 -o crm_app main.cpp CrmService.cpp FlatCustomerRepository.cpp Customer.cpp


Execution

After a successful compilation, you can run the console application:

./crm_app