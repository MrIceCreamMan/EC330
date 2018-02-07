//AUTHOR: Zachary Chapasko
//COLLABORATORS: None

/*
To solve this problem I made extensive use of recursion. Searching in a BST is best
done using recursion and my search algorithm makes use of it. I start by searching
in the given tree for the root node of the desired tree, and saving that path. I then
walk down the given tree using the computed path and stop one node short of the
desired root node. I perform a rotation to move the desired root node up the path,
and then I walk back down the tree and do the operation again. At some point the
desired root node is one of the children of the current root node, so I perform
the appropriate rotation and then reset the root pointer. With the root in the
correct position we now have the correct number of nodes on either side of the root.
I recursively fix up the tree by visiting the children of the root, and then their
children, and so on, using a method nearly identical to placing the root in the
correct location. Searching to create the path is lg(n) time where n is the number
of nodes in the tree. Suppose x = lg(n); x is the length of the vector that stores
the path from the current root to the desired root. I look at the first x items
in the list, then the first x - 1, then x - 2, and so on (to walk down the tree and
perform a single rotation)...therefore the total runtime of positioning the root is
x^2, or (lg(n))^2, which is just lg(n). Each"bubbling up" of a node is therefore also
lg(n) time. In the worst case you would need to "bubble up" every node, giving us a
total runtime of O(n*lg(n)); not bad. In each stack frame of the transformation
function we add two integers, two Node pointers, and two enums, so the overhead
on recursion is arguably minimal. In each stack frame of the search function we add
one enum, which is relatively negligible. This algorithm should perform well even
on large inputs.
*/

#include "MyBST.h"

/**
 * Computes how to transform this MyBST into the target MyBST using rotations.
 * Returns a vector of rotations indicating which rotations around which nodes
 *  must be performed to transform this into the target.
 *
 * IMPORTANT: We want to transform T1 into T2 so the call should look like
 * rotations = t1.transform(t2)
 */
vector<Rotation> MyBST::transform(MyBST target) {
    // clear previously stored rotations
    zigZags.clear();
    rotations.clear();

    // search for the target's root in this tree beginning with the root of this tree
    search(target.root->key, this->root);

    // set up some variables to help us make sense of this mess
    Node *current = root;
    Node *previous = root;
    int len = zigZags.size(), ii;

    // while the desired root isn't where we want it, we are going to bubble it up
    while(this->root->key != target.root->key){
        // climb down the tree until we are 1 node above the desired root; keep track of 2 nodes before the root as well
        for(ii = 0; ii < len - 1; ii++){
            previous = current;
            switch(zigZags[ii]){
                case ZIG:
                    current = current->left;
                    break;
                case ZAG:
                    current = current->right;
                    break;
            }
        }

        // if ii > 0 we don't have to rotate the root
        if(ii > 0){
            switch(zigZags[ii]){
                // if our last traversal is on the left, we need to rotate right (zig)
                case ZIG:
                    switch(zigZags[ii - 1]){
                        // if the current node is to the left of its parent, set result of rotation accordingly
                        case ZIG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->left = rotateRight(current);
                            break;
                        // if the current node is to the right of its parent, set result of rotation accordingly
                        case ZAG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->right = rotateRight(current);
                            break;
                    }
                    break;
                // if our last traversal is on the right, we need to rotate left (zag)
                case ZAG:
                    switch(zigZags[ii - 1]){
                        // if the current node is to the left of its parent, set result of rotation accordingly
                        case ZIG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->left = rotateLeft(current);
                            break;
                        // if the current node is to the right of its parent, set result of rotation accordingly
                        case ZAG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->right = rotateLeft(current);
                            break;
                    }
                    break;
            }

            len--;
            current = root;
            previous = root;

        // now it is time to rotate the root; the desired root is either the left or right child of the current root
        } else if (ii == 0){
            switch(zigZags[ii]){
                case ZIG:
                    rotations.push_back(Rotation(root->key, zigZags[ii]));
                    root = rotateRight(root);
                    break;
                case ZAG:
                    rotations.push_back(Rotation(root->key, zigZags[ii]));
                    root = rotateLeft(root);
                    break;
            }
        }
    }

    // now our tree has the same root as the target tree; recursively fix up the subtrees
    RotationType left = ZIG;
    RotationType right = ZAG;
    if(root->left != nullptr && target.root->left != nullptr){
        transform(root->left, target.root->left, root, left);
    }
    if(root->right != nullptr && target.root->right != nullptr){
        transform(root->right, target.root->right, root, right);
    }

    return rotations;
}

// recursive function to settle all non-root nodes
void MyBST::transform(Node *head, Node *targetHead, Node* parent, RotationType childSide){
    // clear previously stored zigzags
    zigZags.clear();

    // search for the target's head in this tree beginning with the head of this tree
    search(targetHead->key, head);

    // set up some variables to help us make sense of this mess
    Node *current = head;
    Node *previous = head;
    int len = zigZags.size(), ii;

    // while the desired head isn't where we want it, we are going to bubble it up
    while(targetHead->key != head->key){
        // climb down the tree until we are 1 node above the desired head; keep track of 2 nodes before the head as well
        for(ii = 0; ii < len - 1; ii++){
            previous = current;
            switch(zigZags[ii]){
                case ZIG:
                    current = current->left;
                    break;
                case ZAG:
                    current = current->right;
                    break;
            }
        }

        // if ii > 0 we don't have to rotate the head
        if(ii > 0){
            switch(zigZags[ii]){
                // if our last traversal is on the left, we need to rotate right (zig)
                case ZIG:
                    switch(zigZags[ii - 1]){
                        // if the current node is to the left of its parent, set result of rotation accordingly
                        case ZIG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->left = rotateRight(current);
                            break;
                        // if the current node is to the right of its parent, set result of rotation accordingly
                        case ZAG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->right = rotateRight(current);
                            break;
                    }
                    break;
                // if our last traversal is on the right, we need to rotate left (zag)
                case ZAG:
                    switch(zigZags[ii - 1]){
                        // if the current node is to the left of its parent, set result of rotation accordingly
                        case ZIG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->left = rotateLeft(current);
                            break;
                        // if the current node is to the right of its parent, set result of rotation accordingly
                        case ZAG:
                            rotations.push_back(Rotation(current->key, zigZags[ii]));
                            previous->right = rotateLeft(current);
                            break;
                    }
                    break;
            }

            len--;
            current = head;
            previous = head;

        // now it is time to rotate the head; the desired head is either the left or right child of the current head
        } else if (ii == 0){
            switch(zigZags[ii]){
                case ZIG:
                    // our assignment of the child depends on which side the child is on
                    switch(childSide){
                        case ZIG:
                            rotations.push_back(Rotation(head->key, zigZags[ii]));
                            parent->left = rotateRight(head);
                            head = parent->left;
                            break;
                        case ZAG:
                            rotations.push_back(Rotation(head->key, zigZags[ii]));
                            parent->right = rotateRight(head);
                            head = parent->right;
                            break;
                    }
                    break;
                case ZAG:
                    // our assignment of the child depends on which side the child is on
                    switch(childSide){
                        case ZIG:
                            rotations.push_back(Rotation(head->key, zigZags[ii]));
                            parent->left = rotateLeft(head);
                            head = parent->left;
                            break;
                        case ZAG:
                            rotations.push_back(Rotation(head->key, zigZags[ii]));
                            parent->right = rotateLeft(head);
                            head = parent->right;
                            break;
                    }
                    break;
            }
        }
    }

    // now our subtree has the same root as the target subtree; recursively fix up these subtrees
    RotationType left = ZIG;
    RotationType right = ZAG;
    if(head->left != nullptr && targetHead->left != nullptr){
        transform(head->left, targetHead->left, head, left);
    }
    if(head->right != nullptr && targetHead->right != nullptr){
        transform(head->right, targetHead->right, head, right);
    }
}


Node* MyBST::rotateRight(Node* Q)
{
    Node* P = Q->left;
    Q->left = P->right;
    P->right = Q;
    return P;
}

Node* MyBST::rotateLeft(Node* P)
{
    Node* Q = P->right;
    P->right = Q->left;
    Q->left = P;
    return Q;
}

void MyBST::search(int key, Node *node){
    RotationType r;
    if(key < node->key){            // go to the left as the key is smaller than the key at this node
        r = ZIG;                    // if the node is on the left we must perform a right rotation, or a zig
        zigZags.push_back(r);       // store which side we traveled down
        search(key, node->left);    // recurse
    } else if (key > node->key){    // go to the right as the key is bigger than the key at this node
        r = ZAG;                    // if the node is on the right we must perform a left rotation, or a zag
        zigZags.push_back(r);       // store which side we traveled down
        search(key, node->right);   // recurse
    } else { return; }
}
