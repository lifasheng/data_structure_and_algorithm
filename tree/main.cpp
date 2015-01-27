#include "tree.h"
using namespace Tree;

int main(int argc, char* argv[])
{
    {
    vector<int> vs = {2, 3, 3, 4, 5, INT_MAX, 4};
    TreeNode *root = createTree(vs);
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
    }


    {
    vector<int> vs = {1,2,3,4,INT_MAX, INT_MAX, 5};
    TreeLinkNode *root = createLinkTree(vs);
    connect(root);
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
    }

    return 0;
}
