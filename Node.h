#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Generic node class
 * 
 * @tparam T 
 */
template<class T>
class Node {
    public:
    Node *left; /// Pointer to the left child
    Node *right; /// Pointer to the right child
    T data; /// Data stored at the node
    int height; /// Height of subtree
    int cnt; /// Number of nodes in subtree

    /**
     * @brief Construct a new Node object
     * 
     * @param data 
     */
    Node(T data) {       
        left = NULL;
        right = NULL;
        height = 1;
        this -> data = data;
        cnt = 1;
    }

    /**
     * @brief method to update the height and count of tree while balancing 
     * 
     */
    void modify_height_and_cnt() {
        int l, c_l;
        if(left != NULL) {
            l = left -> height;
            c_l = left -> cnt;
        }
        else {
            l = 0;
            c_l = 0;
        }
    
        int r, c_r;
        if(right != NULL) {
            r = right -> height;
            c_r = right -> cnt;
        }
        else {
            r = 0;
            c_r = 0;
        }
        
        height = max(l,r) + 1;
        cnt = c_l + c_r + 1;
    }

    /**
     * @brief method to compute the height difference between the left and right subtree
     * 
     * @return int 
     */
    int height_difference_of_left_and_right_subtree() {
        int balance_factor, h_l, h_r;

        if(left != NULL)
            h_l = left -> height;
        else
            h_l = 0;

        if(right != NULL)
            h_r = right -> height;
        else
            h_r = 0;

        balance_factor = h_l - h_r;

        return balance_factor;
    }

    /**
     * @brief method to left rotate the subtree
     * 
     * @return Node* 
     */
    Node * left_rotate() {
		Node * R = right;
		right = right -> left;
		R -> left = this;
		this -> modify_height_and_cnt();
		R -> modify_height_and_cnt();
		return R;
	}

    /**
     * @brief method to right rotate the subtree
     * 
     * @return Node* 
     */
    Node * right_rotate() {
		Node * L = left;
		left = left -> right;
		L -> right = this;
		this -> modify_height_and_cnt();
		L -> modify_height_and_cnt();
		return L;
	}

};