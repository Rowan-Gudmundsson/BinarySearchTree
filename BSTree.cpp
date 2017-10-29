/**
 * @file BSTree.cpp
 * @author Rowan Gudmundsson
 * @date 10/15/17
 **/

#include "BSTree.h"

/**
 * \brief Constructor, sets root to NULL
 *
 * @param None, default constructor
 * @return None, constructor
 * @pre None
 * @post Tree will be initialized
 **/
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree () : root(NULL) {
}                        

/**
 * \brief Copy Constructor, copies other into (*this)
 *
 * Utilises the assignment helper to traverse the tree and copy each item from other into this
 *
 * @param Other Tree 
 * @return None, Constructor
 * @pre None
 * @post This will contain the data of other
 **/
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other ) : root(NULL) {

	clear();

	assignHelper(root, other.root);
}  

/**
 * \brief Assigns other to this
 * 
 * Utilises the assignment helper to traverse the tree and copy each item from other into this
 * 
 * @param Other tree
 * @return (*this) to allow a = b = c
 * @pre None
 * @post Other will be assigned to this
 **/ 
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator= ( const BSTree<DataType,KeyType>& other ) {

	if(this == &other) return (*this);

	clear();

	assignHelper(root, other.root);

	return (*this);
}

/**
 * \brief Destructor deallocates memory
 * 
 * Calls the clear() function
 * 
 * @param None
 * @return None
 * @pre None 
 * @post Tree will be destructed
 **/						  
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::~BSTree () {

	clear();
}

/** 
 * \brief Inserts a data item into the tree
 * 
 * Utilises insertHelper, calling it with root
 * 
 * @param New Data to insert
 * @return None, void function 
 * @pre None 
 * @post Tree will be that lil bit bigger
 **/
template <typename DataType, class KeyType> 
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem ) {

	insertHelper(root, newDataItem);
}

/**
 * \brief Changes the dataItem passed into it to be the dataItem indicated by the search key
 * 
 * Utilises retreveHelper to first find the key and then equate the data items
 *
 * @param Search key and dataItem
 * @return True if retrieved false if not 
 * @pre Filled tree
 * @post None, no change to class
 **/
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const {

	return retrieveHelper(root, searchKey, searchDataItem);
}

/**
 * \brief Removes a node selected by search key from the tree
 *
 * Utilises the removeHelper() function to locate and delete the node
 *
 * @param Delete Key
 * @return True if found and deleted, false if not
 * @pre None
 * @post
 **/
template <typename DataType, class KeyType>                                                
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey ) {

	return removeHelper(root, deleteKey);
}          

/**
 * \brief Writes all keys in tree in acsending order
 *
 * Uses writeKeysHelper() function to print in-order
 *
 * @param None
 * @return None, void function 
 * @pre Keys in the tree
 * @post None
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys () const {

	if(isEmpty()) return;

	writeKeysHelper(root);

	std::cout << std::endl;
}                   

/**
 * \brief Deallocates memory
 * 
 * Uses the clear helper function to do a post order deletion of the tree
 * 
 * @param None
 * @return None, void function
 * @pre None
 * @post Empty tree
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear () {

	if(isEmpty()) return;

	clearHelper(root);
}                              

/**
 * \brief Checks if the tree is Empty
 *
 * @param None
 * @return True if empty, false if not 
 * @pre None
 * @post None
 **/
template <typename DataType, class KeyType>   
bool BSTree<DataType, KeyType>::isEmpty () const {

	if(root == NULL) return true;
	else return false;
}                     

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const {

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.


    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

/** 
 * \brief Finds the height of the tree
 * 
 * Uses getHeightHelper to traverse the tree
 * 
 * @param None 
 * @return Height of the tree
 * @pre None 
 * @post None 
 **/
template <typename DataType, class KeyType>  
int BSTree<DataType, KeyType>::getHeight () const {

	if(isEmpty()) return 0;

	return getHeightHelper(root);
}                  

/** 
 * \brief Finds how many nodes are in the tree
 * 
 * Uses getCountHelper to traverse the tree
 * 
 * @param None
 * @return Number of nodes in the tree
 * @pre None 
 * @post None
 **/
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount () const {

	return getCountHelper(root);
}			 

/** 
 * \brief Node Constructor, sets data, left, and right to parameters passed
 * 
 * @param Data, left, and right
 * @return None, constructor
 * @pre None
 * @post Node will contain information 
 **/
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ) {

	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p, int level ) const {

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.


     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}

/** 
 * \brief Base case: otherNode is NULL, sets node = new node with otherNode data, recursively calls on left and right
 *
 * @param Node and Source node
 * @return None, void function
 * @pre None
 * @post Node == otherNode
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::assignHelper(BSTreeNode*& node, BSTreeNode* otherNode) {

	if(otherNode == NULL) return;

	node = new BSTreeNode(otherNode->dataItem, NULL, NULL);

	assignHelper(node->left, otherNode->left);
	assignHelper(node->right, otherNode->right);

}

/**
 * \brief Finds the place for new data and inserts it
 * 
 * If new data is smaller than current data recursively call left, if its bigger call right, 
 * if its the same set this->data = newData
 *
 * @param this Node and new Data
 * @return None, void function 
 * @pre None
 * @post Tree will have one more node
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode*& node, const DataType& newDataItem) {

	if(node == NULL) {

		node = new BSTreeNode(newDataItem, NULL, NULL);
		return;
	}
	if(newDataItem.getKey() < node->dataItem.getKey()) {

		insertHelper(node->left, newDataItem);
	}
	else if(newDataItem.getKey() > node->dataItem.getKey()) {

		insertHelper(node->right, newDataItem);
	}
	else {

		node->dataItem = newDataItem;
	}
}

/** 
 * \brief Finds the item at key and sets search data to this->data
 * 
 * @param this Node, search key, search data
 * @return True is found, false if not
 * @pre None
 * @post 
 **/
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* node, const KeyType& searchKey, DataType& searchDataItem) const {

	if(node == NULL) return false;

	if(searchKey < node->dataItem.getKey()) {

		return retrieveHelper(node->left, searchKey, searchDataItem);	
	}
	else if(searchKey > node->dataItem.getKey()) {

		return retrieveHelper(node->right, searchKey, searchDataItem);
	}
	else {

		searchDataItem = node->dataItem;
		return true;
	}
}

/** 
 * \brief Finds the node, removes it based on a few cases
 * 
 * Finds the node by recursively calling either left or right; once found, (case one, no children) delete the node, equal it to NULL
 * (case two, one child) point around the node, delete it (case three, two children) find the predecessor, copy that data to the node 
 * being deleted, delete the predecessor using a trailing pointer.
 *
 * @param this Node, delete key 
 * @return True if found, false if not
 * @pre None
 * @post One less Node
 **/
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& node, const KeyType& deleteKey) {

	if(node == NULL) return false;

	if(deleteKey < node->dataItem.getKey()) {

		return removeHelper(node->left, deleteKey);
	}
	else if(deleteKey > node->dataItem.getKey()) {

		return removeHelper(node->right, deleteKey);
	}
	else {

		//Case 1
		if((node->left == NULL) && (node->right == NULL)) {

			delete node;
			node = NULL;
		}
		//Case 2 (a)
		else if(node->right == NULL) {

			BSTreeNode* tmp = node;

			node = node->left;
			delete tmp;
			tmp = NULL;
		}
		//Case 2 (b)
		else if(node->left == NULL) {

			BSTreeNode* tmp = node;

			node = node->right;
			delete tmp;
			tmp = NULL;
		}
		//Case 3
		else {

			BSTreeNode* tmp = node->left;
			BSTreeNode* tmpTrail = node;

			while(tmp->right) {

				tmpTrail = tmp;
				tmp = tmp->right;
			}

			node->dataItem.setKey(tmp->dataItem.getKey());

			if(tmp->left == NULL && tmp->right == NULL) {

				delete tmp;
				if(tmpTrail == node) tmpTrail->left = NULL;
				else tmpTrail->right = NULL;
			}
			else if(tmp->left != NULL) {

				if(tmpTrail == node) tmpTrail->left = tmp->left;
				else tmpTrail->right = tmp->left;
				delete tmp;
			}
			
		}
		return true;
	}
}

/**
 * \brief If node is null, return, clear left, clear right, delete self
 *
 * @param this Node
 * @return None, void function
 * @pre None
 * @post Empty Tree
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& node) {

	if(node == NULL) return;

	clearHelper(node->left);
	clearHelper(node->right);

	delete node;
	node = NULL;
}

/** 
 * \brief Walks through all node, if NULL return 0, else return 1 plus node in left plus nodes in right
 *
 * @param current Node
 * @return Number of nodes
 * @pre None
 * @post None
 **/
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* node) const {

	if(node == NULL) return 0;

	return 1 + getCountHelper(node->left) + getCountHelper(node->right);
}

/** 
 * \brief if NULL return 0, find the max of left subtree and right subtree, return 1 + max 
 * 
 * @param current Node
 * @return Height of subtree
 * @pre None 
 * @post None
 **/
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* node) const {

	if(node == NULL) return 0;

	int leftHeight = getHeightHelper(node->left);
	int rightHeight = getHeightHelper(node->right);

	int max = MAX(leftHeight, rightHeight);

	return max + 1;
}

/** 
 * \brief In order traversal of the tree printing the keys as we go
 * 
 * @param current Node 
 * @return None, void function 
 * @pre None
 * @post None
 **/
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* node) const{

	if(node == NULL) return;

	writeKeysHelper(node->left);

	std::cout << node->dataItem.getKey() << ' ';

	writeKeysHelper(node->right);
}