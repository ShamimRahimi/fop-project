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
   
    if (access(filename, F_OK) == 0) {
        printf("%s already exists" , filename);
    } else {
        FILE *fp;
        fp=fopen(filename, "w");
        fclose(fp);
    }
  
    if(val[0]==' ' && val[1]=='-' && val[2]=='-' && val[3]=='f' && val[4]=='i' && val[5]=='l' && val[6]=='e'){
        if(val2[0]==' ' && val[1]=='-' && val[2]=='-' && val[3]=='f' && val[4]=='i' && val[5]=='l'){
            
        }
    }

   
}

int main(){
    
    scanf("%[^\n]%*c" , command );
    char command_backup[1000];
    strcpy(command_backup , command);
    
    if( !strcmp (strtok(command_backup, " ") , "createfile")){
        createfile();
    }
    
    return 0;
}
