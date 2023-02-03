#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LINES 10000
#define MAX_LEN 10000

char* word_num[1000];
char copied[1000];
int cnt = 0;
long int lineno;
long int start_pos;
int naro=0;
int i=0;
int tedad=0;
int are_for_paste=0;
int are_for_find=0;
char* filename_for_find;
char data[MAX_LINES][MAX_LEN]={};
int dont_replace=0;
char str_backup[1000000];
int kh=0;



void space_seperate(char**);
void with_space(char*);
int go_to_folder(char*);
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
void findstr(char*);
void str_with_space(char*);
void filename_with_space(char*);
void grep(char*);
void compare(char*);
void read_line_by_line(char*);
void auto_indent(char*);
void tree(char*);
void print_tree(const char* , const int , int , int);
void undo(char*);
void backup_hidden(char* , char*);
int countOccurrences(FILE* , const char*);
void nthOccurrences(FILE* , const char* , int);
void findstr_option(char* , FILE* , char*);
void replace(char*);
void findstr_option2(char* , FILE* , char*);
void findstr_option3(char* , FILE* , char*);

int main(){

    while(1){

        char* command = (char*) calloc(2000 , sizeof(char));
        scanf("%[^\n]%*c" , command );

        char* command_backup = (char*) calloc(2000 , sizeof(char));
        char* command_backup2 = (char*) calloc(2000 , sizeof(char));
        strcpy(command_backup , command);
        strcpy(command_backup2 , command);
        char* chert = strtok(command, " ");
        
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
                tedad=9;
                char ccc[1000000];
                command_backup2 = command_backup2 + 6;
                sprintf(ccc , "removestr%s" , command_backup2);
                removestr(ccc);
            }
        }

        else if( !strcmp (command , "pastestr")){
            tedad=8;
            pastestr(command_backup);
        }

        else if(!strcmp(command , "find")){
            tedad=4;
            findstr(command_backup);
        }

        else if(!strcmp(command , "replace")){
            tedad=7;
            replace(command_backup);
        }

        else if(!strcmp(command , "grep")){
            tedad=4;
            grep(command_backup);
        }

        else if(!strcmp(command , "compare")){
            tedad=7;
            compare(command_backup);
        }

        else if(!strcmp(command , "auto_indent")){
            tedad=11;
            auto_indent(command_backup);
        }

        else if(!strcmp(command , "tree")){
            tedad=4;
            tree(command_backup);
        }

        else if(!strcmp(command , "undo")){
            tedad=4;
            undo(command_backup);
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
        are_for_paste = 1;
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

        else if(!strcmp(abc[0] , "removestr --file \"") || !strcmp(abc[0] , "copystr --file \"") || !strcmp(abc[0] , "cutstr --file \"") || !strcmp(abc[0] , "pastestr --file \"")){
            char* str= "-pos"; 
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

        else if(!strcmp(abc[0] , "removestr --file \"") || !strcmp(abc[0] , "copystr --file \"") || !strcmp(abc[0] , "cutstr --file \"") || !strcmp(abc[0] , "pastestr --file \"")){
            for(int l=3 ; l<i ; l++){
                if(!strcmp(word_num[l] , "-pos")){
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

void str_with_space(char* command){

     char* sticked = (char*) calloc(100000 , sizeof(char));
     char* sticked2 = (char*)calloc(100000 , sizeof(char));

    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , command);
    char* command_backup2 = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup2 , command);

    int injast = 0;
    if(command[tedad+7] == '\"'){
        int pos = 0;
        char* str= "--file"; 
        char* ptr = strstr(command , str);
        pos = ptr - command;

        char* aha = strtok(command_backup, " ");
        char* abc[10000];

        i = 0;

        while (aha != NULL)
        {
            abc[i] = aha;
            aha = strtok(NULL," ");
            i++;
        }

        for(int k=0 ; k<i ; k++){
            if(!strcmp(abc[k] , "--file")){
                injast = k;
            }
        }
        char* string = (char*) calloc(2000 , sizeof(char));
        int o=0;
        for(int k=12 ; k<pos-2 ; k++){
            string[o]=command[k];
            o++;
        }

        space_seperate(&command_backup2);
        strcpy(word_num[2] , string);
        int oo = injast;
        for(int j=3 ; j<i ; j++){
            word_num[j]=word_num[injast];
            injast++;
        }
    }
    else{
        space_seperate(&command_backup2);
    }

}

void filename_with_space(char* command){
    int pos = 0;
    char* str= "--file"; 
    char* ptr = strstr(command , str);
    pos = ptr - command;
    if(command[pos+7]== '\"'){
    are_for_find=1;
    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , command);
    char* sticked = (char*) calloc(100000 , sizeof(char));
    char* sticked2 = (char*)calloc(100000 , sizeof(char));

    char* aha = strtok(command, "/");

    char* abc[10000];

    i = 0;

    while (aha != NULL)
    {
        abc[i] = aha;
        aha = strtok(NULL,"/");
        i++;
    }

    for(int k=1 ; k<i ; k++){
            sprintf(sticked , "/%s" , abc[k]);
            strcat(sticked2 , sticked);
        }
        sticked2[strlen(sticked2)-1]='\0';
        filename_for_find = sticked2;
    }
    else{
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

int go_to_folder(char* path){

    int res=0;
    cnt=0;
 
    char* che = strtok(path , "/");
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
            if(res == -1){
                printf("There is no folder named %s\n" , address_num[ii]);
                return_back();
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
   
    int res=go_to_folder(word_num[2]);
    if(res == -1){
        return;
    }
    FILE* ptr;
    char ch[100000]={};
    if(!strcmp(word_num[1] , "--file")){
        
        ptr = fopen(filename, "r");
 
            if (NULL != ptr) {
                while(fgets(ch , 100000 , ptr)){
                    printf("%s" , ch);
                    // if(!strcmp(word_num[3],"=D")){
                    //     sprintf(str_backup , "%s" , ch);
                    // }
                }
                printf("\n");
                // if(!strcmp(word_num[3],"=D")){
                //     sprintf(str_backup , "\n");
                // }
            }

            else{
                printf("file can't be opened\n");
            }
            // if(!strcmp(word_num[3],"=D")){
            // printf("%s\n" , str_backup);
            // }

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
    if(!dont_replace){
        int res=go_to_folder(word_num[2]);
        if(res == -1){
            return;
        }
    read_line_by_line(filename);
    if(kh){
        return;
    }
    if(!strcmp(data[lineno],"\0")){
        printf("line %ld doesn't exist in %s.\n" , lineno , filename);
        return_back();
        return;
    }
    else if(data[lineno][start_pos]=='\0'){
        printf("Not enough characters in the %ldth line.\n" , lineno);
        return_back();
        return;
    }
    backup_hidden(filename , word_num[2]);
    }
    
    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "--str")) && (!strcmp(word_num[5] , "-pos"))){

        take_parts(filename , string_to_be_added);
         if(!dont_replace){
        return_back();
         }

    }

     else{
         printf("Invalid Command\n");
     }

}

void removestr(char* command){

    with_space(command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;


    find_pos(word_num[4]);

    long int size_removed = strtol(word_num[6] , &word_num[6] , 10 );

    char p1[1000000]={};
    char to_be_deleted[100]={};
    char p2[1000000]={};

     if(!dont_replace){
    int res=go_to_folder(word_num[2]);
    if(res == -1){
        return;
    }

    read_line_by_line(filename);
    if(kh){
        return;
    }
    if(!strcmp(data[lineno],"\0")){
        printf("line %ld doesn't exist in %s.\n" , lineno , filename);
        return_back();
        return;
    }
    else if(data[lineno][start_pos]=='\0'){
        printf("Not enough characters in the %ldth line.\n" , lineno);
        return_back();
        return;
    }

    backup_hidden(filename , word_num[2]);
     }
    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos")) && (!strcmp(word_num[5] , "-size"))){
            FILE* fptr;
            fptr = fopen(filename, "r");
        int ch = 0;
        int k=0;
        int cnt_line = 1;
        int cnt_c = 0;
        
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
             if(!dont_replace){
            return_back();
             }
    }

    else{
    printf("Invalid Command");
    }
}

void copystr(char* command){

    with_space(command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    find_pos(word_num[4]);

    long int size_copied = strtol(word_num[6] , &word_num[6] , 10 ) + 1;

    char p1[1000];

    int res=go_to_folder(word_num[2]);
    if(res == -1){
        // char s[1000];
        // getcwd(s , sizeof(s));
        // printf("%s\n" , s);
        naro=1;
        return_back();
        return;
    }

    read_line_by_line(filename);
    if(kh){
        return;
    }

    if(!strcmp(data[lineno],"\0")){
        printf("line %ld doesn't exist in %s.\n" , lineno , filename);
        naro=1;
        return_back();
        return;
    }
    else if(data[lineno][start_pos]=='\0'){
        printf("Not enough characters in the %ldth line.\n" , lineno);
        naro=1;
        return_back();
        return;
    }

        FILE* fptr;
        char ch;
        int cnt_line = 1;
        int cnt_c = 0;

    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos")) && (!strcmp(word_num[5] , "-size"))){

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

    with_space(command);

    find_pos(word_num[4]);

    if((!strcmp(word_num[1] , "--file")) && (!strcmp(word_num[3] , "-pos"))){
        char* cmd2 = (char*) calloc(2000 , sizeof(char));
        if(are_for_paste == 1){
             sprintf(cmd2 , "insertstr --file \"%s\" --str %s -pos %ld:%ld" , word_num[2] , copied , lineno , start_pos);
        }
        else{
            sprintf(cmd2 , "insertstr --file %s --str %s -pos %ld:%ld" , word_num[2] , copied , lineno , start_pos);
        }
        tedad=9;
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

void findstr(char* command){

    char* command_backup = (char*) calloc(2000 , sizeof(char));
    strcpy(command_backup , command);

    str_with_space(command);
    filename_with_space(command);

    char* slash_filename = strrchr(word_num[4] , '/');
    char* filename=slash_filename+1;

    char* string_to_be_searched = word_num[2];

    int res=go_to_folder(word_num[4]);
    if(res == -1){
        return;
    }

    FILE* fptr;
    fptr = fopen(filename , "r");

    if(i==6){
        findstr_option(command_backup , fptr , filename);
    }

    else if(i==7){
        findstr_option2(command_backup , fptr , filename);
    }

    else if(i==8){
        findstr_option3(command_backup , fptr , filename);
    }

    // else if(i==7){
            
    // }

    else{
        if(are_for_find){
            word_num[4]=filename_for_find;
        }


    // char* str_backup;
    // str_backup = word_num[2];

    // printf("%c\n" , str_backup[9]);

    // for(int k=0 ; k<strlen(word_num[2]) ; k++){
    //     if(str_backup[k] == '*'){
    //         printf("Hi");
    //     }
    //     printf("%c " , str_backup[k]);
    // }
//     //strcpy(str_backup , word_num[3]);
//    // printf("%s\n" , str_backup);
//     char* str_num[100000];
//     char* chert = strtok(str_backup, " ");
    
//     int str_count = 0;

//     while (chert != NULL){
//         str_num[str_count] = chert;
//         chert = strtok(NULL," ");
//         str_count++;
//     }

    // printf("strs: %s\n", str_num[0]);

    // char*wordd = strchr (word_num[3] , '*');
    // printf("%s\n" , wordd);

    if((!strcmp(word_num[1] , "--str")) && (!strcmp(word_num[3] , "--file"))){
      
        char* whole;
        int ch = 0;
        int k=0;
 
        if (fptr != NULL) {
            ch = fgetc(fptr);
            while(ch != EOF){
                whole[k]=ch;
                ch = fgetc(fptr);
                k++;
            }
        }
       
        else{
            printf("file can't be opened\n");
        }
        char* ptr = strstr(whole , string_to_be_searched);
        int first_pos = ptr - whole;
        if(first_pos < 0){
            printf("-1");
            return;
        }
        printf("%d\n" , first_pos);
        
    }
    else{
        printf("Invalid command");
    }
    }
    fclose(fptr);
    return_back();
}

void grep(char* command){

    space_seperate(&command);

    char* word_backup;
    if(!strcmp(word_num[1] , "--str")){
        word_backup = word_num[2];
        word_backup[strlen(word_backup)-1]='\0';
        word_backup=word_backup+1;
    }
    else{
        word_backup = word_num[3];
        word_backup[strlen(word_backup)-1]='\0';
        word_backup=word_backup+1;
    }
    char pattern[100000]={};

    char* file_path[10000];
    char* filename[10000];

    int n = 0;
    int cnt_line = 0;

    if(!strcmp(word_num[1] , "--str")){
        for(int k=4 ; k<i ; k++){
            
            file_path[n]=word_num[k];
            char* slash_filename = strrchr(file_path[n] , '/');
            filename[n]=slash_filename+1;
            strcpy(pattern , word_backup);

            int res=go_to_folder(file_path[n]);
            if(res == -1){
                return;
            }

            read_line_by_line(filename[n]);
            if(kh){
                return;
            }
            int ccnntt=0;
            for(int j=1 ; j<MAX_LINES ; j++){
            if(!strcmp(data[j],"\0")){
                break;
            }
            ccnntt++;
            }
            size_t len = strlen(data[ccnntt]);
            char *str2 = malloc(len + 1 + 1);
            strcpy(str2, data[ccnntt]);
            str2[len] = '\n';
            str2[len + 1] = '\0';
            strcpy(data[ccnntt] , str2);
            free(str2);
           
            for(int l=0 ; l<MAX_LINES ; l++){
                char* ptr = strstr(data[l] , pattern);
                int pos = ptr - data[l];
                if(pos >= 0){
                    printf("%s:%s" , filename[n] , data[l]);
                    break;
                }
            }
        
            n++;
            return_back();
        }
    }

    else if(!strcmp(word_num[1] , "-c")){

        for(int k=5 ; k<i ; k++){
            file_path[n]=word_num[k];

            char* slash_filename = strrchr(file_path[n] , '/');
            filename[n]=slash_filename+1;

            strcpy(pattern , word_backup);

            int res=go_to_folder(file_path[n]);
            if(res == -1){
                return;
            }

            read_line_by_line(filename[n]);
            if(kh){
                return;
            }
            for(int l=0 ; l<MAX_LINES ; l++){
                char* ptr = strstr(data[l] , pattern);
                int pos = ptr - data[l];
                if(pos >= 0){
                    cnt_line++;
                    break;
                }
            }
            
            n++;
            return_back();
        }
        printf("%d\n" , cnt_line);
    }
    
    

    else if(!strcmp(word_num[1] , "-l")){
        for(int k=5 ; k<i ; k++){
            file_path[n]=word_num[k];

            char* slash_filename = strrchr(file_path[n] , '/');
            filename[n]=slash_filename+1;

            strcpy(pattern , word_backup);

            int res=go_to_folder(file_path[n]);
            if(res == -1){
                return;
            }

            read_line_by_line(filename[n]);
            if(kh){
                return;
            }
            
            for(int l=0 ; l<MAX_LINES ; l++){
                char* ptr = strstr(data[l] , pattern);
                int pos = ptr - data[l];
                if(pos >= 0){
                    printf("%s\n" , filename[n]);
                    break;
                }
            }
        
            n++;
            return_back();
        }
    }
}

void compare(char* command){

    char data1[MAX_LINES][MAX_LEN]={};
    char data2[MAX_LINES][MAX_LEN]={};

    space_seperate(&command);

    char* slash_filename1 = strrchr(word_num[1] , '/');
    char* filename1=slash_filename1+1;

    char* slash_filename2 = strrchr(word_num[2] , '/');
    char* filename2=slash_filename2+1;

    int one=0 , two=1 , min=0 , max=0;
        
    int res=go_to_folder(word_num[1]);
    if(res == -1){
        return;
    }

    read_line_by_line(filename1);
    if(kh){
        return;
    }

    for(int j=1 ; j<MAX_LINES ; j++){
        strcpy(data1[j] , data[j]);
        if(!strcmp(data[j],"\0")){
            break;
        }
        one++;
    }

    size_t len = 0;
    len = strlen(data1[one]);
    char *str2 = malloc(len + 1 + 1);
    strcpy(str2, data1[one]);
    str2[len] = '\n';
    str2[len + 1] = '\0';
    strcpy(data1[one] , str2);
    free(str2);

    return_back();

    int res2=go_to_folder(word_num[2]);
    if(res2 == -1){
        return;
    }

    FILE* fptr2;
    fptr2 = fopen(filename2 , "r");

    if(fptr2 == NULL){
        printf("file doesn't exist \n");
    }
    else{
        while (!feof(fptr2) && !ferror(fptr2)){
            while (fgets(data2[two], 10000 , fptr2)){
                two++;
            }
        }
        
        fclose(fptr2);
    }
    two=two-1;
    len = strlen(data2[two]);
    char *str3 = malloc(len + 1 + 1);
    strcpy(str3 , data2[two]);
    str3[len] = '\n';
    str3[len + 1] = '\0';
    strcpy(data2[two] , str3);
    free(str3);

    return_back();

    if(one<two){
        min=one;
    }
    else{
        min=two;
    }

    for(int j=0 ; j<=min ; j++){
        if(strcmp(data1[j] , data2[j])){
            printf("============ #%d ============\n%s%s" , j , data1[j] , data2[j]);
        }
    }

    if(two>one){
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , min+1 , two);
        for(int j=min+1 ; j<=two ; j++){
            printf("%s" , data2[j]);
        }
    }
    else if(one>two){
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , min+1 , one);
        for(int j=min+1 ; j<=one ; j++){
            printf("%s" , data1[j]);
        }
    }

}

void read_line_by_line(char* filename){

    for(int l=1 ; l<MAX_LINES ; l++){
        for(int j=0 ; j<MAX_LEN ; j++){
            data[l][j]='\0';
        }
    }    

    FILE* fptr;
    int line = 1;
    fptr = fopen(filename , "r");

    if(fptr == NULL){
       // return;
        kh=1;
        printf("file doesn't exist \n");
    }
    else{
        while (!feof(fptr) && !ferror(fptr)){
            while (fgets(data[line], MAX_LEN , fptr)){
                line++;
            }
        }
        
        fclose(fptr);
    }

}

void auto_indent(char* command){

    // space_seperate(&command);
    with_space(command);


    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;


    char p1[1000][1000];
    char p2[1000][1000];

    int res = go_to_folder(word_num[2]);
    if(res == -1){
        return;
    }
    backup_hidden(filename , word_num[2]);

    char rest[10000];
    char rest_backup[10000];
    char rest_backup2[10000];
    int cnt_open=0 , cnt_close=0;

    read_line_by_line(filename);
    if(kh){
        return;
    }

    for(int l=1 ; l<MAX_LINES ; l++){
        for(int j=0 ; j<MAX_LEN ; j++){
            if(data[l][j]=='{'){
                cnt_open++;
            }
        }
    }

    for(int l=1 ; l<MAX_LINES ; l++){
        for(int j=0 ; j<MAX_LEN ; j++){
            if(data[l][j]=='}'){
                cnt_close++;
            }
        }
    }

    FILE* fptrr;
    fptrr = fopen(filename , "w");
    fprintf(fptrr , "%s" , rest_backup2);
    fclose(fptrr);

    for(int y=0 ; y<cnt_open ; y++){
        int saved_line = 0;
        int saved_ch=0;
        int naro=0;
        for(int l=1 ; l<MAX_LINES ; l++){
            for(int j=0 ; j<MAX_LEN ; j++){
                if(data[l][j]=='{'){
                    data[l][j]='\0';
                    saved_line = l;
                    saved_ch = j;
                    for(int ll=1 ; ll<l ; ll++){
                        for(int jj=0 ; jj<MAX_LEN ; jj++){
                        p1[ll][jj]=data[ll][jj];
                        data[ll][jj]='\0';
                        }
                    }
                    for(int jj=0 ; jj<j ; jj++){
                    p1[l][jj]=data[l][jj];
                    data[l][jj]='\0';
                    }
                    naro=1;
                }
                if(naro==1){
                    break;
                }
            }
            if(naro==1){
                break;
            }
        }  
        int saved_line2=saved_line;
        int naroo=0;
        int ll=0 , jj=0;
            for(ll=saved_line ; ll>=1 ; ll--){
                for(jj=MAX_LEN ; jj>=0 ; jj--){
                    if(p1[ll][jj]==0){
                    }
                    else if(p1[ll][jj]==' '){
                        p1[ll][jj]='\0';
                    }
                    else if(p1[ll][jj]== '\n'){
                        p1[ll][jj]='\0';
                        saved_line2--;
                    }
                    else{
                        naroo=1;
                        break;
                    }
                }
                if(naroo==1){
                    break;
                }

            }

        int len = 0;

        char str2[100000];
        for(int k=0 ; k<1000 ; k++){
            str2[k]=0;
        }

        for(int k=0 ; k<MAX_LEN ; k++){
            if(p1[saved_line2][k]!=0){
            str2[k] = p1[saved_line2][k];
            len++;
            }
        }

        int n=0;
        for(int ll=1 ; ll<=saved_line ; ll++){
            for(int jj=0 ; jj<MAX_LEN ; jj++){
            rest[n]=p1[ll][jj];
            n++;
            }
        }
        
        for(int j=0 ; j<saved_line*MAX_LEN ; j++){
            rest_backup[j]=rest[j];
        }

    
        fptrr = fopen(filename , "a");

        for(int j=0 ; j<saved_line*MAX_LEN ; j++){
            if(rest_backup[j] != '\0'){
                fprintf(fptrr , "%c" , rest_backup[j] );
            }
        }

        fprintf(fptrr , " {\n");

        if(y==cnt_open-1){
            for(int o=-1 ; o<y-1 ; o++){
            fprintf(fptrr , "\t");
        }
        }
        else{
        for(int o=-1 ; o<y ; o++){
            fprintf(fptrr , "\t");
        }
        }

        for(int ll=0 ; ll<=saved_line ; ll++){
            for(int jj=0 ; jj<MAX_LEN ; jj++){
                p1[ll][jj]='\0';
            }
        }
        
        fclose(fptrr);
    }

//close

    for(int y=cnt_close-1 ; y>=0 ; y--){
        int saved_line = 0;
        int saved_ch=0;
        int naro=0;

        for(int l=1 ; l<MAX_LINES ; l++){
            for(int j=0 ; j<MAX_LEN ; j++){
                if(data[l][j]=='}'){
                    data[l][j]='\0';
                    saved_line = l;
                    saved_ch = j;
                    for(int ll=1 ; ll<l ; ll++){
                        for(int jj=0 ; jj<MAX_LEN ; jj++){
                        p1[ll][jj]=data[ll][jj];
                        data[ll][jj]='\0';
                        }
                    }
                    for(int jj=0 ; jj<j ; jj++){
                    p1[l][jj]=data[l][jj];
                    data[l][jj]='\0';
                    }
                    naro=1;
                }
                if(naro==1){
                    break;
                }
            }
            if(naro==1){
                break;
            }
        }  
        int saved_line2=saved_line;
        int naroo=0;
        int ll=0 , jj=0;
            for(ll=saved_line ; ll>=1 ; ll--){
                for(jj=MAX_LEN ; jj>=0 ; jj--){
                    if(p1[ll][jj]==0){
                    }
                    else if(p1[ll][jj]==' '){
                        p1[ll][jj]='\0';
                    }
                    else if(p1[ll][jj]== '\n'){
                        p1[ll][jj]='\0';
                        saved_line2--;
                    }
                    else{
                        naroo=1;
                        break;
                    }
                }
                if(naroo==1){
                    break;
                }

            }

        int len = 0;

        char str2[100000];
        for(int k=0 ; k<1000 ; k++){
            str2[k]=0;
        }

        for(int k=0 ; k<MAX_LEN ; k++){
            if(p1[saved_line2][k]!=0){
            str2[k] = p1[saved_line2][k];
            len++;
            }
        }

        int n=0;
        for(int ll=1 ; ll<=saved_line ; ll++){
            for(int jj=0 ; jj<MAX_LEN ; jj++){
            rest[n]=p1[ll][jj];
            n++;
            }
        }
        
        for(int j=0 ; j<saved_line*MAX_LEN ; j++){
            rest_backup[j]=rest[j];
        }

       
        fptrr = fopen(filename , "a");

        for(int j=0 ; j<saved_line*MAX_LEN ; j++){
            if(rest_backup[j] != '\0'){
                fprintf(fptrr , "%c" , rest_backup[j] );
            }
        }

        fprintf(fptrr , "\n");
        
        for(int o=y-1 ; o>=0 ; o--){
            fprintf(fptrr , "\t");
        }
        fprintf(fptrr , " }");
        

        for(int ll=0 ; ll<=saved_line ; ll++){
            for(int jj=0 ; jj<MAX_LEN ; jj++){
                p1[ll][jj]='\0';
            }
        }
        
        fclose(fptrr);
    }

    return_back();
}

void tree(char* command){

    space_seperate(&command);
    int depth=0;
    depth = strtol(word_num[1] , &word_num[1] , 10);
    if(depth<-1){
        printf("Invalid depth.\n");
        return;
    }
    int depth_cnt = -1;
    char s[1000];
    getcwd(s,sizeof(s));
    char* curdir = strrchr(s , '/');
    printf("%s\n" , curdir+1);
    print_tree("." , 0 , depth , depth_cnt);
}

void print_tree(const char* dirname ,const int root , int depth , int depth_cnt){
    
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(dirname);
    depth_cnt++;

    if(depth_cnt == depth){
        return;
    }

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL){
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            if( dp->d_name[0]!= '.'){
            for (i=0; i<root ; i++) {
                printf("|  ");
            }
            }
            if( dp->d_name[0]!= '.'){
                printf("├──%s\n", dp->d_name);
            }
           
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, dp->d_name);
            print_tree(path, root + 1 , depth , depth_cnt);
        }
    }

    closedir(dir);
}

void undo(char* command){

    space_seperate(&command);

    char* slash_filename = strrchr(word_num[2] , '/');
    char* filename=slash_filename+1;

    
    char filename2[1000000] = ".";
    strcat(filename2 , filename);

    int res=go_to_folder(word_num[2]);

    if(res == -1){
        return;
    }   

    FILE* ptr;
    FILE* ptr2;
    char ch[100000]={};

    ptr = fopen(filename, "w");
    ptr2 = fopen(filename2 , "r");

     if (NULL != ptr) {
        while(fgets(ch , 100000 , ptr2)){
            fprintf( ptr , "%s" , ch);
                }
               // fprintf(ptr , "\n");
            }

            else{
                printf("file can't be opened\n");
            }

        fclose(ptr);
        fclose(ptr2);

        return_back();
}

void backup_hidden(char* filename , char* path){

    char filename2[1000000] = ".";
    strcat(filename2 , filename);

    FILE* ptr;
    FILE* ptr2;
    char ch[100000]={};

    ptr = fopen(filename, "r");
    ptr2 = fopen(filename2 , "w");
 
    if (NULL != ptr) {
        while(fgets(ch , 100000 , ptr)){
            fprintf( ptr2 , "%s" , ch);
                }
            }

            else{
                printf("file can't be opened\n");
            }

        fclose(ptr);
        fclose(ptr2);

}

int countOccurrences(FILE *fptr, const char *word)
{
    char str[10000];
    char *pos;

    int index, count;
    
    count = 0;

    while ((fgets(str, 10000 , fptr)) != NULL)
    {
        index = 0;

        while ((pos = strstr(str + index, word)) != NULL)
        {
            index = (pos - str) + 1;
            count++;
        }
    }

    return count;
}

void nthOccurrences(FILE *fptr, const char *word , int nth)
{
    char str[10000];
     char *pos;

     int index, count;

     count = 0;

     while ((fgets(str, 10000 , fptr)) != NULL)
     {
         index = 0;

         while ((pos = strstr(str + index, word)) != NULL)
         {

             index = (pos - str) + 1;
             if(count+1 == nth){
                printf("%d\n" , index-1);
             }
             count++;
         }
        if(count==0){
            printf("-1\n");
        }
        else if(nth>count && count!=0){
            printf("Only %d -%s- exists in the file.\n" , count , word);
        }
     }
 }


void findstr_option(char* command , FILE* fptr , char* filename){

    space_seperate(&command);

    char* string_to_be_searched = word_num[2];

    if((!strcmp(word_num[1] , "--str")) && (!strcmp(word_num[3] , "--file"))){
    
        if(!strcmp(word_num[5] , "-count")){
            if(fptr == NULL){
                printf("file can't be opened\n");
            }
            else{
                int counter = countOccurrences(fptr , string_to_be_searched);
                    printf("%d\n" , counter);
            }
        }

        else if(!strcmp(word_num[5] , "-byword")){
            read_line_by_line(filename);
            if(kh){
                return;
            }
            //printf("%s" , data[1]);
            char* fword[10000];
            char* chert = strtok(data[1], " ");
    
            int j = 0;

            while (chert != NULL){
                fword[j] = chert;
                chert = strtok(NULL," ");
                j++;
            }

            for(int k=0 ; k<j ; k++){
              //  printf("%s\n" , fword[k]);
                if(!strcmp(fword[k] , string_to_be_searched)){
                    printf("%d\n" , k+1);
                    break;
                }
            }
        }

        else if(!strcmp(word_num[5] , "-all")){
            char str[10000];
            char *pos;

            int index , flag=0;

            while ((fgets(str, 10000 , fptr)) != NULL){
                index = 0;

                while ((pos = strstr(str + index, string_to_be_searched)) != NULL){
                    index = (pos - str) + 1;
                    printf("%d," , index-1);
                }
                if(index==0){
                    flag=1;
                }
            }

            if(flag==1){
                printf("%s not found\n" , string_to_be_searched);
            }
        }
        else{
        printf("Invalid command\n");
      }

        // else if((!strcmp(word_num[5] , "-at") && !strcmp(word_num[7] , "-byword")) || (!strcmp(word_num[6] , "-at") && !strcmp(word_num[5] , "-all"))){
           
        // }
    }
    else{
        printf("Invalid command\n");
      }
}

void findstr_option2(char* command , FILE* fptr , char* filename){

    space_seperate(&command);

    char* string_to_be_searched = word_num[2];

    if((!strcmp(word_num[1] , "--str")) && (!strcmp(word_num[3] , "--file"))){

      if(!strcmp(word_num[5] , "-at")){
            int nth = strtol(word_num[6] , &word_num[6] , 10 );
            if(fptr == NULL){
                printf("file can't be opened\n");
            }
            else{
                nthOccurrences(fptr , string_to_be_searched , nth);
            }
        }
        else if((!strcmp(word_num[5] , "-all") && !strcmp(word_num[6] , "-byword")) || (!strcmp(word_num[6] , "-all") && !strcmp(word_num[5] , "-byword"))){
            read_line_by_line(filename);
            //int count_words=0;
            if(kh){
                return;
            }
            //printf("%s" , data[1]);
            char* fword[10000];
            char* chert = strtok(data[1], " ");
    
            int j = 0;

            while (chert != NULL){
                fword[j] = chert;
                chert = strtok(NULL," ");
                j++;
            }

            for(int k=0 ; k<j ; k++){
                if(!strcmp(fword[k] , string_to_be_searched)){
                    printf("%d\n" , k+1);
                }
            }
        }
        else{
        printf("Invalid command\n");
      }
    }
    else{
        printf("Invalid command\n");
      }
}

void findstr_option3(char* command , FILE* fptr , char* filename){

    space_seperate(&command);

    char* string_to_be_searched = word_num[2];

    if((!strcmp(word_num[1] , "--str")) && (!strcmp(word_num[3] , "--file"))){

      if((!strcmp(word_num[5] , "-at") && !strcmp(word_num[7] , "-byword"))){
        read_line_by_line(filename);
            int count_words=0;
            int nth = strtol(word_num[6] , &word_num[6] , 10 );
            if(kh){
                return;
            }
            //printf("%s" , data[1]);
            char* fword[10000];
            char* chert = strtok(data[1], " ");
    
            int j = 0;

            while (chert != NULL){
                fword[j] = chert;
                chert = strtok(NULL," ");
                j++;
            }

            for(int k=0 ; k<j ; k++){
                if(!strcmp(fword[k] , string_to_be_searched)){
                    count_words++;
                    if(count_words==nth){
                        printf("%d\n" , k+1);
                    }
                }
            }
      }

      else if((!strcmp(word_num[5] , "-byword") && !strcmp(word_num[6] , "-at"))){
          read_line_by_line(filename);
            int count_words=0;
            int nth = strtol(word_num[7] , &word_num[7] , 10 );
            if(kh){
                return;
            }
            //printf("%s" , data[1]);
            char* fword[10000];
            char* chert = strtok(data[1], " ");
    
            int j = 0;

            while (chert != NULL){
                fword[j] = chert;
                chert = strtok(NULL," ");
                j++;
            }

            for(int k=0 ; k<j ; k++){
                if(!strcmp(fword[k] , string_to_be_searched)){
                    count_words++;
                    if(count_words==nth){
                        printf("%d\n" , k+1);
                    }
                }
            }

      }
      else{
        printf("Invalid command\n");
      }

    }

    else{
        printf("Invalid command\n");
      }

}

void replace(char* command){

    space_seperate(&command);

//      printf("%s\n" , path);

    // // char* path = (char*) calloc(200000 , sizeof(char));
    // // path = word_num[6];
    // path = word_num[6];
    char* slash_filename = strrchr(word_num[6] , '/');
    char* filename=slash_filename+1;

    char path[1000];
    strcpy(path , word_num[6]);

    int res=go_to_folder(word_num[6]);
    if(res == -1){
        return;
    }
    backup_hidden(filename , word_num[6]);

    char* string_to_be_searched = word_num[2];
    char* string_to_be_replace = word_num[4];


    if(i==7){
        FILE* fptr;
        fptr = fopen(filename , "r");

        read_line_by_line(filename);
        if(kh){
            return;
        }

        char* ptr = strstr(data[1] , string_to_be_searched);
        int first_pos = ptr - data[1];
        if(first_pos < 0){
            printf("-1\n");
            return;
        }
        char* cmd2 = (char*) calloc(2000 , sizeof(char));
        char* cmd3 = (char*) calloc(2000 , sizeof(char));
        dont_replace=1;
        int size = strlen(string_to_be_searched);
        sprintf(cmd2 , "removestr --file %s -pos 1:%d -size %d -f" , path , first_pos , size);
        removestr(cmd2);
        sprintf(cmd3 , "insertstr --file %s --str %s -pos 1:%d" , path , string_to_be_replace , first_pos);
        insertstr(cmd3);
    }

    else if(i==9 && !strcmp(word_num[7] , "-at")){
        FILE* fptr;
        fptr = fopen(filename , "r");
        
        int nth = strtol(word_num[8] , &word_num[8] , 10 );

        char str[10000];
        char *pos;

        int index, count;
        
        count = 0;

        while ((fgets(str, 10000 , fptr)) != NULL){
            while ((pos = strstr(str + index, string_to_be_searched)) != NULL){
                index = (pos - str) + 1;
                if(index < 0){
                    printf("-1\n");
                    return;
                }
                if(count+1 == nth){
                    char* cmd2 = (char*) calloc(2000 , sizeof(char));
                    char* cmd3 = (char*) calloc(2000 , sizeof(char));
                    int size = strlen(string_to_be_searched);
                    dont_replace=1;
                    fclose(fptr);
                    sprintf(cmd2 , "removestr --file %s -pos 1:%d -size %d -f" , path , index-1 , size);
                    removestr(cmd2);
                    sprintf(cmd3 , "insertstr --file %s --str %s -pos 1:%d" , path , string_to_be_replace , index-1);
                    insertstr(cmd3);
                }
                count++;
            }
            if(count==0){
                printf("-1\n");
            }
            else if(nth>count && count!=0){
                printf("Only %d -%s- exists in %s.\n" , count , string_to_be_searched , filename);
            }
            index = 0;
        }
    }

    else if(i==8 && !strcmp(word_num[7] , "-all")){
        FILE* fptr;
        fptr = fopen(filename , "r");

        char str[10000];
        char *pos;

        int index;
        int p=0,flag=0;
        int difference;

        while ((fgets(str, 10000 , fptr)) != NULL){
            index = 0;
            while ((pos = strstr(str + index, string_to_be_searched)) != NULL){
                index = (pos - str) + 1;
                char* cmd2 = (char*) calloc(2000 , sizeof(char));
                char* cmd3 = (char*) calloc(2000 , sizeof(char));
                int size = strlen(string_to_be_searched);
                difference = (size - strlen(string_to_be_replace))*p;
                fclose(fptr);
                dont_replace=1;
                sprintf(cmd2 , "removestr --file %s -pos 1:%d -size %d -f" , path , index-1-difference , size);
                removestr(cmd2);
                sprintf(cmd3 , "insertstr --file %s --str %s -pos 1:%d" , path , string_to_be_replace , index-1-difference);
                insertstr(cmd3);
                p++;
            }
            if(index==0){
                flag=1;
            }
        }

        if(flag==1){
            printf("%s not found\n" , string_to_be_searched);
        }
    }

    return_back();
}
