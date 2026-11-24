#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int LRU(const string& ref_str, int frameCnt) {
    list<int> lruList;
    int pageFaults = 0;

    for (int i = 0; i < ref_str.size()l i++) {
        int page = ref_str[i] - '0';
        bool fault = false;

        if (find(lruList.begin(), lruList.end(), page) != lruList.end()) {
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
        
        cout << "Index: " << i << " | ";
        cout << "Page: " << page << " | Frames: [";

        int pos = 0;
        for (int framePage : lruList) {
            cout << framePage;

            if (pos + 1 < lruList.size()) {
                cout << ", ";
            }

            pos++;
        }

        cout << "] | ";
        cout << (fault ? "Page Fault" : "No Page Fault") << '\n';
    }

    return pageFaults;
}

int main() {
    const int FRAME_COUNT = 3;
    const string referenceString = "331153501525755717511054404712";

    int totalFaults = LRU(referenceString, FRAME_COUNT);

    cout << "\nTotal page faults for LRU with a frame count of "<< FRAME_COUNT;
    cout << ": " << totalFaults << '\n';

    return 0;
}
