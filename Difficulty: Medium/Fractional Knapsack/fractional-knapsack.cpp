//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value;
    int weight;
};


// } Driver Code Ends
// class implemented
/*
struct Item{
    int value;
    int weight;
};
*/

class Solution {
  public:
    // Function to get the maximum total value in the knapsack.
     bool static comp(Item a , Item b)
    {
        double r1 = (double)a.value/(double)a.weight;
        double r2 = (double)b.value/(double)b.weight;
        return r1>r2;
    }
    double fractionalKnapsack(int w, Item arr[], int n) {
        
        sort(arr,arr+n,comp);
        int currweight = 0;
        double totalvalue = 0.0;
        
        for(int i=0;i<n;i++)
        {
            if(currweight+arr[i].weight<=w)
            {
                currweight+= arr[i].weight;
                totalvalue+= arr[i].value;
            }
            else
            {
                int remain = w-currweight;
                totalvalue+= arr[i].value/(double)arr[i].weight * (double)remain;
                break;
            }
        }
        return totalvalue;
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    // taking testcases
    cin >> t;
    cout << setprecision(6) << fixed;
    while (t--) {
        // size of array and weight
        int n, W;
        cin >> n >> W;

        Item arr[n];
        // value and weight of each item
        for (int i = 0; i < n; i++) {
            cin >> arr[i].value >> arr[i].weight;
        }

        // function call
        Solution ob;
        cout << ob.fractionalKnapsack(W, arr, n) << endl;
    }
    return 0;
}
// } Driver Code Ends