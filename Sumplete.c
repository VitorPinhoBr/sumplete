#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)
 
typedef struct {
	int tamanho;
	int tempoJogo; 
	char nome[27];
	int *somaLinha;
	int *somaColuna;
	int **matrizJogo;
	int **matrizSolucao;
	int **matrizCor;
	int quantidade_adicionar;
	
} JogoSumplete;

void tabelaComandos()
{
	printf("Bem vindo ao Jogo SUMPLETE\n");
	printf("\n");
	printf("Comandos do jogo\n");
	printf(BOLD("ajuda: ")"Exibe os comandos do jogo\n");
	printf(BOLD("sair: ")"Sair do jogo\n");
	printf(BOLD("novo: ")"Começar novo jogo\n");
	printf(BOLD("carregar: ")"Carregar um jogo salvo em arquivo\n");
	printf(BOLD("ranking: ")"Exibir o ranking\n");
	printf(BOLD("salvar <nome do arquivo>: ")"Salva o jogo\n");
	printf(BOLD("dica: ")"Marca uma posição no jogo\n");
	printf(BOLD("resolver: ")"Resolve o jogo atual\n");
	printf(BOLD("adicionar <lin> <col>: ")"marca a posição <lin> <col> para entrar na soma\n");
	printf(BOLD("remover <lin> <col>: ")"remove a posição da soma\n");
	printf("\n");
}
	

int** criaMatriz(int m,int n)
{
    int **mat;
    mat = malloc(m * sizeof(int*));
    for(int i=0;i<m;i++){
        mat[i] = malloc(n * sizeof(int));
        if(mat[i]==NULL){
            for(int j=0;j<i;j++)
                free(mat[j]);
            free(mat);
            return NULL;
        }
    }   
    return mat;    
}
void liberaMatriz(int **mat,int m)
{
    for(int i=0;i<m;i++)
        free(mat[i]);
    free(mat);
}

 void limpar_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
void inicializaMatriz(int** matriz,int tamanho)
{
	for(int i=0;i<tamanho;i++)
		for(int j=0;j<tamanho;j++)
			matriz[i][j] = 0;
}
void alocarJogo(JogoSumplete *jogo){
	jogo->matrizJogo = criaMatriz(jogo->tamanho,jogo->tamanho);			
	jogo->matrizSolucao = criaMatriz(jogo->tamanho,jogo->tamanho);
	jogo->matrizCor = criaMatriz(jogo->tamanho,jogo->tamanho);
	
	
	inicializaMatriz(jogo->matrizJogo,jogo->tamanho);
	inicializaMatriz(jogo->matrizSolucao,jogo->tamanho);
	inicializaMatriz(jogo->matrizCor,jogo->tamanho);
}


void sair(int num_comando)
{
	char SN;
	int teste = 0;
	do{
		int teste = 0;
		if((num_comando == 3) || (num_comando == 4)){
			printf("Você quer salvar o jogo antes de sair?(S/N): ");
			scanf("%c",&SN);
		}
		if((SN=='S') || (SN=='s')){
			printf("Jogo salvo!");
			//salvar();
		}
		else if((SN=='N') || (SN=='n')){
			printf("Jogo não salvo");
		}
		else{
			printf("Insira uma resposta válida");
			teste = 1;
		}
	}while(teste != 0);
}

void criarNovoJogo(JogoSumplete *jogo) 
{
	int sLinha = 0,sColuna = 0;

	srand(time(NULL));
	
	if(jogo->tamanho ==3){
		int tam = 3;
		for(int i=0;i<tam;i++){					//matriz jogo
			for(int j=0;j<tam;j++)
				jogo->matrizJogo[i][j] = (rand()%8)+1; 
		}
		jogo->quantidade_adicionar = 0;
		for(int i=0;i<tam;i++){					//matriz solucao
			for(int j=0;j<tam;j++){
				jogo->matrizSolucao[i][j] = (rand()%2);
				if(jogo->matrizSolucao[i][j] == 1)
					jogo->quantidade_adicionar +=1; //qtd de respostas add
			}
		}
		jogo->somaLinha = malloc(tam * sizeof(int));
		jogo->somaColuna = malloc(tam * sizeof(int));
		
		
		for(int i=0;i<tam;i++){				//soma linha
			sLinha = 0;
			for(int j=0;j<tam;j++){
				if(jogo->matrizSolucao[i][j] == 1){
					sLinha += jogo->matrizJogo[i][j];
				}
			}
			jogo->somaLinha[i] = sLinha;
		}
		
		
		for(int i=0;i<tam;i++){			//soma coluna
			sColuna = 0;
			for(int j=0;j<tam;j++){
				if(jogo->matrizSolucao[j][i] == 1){
					sColuna += jogo->matrizJogo[j][i];
				}
			}
			jogo->somaColuna[i] = sColuna;
		}
		
	}
	
	
	else if(jogo->tamanho ==5)
		printf("5x5");
	else if(jogo->tamanho==7)
		printf("7x7");
}
void novo(JogoSumplete *jogo)
{

	
	char dif;
	printf("Digite o nome do jogador: ");
	scanf("%s",jogo->nome); limpar_buffer();
	printf("Digite o nível de dificuldade:\n");
	printf(BOLD("F: ")"nível fácil, tamanho 3x3\n");
	printf(BOLD("M: ")"nível médio, tamanho 5x5\n");
	printf(BOLD("D: ")"nível difícil, tamanho 7x7\n");
	scanf("%c",&dif); limpar_buffer();
	if((dif =='F') || (dif =='f')){									
		jogo->tamanho = 3;		
		alocarJogo(jogo);
		criarNovoJogo(jogo);
	}
	else if((dif =='M') || (dif =='m')){
		jogo->tamanho = 5;
		alocarJogo(jogo);
		criarNovoJogo(jogo);
	}
	else if((dif =='D') || (dif =='d')){
		jogo->tamanho = 7;
		alocarJogo(jogo);
		criarNovoJogo(jogo);
	}
	else
		printf("insira uma dificuldade válida!");
	
}

int verifica_Vitoria(JogoSumplete *jogo,int tam)
{
	for(int i=0;i<tam;i++)						//condicao de vitoria
		for(int j=0;j<tam;j++){
			if(jogo->matrizSolucao[i][j] == 0)		
				if(jogo->matrizCor[i][j] !=2)		//nao marcou como errado
					return 0;						//ainda nao ganhou		
			if(jogo->matrizSolucao[i][j] == 1 && jogo->matrizCor[i][j] == 2)
				return 0;							//removeu o errado
		}
			
	return 1;
}

void resolver(JogoSumplete *jogo,int tam)
{
	printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "\n"); //print primeira linha
	printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");

	int k =0;

	for(int i=0;i<tam;i++){	 						//print matriz + somaLinha
		printf("%d",i+1);
		for(int j=0;j<tam+1;j++){
			if(j<tam){
				if(jogo->matrizSolucao[i][j] == 1)
					printf(TAB_VER GREEN("%d "),jogo->matrizJogo[i][j]);
				else
					printf(TAB_VER RED("%d "),jogo->matrizJogo[i][j]);
			}
			else{
				printf(TAB_VER "%d",jogo->somaLinha[k]);
				k++;
			}
		}
		printf("\n");
		printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
	}
	printf(" ");
	for(int i=0;i<tam;i++){
		if(jogo->somaColuna[i] <10)
			printf(TAB_VER "%d ",jogo->somaColuna[i]);
		else
			printf(TAB_VER "%d",jogo->somaColuna[i]);
	}
	printf(TAB_VER);
	printf("\n");

	
}

void carregar(JogoSumplete *jogo,char *fileName){
	int tam=0;
	strcat(fileName,".sum.txt");
	FILE *arquivo = fopen(fileName,"r");
	if(arquivo == NULL)
		printf("Não foi encontrado o arquivo");
	else{
		fscanf(arquivo,"%d",&jogo->tamanho);
		tam = jogo->tamanho;
		alocarJogo(jogo);
		jogo->somaLinha = malloc(tam * sizeof(int));
		jogo->somaColuna = malloc(tam * sizeof(int));
		
	
		for(int i=0;i<tam;i++){
			for(int j=0;j<tam;j++){
				fscanf(arquivo,"%d",&jogo->matrizJogo[i][j]);	//lê a matriz do jogo
			}
		}
		for(int i=0;i<tam;i++)
			fscanf(arquivo,"%d",&jogo->somaLinha[i]);			//lê soma linha
		for(int i=0;i<tam;i++)
			fscanf(arquivo,"%d",&jogo->somaColuna[i]);			//lê soma coluna
		
		
		
	}
	
	
	
	free(jogo->somaLinha);
	free(jogo->somaColuna);
	liberaMatriz(jogo->matrizJogo,tam);		
	liberaMatriz(jogo->matrizSolucao,tam);
	liberaMatriz(jogo->matrizCor,tam);
	fclose(arquivo);
}

void salvar(JogoSumplete *jogo, char *fileName){
	int tam=0,quantidade_remover=0,quantidade_movimentos=0;
	tam = jogo->tamanho;
	quantidade_remover =(tam*tam) - jogo->quantidade_adicionar;
	strcat(fileName,".sum.txt");
	
	for(int i=0;i<tam;i++)
		for(int j=0;j<tam;j++)
			if(jogo->matrizCor[i][j] == 1 || jogo->matrizCor[i][j] == 2)
				quantidade_movimentos +=1; 
	
	FILE *arquivo = fopen(fileName,"w"); // adicionar .sum
	if(arquivo == NULL){
		printf("Não foi encontrado o arquivo");
	}
	else
	{
		fprintf(arquivo,"%d\n",tam);								//add tamanho matriz		
		for(int i=0;i<tam;i++){
			for(int j=0;j<tam;j++){
				fprintf(arquivo,"%d ",jogo->matrizJogo[i][j]);		//add matriz no arquivo
			}
			fprintf(arquivo,"\n");
		}
		for(int i=0;i<tam;i++)
			fprintf(arquivo,"%d ",jogo->somaLinha[i]);				//add soma linha
		fprintf(arquivo,"\n");
		
		for(int i=0;i<tam;i++)
			fprintf(arquivo,"%d ",jogo->somaColuna[i]);				//add soma coluna
		fprintf(arquivo,"\n");
		
		fprintf(arquivo,"%d\n",quantidade_remover);					//numero de remoções 
		
		for(int i=0;i<tam;i++){
			for(int j=0;j<tam;j++){									//add posições das remoções
				if(jogo->matrizSolucao[i][j] == 0)
					fprintf(arquivo,"%d %d\n",i+1,j+1);	
			}
		}
		
		fprintf(arquivo,"%d\n",quantidade_movimentos);	//add quantidade de movimentos
		for(int i=0;i<tam;i++)
			for(int j=0;j<tam;j++)
				if(jogo->matrizCor[i][j] == 1)
					fprintf(arquivo,"a %d %d\n",i+1,j+1);
				else if(jogo->matrizCor[i][j] == 2)
					fprintf(arquivo,"r %d %d\n",i+1,j+1);
		
		fprintf(arquivo,"%s\n",jogo->nome);							//add nome
		fprintf(arquivo,"Tempo gasto: ?");							//add tempo
	}
	fclose(arquivo);
}
 
int main(){
	//tabela inicial
	char comando[15];
	char fileName[20];
	int num_comando=0,exit=0;
	JogoSumplete jogo;
	tabelaComandos();
	//comandos
	printf("Digite um comando: ");
	scanf("%15s",comando); limpar_buffer();
	if(strcmp(comando,"ajuda")==0){
		num_comando = 1;
		tabelaComandos();
	}
	else if(strcmp(comando,"sair")==0){
		num_comando = 2;
		exit = 1;
	}
	else if(strcmp(comando,"novo")==0){
		num_comando = 3;
		novo(&jogo);
	}
	else if(strcmp(comando,"carregar")==0){
		num_comando = 4;
		printf("Insira o nome do jogo salvo: ");
		scanf("%s",fileName);	limpar_buffer();			//fazer: tratar condicao
		carregar(&jogo,fileName);
	}
	else if(strcmp(comando,"ranking")==0){
		num_comando = 5;
	}
	else if(strcmp(comando,"salvar")==0){
		printf("crie um novo jogo antes de salvar");
		num_comando = 6;
	}
	else if(strcmp(comando,"dica")==0){
		printf("crie um novo jogo antes de uma dica");
		num_comando = 7;
	}
	else if(strcmp(comando,"resolver")==0){
		printf("crie um novo jogo antes de resolver");
		num_comando = 8;
	}
	else if(strcmp(comando,"adicionar")==0){
		printf("crie um novo jogo antes de adicionar");
		num_comando = 9;
	}
	else if(strcmp(comando,"remover")==0){
		printf("crie um novo jogo antes de remover");
		num_comando = 10;
	}
	else
		printf("insira um comando válido!\n");
	
	
	if(exit!=0) {
		return 1;
	}
	

	if(jogo.tamanho ==3){
		int tam = 3;
		do
		{
			printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "\n"); //print primeira linha
			printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
			
			int k =0;
			
			for(int i=0;i<tam;i++){	 						//print matriz + somaLinha
				printf("%d",i+1);
				for(int j=0;j<tam+1;j++){
					if(j<tam){
						if(jogo.matrizCor[i][j] ==0)
							printf(TAB_VER "%d ",jogo.matrizJogo[i][j]);
						else if(jogo.matrizCor[i][j] == 1)
							printf(TAB_VER GREEN("%d "),jogo.matrizJogo[i][j]);
						else
							printf(TAB_VER RED("%d "),jogo.matrizJogo[i][j]);
					}
					else{
						printf(TAB_VER "%d",jogo.somaLinha[k]);
						k++;
					}
				}
				printf("\n");
				printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
			}
			printf(" ");
			for(int i=0;i<tam;i++){
				if(jogo.somaColuna[i] <10)
					printf(TAB_VER "%d ",jogo.somaColuna[i]);		//printf soma coluna
				else
					printf(TAB_VER "%d",jogo.somaColuna[i]);
			}
			printf(TAB_VER);
			printf("\n\n");

			int linha,coluna;
			printf("%s, digite o comando: ",jogo.nome);
			scanf("%s",comando);							//testa comando
			if(strcmp(comando,"adicionar")==0){
				scanf("%d %d",&linha,&coluna);
				jogo.matrizCor[linha-1][coluna-1] = 1;		//printf verde
			}
			else if(strcmp(comando,"remover")==0){
				scanf("%d %d",&linha,&coluna);
				jogo.matrizCor[linha-1][coluna-1] = 2;		//printf vermelho
			}
			else if(strcmp(comando,"sair")==0)
				exit = 1;
			else if(strcmp(comando,"ajuda")==0)
				tabelaComandos();
			else if(strcmp(comando,"salvar")==0){
				scanf("%s",fileName);
				salvar(&jogo,fileName);
			}
			
			
			
			else{
				printf("insira um comando válido\n");
				limpar_buffer();
			}
			int vitoria = 0;
			vitoria = verifica_Vitoria(&jogo,tam);
			
			if(vitoria ==1){								// print vitoria
				
				printf("\n" GREEN("Parabéns! Você ganhou!\n"));
				exit = 1;
				resolver(&jogo,tam);
			}
			
		} while (exit==0);
	
	free(jogo.somaLinha);
	free(jogo.somaColuna);
	liberaMatriz(jogo.matrizJogo,tam);		
	liberaMatriz(jogo.matrizSolucao,tam);
	liberaMatriz(jogo.matrizCor,tam);
	}
 }