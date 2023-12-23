# Virtual File System

## Introdution:

In this assignment, I will develop a virtual filesystem (VFS). A user can create/delete/move folders and files, among other operations described below. The filesystem should be organized as a Tree. Each **Node** contains metadata about the node (e.g., file or folder, size, date). A folder can have zero or many folders and files, while a file is considered as a leaf node only. Deleting a file puts the node’s element in a limited size queue (the Bin/Trash) which can be emptied manually or automatically. The interface should allow a user to navigate and perform the described tasks below. At the beginning and end of the session, the file system is loaded, and dumped to the disk, respectively.
## Implementation:

### Overview:

When your program is launched, users will receive a greeting and see a command prompt. Users can enter one of the provided commands. With these commands, the user has the ability to perform various actions such as creating nodes(folders or files), navigating through the directory tree, deleting, moving, and more. The default starting point for the virtual filesystem is the root node (see the figure below). As users navigate through the file system, it's crucial to track and update the current inode location. Users can interact with the system by issuing commands until they enter the "exit" command. When the program starts, it loads an existing filesystem structure from "vfs.dat". If "vfs.dat" doesn't exist, the program assumes a system with just a root node.

### Commends to implement:

When your program starts, the user is greeted and presented with a prompt to enter one of the commands below. By default, the system is initiated at the root of the virtual filesystem. The user is able to interact with the system (using the commands) until an exit command is issued.
(Bonus Feature) When the program starts, it loads a pre-existing filesystem structure from vfs.dat (see visual example above). If the file does not exist, assume starting from just a root inode.
As a user navigates through the file system, you must keep track of the current inode folder location.
Note: in blue are user specified names or parameters
1. help
 - Prints the following menu of commands
2. pwd
 - Prints the path of current inode
3. ls
 - Prints the children of the current inode (if folder, error otherwise)
 - Each line shows: filetype (dir/file), filename, size, date
 - ls sort: order by descending file size, use bubble sort
4. mkdir foldername
 - Creates a folder under the current folder
5. touch filename size
 - Creates a file under the current inode location with the specified filename, size, and current datetime
6. cd
 - cd foldername: change current inode to the specified folder
 - cd filename: return an error
 - cd .. changes current inode to its parent folder
 - cd - changes current inode to the previous working directory
 - cd changes current inode to root
 - cd /my/path/name changes the current inode to the specified path if it exists
7. (find foldername) or (find filename) 
 - Returns the path of the file (or the folder) if it exists
 - You should print all matching paths. The same name may exist in different locations ○ Starts the search from the root folder
8. mv filename foldername 
 - Moves a file located under the current inode location, to the specified folder path
 - The specified file and folder have to be one of the current inode’s children (an error is returned otherwise)
9. (rm foldername) or (rm filename)
 - Removes the specified folder or file and puts it in a Queue of MAXBIN=10
 - The specified file or folder has to be one of the current inode’s children (an error is returned otherwise)
10. Implement mv and rm on arbitrary inode locations 
 - The inode and destination folder are specified using a path
 = Examples:
   ■ mv /user/contact.txt /system/tmp ■ mv /user/tmp /user/
   ■ rm /user/contact.txt
   ■ rm /user/tmp
11. size foldername or filename
 - Returns the total size of the folder, including all its subfiles, or the size of the file
12. emptybin
 - Empties the bin
13. showbin
 - Shows the oldest inode of the bin, including its path
14. recover 
 - Reinstates the oldest inode back from the bin to its original position in the tree (if the path doesn’t exist anymore, an error is returned)
15. Exit
 - The program stops. If you implement the bonus feature then the filesystem is saved in the format of the vfs.dat example


