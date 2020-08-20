#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

/** Problem statement: https://acm.bsu.by/courses/120/problems/870/ */


using namespace std;

struct treenode {
    int val_;
    treenode *left = nullptr, *right = nullptr;

    treenode(int val) : val_(val) {}

    //temp, only for this task
    vector<int> heights;
    int depth;
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void readTree() {
        int input_val;
        std::fstream file("tst.in");
        while (file >> input_val) {
            this->add(root, input_val);
        }
    }

    void test() {
        ofstream fout("tst.out");
        depth(root, 0);

        if (root->left == nullptr || root->right == nullptr) {
            vertices.push_back(*root);
        }

        heights(root);
        int max_val = std::max_element(vertices.begin(), vertices.end(), [](const treenode &tr1, const treenode &tr2) {
            return tr1.depth < tr2.depth;
        })->depth;

        vector<int> toSort;

        int values = 0;
        for (auto el : vertices) {
            if (el.depth == max_val) {
                toSort.push_back(el.val_);
                //values += el.val_;
            }
        }
        if (toSort.size() % 2 != 0) {
            deleteNode(root, toSort[(toSort.size() - 1)/2]);
        }
        dfs(fout, root);
    }

    virtual ~BinaryTree() {
        DestroyTree(root);
    }

private:
    treenode *root;
    int toDelete;
    int max_depth = 0;
    vector<treenode> vertices;


    //supportive functions
    static void DestroyTree(treenode *root) {
        if (root != nullptr) {
            DestroyTree(root->left);
            DestroyTree(root->right);
            delete root;
        }
    }

    void add(treenode *&node, int new_val) {
        if (node == nullptr) {
            node = new treenode(new_val);
        } else {
            if (new_val < node->val_) {
                add(node->left, new_val);
            }
            if (new_val > node->val_) {
                add(node->right, new_val);
            }
        }
    }

    void deleteNode(treenode *&node, const int &toDeleteVal) {
        if (node != nullptr) {
            if (toDeleteVal < node->val_) {
                deleteNode(node->left, toDeleteVal);
            }
            if (toDeleteVal > node->val_) {
                deleteNode(node->right, toDeleteVal);
            }
            if (toDeleteVal == node->val_) {
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
                } else {
                    if (node->left == nullptr) node = node->right;
                    else if (node->right == nullptr) node = node->left;
                    else if (node->left != nullptr && node->right != nullptr) {
                        treenode *temp = node->right;
                        while (temp->left != nullptr) {
                            temp = temp->left;
                        }
                        node->val_ = temp->val_;
                        deleteNode(node->right, node->val_);
                    }
                }
            }
        }
    }

    //templates
    void dfs(ofstream &os, treenode *node) {
        if (node != nullptr) {
            os << node->val_ << endl;
            dfs(os, node->left);
            dfs(os, node->right);
        }
    }

    void depth(treenode *node, int local_depth) {
        if (node != nullptr) {
            node->depth = local_depth;
            if (node->left == nullptr && node->right == nullptr) {
                if (local_depth > max_depth)
                    max_depth = local_depth;
            } else {
                depth(node->left, local_depth + 1);
                depth(node->right, local_depth + 1);
            }
        }
    }

    void heights(treenode *node) {
        if (node != nullptr) {
            heights(node->left);
            heights(node->right);
            if (node->left == nullptr && node->right == nullptr)
                node->heights.push_back(0);
            else if (node->left == nullptr) {
                for (auto el : node->right->heights)
                    node->heights.push_back(el + 1);
            } else if (node->right == nullptr) {
                for (auto el : node->left->heights)
                    node->heights.push_back(el + 1);
            } else {
                //check
                bool stop = false;
                for (auto el_right : node->right->heights) {
                    if (!stop) {
                        for (auto el_left: node->left->heights) {
                            if (el_right + el_left + 2 == max_depth) {
                                vertices.push_back(*node);
                                stop = true;
                                break;
                            }
                        }
                    }
                }
                node->heights = node->left->heights;
                node->heights.insert(node->heights.end(), node->right->heights.begin(), node->right->heights.end());
                for (int &el : node->heights)
                    el = el + 1;

            }
        }
    }

};

int main() {
    BinaryTree binary_tree;
    binary_tree.readTree();
    binary_tree.test();
}

