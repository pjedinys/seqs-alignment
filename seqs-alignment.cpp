#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

void ws_alg(vector<string>& seqs) {
    string a = seqs[0], b = seqs[1], a_out, b_out;
    int rows = b.length() + 1, cols = a.length() + 1, global_max = 0, global_max_i = 0, global_max_j = 0;
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    // populate the scoring matrix
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            int left = matrix[i][j - 1] - 2, top = matrix[i - 1][j] - 2;
            int diag = (a[j - 1] == b[i - 1]) ? (matrix[i - 1][j - 1] + 3) : (matrix[i - 1][j - 1] - 3);
            int max_score = max({ left, top, diag });
            if (max_score > global_max) {
                global_max = max_score;
                global_max_i = i;
                global_max_j = j;
            }
            matrix[i][j] = max(0, max_score);
        }
    }

    // print the scoring matrix
    cout << "       ";
    for (char c : a) cout << " " << c << "  ";
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        if (i > 0) cout << b[i - 1] << " ";
        else cout << "  ";
        for (int j = 0; j < cols; j++) cout << setw(3) << matrix[i][j] << " ";
        cout << "\n";
    }

    // traceback process
    while (matrix[global_max_i][global_max_j] != 0) {
        int left = (global_max_j > 0) ? matrix[global_max_i][global_max_j - 1] - 2 : -1;
        int top = (global_max_i > 0) ? matrix[global_max_i - 1][global_max_j] - 2 : -1;
        int diag = (global_max_i > 0 && global_max_j > 0) ? matrix[global_max_i - 1][global_max_j - 1] + ((a[global_max_j - 1] == b[global_max_i - 1]) ? 3 : -3) : -1;

        if (diag >= left && diag >= top) {
            a_out += a[global_max_j - 1];
            b_out += b[global_max_i - 1];
            global_max_i--; global_max_j--;
        }
        else if (left >= top) {
            a_out += a[global_max_j - 1];
            b_out += "-";
            global_max_j--;
        }
        else {
            a_out += "-";
            b_out += b[global_max_i - 1];
            global_max_i--;
        }
    }

    // alignments result
    reverse(a_out.begin(), a_out.end());
    reverse(b_out.begin(), b_out.end());
    cout << "\n" << a_out << "\n" << b_out << "\n";
}

int main() {
    // algorithm uses first two lines of sequences.txt
    vector<string> sequences;
    string line;
    ifstream MyReadFile("sequences.txt");

    while (getline(MyReadFile, line)) sequences.push_back(line);

    MyReadFile.close();
    ws_alg(sequences);
    cout << "\nPress enter to exit...";
    cin.get();
    return 0;
}
