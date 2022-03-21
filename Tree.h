#include<bits/stdc++.h>
#include "Node.h"

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
        root = NULL;
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
		while(*node != NULL and (*node) -> data != data)
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


	
	Node<T*> extract_min() {
		Node<T*> cur;
			cur = root;
		while(cur != NULL) {
			if(cur -> left) {
				cur = cur -> left;
			} else {
				return cur;
			}
		}
		return NULL;
	}
	Node<T*> extract_max() {
		Node<T*> cur;
		cur = root;
		while(root != NULL) {
			if(cur -> right) {
				cur = cur -> right;
			} else {
				return cur;
			}
		}
		return NULL;
	}
	
	Node<T*> left_neighbour(T data) {

	}

	Node<T*> right_neighbour(T data) {

	}


};