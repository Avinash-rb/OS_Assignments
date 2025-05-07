// 8 Page replacement algorithms
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;


bool search(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}


int findPos(const vector<int>& frames, int page) {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}


int predictOptimal(const vector<int>& frames, const vector<int>& pages, int pageIndex, int n) {
    int res = -1, farthest = pageIndex;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = pageIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}


int fifoPageReplacement(const vector<int>& pages, int capacity) {
    cout << "FIFO Page Replacement Algorithm" << endl;
    int n = pages.size();
    int pageFaults = 0;
    vector<int> frames;
    queue<int> fifoQueue;
    
    for (int i = 0; i < n; i++) {
      
        if (search(frames, pages[i])) {
            cout << "Page " << pages[i] << " already in memory" << endl;
            continue;
        }
        
       
        if (frames.size() < capacity) {
            frames.push_back(pages[i]);
            fifoQueue.push(pages[i]);
            pageFaults++;
        }
        
        else {
            int pageToReplace = fifoQueue.front();
            fifoQueue.pop();
            
            int pos = findPos(frames, pageToReplace);
            frames[pos] = pages[i];
            fifoQueue.push(pages[i]);
            pageFaults++;
        }
        
      
        cout << "Frames after processing page " << pages[i] << ": ";
        for (int j = 0; j < frames.size(); j++)
            cout << frames[j] << " ";
        cout << endl;
    }
    
    return pageFaults;
}


int optimalPageReplacement(const vector<int>& pages, int capacity) {
    cout << "Optimal Page Replacement Algorithm" << endl;
    int n = pages.size();
    int pageFaults = 0;
    vector<int> frames;
    
    for (int i = 0; i < n; i++) {
       
        if (search(frames, pages[i])) {
            cout << "Page " << pages[i] << " already in memory" << endl;
            continue;
        }
        
        
        if (frames.size() < capacity) {
            frames.push_back(pages[i]);
            pageFaults++;
        }
        
        else {
            int pos = predictOptimal(frames, pages, i + 1, n);
            frames[pos] = pages[i];
            pageFaults++;
        }
        
        
        cout << "Frames after processing page " << pages[i] << ": ";
        for (int j = 0; j < frames.size(); j++)
            cout << frames[j] << " ";
        cout << endl;
    }
    
    return pageFaults;
}


int lruPageReplacement(const vector<int>& pages, int capacity) {
    cout << "LRU Page Replacement Algorithm" << endl;
    int n = pages.size();
    int pageFaults = 0;
    vector<int> frames;
    list<int> lruList;  
    unordered_map<int, list<int>::iterator> pageMap; 
    
    for (int i = 0; i < n; i++) {
        if (search(frames, pages[i])) {
            lruList.erase(pageMap[pages[i]]);
            lruList.push_front(pages[i]);
            pageMap[pages[i]] = lruList.begin();
            
            cout << "Page " << pages[i] << " already in memory" << endl;
            continue;
        }
        
        
        if (frames.size() < capacity) {
            frames.push_back(pages[i]);
            lruList.push_front(pages[i]);
            pageMap[pages[i]] = lruList.begin();
            pageFaults++;
        }
        
        else {
          
            int lruPage = lruList.back();
            lruList.pop_back();
            
           
            int pos = findPos(frames, lruPage);
            frames[pos] = pages[i];
            lruList.push_front(pages[i]);
            pageMap[pages[i]] = lruList.begin();
            pageMap.erase(lruPage);
            
            pageFaults++;
        }
        
        
        cout << "Frames after processing page " << pages[i] << ": ";
        for (int j = 0; j < frames.size(); j++)
            cout << frames[j] << " ";
        cout << endl;
    }
    
    return pageFaults;
}


int secondChancePageReplacement(const vector<int>& pages, int capacity) {
    cout << "Second Chance Page Replacement Algorithm" << endl;
    int n = pages.size();
    int pageFaults = 0;
    vector<int> frames;
    vector<int> reference_bits(capacity, 0);  
    int pointer = 0;  
    
    for (int i = 0; i < n; i++) {
    
        if (search(frames, pages[i])) {
            int pos = findPos(frames, pages[i]);
            reference_bits[pos] = 1;
            
            cout << "Page " << pages[i] << " already in memory" << endl;
            continue;
        }
        
        if (frames.size() < capacity) {
            frames.push_back(pages[i]);
            reference_bits[frames.size() - 1] = 1;  
            pageFaults++;
        }
        
        else {
            bool found = false;
            while (!found) {
                if (reference_bits[pointer] == 0) {
                    frames[pointer] = pages[i];
                    reference_bits[pointer] = 1;
                    found = true;
                } else {
                    reference_bits[pointer] = 0;
                }
                
                pointer = (pointer + 1) % capacity;
            }
            pageFaults++;
        }
        
       
        cout << "Frames after processing page " << pages[i] << ": ";
        for (int j = 0; j < frames.size(); j++)
            cout << frames[j] << " ";
        cout << endl;
        
        cout << "Reference bits: ";
        for (int j = 0; j < frames.size(); j++)
            cout << reference_bits[j] << " ";
        cout << endl;
        
        cout << "Pointer position: " << pointer << endl;
    }
    
    return pageFaults;
}

int main() {
    vector<int> pages = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int capacity = 3; 
    
    int choice;
    int pageFaults;
    
    do {
        cout << "\nChoose Page Replacement Algorithm:" << endl;
        cout << "1. FIFO (First-In-First-Out)" << endl;
        cout << "2. OPT (Optimal)" << endl;
        cout << "3. LRU (Least Recently Used)" << endl;
        cout << "4. SC (Second Chance)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                pageFaults = fifoPageReplacement(pages, capacity);
                break;
            case 2:
                pageFaults = optimalPageReplacement(pages, capacity);
                break;
            case 3:
                pageFaults = lruPageReplacement(pages, capacity);
                break;
            case 4:
                pageFaults = secondChancePageReplacement(pages, capacity);
                break;
            case 5:
                cout << "Exiting the program" << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
                continue;
        }
        
        cout << "Total Page Faults: " << pageFaults << endl;
        
    } while (choice != 5);
    
    return 0;
}
