#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int FIFO(const string& ref_str, int frameCnt) {
    vector<int> frames;
    int nxtReplacement = 0;
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
                frames[nxtReplacement] = page;
                nxtReplacement = (nxtReplacement + 1) % frameCnt;
            }
        }

        cout << "Index: " << i << " | ";
        cout << "Page: " << page << " | Frames: [";

        for (size_t j = 0; j < frames.size(); ++j) {
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

    // Example reference string with 30 page references.
    const string referenceString = "331153501525755717511054404712";

    int totalFaults = FIFO(referenceString, FRAME_COUNT);

    cout << "\nTotal page faults for FIFO with a frame count of "<< FRAME_COUNT;
    cout << " : "<< totalFaults << '\n';

    return 0;
}