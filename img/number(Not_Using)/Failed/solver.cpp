#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std; 

const int SIZE_W = 48;
const int SIZE_H = 39;


vector<pair<int, int>> d = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1}
};

bool in_board(int i, int j) {
    return (0 <= i && i < SIZE_H && 0 <= j && j < SIZE_W);
}

pair<vector<pair<int, int>>, vector<pair<int, int>>> around(int i, int j, vector<vector<int>>& v, vector<vector<int>>& f) {
    vector<pair<int, int>> s, s_;

    for (const auto& D : d) {
        int ny = i + D.first;
        int nx = j + D.second;

        if (in_board(ny, nx)) {
            if (v[ny][nx] == 0) {
                s.push_back(make_pair(ny, nx));
                if (f[ny][nx]) {
                    s_.push_back(make_pair(ny, nx));
                }
            }
        }
    }

    return make_pair(s, s_);
}

vector<vector<int>> Open_F(){
	ifstream infile("./F.txt"); 
	vector<vector<int>> F; 
    string line;
    while (getline(infile, line)) {
        vector<int> row;
        istringstream iss(line);

        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        F.push_back(row);
    }
	return F; 
}

vector<vector<int>> Open_V(){
	ifstream infile("./V.txt"); 
	vector<vector<int>> V; 
    string line;
    while (getline(infile, line)) {
        vector<int> row;
        istringstream iss(line);

        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        V.push_back(row);
    }
	return V; 
}

void solve() {
	vector<vector<int>> f = Open_F();

    while (1) {
        is_arrive();
        auto v = lib::get_map();
        for (int i = 0; i < SIZE_H; ++i) {
            v = lib::get_map();
            for (int j = 0; j < SIZE_W; ++j) {
                if (v[i][j] == -1 || f[i][j]) {
                    continue;
                }
                auto [s, s_] = around(i, j, v, f);
                if (s.size() == static_cast<size_t>(v[i][j])) {
                    for (const auto& c : s) {
                        if (!f[c.first][c.second]) {
                            cout << "bomb : " << c.first << " " << c.second << endl;
                            lib::click(c.first, c.second, false);
                            f[c.first][c.second] = 1;
                        }
                    }
                } else if (s_.size() == static_cast<size_t>(v[i][j]) && v[i][j] != 0) {
                    for (const auto& c : s) {
                        cout << "safe : " << c.first << " " << c.second << endl;
                        lib::click(c.first, c.second, true);
                    }
                }
            }
        }
    }
}

solve(); 
