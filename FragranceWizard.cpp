/*
 * Fragrance Wizard
 *
 * Purpose:
 * The program loads and prases a fregrance dataset the it allow to perform
 * number of task using the fragrance informaition for the user the dataset 
 * contains informaion like purfume name, brand, country, gender, rating,
 * year, and fregrance notes.
 * 
 * The user gets a menu where thay can select:
 * 1. Search fregrance by its name
 * 2. Find the oldest fregrance
 * 3. Display the top 5 fregrance for each gender category
 * 4. Can find the fragrance with the longest name
 * 5. Display the top countries based on feagrance count
 * 6. Exit program
 * 
 * Program comes back to the main menu after completing a task
 * 
 * Author: [Adhil Ahamed] ([10739721])
 * Date: [06/09/2026]
 * 
 * Notes:
 * - The fragrance dataset use semicolons (;) to seperate fields.
 * - The first 11 fields of dataset only used.
 * - We use comma (,) for rating values as decimal seperator and is should
 *   be converted before being sorted as floating-point values
 * - Fregrance searches are case-insensitive and support substring matches.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// purfum struct this is used to hold one fragrance record
struct Parfum
{
    string url;
    string perfume;
    string brand;
    string country;
    string gender;
    float ratingValue;
    int ratingCount;
    int year;
    string top;
    string middle;
    string base;
};

// Function prototypes
void loadDataset(vector<Parfum>& Parfumerie);
void displayMenu();
void printParfum(const Parfum& parfum);
void fragranceSearch(const vector<Parfum>& Parfumerie);
void findOldest(const vector<Parfum>& Parfumerie);
void topFive(const vector<Parfum>& Parfumerie);
void tongueTwister(const vector<Parfum>& Parfumerie);
void WWFragrance(const vector<Parfum>& Parfumerie);
bool compareRating(const Parfum& first, const Parfum& second);

/*
* This runs the main part of the fragrance wizard program
* 
* Purpose:
* This creates the Parfumerie vector and loads the dataset and display
* main menu repeatly till the user get exit.
* 
* Input:
* The user enter option 1 and 6 from main menu.
* 
* Output: 
* Then displays the menu and calls the function selected by the user. 
* 
* @return int - Returns 0 when the program finishes completely.
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [06/09/2026]
*/
int main()
{
    // Create the needed Parfumerie vector
    vector<Parfum> Parfumerie;

    // Loads fragrance dataset
    loadDataset(Parfumerie);

    // If the dataset cannot be loaded stop the program 
    if (Parfumerie.empty()) {
        cout << "\nThe fragrance dataset couldnt load.\n";
        cout << "Please check the data file and try again.\n";
        return 0;
    }
    bool running = true;

    while (running) {
        displayMenu();
        string choiceInput;
        cout << "Enter your choice (1-6): ";
        getline(cin, choiceInput);

        if (choiceInput.length() != 1 ||
            choiceInput[0] < '1' ||
            choiceInput[0] > '6') {
            cout << "\nInvalid choice please enter one integer between 1 & 6.\n";
            continue;
        }

        int choice = choiceInput[0] - '0';

        switch (choice) {
        case 1:
            fragranceSearch(Parfumerie);
            break;
        case 2:
            findOldest(Parfumerie);
            break;
        case 3:
            topFive(Parfumerie);
            break;
        case 4:
            tongueTwister(Parfumerie);
            break;
        case 5:
            WWFragrance(Parfumerie);
            break;
        case 6:
            cout << "\nThanks for using Fragrance Wizard.\n";
            cout << "Goodbye!\n";
            running = false;
            break;

        default:
            cout << "\nInvalid choice please enter a number between 1 & 6.\n";
        }
    }

    return 0;
}

/**
* Loads and parses the fragrance dataset to the Parfumerie vector.
* 
* Purpose:
* This open fregrance dataset and gose to each record then store the first
* 11 fields in the perfum structure the semicolan chracter we used for 
* field seperator.
* 
* Input:
* Parfumerie - Reference to the vector where fragrance records are stored.
*
* Output:
* The Parfumerie vector is filled with fragrance records.
*
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [06/09/2026]
*/
void loadDataset(vector<Parfum>& Parfumerie) {
    Parfumerie.clear();

    ifstream file("CSP2104_A1DataFile_2026S2.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open the fragrance dataset.\n";
        return;
    }
    cout << "Loading fragrance dataset...\n";

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        Parfum parfum;
        string ratingValue;
        string ratingCount;
        string year;

        // Read the first 11 fields using semicolon as the separator
        getline(ss, parfum.url, ';');
        getline(ss, parfum.perfume, ';');
        getline(ss, parfum.brand, ';');
        getline(ss, parfum.country, ';');
        getline(ss, parfum.gender, ';');
        getline(ss, ratingValue, ';');
        getline(ss, ratingCount, ';');
        getline(ss, year, ';');
        getline(ss, parfum.top, ';');
        getline(ss, parfum.middle, ';');
        getline(ss, parfum.base, ';');

        // Change rating comma into a decimal point
        for (int i = 0; i < ratingValue.length(); i++) {
            if (ratingValue[i] == ',') {
                ratingValue[i] = '.';
            }
        }

        // Convert numeric strings to numeric variables
        parfum.ratingValue = stof(ratingValue);
        parfum.ratingCount = stoi(ratingCount);

        // Some fragrance records havent a year
        if (year.empty()) {
            parfum.year = 0;
        }
        else
        {
            parfum.year = stoi(year);
        }

        // Add the completed fragrance to Parfumerie
        Parfumerie.push_back(parfum);
    }
    file.close();
    cout << "Dataset loaded successfully.\n";
    cout << Parfumerie.size() << " fragrance records loaded.\n";
}
/**
* Display the main menu for the user
* 
* Purpose:
* Display all available fragrance wizard in a nice user-friendly menu
* 
* Input:
* none
* 
* Output:
* Prints the main menu
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [07/09/2026]
*/
void displayMenu() {
    cout << "\n============================================\n";
    cout << "             Main Menu\n";
    cout << "============================================\n";
    cout << "1. Search for a Fragrance\n";
    cout << "2. Find the Oldest Fragrance\n";
    cout << "3. Display Top 5 Fragrances by gender\n";
    cout << "4. Find the Longest Fragrance Name\n";
    cout << "5. Display top fragrance countries\n";
    cout << "6. Exit\n";
    cout << "============================================\n";
}

/**
* Display all stored information for one fragrance.
* 
* purpose:
* Gives one reusable function for displaying fragrance imformation.
* This stops the same output code from being repeated in different tasks.
* 
* Input:
* Fragrance A referance to the parfum object to be displayd.
* 
* Output:
* Show the fregrance details in console.
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [07/09/2026]
*/
void printParfum(const Parfum& parfum) {
    cout << "--------------------------------------------\n";
    cout << "Perfume:      " << parfum.perfume << "\n";
    cout << "Brand:        " << parfum.brand << "\n";
    cout << "Country:      " << parfum.country << "\n";
    cout << "Gender:       " << parfum.gender << "\n";
    cout << fixed << setprecision(2);
    cout << "Rating:       " << parfum.ratingValue << " / 5\n";
    cout << "Rating Count: " << parfum.ratingCount << "\n";
    if (parfum.year == 0) {
        cout << "Year:         Unknown\n";
    }
    else
    {
        cout << "Year:         " << parfum.year << "\n";
    }
    cout << "Top Notes:    " << parfum.top << "\n";
    cout << "Middle Notes: " << parfum.middle << "\n";
    cout << "Base Notes:   " << parfum.base << "\n";
    cout << "URL:          " << parfum.url << "\n";
    cout << "--------------------------------------------\n";
}

/**
* Search fragrance using the name enterd by the user.
* 
* Purpose:
* Allow the user to enter the start of perfum name or full name and all
* perfumes containing the search term are stored in seperate vector and 
* displayed.
* 
* Input:
* Parfumerie vector have all fregrance records.
* 
* Output:
* Shows the matching fragrance and the details for each match.
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [08/09/2026]
*/
void fragranceSearch(const vector<Parfum>& Parfumerie) {
    if (Parfumerie.empty()) {
        cout << "Error fragrance dataset empty\n";
        return;
    }

    string searchTerm;
    cout << "Enter fragrance name to search: ";
    getline(cin, searchTerm);
    vector<string> searchWords;
    string word;
    stringstream searchStream(searchTerm);

    while (searchStream >> word) {
        // Convert each search word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        searchWords.push_back(word);
    }

    // Make sure the user entered even one word
    if (searchWords.empty()) {
        cout << "Please enter a fragrance name.\n";
        return;
    }
    vector<Parfum> matches;

    for (const Parfum& parfum : Parfumerie) {
        string lowerName = parfum.perfume;

        // Convert perfume name to lowercase
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        bool allWordsFound = true;

        // Check every search word against the perfume name
        for (const string& searchWord : searchWords) {
            if (lowerName.find(searchWord) == string::npos) {
                allWordsFound = false;
                break;
            }
        }

        if (allWordsFound) {
            matches.push_back(parfum);
        }
    }

    if (matches.empty()) {
        cout << "No matching fragrances found.\n";
    }
    else 
    {
        cout << "\n"
            << matches.size()
            << " matching fragrance(s) found out of "
            << Parfumerie.size()
            << " fragrances.\n\n";

        for (const Parfum& parfum : matches) {
            printParfum(parfum);
            cout << "\n";
        }
    }
}
/**
* Finds the oldest fragrance from the dataset and display.
* 
* Purpose:
* Search every fragrance records and find the fragrance with the smallest
* year value.
* 
* Input:
* Parfumerie vector have all fregrance records.
* 
* Output:
* Display the details of the oldest fragrance.
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [08/09/2026]
*/
void findOldest(const vector<Parfum>& Parfumerie) {
    int oldestIndex = -1;
    for (int i = 0; i < Parfumerie.size(); i++) {
        // Ignore records where the year is missing
        if (Parfumerie[i].year == 0) {
            continue;
        }
        if (oldestIndex == -1 ||
            Parfumerie[i].year < Parfumerie[oldestIndex].year) {
            oldestIndex = i;
        }
    }

    cout << "\n=== Oldest Fragrance ===\n";

    if (oldestIndex == -1) {
        cout << "No valid fragrance year was found.\n";
        return;
    }
    cout << "The oldest fragrance in the dataset is:\n\n";
    printParfum(Parfumerie[oldestIndex]);
}
/**
* Compares two fragrance from the rating.
* 
* Purpose:
* This is used when soring fragrance from higest rate and low rate.
* When two fragrance have the same rate value fragrance wiche has the 
* larger rate count it is placed first.
* 
* Input:
* First fragrance being compared.
* Second fragrance being compared.
* 
* Output:
* This shows which fragrance should come first.
* 
* @return bool - True when first should appear before second.
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [09/09/2026]
*/
bool compareRating(const Parfum& first, const Parfum& second) {
    if (first.ratingValue == second.ratingValue) {
        return first.ratingCount > second.ratingCount;
    }
    return first.ratingValue > second.ratingValue;
}
/**
* Display the top 5 fragrance for men, women and unisex
* 
* Purpose:
* Should seperate fragrance by men, women and unisex sorts each category
* by rating value from higest and lowest then display up to 5 fragrance from 
* each category.
* 
* If there is lower than 5 fragrance exist in a catogory every available 
* fragrance will be display in that category.
* 
* Input:
* Parfumerie vector containing all loaded fragrance record.
* 
* Output:
* Display till to 5 top rated fragrance to men, women and unisex.
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [09/09/2026]
*/
void topFive(const vector<Parfum>& Parfumerie) {
    vector<Parfum> men;
    vector<Parfum> women;
    vector<Parfum> unisex;

    // Separate fragrances to gender categories
    for (int i = 0; i < Parfumerie.size(); i++) {
        string currentGender = Parfumerie[i].gender;

        // Make gender to lowercase before compare
        transform(currentGender.begin(), currentGender.end(), currentGender.begin(), ::tolower);

        if (currentGender == "men") {
            men.push_back(Parfumerie[i]);
        }
        else if (currentGender == "women") {
            women.push_back(Parfumerie[i]);
        }
        else if (currentGender == "unisex") {
            unisex.push_back(Parfumerie[i]);
        }
    }

    // Sort each category from high rate to low
    sort(men.begin(), men.end(), compareRating);
    sort(women.begin(), women.end(), compareRating);
    sort(unisex.begin(), unisex.end(), compareRating);

    int amount;

    cout << "\n--------------- MEN -------------------------\n";

    amount = 5;

    if (men.size() < 5) {
        amount = men.size();
    }
    for (int i = 0; i < amount; i++) {
        cout << "\nRank " << i + 1 << "\n";
        printParfum(men[i]);
    }
    
    cout << "\n--------------- WOMEN -----------------------\n";
    
    amount = 5;

    if (women.size() < 5) {
        amount = women.size();
    }
    for (int i = 0; i < amount; i++) {
        cout << "\nRank " << i + 1 << "\n";
        printParfum(women[i]);
    }
    cout << "\n--------------- UNISEX ----------------------\n";

    amount = 5;

    if (unisex.size() < 5) {
        amount = unisex.size();
    }
    for (int i = 0; i < amount; i++) {
        cout << "\nRank " << i + 1 << "\n";
        printParfum(unisex[i]);
    }
}
/**
* Finds the fragrance from the longest perfume name.
* 
* Purpose:
* Compares the length from every perfume name in dataset then 
* identifies the perfume has largest number of characters.
* 
* Input:
* Parfumerie vector containing all loaded fragrance record.
* 
* Output:
* Display the longest perfume name, character length and its
* fragrance details. 
* 
* @return None
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [10/09/2026]
*/
void tongueTwister(const vector<Parfum>& Parfumerie) {
    if (Parfumerie.empty()) {
        cout << "No fragrance information is available.\n";
        return;
    }

    int longestIndex = 0;

    for (int i = 1; i < Parfumerie.size(); i++) {
        if (Parfumerie[i].perfume.length() >
            Parfumerie[longestIndex].perfume.length())
        {
            longestIndex = i;
        }
    }

    cout << "\n=== Tongue Twister ===\n";
    cout << "The longest fragrance name:\n";
    cout << Parfumerie[longestIndex].perfume << "\n";
    cout << "Name length: "
        << Parfumerie[longestIndex].perfume.length()
        << " characters\n";

    printParfum(Parfumerie[longestIndex]);
}
/**
* Display the countries that produce the large number of fragrance.
* 
* Purpose:
* Counts the number of individual perfumes associated with each
* country sorts the counrty that has the high count to low count
* and display the top 10 countries
* 
* If it is less than 10 different countries exiist in dataset only
* available countries displayed.
* 
* Input:
* Parfumerie vector containing all loaded fragrance record.
* 
* Output:
* Displays country rankings and individual perfume counts.
* 
* @return none
* 
* Author: [Adhil Ahamed] ([10739721])
* Date: [10/09/2026]
*/
void WWFragrance(const vector<Parfum>& Parfumerie) {
    if (Parfumerie.empty()) {
        cout << "Error fragrance dataset empty\n";
        return;
    }
    vector<string> countries;
    vector<int> countryCount;

    for (const Parfum& parfum : Parfumerie) {
        bool found = false;

        for (int i = 0; i < countries.size(); i++) {
            string lowerCountry1 = countries[i];
            string lowerCountry2 = parfum.country;
            transform(lowerCountry1.begin(), lowerCountry1.end(), lowerCountry1.begin(), ::tolower);
            transform(lowerCountry2.begin(), lowerCountry2.end(), lowerCountry2.begin(), ::tolower);

            if (lowerCountry1 == lowerCountry2) {
                countryCount[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            countries.push_back(parfum.country);
            countryCount.push_back(1);
        }
    }

    // Sort countries from high count to low count
    for (int i = 0; i < countryCount.size(); i++) {
        for (int j = i + 1; j < countryCount.size(); j++) {
            if (countryCount[j] > countryCount[i]) {
                int tempCount = countryCount[i];
                countryCount[i] = countryCount[j];
                countryCount[j] = tempCount;
                string tempCountry = countries[i];
                countries[i] = countries[j];
                countries[j] = tempCountry;
            }
        }
    }

    int amount = 10;

    // If less than 10 countries exist, display all available countries
    if (countries.size() < 10) {
        amount = countries.size();
    }

    cout << "\n=== Top Countries ===\n";

    for (int i = 0; i < amount; i++) {
        cout << i + 1
            << ". "
            << countries[i]
            << " - "
            << countryCount[i]
            << " perfumes\n";
    }

    cout << "\n=== Bottom Countries ===\n";

    int rank = 1;

    for (int i = countries.size() - 1;
        i >= 0 && rank <= amount;
        i--)
    {
        cout << rank
            << ". "
            << countries[i]
            << " - "
            << countryCount[i]
            << " perfumes\n";

        rank++;
    }
}