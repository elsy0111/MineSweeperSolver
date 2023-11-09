#include <csignal>
#include <utility>
#include <vector>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace cv; 

const int div_   = 32;
const int SIZE_W = 48;
const int SIZE_H = 39;
const int src_H  = 300; 
const int src_W  = 2000; 

void screenshot(){
	system("py screenshot.py"); 
}

pair<int, int> pos_origin() {
	screenshot();
	Mat src_    = imread("./img/src.png",    IMREAD_COLOR);
	Mat corner_ = imread("./img/corner.png", IMREAD_COLOR);

	vector<vector<vector<int>>> src(src_H, vector<vector<int>>(src_W, vector<int>(3)));
	vector<vector<vector<int>>> corner(src_H, vector<vector<int>>(src_W, vector<int>(3)));

	// Mat2Vec src
	for (int i = 0; i < src_H; ++i) {
		for (int j = 0; j < src_W; ++j) {
			Vec3b intensity = src_.at<Vec3b>(i, j);
			// BGR2Vector
			src[i][j][0] = static_cast<int>(intensity[0]);  // Red
			src[i][j][1] = static_cast<int>(intensity[1]);  // Green
			src[i][j][2] = static_cast<int>(intensity[2]);  // Blue
		}
	}
	// Mat2Vec corner
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			Vec3b intensity = corner_.at<Vec3b>(i, j);
			// BGR2Vector
			corner[i][j][0] = static_cast<int>(intensity[0]);  // Red
			corner[i][j][1] = static_cast<int>(intensity[1]);  // Green
			corner[i][j][2] = static_cast<int>(intensity[2]);  // Blue
		}
	}

	for (int i = 0; i < src_H; ++i){
		for (int j = 0; j < src_W; ++j){
			bool c = true; 
			for (int p = 0; p < 30; ++p){
				for (int q = 0; q < 30; ++q){
					for (int k = 0; k < 3; ++k){
						if (src[i + p][j + q][k] != corner[p][q][k]){
							c = false; 
							break; 
						}
					}
				}
				if (!c) break; 
			}
			if (c) return make_pair(i, j);
		}
	}
    return make_pair(-1, -1);
}
/*


pair<int, int> po = pos_origin();
int oy = po.first;
int ox = po.second; 

void click(int j, int i, bool left = true) {

    if (left) {
		SetCursorPos(ox, oy);
		mouse_event(MOUSEEVENTF_LEFTDOWN, ox, oy, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, ox, oy, 0, 0);
        cout << "dig  : " << i << " " << j << endl;
    } else {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, ox, oy, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, ox, oy, 0, 0);
        cout << "flag : " << i << " " << j << endl;
    }
}

int cell(const vector<int>& v) {
    if (v == vector<int>{0, 0, 255}) {
        return 1;
    } else if (v == vector<int>{  0, 128,   0}) {
        return 2;
    } else if (v == vector<int>{255,   0,   0}) {
        return 3;
    } else if (v == vector<int>{  0,   0, 128}) {
        return 4;
    } else if (v == vector<int>{128,   0,   0}) {
        return 5;
    } else if (v == vector<int>{192, 192, 192}) {
        return -1;
    } else if (v == vector<int>{174, 189, 223}) {
        return 0;
    } else if (v == vector<int>{  0,   0,   0}) {
        return 0;
    } else if (v == vector<int>{128,   0, 128}) {
        return 6;
    }
	cout << "NONE Cell Type" << endl; 
	exit(0); 
}

void is_arrive() {
	screenshot();
	Mat src_ = imread("./img/src.png");
	Mat dead_ = imread("./img/dead.png");

	vector<vector<vector<int>>> src(SIZE_H, vector<vector<int>>(SIZE_W, vector<int>(3)));
	vector<vector<vector<int>>> dead(SIZE_H, vector<vector<int>>(SIZE_W, vector<int>(3)));

	// Mat2Vec src
	for (int i = 0; i < SIZE_H; ++i) {
		for (int j = 0; j < SIZE_W; ++j) {
			Vec3b intensity = src_.at<Vec3b>(i, j);
			// BGR2Vector
			src[i][j][0] = static_cast<int>(intensity[0]);  // Red
			src[i][j][1] = static_cast<int>(intensity[1]);  // Green
			src[i][j][2] = static_cast<int>(intensity[2]);  // Blue
		}
	}
	// Mat2Vec dead
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			Vec3b intensity = dead_.at<Vec3b>(i, j);
			// BGR2Vector
			dead[i][j][0] = static_cast<int>(intensity[0]);  // Red
			dead[i][j][1] = static_cast<int>(intensity[1]);  // Green
			dead[i][j][2] = static_cast<int>(intensity[2]);  // Blue
		}
	}

	for (int i = 0; i < SIZE_H; ++i){
		for (int j = 0; j < SIZE_W; ++j){
			bool c = true; 
			for (int p = 0; p < 30; ++p){
				for (int q = 0; q < 30; ++q){
					if (src[i + p][j + q] != dead[p][q]){
						c = false; 
						break; 
					}
				}
				if (!c) break; 
			}
			if (c) {
				cout << "DEAD :( " << endl; 
				exit(0);
			}
		}
	}
}

*/

/*
vector<vector<int>> get_map(bool debug = false) {
	is_arrive();

	Mat src = imread("./img/src.png");
	if (src.empty()){
		cout << "Err Src Not Found" << endl;
	}

	int ox_, oy_; 

    // Rect region(ox_, oy_, SIZE_W * div_, SIZE_H * div_); 

    vector<vector<int>> res(SIZE_H, vector<int>(SIZE_W, 0));

    for (int i = 0; i < SIZE_H; ++i) {
        for (int j = 0; j < SIZE_W; ++j) {
            // Rect cellRegion(j * div_, i * div_, div_, div_); 
            // Mat cellImage = screenshot(cellRegion); 
            // res[i][j] = cell(cellImage.at<Vec3b>(16, 16)); 
        }
    }

    if (debug) {
        for (const auto& row : res) {
            for (int p : row) {
                if (p == -1) {
                    cout << " ";
                } else {
                    cout << p;
                }
            }
            cout << endl;
        }
    }

    return res;
}
*/

int main() {
	screenshot();
	/* cout << pos_origin().first << " " << pos_origin().second << endl; */ 
    return 0;
}
