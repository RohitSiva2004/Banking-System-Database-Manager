# Banking System

This repository contains a simple banking system application implemented in C++ using the Oracle C++ Call Interface (OCCI) to interact with an Oracle database. The application allows you to:

- Find a customer by ID or name.
- Generate a customer report.
- Add, update, and remove customers from the database.
- View customer order details and product names.

## Structure

- **Source Code**: The main application logic is implemented in C++.
- **SQL Scripts**: The SQL queries for database operations are stored in `banking_system_queries.sql`.

## Features

- **Customer Management**: Search, add, update, and delete customer records.
- **Order Management**: View customer orders and associated product details.

## Requirements

- Oracle Database
- Oracle C++ Call Interface (OCCI)
- C++ Compiler

## Usage

1. Compile the C++ code.
2. Execute the binary and follow the menu prompts for various operations.
3. The SQL queries are defined in `banking_system_queries.sql`.

## How to Run

```sh
# Compile the code
g++ -o banking_system banking_system.cpp -locci

# Run the application
./banking_system
