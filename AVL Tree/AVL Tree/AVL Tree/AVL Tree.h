#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class AVLTree
{
	private:
		class Node
		{
			public:
				Node* left;
				Node* right;
				T content;
				//int balanceFactor;

				Node():left(nullptr), right(nullptr){}
				Node(Node* _left, Node* _right): left(_left), right(_right){}
				Node(T& val):content(val), left(nullptr), right(nullptr){}
				~Node()
				{
					delete left;
					delete right;
				}

				Node& operator=(const Node& other)
				{
					if (this == &other)
						return *this;

					this->right = other.right;
					this->left = other.left;
					this->content = other.content;

					return *this;
				}
		};

		Node* root = nullptr;

		Node* rightRightRotation(Node* parent)
		{
			Node* n = parent->right;
			parent->right = n->left;
			n->left = parent;

			return n;
		}

		Node* leftLeftRotation(Node* parent)
		{
			Node* n=parent->left;
			parent->left = n->right;
			n->right = parent;

			return n;
		}

		Node* leftRightRotation(Node* parent)
		{
			Node* n = parent->left;
			parent->left = rightRightRotation(n);

			return leftLeftRotation(parent);
		}

		Node* rightLeftRotation(Node* parent)
		{
			Node* n = parent->right;
			parent->right = leftLeftRotation(n);

			return rightRightRotation(parent);
		}

public:

		int calculateHeight(Node* rootNode)
		{
			int height = 0;
			if (rootNode != nullptr)
			{
				int left_height = calculateHeight(rootNode->left);
				int right_height = calculateHeight(rootNode->right);
				height = std::max(left_height, right_height) + 1;
			}

			return height;
		}

		int calculateBalanceFactor(Node* rootNode)
		{
			int left_height = calculateHeight(rootNode->left);
			int right_height = calculateHeight(rootNode->right);

			return left_height - right_height;
		}

		int getTreeHeight()
		{
			return calculateTreeHeight();
		}
private:

	int calculateTreeHeight()
	{
		return calculateHeight(root);
	}

		Node* balance(Node* parent)
		{
			if (parent == nullptr)
				return nullptr;

			int balanceFactor = calculateBalanceFactor(parent);
			
			//perform rotations
			//node is right heavy

			if (balanceFactor > 1)
			{
				if (calculateBalanceFactor(parent->left) > 0)
					parent = leftLeftRotation(parent);
				else
					parent = leftRightRotation(parent);
			}
			//node is left heavy
			else if (balanceFactor < -1)
			{
				if (calculateBalanceFactor(parent->right) > 0)
					parent = rightLeftRotation(parent);
				else
					parent = rightRightRotation(parent);
			}

			return parent;
		}

		Node* insert(Node* rootNode, T val)
		{
			if (rootNode == nullptr)
			{
				rootNode = new Node(val);
				return rootNode;
			}
			else if (val < rootNode->content)
			{
				rootNode->left =insert(rootNode->left, val);
				rootNode = balance(rootNode);
			}
			else if (val >= rootNode->content)
			{
				rootNode->right = insert(rootNode->right, val);
				rootNode = balance(rootNode);
			}

			return rootNode;
		}


		//cannot use just delete, cause it is keyword
		Node* deleteNode(Node* rootNode, T val)
		{
			if (rootNode == nullptr)
				return nullptr;

			if (rootNode->content < val)
				rootNode->right = deleteNode(rootNode->right, val);
			else if (rootNode->content > val)
				rootNode->left = deleteNode(rootNode->left, val);

			//value has been found
			else
			{
				if (rootNode->left == nullptr && rootNode->right == nullptr)
					rootNode = nullptr;
				else if (rootNode->left == nullptr)
				{
					rootNode->content = findLeft(rootNode->right)->content;
					rootNode->right = deleteNode(rootNode->right, rootNode->content);
				}
				else
				{
					rootNode->content = findRight(rootNode->left)->content;
					rootNode->left = deleteNode(rootNode->left, rootNode->content);
				}
			}

			return balance(rootNode);
		}

		//finds last left node of given root
		Node* findLeft(Node* rootNode)
		{
			if (rootNode == nullptr)
				return rootNode;

			while (rootNode->left != nullptr)
				rootNode = rootNode->left;
			return rootNode;
		}

		//finds last right node of given root
		Node* findRight(Node* rootNode)
		{
			if (rootNode == nullptr)
				return rootNode;

			while (rootNode->right != nullptr)
				rootNode = rootNode->right;
			return rootNode;
		}

		Node* find(Node* rootNode, T val)
		{
			if (rootNode == nullptr)
				return nullptr;

			if (rootNode->content == val)
				return rootNode;
			else if (val < rootNode->content)
				rootNode=find(rootNode->left, val);
			else if (val > rootNode->content)
				rootNode=find(rootNode->right, val);

			return rootNode;
		}

		void printContent(Node* rootNode)
		{

			if (rootNode != nullptr)
			{
				cout << rootNode->content<<"("<<calculateBalanceFactor(rootNode)<<")"<<"\n";
			}
			else
				return;
			printContent(rootNode->left);
			printContent(rootNode->right);
		}

		void saveToFile(Node* rootNode, ofstream& os)
		{
		
			if (rootNode != nullptr)
			{
				os << rootNode->content << "(" << calculateBalanceFactor(rootNode) << ")" << "\n";
			}
			else
				return;
			saveToFile(rootNode->left, os);
			saveToFile(rootNode->right, os);
		}


public:

	//we do insert like in normal BST, but we do balance at the end
	Node* insert(T val)
	{
		root = insert(root, val);
		return root;
	}

	Node* deleteNode(T val)
	{
		root=deleteNode(root, val);
		return root;
	}

	Node* find(T val)
	{
		return find(root, val);
	}

	void printContent()
	{
		printContent(root);
	}

	void clear()
	{
		delete root;
		root = nullptr;
	}

	void saveToFile(const string& fileName)
	{
		ofstream of{ fileName };

		saveToFile(root, of);
	}
	vector<T> getContent(Node* rootNode)
	{
		static vector<T> output;

		if (rootNode != nullptr)
		{
			getContent(rootNode->left);
			getContent(rootNode->right);
			output.push_back(rootNode->content);
		}

		return output;
	}

};
