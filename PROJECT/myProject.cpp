#include<bits/stdc++.h>
using namespace std;

class Bankers {
public:
    int process;
    int resource;
    vector<int> resourceInstance;
    vector<int> possessed;
    vector<int> available;
    vector<int> work;
    vector<bool> finish;

    vector<vector<int>> Maximum;
    vector<vector<int>> allocated;
    vector<vector<int>> need;

    vector<string>list;

    Bankers() {
        int p, r;
        cout << "Enter the process numbers:" << "\n";
        cin >> p;
        process = p;
        cout << "Enter the resource numbers:" << "\n";
        cin >> r;
        resource = r;

        for (int i = 0; i < r; i++) {
            cout << "How many resource instances available for resource " << i << "\n";
            int a;
            cin >> a;
            resourceInstance.push_back(a);
        }
        cout << "\n";
        available.resize(resource);
        possessed.resize(resource);
        work.resize(resource);
        finish.resize(process);

        Maximum.resize(process, vector<int>(resource));
        allocated.resize(process, vector<int>(resource));
        need.resize(process, vector<int>(resource));
        list.resize(process);
    }

    void calcNeed() {
        for (int i = 0; i < process; i++) {
            for (int j = 0; j < resource; j++) {
                need[i][j] = Maximum[i][j] - allocated[i][j];
            }
        }
    }

    void allocateResource() {
        cout << "Allocated Resources:\n";
        for (int i = 0; i < process; i++) {
            cout << "Process " << i << ":\n";
            for (int j = 0; j < resource; j++) {
                int num;
                cin >> num;
                allocated[i][j] = num;
            }
        }
    }
    
    void Read() {
        cout << "Enter Maximum Resource Needed: \n";
        cout << "\n";
        for (int i = 0; i < process; i++) {
            cout << "Process " << i << ":\n";
            for (int j = 0; j < resource; j++) {
                int num;
                cin >> num;
                Maximum[i][j] = num;
            }
        }
        cout << "\n";
        allocateResource();
        cout << "\n";
        fill(possessed.begin(), possessed.end(), 0);
        fill(available.begin(), available.end(), 0);

        for (int i = 0; i < resource; i++) {
            int sum = 0;
            for (int j = 0; j < process; j++) {
                sum += allocated[j][i];
            }
            possessed[i] = sum;
        }

        for (int i = 0; i < resource; i++) {
            available[i] = resourceInstance[i] - possessed[i];
        }

        fill(finish.begin(), finish.end(), false);
        for (int i = 0; i < resource; i++) {
            work[i] = available[i];
        }

        calcNeed();
    }


    void CheckSafeState() {
        queue<int> q;
        for (int i = 0; i < process; i++) q.push(i);
        int index = q.front();
        int Current = 0;
        vector<int> safeSequence;

        while (!q.empty()) {
            if (!finish[index] && CheckAllocation(index)) {
                for (int i = 0; i < resource; i++) {
                    work[i] += allocated[index][i];
                }

                finish[index] = true;
                safeSequence.push_back(index);
                q.pop();
                Current = 0;
                index++;
            }
            else {
                Current++;
                index++;
                if (index == process) index = 0;
                if (Current == q.size() + 1) break;
                continue;
            }
            if (index == process) index = 0;
            if (Current == q.size()) break;
        }

        if (CheckFinish()) {
            cout << "Safe state\n";
            cout << "Safe sequence: ";
            for (int i = 0; i < safeSequence.size(); i++) {
                cout << "Process" << safeSequence[i];
                if (i != safeSequence.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
        else {
            cout << "Not Safe State - Deadlock detected\n";
        }
        cout << "\n";
    }


    bool CheckFinish() {
        for (int i = 0; i < process; i++) {
            if (!finish[i]) return false;
        }
        return true;
    }

    bool CheckAllocation(int index) {
        for (int i = 0; i < resource; i++) {
            if (need[index][i] > work[i]) return false;
        }
        return true;
    }
    void printVectors() {
        cout << "Resource Allocated matrix: \n";
        for (const auto& row : allocated) {
            for (int element : row) {
                cout << element << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        cout << "Maximum matrix: \n";
        for (const auto& row : Maximum) {
            for (int element : row) {
                cout << element << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        cout << "Need matrix: \n";
        for (const auto& row : need) {
            for (int element : row) {
                cout << element << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        cout << "Existing resource: \n";
        for (auto& c : resourceInstance) {
            cout << c << " ";
        }
        cout << "\n";
        cout << "\n";
        cout << "Possessed resource: \n";
        for (auto& c : possessed) {
            cout << c << " ";
        }
        cout << "\n";
        cout << "\n";
        cout << "Available resource: \n";
        for (auto& c : available) {
            cout << c << " ";
        }
        cout << "\n";
        cout << "\n";
    }

    
};

int main() {
    Bankers* b = new Bankers();
    while (1)
    {
        b->Read();
        b->printVectors();
        b->CheckSafeState();
        cout << "Enter 1 to exit or press any number to continue \n";
        int n;
        cin >> n;
        if (n == 1) break;
    }
    delete b;
    return 0;
}
