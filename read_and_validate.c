#include "invsearch.h"

int read_and_validate(int argc, char* argv[], filenames_t** head)
{
    int flag;
    if (argc < 2)  // Check if at least one file is provided
    {
        printf("\033[1;31mError! --> Usage: ./a.out file1.txt file2.txt\033[0m\n");
        return FAILURE;
    }
    for (int i = 1; i < argc; i++) // Loop through all command-line arguments 
    {
        if (open_files(argv[i]) == SUCCESS) // Validate file
        {
            filenames_t* temp = *head;
            flag = 0;
            while (temp != NULL) // Traverse linked list of filenames
            {
                if (strcmp(temp->file_name, argv[i]) == 0) //duplicate check
                {
                    printf("\033[1;34mDuplicate Found\033[0m: %s\n", argv[i]);
                    flag = 1; // flag duplicate
                    break;
                }
                temp = temp->f_link; // Move to next file node
            }
            if (flag == 0) // If not duplicate, add to linked list
            {
                filenames_t* new = malloc(sizeof(filenames_t)); // Allocate new node
                strcpy(new->file_name, argv[i]); // Copy filename
                new->f_link = *head; // Insert at head
                *head = new; // Update head pointer
            }
        }
        else if (open_files(argv[i]) == FILE_EMPTY) // File exists but empty
        {
            printf("\033[1;34mFile is Empty\033[0m\n");
            return FAILURE;
        }
        else // File cannot be opened
        {
            printf("\033[1;31mError!: Files Cannot be opened\033[0m\n");
            return FAILURE;
        }
    }
    printf("\033[1;32mAll Files Validated Successfully\033[0m\n");
    return SUCCESS;
}

int open_files(char* argv)
{
    char* exten = strrchr(argv, '.'); // Find file extension
    if (exten != NULL  && strcmp(exten, ".txt") == 0) // Check if extension is ".txt"
    {
        FILE *fptr = fopen(argv, "r"); //open the file
        if (fptr != NULL)
        {
            fseek(fptr, 0, SEEK_END);  // Move to end of file
            if (ftell(fptr) <= 0) //empty file
            {
                return FILE_EMPTY;
            }
            else //file has some contents
            {
                return SUCCESS;
            }
        }
        else  // File cannot be opened
        { 
            return FAILURE;
        }
    }
}