#include <iostream>
#include <queue>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int value)
    {
        this->data = value;
        this->left = NULL;
        this->right = NULL;
    }
};
class Operation
{
public:
    Node *insertIntoBST(Node *root, int data)
    {
        if (root == NULL)
        {
            root = new Node(data);
            return root;
        }
        if (data > root->data)
        {
            root->right = insertIntoBST(root->right, data);
        }
        else
        {
            root->left = insertIntoBST(root->left, data);
        }
        return root;
    }
    void createBST(Node *&root)
    {
        cout << "Enter data:" << endl;
        int data;
        cin >> data;
        while (data != -1)
        {
            root = insertIntoBST(root, data);
            cout << "Enter data:" << endl;
            cin >> data;
        }
    }
    int maxPath(Node *root)
    {
        if (!root)
            return 0;
        int left = 0, right = 0;
        if (root->left)
            left = maxPath(root->left);
        if (root->right)
            right = maxPath(root->right);
        return 1 + max(left, right);
    }
    void levelOrderTraversal(Node *root)
    {
        queue<Node *> q;
        q.push(root);
        q.push(NULL);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << endl;
                if (!q.empty())
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout << temp->data << " ";
                if (temp->left != NULL)
                {
                    q.push(temp->left);
                }
                if (temp->right != NULL)
                {
                    q.push(temp->right);
                }
            }
        }
    }
    void preorder(Node *root)
    {
        if (root == NULL)
            return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
    void inorder(Node *root)
    {
        if (root == NULL)
            return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
    void postorder(Node *root)
    {
        if (root == NULL)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
    Node *minValue(Node *root)
    {
        if (root == NULL)
        {
            cout << "NO MIN VALUE" << endl;
            return NULL;
        }
        Node *temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    Node *maxValue(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        Node *temp = root;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }
    bool searchInBST(Node *root, int target)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->data == target)
        {
            return true;
        }
        bool leftAns = false;
        bool rightAns = false;
        if (target > root->data)
        {
            rightAns = searchInBST(root->right, target);
        }
        else
        {
            leftAns = searchInBST(root->left, target);
        }
        return leftAns || rightAns;
    }
    Node *swap_left_right(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
        {
            Node *temp;
            temp = root->left;
            root->left = root->right;
            root->right = temp;
            swap_left_right(root->left);
            swap_left_right(root->right);
            return root;
        }
    }
    Node *copyTree(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        Node *root_copy = new Node(root->data);
        root_copy->left = copyTree(root->left);
        root_copy->right = copyTree(root->right);
        return root_copy;
    }
    void delTreeHelper(Node *_root)
    {
        if (!_root)
            return;
        delTreeHelper(_root->left);
        delTreeHelper(_root->right);
        _root->left = nullptr;
        _root->right = nullptr;
        delete _root;
    }
    void delTree(Node *&root)
    {
        delTreeHelper(root);
        root = NULL;
        //  cout<<"Tree deleted successfully"<<endl;
    }
};
// 100 50 200 30 90 300 70 95 400 -1
int main()
{
    Node *root = NULL;
    while (true)
    {
        Operation obj;
        cout << "Choose the one of the option" << endl;
        cout << "1)Create a BST" << endl;
        cout << "2)Display BST" << endl;
        cout << "3)Insert a new node" << endl;
        cout << "4)Find the number node in longest path" << endl;
        cout << "5)Minimum and Maximum data value" << endl;
        cout << "6)swapped left and right pointer of every node" << endl;
        cout << "7)Search an element" << endl;
        cout << "8)erase tree" << endl;
        cout << "9)Exit" << endl;
        int choice;
        cin >> choice;
        try
        {
            if (choice > 9 || choice < 1)
            {
                cout << "please enter valid input";
                continue;
            }
            if (choice == 1)
            {
                obj.delTree(root);
                obj.createBST(root);
                cout << "Binary Search Tree is created successfully" << endl;
            }
            if (root == NULL)
            {
                throw "PLEASE CREATE A TREE FIRST";
            }
            else if (choice == 2)
            {
                obj.levelOrderTraversal(root);
                cout << endl;
                cout << endl
                     << "Inorder: ";
                obj.inorder(root);
                cout << endl
                     << "Preorder: ";
                obj.preorder(root);
                cout << endl
                     << "PostOrder: ";
                obj.postorder(root);
                cout << endl;
            }
            else if (choice == 3)
            {
                int data;
                cout << "Enter the data to insert" << endl;
                cin >> data;
                root = obj.insertIntoBST(root, data);
                obj.levelOrderTraversal(root);
            }
            else if (choice == 4)
            {
                cout << endl
                     << "NO of nodes in logest path is " << endl;
                cout << obj.maxPath(root);
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << endl;
                Node *minNode = obj.minValue(root);
                if (minNode == NULL)
                {
                    cout << "There is no node in tree, so no min value" << endl;
                }
                else
                {
                    cout << "Min Value: " << minNode->data << endl;
                }
                cout << endl;
                Node *maxNode = obj.maxValue(root);
                if (maxNode == NULL)
                {
                    cout << "There is no node in tree, so no max value" << endl;
                }
                else
                {
                    cout << "Max Value: " << maxNode->data << endl;
                }
            }
            else if (choice == 6)
            {
                Node *tempnode = NULL;
                tempnode = obj.copyTree(root);
                Node *change = obj.swap_left_right(tempnode);
                cout << "After swapping" << endl;
                obj.levelOrderTraversal(change);
                cout << "Original Tree" << endl;
                obj.levelOrderTraversal(root);
            }
            else if (choice == 7)
            {
                int t;
                cout << "Enter the target: " << endl;
                cin >> t;
                bool ans = obj.searchInBST(root, t);
                if (ans == true)
                {
                    cout << "Found" << endl;
                }
                else
                {
                    cout << "Not Found" << endl;
                }
            }
            else if (choice == 8)
            {
                obj.delTree(root);
                cout << "tree deleted successfully" << endl;
            }
            else if (choice == 9)
            {
                cout << "Thank you" << endl;
                break;
            }
        }
        catch (const char *message)
        {
            cout << "Exception caught: " << message << endl;
            continue;
        }
    }
    return 0;
}
