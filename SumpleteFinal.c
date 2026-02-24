//Vitor Pinho Galvao 25.2.4146
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
	float tempoGasto; 
	char nome[28];
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

void criarNovoJogo(JogoSumplete *jogo) 
{
	int sLinha = 0,sColuna = 0;

	srand(time(NULL));
	
	int tam = jogo->tamanho;
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
void novo(JogoSumplete *jogo)
{
	jogo->tempoGasto = 0;
	int teste =0;
	
	printf("Digite o nome do jogador: ");
	scanf("%s",jogo->nome); limpar_buffer();
	do{
		char dif;			
		printf("Digite o nível de dificuldade:\n");
		printf(BOLD("F: ")"nível fácil, tamanho 3x3\n");
		printf(BOLD("M: ")"nível médio, tamanho 5x5\n");
		printf(BOLD("D: ")"nível difícil, tamanho 7x7\n");
		
		scanf("%c",&dif); limpar_buffer();
		if((dif =='F') || (dif =='f')){									
			jogo->tamanho = 3;		
			alocarJogo(jogo);
			criarNovoJogo(jogo);
			teste = 0;
		}
		else if((dif =='M') || (dif =='m')){
			jogo->tamanho = 5;
			alocarJogo(jogo);
			criarNovoJogo(jogo);
			teste = 0;
		}
		else if((dif =='D') || (dif =='d')){
			jogo->tamanho = 7;
			alocarJogo(jogo);
			criarNovoJogo(jogo);
			teste = 0;
		}
		else{
			printf("insira uma dificuldade válida!\n");
			teste = 1;
		}
	}while(teste ==1);
}

int verifica_Vitoria(JogoSumplete *jogo)
{
	int tam;
	tam = jogo->tamanho;
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

void resolver(JogoSumplete *jogo)
{
	if(jogo->tamanho ==3){
		printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "\n"); //print primeira linha
		printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
	}
	if(jogo->tamanho ==5){
		printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "4 " TAB_VER "5 " TAB_VER "\n"); //print primeira linha
		printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
	}
	if(jogo->tamanho ==7){
		printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "4 " TAB_VER "5 " TAB_VER "6 " TAB_VER "7 " TAB_VER"\n"); //print primeira linha
		printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR"\n");
	}
	
	int tam;
	tam = jogo->tamanho;
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
		printf(TAB_HOR);
		for(int i=0;i<tam+1;i++)
			printf(TAB_MJ TAB_HOR TAB_HOR);
		printf("\n");
	}
	printf(" ");
	for(int i=0;i<tam;i++){
		if(jogo->somaColuna[i] <10)
			printf(TAB_VER "%d ",jogo->somaColuna[i]);		//printf soma coluna
		else
			printf(TAB_VER "%d",jogo->somaColuna[i]);
	}
	printf(TAB_VER);
	printf("\n\n");
}

void dica(JogoSumplete *jogo)
{
	for(int i =0;i<jogo->tamanho;i++)
		for(int j=0;j<jogo->tamanho;j++)
			if(jogo->matrizSolucao[i][j] == 1 && jogo->matrizCor[i][j] !=1){
				jogo->matrizCor[i][j] = 1;
				return;
			}
}

void carregar(JogoSumplete *jogo,char *fileName){
	int tam=0,quantidade_remover=0,quantidade_movimentos=0,tam_nome=0;
	char condicional;
	tam_nome = strlen(fileName);
	if (tam_nome >= 4)
		if(strcmp(&fileName[tam_nome - 5],".sum.txt")!=0)
			strcat(fileName,".sum");
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
		
		fscanf(arquivo,"%d",&quantidade_remover);				//lê número de remoções
		
		for(int i=0;i<tam;i++){
			for(int j=0;j<tam;j++){
				jogo->matrizSolucao[i][j] = 1;						//preenchendo a matriz com '1'
			}	
		}	
		int lin,col;
		for(int i=0;i<quantidade_remover;i++){						//removendo os necessários
			fscanf(arquivo,"%d %d",&lin,&col);
			jogo->matrizSolucao[lin-1][col-1] = 0;
		}
		
		fscanf(arquivo,"%d",&quantidade_movimentos);				//lê quantidade de movimentos feitos
		
		for(int i=0;i<quantidade_movimentos;i++){						
			fscanf(arquivo," %c",&condicional);
			if(condicional == 'a'){
				fscanf(arquivo,"%d %d",&lin,&col);
				jogo->matrizCor[lin-1][col-1] = 1;					//colore a matriz com verde
			}
			else{
				fscanf(arquivo,"%d %d",&lin,&col);					//colore a matriz com vermelho
				jogo->matrizCor[lin-1][col-1] = 2;
			}
		}
		fscanf(arquivo,"%s",jogo->nome);							//pega o nome
		fscanf(arquivo,"%f",&jogo->tempoGasto);						//lê o tempo gasto
	}
	fclose(arquivo);
}

void salvar(JogoSumplete *jogo, char *fileName){
	int tam=0,quantidade_remover=0,quantidade_movimentos=0;
	tam = jogo->tamanho;
	quantidade_remover =(tam*tam) - jogo->quantidade_adicionar;
	strcat(fileName,".sum");
	
	for(int i=0;i<tam;i++)
		for(int j=0;j<tam;j++)
			if(jogo->matrizCor[i][j] == 1 || jogo->matrizCor[i][j] == 2)
				quantidade_movimentos +=1; 
	
	FILE *arquivo = fopen(fileName,"w"); // adicionar .sum
	if(arquivo == NULL){
		printf("Não foi encontrado o arquivo");
		return;
	}

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
	
	fprintf(arquivo,"%d\n",quantidade_movimentos);				//add quantidade de movimentos
	for(int i=0;i<tam;i++)
		for(int j=0;j<tam;j++)
			if(jogo->matrizCor[i][j] == 1)
				fprintf(arquivo,"a %d %d\n",i+1,j+1);			// adicionar + posicao
			else if(jogo->matrizCor[i][j] == 2)
				fprintf(arquivo,"r %d %d\n",i+1,j+1);			//remover + posicao
	
	fprintf(arquivo,"%s\n",jogo->nome);							//add nome
	fprintf(arquivo,"%.1f",jogo->tempoGasto);									//add tempo

	fclose(arquivo);
}

void printarJogo(JogoSumplete *jogo)
{
	int tam;
	tam = jogo->tamanho;
	int k =0;
			for(int i=0;i<tam;i++){	 						//print matriz + somaLinha
				printf("%d",i+1);
				for(int j=0;j<tam+1;j++){
					if(j<tam){
						if(jogo->matrizCor[i][j] ==0)
							printf(TAB_VER "%d ",jogo->matrizJogo[i][j]);
						else if(jogo->matrizCor[i][j] == 1)
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
				printf(TAB_HOR);
				for(int i=0;i<tam+1;i++)
					printf(TAB_MJ TAB_HOR TAB_HOR);
				printf("\n");
			}
			printf(" ");
			for(int i=0;i<tam;i++){
				if(jogo->somaColuna[i] <10)
					printf(TAB_VER "%d ",jogo->somaColuna[i]);		//printf soma coluna
				else
					printf(TAB_VER "%d",jogo->somaColuna[i]);
			}
			printf(TAB_VER);
			printf("\n\n");
}
 
 void sair(JogoSumplete *jogo)
{
	char SN,fileName[20];
	int teste = 0;
	do{
		teste = 0;
		printf("Você quer salvar o jogo antes de sair?(S/N): ");
		scanf(" %c",&SN); limpar_buffer();
		if((SN=='S') || (SN=='s')){
			printf("Digite o nome do arquivo para salvar: ");
			scanf("%s",fileName); limpar_buffer();
			salvar(jogo,fileName);
			printf("Jogo salvo!\n");
		}
		else if((SN=='N') || (SN=='n')){
			printf("Jogo não salvo\n");
		}
		else{
			printf("Insira uma resposta válida\n");
			teste = 1;
		}
	}while(teste != 0);
}

int ValidarMatriz(int linha, int coluna, int tamanhoMatriz) {
	int LinhaValida = linha <= tamanhoMatriz  && linha >= 1;
	int ColunaValida = coluna <= tamanhoMatriz && coluna >= 1;
	
	if(LinhaValida == 0) {
		printf("Erro: adicione uma linha válida \n"); // refinar condicao 
		return 0;
	}
	
	if(ColunaValida == 0){
		printf("Erro: adicione uma coluna válida \n"); // refinar condicao 
		return 0;
	}
	
	return 1;
}

int validarNome(char *str)
{
	char proibidos[] = "*<>:/\\?|";
	int tam = strlen(str);
	
	for(int i=0;i<tam;i++){
		for(int j=0;j<strlen(proibidos);j++)
			if(str[i] == proibidos[j])
				return 0;			//invalido
	}
	return 1;						//valido
}

void salvarRanking(JogoSumplete *jogo)
{
	char nomes[11][28] = {0};
	float temposRanking[11] = {0};
	int totalRegistros = 0;
	
	FILE *arquivo = fopen("sumplete.rnk","r");
	if(arquivo != NULL){
		while (totalRegistros < 10 && fscanf(arquivo,"%s %f", nomes[totalRegistros], &temposRanking[totalRegistros]) == 2)
		{
			totalRegistros++;
		}
		fclose(arquivo);
	}
	
	strcpy(nomes[totalRegistros],jogo->nome);
	temposRanking[totalRegistros] = jogo->tempoGasto;
	totalRegistros++;									//+1 para ordenar o vetor
	
	for (int i =0;i<totalRegistros - 1;i++) {
        for (int j =0;j< totalRegistros -i-1;j++) {
            if (temposRanking[j] > temposRanking[j + 1]) {
                // Troca tempo
                float tempT;
				tempT = temposRanking[j];
                temposRanking[j] = temposRanking[j + 1];
                temposRanking[j + 1] = tempT;
                // Troca nome
                char tempN[28];
                strcpy(tempN, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], tempN);
            }
        }
    }
	
	FILE *clear = fopen("sumplete.rnk","w");
	int limite;
	
	if(totalRegistros > 10)
		limite = 10;
	else
		limite = totalRegistros;
	
	if(clear != NULL)
	{
		for(int i =0;i<limite;i++)
			fprintf(clear,"%s %.f\n",nomes[i],temposRanking[i]);
		fclose(clear);
	}
}

void posicaoRanking()
{
	char nome[28];
	float temposRanking =0;
	
	FILE *arquivo = fopen("sumplete.rnk","r");
	if(arquivo == NULL)
		return;
	
	int i=1;
	while (fscanf(arquivo,"%s %f",nome,&temposRanking) == 2)
		printf("%dº- %s %.f\n",i++,nome,temposRanking);
	fclose(arquivo);
}


int main(){
	//tabela inicial
	char comando[15];
	char fileName[28];
	int num_comando=0,exit=0;
	struct timeval inicio, fim;
	JogoSumplete jogo;
	jogo.tempoGasto = 0;
	tabelaComandos();
	//comandos
	do{
		printf("Digite um comando: ");
		if(scanf("%14s",comando) !=1){
			limpar_buffer();
			continue;
		}
		if(strcmp(comando,"ajuda")==0){
			num_comando = 1;
			tabelaComandos();
		}
		else if(strcmp(comando,"sair")==0){
			num_comando = 0;
			exit = 1;
		}
		else if(strcmp(comando,"novo")==0){
			novo(&jogo);
			num_comando = 0;
			
		}
		else if(strcmp(comando,"carregar")==0){
			num_comando = 4;
			printf("Insira o nome do jogo salvo: ");
			scanf("%27s",fileName);					
			if (validarNome(fileName)){
				carregar(&jogo,fileName);
				num_comando =0;
			}
			else
				printf("Erro: nome do arquivo com caracteres inválidos!\n");
		}
		else if(strcmp(comando,"ranking")==0){
			posicaoRanking();
			num_comando = 1;
			exit =0;
		}
		else if(strcmp(comando,"salvar")==0){
			printf("crie um novo jogo antes de salvar\n");
			num_comando = 6;
		}
		else if(strcmp(comando,"dica")==0){
			printf("crie um novo jogo antes de uma dica\n");
			num_comando = 7;
		}
		else if(strcmp(comando,"resolver")==0){
			printf("crie um novo jogo antes de resolver\n");
			num_comando = 8;
		}
		else if(strcmp(comando,"adicionar")==0){
			printf("crie um novo jogo antes de adicionar\n");
			num_comando = 9;
		}
		else if(strcmp(comando,"remover")==0){
			printf("crie um novo jogo antes de remover\n");
			num_comando = 10;
		}
		else{
			printf("insira um comando válido!\n");
			num_comando = 11;
		}
	}while(num_comando !=0);
	
	
	if(exit!=0) {
		return 0;
	}
	
	gettimeofday(&inicio, 0);
	
	do
	{
		if(jogo.tamanho ==3){
			printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "\n"); //print primeira linha
			printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
		}
		if(jogo.tamanho ==5){
			printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "4 " TAB_VER "5 " TAB_VER "\n"); //print primeira linha
			printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR "\n");
		}
		if(jogo.tamanho ==7){
			printf(" "TAB_VER "1 " TAB_VER "2 " TAB_VER "3 " TAB_VER "4 " TAB_VER "5 " TAB_VER "6 " TAB_VER "7 " TAB_VER"\n"); //print primeira linha
			printf(TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR"\n");
		}
		printarJogo(&jogo);
		
		int linha,coluna;
		int vitoria = 0;
		int condicaoRanking =0;
		printf("%s, digite o comando: ",jogo.nome);
		
		scanf("%s",comando);
		
		if(strcmp(comando,"adicionar")==0){
			scanf("%d %d",&linha,&coluna);
			if(ValidarMatriz(linha, coluna, jogo.tamanho)){
				jogo.matrizCor[linha-1][coluna-1] = 1;		//printf verde
			}
			
		}
		else if(strcmp(comando,"remover")==0){
			scanf("%d %d",&linha,&coluna);
			if(ValidarMatriz(linha, coluna, jogo.tamanho)){
				jogo.matrizCor[linha-1][coluna-1] = 2;				//printf vermelho
			}
			
		}
		else if(strcmp(comando,"sair")==0){
			exit = 1;
			gettimeofday(&fim, 0);
			long sec = fim.tv_sec - inicio.tv_sec;
			long microsec = fim.tv_usec - inicio.tv_usec;
			double passado = sec + microsec*1e-6;
			jogo.tempoGasto = passado;
			sair(&jogo);
		}
		else if(strcmp(comando,"ajuda")==0)
			tabelaComandos();
		else if(strcmp(comando,"resolver")==0){
			vitoria = 1;
			condicaoRanking = 1;
		}
		else if(strcmp(comando,"dica")==0)
			dica(&jogo);
		else if(strcmp(comando,"salvar")==0){
			scanf("%s",fileName);
			gettimeofday(&fim, 0);
			long sec = fim.tv_sec - inicio.tv_sec;
			long microsec = fim.tv_usec - inicio.tv_usec;
			double passado = sec + microsec*1e-6;
			jogo.tempoGasto = passado;
			salvar(&jogo,fileName);
		}else{
			printf("insira um comando válido\n");
			limpar_buffer();
		}
		
		if(vitoria == 0)
			vitoria = verifica_Vitoria(&jogo);
		
		if(vitoria ==1){								// print vitoria
			gettimeofday(&fim, 0);
			long sec = fim.tv_sec - inicio.tv_sec;
			long microsec = fim.tv_usec - inicio.tv_usec;
			
			jogo.tempoGasto = (sec + microsec*1e-6);
			
			printf("\n" GREEN("Parabéns! Você ganhou!\n"));
			exit = 1;
			resolver(&jogo);
			if(condicaoRanking !=1){
				printf("Tempo de jogo: %.3f segundos.\n", jogo.tempoGasto);
				salvarRanking(&jogo);
				posicaoRanking();
			}
		}
		
	} while (exit==0);
	
	free(jogo.somaLinha);
	free(jogo.somaColuna);
	liberaMatriz(jogo.matrizJogo,jogo.tamanho);		
	liberaMatriz(jogo.matrizSolucao,jogo.tamanho);
	liberaMatriz(jogo.matrizCor,jogo.tamanho);
	return 0;
}