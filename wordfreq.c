
//Implement a program to count the frequency of words in a text file. The text file is partitioned into N segments. Each segment is processed by a separate thread that out- puts the intermediate frequency count for its segment. The main process waits until all the threads complete; then it computes the consolidated wordfrequency data based on the individual threads’ output.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int a=0;
int *N=&a;
char file[500];        

void *myfunc ();

int main(void){
    FILE *pFile;
        
        pFile = fopen("prog2.txt","r");
        while (fgets(file,500,pFile)) {
                *N=*N+1;        
        pthread_t line;
        pthread_create(&line, NULL, myfunc, NULL);        
                pthread_join(line, NULL);    
        }
        fclose(pFile);  
        return 0;
}

void *myfunc (){
    size_t length=strlen(file);    
    
    //Counts number of spaces in line
    int k;
    int spaces=0;
    for (k=0; k<length;k++){
        if (file[k]==' '){
            spaces=spaces+1;
        }
    }
    
    char words[spaces+1][15];        //Assuming no word is more than 15 letters
    //Tried to convert char array into a string array. For example, {'h','e','l','l','o',' ','t','h''e','r','e'} would get converted to {"hello","there"}
    //BUG ISSUE. When file[i]=='', I wanted this piece of code to break out of the inner-for-loop, increment outer-for-loop by 1 and continue
    int i;
    int j;
    int a=0;
    for(j=0;j<=spaces;j++){
        for (i=a; i<length;i++){    
            if(file[i]==' '){
                a=i+1;            
                break;
            }
            else{
            words[j][i]=file[i];
            }
        }
    }

    //Create an int array with size (spaces+1)
    int frequency[spaces+1];
    int l;
    for(l=0;l<=spaces;l++){
        frequency[l]=0;
    }

    //Calculating word-frequency
    //BUG ISSUE. When the code below was compiled from a separate file -->Segmentation fault (Core dumped)
    int m;
    int q;
    for (m=spaces;m>=0;m--){
        for(q=m;q>=0;q--){
            int similarity=strcmp(words[m],words[q]);
            if(similarity==0){
                frequency[m]=frequency[m]-1;
                frequency[q]=frequency[q]+1;
            }
        }
    }
    
    
    int o;
    int p;
    for(o=0;o<spaces;o++){
        if (frequency[o]==0){
            p=o;
        }
    }
    
    printf("LINE NUMBER %d\n", *N);
    int b;
    for(b=0;b<p;b++){
        printf("%s %d", words[b], frequency[b]);
        printf("\n");
    }


}
