# Fragrance Wizard — Fragrance Dataset Analysis System

A console-based C++ application developed to process, search, and analyze fragrance data using CSV file handling and the C++ Standard Template Library (STL).

This project was developed as part of the **CSP2104 C++ Programming** coursework at Edith Cowan University.

## Features

**1. Fragrance Search**
- Search fragrances by name using case-insensitive matching.
- Supports partial names and multiple search keywords.
- Displays matching fragrances with detailed information, including brand, country, gender, ratings, year, and fragrance notes.

**2. Oldest Fragrance Analysis**
- Identifies the oldest fragrance in the dataset.
- Excludes records with missing release years.

**3. Top 5 Fragrances by Gender**
- Separates fragrances into Men, Women, and Unisex categories.
- Ranks fragrances by rating, using rating count to break ties.
- Displays the top five fragrances in each category.

**4. Longest Fragrance Name**
- Identifies the fragrance with the longest name.
- Displays its character count and full details.

**5. Country-Based Fragrance Analysis**
- Counts fragrances associated with each country.
- Displays the top 10 and bottom 10 countries by fragrance count.
- Handles country-name comparisons without case sensitivity.

## Technologies Used

- **Language:** C++
- **Development Environment:** Microsoft Visual Studio
- **Data Format:** CSV (semicolon-delimited)
- **Libraries:** C++ Standard Template Library (STL)

## C++ Concepts Applied

- Structures (`struct`)
- Vectors (`std::vector`)
- File handling (`ifstream`)
- String processing (`stringstream`)
- Functions and parameter passing by reference
- Sorting and comparison functions
- Searching, iteration, and conditional statements
- Input validation

## Project Files

- `FragranceWizard.cpp` — Main application source code
- `CSP2104_A1DataFile_2026S2.csv` — Fragrance dataset

## How to Run

1. Download or clone this repository.
2. Open `FragranceWizard.cpp` in a C++ development environment.
3. Compile the program using a compatible C++ compiler.
4. Ensure `CSP2104_A1DataFile_2026S2.csv` is in the program's working directory.
5. Run the application and select an option from the menu.

## About the Project

This project focuses on applying fundamental C++ programming concepts to a dataset. It demonstrates how structured records can be loaded from a CSV file, stored in memory, searched, sorted, and analyzed to generate useful information.

## Author

**Adhil Ahamed**

CSP2104 — C++ Programming  
Edith Cowan University
