#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>

using namespace std;

class PointTracker {
    private:
        vector<string> all_uniquenames;
        unordered_set<string> participant_names;
        int size = 0;

    public:
        void header() {
            cout << "----------------------------------------\n";
            cout << "      Point Tracker Application        \n";
            cout << "----------------------------------------\n";
            cout << "This application tracks participant uniquenames against a master list.\n";
            cout << "Please ensure swe_uniquenames.txt is in the same directory and is up to date.\n";
            cout << "If you are ready to continue, please press Enter...\n";
            cin.get();
        }

        void input_uniquenames() {
            cout << "\nReading SWE uniquenames from file...\n";
            ifstream infile("swe_uniquenames.txt");
            if (!infile.is_open()) {
                cerr << "Error opening swe_uniquenames.txt\n";
                return;
            }
            string uniquename;
            while (infile >> uniquename) {
                all_uniquenames.push_back(uniquename);
            }
            infile.close();
            size = all_uniquenames.size();
            cout << "Loaded " << size << " uniquenames\n";
        }

        void participant_tracker() {
            cout << "\nPlease enter participant uniquenames (Ctrl+D when finished): \n";
            string participant_name;
            while (cin >> participant_name) {
                participant_names.insert(participant_name);
            }
        }

        bool is_participant(const string& name) {
            return participant_names.count(name) > 0;
        }

        void output_results() {
            ofstream outfile("output.txt");
            if (!outfile.is_open()) {
                cerr << "Error opening output file\n";
                return;
            }
            for (const auto& name : all_uniquenames) {
                if (is_participant(name)) {
                    outfile << "1\n";
                } else {
                    outfile << "\n";
                }
            }
            outfile.close();
            cout << "\nResults written to output.txt\n";
        }
};

int main() {
    PointTracker pt;
    pt.header();
    pt.input_uniquenames();
    pt.participant_tracker();
    pt.output_results();
    return 0;
}