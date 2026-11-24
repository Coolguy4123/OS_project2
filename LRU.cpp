#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

int LRU(const string& ref_str, int frameCnt) {
    list<int> lruList;
    int pageFaults = 0;

    for (int i = 0; i < ref_str.size(); i++) {
        int page = ref_str[i] - '0';
        bool fault = false;

        if (find(lruList.begin(), lruList.end(), page) != lruList.end()) { // Found the page, no page fault
            fault = false;

            lruList.remove(page);
            lruList.push_back(page);
        } else {
            fault = true;
            pageFaults++;

            if (lruList.size() == frameCnt) {
                lruList.pop_front();
            }

            lruList.push_back(page);
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
        int pf = LRU(ref, FRAME_COUNT);
        total += pf;
        cnt++;
    }

    cout << "\nAverage page faults for LRU with a frame count of "
         << FRAME_COUNT << ": "
         << static_cast<double>(total) / cnt << '\n';


    return 0;
}
