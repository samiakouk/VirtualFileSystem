#include<iostream>
#include<sstream>
#include<stdlib.h>
#include "vfs.h"
using namespace std;

void listCommands()
{
	cout<<"Welcome to the Virtual File System:"<<endl
		<<"pwd                                         : Print the path of current file (or folder)"<<endl
		<<"ls                                          : Print the subfiles of the current folder (error otherwise)"<<endl
		<<"lsSort                                      : Print the subfiles of the current folder (error otherwise) in order (size)"<< endl
		<<"mkdir <foldername>                          : Create a folder under the current folder"<<endl
		<<"touch <filename, size>                      : Create a file under the current inode location with the specified filename, size, and current datetime"<<endl
		<<"cd                                          : Change the current working directory."<<endl
		<<"rm <foldername || filename>                 : Remove the specified folder or file given that the file/folder are within the current deirectory"<<endl
		<<"rm <folder's path || file's path>           : Remove the specified folder or file anywhere in the file system given its path"<<endl
		<<"size <path>                                 : Print total size of the folder, including all its subfiles, or the size of the file" << endl
		<<"find <foldername || filename>               : Return the path of the file (or the folder) if it exists"<<endl
		<<"showbin                                     : Show the oldest Folder/File of the bin, including its path"<<endl
		<<"emptybin                                    : Empty the bin" << endl
		<<"recover                                     : Reinstate the oldest inode back from the bin to its original position in the tree " << endl
		<<"mv <filename, foldername>                   : Move a file located under the current directory, to the specified folder" << endl
		<<"mv <file's path, folder's path>             : Move a file anywhere on the file system, to the specified folder path" << endl
		<<"help                                        : Print the following menu of commands"<<endl
		<<"exit                                        : Exit the Program"<<endl;
}

int main()
{
	Tree VFS;

	while(true)
	{
		string user_input;
		string command;
		string parameter1;
		string parameter2;
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			//Required commands
			if(command=="help")		         listCommands();
			else if(command=="pwd")			 cout << VFS.pwd() << endl;
			else if(command=="ls") 			 VFS.ls();
			else if(command=="lsSort" || user_input == "ls sort")       VFS.lsSort();
			else if(command=="mkdir")		 VFS.mkdir(parameter1);
			else if(command=="touch")		 VFS.touch(parameter1,stoi(parameter2));
			else if(command=="cd")			 VFS.cd(parameter1);
			else if(command=="rm")			 VFS.rm(parameter1);
			else if(command=="size")		 cout << VFS.size(parameter1) << "bytes. \n";
			else if(command=="showbin")		 VFS.showBin();
			else if(command=="emptybin")	 VFS.emptyBin();
			else if(command=="exit")		 {break; return(EXIT_SUCCESS);}

			//optional commands
			else if(command=="find")		 VFS.find(parameter1);
			else if(command=="mv")			 VFS.mv(parameter1, parameter2);
			else if(command=="recover")		 VFS.recover();
			else if(command=="clear")		 system("clear");
			else 							 cout<<command<<": command not found"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}
}
