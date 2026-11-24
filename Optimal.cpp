#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int Optimal(const string& ref_str, int frameCnt) {
    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < ref_str.length(); i++) {
        int page = ref_str[i] - '0';
        bool fault = false;

        if (find(frames.begin(), frames.end(), page) != frames.end()) { // Found the page, no page fault
            fault = false;
        } else {
            fault = true;
            pageFaults++;

            if (frames.size() < frameCnt) {
                frames.push_back(page);
            } else {
                int replaceIndex = 0;
                int farthest = -1;

                for (int f = 0; f < frames.size(); f++) {
                    int framePage = frames[f];
                    int nextUse = numeric_limits<int>::max();

                    for (int j = i + 1; j < ref_str.length();j++) {
                        if (ref_str[j] - '0' == framePage) {
                            nextUse = j;
                            break;
                        }
                    }

                    if (nextUse == numeric_limits<int>::max()) {
                        replaceIndex = f;
                        break;
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = f;
                    }
                }

                frames[replaceIndex] = page;
            }
        }
    }

    return pageFaults;
}

int main() {
    const int FRAME_COUNT = 6;

    ifstream in("TestingData.txt");
    string ref;

    int total = 0;
    int cnt = 0;

    while (in >> ref) {
        int pf = Optimal(ref, FRAME_COUNT);
        total += pf;
        cnt++;
    }

    cout << "\nAverage page faults for Optimal with a frame count of "
         << FRAME_COUNT << ": "
         << static_cast<double>(total) / cnt << '\n';

    return 0;
}
