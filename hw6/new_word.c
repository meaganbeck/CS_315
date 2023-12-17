#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define NUM_WORDS 58114
			
#define n 200

int dict(char** diction, char* w){ 
	for (int i = 0; i < NUM_WORDS; i++){
		if (strcmp(diction[i], w) == 0)
			return 1;
	}
	return 0;
}

char* substring(char* w, int i, int j){
    int len = j - i;
    char * substr = malloc(sizeof(char) * len *2);
    int l = 0;
	for (int k = i; k < j; k++){
 	    substr[l] = w[k];
	    l++;
	}
	substr[l] = '\0';
       return substr;	
}

int split(char** diction, char* w){
    int len = strlen(w);
    int val = 0;
    int dict_val;
    int split_val;
    int valid_word[strlen(w) + 1];

    //all subs invalid
    for (int j = 0; j < strlen(w) +1; j++){
	valid_word[j] = 0;
    }

    if (len == 0) //empty string
	    return 0;

    for (int i = 1; i <= len; i++){
	    char* substr1 = substring(w, 0, i);
	    if (valid_word[i] == 0 && dict(diction, substr1))
		    valid_word[i] = 1;
	    
	    if (valid_word[i] == 1){
		if (i == len)
			return 1;
		for (int k = i+1; k <= len; k++)
		{
	    	    char* substr2 = substring(w, i, k);
		    if (valid_word[k] == 0 && dict(diction,substr2)){
			valid_word[k] = 1;
		    }

		    if( k == len && valid_word[k] == 1)
		    	    return 1;
		}
	    
	    }
	}
	return 0;
}

int getwords(char** diction, char* w, int len, char* result, char* str, int ret){
    int size = strlen(str);
    for (int i = 1; i <= len; i++){	
	char* substr = substring(w, 0, i);
	if (dict(diction, substr)){
	    if (i == len){ //this is the result 
		
 		strcat(result, substr);
    		printf("%s\n\n", result);
		memset(result, '\0', strlen(result));
		ret = 1;
		return ret;
	    }
	    strcat(result, substr);
	    strcat(result, " ");
	    substr = substring(w, i, len); //i -> len
	    ret = getwords(diction, substr, len - i, result, str, ret);

	    if (ret == 1)
		    return ret;
	    }
    }
}

int main(int argc, char* argv[]){
	
	size_t N = n;
	const char* filename = "diction10k.txt";
	FILE* fp;
        fp = fopen(filename, "r");
	
	//malloc dictionary	
	int i;
	size_t size = 20;
	//-------------GET DICTIONARY----------
	char** diction = (char**)malloc(sizeof(char*) * NUM_WORDS*2);
	if (fp != NULL){
  	    for (i = 0; i < NUM_WORDS; i++){
	        diction[i] = (char*)malloc(sizeof(char) * 25);

		getline(&diction[i], &size, fp);
		strtok(diction[i], "\n");
		char* words = malloc(sizeof(char) * 20);
		words = diction[i];
		words[strlen(words) - 1] = 0;
		diction[i] = words;
	    }
	}
	i = 0;
	fclose(fp);
	
	
	char lines[3]; 
	fgets(lines, 3, stdin); //reads in number of lines
	int line_num = (int)(lines[0] - '0');
	
	char** buffer = malloc(sizeof(char*) * line_num);
	for (int i = 0; i < line_num; i++){
	    buffer[i] = malloc(sizeof(char) * 100);
	}
	

//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}


	int validstring = 0;
	int len;
	for (int i = 0; i < line_num; i++){
	    
	    len = strlen(buffer[i]); // +1
	    char* result = malloc(sizeof(char)* 256);
	    strcpy(result, "");
	    validstring = split(diction, buffer[i]); //check if buffer[i] is in diction

            int ret = 0;
	    if(validstring ==1 ){
		printf("phrase %d\n%s\n",i, buffer[i]);
		printf("output %d\nYES, can split\n", i);
		getwords(diction, buffer[i], len, result, buffer[i], ret);
  	    }
	    else{
		printf("phrase %d\n%s\n",i,  buffer[i]);
		printf("output %d\nNO, cannot split\n", i);
	    }
	}

}
