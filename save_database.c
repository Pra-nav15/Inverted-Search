#include "invsearch.h"

int save_database(hashtable_t *hash_table)
{
    if (hash_table == NULL) // Check if hash table is valid
    {
        return FAILURE;
    }
    char database[15];  // Buffer to store database file name
    printf("\033[1;34mEnter the database name: \033[0m");
    scanf("%s", database); // Read database file name from user
    char* exten = strstr(database, ".txt");
    if (exten == NULL || strcmp(exten, ".txt") != 0) // Check if file has ".txt" extension
    {
        printf("\033[1;31mError :Database File Should be .txt format\033[0m\n");
        return INVALID;
    }
    FILE* fptr = fopen(database, "w"); // Open file in write mode
    if (fptr == NULL)
    {
        printf("\033[1;31mError :Cannot Open DataBase File\033[0m\n");
        return FAILURE;
    }
    for (int i = 0; i < 28; i++) // Traverse all hash table indices
    {
        if (hash_table[i].h_link != NULL) // If index has a mainnode
        {
            mainnode_t* main_temp = hash_table[i].h_link; // Traverse mainnode list
            while (main_temp != NULL)
            {
                 // Write index, word, and file count to database file
                fprintf(fptr, "#%d;%s;%d;", i, main_temp->word, main_temp->file_count);
                subnode_t *sub_temp = main_temp->s_link; // Traverse subnode list
                while (sub_temp != NULL)
                {
                    // Write file name and word count for each subnode
                    fprintf(fptr, "%s;%d;", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->s_link; // Move to next subnode
                }
                fprintf(fptr, "#\n"); // end of record marker
                main_temp = main_temp->m_link;  // Move to next mainnode
            }
        }
    }
    fclose(fptr);        // Close database file
    return SUCCESS;
}