// Name: Ramesh Chandra Soren
// Class: DBMS
// Date of Submission: July 30, 2024

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_REGIONS = 4;
const int NUM_SALESMEN = 6;
const int NUM_PRODUCTS = 8;
const int NUM_ENTRIES = 500; // Total number of sales entries

// Function to generate product prices file
void generateProductPricesFile() {
    ofstream outfile("product_prices.txt");
    if (!outfile) {
        cerr << "Error: Could not create product_prices.txt\n";
        exit(1);
    }

    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        int price = (rand() % 1000) + 100; // Generate random price between 100 and 1099
        outfile << i << " " << price << "\n";
    }
}

// Function to generate sales data file
void generateSalesDataFile() {
    ofstream outfile("sales_data.txt");
    if (!outfile) {
        cerr << "Error: Could not create sales_data.txt\n";
        exit(1);
    }

    for (int i = 0; i < NUM_ENTRIES; ++i) {
        int region = (rand() % NUM_REGIONS) + 1;
        int salesman = (rand() % NUM_SALESMEN) + 1;
        int product = (rand() % NUM_PRODUCTS);
        int unitsSold = (rand() % 100) + 1; // Generate random units sold between 1 and 100
        outfile << region << " " << salesman << " " << product << " " << unitsSold << "\n";
    }
}

// Function to read product prices from a file
void readProductPrices(vector<int>& productPrices) {
    ifstream infile("product_prices.txt");
    if (!infile) {
        cerr << "Error: Could not open product_prices.txt\n";
        exit(1);
    }

    int productCode, price;
    while (infile >> productCode >> price) {
        productPrices[productCode] = price;
    }
}

// Function to read sales data and compute total sales
void readSalesData(const vector<int>& productPrices, vector<vector<int>>& sales) {
    ifstream infile("sales_data.txt");
    if (!infile) {
        cerr << "Error: Could not open sales_data.txt\n";
        exit(1);
    }

    int region, salesman, productCode, unitsSold;
    while (infile >> region >> salesman >> productCode >> unitsSold) {
        sales[region - 1][salesman - 1] += unitsSold * productPrices[productCode];
    }
}

// Function to generate the sales report
void generateReport(const vector<vector<int>>& sales) {
    ofstream outfile("sales_report.txt");
    if (!outfile) {
        cerr << "Error: Could not open sales_report.txt\n";
        exit(1);
    }

    outfile << "ABC Company\n";

    for (int region = 0; region < NUM_REGIONS; ++region) {
        outfile << "Region " << region + 1 << "\n";
        int totalSales = 0;
        for (int salesman = 0; salesman < NUM_SALESMEN; ++salesman) {
            outfile << "Salesman " << salesman + 1 << " Rs. " << sales[region][salesman] << "/-\n";
            totalSales += sales[region][salesman];
        }
        outfile << "Total sale at Region " << region + 1 << " Rs " << totalSales << "/-\n\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Generate product prices and sales data files
    generateProductPricesFile();
    generateSalesDataFile();

    // Initialize product prices
    vector<int> productPrices(NUM_PRODUCTS, 0);
    readProductPrices(productPrices);

    // Initialize sales data
    vector<vector<int>> sales(NUM_REGIONS, vector<int>(NUM_SALESMEN, 0));
    readSalesData(productPrices, sales);

    // Generate the report
    generateReport(sales);

    cout << "Sales report generated successfully in 'sales_report.txt'\n";

    return 0;
}
