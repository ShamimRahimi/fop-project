#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



void createfile(char* commandkh){
    char* command_backup3 = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup3 , commandkh);
    char* slash_filename = strrchr(command_backup3 , '/');
    char* filename=slash_filename+1;

    char* chertt = strtok(commandkh, " ");
    char* word_numm[100];
    

    int j = 0;
    while (chertt != NULL)
        {
            word_numm[j] = chertt;
            chertt = strtok(NULL," ");
            j++;
        }
    char* che = strtok(word_numm[2] , " / ");
    char* address_num[100];
  
   
    int cnt = 0;
    int k = 0;
    while (che != NULL){
            address_num[k] = che;
            che = strtok(NULL," / ");
            k++;
            cnt++;
        }

   chdir("..");

    if(!strcmp(word_numm[1] , "--file")){
        for(int ii = 0 ; ii<cnt-1 ; ii++){
            int res = chdir(address_num[ii]);
            if(res==-1){
                mkdir(address_num[ii],0777);
                chdir(address_num[ii]);
            }      
        }
        if(access(filename, F_OK) == 0) {
            printf("%s already exists" , filename);
        }
        else{
            FILE *fp;
            fp=fopen(filename, "w");
            fclose(fp);
            printf("%s successfully created!" , filename);
        }
        for(int jj = 0 ; jj<cnt-2 ; jj++){
            chdir("..");
        }
        }
        else{
            printf("Invalid Command\n");
        }
  
  }

void cat(char* commandkh){
    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , commandkh);
    char* slash_filename = strrchr(command_backup , '/');
    char* filename=slash_filename+1;

    char* chertt = strtok(commandkh, " ");
    char* word_numm[100];
    

    int j = 0;
    while (chertt != NULL)
        {
            word_numm[j] = chertt;
            chertt = strtok(NULL," ");
            j++;
        }
    char* che = strtok(word_numm[2] , " / ");
    char* address_num[100];
  
   
    int cnt = 0;
    int k = 0;
    while (che != NULL){
            address_num[k] = che;
            che = strtok(NULL," / ");
            k++;
            cnt++;
        }

        FILE* ptr;
        char ch[1000];
    char s[100];
    if(!strcmp(word_numm[1] , "--file")){
        for(int ii = 1 ; ii<cnt-1 ; ii++){
            chdir(address_num[ii]);
        }
        
        ptr = fopen(filename, "r");
 
            if (NULL != ptr) {
                while(fgets(ch , 1000 , ptr)){
                    printf("%s" , ch);
                }            
            }

            else{
                printf("file can't be opened \n");
            }
            

        fclose(ptr);
         for(int jj = 0 ; jj<cnt-2 ; jj++){
            chdir("..");
         }
         if(strcmp(s, "/Users/shamim/root")){
            chdir("root");
         }
        //  getcwd(s, sizeof(s));
        //  printf("Current working dir: %s\n", s);
        
            
    }
    else{
        printf("Invalid Command\n");
    }
    
}

int main(){

    while(1){
        char* command = (char*) calloc(2000 , sizeof(char));
        scanf("%[^\n]%*c" , command );
        char* command_backup = (char*) calloc(2000 , sizeof(char));
        strcpy(command_backup , command);
        char* chert = strtok(command, " ");
        char* word_num[100];
        
        
        int i = 0;
        while (chert != NULL)
        {
            word_num[i] = chert;
            chert = strtok(NULL," ");
            i++;
        }
        
        if( !strcmp (strtok(word_num[0], " ") , "createfile")){
            createfile(command_backup);
        }
        
        if( !strcmp (strtok(word_num[0], " ") , "cat")){
            cat(command_backup);
        }
    }
    return 0;
}

