#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_WORDS 58114
			
#define n 200

int dict(char** diction ,char* w){ //w is whole string to compare?
	for (int i = 0; i < NUM_WORDS; i++){
		int match = 1;
		//printf("comparing diction[%d]: %s and w: %s\n",i, diction[i], w); 
		
		if (strcmp(diction[i], w) == 0)
			return 1;
		else
			return 0;
			printf("yay match %s %s\n", diction[i], w);
	//	if (diction[i][0] == w[0] && strlen(diction[i]) == strlen(w)){ //check if faster or slower  
			//printf("1. %s\nand 2. %s\n", diction[i], w);
/*			for (int j = 0; j < strlen(w); j++){
		    	    if (diction[i][j] != w[j])
			        match = 0;
			}
			if(match == 1){
				printf("match: %s and %s\n", diction[i], w);
			    }*/
//		if (strcmp(diction[i], w) == 0){// && (diction[i] != ' ' && w != ' ')){ //are equal -> return true
//			printf("comparing words %s == %s\n", diction[i], w);
 //		        return 1;
//		    }
//		else
//			printf("%s and %s\n", w, diction[i]);
//		}
/*		if (diction[i][0] == w[0]){ //TODO: make this faster if first character is same.  
			//printf("first diction = %c, first w = %c\n", diction[i][0], w[0]);
			//TODO make this actually work.
			if(strlen(diction[i]) == strlen(w)){	
		           int size = strlen(diction[i]);
			   for (int j = 0; j < size; j++){
				if (diction[i][j] != w[j]){
				    match = 0;
				}
			   }
			   if (match == 1){
	//			   printf("we found match");
	 			   printf("%s == %s\n", diction[i], w);
				   return match;
			   }
			   // printf("diction len = %ld, w len = %ld\n", strlen(diction[i]), strlen(w));    
			}
		//	else{}
	//			printf("%s != %s\n", diction[i], w);
			
		}
		*/
	}

	return 0;
}

int split(char** diction, int val, char* w,int i){ //w is the whole string of letters
	char newstr[strlen(w) +1];
	int new_val;
	int old_val;
	int len = (int)strlen(w); //include newline
	for (int j = i; j < len; j++){ //or from j = i -> n
		int l = 0;
	
		//reset string
		for (int m = 0; m < len; m++)
		    newstr[m] = '\0';
	
		//get characters from i->j
		for (int k = i; k <= j; k++){
		    newstr[l] = w[k];
		    l++;
		}
//	        printf("%s\n", newstr);
		if (i == (n + 1)){ //bottom of recursion
		    return 1;
		}
		else{
			int dict_val = dict(diction, newstr);
			int split_val = split(diction, val, w, j+1);
		//	val = val || (dict_val && split_val);
			val =  val || floor(dict_val && split(diction, val, w, j+1));
//			new_val = old_val || (dict_val && split(diction, new_val, w, j+1));
		}
//		fflush(stdout);
			//return val;
			//return val;
	}
	
	return val;
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
//		fgets(diction[i], 20, fp);
		strtok(diction[i], "\n");
//		strtok(diction[i], " ");
		char* words = malloc(sizeof(char) * 20);
		words = diction[i];
//		word[strcspn(word, "\n")] = 0;
		words[strlen(words) - 1] = 0;
		diction[i] = words;
//		diction[i][strcspn(diction[i], "\n")] = 0;
//		diction[i][strcspn(diction[i], " ")] = 0;
//		printf("word: %s\n", diction[i]);		
	    }
	}
//	fflush(stdin);

	printf("diction 0 and 1 %s %s\n", diction[0], diction[1]);
	i = 0;
		
	fclose(fp);
	
	char lines[3]; 
	fgets(lines, 3, stdin); //reads in number of lines
	int line_num = (int)(lines[0] - '0');
	
//	printf("line_num: %d\n", line_num);
	
	char** buffer = malloc(sizeof(char*) * line_num);
	for (int i = 0; i < line_num; i++){
	    buffer[i] = malloc(sizeof(char) * 100);
	}
	

//	fflush(stdin);
//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
//		strtok(buffer[i], "\n");
		//printf("buffer[0] = %s", buffer[0]);
	}

//	printf("buffer[0] = %s", buffer[0]);
	int val = 1;

	int validstring = 0;
//	for (i = 0; i < line_num; i++){
//		printf("buffer[%d] = %s",i, buffer[i]);
//		validstring = split(diction, 1, buffer[i], 0); //check if buffer[i] is in diction
 	validstring = split(diction, 1, buffer[1], 0); //check if buffer[i] is in diction

	printf("%s is %d valid \n", buffer[1], validstring);
//		getwords(buffer[0], diction);
//	    validstring = 0;
//	}

	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
