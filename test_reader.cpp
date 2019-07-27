#include <vector>
#include "process.h"


void multiple_reads(vector<string>& ans) {
    int shmid;
    void* ptr = setup(SHM_KEY, &shmid);

    cout << shmid << endl;

    string temp;

    for (int i = 0; i < MAX; i++) {
        ans[i] = get(shmid, ptr);
    }

    clean(SHM_KEY, ptr);

}

int main() {

    vector<string> ans(MAX);

    clock_t t;
    t = clock();

    multiple_reads(ans);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    cout << "Time Taken by Reader: " << time_taken << endl;

    bool valid = false;

    for (int i = 0; i < ans.size(); i++) {
        valid = false;
        for (int j = 0; j < data_to_write.size(); j++) {
            if (ans[i] == data_to_write[j]) {
                valid = true;
            }
        }
        if (!valid) {
            cout << "Failed: " << ans[i] << endl;
            return 1;
        }
    }
}