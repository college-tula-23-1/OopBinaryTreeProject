#pragma once

template <typename T>
class BinaryTree
{
	template <typename T>
	struct Node
	{
		T value;
		Node<T>* parent = nullptr;
		Node<T>* left = nullptr;
		Node<T>* right = nullptr;
	};

	Node<T>* root;
	int count;

public:
	BinaryTree() : root{}, count{} {}
	~BinaryTree();

	Node<T>* CreateNode(Node<T>* parent, T value);

	InsertLoop(T value);
	InsertReq(T value);

	RemoveNode(Node<T>* node);
	RemoveBranch(Node<T>* node);

	Node<T>* Min(Node<T>* node = nullptr);
	Node<T>* Max(Node<T>* node = nullptr);

	int Count() const;
	Node<T>* Root() const;

	bool Contains(T value);

	void PrintBranch(Node<T>* node);
	void Print();
};


template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	RemoveBranch(root);
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::CreateNode(Node<T>* parent, T value)
{
	Node<T>* node = new Node<T>;
	node->value = value;
	node->parent = parent;
	return node;
}

template<typename T>
inline int BinaryTree<T>::Count() const
{
	return count;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Root() const
{
	return root;
}
