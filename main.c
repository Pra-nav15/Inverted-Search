/*
                         Project Documentation – Inverted Search
Name: Pranav Prasad
Date: 7/1/2026
Description:
• This project is a Command Line Based Inverted Search Engine implemented in C.
• Inverted Search is a data structure technique used to map words to the documents in which they appear.
• The system scans multiple text files and builds an inverted index for fast word-based searching.
• Each unique word is stored along with the list of files in which it occurs and its frequency.
• The project uses Hash Tables for indexing words based on their first character.
• Collision handling in the hash table is implemented using Linked Lists(SLL).
• The database uses a two-level linked structure where each main node stores a word and its file count, and each sub node stores the corresponding filename and word counts.
• Filenames provided via command line are validated for uniqueness, existence, and non-empty content.
• The Create Database operation scans files, tokenizes words, and builds the inverted index dynamically.
• The Display Database operation prints all indexed words along with their file counts and frequencies.
• The Search Database operation locates a word and displays the list of files and occurrence count.
• The Update Database operation loads data from a previously saved database file and updates the index.
• During update, processed filenames are removed from the filename linked list to avoid duplication.
• The Save Database operation writes the current database into a file using a predefined format.
• File parsing uses delimiters and tokenization to reconstruct the database accurately.
• Proper validations are implemented for file format, database state, and invalid user operations.
• This project uses structures, pointers, linked lists, hash tables, dynamic memory allocation and file handling.
• The system demonstrates real-world applications such as search engines and document retrieval systems.
• Advantages include fast search operations, modular design, and efficient data organization.
• This project helps in understanding how text indexing and search engines work internally.
*/
#include "invsearch.h"

int main(int argc, char* argv[])
{
    filenames_t* head = NULL; // Head pointer for linked list of filenames
    db_status status = db_empty; // Track database status (empty, created, updated)
    hashtable_t hash_table[28]; // Hash table with 28 slots (a–z, digits, special chars)
    for (int i = 0;i < 28;i++) // Initialize hash table
    {
        hash_table[i].index = i;
        hash_table[i].h_link = NULL;
    }
    // Validate command-line arguments and files
    if (read_and_validate(argc, argv, &head) == FAILURE)
    {
        printf("\033[1;31mCommand Line Validations Failed\033[0m\n");
        return FAILURE;
    }
    int choice; // Variable to store user menu choice
    while (1)
    {
       printf("\033[1;33m");
        printf("+================================================+\n");
        printf("|                    MAIN MENU                   |\n");
        printf("+================================================+\n");
        printf("| 1  Create Database      | 4  Update Database   |\n");
        printf("| 2  Display Database     | 5  Save Database     |\n");
        printf("| 3  Search Database      | 6  Exit              |\n");
        printf("+================================================+\n");
        printf("\033[1;36mEnter your choice [1-6]: \033[0m");
        scanf("%d", &choice); // Read user choice
        switch (choice)
        {
        case 1:  // Create Database
            if (status == db_created)
            {
                printf("\033[1;31mError :Database Already Created\033[0m\n");
            }
            else if (status == db_updated)
            {
                printf("\033[1;31mError :Cannot Create After the Database is Updated\033[0m\n");
            }
            else
            {
                if (create_database(head, hash_table) == SUCCESS)
                {
                    printf("\033[1;32mDatabase Created Successfully\033[0m\n");
                    status = db_created;
                }
            }
            break;
        case 2: // Display Database
            if (status == db_empty)
            {
                printf("\033[1;31mDatabase Not Created Yet.Please Create Database First\033[0m\n");
            }
            else if (display_database(hash_table) == FAILURE)
            {
                printf("\033[1;31mNothing to Display in Database\033[0m");
            }
            break;
        case 3: // Search Database
            if (status == db_empty)
            {
                printf("\033[1;31mError :Database is Not Even Created.Please Create Database First\033[0m\n");
            }
            else
            {
                char search_word[WORD_SIZE]; // Buffer for search word
                printf("\033[1;36mEnter Word to Search: \033[0m");
                scanf("%s", search_word);
                if (search_database(hash_table, search_word) == DATA_NOT_FOUND)
                {
                    printf("\033[1;31mWord Not Found in Database\033[0m\n");
                }
            }
            break;
        case 4: // Update Database
            if (status == db_empty) // update is possible even if database is empty
            {
                if (update_database(&head, hash_table) == SUCCESS)
                {
                    status = db_updated;
                    printf("\033[1;32mDatabase Updated Successfully\033[0m\n");
                }
                else
                {
                    printf("\033[1;31mNo Existing Database File Found. Please Create Database File First\033[0m\n");
                }
            }
            else if (status == db_created) // update after create possible for new files
            {
                if (update_database(&head, hash_table) == SUCCESS)
                {
                    status = db_updated;
                    printf("\033[1;32mDatabase Updated Successfully\033[0m\n");
                }
            }
            else if (status == db_updated) // update after update is not possible
            {
                printf("\033[1;31mWe Cannot Update an Updated Database\033[0m\n");
            }
            break;
        case 5: // Save Database
            if (save_database(hash_table) == SUCCESS)
            {
                printf("\033[1;32mDatabase Saved Successfully\033[0m\n");
            }
            else
            {
                printf("\033[1;31mFailed to Save Database\033[0m\n");
            }
            break;
        case 6:  // Exit
            printf("\033[1;33mExiting........\033[0m\n");
            return EXIT;
            break;
        default: // Invalid choice
            printf("\033[1;31mInvalid Choice Entered,Try Again\033[0m\n");
        }
    }
}