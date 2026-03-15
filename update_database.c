#include"invsearch.h"

int update_database(filenames_t** head, hashtable_t* hash_table)
{
    char db_file[100]; // Store database filename
    char backup_file[100]; // Store database filename
    int index;  // Hash table index
    printf("\033[1;35mEnter the Database File to Update : \033[0m");
    scanf("%s", db_file);   // Read database filename from user
    char* exten = strstr(db_file, ".txt");
    if (exten == NULL || strcmp(exten, ".txt") != 0)  // Validate file extension for .txt
    {
        printf("\033[1;31mDatabase File should be in .txt\033[0m\n");
        return FAILURE;
    }
    FILE* fptr = fopen(db_file, "r");  // Open database file in read mode
    if (fptr == NULL)
    {
        printf("\033[1;31mFile Could Not be opened\033[0m\n");
        return FAILURE;
    }
      // Read database file entry by entry
    while (fscanf(fptr, "%s", db_file) != EOF)
    {
        if (db_file[0] == '#') // Validate database start marker #
        {
            char* token = strtok(db_file + 1, ";"); // Extract index token
            if(token == NULL)
            {
                return FAILURE;
            }
            index = atoi(token); // Convert index string to integer

            mainnode_t* m_new = malloc(sizeof(mainnode_t)); // Allocate a new main node
            if (m_new == NULL)
            {
                return FAILURE;
            }
            m_new->m_link = NULL; // Initialize main node link
            m_new->s_link = NULL; // Initialize subnode list
            strcpy(m_new->word, strtok(NULL, ";")); // Extract word
            m_new->file_count = atoi(strtok(NULL, ";")); // Extract file count
             // Create subnodes for each file entry
            for (int i = 0;i < m_new->file_count;i++)
            {
                subnode_t* s_new = malloc(sizeof(subnode_t)); // Allocate a new subnode
                if (s_new == NULL)
                {
                    return FAILURE;
                }
                strcpy(s_new->file_name, strtok(NULL, ";")); // Extract filename
                strcpy(backup_file, s_new->file_name); //Copy to Backup filename
                s_new->word_count = atoi(strtok(NULL, ";")); // Extract word count
                s_new->s_link = NULL; // Initialize subnode link
                filenames_t* temp = *head; // Traverse filename list
                filenames_t* prev = NULL; // Track previous node
                // Remove processed filename from list
                while (temp != NULL)
                {
                    if (strcmp(temp->file_name, backup_file) == 0) //check if file name and backup file name is same
                    {
                        if (prev == NULL)
                        {
                            *head = temp->f_link; // Update head pointer
                        }
                        else
                        {
                            prev->f_link = temp->f_link;  // Bypass node
                        }
                        filenames_t* delete = temp;  // Store node to delete
                        temp = temp->f_link;
                        free(delete); // Free node
                    }
                    else
                    {
                        prev = temp;  // Move previous pointer
                        temp = temp->f_link; // Move next
                    }
                }
                 // Insert subnode into subnode list
                if (m_new->s_link == NULL)
                {
                    m_new->s_link = s_new; // First subnode
                }
                else
                {
                    subnode_t* sub_temp = m_new->s_link;
                    while (sub_temp->s_link != NULL)
                    {
                        sub_temp = sub_temp->s_link; // Traverse subnode list
                    }
                    sub_temp->s_link = s_new; // Append subnode
                }
            }
             // Insert main node into hash table
            if (hash_table[index].h_link == NULL)
            {
                hash_table[index].h_link = m_new; // First main node
            }
            else
            {
                mainnode_t* main_temp = hash_table[index].h_link;
                while (main_temp->m_link != NULL)
                {
                    main_temp = main_temp->m_link; // Traverse main list
                }
                main_temp->m_link = m_new; // Append main node
            }
        }
        else
        {
            // Invalid database file format
            printf("\033[1;31mNo database file is detected\033[0m\n");
            fclose(fptr);
            return FAILURE;
        }
    }
    fclose(fptr); // Close database file
    return SUCCESS;

}