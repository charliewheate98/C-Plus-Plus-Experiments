#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>

using namespace std;

struct Node 
{
    bool visited;
    int data;
    vector<Node*> adj;

    Node(int val) : data(val), visited(false) {}
    ~Node() { adj.clear(); }
};

class Graph {
public:
    Graph(int s) {
        this->size = s;
    }
    ~Graph() {}

    void addEdge(Node* a, Node* b) {
        a->adj.push_back(b);
        b->adj.push_back(a);
    }

    void visit(Node* n) {
        cout << n->data << endl;
    }

    int isIntersecting(bool a_visited[], bool b_visited[]) {
        for (auto i = 0; i < size; ++i) {
            if (a_visited[i] && b_visited[i])
                return i;
        }

        return -1;
    }

    void DFS(Node* root) {
        if (root == nullptr)
            return;
        
        visit(root);
        root->visited = true;

        for (Node* n : root->adj) {
            DFS(n);
        }
    }
    void BFS(queue<Node*> q, Node* root) {
        if (root == nullptr)
            return;

        root->visited = true;
        q.push(root);

        while(!q.empty()) {
            Node* r = q.front();
            q.pop();

            for (Node* n : r->adj) {
                if (n->visited == false) {
                    n->visited = true;
                    q.push(n);
                }
            }
        }
    }

    bool isRoute(Node* a, Node* b)
    {
        bool a_visited[size], b_visited[size];
        int a_parent[size], b_parent[size];

        int intersectNode = -1;

        for (auto i = 0; i < size; ++i) {
            a_visited[i] = false;
            b_visited[i] = false;
        }

        queue<int> qa;
        queue<int> qb;

        a_visited[a] = true;
        qa.push(a);
        a_parent[a] = -1;

        b_visited[b] = true;
        qb.push(b);
        b_parent[b] = -1;

        while (!qa.empty() && !qb.empty()) 
        {
            BFS(qa, a_visited, a_parent);
            BFS(qb, b_visited, b_parent);

            intersectNode = isIntersecting(a_visited, b_visited);

            if (intersectNode != -1) {
                cout << "A Route Exists between nodes " << a << " and " << b << endl;
                exit(0);
            }
        }

    }
private:
    int size;
};

struct ListNode
{
    int data;
    ListNode* next;

    ListNode(int val) : data(val), next(nullptr) {}
    ~ListNode() { delete next; }
};
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    ~TreeNode() {}
};
TreeNode* newNode(int data)
{
    TreeNode* new_node = new TreeNode(data);
    return new_node;
}

TreeNode* SortedArrayToBST(int arr[], int start, int end) 
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    TreeNode* root = newNode(arr[mid]);

    root->left = SortedArrayToBST(arr, start, mid - 1);
    root->right = SortedArrayToBST(arr, mid + 1, end);
    
    return root;
}

TreeNode* Insert(TreeNode* root, int data)
{
    if (root == nullptr)
        return newNode(data);

    if (root->data > data) {
        Insert(root->left, data);
    }
    else if (root->data < data) {
        Insert(root->right, data);
    }

    return root;
}

// in-order traversal
void printInOrder(TreeNode* root)
{
    if (root == nullptr)
        return;

    printInOrder(root->left);
    cout << root->data << endl;
    printInOrder(root->right);
}

int GetHeight(TreeNode* root)
{
    if (root == nullptr) {
        return 0;
    }
    else {
        int lheight = GetHeight(root->left);
        int rheight = GetHeight(root->right);

        if (lheight > rheight) {
            return(lheight + 1);
        }
        else return (rheight + 1);
    }
}

void getNodesAtGivenLevel(TreeNode* root, int level)
{
    if (root == nullptr)
        return;

    if (level == 1) {
        cout << root->data << " ";
    }
    else if (level > 1) {
        getNodesAtGivenLevel(root->left, level - 1);
        getNodesAtGivenLevel(root->right, level - 1);
    }
}

void LevelOrderTraversal(TreeNode* root)
{
    int bst_height = GetHeight(root);

    for (unsigned i = 1; i <= bst_height; ++i) {
        getNodesAtGivenLevel(root, i);
    }
}

void Display(vector<ListNode*> al)
{
    for (auto i = 0; i < al.size(); ++i)
    {
        ListNode* temp = al[i];

        while (al[i] != nullptr)
        {
            cout << "->" << al[i]->data;
            al[i] = al[i]->next;
        }
        cout << endl;
    }
}

vector<ListNode*> al;
void ListOfDepths(TreeNode* root)
{
    if (root == nullptr)
        return;

    int levelNodes = 0;

    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        levelNodes = nodeQueue.size();
        ListNode* head = nullptr;
        ListNode* current = nullptr;

        while (levelNodes > 0)
        {
            TreeNode* n = nodeQueue.front();
            nodeQueue.pop();

            ListNode* ln = new ListNode(n->data);

            if (head == nullptr) {
                head = ln;
                current = ln;
            }
            else {
                current->next = ln;
                current = current->next;
            }

            if (n->left != nullptr) nodeQueue.push(n->left);
            if (n->right != nullptr) nodeQueue.push(n->right);
            
            --levelNodes;
        }

        al.push_back(head);
    }

    Display(al);
}

////////////////////////////////////////////////////////////////
// Check Balanced Challenge                                   //
////////////////////////////////////////////////////////////////
// Implement a function to check if a binary tree is balanced //
////////////////////////////////////////////////////////////////
int height(TreeNode* root)
{
    if (root == nullptr)
        return 0;
    else 
    {
        int lheight = height(root->left);
        int rheight = height(root->right);

        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}
bool isBalanced(TreeNode* left_r, TreeNode* right_r)
{
    int left_subtree_height = height(left_r);
    int right_subtree_height = height(right_r);

    int threshold = 1;

    if (left_subtree_height > right_subtree_height + threshold) {
        return false;
    }
    else if (right_subtree_height > left_subtree_height + threshold) {
        return false;
    }

    return true;
}

// O(n)
template<typename Key, typename Value>
bool all_equal(std::map<Key, Value> const& map)
{
    // the lambda will only get called when the map is not empty
    // so we can safely access begin()->second
    auto const cmpWithFirst = [&](std::pair<Key, Value> const& i)
    {
        return map.begin()->second == i.second;
    };

    return std::all_of(map.begin(), map.end(), cmpWithFirst);
}
// N O(log n)
bool isValid(string & str)
{
    int n = strlen(str.c_str());

    map<char, int> occurs;
    occurs.insert(make_pair(str[0], 1));

    if (occurs.empty()) {
        printf("Invalid Hashmap in 'isValid' function");
        return;
    }

    if (n < 2)
        return true;
    else
    {
        for (auto i = 1; i < str.length(); ++i)
        {
            if (occurs.find(str[i]) == occurs.end()) {
                occurs.insert(make_pair(str[i], 1));
            }
            else
            {
                occurs.find(str[i])->second++;
            }
        }
    }

    if (all_equal(occurs)) {
        return true;
    }
    else
        return false;

    return true;
}

int lengthOfLongestSubstring(string s) 
{
    int WindowStart = 0;
    int WindowEnd = 0;
    int maxSoFar = INT_MIN;

    set<char> hashset;

    while (WindowEnd < s.length())
    {
        if (hashset.find(s[WindowEnd]) == hashset.end()) {
            hashset.insert(s[WindowEnd]);
            WindowEnd++;

            maxSoFar = std::max((int)hashset.size(), maxSoFar);
        }
        else {
            hashset.erase(s[WindowStart]);
            WindowStart++;
        }
    }

    return maxSoFar;
}

int main(int argc, char* argv[])
{
    //int arr[5] = { 1, 2, 3, 4, 5 };
    //int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode* root = newNode(1); 
    root->left = newNode(2); 
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5); 

    //TreeNode* root = SortedArrayToBST(arr, 0, n-1);
    //printInOrder(root);
    //LevelOrderTraversal(root);
    //ListOfDepths(root);

    //if (isBalanced(root->left, root->right)) {
    //    printf("Balanced!\n\n");
    //} 
    //else  printf("Unbalanced!\n\n");

    string test = "aabb";
    if (isValid(test))
        printf("VALID!");
    else 
        printf("NOT VALID!");

    system("pause");
    return EXIT_SUCCESS;
}
