template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree ();                        

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other );  

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator= ( const BSTree<DataType,KeyType>& other );
						  
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::~BSTree ();

template <typename DataType, class KeyType> 
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem ); 

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const;

template <typename DataType, class KeyType>                                                
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey );           

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys () const;                    

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear ();                               

template <typename DataType, class KeyType>   
bool BSTree<DataType, KeyType>::isEmpty () const;                       

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
int BSTree<DataType, KeyType>::getHeight () const;                   

template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount () const;			 

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const; 

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr );

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
