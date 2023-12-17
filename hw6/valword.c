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
		//printf("num words = %d", NUM_WORDS);
		if (diction[i][0] == w[0]){
		if (strcmp(diction[i], w) == 0){
			printf("comparing diction[%d]: %s and w: %s\n",i, diction[i], w); 
			return 1;
//			printf("yay match %s %s\n", diction[i], w);
		
		}
		}
	}
	return 0;
}

int split(char** diction, int val, char* w,int i){ //w is the whole string of letters
	char newstr[strlen(w) +1];
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
			int dict_val = dict(diction, newstr); //is this newstr in the dictionary?
			int split_val = split(diction, val, w, j+1);
			printf ("%d OR (%d AND %d)\n", val, dict_val, split_val);
			val = val || (dict_val && split_val);
//			val =  (val) || (dict_val && split(diction, val, w, j+1));
		}
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
	

//	fflush(stdin);
//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}

//	int val = 0;

//	int validstring = 0;
 	validstring = split(diction, 0, buffer[0], 0); //check if buffer[i] is in diction

	if(validstring ==1 )
		printf("YES, can split");
	else
		printf("NO, cannot split");

	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
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
		//printf("num words = %d", NUM_WORDS);
		if (diction[i][0] == w[0]){
		if (strcmp(diction[i], w) == 0){
			printf("comparing diction[%d]: %s and w: %s\n",i, diction[i], w); 
			return 1;
//			printf("yay match %s %s\n", diction[i], w);
		
		}
		}
	}
	return 0;
}

int split(char** diction, char* w,int i){ //w is the whole string of letters
	char newstr[strlen(w) +1];
	int len = (int)strlen(w); //include newline
	int val = 1; //try with 0 also
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
			int dict_val = dict(diction, newstr); //is this newstr in the dictionary?
			int split_val = split(diction, w, j+1);
			printf ("%d OR (%d AND %d)\n", val, dict_val, split_val);
			val = val || (dict_val && split_val);
//			val =  (val) || (dict_val && split(diction, val, w, j+1));
		}
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
	

//	fflush(stdin);
//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}

//	int val = 0;

	int validstring = 0;
 	validstring = split(diction, buffer[0], 0); //check if buffer[i] is in diction

	if(validstring ==1 )
		printf("YES, can split");
	else
		printf("NO, cannot split");

	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
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
		//printf("num words = %d", NUM_WORDS);
		if (diction[i][0] == w[0]){
		if (strcmp(diction[i], w) == 0){
			printf("comparing diction[%d]: %s and w: %s\n",i, diction[i], w); 
			return 1;
//			printf("yay match %s %s\n", diction[i], w);
		
		}
		}
	}
	return 0;
}

int split(char** diction, char* w,int i){ //w is the whole string of letters
	char newstr[strlen(w) +1];
	int len = (int)strlen(w); //include newline
	int val = 1; //try with 0 also
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
			int dict_val = dict(diction, newstr); //is this newstr in the dictionary?
			int split_val = split(diction, w, j+1);
			printf ("%d OR (%d AND %d)\n", val, dict_val, split_val);
			val = val || (dict_val && split_val);
//			val =  (val) || (dict_val && split(diction, val, w, j+1));
		}
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
	

//	fflush(stdin);
//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}

//	int val = 0;

	int validstring = 0;
 	validstring = split(diction, buffer[1], 0); //check if buffer[i] is in diction

	if(validstring ==1 )
		printf("YES, can split");
	else
		printf("NO, cannot split");

	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
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
		//printf("num words = %d", NUM_WORDS);
		if (diction[i][0] == w[0]){
		if (strcmp(diction[i], w) == 0){
		//	printf("comparing diction[%d]: %s and w: %s\n",i, diction[i], w); 
			return 1;
		 }
		}
	}
	return 0;
}

int split(char** diction, char* w,int i, int old_val){ //w is the whole string of letters
	char newstr[strlen(w) +1];
	int new_val = 0;
	int len = (int)strlen(w); //include newline
//	int val = 0; //try with 0 also
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
		if (i == (len + 1)){ //bottom of recursion
		    return 1;
		}
		else{
		        new_val = dict(diction, newstr) & split(diction, w, j+1, old_val);
			new_val = old_val | new_val;
//			int dict_val = dict(diction, newstr); //is this newstr in the dictionary?
//			int split_val = split(diction, w, j+1);
//			printf ("%d OR (%d AND %d) - %s\n", val, dict_val, split_val, newstr);
//			val = (val | (dict_val & split_val));
			//val = val || (dict_val && split_val);
//			val =  (val) || (dict_val && split(diction, val, w, j+1));
		}
	}
	
	return new_val;
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
	

//	fflush(stdin);
//	//---------GET LINE FROM FILES-----
	for (int i = 0; i < line_num; i++){
		fgets(buffer[i], n, stdin);
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}

//	int val = 0;

	int validstring = 0;
	for (int i = 0; i < line_num; i++){
	validstring = split(diction, buffer[i], 0, 0); //check if buffer[i] is in diction

	if(validstring ==1 ){
		printf("YES, can split");
		printf("%s", buffer[i]);
	}
	else{
		printf("NO, cannot split");
		printf("%s", buffer[i]);
	    }
	}
	end = clock();
	time_used = ((double) (end-start));
//	printf("time: %lf\n", time_used)/CLOCKS_PER_SEC;
}
