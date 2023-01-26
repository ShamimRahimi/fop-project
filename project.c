#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

char* word_num[1000];
char copied[1000];
int cnt = 0;
long int lineno;
long int start_pos;
int naro=0;
int i=0;
int tedad=0;


void space_seperate(char**);
void with_space(char*);
int go_to_folder();
void return_back();
void find_pos(char*);
int copytoclipboard(const char*);
void createfile(char*);
void cat(char*);
void insertstr(char*);
void removestr(char*);
void copystr(char*);
void pastestr(char*);
void take_parts(char* , char*);
void write_to_file(char* , char* , char* , char*);


// int check_dir(char* path){

//     char* che = strtok(word_num[2] , "/");
//     char* address_num[100];
   
//     int cnt = 0;
//     int k = 0;
//     int res = 0;

//     while (che != NULL){
//             address_num[k] = che;
//             che = strtok(NULL,"/");
//             k++;
//             cnt++;
//         }
//     chdir("..");
    
//     // char s[10000];
//     // getcwd(s , sizeof(s));
//     // printf("%s\n" , s);

//      for(int ii = 0 ; ii<cnt-1 ; ii++){
//             res = chdir(address_num[ii]);
//             if(res==-1){
//                 printf("There is no folder named khhhhh %s\n" , address_num[ii]);
//                 break;
//             }
//         }

//     return res;
// }
  

int main(){

   // get_command();
   // int invalid = 0;

    while(1){

        char* command = (char*) calloc(2000 , sizeof(char));
        scanf("%[^\n]%*c" , command );

        char* command_backup = (char*) calloc(2000 , sizeof(char));
        char* command_backup2 = (char*) calloc(2000 , sizeof(char));
        strcpy(command_backup , command);
        strcpy(command_backup2 , command);
        char* chert = strtok(command, " ");
       // printf("%s" , command);
        
        if( !strcmp ( command , "createfile")){
            tedad=10;
            createfile(command_backup);
        }
        
        else if( !strcmp (command , "cat")){
            tedad=3;
            cat(command_backup);
        }

        else if( !strcmp (command , "insertstr")){
            tedad=9;
            insertstr(command_backup);
        }

        else if( !strcmp (command , "removestr")){
            tedad=9;
            removestr(command_backup);
        }

        else if( !strcmp (command , "copystr")){
            tedad=7;
            copystr(command_backup);
        }

        else if( !strcmp (command , "cutstr")){
            tedad=6;
            copystr(command_backup);
            if(naro!=1){
            removestr(command_backup2);
            }
        }

        else if( !strcmp (command , "pastestr")){
            tedad=8;
            pastestr(command_backup);
        }

        else{
            printf("Invalid command\n");
        }
    }
    return 0;
}

void with_space(char* command){

   char* sticked2 = (char*)calloc(100000 , sizeof(char));

    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , command);

    char* sticked = (char*) calloc(100000 , sizeof(char));
    
    if(command[tedad+8] == '\"'){
        char* slash_filename = strrchr( command , '/');
        char* filename=slash_filename+1;

        char* aha = strtok(command, "/");

        char* abc[10000];

        i = 0;

        while (aha != NULL)
        {
            abc[i] = aha;
            aha = strtok(NULL,"/");
            i++;
        }

        char* akhari = abc[i-1];
    
        int length_akhari=strlen(akhari);

        if(!strcmp(abc[0] , "insertstr --file \"")){
            char* str= "--str"; 
            char* ptr = strstr(akhari , str);
            int pos = ptr - akhari;
            for(int n=pos-1 ; n<length_akhari ; n++){
                akhari[n]='\0';
            }
        }

        akhari[strlen(akhari)-1]='\0';
        abc[i-1] = akhari;

        for(int k=1 ; k<i ; k++){
            sprintf(sticked , "/%s" , abc[k]);
            strcat(sticked2 , sticked);
        }

        space_seperate(&command_backup);
        
        strcpy(word_num[2] , sticked2);
        int injast = 0;
        if(!strcmp(abc[0] , "insertstr --file \"")){
            for(int l=3 ; l<i ; l++){
                if(!strcmp(word_num[l] , "--str")){
                    injast = l;
                    break;
                }
            }
            int jj = 3;
            for(int l=injast ; l<i ; l++){
                word_num[jj] = word_num[l];
                jj++;
            }
        }
    }

    else{
       space_seperate(&command_backup);
        return;
    }

 }


void space_seperate(char* command[]){

    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , *command);
    char* chert = strtok(*command, " ");
    
    i = 0;

    while (chert != NULL)
    {
        word_num[i] = chert;
        chert = strtok(NULL," ");
        i++;
    }
}

int go_to_folder(){
    int res=0;
    cnt=0;
 
    char* che = strtok(word_num[2] , "/");
    char* address_num[100];
  
    int k = 0;
    while (che != NULL){
            address_num[k] = che;
            che = strtok(NULL,"/");
            k++;
            cnt++;
        }

        for(int ii = 1 ; ii<cnt-1 ; ii++){
            res = chdir(address_num[ii]);
           // printf("vaa %d\n" , res);
            if(res == -1){
                printf("There is no folder named %s\n" , address_num[ii]);
                 return res;
                 break;
            }
        }
        return res;

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

void createfile(char* command){

    with_space(command);


    if(i<3){
        printf("Invalid command\n");
        return;
    }

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;


    char* che = strtok(word_num[2] , "/");
    char* address_num[100];
  
   
    int cnt = 0;
    int k = 0;
    while (che != NULL){
            address_num[k] = che;
            che = strtok(NULL,"/");
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
            printf("%s already exists\n" , filename);
        }
        else{
            FILE *fp;
            fp=fopen(filename, "w");
            fclose(fp);
            printf("%s successfully created!\n" , filename);
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
    
    with_space(command);

    if(i<3){
        printf("Invalid command\n");
        return;
    }
   
    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;
   
    int res=go_to_folder();
    if(res == -1){
        return;
    }
    FILE* ptr;
    char ch[1000]={};
    if(!strcmp(word_num[1] , "--file")){
        
        ptr = fopen(filename, "r");
 
            if (NULL != ptr) {
                while(fgets(ch , 1000 , ptr)){
                    printf("%s" , ch);
                }
                printf("\n");
            }

            else{
                printf("file can't be opened\n");
            }

        fclose(ptr);
        return_back();
    }
    else{
        printf("Invalid Command\n");
    }
    
}

void insertstr(char* command){
 
    with_space(command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    char* string_to_be_added = word_num[4];
    char string2[1000000];
    char* newline = "\\n";
    char* exist = strstr (string_to_be_added , newline);
    char* not_newline = "\\\n";
    int ah = 92;
    char not_newline2[1000];
    sprintf(not_newline2 , "%c%s" , ah , newline);
    char* exist2 = strstr (string_to_be_added , not_newline2);

    if(exist != NULL && exist2 == NULL){
        int pos = (exist - string_to_be_added);
        char* remaining = string_to_be_added+pos+2;
        for(int i=0 ; i<pos ; i++){
            string2[i]=string_to_be_added[i];
        }
        sprintf(string_to_be_added , "%s\n%s" , string2 , remaining);
    }
    if(exist2 != NULL ){
        char* not_newline3 = not_newline2 + 1;
       int pos = (exist2 - string_to_be_added);
        char* remaining = string_to_be_added+pos+3;
        for(int i=0 ; i<pos ; i++){
            string2[i]=string_to_be_added[i];
        }
        sprintf(string_to_be_added , "%s%s%s" , string2 , not_newline3 , remaining);
    }

    find_pos(word_num[6]);

    int res=go_to_folder();
    if(res == -1){
        return;
    }
    
    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "--str")) && (!strcmp(word_num[5] , "-pos"))){

        take_parts(filename , string_to_be_added);
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
        int ch = 0;
        int k=0;
        int cnt_line = 1;
        int cnt_c = 0;
        fptr = fopen(filename, "r");
        
        if(fptr == NULL){
            printf("file doesn't exist \n");
        }
            
        
            while(ch != EOF) {
                if(cnt_line == lineno){
                    while(ch != EOF ){
                        if(cnt_c == start_pos){
                            break;
                        }
                        ch = fgetc(fptr);
                        printf("%c " , ch);
                        p1[k]=ch;
                        cnt_c++;
                        k++;
                    }
                }
                else{
                    ch = fgetc(fptr);
                    p1[k]=ch;
                    if(ch == '\n'){
                        cnt_line++;
                    }
                k++;
                }
                if(cnt_c == start_pos && cnt_line == lineno){
                    break;
                }
            }

            int kk=0;
            while((ch = fgetc(fptr)) != EOF) {
                p2[kk]=ch;
                kk++;
            }
            fclose(fptr);

            char* p22;
            int index = 0;
            index = (k-size_removed);

            fopen(filename , "w");
            if((!strcmp(word_num[7], "-f"))){
                p22 = p2+size_removed;
                fprintf(fptr , "%s%s" , p1 , p22);
            }
            else if((!strcmp(word_num[7], "-b"))){

                fprintf(fptr , "%s" , p1);
                fseek(fptr , index , SEEK_SET);
                fprintf(fptr , "%s" , p2);
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

    int res=go_to_folder();
    if(res == -1){
        naro=1;
        return;
    }

        int cnt_line = 1;
        int cnt_c = 0;

    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos")) && (!strcmp(word_num[5] , "-size"))){
        go_to_folder();
        FILE* fptr;
        char ch;
        int k=0;
        fptr = fopen(filename, "r");
            
        if(fptr == NULL){
            printf("file doesn't exist \n");
            naro=1;
        }
                
        else{
        while(ch != EOF) {
            if(cnt_line == lineno){
                break;
            }
            ch = fgetc(fptr);
            p1[k]=ch;
            k++;
            if(ch == '\n'){
                cnt_line++;
            }
        }

        while(ch != EOF){
            if(cnt_c == start_pos){
                cnt_c = 0;
                break;
            }
            ch = fgetc(fptr);
            p1[k]=ch;
            cnt_c++;
            k++;
        }

        if(!strcmp(word_num[7] , "-f")){
            int counter = 0 , kk = 0;
            char tocopy[size_copied];
            while(counter != (size_copied-1)){
                ch=fgetc(fptr);
                tocopy[kk]=ch;
                kk++;
                counter++;
            }
            copytoclipboard(tocopy);
            strcpy(copied , tocopy);
        }

        if(!strcmp(word_num[7] , "-b")){
            int counter = 0 , kk = 0;
            char tocopy[size_copied];
            while(counter != size_copied){
                tocopy[kk]=p1[k-size_copied+1];
                counter++;
                k++;
                kk++;
            }
            copytoclipboard(tocopy);
            strcpy(copied , tocopy);
        }
        fclose(fptr);
        return_back();
        }
    }

    else{
        printf("Invalid Command\n");
    }

    }

void pastestr(char* command){

    space_seperate(&command);
    find_pos(word_num[4]);

    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos"))){
        char* cmd2 = (char*) calloc(2000 , sizeof(char));
        sprintf(cmd2 , "insertstr --file %s --str %s -pos %ld:%ld" , word_num[2] , copied , lineno , start_pos);
        insertstr(cmd2);
    }
    else{
        printf("Invalid Command\n");
    }

}

void take_parts(char* filename , char* string_to_be_added){


    char* content = (char*)malloc(10000 * sizeof(char));
    char* rest = (char*)malloc(10000 * sizeof(char));

    FILE* fptr;

        fptr = fopen(filename, "r");
        
        if(fptr == NULL){
            printf("file doesn't exist \n");
        }

        char ch;
        int k=0;
        int cnt_line = 1;
        int cnt_c = 0;

    while(ch != EOF) {
            if(cnt_line == lineno){
                break;
            }
            ch = fgetc(fptr);
            content[k]=ch;
            k++;
            if(ch == '\n'){
                cnt_line++;
            }
        }

        while(ch != EOF){
            if(cnt_c == start_pos){
                break;
            }
            ch = fgetc(fptr);
            content[k]=ch;
            cnt_c++;
            k++;
        }

   
        int kk = 0;
        
        while ((ch = fgetc(fptr)) != EOF)
        {
            rest[kk] = ch;
            kk++;
        }

        fclose(fptr);
        write_to_file(filename , content , string_to_be_added , rest);
  
        cnt_line = 0;
        ch = 0;

}

void write_to_file(char* filename ,char* content , char* string_to_be_added , char* rest){

    FILE* fptr;
    fptr = fopen(filename, "w");
    fprintf(fptr , "%s" , content);
    fseek(fptr , 0 , SEEK_CUR);
    fprintf(fptr , "%s" , string_to_be_added);
    fseek(fptr , 0 , SEEK_CUR);
    fprintf(fptr , "%s" , rest);
    fclose(fptr);

}

