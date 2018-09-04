#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

FILE *arquivo_codificado;
FILE *arquivo_decodificado;

static const struct{
    const char letra, *morse;
} Dicionario[] ={
    {'A', ".- "},{'B', "-... "},{'C', "-.-. "},{'D', "-.. "        },
    {'E', ". "},{'F', "..-. "},{'G', "--. "},{'H', ".... "         },
    {'I', ".. "},{'J', ".--- "},{'K', ".-.- "},{'L', ".-.. "       },
    {'M', "-- "},{'N', "-. "},{'O', "--- "},{'P', ".--. "          },
    {'Q', "--.- "},{'R', ".-. "},{'S', "... "},{'T', "- "          },
    {'U', "..- "},{'V', "...- "},{'W', ".-- "},{'X', "-..- "       },
    {'Y', "-.-- "},{'Z', "--.. "},{' ', "/ "},{'1', ".---- "       },
    {'2', "..--- "},{'3', "...-- "},{'4', "....- "}, {'5', "..... "},
    {'6', "-.... "},{'7', "--... "},{'8', "---.. "},{'9', "----. " },
    {'0', "----- "},
};

void decodifica(){

    size_t i, j;
    int tamanho;
    char letra_morse[7];

    printf("\nFrase Decodificada:\n");

    arquivo_decodificado = fopen("decodificado.txt", "w");
    fclose(arquivo_decodificado);


    arquivo_codificado = fopen("codificado.txt", "r");
    arquivo_decodificado = fopen("decodificado.txt", "a");

    tamanho = sizeof(Dicionario);
    tamanho /= sizeof(*Dicionario);
    
    while(1){
    	fscanf(arquivo_codificado, "%s", letra_morse);

    	if (feof(arquivo_codificado)){
    		break;
    	}
    	
    	strcat(letra_morse, " ");

    	if (feof(arquivo_codificado)){
    		break;
    	}
		for (j = 0; j < tamanho; j++){
			if (strcmp(letra_morse, Dicionario[j].morse) == 0){
    			printf("%c", Dicionario[j].letra);
                fputc(Dicionario[j].letra, arquivo_decodificado);
                break;
           }
        }
    }
    printf("\n");
    fputs("\n", arquivo_decodificado);
    fclose(arquivo_codificado);
    fclose(arquivo_decodificado);
}


void main(){

    int user_option = 0, tamanho;
    char frase_morse[1000];

    do{
		printf("\t\t\tDigite uma opção\n");
		printf("1 - Decodifica\n");
		printf("999 - Sair\n");
		printf("\nOpção: ");
		scanf("%d",&user_option);

        switch (user_option){
            case 1:{
                arquivo_codificado = fopen("codificado.txt", "r");

                if (arquivo_codificado == NULL)
                    printf("Erro na Abertura do arquivo!\n");
                else{
                    printf("Frase em Morse:\n");

                    while(1){
                        fscanf(arquivo_codificado, " %[^\n]", frase_morse);

                        if(ferror(arquivo_codificado)) 
                            printf("Erro na leitura do arquivo!\n");
                        else{
                        	if (feof(arquivo_codificado)){
                        		break;
                        	}
                            printf("%s\n", frase_morse);
                        } 
                    }
                }
                fclose(arquivo_codificado);

                decodifica();
                break;
            }
            case 999:{
                printf("Adeus e até logo!\n");
                break;
            }
            default:{
              printf("Opção Inválida!");
              break;
            }
        }
    }while(user_option == 0);
}