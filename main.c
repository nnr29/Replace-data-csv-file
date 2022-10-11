#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME_SIZE 200
#define MAX_LINE 200
int replace();
FILE *file_ptr, *temp_file_ptr;                                                         //declaring two pointers main file pointer and temp file pointer
int main()
{
   replace();
   return 0;
}
int replace()
{
    char filename[FILENAME_SIZE]="edit_data.csv";
    char temp_filename[FILENAME_SIZE];                                                // store  temp filename array
    char buffer[MAX_LINE];                                                           // buffer array will store will store each line from the main file
    char *employee_name,*employee_id,*employee_salary;                              // This array will store data from the user
    int  replace_line = 0,track_data = 1,current_line = 1;
    if((file_ptr=fopen(filename,"r")) == NULL)                                     //opening the file in reading mode
    {
        printf("Error in opening the file");
        exit(1);
    }
    while(fgets(buffer,MAX_LINE,file_ptr))                                       //reads the data line by line
    {
        printf("%s",buffer);
    }
    fclose(file_ptr);
    strcpy(temp_filename, "temp--");                                           //copying the temp file with tempfilename format
    strcat(temp_filename, filename);                                          //string concatenate main array and temporary array
    employee_name=(char*)malloc(sizeof (char));                                                       //flush out the temporary data
    employee_id=(char*)malloc(sizeof (char));
    employee_salary=(char*)malloc(sizeof (char));

    printf("Enter the line number to be replaced\n");
    scanf("%d",&replace_line);

    printf("Enter the employee name\n");
    fflush(stdin);
    scanf("%s",employee_name);

    printf("Enter the employee id\n");
    fflush(stdin);
    scanf("%s",employee_id);

    printf("Enter the salary of the employee\n");
    fflush(stdin);
    scanf("%s",employee_salary);

    file_ptr=fopen(filename,"r");                                        //file opened in reading mode
    temp_file_ptr=fopen(temp_filename,"w");                             // file opened in writing mode

    if (file_ptr == NULL || temp_file_ptr == NULL)                    //if any one of the file is empty
    {
        printf("Error opening file \n");
        return 0;
    }
    do
    {
        fgets(buffer,MAX_LINE,file_ptr);
        if (feof(file_ptr)) track_data = 0;
        else if(current_line == replace_line)
        {
            strcat(employee_name,",");
            strcat(employee_name,employee_id);
            strcat(employee_name,",");
            strcat(employee_name,employee_salary);
            strcat(employee_name,"\n");
            fflush(stdin);
            fputs(employee_name,temp_file_ptr);
        }
        else
        {
            fputs(buffer,temp_file_ptr);                            //writing the data to the temporary file
        }
        current_line++;                                            //incrementing the current line
    }while (track_data);
    fclose(file_ptr);                                             //closing the main file
    fclose(temp_file_ptr);                                       //closing the temporary file

    remove(filename);                                          //delete the main file,rename the temporary file name as original file name
    rename(temp_filename,filename);

    free(employee_name);
    free(employee_id);
    free(employee_salary);

    return 0;
}
