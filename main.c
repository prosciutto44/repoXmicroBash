#include <stdio.h>
#include "pingpong.h"
#define PATH "PATH"
#define PWD "PWD"
#define HOME "HOME"

void fail(const char *const msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
void fail_errno(const char * const msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void *my_malloc(size_t size)
{
    void *result = malloc(size);
    if (!result)
        fail_errno("Cannot allocate memory with malloc");
    return result;
}

void *my_realloc(void *ptr, size_t size)
{
    void *result = realloc(ptr, size);
    if (!result)
        fail_errno("Cannot re-allocate memory");
    return result;
}

void yyerror(void *scanner, const struct shell * const sh, struct node ** const cmd, char const * const msg)
{
    fprintf (stderr, "Parsing error: %s\n", msg);
}

char *my_strdup(const char * const s) {
    char *result = strdup(s);
    if (!result)
        fail_errno("Cannot allocate memory for strdup");
    return result;
}


void stampaPrompt(){

}

void leggiRiga(){

}
void leggiFile(){

}



/*bool isCd(char *comando){
    return( strncmp(comando, "cd", 2)==0 );
        //fail(strcat("errore: il comando %s non esiste", comando));
}*/

char * pwd(){
    char *cwd;
    cwd = getcwd(NULL, 0); //getcwd() allocates the buffer dynamically using malloc(3) if buf is NULL
    if(cwd==NULL)
        fail_errno("Error work");
    //free(cwd);
    return cwd;
}
void cd(char *path){
    if(path==NULL)
        chdir(HOME);
    if(chdir(path) == -1)
        fail_errno("Error: cannot change working directory");
}
int main(int argc, char **argv) {
	int MAX=50;
	FILE *stream=stdin;
	while(1){
	    printf("%s $ ", pwd());
	    char *line=my_malloc(MAX*sizeof(char));
	    fgets(line, MAX, stream);
		//printf("FGETS: %s\n", line);
		if(strncmp(line, "cd", 2)==0){
			char *path=my_malloc(strlen(line));
			for(int i=3; i<strlen(line); ++i){
				path[i-3]=line[i];
			}
			char *pos;
			if ((pos=strchr(path, '\n')) != NULL) //se path termina con \n lo sostituisco con '\0'
				*pos = '\0';
			//printf("PATH E' >%s< $ \n", path);
			cd(path);
			free(path);
	    	//printf("%s $ ", pwd());
		}
		free(line);
		
	}
    //return 0;
}