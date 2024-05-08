//. Beginning with an empty binary tree, Construct binary tree by inserting the values
// in the order given. After constructing a binary tree perform following operations
// on it-
// Perform inorder / preorder and post order traversal
// Change a tree so that the roles of the left and right pointers are swapped at
// every node
// Find the height of tree
// Copy this tree to another [operator=
// Count number of leaves, number of internal nodes.
// Erase all nodes in a binary tree
//(implement both recursive and non-recursive methods)

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *left;
    int data;
    Node *right;

    Node()
    {
        this->data = 0;
        this->left = NULL;
        this->right = NULL;
    }

    Node(int val)
    {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }
};

class Operation
{
public:
    Node *temp;

    Operation operator=(Operation &tree)
    {
        Operation new_obj;
        new_obj.temp = copyTree(tree.temp);
        return new_obj;
    }

    void levelOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        queue<Node *> q;
        Node *curr;
        q.push(root);
        q.push(NULL);
        while (q.size() > 1)
        {
            curr = q.front();
            q.pop();
            if (curr == NULL)
            {
                q.push(NULL);
                cout << "\n";
            }
            else
            {
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
                cout << curr->data << " ";
            }
        }
    }

    Node *createTree()
    {
        cout << "Enter the value for Node: " << endl;
        int data;
        cin >> data;
        if (data == -1)
        {
            return NULL;
        }
        Node *root = new Node(data);
        root->left = createTree();
        root->right = createTree();
        return root;
    }

    void inOrderS(Node *root)
    {
        stack<Node *> s;
        Node *curr = root;
        while (curr != NULL || s.empty() == false)
        {
            while (curr != NULL)
            {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    void preOrder(Node *root)
    {
        if (root == NULL)
            return;
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void postOrder(Node *root)
    {
        if (root == NULL)
            return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }

    void inOrder(Node *root)
    {
        if (root == NULL)
            return;
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    void preOrderS(Node *root)
    {
        stack<Node *> s;
        Node *curr = root;
        while (curr != NULL || s.empty() == false)
        {
            while (curr != NULL)
            {
                cout << curr->data << " ";
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            curr = curr->right;
        }
    }

    void postOrderS(Node *root)
    {
        stack<Node *> s;
        Node *curr = root;
        stack<Node *> p;
        while (curr != NULL || s.empty() == false)
        {
            while (curr != NULL)
            {
                p.push(curr);
                s.push(curr);
                curr = curr->right;
            }
            curr = s.top();
            s.pop();
            curr = curr->left;
        }
        while (!p.empty())
        {
            Node *curr = p.top();
            p.pop();
            cout << curr->data << " ";
        }
    }

    int height(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int left = height(root->left);
        int right = height(root->right);
        int height = max(left, right) + 1;
        return height;
    }

    void height_levelOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        queue<Node *> q;
        Node *curr;
        int depth = 1;
        q.push(root);
        q.push(NULL);
        while (q.size() > 1)
        {
            curr = q.front();
            q.pop();
            if (curr == NULL)
            {
                q.push(NULL);
                depth++;
            }
            else
            {
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
        cout << "Height is " << depth << endl;
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
            swap_left_right(root->left);
            swap_left_right(root->right);
            temp = root->left;
            root->left = root->right;
            root->right = temp;
            return root;
        }
    }

    int get_leaf_count(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->left == NULL && root->right == NULL)
        {
            return 1;
        }
        else
        {
            return get_leaf_count(root->left) + get_leaf_count(root->right);
        }
    }

    int get_leaf_count_nrecursive(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        queue<Node *> q;
        q.push(root);
        int count = 0;
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            if ((temp->left == NULL) && (temp->right == NULL))
            {
                count++;
            }
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
        return count;
    }

    int count_internal_node(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->left == NULL && root->right == NULL)
        {
            return 0;
        }
        return (1 + count_internal_node(root->left) + count_internal_node(root->right));
    }

    int count_internal_node_nonrecursive(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        queue<Node *> q;
        q.push(root);
        int count = 0;
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            if (temp->left != NULL || temp->right != NULL)
            {
                count++;
            }
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
        return count;
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
        cout << "Tree deleted successfully" << endl;
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
};

int main()
{
    Operation obj;
    Node *root;
    root = NULL;
    int choice;
    while (true)
    {
        cout << "Choice the one of the option" << endl;
        cout << "1) create Tree" << endl;
        cout << "2) Preorder traversal using recursion  " << endl;
        cout << "3) Preorder traversal without recursion  " << endl;
        cout << "4) Inorder traversal using recursion  " << endl;
        cout << "5) Inorder traversal without recursion  " << endl;
        cout << "6) Postorder traversal using recursion  " << endl;
        cout << "7) Postorder traversal without recursion  " << endl;
        cout << "8) Levelorder traversal  " << endl;
        cout << "9) Swapped left and right pointer of every node" << endl;
        cout << "10) Height of tree using recursion" << endl;
        cout << "11) Height of tree without recursion" << endl;
        cout << "12) Copy tree to another tree" << endl;
        cout << "13) count no of leaf node using recursion" << endl;
        cout << "14) count no of leaf node without recursion" << endl;
        cout << "15) count the internal node using recursion" << endl;
        cout << "16) count the internal node without recursion" << endl;
        cout << "17) Delete tree" << endl;
        cout << "18) Exit" << endl;
        cin >> choice;
        try
        {
            if (choice > 18 && choice < 0)
            {
                cout << "please enter valid input";
                continue;
            }
            if (choice == 1)
            {
                root = obj.createTree();
                cout << "Tree created Successfully" << endl;
            }
            if (root == NULL)
            {
                throw "PLEASE CREATE A TREE FIRST";
            }
            else if (choice == 2)
            {
                cout << "Preorder Traversal is" << endl;
                obj.preOrder(root);
                cout << endl;
            }
            else if (choice == 3)
            {
                cout << "Preorder using stack" << endl;
                obj.preOrderS(root);
                cout << endl;
            }
            else if (choice == 4)
            {
                cout << "Inorder Traversal is" << endl;
                obj.inOrder(root);
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << "Inorder using stack" << endl;
                obj.inOrderS(root);
                cout << endl;
            }
            else if (choice == 6)
            {
                cout << "Postorder Traversal is" << endl;
                obj.postOrder(root);
                cout << endl;
            }
            else if (choice == 7)
            {
                cout << "Postorder using stack" << endl;
                obj.postOrderS(root);
                cout << endl;
            }
            else if (choice == 8)
            {
                cout << "level order" << endl;
                obj.levelOrder(root);
                cout << endl;
            }
            else if (choice == 9)
            {
                cout << "changing left to right" << endl;
                Node *change = obj.swap_left_right(root);
                obj.levelOrder(change);
                cout << endl;
            }
            else if (choice == 10)
            {
                cout << "Height of tree is " << endl;
                cout << " " << obj.height(root) << endl;
            }
            else if (choice == 11)
            {
                cout << "Height of tree (non recursive)" << endl;
                obj.height_levelOrder(root);
            }
            else if (choice == 12)
            {
                cout << "Copy tree to another tree" << endl;
                obj.temp = root;
                Operation ans = obj;
                obj.levelOrder(ans.temp);
                cout << endl;
            }
            else if (choice == 13)
            {
                cout << "counting the leaf node" << endl;
                cout << obj.get_leaf_count(root);
                cout << endl;
            }
            else if (choice == 14)
            {
                cout << "counting the leaf node using non recursive" << endl;
                cout << obj.get_leaf_count_nrecursive(root);
                cout << endl;
            }
            else if (choice == 15)
            {
                cout << "Counting the internal node" << endl;
                cout << obj.count_internal_node(root);
                cout << endl;
            }
            else if (choice == 16)
            {
                cout << "counting the internal node nonrecursive" << endl;
                cout << obj.count_internal_node_nonrecursive(root);
                cout << endl;
            }
            else if (choice == 17)
            {
                cout << "deleting the tree" << endl;
                obj.delTree(root);
            }
            else if (choice == 18)
            {
                cout << "Thank you ";
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
