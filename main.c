#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char command[1000];

void createfile(){
    char command_backup2[1000];
    strcpy(command_backup2 , command);
    char* val = strchr(command_backup2 , ' ');//--file oomade ya na
    char* val2 = strchr(val , ' '); // / biad
    char* slash_filename = strrchr(command_backup2 , '/');
    char* filename=slash_filename+1;
   
    
  
    if(val[0]==' ' && val[1]=='-' && val[2]=='-' && val[3]=='f' && val[4]=='i' && val[5]=='l' && val[6]=='e'){
        if(val2[0]==' ' && val[1]=='-' && val[2]=='-' && val[3]=='f' && val[4]=='i' && val[5]=='l'){
            if (access(filename, F_OK) == 0) {
             printf("%s already exists" , filename);
             }
            else {
            FILE *fp;
            fp=fopen(filename, "w");
            fclose(fp);
            }
        }
    }
    else{
        printf("Invalid Command\n");
    }
}

void cat(){
    char command_backup2[1000];
    strcpy(command_backup2 , command);
    char* val = strchr(command_backup2 , ' ');
    char* slash_filename = strrchr(command_backup2 , ' ');
    char* filename=slash_filename+1;
    
     if(val[0]==' ' && val[1]=='-' && val[2]=='-' && val[3]=='f' && val[4]=='i' && val[5]=='l' && val[6]=='e'){
        FILE* ptr;
        char ch;
        ptr = fopen(filename, "r");
 
            if (NULL == ptr) {
            printf("file can't be opened \n");
            }
 
  
            while (ch != EOF){
                ch = fgetc(ptr);
                printf("%c", ch);
            }

            fclose(ptr);
    }
    else{
        printf("Invalid Command\n");
    }
    
}

int main(){
    
    scanf("%[^\n]%*c" , command );
    char command_backup[1000];
    strcpy(command_backup , command);
    
    if( !strcmp (strtok(command_backup, " ") , "createfile")){
        createfile();
    }

    if( !strcmp (strtok(command_backup, " ") , "cat")){
        cat();
    }
    
    return 0;
}
