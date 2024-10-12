#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) {
        root->left = insert(root->left, val);
    }
    else {
        root->right = insert(root->right, val);
    }
    return root;
}

void preOrder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preOrder(root->left, result);
    preOrder(root->right, result);
}

int find(TreeNode* root, int val, int count) {
    if (!root) return -1;
    if (root->val == val) return count;
    if (val < root->val) return find(root->left, val, count + 1);
    return find(root->right, val, count + 1);
}

void quickSortFirstPass(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    while (i <= j) {
        while (i <= high && arr[i] < pivot) i++;
        while (j > low && arr[j] >= pivot) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
}

int main() {
    int n, target;
    cin >> n;
    vector<int> elements(n);
    for (int i = 0; i < n; ++i) {
        cin >> elements[i];
    }
    cin >> target;

    TreeNode* root = nullptr;
    for (int val : elements) {
        root = insert(root, val);
    }

    int searchCount = find(root, target, 1);
    cout << searchCount << endl;

    vector<int> preOrderResult;
    preOrder(root, preOrderResult);
    for (int val : preOrderResult) {
        cout << val << " ";
    }
    cout << endl;

    quickSortFirstPass(preOrderResult, 0, preOrderResult.size() - 1);
    for (int val : preOrderResult) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
