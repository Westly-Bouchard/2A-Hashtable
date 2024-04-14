//
// Created by Westly Bouchard on 3/25/24.
//

#include <fstream>
#include <iostream>
#include <string>

#include "hashtable.h"
#include "hash_functions.h"
#include "random220.h"

// Number of words in `dictionary.txt`
#define W 172'823

struct point {
    size_t tableSize;
    double comparisonsOverTests;
};

ostream& operator<<(ostream& os, const point& pt) {
    os << pt.tableSize << "," << pt.comparisonsOverTests << endl;
    return os;
}

point* make_point(const size_t tabS, const double compTests) {
    auto* temp = new point;
    temp->tableSize = tabS;
    temp->comparisonsOverTests = compTests;

    return temp;
}

template <typename T>
point* experiment(int M, vector<string>& dictionary);

int main() {
    // // You can use this main() to run your own analysis or testing code.
    // cout << "If you are seeing this, you have successfully run main!" << endl;
    //
    // // ==================================================================
    // // The code below this point is relevant for the analysis part of the
    // // hashtable project.  You do not need it for the programming part.
    // // ==================================================================
    //
    // // The code below illustrates how to use the provided hash function
    // // "functional" objects, and lets you see the different hash values
    // // produced by each.
    // hash0 h0;
    // hash1 h1;
    // hash2 h2;
    // hash3 h3;
    // hash4 h4;
    //
    // string s("Hello");
    // cout << h0(s) << endl;
    // cout << h1(s) << endl;
    // cout << h2(s) << endl;
    // cout << h3(s) << endl;
    // cout << h4(s) << endl;

    //
    // // Here's how you create a hashtable to use a particular hash function:
    // hashtable<string, hash1> ht;
    // ht.insert(s);

    seed_now();

    ifstream dict("dictionary.txt");

    vector<string> dictionary;

    string word;
    while (dict >> word) {
        dictionary.push_back(word);
    }

    dict.close();

    // Get name of output file from user
    string outFile;
    cout << "Name of output file: ";
    cin >> outFile;

    // Get number of data points per series
    int seriesSize;
    cout << "Number of points per series: ";
    cin >> seriesSize;

    // Create and open output file for writing
    ofstream out(outFile + ".csv");

    /**
     * CSV STRUCTURE:
     * Name of Series
     * x,y
     * x,y
     * ...
     * x,y
     * END
     * Name of Next Series
     * ...
     */

    for(int i = 0; i < 5; i++) {
        // Series header / title
        out << "hash" + to_string(i) << endl;
        cout << "hash" + to_string(i) << endl;

        for (int j = 0; j < seriesSize; j++) {
            point* result = nullptr;
            switch (i) {
                case 0: result = experiment<hash0>(equalikely(1000, W/2), dictionary); break;
                case 1: result = experiment<hash1>(equalikely(1000, W/2), dictionary); break;
                case 2: result = experiment<hash2>(equalikely(1000, W/2), dictionary); break;
                case 3: result = experiment<hash3>(equalikely(1000, W/2), dictionary); break;
                case 4: result = experiment<hash4>(equalikely(1000, W/2), dictionary); break;
                default: break;
            }

            if (result != nullptr) {
                cout << *result;
                out << *result;

                delete result;
            }
        }

        out << "END" << endl;
        cout << endl << endl << endl;

    }
}

template <typename T>
point* experiment(const int M, vector<string>& dictionary) {

    // Hash table used for experimentation
    hashtable<string, T> table;

    // List of words that are randomly sampled for testing
    vector<string> words;

    // Bernoulli probability of appearance
    const double p = (2.0 * M) / W;

    for (const auto& word : dictionary) {
        // Should we use this word in the experiment?
        if (bernoulli(p)) {
            // Save string for testing
            words.push_back(word);

            // Should it go into the table
            if (bernoulli(0.5)) {
                table.insert(word);
            }
        }
    }

    // Now test and find average number of comparisons for lookup
    double tests(0), comparisons(0);

    // For every word in the experiment
    for (const auto& word : words) {
        // Should we use it for testing?
        if (bernoulli(1000.0 / static_cast<double>(words.size()))) {
            tests++;
            comparisons += table.count_comparisons(word);
        }
    }

    // Data-point form following experiment will be in the form of (table.size(), comparisons / tests)
    return make_point(table.size(), comparisons / tests);
}