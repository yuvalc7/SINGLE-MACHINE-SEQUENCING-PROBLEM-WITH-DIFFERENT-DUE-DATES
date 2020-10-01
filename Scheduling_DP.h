//
// Created by yuval on 29/09/2020.
//

#include <vector>
#include <unordered_map>
using  namespace std;
struct val{
    string order;
    int F;
};
class Scheduling_DP {

    /*---- Fields ----*/
    private:
        int*  p_j;
        int* d_j ;
        int* index_permutation ;//Go over all the permutations on the Task Vector indexes
        int* optimal_permutation;//The optimal order of the tasks from task 0 ..
        int Min_Late = INT_MAX;
        int size;
        unordered_map<string  , val > F_j_1;
        unordered_map<string  , val > F_j_2;
        string * combination;
        /*---- Constructors ----*/
    public:
        Scheduling_DP(int p_j [] , int d_j [] , int size);
        /*---- Methods ----*/
        void Min_Late_times();
        void combinationUtil(int arr [] , int n, int r, int index, int data[], int i );
        void setMin();
};
