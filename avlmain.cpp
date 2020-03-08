#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


#include "stacks.h"
#include "myconsole.h"
#include "mygraphics.h"
#include "avl.h"

using namespace std;


int main()
{
	int j=10;

	/*avltree<int> tree;
	tree.createSampleTree(30,15,35);
	tree.printTree();
	cin >> j;*/	
	avltree<int> tree;
	tree.insert(100);
	tree.insert(100);
	tree.insert(90);
	tree.insert(90);
	
	tree.insert(80);
	tree.insert(80);
	tree.insert(70);
	tree.insert(70);
	tree.insert(60);
	tree.insert(60);
	tree.insert(75);
	tree.insert(75);
	
	tree.insert(50);
	
	tree.insert(40);
	tree.insert(100);
	tree.insert(30);
	tree.deleteKey(40);
	tree.printTree();
	cin>>j;

}
