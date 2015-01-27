#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits.h>
using namespace std;

namespace Tree {

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int v): val(v), left(NULL), right(NULL), next(NULL) {}
};

template <typename T>
T* createTree(const vector<int> &vs, size_t index, T *p) {
    if (index >= vs.size()) {
        cout << "index is out of range\n";
        abort();
    }
    T *node = new T(vs[index]);
    size_t leftIndex =  2 * index + 1;
    size_t rightIndex = 2 * index + 2;
    if (leftIndex < vs.size() && vs[leftIndex] != INT_MAX) {
        node->left = createTree(vs, leftIndex, p);
    }
    if (rightIndex < vs.size() && vs[rightIndex] != INT_MAX) {
        node->right = createTree(vs, rightIndex, p);
    }

    return node;
}

template <typename T>
T* createTree(const vector<int> &vs, T *p) {
    return createTree(vs, 0, p);
}
TreeNode* createTree(const vector<int> &vs) {
    return createTree(vs, 0, (TreeNode*)NULL);
}
TreeLinkNode* createLinkTree(const vector<int> &vs) {
    return createTree(vs, 0, (TreeLinkNode*)NULL);
}

template <typename T>
void inorderTraversal(T* root, vector<int> & result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}
template <typename T>
vector<int> inorderTraversal(T *root) {
    vector<int> result;
    inorderTraversal(root, result);
    return result;
}
template <typename T>
void levelTraversal(T *root, int level, vector<vector<int> > &result) {
    if (!root) return;
    if (level > result.size()) {
        result.push_back(vector<int>());
    }

    result[level-1].push_back(root->val);

    levelTraversal(root->left, level+1, result);
    levelTraversal(root->right, level+1, result);
}

template <typename T>
vector<vector<int> > levelTraversal(T *root) {
    vector<vector<int> > result;
    levelTraversal(root, 1, result);
    return result;
}



void connect(TreeLinkNode *root) {
    TreeLinkNode *cur = root, *prev = NULL;
    
    while (cur) {
        if (cur->left == NULL) {
            // 此处省略访问当前结点的代码
            cur = cur->right; // 注意在morris方法中，叶子结点的right是用来指向中序遍历的后续结点的，所以此处cur->right肯定不为空。
        }
        else {
            //下面这段代码不能放在访问当前结点的位置，跟一遍题目中的测试用例即明白了。
            // 放在这能保证每个结点的左孩子尽早指向它的右孩子，这样左孩子的子树就能利用这个信息了。
            // 例外，放在这会导致这段代码执行两遍，虽然效率上不会右太大损失，但还是加上一个if判断。
            //--------------------------------------
            if(cur->left->next == NULL) {
                if (cur->right != NULL) {
                    cur->left->next = cur->right; // 左孩子指向右孩子
                    if (cur->next) { // 为右孩子找到next结点
                        TreeLinkNode *p = cur->next;
                        while (p && p->left == NULL && p->right == NULL) p = p->next;
                        if (p != NULL)
                            cur->right->next = p->left ? p->left : p->right;
                    }
                }
                else { // 右孩子为空
                    if (cur->next) { // 为左孩子找到next结点
                        TreeLinkNode *p = cur->next;
                        while (p && p->left == NULL && p->right == NULL) p = p->next;
                        if (p != NULL)
                            cur->left->next = p->left ? p->left : p->right;
                    }
                }
            }
            //--------------------------------------
            
            prev = cur->left;
            while(prev->right != NULL && prev->right != cur) {
                prev = prev->right;
            }
            
            if (prev->right == NULL) {
                prev->right = cur;
                cur = cur->left;
            }
            else {
                prev->right = NULL;
                // 此处省略访问当前结点的代码
                cur = cur->right;
            }
        }
    }
}

} // namespace Tree
