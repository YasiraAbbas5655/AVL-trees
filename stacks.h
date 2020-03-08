#ifndef STACKS_H
#define STACKS_H

const int MAXSIZE = 500;

template <class typeName>
class stack
{
public:
	stack(){index = 0;}
	bool push(typeName item);
	bool pop(typeName &item);
	bool peak(typeName &item);
	bool pop();
	bool empty();  //make the stack empty
	bool full();
	void initialize(){index=0;};
private:
	typeName arr[MAXSIZE];
	int index;
};

template <class typeName>
bool stack<typeName>::empty()
{
	if (index==0)
	{
		return true;
	}
	return false;
}

template <class typeName>
bool stack<typeName>::full()
{
	if (index==MAXSIZE)
	{
		return true;
	}
	return false;
}

template <class typeName>
bool stack<typeName>::push(typeName item)
{
	if (full())
	{
		return false;
	}
	
	 arr[index]=item;
	  index++;
	    
	
}

template <class typeName>
bool stack<typeName>::pop(typeName &item)
{
	if (empty())
	{
		return false;
	}
	index--;
	item=arr[index];
	
}

template <class typeName>
bool stack<typeName>::peak(typeName &item)
{
	if (empty())
	{
		return false;
	}
	item=arr[index-1];
}

//
//template <class typeName>
//bool stack<typeName>::pop()
//{
//	index--;
//}

#endif