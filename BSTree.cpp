#include "BSTree.h"

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree () : root(NULL) {
}                        

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other ) : root(NULL) {

	clear();

	assignHelper(root, other.root);
}  

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator= ( const BSTree<DataType,KeyType>& other ) {

	if(this == &other) return (*this);

	clear();

	assignHelper(root, other.root);

	return (*this);
}
						  
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::~BSTree () {

	clear();
}

template <typename DataType, class KeyType> 
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem ) {

	insertHelper(root, newDataItem);
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const {

	return retrieveHelper(root, searchKey, searchDataItem);
}

template <typename DataType, class KeyType>                                                
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey ) {

	return removeHelper(root, deleteKey);
}          

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys () const {

}                   

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear () {

	if(isEmpty()) return;

	clearHelper(root);
}                              

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

template <typename DataType, class KeyType>  
int BSTree<DataType, KeyType>::getHeight () const {

}                  

template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount () const {

}			 

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const {

}

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

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::assignHelper(BSTreeNode*& node, BSTreeNode* otherNode) {

	if(otherNode == NULL) return;

	node = new BSTreeNode(otherNode->dataItem, NULL, NULL);

	assignHelper(node->left, otherNode->left);
	assignHelper(node->right, otherNode->right);

}
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

		node->dataItem.setKey(newDataItem.getKey());
	}
}

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

		searchDataItem.setKey(node->dataItem.getKey());
		return true;
	}
}

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
		if(node->left == NULL && node->right == NULL) {

			delete node;
			node = NULL;
		}
		if(node->right == NULL) {

			BSTreeNode* tmp = node;

			node = node->left;
			delete tmp;
			tmp = NULL;
		}
		if(node->left == NULL) {

			BSTreeNode* tmp = node;

			node = node->right;
			delete tmp;
			tmp = NULL;
		}
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

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& node) {

	if(node == NULL) return;

	clearHelper(node->left);
	clearHelper(node->right);

	delete node;
	node = NULL;
}