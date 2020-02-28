# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> myStack;
    stack<T> minVal;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return myStack.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return myStack.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if(!minVal.empty()){
        if(myStack.top()==minVal.top()){
            minVal.pop();
        }
    }
    myStack.pop();

}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if(minVal.empty() || minVal.top()>val){
        minVal.push(val);
    }
    myStack.push(val);
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return minVal.top();
}

