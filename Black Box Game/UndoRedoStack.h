#pragma once

#pragma once

template<class Type, int size = 1>

//In Undo Redo stack we move elements from the bottom to the top, popping top
//We do not have stack overflow, but rather stack_underflow
class UndoRedoStack
{
	Type stack[size];
	int top = -1;

private:
	void moveElementsToBottom()
	{
		for (int x = 0; x < size - 1; x++)
			stack[x] = stack[x + 1];
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
			return Type();

		return stack[top--];
	}

	Type getTop()
	{
		if (top < 0)
			return Type();

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
