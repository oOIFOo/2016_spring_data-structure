#include<iostream>
using namespace std;

class node{
public:
	node();
	node(int value);
	~node();
	friend void gothrough(node *p);

private:
	node *left, *right; // the left child and the right child pointer
	int number; // record the node's number
	int is_threadl, is_threadr; //the flag to record whether the pointer is a thread or not

	friend class op_tree_totum;//you could access all valuables in class op_tree_totum
};

//ctor
node::node(){
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//ctor
node::node(int value){
	number = value;
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//dtor
node::~node(){

}

class op_tree_totum{

public:
	op_tree_totum();
	~op_tree_totum();
	void insertion(int s);
	void deletion(int s);
	void inorder_run();
	void reverseorder_run();
	int size();

private:
	node *root, *head, *tail;
	int num;//caculate how many nodes in the totum
};

//ctor
op_tree_totum::op_tree_totum(){
	head = new node();
	tail = new node();
	head->right = tail; //initialize the head node to connect to the tail node
	tail->left = head;
	root = NULL;
	num = 0;
}

//dtor
op_tree_totum::~op_tree_totum(){
	node *p = root;
	if(p!=NULL)	gothrough(p);
	num = 0;
	if (head != NULL)delete head;
	if (tail != NULL)delete tail;
}

void gothrough(node *p){
	if (p->is_threadl==0 && p->left!= NULL) gothrough(p->left);
	if (p->is_threadr==0 && p->right!= NULL) gothrough(p->right);
	delete p;
}

void op_tree_totum::insertion(int s){
	//TODO: fill in the code to do the insertion of the node with number s
	int flag = 0;
	node *idx, *tmp;
	idx = root;
	tmp = new node;
	while(flag == 0){
	//	cout << "s = " << s << endl;
	//	if(root != NULL)cout << idx -> number << " " << s << endl;
	//	system("pause");
	
		if(root == NULL) {
			root = new node;
			root -> number = s;
			root -> right = NULL;
			root -> left = NULL;
			head = root;
			tail = root;
			flag = 1;
		}
		else if(s > idx -> number){
			if(idx -> is_threadr == 0) idx = idx -> right;
			else {
				tmp -> number = s;
				tmp -> left = idx;
				tmp -> right = idx -> right;
				idx -> right = tmp;
				idx -> is_threadr = 0;
				flag = 1;
				if(tmp -> right == NULL){
					tail = tmp;
				}
			}
		}
		else if(s < idx -> number){
			if(idx -> is_threadl == 0) idx = idx -> left;
			else {
				tmp -> number = s;
				tmp -> right = idx;
				tmp -> left = idx -> left;
				idx -> left = tmp;
				idx -> is_threadl = 0;
				flag = 1;
				if(tmp -> left == NULL){
					head = tmp;
				}
				//cout << head -> number << endl;
			}
		}
	}
//	delete tmp;
//	delete idx;
}

void op_tree_totum::deletion(int s){
	//TODO: fill in the code to do the deletion of the node with number s
	int flag = 0;
	node *find_root;
	node *idx_root, *point_to_idx, *idx, *debug;
	node *find = root;
	while(flag == 0){////find "find"
		find_root = find;
	//	cout << s << find -> number << " ";
		if(s > find -> number) {
			if(find -> is_threadr == 0) find = find -> right;
			else flag = -1;
		}
		else if(s < find -> number){
			if(find -> is_threadl == 0) find = find -> left;
			else flag = -1;
		}
		if(s == find -> number) {
			flag = 1;
		}
	}
//	cout << find -> number;
	if(flag == 1){
		if(find -> is_threadr == 1 && find -> is_threadl == 1){//find is leaf
			if(find == root) root = NULL;
			else {
				if(find_root -> right == find){
					find_root -> right = find -> right;
					find_root -> is_threadr = 1;
					if(tail == find) tail = find_root;
				}
				else{
				//	cout << find_root -> number;
					find_root -> left = find -> left;
					find_root -> is_threadl = 1;
					if(head == find) head = find_root;
				}
			}
		}
		else{//find is NOT leaf
			if(find -> is_threadl == 0){//find have left child
				idx = find -> left;
				while(idx -> is_threadr == 0){
					idx_root = idx;
					idx = idx -> right;
				}
				if(idx -> is_threadr == 1){//idx must only have left child;
					if(find -> left == idx){
						if(idx -> left == NULL){
							find -> number = idx -> number;
							find -> left = NULL;
							find -> is_threadl = 1;
							head = find;
						}
						else if(idx -> left != NULL){
							find -> number = idx -> number;
							if(find == find_root -> left){
								find_root -> left = find -> left;
								idx -> right = find -> right;
								idx -> is_threadr = find -> is_threadr;
								idx_root = idx;
								if(find -> is_threadr == 0){
									idx = find -> right;
									while(idx -> is_threadl == 0){
										idx = idx -> left;
									}
									idx -> left = idx_root;
								}
								idx = find -> right;
								while(idx -> is_threadl == 0){
									idx = idx -> left;
								}
							}
							else if(find == find_root -> right){
								find_root -> right = find -> left;
								idx -> right = find -> right;
								idx -> is_threadr = find -> is_threadr;
								idx_root = idx;
								if(find -> is_threadr == 0){
									idx = find -> left;
									while(idx -> is_threadl == 0){
										idx = idx -> left;
									}
									idx -> left = idx_root;
								}
							}
						}
					}
					else if(!(find -> left == idx)){
						find -> number = idx -> number;
					//	cout << find -> number << "ok ";
						////idx's right must be threaded
						idx_root -> right = idx -> right;
						idx_root -> is_threadr = 1;
						if(idx -> is_threadl == 0){//get the node who's right threaded is point to idx
							idx_root -> is_threadr = 0;
							idx_root -> right = idx -> left;						
							point_to_idx = idx -> left;
							while(point_to_idx -> is_threadr == 0){
								point_to_idx = point_to_idx -> right;
							}
							point_to_idx -> right = idx -> right;
							point_to_idx -> is_threadr = 1;
						}
					}
				}
			}
			else if(find -> is_threadl == 1 && find -> is_threadr == 0){//find only have right child
				if(find == tail) find_root = tail;
				if(find == root){
				//	cout << find -> number << "ok";
					root = find -> right;
					idx = find -> right;
					while(idx -> is_threadl == 0){
						idx = idx -> left;
					}
					head = idx;
					idx -> left = NULL;
				}
				else if(find != root){
					idx = find -> right;
					if(find == find_root -> left){
						find_root -> left = find -> right;
						find_root -> is_threadl = find -> is_threadr;
						find_root -> left = idx;
						while(idx -> is_threadl == 0) idx = idx -> left;
						idx -> left = find -> left;
					}
					else{
						if(idx -> left == NULL){
							find -> number = idx -> number;
							find -> right = idx -> right;
							find -> is_threadr = idx -> is_threadr;
							if(tail == idx )tail = find;
							idx = idx -> right;
							while(idx -> is_threadl == 0) idx = idx -> left;
							idx -> left = find_root;
						}
						else if(idx -> left != NULL){
							find_root -> right = idx;
							while(idx -> is_threadl == 0){
								idx = idx -> left;
							}
							idx -> left = find_root;
						}
					}
				}
			}
		}
	}
}
	
void op_tree_totum::inorder_run(){
	//TODO: travel the tree from the head node to the tail node and output the values
	//You should NOT use stack or recurtion 
	node *idx = head;
	int flag = 0;
	if(root != NULL){
		while(idx -> right != NULL){
			if(idx == root && flag == 0){
			//	cout << root -> number;
				cout << root -> number << " ";
				if(idx -> is_threadr == 1) break;
				idx = idx -> right;
				while(idx -> is_threadl == 0){
					idx = idx -> left;
				}
			}
			else if(idx -> is_threadr == 1){
				cout << idx -> number << " ";
				idx = idx -> right;;
			}
			else{
				cout << idx -> number << " ";
				if(idx -> right != NULL){
					idx = idx -> right;
					while(idx -> is_threadl == 0){
						idx = idx -> left;
					}
				}
			}
			
		//	system("pause");
		}
		if(idx == tail)cout << idx -> number << endl;
	}
}

void op_tree_totum::reverseorder_run(){
	//TODO: travel the tree from the tail node to the head node and output the values
	//You should NOT use stack or recurtion 
	node *idx = tail;
	int flag = 0;
	if(root != NULL){
		while(idx -> left != NULL){
			if(idx == root && flag == 0){
			//	cout << root -> number;
				cout << root -> number << " ";
				if(idx -> is_threadl == 1) break;
				idx = idx -> left;
				while(idx -> is_threadr == 0){
					idx = idx -> right;
				}
			}
			else if(idx -> is_threadl == 1){
				cout << idx -> number << " ";
				idx = idx -> left;;
			}
			else{
				cout << idx -> number << " ";
				if(idx -> left != NULL){
					idx = idx -> left;
					while(idx -> is_threadr == 0){
						idx = idx -> right;
					}
				}
			}
			
		//	system("pause");
		}
		if(idx == head)cout << idx -> number << endl;
	}
}

int op_tree_totum::size(){
	return num;
}
