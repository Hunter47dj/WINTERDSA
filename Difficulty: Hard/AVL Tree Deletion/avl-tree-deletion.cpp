//{ Driver Code Starts
//

#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};

int setHeights(Node* n)
{
	if(!n) return 0;
	n->height = 1 + max( setHeights(n->left) , setHeights(n->right) );
	return n->height;
}

Node* buildTree(string str)
{   
    // Corner Case
    if(str.length() == 0 || str[0] == 'N')
            return NULL;
    
    // Creating vector of strings from input 
    // string after spliting by space
    vector<string> ip;
    
    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);
        
    // Create the root of the tree
    Node* root = new Node(stoi(ip[0]));
        
    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);
        
    // Starting from the second element
    int i = 1;
    while(!queue.empty() && i < ip.size()) {
            
        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();
            
        // Get the current node's value from the string
        string currVal = ip[i];
            
        // If the left child is not null
        if(currVal != "N") {
                
            // Create the left child for the current node
            currNode->left = new Node(stoi(currVal));
                
            // Push it to the queue
            queue.push(currNode->left);
        }
            
        // For the right child
        i++;
        if(i >= ip.size())
            break;
        currVal = ip[i];
            
        // If the right child is not null
        if(currVal != "N") {
                
            // Create the right child for the current node
            currNode->right = new Node(stoi(currVal));
                
            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }
    
    setHeights(root);
    return root;
}

bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}

struct Node* deleteNode(struct Node* root, int data);

int main()
{
	int t;
	cin>>t;
	getchar();

	while(t--)
	{
		string s;
		getline(cin,s);
		Node* root = buildTree(s);
        
		int n;
		cin>> n;
		int ip[n];
		for(int i=0; i<n; i++)
			cin>> ip[i];
        
		for(int i=0; i<n; i++)
		{
			root = deleteNode(root, ip[i]);
			
			if( !isBalancedBST(root) )
				break;
		}
        
		if(root==NULL)
			cout<<"null";
		else
			printInorder(root);
		cout<< endl;
        
		getline(cin,s); // to deal with newline char
	}
	return 1;
}

// } Driver Code Ends


/* Node is as follows:

struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};

*/

int height(Node* N){
    if(N==NULL){
        return 0;
    }
    return N->height;
}

int getBalance(Node* N){
    if(N==NULL){
        return 0;
    }
    return height(N->left)-height(N->right);
}

Node* leftRotation(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = 1+max(height(x->left),height(x->right));
    y->height = 1+max(height(y->left),height(y->right));
    
    return y;
}

Node* rightRotation(Node* x){
    Node* y = x->left;
    Node* T2 = y->right;
    
    y->right = x;
    x->left = T2;
    
    x->height = 1+max(height(x->left),height(x->right));
    y->height = 1+max(height(y->left),height(y->right));
    
    return y;
}

Node* getSuccessor(Node* curr){
    curr = curr->right;
    while(curr!=NULL && curr->left!=NULL){
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root, int data)
{
    if(root==NULL){
        return root;
    }else if(data > root->data){
        root->right = deleteNode(root->right,data);
    }else if(data < root->data){
        root->left = deleteNode(root->left,data);
    }else{
        if(root->left==NULL || root->right==NULL){
            Node* temp = root->left ? root->left : root->right;
            if(temp==NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;    
            }
            delete temp;
        }else{
            Node* succ = getSuccessor(root);
            root->data = succ->data;
            root->right = deleteNode(root->right,succ->data);
        }
    }
    
    if(root==NULL){
        return root;
    }
    
    root->height = 1+max(height(root->left),height(root->right));
    
    int balance = getBalance(root);
    
    if(balance>1 && getBalance(root->left)>=0){
        return rightRotation(root);
    }
    if(balance<-1 && getBalance(root->right)<=0){
        return leftRotation(root);
    }
    if(balance>1 && getBalance(root->left)<0){
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if(balance<-1 && getBalance(root->right)>0){
        root->right= rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}


