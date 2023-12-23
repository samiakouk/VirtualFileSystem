// Include all the header files necessary
#include "vfs.h"
#include "myvector.hpp"
#include "myqueue.hpp"
#include "mystack.hpp"

// Include all the built-in libraries
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
#include<regex>
#include<exception>

using namespace std; // 


// Global file stream for output
ofstream ofile;


// Default constructor for the TreeNode (specifically for root).
TreeNode::TreeNode(){
    // Default constructor for the root node
    name = "/";
    size = 0;
    isFile = false;

    // Get the current time and format it
    time_t currentTime = time(nullptr);
    char buffer[80];
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", localtime(&currentTime));
    date = buffer;

    // Root has no parent 
    parent = NULL;


}

// Constructor with parameters for non-root nodes
TreeNode::TreeNode(string name, int size, bool value){
    // Initialise the class's private attribute
    this->name = name;
    this->size = size;
    this->isFile = value;

    // Get the current time and format it
    time_t currentTime = time(nullptr);
    char buffer[80];
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", localtime(&currentTime));
    date = buffer;

    // Parent is initially set to nullptr
    parent = NULL;
}


//Constructor 
Tree::Tree(){
    // Constructor initializes the root node and opens the output file
    root = new TreeNode();
    current = root;
    prev = NULL;

    // Open "vfs.dat" the output file
    ofile.open("vfs.dat");


}

// Prints the path of working directory (current TreeNode)
string Tree::pwd() const{
    myStack<string> path;
    string ans;

    TreeNode* currentNode = current;

    if(currentNode == root){
        return root->name;
    }

    // Build the path by traversing up to the root
    while(currentNode != root){
        path.push(currentNode->name);
        path.push("/");

        currentNode = currentNode->parent;
    }

    // Construct the full path by popping elements from the stack
    while(!path.empty()){
        ans += path.top();
        path.pop();
    }

    // Return the path of the current node
    return ans; 
}

// Lists the subfiles of the current folder
void Tree::ls() const{
    // If current node is empty then return
    if(current->children.empty()){
        return;
    }

    // Display information for each child node
    for(int i = 0; i < current->children.size(); i++){
        if(current->children[i]->isFile){
            cout << "File: " << current->children[i]->name << "    " << current->children[i]->size << "    " << current->children[i]->date << endl;
        }else{
            cout << "Directory: " << current->children[i]->name << "    " << current->children[i]->size << "    " << current->children[i]->date << endl;
        }
    }
}

// Lists the subfiles of the current folder in a sorted way
void Tree::lsSort() const{
    // If current node is empty then return
    if(current->children.empty()){
        return;
    }

    // Create a vector to store children nodes
    MyVector<TreeNode*> lsSorted;
    for(int i = 0; i < current->children.size(); i++){
        lsSorted.push_back(current->children[i]);
    }

    // Bubble Sort 
    for(int i = 0; i < lsSorted.size(); i++){
        for(int j = 0 ; j < lsSorted.size() - 1; j++){
            // Check if one node's size is less than the size of the next node
            if(lsSorted[j]->size < lsSorted[j+1]->size){
                // Perform the swapping
                TreeNode* tmp = lsSorted[j];
                lsSorted[j] = lsSorted[j+1];
                lsSorted[j+1] = tmp;
            }
        }
    }

    // Display information for the sorted vector.
    for(int i = 0; i < lsSorted.size(); i++){
        if(lsSorted[i]->isFile){
            cout << "File: " << lsSorted[i]->name << "    " << lsSorted[i]->size << "    " << lsSorted[i]->date << endl;
            continue;
        }else{
            cout << "Directory: " << lsSorted[i]->name << "    " << lsSorted[i]->size << "    " << lsSorted[i]->date << endl;
            continue;
        }
    }   
}

// Creates a folder within the current directory
void Tree::mkdir(string foldername){
    //     // Validate the file name format using a regex pattern
    regex pattern("^[a-zA-Z0-9]+$");
    if(!regex_match(foldername, pattern)){
        cout << "File names should be alphanumeric only (i.e. comprises the letters A to Z, a to z, and the digits 0 to 9) with no whitspace or special character" << endl;
        return;
    }

    // if current is file throw error
    if(current->isFile){
        throw logic_error("Cannot create a Directory under a File");
    }else{
        // Check if there exits a folder already with the same name
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == foldername){
                cerr << foldername << " has already been used in the same directory" << endl;
                return;
            }
        }

        // Creates a new Node for the folder
        TreeNode* newFolder = new TreeNode(foldername, 10, false);

        // Makes the necessary connection between current and the new Folder.
        current->children.push_back(newFolder);
        newFolder->parent = current;

        // Update the size of the current node
        updateSize(current);
    }
}  

// Creates a file within the current directory
void Tree::touch(string filename, int size){
    // Validate the file name format using a regex pattern
    regex pattern("^[a-zA-Z0-9]+\\.[a-zA-Z]{1,4}$");
    if(!regex_match(filename, pattern)){
        cout << "Write the file name in the following format: filename.extension" << endl;
        return;
    }

    //if current is a file throw an error
    if(current->isFile){
        throw logic_error("Cannot create a File under a File");
    }else{
        // Check if there exits a file already with the same name
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == filename){
                cerr << filename << " has already been used in the same directory" << endl;
                return;
            }
        }

        // Creates a new Node for the file
        TreeNode* newFile = new TreeNode(filename, size, true);

        // Makes the necessary connection between current and the new File
        current->children.push_back(newFile);
        newFile->parent = current;

        // Update the size of the current node
        updateSize(current);

    }
}

// Changes the current directory to another directory
void Tree::cd(string arg){
    if(arg == ".."){
        // if current is set to root return
        if(current == root){
            return;
        }

        // Set prev to current
        prev = current;

        // Move up to the parent directory
        current = current->parent;
    }else if(arg == "-"){
        // if prev is pointing to a null pointer returns
        if(prev == NULL){
            return;
        }

        // set current to prev
        current = prev;
    }else if(arg == ""){
        // Set prev to current
        prev = current;

        // Set current to root
        current = root;
    }else{
        // If the first character starts with "/", it means the argument passed is a path otherwise it is a folder's name
        if(arg[0] == '/'){
            // Set prev to current
            prev = current;

            // Check if path is valid using the getNode() function
            if(getNode(arg) == NULL){
                // Display an error message in case the path is invalid and then return
                cerr << "Invalid Path" << endl;
                return;
            }

            // Otherwise set current to the node returned by the getNode() function 
            current = getNode(arg);

        }else{
            // Set prev to current
            prev = current;

            // Loop through the current's children
            for(int i = 0; i < current->children.size(); i++){
                // Check if a child node's name corresponds to the folder name
                if(current->children[i]->name == arg){

                    // Check if the child node is file
                    if(current->children[i]->isFile){
                        // If it is a file: display an error message and then return
                        cerr << "Error: "<<  current->children[i]->name << " is a file" << endl;
                        return;
                    }else{
                        // Set current to its child
                        current = current->children[i];
                        return;
                    }
                }
            }

            // In case we did not find the specified node: display an error message
            cerr << arg << "  is not a directory." << endl;
        }
    }
}

// Removes a file/folder within the current directory or arbitrarily given its path and adds it to the bin
void Tree::rm(string name){
    // Check if the argument is a path (starts with '/')
    if(name[0] == '/'){
        // Check if the argument is equal to "/" (means it is a root)
        if(name == "/"){
            //Display an error message
            cout << "root cannot be deleted" << endl;
            return;
        }

        // Gets the node corresponding to the provided path
        TreeNode* newNode = getNode(name);
        if(newNode == NULL){
            cerr << "Invalid Path" << endl;
            return;
        }

        // Assign current to the targeted node's parent
        current = newNode->parent;

        
        // Iterates through the children of the parent node to find the node to delete
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == newNode->name){
                // If the bin is FULL. Display an error message and return
                if(bin.isFull()){
                    cerr << "The bin is FULL. Empty the bin or Recover some files / folder before executing the 'rm' function again" << endl;
                    return;
                }
                /*
                    1st: enque the node to node to bin and its ancestor's path to bin_path
                    2st: erase the node from the current's children
                    3rd: update the size of current
                    4th: set current to the root in case the path deleted was the current's path
                */
                bin.enqueue(current->children[i]);
                bin_paths.enqueue(pwd());
                current->children.erase(i);
                updateSize(current);
                current = root;
                return;
            }
        }

        // If the loop did not break, it means the file/folder's path was not found
        cerr << name << "was not found" << endl;

    }else{
        // Iterates through the children of current to find the node to delete 
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == name){
                // If the bin is FULL. Display an error message and return
                if(bin.isFull()){
                    cerr << "The bin is FULL. Empty the bin or Recover some files / folder before executing the 'rm' function again" << endl;
                    return;
                }
                /*
                    1st: enque the node to node to bin and its ancestor's path to bin_path
                    2st: erase the node from the current's children
                    3rd: update the size of current
                    4th: set current to the root in case the path deleted was the current's path
                */
                bin.enqueue(current->children[i]);
                bin_paths.enqueue(pwd());
                current->children.erase(i);
                updateSize(current);
                return;
            }
        }

        // If the loop did not break, it means the file/folder was not found
        cerr << name << " was not found." << endl;
    }
}


// Returns the size of a file or folder (Taking into account potential subfiles)
int  Tree::size(string path){
    // If getNode() returns a NULL pointer that means the path did not exists
    if(getNode(path) == NULL){
        throw logic_error("Invalid path");
    }

    // Otherwise returns the size of the pointer getNode()
    return getNode(path)->size;
}

// Empties the bin
void Tree::emptyBin(){
    // while the the queue is not empty, keep dequeue.
    while(!bin.isEmpty()){
        bin.dequeue();
    }
}

// Shows the first deleted file along with its path
void Tree::showBin(){
    // if queue is empty, print an error message and returns
    if(bin.isEmpty()){
        cout << "The bin is empty" << endl;
        return;
    }

    string path;
    // Check if the bin_paths is "/" so that we do not write it twice
    if(bin_paths.getFront() == "/"){
        path = bin_paths.getFront() + bin.getFront()->name;
    }else{
        path = bin_paths.getFront() + "/" + bin.getFront()->name;
    }
    // Display the information of the first deleted node 
    cout << "Name: " << bin.getFront()->name << " Size: " << bin.getFront()->size << " Date: " << bin.getFront()->date << endl;
    cout << "Path: " << path << endl;
}

// Recover the first deleted file
void Tree::recover(){
    // keep track of the current's original position
    TreeNode* currentNode = current;

    // set current to the parent of the node we want to recover
    current = getNode(bin_paths.getFront());

    // If current is pointing to null pointer
    if(current == NULL){
        // Set current to its original position
        current = currentNode;
        // Throw an error
        throw logic_error("Path has been deleted");
    }

    // Make the necessary connection
    bin.getFront()->parent = current;
    current->children.push_back(bin.getFront());

    // Dequeue
    bin_paths.dequeue();
    bin.dequeue();

    // Set current to its original position
    current = currentNode;

}

// Prints all the paths given a file's name
void Tree::find(string name){
    find_helper(root, name);
}


// Moves a file inside a folder (given both the file and the folder are within the current directory or anywhere from the file system given their paths)
void Tree::mv(string filename, string foldername){
    if(filename[0] == '/' && foldername[0] == '/'){
        TreeNode* file_node = getNode(filename);
        TreeNode* old_folder_node = file_node->parent;
        TreeNode* folder_node = getNode(foldername);

        if(file_node == NULL || !file_node->isFile){
            cerr << "file's path does not exist or does not correspond to a file" << endl;
            return;
        }

        if(folder_node == NULL || folder_node->isFile){
            cerr << "folder's does not exist or does not correspond to a folder" << endl;
            return;
        }

        for(int i = 0; i < old_folder_node->children.size(); i++){
            if(old_folder_node->children[i]->name == file_node->name){
                old_folder_node->children.erase(i);
                updateSize(old_folder_node);
                break;
            }
        }

        for(int i = 0; i < folder_node->children.size(); i++){
            if(folder_node->children[i]->name == file_node->name){
                cerr << file_node->name << " already exist in " << folder_node->name << endl;
                old_folder_node->children.push_back(file_node);
                updateSize(old_folder_node);
                return;
            }
        }

        file_node->parent = folder_node;
        folder_node->children.push_back(file_node);
        updateSize(folder_node);
        return;


    }else{
        TreeNode* file_node = NULL;
        TreeNode* old_folder_node = NULL;
        TreeNode* folder_node = NULL;

        int index = 0;
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == filename){
                old_folder_node = current;
                file_node = current->children[i];
                if(!file_node->isFile){
                    cerr << filename << " does not correspond to a file." << endl;
                    return;
                }
                current->children.erase(i);
                updateSize(current);
                break;
            }
        }

        if(file_node == NULL){
            cerr << filename << " does not exist in this directory" << endl;
            return;
    
        }

        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == foldername){
                folder_node = current->children[i];
                if(folder_node->isFile){
                    cerr << foldername << " does not correspond to a folder." << endl;
                    return;
                }
            }
        }

        if(folder_node == NULL){
            old_folder_node->children.push_back(file_node);
            updateSize(old_folder_node);
            cerr << foldername << " does not exist in this directory" << endl;
            return;
        }

        for(int i = 0; i  < folder_node->children.size(); i++){
            if(folder_node->children[i]->name == filename){
                cerr << filename << " already exist in " << foldername << endl;
                old_folder_node->children.push_back(file_node);
                updateSize(old_folder_node);
                return;
            }
        }

        file_node->parent = folder_node;
        folder_node->children.push_back(file_node);
        updateSize(folder_node);
    }
}

//Helper method to get a pointer to TreeNode at given path
TreeNode* Tree::getNode(string path){
    stringstream ss(path);
    string dirName;
    char dummyChar;

    // Special Case: if path is equal to "/" return the root
    if(path == "/"){
        return root;
    }
    // Check if the path starts with the character '/', if it does not return null pointer since it is not a valid path
    if(ss.peek() == '/'){
        // read the firt character and assign it to a dummy character
        ss >> dummyChar;


        TreeNode* tracker = root;

        // Keep iterating while we did not reach the end of the stream
        while(!ss.eof()){
            // Read a string from the stream until it encounters '/' and stores that in "dirName"
            getline(ss, dirName, '/');


            bool found = false; // Flag to track whether the current path component was found

            // Recursive loop to check if the name of tracker matches "dirName"
            for(int i = 0; i < tracker->children.size(); i++){
                if(tracker->children[i]->name == dirName){
                    tracker = tracker->children[i];
                    found = true; // Mark as found
                    break; // No need to continue checking other children
                }
            }

            // In case we did not find the node, return a null pointer
            if (!found) {
                return nullptr; // Path component not found
            }
        }

        return tracker; // Return the final node in the path
    } else {
        return nullptr; // Path does not start with '/'
    }
}

// Recursive method that deletes a TreeNode with all its descendants
void Tree::deleteNode(TreeNode* node){
        // Travese the tree in postorder way and then delete nodes (the other way around will not work)
        if (node != NULL) {
            for (int i = 0; i < node->children.size(); i++) {
                deleteNode(node->children[i]);
            }
            delete node;
        }else{
            throw logic_error("Cannot delete this Node!");
        }
    
}

// Recursive function that calculates the size of TreeNode and thus update the size of its ancestors
void Tree::updateSize(TreeNode* node){
    if (node == nullptr) {
        return;
    }
    int totalSize = 0;
    for (int i = 0; i < node->children.size(); i++) {
        totalSize += node->children[i]->size;
    }

    /*
        1st case (node is the root): the root's size is equal to its children's size (since its size by default is 0)
        2nd case (node is a file): we call the function on its direct ancestor
        3rd case (node is neither root nor a file => node is a folder) : the node's size is equal to its children's size plus 10 (since its size by default is 10)
    */
    if(node == root){
        node->size = totalSize;
    }else if(node->isFile){
        updateSize(node->parent);
    }else{
        node->size = totalSize + 10;
    }

    // As long as node is not the root, keep calling the function on the node's parent
    if (node != root) {
        updateSize(node->parent);
    }
}

// Prints all the paths of a given file name (The search starts from a given pointer) (Pre-order Traversal)
void Tree::find_helper(TreeNode *ptr, string name){
    // Kepp track of the current's original position
    TreeNode* tracker = current;

    // Base condition: if ptr's name corresponds to the target name
    if(ptr->name == name){
        // assign current to ptr (in order to perform pwd())
        current = ptr;
        cout << pwd() << endl;
    }

    // Keep calling the function on the children of ptr
    for(int i = 0; i < ptr->children.size(); i++){
        find_helper(ptr->children[i], name);
    }

    // Assign current to its original position
    current = tracker;
}

//Traverses and writes recrusively the vfs data (Pre-order Style)
void Tree::write(ofstream &fout, TreeNode *ptr) {
    current = ptr;
    fout << pwd() << "," << ptr->size << "," << ptr->date << endl;
    for (int i = 0; i < ptr->children.size(); i++) {
        write(fout, ptr->children[i]);
    }
}



//Destructor
Tree::~Tree(){

    write(ofile, root);// Load the file system into the "vfs.dat"
    deleteNode(root);// Delete all the nodes

    ofile.close();// Close the output file (vfs.dat)
}

