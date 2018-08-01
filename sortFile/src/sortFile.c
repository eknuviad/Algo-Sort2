/*
 ============================================================================
 Description : File Sorting Program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBUF 100

//BinaryTree structure
struct BinaryTree
{

	char value[100];			//character array to store string names
	struct BinaryTree* left;
	struct BinaryTree* right; 	// these are two address

};

//Method to traverse binary tree inorder
void inorder_traverse_binaryTree(struct BinaryTree* bt)
{

	if(bt->left != NULL)									//traverse Tree to the left until left is null
		inorder_traverse_binaryTree(bt->left);
	printf("%s\n",bt->value);								//then print values at node (left-root-right)
	if(bt->right !=NULL)
		inorder_traverse_binaryTree(bt->right);

}

//Method to create an instance of a binary tree structure with new_value from main
struct BinaryTree* create_one_binaryTree(char new_value[])
{

	struct BinaryTree* tree_add = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
	char array[100];
	strcpy(array,new_value);							//copy into an array
	strcpy(tree_add->value,array);						//assign by copying array value to tree value
	tree_add->left = NULL;
	tree_add->right = NULL;
	return tree_add;

}

//add a node to the tree
void addNode(char* new_value,struct BinaryTree* bt)
{
	int compvalue;
	compvalue = strcmp(new_value,bt->value);	//compare incoming string with string in root

	if (compvalue<0)
	{
		// if it is smaller than root, add it to the left tree

		if(bt->left != NULL)
		{
			addNode(new_value,bt->left);
		}
		else
		{
			bt->left = create_one_binaryTree(new_value);
		}

	}else{
		// if it is bigger than the root, add it to the right tree
		if(bt->right != NULL){
			addNode(new_value,bt->right);
		}
		else
		{
			bt->right = create_one_binaryTree(new_value);
		}
	}
}


// Main method to read from file and pass names read to binary Tree
int main(int argc, char *argv[]) {
	// Internal declarations
	FILE * FileD; 					// File descriptor (an object)!
	char *line; 					// Pointer to buffer used by getline
	int bufsize = MAXBUF; 			// Size of buffer to allocate
	int linelen; 					// Length of string returned (getline)
	// Argument check
	if (argc != 2) {
		printf("Usage: fileReader [text file name]\n");
		return -1;
	}

	// Attempt to open the user-specified file. If no file with
	// the supplied name is found, exit the program with an error
	// message.
	if ((FileD=fopen(argv[1],"r"))==NULL) {
		printf("Can't read from file %s\n",argv[1]);
		return -2;
	}

	// Allocate a buffer for the getline function to return data to.
	line=(char *)malloc(bufsize+1);
	if (line==NULL) {
		printf("Unable to allocate a buffer for reading.\n");
		return -3;
	}
	// If the file exists and a buffer was successfully allocated,
	// use the getline function to read the file libe by line.

	printf("Assignment 6 - File Sorting Program\n");
	printf("Enter name of file to sort: %s\n",argv[1]);


	struct BinaryTree* my_bt_add;								//create a pointer to a binaryTree structure

	int count = 0;												//begin a counter

	while ((linelen=getline(&line,(size_t *)&bufsize,FileD))>0){
		count++;
		if(count == 1){
			char n_array[100];									//check if count==1
			line[strlen(line)-1]='\0';							//remove the newline delimiter
			strcpy(n_array,line);								//copy names into n_array
			my_bt_add = create_one_binaryTree(n_array);			//create a root with the first name
		}
		else {													//if count is different from 1
			char n2_array[100];
			line[strlen(line)-1]='\0';
			strcpy(n2_array,line);
			addNode(n2_array,my_bt_add);						//use addNode method to begin comparison to root value
		}

	}

	printf("\nFile in sort order:\n\n");
	inorder_traverse_binaryTree(my_bt_add);						//traverse the Tree in order
	printf("\n");
	printf("Program terminated\n");
	return EXIT_SUCCESS;
}


