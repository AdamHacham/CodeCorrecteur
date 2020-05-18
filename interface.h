#ifndef INTERFACE_H__
#define INTERFACE_H__

#define TAILLE_BUFFER 150

//const char* function_Strings[] = {"HammingCode", "CodeParite", "DistanceMinimal", "Code", "ReedMuller"};
int traitement_buffer(char buffer[],char * function, char * variable, char ** params);
void commande_client(char buffer[], char *variables, char *functions, char **param, int z);
int cfileexists(const char * filename);
char * concatstring(char * name,char * ext);
#endif /* __INTERFACE_H__ */
