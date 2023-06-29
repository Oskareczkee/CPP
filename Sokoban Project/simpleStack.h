#pragma once

template<class Type, int size=1>

//this is not standard implementation, in this implementation we do not have stack overflow, because we move elements to bottom and pop top
class  Stack
{
	Type stack[size];
	int top = -1;

private:
	void moveElementsToBottom()
	{
		for (int x = 0; x <size-1; x++)
			stack[x] = stack[x+1];
	}
public:

	void push(const Type t)
	{
		if (top >= size - 1)
		{
			moveElementsToBottom();
			stack[top] = t;
			return;
		}

		 top++;
		 stack[top] = t;
	}

	Type pop()
	{
		if (top < 0)
			throw underflow_error("Stack underflow error!");

		return stack[top--];
	}

	Type getTop()
	{
		if (top < 0)
			throw underflow_error("Stack underflow error!");

		return stack[top];
	}

	bool isEmpty()
	{
		return top < 0;
	}

	void clear()
	{
		top = -1;
	}
};