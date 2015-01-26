// g++ tree.cpp -std=c++11
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

TreeNode* createTree(const vector<int> &vs, size_t index) {
    if (index >= vs.size()) {
        cout << "index is out of range\n";
        abort();
    }
    TreeNode *node = new TreeNode(vs[index]);
    size_t leftIndex =  2 * index + 1;
    size_t rightIndex = 2 * index + 2;
    if (leftIndex < vs.size() && vs[leftIndex] != INT_MAX) {
        node->left = createTree(vs, leftIndex);
    }
    if (rightIndex < vs.size() && vs[rightIndex] != INT_MAX) {
        node->right = createTree(vs, rightIndex);
    }

    return node;
}

void inorderTraversal(TreeNode* root, vector<int> & result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}
vector<int> inorderTraversal(TreeNode *root) {
    vector<int> result;
    inorderTraversal(root, result);
    return result;
}
void levelTraversal(TreeNode *root, int level, vector<vector<int> > &result) {
    if (!root) return;
    if (level > result.size()) {
        result.push_back(vector<int>());
    }

    result[level-1].push_back(root->val);

    levelTraversal(root->left, level+1, result);
    levelTraversal(root->right, level+1, result);
}

vector<vector<int> > levelTraversal(TreeNode *root) {
    vector<vector<int> > result;
    levelTraversal(root, 1, result);
    return result;
}

int main(int argc, char* argv[])
{
    vector<int> vs = {2, 3, 3, 4, 5, INT_MAX, 4};
    TreeNode *root = createTree(vs, 0);
    vector<int> inorder = inorderTraversal(root);
    cout << "[";
    for_each(inorder.begin(), inorder.end(), [](int &i) { cout << i << " " ; });
    cout << "]\n";
    vector<vector<int> > ltr = levelTraversal(root);
    cout << "[\n";
    for(int i=0; i<ltr.size(); ++i) {
        const vector<int> &row = ltr[i];
        cout << "  [ ";
        for(int j=0; j<row.size(); ++j) {
            cout << row[j] << " ";
        }
        cout << "]\n";
    }
    cout << "]\n";


    return 0;
}
