#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int Optimal(const string& ref_str, int frameCnt) {
    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < ref_str.length(); i++) {
        int page = ref_str[i] - '0';
        bool fault = false;

        if (find(frames.begin(), frames.end(), page) != frames.end()) {
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

        cout << "Index: " << i << " | ";
        cout << "Page: " << page << " | Frames: [";

        for (int j = 0; j < frames.size(); ++j) {
            cout << frames[j];

            if (j + 1 < frames.size()) {
                cout << ", ";
            }
        }

        cout << "] | ";
        if (fault){
            cout << "Page Fault";
        } else {
            cout << "No Page Fault";
        }
        cout << '\n';
    }

    return pageFaults;
}

int main() {
    const int FRAME_COUNT = 3;
    const string referenceString = "331153501525755717511054404712";

    int totalFaults = Optimal(referenceString, FRAME_COUNT);

    cout << "\nTotal Optimal page faults: " << totalFaults << '\n';

    return 0;
}
