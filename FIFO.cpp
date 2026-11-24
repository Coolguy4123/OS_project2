#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int FIFO(const string& ref_str, int frameCnt) {
    vector<int> frames;
    int nxtReplacement = 0;
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
                frames[nxtReplacement] = page;
                nxtReplacement = (nxtReplacement + 1) % frameCnt;
            }
        }
    }

    return pageFaults;
}

int main() {
    const int FRAME_COUNT = 3;

    ifstream in("TestingData.txt");
    string ref;

    int total = 0;
    int cnt = 0;

    while (in >> ref) {
        int pf = FIFO(ref, FRAME_COUNT);
        total += pf;
        cnt++;
    }

    cout << "\nAverage page faults for FIFO with a frame count of "
         << FRAME_COUNT << ": "
         << static_cast<double>(total) / cnt << '\n';


    return 0;
}