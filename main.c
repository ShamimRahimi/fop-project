#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

char* word_num[1000];
int cnt = 0;
long int lineno;
long int start_pos;

void go_to_folder(){

    cnt=0;
    char* che = strtok(word_num[2] , " / ");
    char* address_num[100];
  
    int k = 0;
    while (che != NULL){
            address_num[k] = che;
            che = strtok(NULL," / ");
            k++;
            cnt++;
        }

        for(int ii = 1 ; ii<cnt-1 ; ii++){
            chdir(address_num[ii]);
        }

}

void return_back(){

    char s[100];
    for(int jj = 0 ; jj<cnt-2 ; jj++){
            chdir("..");
         }
         getcwd(s, sizeof(s));
         
         if(strcmp(s, "/Users/shamim/root")){
            chdir("root");
         }

}

void find_pos(char* wordnum){

    lineno = 0;
    start_pos = 0;
    char* pos= strrchr(wordnum , ':');
    char* poss=pos+1;
    lineno = strtol(wordnum , &wordnum , 10 );
    start_pos = strtol(poss , &poss , 10 );

}

int copytoclipboard(const char *str) {

    char cmd[100];
    sprintf(cmd , "echo '%s' | pbcopy" , str);

    return system(cmd);
}

void space_seperate(char* command[]){

    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , *command);
    char* chert = strtok(*command, " ");
    
    
    int i = 0;
    while (chert != NULL)
    {
        word_num[i] = chert;
        chert = strtok(NULL," ");
        i++;
    }
}

void createfile(char* command){

    space_seperate(&command);
    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    char* che = strtok(word_num[2] , " / ");
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

    if(!strcmp(word_num[1] , "--file")){
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

void cat(char* command){
   
    space_seperate(&command);
    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    go_to_folder();
    
        FILE* ptr;
        char ch[1000]={};
    if(!strcmp(word_num[1] , "--file")){
        
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

        return_back();
    }
    else{
        printf("Invalid Command\n");
    }
    
}

void insertstr(char* command){
    
   
    space_seperate(&command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    char* string = word_num[4];
   
    find_pos(word_num[6]);

    char content[1000000]={};
    char rest[100000]={};

    go_to_folder();
    
    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "--str")) && (!strcmp(word_num[5] , "-pos"))){
        FILE* fptr;
        char ch;
        int k=0;
        int cnt_line = 1;
        int cnt_c = 0;
        fptr = fopen(filename, "r");
        
        if(fptr == NULL){
            printf("file doesn't exist \n");
        }
            
        
        while((ch = fgetc(fptr))!= EOF) {
            if((cnt_line == lineno) && (cnt_c == start_pos)){
                break;
            }
            content[k]=ch;
            cnt_c++;
            if(ch == '\n'){
                cnt_line++;
                cnt_c=0;
            }
            k++;
        }
   
        int kk = 0;
        
        while (ch != EOF)
        {
            rest[kk] = ch;
            kk++;
            ch = fgetc(fptr);
        }
        
        fclose(fptr);
        fptr = fopen(filename, "w");
        fprintf(fptr , "%s%s%s", content , string , rest);
        fclose(fptr);
        cnt_line = 0;
        ch = 0;

        return_back();

    }
     else{
         printf("Invalid Command\n");
     }

}

void removestr(char* command){

    space_seperate(&command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    find_pos(word_num[4]);

    long int size_removed = strtol(word_num[6] , &word_num[6] , 10 );

    char p1[1000000]={};
    char to_be_deleted[100]={};
    char p2[1000000]={};

    go_to_folder();

    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos")) && (!strcmp(word_num[5] , "-size"))){
        FILE* fptr;
        char ch;
        int k=0;
        int cnt_line = 1;
        int cnt_c = 0;
        fptr = fopen(filename, "r");
        
        if(fptr == NULL){
            printf("file doesn't exist \n");
        }
            
        
            while((ch = fgetc(fptr))!= EOF) {
                if((cnt_line == lineno) && (cnt_c == start_pos)){
                    break;
                }
                p1[k]=ch;
                cnt_c++;
                if(ch == '\n'){
                    cnt_line++;
                    cnt_c=0;
                }
                k++;
            }

            int kk=0;
            while((ch = fgetc(fptr))!= EOF) {
                p2[kk]=ch;
                kk++;
            }
            fclose(fptr);

            char* p22;
            fopen(filename , "w");
            if((!strcmp(word_num[7], "-f"))){
               
                p22 = p2+size_removed;
                fprintf(fptr , "%s%s" , p1 , p22);
            }

            else if((!strcmp(word_num[7], "-b"))){
                p1[k-(size_removed)] = '\0';
                fprintf(fptr , "%s%s" , p1 , p2);
            }
             fclose(fptr);

            return_back();
    }

    else{
    printf("Invalid Command");
    }
}

void copystr(char* command){

space_seperate(&command);

char* slash_filename = strrchr(word_num[2] , '/');
char* filename=slash_filename+1;

find_pos(word_num[4]);

long int size_copied = strtol(word_num[6] , &word_num[6] , 10 ) + 1;

char p1[1000];

if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos")) && (!strcmp(word_num[5] , "-size"))){
    go_to_folder();
    FILE* fptr;
    char ch;
    int k=0;
    int cnt_line = 1;
    int cnt_c = 0;
    fptr = fopen(filename, "r");
        
    if(fptr == NULL){
        printf("file doesn't exist \n");
    }
            
        
    while((ch = fgetc(fptr))!= EOF) {
        if((cnt_line == lineno) && (cnt_c == start_pos)){
            break;
        }
        p1[k]=ch;
        cnt_c++;
        k++;
        if(ch == '\n'){
            cnt_line++;
            cnt_c=0;
        }
    }


    if(!strcmp(word_num[7] , "-f")){
        int counter = 0 , kk = 0;
        char tocopy[size_copied];
        while(counter != (size_copied-1)){
            tocopy[kk]=ch;
            ch=fgetc(fptr);
            kk++;
            counter++;
        }
        copytoclipboard(tocopy);
    }

    if(!strcmp(word_num[7] , "-b")){
        int counter = 0 , kk = 0;
        char tocopy[size_copied];
        while(counter != size_copied){
            tocopy[kk]=p1[k-size_copied+1];
            k++;
            kk++;
            counter++;
        }
        copytoclipboard(tocopy);
    }
    fclose(fptr);
    return_back();
}

else{
     printf("Invalid Command");
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

        if( !strcmp (strtok(word_num[0], " ") , "insertstr")){
            insertstr(command_backup);
        }

        if( !strcmp (strtok(word_num[0], " ") , "removestr")){
            removestr(command_backup);
        }

        if( !strcmp (strtok(word_num[0], " ") , "copystr")){
            copystr(command_backup);
        }
    }
    return 0;
}
