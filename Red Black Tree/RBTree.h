#ifndef _RBTREE_H_
#define  _RBTREE_H_
#include<iostream>
#include<queue>
using namespace std;
enum Color
{
	RED,BLACK
};
class Node
{
public:
	int data;
	Color color;
	Node* left, * right, * parent;
	Node();
	Node(int data)
	{
		this->data = data;
		left = right = parent = NULL;
		this->color = RED;
	}
	~Node();

private:

};

Node::Node()
{
	left = right = parent = NULL;
	color = RED;
}

Node::~Node()
{
}
class RBTree
{
private:
	Node* root;
protected:
	void leftRotate(Node*& root, Node*& pt);
	void rightRotate(Node*& root, Node*& pt);
	void fixViolation(Node*& root, Node*& pt);
public:
	RBTree() { root = NULL; }
	void insertNode(const int& value);
	void inorder();
	void levelOrder();
};

void insertBST(Node*& root, Node* pt)
{
	if (root == NULL) root= pt;
	if (pt->data > root->data)
	{
		insertBST(root->right, pt);
		root->right->parent = root;
	}
	else if (pt->data < root->data)
	{
		insertBST(root->left, pt);
		root->left->parent = root;
	}
}

void inorderHelper(Node* root)
{
	if (root == NULL) return;
	inorderHelper(root->left);
	cout << root->data << " " << root << " ";
	inorderHelper(root->right);
}

void levelorderHelper(Node* root)
{
	if (root == NULL) return;
	queue<Node*> p;
	p.push(root);
	while (!p.empty())
	{
		Node* temp = p.front();
		cout << temp->data << " ";
		p.pop();
		if (temp->left != NULL)
		{
			p.push(temp->left);
		}
		if (temp->right != NULL)
		{
			p.push(temp->right);
		}
	}
}
void swapColor(Color& a, Color& b);
#endif // !_RBTREE_H_



