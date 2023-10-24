#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
    key = 0;    // The key of the current node
    left = nullptr;     // A pointer to the left child of the node
    right = nullptr;    // A pointer to the right child of the node
    parent = nullptr;   // A pointer to the node above it
}
// Constructor
Node::Node(int in) {
    key = in;    // The key of the current node
    left = nullptr;     // A pointer to the left child of the node
    right = nullptr;    // A pointer to the right child of the node
    parent = nullptr;   // A pointer to the node above it
}
// Destructor
Node::~Node() {
// Since we didnt malloc anything no need for deletes, that is all dont in main and delete function
}

// Add parent 
void Node::add_parent(Node* in) {
    parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
    left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
    right = in;
}

// Get key
int Node::get_key()
{
    return key;
}
// Get parent node
Node* Node::get_parent()
{
    return parent;
}
// Get left node
Node* Node::get_left()
{
    return left;
}
// Get right node
Node* Node::get_right()
{
    return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
    if (in != nullptr){   // Verfity that the inputted node is a real node
    inorder_walk(in->get_left(), to);   // Walk recursively down the left subtree
    in->print_info(to);  // Print the current node's key
    inorder_walk(in->get_right(), to);  // Walk recursively down the right subtree
    }
}

// Constructor
BST::BST()
{
    root = nullptr;	// Simply make sure the root is a nullptr on intialitzation
}
// Destructor
BST::~BST(){ 
while (tree_min() != nullptr){		// Have to go through and delete all the nodes
	delete_node(tree_min());	// This just seemed like the simplest method for me, but there are otherways to go through and delete too
}
}

// Insert a node to the subtree
void BST::insert_node(Node* in)
{
    Node* parent = nullptr; 	// Set parent to a null pointer
    Node * current_node = root;	// Set the current node to the root of the tree
    while (current_node != nullptr){	// While the current node is not a null pointer
        parent = current_node;	// Make the parent the current node
        if (in->get_key() < current_node->get_key()){	// Checks what side to go down
            current_node = current_node->get_left();	// If key is less than the current node go down the left side
        } else {
            current_node = current_node->get_right();	// Otherwise go down the right side
        }
    }
    in->add_parent(parent);	// Make the parent of the insert node parent
    if (parent == nullptr){	// If the parent is a nullpointer then we are at the root
        root = in;	// Thus the inserted tree becomes the new root
    } else if (in->get_key() < parent->get_key()){	// Otherwise if the key is less than the parent
        parent->add_left(in);	// Then make the inserted node the left child
    } else {
        parent->add_right(in);	// Othewise make it the right child
    }
}

// Delete a node to the subtree
void BST::delete_node(Node* out)
{
    if (out == nullptr) {   // Since the node itself is null there is nothing to delete
        return; 
    }
    
    if (out->get_left() == nullptr) {   // Checks if there is not a left child to delete
        transplant(out, out->get_right());  // Simply transplant the right child to take the place of the deleted node
    } else if (out->get_right() == nullptr) {   // Otherwise if there is not a right child to delete
        transplant(out, out->get_left());   // Simply transplant the left child to take the place of the deleted node
    } else {    // Has a left and right child
        Node* succ_node = get_succ(out);    // Find successor node
        
        if (succ_node->get_parent() != out) {   // If the successor nodes parent is not the node we want to remove then
            transplant(succ_node, succ_node->get_right());  // Transplant the succssessor node with their right child
            succ_node->add_right(out->get_right()); // Then add a right child to the succ_node (the right child of the removed node)
            succ_node->get_right()->add_parent(succ_node);  // Update the right child's parent to reflect the change
        }
        
        transplant(out, succ_node); // Transplant the node we want to remove with the successor node
        succ_node->add_left(out->get_left());   // Then add a left child to the succ_node (the left child of the removed node)
        succ_node->get_left()->add_parent(succ_node);   // Update the left child's parent to reflect the change
    }
    
    delete out; // Delete the node we removed	
}

// minimum key in the BST
Node* BST::tree_min()
{
    if (root == nullptr){
	    return nullptr;
    }

    Node* current_node = root;      // Initalize current node to root of tree
    
    while (current_node->get_left() != nullptr){    // Make sure not to go to a nullptr
        current_node = current_node->get_left();    // Goes down the left side
    }
    
    return current_node;    // This is the trees lowest value node

}
// maximum key in the BST
Node* BST::tree_max()
{
    Node* current_node = root;      // Initalize current node to root of tree
    
    while (current_node->get_right() != nullptr){    // Make sure not to go to a nullptr
        current_node = current_node->get_right();    // Goes down the right side
    }
    
    return current_node;    // This is the trees largest value node

}

// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
    Node* current_node = in;
    while (current_node->get_left() != nullptr){    // Make sure not to go to a nullptr
        current_node = current_node->get_left();    // Goes down the left side
    }
    
    return current_node;    // This is the sub-trees smallest value node
}

// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
    Node* current_node = in;
    while (current_node->get_right() != nullptr){    // Make sure not to go to a nullptr
        current_node = current_node->get_right();    // Goes down the right side
    }
    
    return current_node;    // This is the sub-trees largest value node
}

// Get successor of the given node
Node* BST::get_succ(Node* in)
{
    Node* current_node = in;	// Intialize current node to input node
    if (current_node->get_right() != nullptr){	// If the right child exists
        return get_min(current_node->get_right());	// Then get the minimum from the starting point of the right child
    } else {	// Otherwise
        Node * parent = current_node->get_parent();	// Set the parent to the parent of the current node
        while ((parent != nullptr) && (current_node == parent->get_right())){	// While the parent of the node exists and the current node is the right side child of parent then
            current_node = parent;	// Set current node to parent
            parent = parent->get_parent();	// Get the new parent
        }
        return parent;	// Return parent node
    }
}

// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
    Node* current_node = in;	// Initialize current node to input node
    if (current_node->get_left() != nullptr) {	// If left child exits
        return get_max(current_node->get_left());	// Get the maximum from the starting point of the left child
    } else {
        Node* parent = current_node->get_parent();	// Set parent node to the current nodes parent
        while ((parent != nullptr) && (current_node == parent->get_left())) {	// While the parent exitsts and the current node is the left side child of parent
            current_node = parent;	// Set the current_node to the parent
            parent = parent->get_parent();	// Set the parent node to the parent of parent
        }
        return parent;
    }
}

// Walk the BST from min to max
void BST::walk(ostream& to)
{
    Node * current_node = tree_min(); // Initialize the current node to be the minimum value in the tree
    while (current_node != nullptr) {
        current_node->print_info(to);  // Print the key of the current node
        current_node = get_succ(current_node);  // Get the successor of the current node
    }
}

// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
    Node * current_node = root; // Initialize the current node to be the root

    while (current_node != nullptr){    // Make sure we never reach a null pointer node, preven seg faults
        int current_key = current_node->get_key();

        if(search_key == current_key){   // Check if we found the key
            return current_node;    // Yay! We found the node with the matching key, we can now return it
        } else if (search_key < current_key){   // Determine what side to go down the binary tree
            current_node = current_node->get_left();    // The key is less than so go down the left side
        } else {
            current_node = current_node->get_right();   // The key is greater than so go down the right side
        }
    }
    return nullptr;
    

}
// ---------------------------------------

/* Transplants a subtree with a different subtree, helpful in removing nodes, in this 
case the subtree rooted at u will be replaced with the one rooted at v */
void BST::transplant(Node* u, Node* v) {
    if (u->get_parent() == nullptr) { // Checks if 'u' is the root node
        root = v;   // If so the transplant is simple, just make the node v the root
    } else if (u == u->get_parent()->get_left()) {  // Checks if u is a leftchild
        u->get_parent()->add_left(v);    // If so then simply update the parent of u to have the new left child of v
    } else {    // Othewise u is the right child
        u->get_parent()->add_right(v);   // Replace the right child of u's parent with v
    }

    if (v != nullptr) { // If v is a null pointer then simply make the parent of v equal to the parent of u
        v->add_parent(u->get_parent());
    }
}

