#include "invsearch.h"

int create_database(filenames_t* head, hashtable_t* hash_table)
{
    filenames_t* temp = head; // Pointer to traverse file list
    char word[30]; // Buffer to store each word
    while (temp != NULL)   // Loop through all files
    {
        FILE* fptr = fopen(temp->file_name, "r"); // Open current file
        if (fptr == NULL)  // Check if file opened successfully
        {
            printf("\033[1;31mError: File Cannot be Opened\033[0m");
            return FAILURE;
        }
        while (fscanf(fptr, "%s", word) != EOF) // Read words until EOF
        {
            int index = hash_index(word[0]); // Get hash index based on first character of word
            if (hash_table[index].h_link == NULL) // Case 1: No mainnode exists at this index
            {
                mainnode_t* m_new = malloc(sizeof(mainnode_t)); // Allocate new mainnode
                subnode_t* s_new = malloc(sizeof(subnode_t));   // Allocate new subnode
                if (m_new == NULL || s_new == NULL)   // Check allocation
                {
                    return FAILURE;
                }
                m_new->file_count = 1;  // First file occurrence
                strcpy(m_new->word, word); // Store word
                m_new->m_link = NULL; // No next mainnode yet
                m_new->s_link = s_new; // Link to subnode

                s_new->word_count = 1;  // Word appears once
                strcpy(s_new->file_name, temp->file_name); // Store file name
                s_new->s_link = NULL; // No next subnode yet

                hash_table[index].h_link = m_new; // Link mainnode to hash table
            }
            else    // Case 2: Mainnode exists at this index
            {
                mainnode_t* main_temp = hash_table[index].h_link;  // Traverse mainnode list
                mainnode_t* main_prev = NULL;
                int found = 0; // Flag for word found
                while (main_temp != NULL)
                {
                    if (strcmp(main_temp->word, word) == 0) // Word already exists
                    {
                        found = 1;
                        subnode_t* sub_temp = main_temp->s_link; // Traverse subnode list
                        subnode_t* sub_prev = NULL;
                        int f_found = 0; // Flag for file found
                        while (sub_temp != NULL)
                        {
                            if (strcmp(sub_temp->file_name, temp->file_name) == 0)
                            {
                                f_found = 1; // File already exists
                                sub_temp->word_count++;  // Increment word count
                                break;
                            }
                            sub_prev = sub_temp;
                            sub_temp = sub_temp->s_link;
                        }
                        if (f_found == 0)  // File not found, create new subnode
                        {
                            subnode_t* s_new = malloc(sizeof(subnode_t));
                            if (s_new == NULL)
                            {
                                return FAILURE;
                            }
                            s_new->word_count = 1;  // First occurrence in this file
                            strcpy(s_new->file_name, temp->file_name);
                            s_new->s_link = NULL; 
                            sub_prev->s_link = s_new; // Link new subnode
                            main_temp->file_count++; // Increment file count

                        }
                        break;  // Exit after handling word
                    }
                    main_prev = main_temp;    // Move to next mainnode
                    main_temp = main_temp->m_link;
                }
                if (found == 0) // Word not found, create new mainnode and subnode
                {
                    mainnode_t* m_new = malloc(sizeof(mainnode_t));
                    subnode_t* s_new = malloc(sizeof(subnode_t));
                    if (m_new == NULL || s_new == NULL)
                    {
                        return FAILURE;
                    }
                    m_new->file_count = 1; // First file occurrence
                    strcpy(m_new->word, word);  // Store word
                    m_new->m_link = NULL; // No next mainnode yet
                    m_new->s_link = s_new;    // Link to subnode
                    s_new->word_count = 1; // Word appears once
                    strcpy(s_new->file_name, temp->file_name); // Store file name
                    s_new->s_link = NULL; // No next subnode yet
                    main_prev->m_link = m_new;  // Link new mainnode
                }
            }
        }
        fclose(fptr);   // Close current file
        temp = temp->f_link; // Move to next file
    }
    return SUCCESS;
}

int hash_index(char ch)
{
    if (isalpha(ch)) // for alphabets
    {
        int ret = tolower(ch) - 97;  // Convert to lowercase and map 'a' → 0, 'b' → 1, etc.
        return ret;
    }
    else if (isdigit(ch))
    {
        return 26; // for digits 0 to 9 Map all digits to index 26
    }
    else
    {
        return 27; //Map special characters to index 27
    }
}