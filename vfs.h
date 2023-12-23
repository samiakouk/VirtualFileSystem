#ifndef VFS_H
#define VFS_H

#include "myvector.hpp"
#include "myqueue.hpp"

#include<iostream>
#include<fstream>
#include<ctime>

using namespace std;



class TreeNode{
private:
	string name;
	int size;
	string date;

	TreeNode* parent;
	MyVector<TreeNode*> children;

	bool isFile;// true if file, false otherwise

	friend class Tree;
public:

	TreeNode();
	TreeNode(string name, int size, bool value);

};


class Tree{
private:
	TreeNode* root;
	TreeNode* current;
	TreeNode* prev;


	Queue<TreeNode*> bin;
	Queue<string> bin_paths;


public:
	
	Tree();
	~Tree();


    string pwd() const; // Prints the path of working directory (current TreeNode)
    void ls() const; // Lists the subfiles of the current folder
	void lsSort() const; // Lists the subfiles of the current folder in a sorted way
    void mkdir(string foldername); // Creates a folder within the current directory	 
    void touch(string filename, int size); // Creates a file within the current directory
	void cd(string arg); // Changes the current directory to another directory
    void rm(string name); // Removes a file/folder within the current directory and adds it to the bin
	int size(string path); // Returns the size of a file or folder (Taking into account potential subfiles)
    void emptyBin(); // Empties the bin
    void showBin(); // Shows the first deleted file along with its path
    void recover(); // Recovers the first deleted file
    void find(string name); // Prints all the paths given a file's name
    void mv(string filename, string foldername); // Moves a file inside a folder (given both the file and the folder are within the current directory or anywhere from the file system given their paths)

    


    // Helper methods
    TreeNode* getNode(string path);	//Helper method to get a pointer to TreeNode at given path
    void deleteNode(TreeNode* node); // Recursive method that deletes a TreeNode with all its descendants
	void updateSize(TreeNode* node); // Recursive function that calculate the size of TreeNode and thus update the size of its ancestors
	void find_helper(TreeNode *ptr, string name); // Helper method
	void write(ofstream &fout, TreeNode *ptr);	//traverse and write recrusively the vfs data
	

};


#endif