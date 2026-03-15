#include "invsearch.h"

int search_database(hashtable_t* hash_arr, char* word)
{
    if (hash_arr == NULL) // Check if hash table is valid
    {
        return FAILURE;
    }
    int index = hash_index(word[0]);  // Get hash index based on first character of word
    mainnode_t* main_temp = hash_arr[index].h_link; // Pointer to traverse mainnode list at index
    while (main_temp != NULL)  // Traverse mainnode list
    {
        if (strcmp(main_temp->word, word) == 0)  // Check if word matches
        {
            // Word found: print number of files containing it
            printf("\033[1;32mThis Word is found in\033[1;33m %d \033[1;32mfiles\033[0m\n", main_temp->file_count);
            subnode_t* sub_temp = main_temp->s_link; // Traverse subnode list
            while (sub_temp != NULL)
            {
                 // Print file name and word count for each subnode
                printf("\033[1;35mFile Name is \033[1;33m %s\033[0m\n", sub_temp->file_name);
                printf("\033[1;35mWord Count is \033[1;33m %d\033[0m\n", sub_temp->word_count);
                sub_temp = sub_temp->s_link; // Move to next subnode
            }
            return SUCCESS;
        }
        else
        {
            main_temp = main_temp->m_link; // Move to next mainnode if word not matched
        }
    }
    return DATA_NOT_FOUND;  // Word not found in database
}