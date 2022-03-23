#include<bits/stdc++.h>
#include "Node.h"
#include "Event.h"


template<class T>
class Tree
{
    //Todo:- AVL Tree
    //inserting nodes -- done
    //deleting nodes -- done
    //balance the tree -- done
    //find left neighbour
    //find right neighbour
    //..
    //..
    //whatever else that is required(?) while implementing bentley

    public:
    Node<T> * root;
    int no_of_nodes;

    Tree()
    {
        this -> root = NULL;
        no_of_nodes = 0;
    }

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

    void insert_node(T data)
	{
		vector< Node<T>** > path; 
		Node<T> **  node = &root;

		while((*node) != NULL)
		{
			path.push_back(node);
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
		path.push_back(node);

		balance(path);
		no_of_nodes++;
	} 



    void delete_node(T data)
	{
		Node<T> ** node = &root;
		vector< Node<T> ** > path;
		while((*node) != NULL && (*node) -> data != data)
		{
			path.push_back(node);
	
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
			path.push_back(node);
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
				path.push_back(successor);
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


	
	T* extract_min() {
		Node<T> *current = root;
		while(current) {
			if(current -> left) {
				current = current -> left;
			} else {
				return &current->data;
			}
		}
		return NULL;
	}
	T* extract_max() {
		Node<T*> current;
		current = root;
		while(current) {
			if(current -> right) {
				current = current -> right;
			} else {
				return current -> data;
			}
		}
		return NULL;
	}
	
	T * left_neighbour(T data) {
		T* left = NULL;
		Node<T> *current = root;
		while(current) {
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

		if(current) //find rightmost node in left subtree
		{
			current = current -> left;
			while(current)
			{
				left = &current -> data;
				current = current -> right;
			}
		}
		return left;
	}

	T * right_neighbour(T data) {
		T* right = NULL;
		Node<T> *current = root;
		vector < Node <T> ** > path;
		while(current) {
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

		if(current) //find rightmost node in left subtree
		{
			current = current -> right;
			while(current) {
				right = &current -> data;
				current = current -> left;
			}
		}
		return right;
	}

	T* lowerBound(T data) {
		Node <T*> current = root;
		T* node = NULL;

		while(current) {
			if(current -> data < data) {
				current = current -> right;
			} else {
				node = &current -> data;
				current = current -> left;
			}
		}

		return node;
	}

	T* upperBound(T data) {
		Node <T> ** current = &root;
		T* node = NULL;

		while(*current) {
			if((*current) -> data > data) {
				node = &(*current) -> data;
				current = &(*current) -> left;
			} else {
				current = &(*current) -> right;
			}
		}
		return node;
	}

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

		if(size == 0) {
			cout << "No node to delete" << endl;
		}
		path.resize(size);
		current = path[size - 1];

		if(*current) {
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

		//delete_node(&upperBound(data)->data);

		return;
	}

	bool search(T data) {
		Node<T> *current = root;
		while(current)
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


	void display(Node<T> *cur,int depth = 0,int state = 0)
	{
		if (cur->left)
		    display(cur->left, depth + 1, 1);
		    
		    for (int i=0; i < depth; i++)
		        printf("     ");
		    
		    if (state == 1) // left
		        printf("┌───");
		    else if (state == 2)  // right
		        printf("└───");
		    
		    cout << "[" << cur->data.A.x << " " << cur->data.A.y << " " << cur->data.B.x << " " << cur->data.B.y << "] - (" << cur->cnt << ", "  << cur -> height << ")" << endl;
			// cout << "[" << cur->data.P.x << " " << cur->data.P.y << "] - (" << cur->cnt << ", "  << cur -> height << ")" << endl;
		    
		    if (cur->right)
		display(cur->right, depth + 1, 2);
	}

	void display()
	{
		cout << endl;
		if(root != NULL)
			display(root);
		else
			cout << "Empty" << endl;

	} 	


};