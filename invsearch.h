#ifndef INVSEARCH_H
#define INVSEARCH_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define WORD_SIZE 26 // Maximum word size
#define FNAME_SIZE 20 // Maximum file name size
#define SUCCESS 1
#define FAILURE 0
#define DATA_NOT_FOUND -1
#define EXIT -2  // Terminate program
#define FILE_EMPTY -3
#define INVALID -4 // Invalid extension status code

typedef enum // Enum to represent database status
{
    db_empty,
    db_created,
    db_updated,
}db_status;

// Structure to store file names
typedef struct file
{
    char file_name[WORD_SIZE]; // File name
    struct file* f_link;  // link to next file node
}
filenames_t;
// Structure for subnode (stores word occurrence in files)
typedef struct subnode
{
    char file_name[FNAME_SIZE]; // File name containing the word
    int word_count; // Count of word occurrences
    struct subnode* s_link;  // link to next subnode
}subnode_t;
// Structure for mainnode (stores words and linked subnodes)
typedef struct mainnode
{
    int file_count; // Number of files containing the word
    char word[WORD_SIZE]; // Word in the file
    struct mainnode* m_link; // link to next mainnode
    subnode_t *s_link; // link to subnode list
}mainnode_t;
// Structure for hashtable (stores index and mainnode link)
typedef struct hashtable
{
    int index; // Hash index
    mainnode_t* h_link;   // link to mainnode list
}hashtable_t;

// Function declarations
int read_and_validate(int argc, char* argv[], filenames_t** head); // Validate input files
int open_files(char* argv); //open files passed via command line
int hash_index(char ch); // find the hash index to store to hash table
int display_database(hashtable_t* hash_table); // display the database
int create_database(filenames_t* head, hashtable_t* hash_table); // create the database from files
int search_database(hashtable_t* hash_table, char* word); // search a\for a word in database
int save_database(hashtable_t* hash_table); // save the database to a file
int update_database(filenames_t** head,hashtable_t* hash_table); //update the database

#endif
