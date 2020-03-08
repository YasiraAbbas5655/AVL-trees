#include <iostream>
#include <math.h>

int const MAXSTRING = 500;

template <class type>
void avltree<type>::printTree()
{
	myRect(0, 0,800,500,RGB(255,255,255),RGB(255,255,255));
	printPreorder(root,0,600,0,1);

}

//will print in preorder
template <class type>
void avltree<type>::printPreorder(avlnode<type> *n,int minx,int maxx,int y,int ht)
{
	if (!n) return;
	int width = 30;
	int down = 25;
	COLORREF red = RGB(255,0,0);
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(0,0,0);
	COLORREF yellow = RGB(0,255,255);
	int x=(minx+maxx)/2;

	if (n->child[LEFT])
		myLine(x,y,(x+minx)/2,y+down,yellow);
	if (n->child[RIGHT])
		myLine(x,y,(x+maxx)/2,y+down,yellow);
	

	char str[MAXSTRING];
	char str1[MAXSTRING];
	_itoa_s(n->data,str,10);
	_itoa_s(n->height,str1,10);
	strcat(str,"(");			//uncomment this line if you want to print the node data and its height
	strcat(str,str1);			//uncomment this line if you want to print the node data and its height
	strcat(str,")");			//uncomment this line if you want to print the node data and its height
	COLORREF colour = black;

	myDrawText(x,y,20,str,colour,white);

	//recursive
	printPreorder(n->child[LEFT], minx,x,y+down,ht+1);
	printPreorder(n->child[RIGHT],x,maxx,y+down,ht+1);
}


template <class type>
bool avltree<type>::createRoot(type item)
{
	root = new avlnode<type>;
	root->data = item;
	root->height = 0;
	return true;
}

template <class type>
bool avltree<type>::findInsertionPoint(stack<avlnode<type>*> &nodeStack,stack<int> &directionStack,type value)
{
	//here find the insertion point and the direction you traversed to reach this point
	avlnode<type>* current=root;
	while (current)
	{
		if (value==current->data)
		{
			return false;
		}
		else if (value>current->data)
		{
			nodeStack.push(current);
			directionStack.push(RIGHT);
			current=current->child[RIGHT];
		}
		else
		{
			nodeStack.push(current);
			directionStack.push(LEFT);
			current=current->child[LEFT];

		}
		
	}
	return true;
}

//check the 2 single rotate cases here
template <class type>
void avltree<type>::rotateSingle(stack<avlnode<type>*> &nodeStack,stack<int> &directionStack,avlnode<type> *n,int nChildDirection)
{
	avlnode<type> *parent=NULL;	//parent of n
	int pChildDirection = 0;	//direction (between parent and n)
	nodeStack.pop(parent);		//parent is NULL if stack is empty.  No need to set anything here or check if stack is empty
	directionStack.pop(pChildDirection);

	if (nChildDirection == RIGHT)
		rotateLeft(n,parent,pChildDirection);
	else
		rotateRight(n,parent,pChildDirection);

}

//check the 2 double rotate cases here
template <class type>
void avltree<type>::rotateDouble(stack<avlnode<type>*> &nodeStack,stack<int> &directionStack,avlnode<type> *n,int nChildDirection)
{
	avlnode<type> *child = n->child[nChildDirection];
	directionStack.push(nChildDirection);	nodeStack.push(n);

	rotateSingle(nodeStack,directionStack,child,!nChildDirection);
	rotateSingle(nodeStack,directionStack,n,nChildDirection);
	
}

//current is the node whose balance is out of order
//parent is the parent of current
//don't forget to change heights
//also don't forget to change the root if needed
template <class type>
bool avltree<type>::rotateLeft(avlnode<type> *current,avlnode<type>*parent,int pChildDirection)
{
	if (current==root)
	{
		root=current->child[RIGHT];
	}
	avlnode<type> * right=current->child[RIGHT];
	if (parent)
	{
	parent->child[pChildDirection]=right;
	}
	avlnode<type>* right_left_child=nullptr;
	if (right!=nullptr)
	{
		right_left_child=right->child[LEFT];
		current->child[RIGHT]=right_left_child;
	}
	if (right)
	{
		right->child[LEFT]=current;
	}
	
	current->changeHeight();
	right->changeHeight();
	return true;
}

//current is the node whose balance is out of order
//parent is the parent of current
//don't forget to change heights
//also don't forget to change the root if needed
template <class type>
bool avltree<type>::rotateRight(avlnode<type> *current,avlnode<type>*parent,int pchilddirection)
{
		if (current==root)
	{
		root=current->child[LEFT];
	}
	avlnode<type> * left=current->child[LEFT];
	if (parent){
	parent->child[pchilddirection]=left;
	}
	avlnode<type>* left_right_child=nullptr;
	if (left!=nullptr)
	{
		left_right_child=left->child[RIGHT];
		current->child[LEFT]=left_right_child;
	}
	if (left)
	{
		left->child[RIGHT]=current;
	}
	
	current->changeHeight();
	left->changeHeight();
	return true;
}

template <class type>
bool avltree<type>::insert(type item)
{
	stack <avlnode<type>*> nodeStack;   //both stacks to be filled by findInsertionPoint
	stack <int> directionStack;
	avlnode<type> *parent=nullptr,*current = nullptr;

	
	
	
	//STEP 1:  check if no root exists then create it and exit the function
	if (root==nullptr)
	{
		createRoot(item);
		return true;
	}

	
	
	
	//STEP 2: call findInsertionPoint.  If insertionPoint not found exit the function
	bool success=findInsertionPoint(nodeStack,directionStack,item);
	if (!success)
	{
		return false;
	}
	
	
	
	
	//STEP 3: allocate memory for a new node
	avlnode<type> *newNode = new avlnode<type>(item);

	
	
	
	
	
	//STEP 4: pop the parent and insert the newNode in its correct place in the tree
	//you can do something like parent->child[pChildDirection] = newNode; 
	//the parent and pChildDirection should be popped from stack
	nodeStack.pop(parent);
	int pChildDirection;
	directionStack.pop(pChildDirection);
	parent->child[pChildDirection]=newNode;
	parent->changeHeight();


	
	
	//STEP 5: now adjust all the heights and perform rotations in all ancestors.  All ancestors are stored on the stack
	current = parent;			//isnertion point is the current node
	while(!nodeStack.empty())
	{
		
		nodeStack.pop(parent);//the parent of current node 
		directionStack.pop(pChildDirection);
		parent->changeHeight();//update height of parent
		if (parent->balanceFactor()<-1 || parent->balanceFactor()>1/* check wrong balance factor of parent here */)
		{	
			balance(nodeStack,directionStack,parent,pChildDirection);
			//check if you have to perform single or double rotation
			//call the functions corresponding to single rotation or double rotation. 
			//you need around 4-6 lines of code here
		}
		int currChildDirection;
		/*pChildDirection = currChildDirection;
		current = parent;*/

	}

	return true;
}


template <class type>
avlnode<type>* avltree<type>::findNode(type item,stack<avlnode<type>*> &nodeStack,stack<int> &directionStack)
{
	avlnode<type> *temp=root;
	while (temp->data!=item)
	{
		if (item>temp->data)
		{
			nodeStack.push(temp);
			directionStack.push(RIGHT);
			temp=temp->child[RIGHT];
		}
		else
		{
			nodeStack.push(temp);
			directionStack.push(LEFT);
			temp=temp->child[LEFT];

		}


	}
	return temp;
	//required by deleteKey function
	//return pointer to node to be deleted
}

template <class type>
type avltree<type>::findHighestKeyOnLeft(avlnode<type>*n)
{
	avlnode<type>* left=n->child[LEFT];
	while (left->child[RIGHT])
	{
		left=left->child[RIGHT];
	}
	return left->data;
	//return the data as the highest key on the left of n
}

template <class type>
bool avltree<type>::deleteKey(type item)
{
	
	bool done = false;
	stack <avlnode<type>*> nodeStack;
	stack <int> directionStack;
	avlnode<type> *n = nullptr;
	//STEP 1: call find node to find the node that stores the key to be deleted and store that pointer in n
	//the findNode function should also fill out the ancestor node pointers and the direction variables
	//return false if node is not found
	n=findNode(item,nodeStack,directionStack);
	//STEP 2: check if you are deleting the root and its the only node in the tree
	//deleting root
	if (n==root && n->totalChild()==0)
	{
		delete n;
		root=nullptr;
	}
	//STEP 3: check if n has two child nodes.  Call findHighetKeyOnLeft (saving its key) and call delteKey recursively
	if (n->totalChild()==2)
	{
		int maxkey=findHighestKeyOnLeft(n);
		deleteKey(maxkey);
		n->data=maxkey;
		return true;
	}

	////STEP 4 check if only one child
	////first check the parent and direction in which n is located
	avlnode<type>* parent=nullptr;
	int pChildDirection=0;
	nodeStack.peak(parent);
	directionStack.peak(pChildDirection);
	//STEP 5: deleting node with one child
	if (parent && n->totalChild() == 1)
	{
		if (n->child[LEFT])
			parent->child[pChildDirection] = n->child[LEFT];
		else
			parent->child[pChildDirection] = n->child[RIGHT];
		parent->changeHeight();
		delete n;
	}

	else if (parent)//deleting the leaf
	{
		parent->child[pChildDirection]=nullptr;
		parent->changeHeight();
		delete n;
		//set the correct links of parent to null
		//don't forget to deallocate n
	}
	else if (!parent)  //deleting root with one child
	{
		avlnode<type>*temp=root;
		if(root->child[LEFT])
		{
			root=root->child[LEFT];
			root->child[LEFT]=nullptr;
			delete temp;
		}
		else
		{
			root=root->child[RIGHT];
			root->child[RIGHT]=nullptr;
			delete temp;
		}
		
		//make sure you reset the root here
		//deallocate n
	}
	//STEP 6: update the heights and perform rotations if necessary
	avlnode<type>*current=nullptr;
	int currChildDirection=0;
	while(!nodeStack.empty())
	{

		nodeStack.pop(current);
		directionStack.pop(currChildDirection);
		current->changeHeight();
		if (current->balanceFactor()!=0 && current->balanceFactor()!=-1 && current->balanceFactor()!=1)
		{
			balance(nodeStack,directionStack,current,!currChildDirection);
			//call the balance method here
		}
	}
	return true;
}

////this function will balance the current node 
template <class type>
void avltree<type>::balance(stack <avlnode<type>*> nodestack,stack <int> directionstack, avlnode<type>*current, int currchilddirection)
{
	//these variables would be required.  initialize them yourself
	avlnode<type> *child = nullptr,*grandchild=nullptr,*parent=nullptr;
	int childdir=LEFT,grandchilddir=LEFT,pchilddirection=0;
	int htchildleft = -1, htchildright = -1;
	int htgrandchildleft = -1, htgrandchildright = -1;

	child=current->child[currchilddirection];
	nodestack.peak(parent);
	directionstack.peak(pchilddirection);
	childdir=currchilddirection;
	if (child->child[LEFT])
	{
		htchildleft=child->child[LEFT]->height;
	}
	if (child->child[RIGHT])
	{
		htchildright=child->child[RIGHT]->height;
	}
	if((htchildright-htchildleft)>0)
	{
		grandchild=child->child[RIGHT];
		grandchilddir=RIGHT;
	}
	else
	{
		grandchild=child->child[LEFT];
		grandchilddir=LEFT;
	}
	if (childdir==grandchilddir)
	{
		rotateSingle(nodestack,directionstack,current,currchilddirection);
	}
	else
	{
		rotateDouble(nodestack,directionstack,current,currchilddirection);
	}
	//call rotate methods here
}
////code will not check that leftVal is less than root and rightVal > rootVal.  But you can print the tree and check it
//template <class type>
//void avltree<type>::createSampleTree(type rootValue,type leftValue, type rightValue)
//{
//	root = new avlnode<type>(rootValue);
//	root->child[LEFT] = new avlnode<type>(leftValue);
//	root->child[RIGHT] = new avlnode<type>(rightValue);
//
//}
