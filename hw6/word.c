#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_WORDS 58114
			
#define n 200

//FIX SPLIT
//WRITE GETWORD

int dict(char** diction, char* w, int k, int** valid){ //w is whole string to compare?
	for (int i = 0; i < NUM_WORDS; i++){
		if (strcmp(diction[i], w) == 0){
			valid[k][strlen(w)] = 1;
//			printf("got a match %s\n", w);
			return 1;
		}
	}
	return 0;
}

int new_split(char** diction, char* w, int i, int** valid){
	char substr[strlen(w) +1];
	int l = 0;
	int split_val = 0;
	
	int len = (int)strlen(w); //include newline
	printf("len= %d", len);
	int dict_val = 0;
	int val = 1;
	
	if (len == 0) //no string => base case
		return 0;
	if (i == (len)){ //bottom of recursion
		return 1;
	}
	else{
	    
	    for (int j = i; j < len; j++)
	    {
		for (int m = 0; m <= len; m++)
		    newstr[m] = '\0';
	       
		for (int k = i; k <= j; k++){
		    newstr[l] = w[k];
		    l++;
		}
		
	for (int i = 0; i < 100; i++){
		valid[i] = malloc(sizeof(char) * 25);
	}
		substr[l] = w[j];
	        printf(" %s\n", substr);
	        dict_val = dict(diction, substr, i, valid); //is this newstr in the dictionary

		split_val = new_split(diction, w, j+1); 
	        val = val || (dict_val && split_val);
	        l++;
	    }
	}
	/*
	int index = 0;
	
	while (i < len){
		while (j < len){
			while (index < len){
			
		         if (valid[i][j] == 1){
			     valid[i + j][j]
		         }
			}

		j++;
		}
	    i++;
	}
	if (success == 1)
		return 1;

	for (int i = 0; i < len; i++){
		for (int j = 0; j < 
	return val;
//	return is_word[len] | (dict_val & is_word[j+1]);
}

int split(char** diction, char* w,int i){ //w is the whole string of letters
	char newstr[strlen(w) +1];
	int len = (int)strlen(w); //include newline
	int val[len];
	int split_val = 0;
	char* newword = malloc(sizeof(char) * strlen(w) +1);
	if (i == (len)){ //ottom of recursion
		return 1;
	}
	else{
//	   int j = i;
//	    while (j < len){
	    	//update length of loop/recursions
	    for (int j = i; j < len; j++){ //or from j = i -> n
	    	    int l = 0;	
//reset string
		for (int m = 0; m <= len; m++)
		    newstr[m] = '\0';
	
		//get characters from i->j
	       for (int k = i; k <= j; k++){
		    newstr[l] = w[k];
		    l++;
		}
//		printf("i = %d, j = %d\n", i, j);
	        printf("w: %s newstr: %s\n", w, newstr);
	        
		int dict_val = dict(diction, newstr); //is this newstr in the dictionary?
//		if (is_word[j+1] == 1){
//	    	    len = j; //finish loop then break, dont go any further
//		}
//		else{ //is not a word -> will not be all way down recursion
			int split_val = split(diction, w, j+1);
//		}
//		else (is_word[i] == 1){
//			split_val = split(diction, w, i, is_word);
		//after on way back up with recurssion -> 
		l = 0;
		if (dict_val == 1 && j == (len-1)){
		    
		    for(int k = i; k < j; k++)
		    {
			w[k] = '\0';
//		    	newword[l] = w[k];
//			l++;
		    }
//		    w = newword;
		    len = strlen(w);
		   // split_val = 1;
		   // is_word[i] == 1; //is word from j - k dont wanna redo    
		}
		//
//		if (is_word[i] == 1){
//	  	  len = i;
//		}
		//else
		//	split_val = 0;
//		is_word[j] = dict_val;
		val[j] = dict_val && split_val;	
	//	l++;
		j++;
	    }
	}
	int val_total = val[i];
	for (int j = i+1; j < len; j++){
//	    printf("%d\n", val[j]);
	    val_total = val_total || val[j];
	}	

	return val_total;
}
int getwords(char* w, char** diction){

	int len = (int)strlen(w);
	int start = 0;
	for (int i = 0; i < len; i++){
		char* split_word = malloc(sizeof(char)*len+1);
		//reset word
//		for (int m = 0; m < len; m++)
//		    split_word[m] = '\0';
		
		int l = 0;
		printf("i : %d\n", i);
		printf("start: %d\n", start);
		for (int k = start; k < i; k++){
		    split_word[l] = w[k];
		    l++;
		    printf("int getwords:  %s\n", split_word);
		}
		
		char final[len+1];
		int z = 0;
		while (split_word[z] != '\0'){
			final[z] = split_word[z];
			z++;
		}
		final[z] = '\0';
		if (dict(diction, final) == 1){ //if is a real word
			printf("split word: %s \n", split_word); //print said word
			start = i;
		}
		free(split_word);
//		i++; //incremement i. 
	}
	//printf(words);
}
int main(int argc, char* argv[]){
	
	clock_t start, end;
	double time_used;
	start = clock();
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
	char** valid = malloc(sizeof(char*) * 100);

	int *is_word = malloc(sizeof(int) * n); //or whatever

	for (int i = 0; i < line_num; i++){
//	for (int j = 0; j < n; j++)
//		is_word[j] = 0;
	validstring = new_split(diction, buffer[i], 0, valid); //check if buffer[i] is in diction

	if(validstring ==1 ){
		printf("YES, can split");
		printf("%s", buffer[i]);
	}
	else{
		printf("NO, cannot split");
		printf("%s", buffer[i]);
	    }
	//getword
	}
	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
