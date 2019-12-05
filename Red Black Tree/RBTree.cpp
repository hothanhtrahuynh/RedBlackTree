#include "RBTree.h"

void RBTree::leftRotate(Node*& root, Node*& pt)
{
	Node* pt_right = pt->right;
	pt->right = pt_right->left;
	if (pt->right != NULL)
	{
		pt->right->parent = pt;
	}
	pt_right->parent = pt->parent;
	if (pt->parent == NULL) root = pt_right;
	else if (pt == pt->parent->left)
	{
		pt->parent->left = pt_right;
	}
	else pt->parent->right = pt_right;
	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rightRotate(Node*& root, Node*& pt)
{
	Node* pt_left = pt->left;
	pt->left = pt_left->right;
	if (pt->left != NULL)
	{
		pt->left->parent = pt;
	}
	pt_left->parent = pt->parent;
	if (pt->parent == NULL) root = pt_left;
	else if (pt == pt->parent->left)
	{
		pt->parent->left = pt_left;
	}
	else pt->parent->right = pt_left;
	pt_left->right = pt;
	pt->parent = pt_left;
}

void swapColor(Color& a, Color& b)
{
	Color temp;
	temp = a;
	a = b;
	b = temp;
}

void RBTree::fixViolation(Node*& root, Node*& pt)
{
	Node* parent_pt = NULL;
	Node* grand_parent_pt = NULL;
	while (pt != root && pt->color != BLACK && pt->parent->color == RED)
		//con thuc hien neu nut cha va nut ong noi co cung mau do
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;
		if (grand_parent_pt == NULL) return;
		//A: nút cha là nút trái
		if (parent_pt == grand_parent_pt->left)
		{
			Node* uncle = grand_parent_pt->right;
			//th1 node uncle->red
			if(uncle!=NULL&&uncle->color==RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle->color = BLACK;
				pt = grand_parent_pt;
			}
			//th2 node uncle--> black
			else
			{
				// nếu pt là nút phải của cha nó
				if (pt == parent_pt->right)
				{
					leftRotate(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				//th3 pt là nút trái của cha nó
				rightRotate(root, grand_parent_pt);
				swapColor(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
		//B : nút cha là nút bên phải
		else
		{
			Node* uncle = grand_parent_pt->left;
			//th1 nút chú cũng có màu đỏ
			if (uncle != NULL && uncle->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				//th2
				//khi đó nút chú màu đen 
				//pt là con trái của pt.
				if (pt == parent_pt->left)
				{
					rightRotate(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				//th3
				//pt là con phải của pt
				leftRotate(root, grand_parent_pt);
				swapColor(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
		root->color = BLACK;
	}

}

void RBTree::insertNode(const int& value)
{
	Node* p = new Node(value);
	insertBST(root, p);
	fixViolation(root, p);
}

void RBTree::inorder()
{
	inorderHelper(root);
}

void RBTree::levelOrder()
{
	levelorderHelper(root);
}

int main()
{
	int a[] = { 7,6,5,4,3,2,1 };
	int n = sizeof(a) / sizeof(a[0]);
	RBTree root;
	for (int i = 0; i < n; i++)
	{
		root.insertNode(a[i]);
	}
	root.inorder();
}