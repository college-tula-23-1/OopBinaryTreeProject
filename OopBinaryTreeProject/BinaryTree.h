#pragma once

template <typename T>
class IComparator
{
public:
	virtual int Compare(T left, T right) = 0;
	virtual int operator()(T left, T right) = 0;
};


template <typename T>
class BinaryTree
{
	template <typename T>
	struct Node
	{
		T value;
	//private:
		Node<T>* parent = nullptr;
		Node<T>* left = nullptr;
		Node<T>* right = nullptr;
	};

	Node<T>* root;
	int count;

	IComparator<T>* comparator;

public:
	BinaryTree(IComparator<T>* comparator = nullptr)
		: root{}, count{} 
	{
		if (comparator != nullptr)
			this->comparator = comparator;
	}
	~BinaryTree();

	Node<T>* CreateNode(Node<T>* parent, T value);

	void InsertLoop(T value);
	void InsertReq(T value, Node<T>* node = nullptr);

	void RemoveNode(Node<T>* node);
	void RemoveBranch(Node<T>* node);

	Node<T>* Find(T value);

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
void BinaryTree<T>::InsertLoop(T value)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		count = 1;
		return;
	}

	Node<T>* nodeCurrent = root;
	Node<T>* nodeParent = nullptr;

	while (nodeCurrent)
	{
		nodeParent = nodeCurrent;
		/*if (value < nodeCurrent->value)*/
		if(comparator->Compare(value, nodeCurrent->value) < 0)
			nodeCurrent = nodeCurrent->left;
		else
			nodeCurrent = nodeCurrent->right;
	}

	nodeCurrent = CreateNode(nodeParent, value);
	/*if (nodeCurrent->value < nodeParent->value)*/
	if(comparator->Compare(nodeCurrent->value, nodeParent->value) < 0)
		nodeParent->left = nodeCurrent;
	else
		nodeParent->right = nodeCurrent;

	count++;
}

template<typename T>
inline void BinaryTree<T>::InsertReq(T value, Node<T>* node)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		count = 1;
		return;
	}

	if (!node)
		node = root;

	if ((*comparator)(value, node->value) < 0)
	{
		if (node->left)
			InsertReq(value, node->left);
		else
		{
			node->left = CreateNode(node, value);
			count++;
		}
			
	}
	else
	{
		if (node->right)
			InsertReq(value, node->right);
		else
		{
			node->right = CreateNode(node, value);
			count++;
		}	
	}
}

template<typename T>
inline void BinaryTree<T>::RemoveNode(Node<T>* node)
{
	// delete leaf
	if (!node->left && !node->right)
	{
		if (node == root)
			root = nullptr;
		else
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}
		delete node;
		count--;
		return;
	}

	// delete node with one child
	if ((bool)node->left ^ (bool)node->right)
	{
		Node<T>* child;
		child = (node->left) ? node->left : node->right;

		if (node == root)
			root = child;
		else
		{
			if (node == node->parent->left)
				node->parent->left = child;
			else
				node->parent->right = child;
		}

		delete node;
		count--;
		return;
	}

	Node<T>* nodeMinRight = Min(node->right);
	node->value = nodeMinRight->value;
	RemoveNode(nodeMinRight);
}

template<typename T>
inline void BinaryTree<T>::RemoveBranch(Node<T>* node)
{
	if (node->left)
		RemoveBranch(node->left);
	if (node->right)
		RemoveBranch(node->right);

	if (node != root)
	{
		if (node->parent->left == node)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
	}

	delete node;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Find(T value)
{
	Node<T>* node{ root };
	while (node)
	{
		if (value == node->value)
			break;
		if (value < node->value)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Min(Node<T>* node)
{
	if (!node)
		node = root;

	while (node->left)
		node = node->left;

	return node;
}

template<typename T>
inline BinaryTree<T>::Node<T>* BinaryTree<T>::Max(Node<T>* node)
{
	if (!node)
		node = root;

	while (node->right)
		node = node->right;

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

template<typename T>
void BinaryTree<T>::PrintBranch(Node<T>* node)
{
	if (node)
	{
		PrintBranch(node->left);
		std::cout << node->value << " " << "\n";
		PrintBranch(node->right);
	}
}

template<typename T>
void BinaryTree<T>::Print()
{
	PrintBranch(root);
}


