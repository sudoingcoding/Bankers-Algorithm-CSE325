#include<bits/stdc++.h>
#include <cstdlib>
using namespace std;

class Bankers {
public:
    int process;
    int resource;
    vector<int> resourceInstance;
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

        available.resize(resource);
        work.resize(resource);
        finish.resize(process);

        Maximum.resize(process, vector<int>(resource));
        allocated.resize(process, vector<int>(resource));
        need.resize(process, vector<int>(resource));
        list.resize(process);
    }

    void calcNeed() {
        cout << "Current Resource Need: \n";
        for (int i = 0; i < process; i++) {
            cout << "Process " << i << " \n";
            for (int j = 0; j < resource; j++) {
                need[i][j] = Maximum[i][j] - allocated[i][j];
                cout << "Resource " << j << " : " << need[i][j] << "\n";
            }
        }
    }

    void displayNeed() {
        for (const auto& row : need) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << "\n";
        }
    }

    void allocateResource() {
        cout << "Allocated Resources:\n";
        for (int i = 0; i < process; i++) {
            cout << "Process " << i << ":\n";
            for (int j = 0; j < resource; j++) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dist(1, resourceInstance[j]);
                int num = dist(gen);
                allocated[i][j] = num;
                cout << "Resource " << j << " : " << num << "\n";
            }
        }
    }

    void Read() {
        cout << "Enter Maximum Resource Needed: \n";
        for (int i = 0; i < process; i++) {
            cout << "Process " << i << ":\n";
            for (int j = 0; j < resource; j++) {
                cout << "Resource " << j << ": ";
                int num;
                cin >> num;
                Maximum[i][j] = num;
            }
        }
        allocateResource();
        calcNeed();
    }

    bool CheckSafeState() {
        queue<int> q;
        for (int i = 0; i < process; i++) q.push(i);

        vector<int> work_copy = work;
        vector<bool> finish_copy = finish;

        int count = 0;
        vector<int> safe_sequence;

        while (!q.empty()) {
            int index = q.front();
            q.pop();

            if (!finish_copy[index] && CheckAllocation(index, work_copy)) {
                safe_sequence.push_back(index);
                finish_copy[index] = true;
                for (int i = 0; i < resource; i++) {
                    work_copy[i] += allocated[index][i];
                }
                count = 0;
            }
            else {
                count++;
            }

            if (count == process) {
                break;
            }

            if (q.empty()) {
                for (int i = 0; i < process; i++) {
                    if (!finish_copy[i]) {
                        q.push(i);
                        break;
                    }
                }
            }
        }

        if (safe_sequence.size() == process) {
            cout << "Safe state\n";
            cout << "Safe sequence: ";
            for (int i = 0; i < process; i++) {
                cout << "Process " << safe_sequence[i];
                if (i != process - 1) cout << " -> ";
            }
            cout << endl;
            return true;
        }
        else {
            cout << "Not Safe State - Deadlock detected\n";
            return false;
        }
    }

    bool CheckAllocation(int index, const vector<int>& work_copy) {
        for (int i = 0; i < resource; i++) {
            if (need[index][i] > work_copy[i]) return false;
        }
        return true;
    }
};

int main() {
    system("bash cmd.txt");
    Bankers* b = new Bankers();
    b->Read();
    b->calcNeed();
    b->displayNeed();
    b->CheckSafeState();
    delete b;
    return 0;
}

