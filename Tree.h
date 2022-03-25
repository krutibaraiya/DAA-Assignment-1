#include<bits/stdc++.h>
#include "Node.h"
#include "Event.h"

/**
 * @brief Generic tree class
 * 
 * @tparam T 
 */
template<class T>
class Tree
{

    public:
    Node<T> * root; /// pointer to the root node of the tree
    int no_of_nodes; /// number of nodes in the tree

	/**
	 * @brief Construct a new Tree object
	 * 
	 */
    Tree()
    {
        this -> root = NULL;
        no_of_nodes = 0;
    }

	/**
	 * @brief method to balance the tree
	 * 
	 * @param path path of the tree to be balanced
	 */
    void balance(vector< Node<T> ** > path)
	{
		reverse(path.begin(),path.end());
		for (auto node : path)
		{
			
			(*node) -> modify_height_and_cnt();

			if((*node) -> height_difference_of_left_and_right_subtree() >= 2 && (*node) -> left -> height_difference_of_left_and_right_subtree() >= 0)
				(*node) = (*node) -> right_rotate();
			else if((*node)->height_difference_of_left_and_right_subtree() <= -2 and (*node)->right->height_difference_of_left_and_right_subtree() <= 0)
				(*node) = (*node) -> left_rotate();
			else if((*node)->height_difference_of_left_and_right_subtree() >= 2)
			{
				(*node)->left = (*node) -> left->left_rotate();
				(*node) = (*node) -> right_rotate();
			}
			else if ((*node)->height_difference_of_left_and_right_subtree() <= -2)
			{
				(*node) -> right = (*node) -> right -> right_rotate();
				(*node) = (*node) -> left_rotate();
			}

		}
	}

	/**
	 * @brief method to insert a new node into the tree
	 * 
	 * @param data data to be stored in the new node
	 */
    void insert_node(T data)
	{
		vector< Node<T>** > path; 
		Node<T> **  node = &root;

		while((*node) != NULL)
		{
			path.emplace_back(node);
			if((*node) -> data > data)
            {
				node = &((*node) -> left);
            }
			else
            {
				node = &((*node) -> right);
            }
		}	
		*node = new Node<T>(data);
		path.emplace_back(node);

		balance(path);
		no_of_nodes++;
	} 


	/**
	 * @brief method to delete a node from the tree
	 * 
	 * @param data data of the node to be deleted from the tree
	 */
    void delete_node(T data)
	{
		Node<T> ** node = &root;
		vector< Node<T> ** > path;
		while((*node) != NULL && (*node) -> data != data)
		{
			path.emplace_back(node);
	
			if((*node) -> data > data)
				node = & (*node)->left;
			else
				node = & (*node)->right;
		}
		if(*node == NULL)
		{
			return ;
		}
		else
        {
			path.emplace_back(node);
        }
		
        int pathsize = path.size();
		
		if((*node) -> left == NULL and (*node) -> right == NULL)
		{
			delete *node;
			*node = NULL;
			path.pop_back();
		}

		else if((*node) -> right == NULL)
		{
			Node<T> * to_delete = *node;
			*node = (*node) -> left;
			delete to_delete;
			path.pop_back();
		}
		else
		{
			Node<T> ** successor  = & ((*node) -> right);
			while((*successor) -> left != NULL)
			{
				path.emplace_back(successor);
				successor = &((*successor) -> left);
			}
			if(*successor == (*node) -> right)
			{
				(*successor) -> left = (*node) -> left;
				Node<T> * to_delete = *node;
				*node = *successor;
				delete to_delete;
			}
			else
			{
				Node<T> *temp = *path.back(),*suc = *successor;
				temp -> left = (*successor) -> right;
				suc -> left = (*node) -> left;
				suc -> right = (*node) -> right;
				delete *node;
				*node = suc;
				path[pathsize] = & (suc -> right);
			}

		}
		balance(path);
		no_of_nodes--;
	}


	/**
	 * @brief method to extract the node with minimum value from the tree
	 * 
	 * @return T* 
	 */
	T* extract_min() {
		Node<T> *current = root;
		while(current != NULL) {
			if(current -> left) {
				current = current -> left;
			} else {
				return &current->data;
			}
		}
		return NULL;
	}

	/**
	 * @brief method to extract the node with maximum value from the tree
	 * 
	 * @return T* 
	 */
	T* extract_max() {
		Node<T*> current;
		current = root;
		while(current != NULL) {
			if(current -> right) {
				current = current -> right;
			} else {
				return current -> data;
			}
		}
		return NULL;
	}
	
	/**
	 * @brief method to find the left neighbour of a particular node
	 * 
	 * @param data data of the node whose left neighbour is to be found
	 * @return T* 
	 */
	T * left_neighbour(T data) {
		T* left = NULL;
		Node<T> *current = root;
		while(current != NULL) {
			if(current-> data == data) {
				break;
			}

			if(current -> data < data) {
				
				left = &current -> data;
				current = current -> right;
			} else {
				current = current -> left;
			}
		}

		if(current != NULL) ///find rightmost node in left subtree
		{
			current = current -> left;
			while(current != NULL)
			{
				left = &current -> data;
				current = current -> right;
			}
		}
		return left;
	}

	/**
	 * @brief method to find the right neighbour of a particular node
	 * 
	 * @param data data of the node whose right neighbour is to be found
	 * @return T* 
	 */
	T * right_neighbour(T data) {
		T* right = NULL;
		Node<T> *current = root;
		vector < Node <T> ** > path;
		while(current != NULL) {
			if(current-> data == data) {
				break;
			}

			if(current -> data < data) {
				current = current -> right;
			} else {
				right = &current -> data;
				current = current -> left;
			}
		}

		if(current != NULL) ///find rightmost node in left subtree
		{
			current = current -> right;
			while(current != NULL) {
				right = &current -> data;
				current = current -> left;
			}
		}
		return right;
	}

	/**
	 * @brief method to find the lower bound of a particular node
	 * 
	 * @param data data of the node whose lower bound is to be found
	 * @return T* 
	 */
	T* lowerBound(T data) {
		Node <T*> current = root;
		T* node = NULL;

		while(current != NULL) {
			if(current -> data < data) {
				current = current -> right;
			} else {
				node = &current -> data;
				current = current -> left;
			}
		}

		return node;
	}

	/**
	 * @brief method to find the upper bound of a particular node
	 * 
	 * @param data data of the node whose upper bound is to be found	
	 * @return T* 
	 */
	T* upperBound(T data) {
		Node <T> ** current = &root;
		T* node = NULL;

		while(*current != NULL) {
			if((*current) -> data > data) {
				node = &(*current) -> data;
				current = &(*current) -> left;
			} else {
				current = &(*current) -> right;
			}
		}
		return node;
	}

	/**
	 * @brief method to find the upper bound and delete that node 
	 * 
	 * @param data data of the node whose upper bound is to be found and delete
	 */
	void deleteUpperBound(T data) {
		Node <T> ** current = &root;
		vector< Node <T> ** > path;
		int size;

		while(*current) {
			path.push_back(current);

			if((*current) -> data > data) {
				size = path.size();
				current = &(*current) -> left;
			} else {
				current = & (*current) -> right;
			}
		}

		
		path.resize(size);
		current = path[size - 1];
		if(*current == NULL) {
			cout << "value not found in upper bound and delete" << endl;
			cout << data.index << endl;
			assert(1 == 2);
			return ;
		}
		int pathsize = path.size();
		if((*current) -> left == NULL && (*current) -> right == NULL) {
			delete *current;
			*current = NULL;
			path.pop_back();
		} else if((*current) -> right == NULL) {
			Node <T> *toRemove = *current;
			*current = (*current) -> left;
			delete toRemove;
			path.pop_back();
		} else {
			Node <T> **successor = &((*current) -> right);
			while((*successor) -> left) {
				path.push_back(successor);
				successor = &(*successor) -> left;
			}
			if(*successor == (*current) -> right) {
				(*successor) -> left = (*current) -> left;
				Node <T> *toRemove = *current;
				*current = *successor;
				delete toRemove;
			} else {
				Node <T> *temp = *path.back(), *suc = *successor;
				temp -> left = (*successor) -> right;
				suc -> left = (*current) -> left;
				suc -> right = (*current) -> right;
				delete *current;
				*current = suc;
				path[pathsize] = &(suc -> right);
			}
		}
		balance(path);
		no_of_nodes--;

		// T* node = upperBound(data);
		// if(node == NULL) {
		// 	return ;
		// }
		// T value = (*node);
		// delete_node(value); 

		return;
	}

	/**
	 * @brief method to search a particular node in the tree
	 * 
	 * @param data data of the node to be searched
	 * @return true if node is found
	 * @return false if node is not found
	 */
	bool search(T data) {
		Node<T> *current = root;
		while(current != NULL)
		{
			if(current -> data == data)
				return true;
			if(current -> data < data)
			{
				current = current -> right;
			}
			else
			{
				current = current -> left;
			}
		}
		return 0;
	}
};