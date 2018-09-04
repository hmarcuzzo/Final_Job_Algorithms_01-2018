#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *arquivo_decodificado;
FILE *frase_codificada;

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

void codifica(const char *frase_decodificada){

	size_t i, j;

    frase_codificada = fopen("codificado.txt", "w");
    fclose(frase_codificada);

    frase_codificada = fopen("codificado.txt", "a");
    

		printf("Texto Codificado:\n");

		for (i = 0; frase_decodificada[i]; ++i)
			for (j = 0; j < sizeof Dicionario / sizeof *Dicionario; ++j)
				if (toupper(frase_decodificada[i]) == Dicionario[j].letra){
	    			printf("%s", Dicionario[j].morse);
                    fputs(Dicionario[j].morse, frase_codificada);
                    break;
                }
        fputs("\n", frase_codificada);
        fclose(frase_codificada);
		printf("\n");
}


void main(){

    int user_option = 0, tamanho;
    char frase_decodificada[1000];

    do{
		printf("\t\t\tDigite uma opção\n");
		printf("1 - Codifica\n");
		printf("999 - Sair\n");
		printf("\nOpção: ");
		scanf("%d",&user_option);

        switch (user_option){
            case 1:{
                arquivo_decodificado = fopen("decodificado.txt", "r");

        		printf("Texto Decodificado:\n");
                
                if (arquivo_decodificado == NULL)
                    printf("Erro na Abertura do arquivo!\n");
                else{
                    while(fgets(frase_decodificada, 1000, arquivo_decodificado) != NULL){
                        fscanf(arquivo_decodificado, " %[^\n]", frase_decodificada);

                        if(ferror(arquivo_decodificado))
                            printf("Erro na leitura do arquivo!\n");
                        else{
                            tamanho = strlen(frase_decodificada);
                            printf("%s\n", frase_decodificada);
                        }
                    }
                }
                fclose(arquivo_decodificado);

                codifica(frase_decodificada);
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
