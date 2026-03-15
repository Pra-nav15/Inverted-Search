#include "invsearch.h"

int display_database(hashtable_t* hash_table)
{
    if (hash_table == NULL) // Check if hash table is valid
    {
        return FAILURE; // Return failure if NULL
    }
    printf("\033[1;35m+------+------------+----------------+----------------------+------------+\033[0m\n");
    printf("\033[1;33m| %-3s | %-9s | %-14s | %-19s | %-10s |\033[0m\n","Index", "FileCount", "Word", "File Name", "Word Count");
    printf("\033[1;35m+------+------------+----------------+----------------------+------------+\033[0m\n");
    for (int i = 0;i < 28;i++) // Loop through all hash table indices
    {
        if (hash_table[i].h_link != NULL) // If index has a mainnode
        {
            mainnode_t* main_temp = hash_table[i].h_link; // temp variable to Traverse mainnode list
            while (main_temp != NULL)
            {
                subnode_t* sub_temp = main_temp->s_link; // temp variable to Traverse subnode list
                int first = 1;  // Flag for first subnode print
                while (sub_temp != NULL)
                {
                    if (first == 1)  // Print full row for first subnode
                    {
                        printf("\033[1;36m| %-4d | %-10d | %-14s | %-20s | %-10d |\033[0m\n", i, main_temp->file_count, main_temp->word,sub_temp->file_name, sub_temp->word_count);
                        first = 0; // Reset flag after first print
                    }
                    else // Print only file details for subsequent subnodes
                    {
                        printf("\033[1;36m| %-4s | %-10s | %-14s | %-20s | %-10d |\033[0m\n", " ", " ", " ", sub_temp->file_name, sub_temp->word_count);
                    }
                    sub_temp = sub_temp->s_link;  // Move to next subnode
                }
                main_temp = main_temp->m_link; // Move to next mainnode
            }
        }
    }
    printf("\033[1;35m+------+------------+----------------+----------------------+------------+\033[0m\n");
    return SUCCESS;
}