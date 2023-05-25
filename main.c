/*
    Programa: CADASTRO LETIVO
    Plataforma: Windows

    *O que h� de errado no Bubble Sort ou no print dos alunos? Simplesmente n�o aparecem.
    *Foquei bastante na TUI, fiz v�rias fun��es e procedimentos pra deix�-la bem atrativa. Mas por falta de tempo, n�o pude trabalhar nelas direito. Ent�o o senhor pode notar muita coisa que deixei de usar.

    ENTRADA: "Ser�o cadastrados 3 professores, 2 disciplinas e no m�ximo 15 estudantes distribu�dos entre as duas disciplinas, uma disciplina n�o poder� ter mais que 10 estudantes matriculados."
    PROCESSAMENTO: "Aplique o bubble sort para ordena��o utilizando um procedimento com passagem de par�metros por refer�ncia."
                   "Idade do estudante dever� estar validada entre 16 e 26 por meio de uma fun��o le_valida_idade."
    SA�DA: "Apresente um relat�rio dos alunos matriculados na primeira disciplina ordenados por idade."
           "Apresente um relat�rio dos alunos matriculados na segunda disciplina ordenados por idade em ordem decrescente."
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define NUM_PROF 3
#define NUM_DISC 2

struct Professor{
    char nome[50];
    char funcional[20];
    char titulacao[20]; //especialista, mestre ou doutor
};
struct Disciplina{
    char nome[50];
    char codigo[20];
    int carga_horaria;
    char professor_responsavel[50];
};
struct Aluno{
    char nome[50];
    char matricula[20];
    int idade;
    char disciplina[50];
};

void titulo();
int le_valida_num_alunos();
void menu_principal(struct Professor professores[], struct Disciplina disciplinas[]);
    void menu_principal_opcoes(int opcao); //mostrar op��es com a devida marca��o
void menu_relatorio(struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos);
void cadastro_professores(struct Professor professores[]);
void cadastro_disciplinas(struct Disciplina disciplinas[], struct Professor professores[]);
int cadastro_alunos(struct Aluno alunos[], struct Disciplina disciplinas[]);
    //seletor de disciplinas com o devido espa�amento
    int le_valida_idade(struct Aluno alunos[], int num_alunos, int i);
    void selecao_disciplinas_indentado(struct Disciplina disciplinas[], int opcao, int cont_disc_1, int cont_disc_2);
        void disciplina_lotada_indentado();
void relatorios();
    void relatorio_1(struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos);
    void relatorio_2(struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos); //ctrl c + ctrl v do 1�
        void bubble_sort_idade(struct Aluno alunos[], int num_alunos);

int main(){

    struct Aluno alunos[15];
    struct Professor professores[NUM_PROF];
    struct Disciplina disciplinas[NUM_DISC];
    int num_alunos = 0, i = 0;
    int tecla = 0, opcao = 0;

    strcpy(professores[0].nome, "Fulano de Tal");
    strcpy(professores[1].nome, "Beltranho de Tal");
    strcpy(professores[2].nome, "Ciclano de Tal");

    strcpy(disciplinas[0].nome, "Algoritmos");
    strcpy(disciplinas[1].nome, "Programa��o Estruturada");
    strcpy(disciplinas[0].codigo, "123");
    strcpy(disciplinas[1].codigo, "456");
    strcpy(disciplinas[0].professor_responsavel, professores[0].nome);
    strcpy(disciplinas[1].professor_responsavel, professores[1].nome);

    system("chcp 1252");
    
    //CADASTRO
    cadastro_professores(professores);
    cadastro_disciplinas(disciplinas, professores);
    num_alunos = cadastro_alunos(alunos, disciplinas); //usar num_alunos no relat�rio abaixo

    //RELAT�RIO
    titulo();
    printf("\n");
    printf("        RELAT�RIO");
    system("timeout /t 1 >nul");

    menu_relatorio(disciplinas, alunos, num_alunos);

    //disciplina selecionada
    switch (opcao) {
        case 1:
            titulo();
            printf("        RELAT�RIO");
            printf("\n\n");
            printf("        Matriculados em -> %s\n\n", disciplinas[0].nome);
            getch();

            //alunos na primeira disciplina
            relatorio_1(disciplinas, alunos, num_alunos);
        case 2:
            titulo();
            printf("        RELAT�RIO");
            printf("\n\n");
            printf("        Matriculados em -> %s\n\n", disciplinas[1].nome);
            getch();

            //alunos na segunda disciplina
            relatorio_2(disciplinas, alunos, num_alunos);            
    }

    return 0;
}





void titulo(){
    system("cls");
    printf("CADASTRO LETIVO\n\n");
}

int le_valida_num_alunos(){
    int num_alunos = 0;

    do{
        titulo();
        printf("\t3 professores,\n\t2 disciplinas,\n\tQuantos alunos? (M�X = 15) ");
        scanf("%d", &num_alunos);
        fflush(stdin);
        if(num_alunos < 1 || num_alunos > 15){
            printf("\n\t\t\t\tQUANTIDADE INV�LIDA! ");
            getch();
        }
    }while(num_alunos < 1 || num_alunos > 15);

    return num_alunos;
}

void menu_principal(struct Professor professores[], struct Disciplina disciplinas[]) {
    //C�digo Teclas: {UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77}, {ENTER = 13, ESC = 27}
    int tecla = 0, opcao = 0;

    do {
        if (opcao == 0) {
            opcao = 1;
        }
        switch (opcao) {
            case 1:
                do {
                    menu_principal_opcoes(opcao);

                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 80 && tecla != 13 && tecla != 27);
                
                if (tecla == 80) {
                    opcao = 2;
                } else if (tecla == 13) {
                    opcao = 0; //selecionar
                } else {
                    opcao = -1; //sair
                }
                break;
            case 2:
                do {
                    menu_principal_opcoes(opcao);
                
                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 80 && tecla != 72 && tecla != 13 && tecla != 27);

                if (tecla == 80) {
                    opcao = 3;
                } else if (tecla == 72){
                    opcao = 1;
                } else if (tecla == 13) {
                    opcao = 0;
                } else {
                    opcao = -1;
                }
                break;
            case 3:
                do {
                    menu_principal_opcoes(opcao);
                
                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 80 && tecla != 72 && tecla != 13 && tecla != 27);

                if (tecla == 80) {
                    opcao = 4;
                } else if (tecla == 72){
                    opcao = 2;
                } else if (tecla == 13) {
                    opcao = 0;
                } else {
                    opcao = -1;
                }
                break;
            case 4:
                do {
                    menu_principal_opcoes(opcao);
                
                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 72 && tecla != 13 && tecla != 27);

                if (tecla == 72) {
                    opcao = 3;
                } else if (tecla == 13) {
                    opcao = 0;
                } else {
                    opcao = -1;
                }
                break;
        }
    } while (opcao != 0 && opcao != -1);
}

void menu_principal_opcoes(int opcao) {
    switch (opcao) {
        case 1:
            titulo();
            printf("     -> CADASTRAR\n");
            printf("        RELAT�RIO\n");
            printf("        AJUDA\n");
            printf("        SAIR");
            break;
        case 2:
            titulo();
            printf("        CADASTRAR\n");
            printf("     -> RELAT�RIO\n");
            printf("        AJUDA\n");
            printf("        SAIR");
            break;
        case 3:
            titulo();
            printf("        CADASTRAR\n");
            printf("        RELAT�RIO\n");
            printf("     -> AJUDA\n");
            printf("        SAIR");
            break;
        case 4:
            titulo();
            printf("        CADASTRAR\n");
            printf("        RELAT�RIO\n");
            printf("        AJUDA\n");
            printf("     -> SAIR");
            break;
        default:
            break;            
    }
}

void menu_relatorio(struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos) {
    int opcao = 0, tecla = 0;

    do {
        if (opcao == 0){
            opcao = 1;
        }

        switch (opcao) {
            case 1:
                titulo();
                printf("        RELAT�RIO");
                printf("\n\n");
                printf("        Matriculados em -> %s\n", disciplinas[0].nome);
                printf("                           %s", disciplinas[1].nome);
                
                do {
                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 80 && tecla != 13);

                if (tecla == 80) {
                    opcao = 2;
                } else {
                    //MOSTRAR RELAT�RIO!
                    relatorio_1(disciplinas, alunos, num_alunos);
                    opcao = 0;
                }
                break;
            case 2:
                titulo();
                printf("        RELAT�RIO");
                printf("\n\n");
                printf("        Matriculados em    %s\n", disciplinas[0].nome);
                printf("                        -> %s", disciplinas[1].nome);
                
                do {
                    tecla = getch();
                    if (tecla == 0 || tecla == 224) {
                        tecla = getch();
                    }
                } while (tecla != 72 && tecla != 13);

                if (tecla == 72) {
                    opcao = 1;
                } else {
                    //MOSTRAR RELAT�RIO!
                    relatorio_2(disciplinas, alunos, num_alunos);
                    opcao = 0;
                }
                break;
            default:
                break;
        }
    } while (opcao != 0);
}

void cadastro_professores(struct Professor professores[]){
    int tecla = 0, opcao = 0, i = 0;

    titulo();
    printf("     -> CADASTRAR\n\n");
    printf("            3 professores\n");
    printf("            2 disciplinas\n");
    printf("            x   alunos\n\n");

    printf("            Pressione ENTER para come�ar");
    do {
        tecla = getch();
    } while (tecla != 13);
    
    for (i = 0; i < NUM_PROF; i++){
        titulo();
        printf("        CADASTRAR\n\n");
        printf("          � 3 professores\t[%d/3]\n", i + 1);
        printf("            2 disciplinas\n");
        printf("            x   alunos\n\n");
        
        printf("            Nome: ");
        scanf("%[^\n]s", &professores[i].nome);
        fflush(stdin);
        printf("       Funcional: ");
        scanf("%[^\n]s", &professores[i].funcional);
        fflush(stdin);

        do { //selecao da titula��o
            if (opcao == 0){
                opcao = 1;
            }
            switch (opcao){
                case 1:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("          � 3 professores\t[%d/3]\n", i + 1);
                    printf("            2 disciplinas\n");
                    printf("            x   alunos\n\n");
                    printf("            Nome: %s\n", professores[i].nome);
                    printf("       Funcional: %s\n", professores[i].funcional);

                    printf("       Titula��o -> Especialista\n");
                    //printf("                  Especialista <-\n");
                    printf("                    Mestre\n");
                    printf("                    Doutor");
            
                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 80 && tecla != 13);
                    if (tecla == 80) {
                        opcao = 2;
                    } else {
                        opcao = 0;
                        strcpy(professores[i].titulacao, "Especialista");
                    }
                    break;
                case 2:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("          � 3 professores\t[%d/3]\n", i + 1);
                    printf("            2 disciplinas\n");
                    printf("            x   alunos\n\n");
                    printf("            Nome: %s\n", professores[i].nome);
                    printf("       Funcional: %s\n", professores[i].funcional);

                    printf("       Titula��o    Especialista\n");
                    //printf("                  Especialista <-\n");
                    printf("                 -> Mestre\n");
                    printf("                    Doutor");
            
                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 72 && tecla != 80 && tecla != 13);
                    if (tecla == 72) {
                        opcao = 1;
                    } else if (tecla == 80){
                        opcao = 3;
                    } else {
                        opcao = 0;
                        strcpy(professores[i].titulacao, "Mestre");
                    }
                    break;
                case 3:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("          � 3 professores\t[%d/3]\n", i + 1);
                    printf("            2 disciplinas\n");
                    printf("            x   alunos\n\n");
                    printf("            Nome: %s\n", professores[i].nome);
                    printf("       Funcional: %s\n", professores[i].funcional);

                    printf("       Titula��o    Especialista\n");
                    //printf("                  Especialista <-\n");
                    printf("                    Mestre\n");
                    printf("                 -> Doutor");
            
                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 72 && tecla != 13);
                    if (tecla == 72) {
                        opcao = 2;
                    } else {
                        opcao = 0;
                        strcpy(professores[i].titulacao, "Doutor");
                    }
                    break;
                default:
                    break;                    
                }
        } while (opcao != 0);
    }
}

void cadastro_disciplinas(struct Disciplina disciplinas[], struct Professor professores[]){
    int tecla = 0, opcao = 0, i = 0;

    titulo();
    printf("        CADASTRAR\n\n");
    printf("            3 professores\t[OK]\n");
    printf("          � 2 disciplinas\n");
    printf("            x   alunos\n\n");
    
    printf("            ENTER para continuar");
    do {
        tecla = getch();
    } while (tecla != 13);

    for (i = 0; i < NUM_DISC; i++){
        titulo();
        printf("        CADASTRAR\n\n");
        printf("            3 professores\t[OK]\n");
        printf("          � 2 disciplinas\t[%d/%d]\n", i + 1, NUM_DISC);
        printf("            x   alunos\n\n");

        printf("                   Nome: ");
        scanf("%[^\n]s", &disciplinas[i].nome);
        fflush(stdin);
        printf("                 C�digo: ");
        scanf("%[^\n]s", &disciplinas[i].codigo);
        fflush(stdin);
        printf("      Carga Hor�ria (h): ");
        scanf("%d", &disciplinas[i].carga_horaria);
        fflush(stdin);

        do { //selecao do professor respons�vel pela disciplina
            if (opcao == 0){
                opcao = 1;
            }
            switch (opcao){
                case 1:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("            3 professores\t[OK]\n");
                    printf("          � 2 disciplinas\t[%d/%d]\n", i + 1, NUM_DISC);
                    printf("            x   alunos\n\n");

                    printf("                   Nome: %s\n", disciplinas[i].nome);
                    printf("                 C�digo: %s\n", disciplinas[i].codigo);
                    printf("          Carga Hor�ria: %d horas\n", disciplinas[i].carga_horaria);

                    printf("  Professor Respons�vel -> %s\n", professores[0].nome);
                    printf("                           %s\n", professores[1].nome);
                    printf("                           %s", professores[2].nome);

                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 80 && tecla != 13);
                    if (tecla == 80) {
                        opcao = 2;
                    } else {
                        opcao = 0;
                        strcpy(disciplinas[i].professor_responsavel, professores[0].nome);
                    }
                    break;
                case 2:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("            3 professores\t[OK]\n");
                    printf("          � 2 disciplinas\t[%d/%d]\n", i + 1, NUM_DISC);
                    printf("            x   alunos\n\n");

                    printf("                   Nome: %s\n", disciplinas[i].nome);
                    printf("                 C�digo: %s\n", disciplinas[i].codigo);
                    printf("          Carga Hor�ria: %d horas\n", disciplinas[i].carga_horaria);

                    printf("  Professor Respons�vel    %s\n", professores[0].nome);
                    printf("                        -> %s\n", professores[1].nome);
                    printf("                           %s", professores[2].nome);

                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 72 && tecla != 80 && tecla != 13);
                    if (tecla == 72) {
                        opcao = 1;
                    } else if (tecla == 80) {
                        opcao = 3;
                    } else {
                        opcao = 0;
                        strcpy(disciplinas[i].professor_responsavel, professores[1].nome);
                    }                           
                    break;
                case 3:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("            3 professores\t[OK]\n");
                    printf("          � 2 disciplinas\t[%d/%d]\n", i + 1, NUM_DISC);
                    printf("            x   alunos\n\n");

                    printf("                   Nome: %s\n", disciplinas[i].nome);
                    printf("                 C�digo: %s\n", disciplinas[i].codigo);
                    printf("          Carga Hor�ria: %d horas\n", disciplinas[i].carga_horaria);

                    printf("  Professor Respons�vel    %s\n", professores[0].nome);
                    printf("                           %s\n", professores[1].nome);
                    printf("                        -> %s", professores[2].nome);

                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 72 && tecla != 13);
                    if (tecla == 72) {
                        opcao = 2;
                    } else {
                        opcao = 0;
                        strcpy(disciplinas[i].professor_responsavel, professores[2].nome);
                    }
                    break;
                default:
                    break;                    
                }
        } while (opcao != 0);
    }
}

int cadastro_alunos(struct Aluno alunos[], struct Disciplina disciplinas[]){
    int num_alunos = 0, tecla = 0, opcao = 0, i = 0;
    int cont_disc_1 = 0, cont_disc_2 = 0; //validar alunos/disciplinas (M�X = 10)

    do
    {
        titulo();
        printf("        CADASTRAR\n\n");
        printf("            3 professores\t[OK]\n");
        printf("            2 disciplinas\t[OK]\n");
        printf("          � x   alunos\n\n");
        
        printf("            Quantos alunos? (M�X = 15) ");
        scanf("%d", &num_alunos);
        fflush(stdin);

        if (num_alunos < 1 || num_alunos > 15) {
            printf("\n\t\t\t    ERRO!!! Quantidade deve estar entre 1 e 15.");
            getch();
        }
        
    } while (num_alunos < 1 || num_alunos > 15);

    for (i = 0; i < num_alunos; i++){
        titulo();
        printf("        CADASTRAR\n\n");
        printf("            3 professores\t[OK]\n");
        printf("            2 disciplinas\t[OK]\n");
        printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

        printf("                   Nome: ");
        scanf("%[^\n]s", &alunos[i].nome);
        fflush(stdin);
        printf("              Matr�cula: ");
        scanf("%[^\n]s", &alunos[i].matricula);
        fflush(stdin);
        le_valida_idade(alunos, num_alunos, i);

        do { //sele��o da disciplina a ser matriculada
            if (opcao == 0){
                opcao = 1;
            }
            switch (opcao){
                case 1:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("            3 professores\t[OK]\n");
                    printf("            2 disciplinas\t[OK]\n");
                    printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

                    printf("                   Nome: %s\n", alunos[i].nome);
                    printf("              Matr�cula: %s\n", alunos[i].matricula);
                    printf("                  Idade: %d anos\n", alunos[i].idade);

                    selecao_disciplinas_indentado(disciplinas, opcao, cont_disc_1, cont_disc_2);
                    //printf("             Disciplina -> %s\n", disciplinas[0].nome);
                    //printf("                           %s", disciplinas[1].nome);

                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 80 && tecla != 13);
                    if (tecla == 80) {
                        opcao = 2;
                    } else {
                        if (cont_disc_1 < 10) {
                            opcao = 0;
                            strcpy(alunos[i].disciplina, disciplinas[0].nome);
                            cont_disc_1++;
                        } else {
                            titulo();
                            printf("        CADASTRAR\n\n");
                            printf("            3 professores\t[OK]\n");
                            printf("            2 disciplinas\t[OK]\n");
                            printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

                            printf("                   Nome: %s\n", alunos[i].nome);
                            printf("              Matr�cula: %s\n", alunos[i].matricula);
                            printf("                  Idade: %d anos\n", alunos[i].idade);

                            disciplina_lotada_indentado(disciplinas, opcao);
                            //printf("             Disciplina -> %s   [LOTADA!]", disciplinas[0].nome);
                            //getch();
                        }
                    }
                    break;
                case 2:
                    titulo();
                    printf("        CADASTRAR\n\n");
                    printf("            3 professores\t[OK]\n");
                    printf("            2 disciplinas\t[OK]\n");
                    printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

                    printf("                   Nome: %s\n", alunos[i].nome);
                    printf("              Matr�cula: %s\n", alunos[i].matricula);
                    printf("                  Idade: %d anos\n", alunos[i].idade);

                    selecao_disciplinas_indentado(disciplinas, opcao, cont_disc_1, cont_disc_2);
                    //printf("             Disciplina    %s\n", disciplinas[0].nome);
                    //printf("                        -> %s", disciplinas[1].nome);

                    do {
                        tecla = getch();
                        if (tecla == 0 || tecla == 224){
                            tecla = getch();
                        }
                    } while (tecla != 72 && tecla != 13);
                    if (tecla == 72) {
                        opcao = 1;
                    } else {
                        if (cont_disc_2 < 10) {
                            opcao = 0;
                            strcpy(alunos[i].disciplina, disciplinas[1].nome);
                            cont_disc_2++;
                        } else {
                            titulo();
                            printf("        CADASTRAR\n\n");
                            printf("            3 professores\t[OK]\n");
                            printf("            2 disciplinas\t[OK]\n");
                            printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

                            printf("                   Nome: %s\n", alunos[i].nome);
                            printf("              Matr�cula: %s\n", alunos[i].matricula);
                            printf("                  Idade: %d anos\n", alunos[i].idade);

                            disciplina_lotada_indentado(disciplinas, opcao);
                            //printf("             Disciplina      \n", disciplinas[0].nome);
                            //printf("                        -> %s   [LOTADA!]", disciplinas[1].nome);
                        }
                    }
                    break;
                default:
                    break;
                }
        } while (opcao != 0);
    }

    return num_alunos;
}

int le_valida_idade(struct Aluno alunos[], int num_alunos, int i){
    do
    {
        titulo();
        printf("        CADASTRAR\n\n");
        printf("            3 professores\t[OK]\n");
        printf("            2 disciplinas\t[OK]\n");
        printf("          � %d   alunos\t\t[%d/%d]\n\n", num_alunos, i + 1, num_alunos);

        printf("                   Nome: %s\n", alunos[i].nome);
        printf("              Matr�cula: %s\n", alunos[i].matricula);

        printf("        Idade (16 a 26): ");
        scanf("%d", &alunos[i].idade);
        fflush(stdin);

        if (alunos[i].idade < 16 || alunos[i].idade > 26) {
            printf("\n\t\t\tERRO!!! Aluno deve ter entre 16 e 26 anos.");
            getch();
        }
    } while (alunos[i].idade < 16 || alunos[i].idade > 26);
}

void selecao_disciplinas_indentado(struct Disciplina disciplinas[], int opcao, int cont_disc_1, int cont_disc_2) {
    int diferenca_tamanho = strlen(disciplinas[0].nome) - strlen(disciplinas[1].nome);
    int i = 0;

    if (opcao == 1) {
        if (diferenca_tamanho > 0) {
            printf("             Disciplina -> %s   [%d/10]\n", disciplinas[0].nome, cont_disc_1);
            printf("                           %s   ", disciplinas[1].nome);
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[%d/10]", cont_disc_2);
        } else if (diferenca_tamanho < 0){
            printf("             Disciplina -> %s   ", disciplinas[0].nome, cont_disc_1);
            diferenca_tamanho *= -1;
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[%d/10]\n", cont_disc_1);
            printf("                           %s   [%d/10]", disciplinas[1].nome, cont_disc_2);
        } else {
            printf("             Disciplina -> %s   [%d/10]\n", disciplinas[0].nome, cont_disc_1);
            printf("                           %s   [%d/10]", disciplinas[1].nome, cont_disc_2);
        }
    } else {
        if (diferenca_tamanho > 0) {
            printf("             Disciplina    %s   [%d/10]\n", disciplinas[0].nome, cont_disc_1);
            printf("                        -> %s   ", disciplinas[1].nome);
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[%d/10]", cont_disc_2);
        } else if (diferenca_tamanho < 0){
            printf("             Disciplina    %s   ", disciplinas[0].nome, cont_disc_1);
            diferenca_tamanho *= -1;
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[%d/10]\n", cont_disc_1);
            printf("                        -> %s   [%d/10]", disciplinas[1].nome, cont_disc_2);
        } else {
            printf("             Disciplina    %s   [%d/10]\n", disciplinas[0].nome, cont_disc_1);
            printf("                        -> %s   [%d/10]", disciplinas[1].nome, cont_disc_2);
        }        
    }
}

void disciplina_lotada_indentado(struct Disciplina disciplinas[], int opcao) {
    int diferenca_tamanho = strlen(disciplinas[0].nome) - strlen(disciplinas[1].nome);
    int i = 0;

    if (opcao == 1) {
        if (diferenca_tamanho > 0) {
            printf("             Disciplina -> %s   [LOTADA!]", disciplinas[0].nome);
        } else if (diferenca_tamanho < 0){
            printf("             Disciplina -> %s   ", disciplinas[0].nome);
            diferenca_tamanho *= -1;
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[LOTADA!]");
        } else {
            printf("             Disciplina -> %s   [LOTADA!]", disciplinas[0].nome);
        }
    } else {
        if (diferenca_tamanho > 0) {
            printf("             Disciplina    \n");
            printf("                        -> %s   ", disciplinas[1].nome);
            for (i = 0; i < diferenca_tamanho; i++){
                printf(" ");
            }
            printf("[LOTADA!]");
        } else if (diferenca_tamanho < 0){
            printf("             Disciplina    ");
            printf("                        -> %s   [LOTADA!]", disciplinas[1].nome);
        } else {
            printf("             Disciplina    \n");
            printf("                        -> %s   [LOTADA!]", disciplinas[1].nome);
        }        
    }
    getch();
}

void relatorio_1 (struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos) {
    int tam_maior_nome_aluno = 0, quant_tracos = 23; //tamanho do maior nome de um aluno para adicionar � "quant_tracos". FORMATA��O!
    int i = 0, j = 0;
    int tecla = 0;

    //organizar vetor struct alunos[] por idade, ordem CRESCEENTE
    bubble_sort_idade(alunos, num_alunos);

    //atribui��o do tamanho do maior nome de aluno, que est� matriculado nesta disciplina
    for (i = 0; i < num_alunos; i++){
        if (strlen(alunos[i].nome) > tam_maior_nome_aluno){
            //POR ALGUMA RAZ�O a compara��o "alunos[i].disciplina == disciplinas[0].nome" N�O DEU CERTO, MESMO SENDO IGUAIS, ENT�O IMPROVISEI AQUI!
            if ((strlen(alunos[i].disciplina) == strlen(disciplinas[0].nome)) && alunos[i].disciplina[7] == disciplinas[0].nome[7]) {
                tam_maior_nome_aluno = strlen(alunos[i].nome);
            }
        }
    }

    quant_tracos += tam_maior_nome_aluno; //quantidade de tra�os

    do {
        titulo();
        printf("        RELAT�RIO");
        printf("\n\n");
        printf("        Matriculados em -> %s\n\n", disciplinas[0].nome);

        printf("        ");
        for (i = 0; i < quant_tracos; i++){
            printf("-");
        }
        printf("\n");

        printf("        Disciplina de %s\n\n", disciplinas[0].nome);
        printf("            C�digo: %s\n", disciplinas[0].codigo);
        printf("            Professor: %s\n\n", disciplinas[0].professor_responsavel);
        printf("            Alunos\n");

        //mostrar alunos lindamente FORMATADOS
        for (i = 0; i < num_alunos; i++) {
            //POR ALGUMA RAZ�O a compara��o "alunos[i].disciplina == disciplinas[0].nome" N�O DEU CERTO, MESMO SENDO IGUAIS, ENT�O IMPROVISEI AQUI!        
            if ((strlen(alunos[i].disciplina) == strlen(disciplinas[0].nome)) && alunos[i].disciplina[7] == disciplinas[0].nome[7]) {
                printf("                ");
                printf("%s", alunos[i].nome);
                for (j = 0; j < tam_maior_nome_aluno - strlen(alunos[i].nome); j++) {
                    printf(" ");
                }
                printf("        ");
                printf("%d anos\n", alunos[i].idade);
            }
        }

        printf("\n");
        printf("        Fechar [Esc]");

        tecla = getch();
    } while (tecla != 27);
}

void relatorio_2(struct Disciplina disciplinas[], struct Aluno alunos[], int num_alunos) {
    int tam_maior_nome_aluno = 0, quant_tracos = 23; //tamanho do maior nome de um aluno para adicionar � "quant_tracos". FORMATA��O!
    int i = 0, j = 0;
    int tecla = 0;

    //organizar vetor struct alunos[] por idade, ordem CRESCEENTE
    bubble_sort_idade(alunos, num_alunos);

    //atribui��o do tamanho do maior nome de aluno, que est� matriculado nesta disciplina
    for (i = 0; i < num_alunos; i++){
        if (strlen(alunos[i].nome) > tam_maior_nome_aluno){
            //POR ALGUMA RAZ�O a compara��o "alunos[i].disciplina == disciplinas[0].nome" N�O DEU CERTO, MESMO SENDO IGUAIS, ENT�O IMPROVISEI AQUI!
            if ((strlen(alunos[i].disciplina) == strlen(disciplinas[1].nome)) && alunos[i].disciplina[7] == disciplinas[1].nome[7]) {
                tam_maior_nome_aluno = strlen(alunos[i].nome);
            }
        }
    }

    quant_tracos += tam_maior_nome_aluno; //quantidade de tra�os

    do {
        titulo();
        printf("        RELAT�RIO");
        printf("\n\n");
        printf("        Matriculados em -> %s\n\n", disciplinas[1].nome);

        printf("        ");
        for (i = 0; i < quant_tracos; i++){
            printf("-");
        }
        printf("\n");

        printf("        Disciplina de %s\n\n", disciplinas[1].nome);
        printf("            C�digo: %s\n", disciplinas[1].codigo);
        printf("            Professor: %s\n\n", disciplinas[1].professor_responsavel);
        printf("            Alunos\n");

        //mostrar alunos lindamente FORMATADOS
        for (i = num_alunos - 1; i >= 0; i--) {
            //POR ALGUMA RAZ�O a compara��o "alunos[i].disciplina == disciplinas[0].nome" N�O DEU CERTO, MESMO SENDO IGUAIS, ENT�O IMPROVISEI AQUI!        
            if ((strlen(alunos[i].disciplina) == strlen(disciplinas[1].nome)) && alunos[i].disciplina[7] == disciplinas[1].nome[7]) {
                printf("                ");
                printf("%s", alunos[i].nome);
                for (j = 0; j < tam_maior_nome_aluno - strlen(alunos[i].nome); j++) {
                    printf(" ");
                }
                printf("        ");
                printf("%d anos\n", alunos[i].idade);
            }
        }

        printf("\n");
        printf("        Fechar [Esc]");

        tecla = getch();
    } while (tecla != 27);    
}

void bubble_sort_idade(struct Aluno alunos[], int num_alunos) {
    int i = 0, j = 0;
    struct Aluno aux_aluno;

    //ordenando por idade vetor de alunos
    for (j = 0; j < num_alunos; j++){
        for (i = 0; i < num_alunos; i++) {
            if (alunos[i].idade > alunos[i+1].idade) {
                //aux_aluno = alunos[i+1]
                strcpy(aux_aluno.nome, alunos[i+1].nome);
                strcpy(aux_aluno.matricula, alunos[i+1].matricula);
                aux_aluno.idade = alunos[i+1].idade;
                strcpy(aux_aluno.disciplina, alunos[i+1].disciplina);
                
                //alunos[i+1] = alunos[i]
                strcpy(alunos[i+1].nome, alunos[i].nome);
                strcpy(alunos[i+1].matricula, alunos[i].matricula);
                alunos[i+1].idade = alunos[i].idade;
                strcpy(alunos[i+1].disciplina, alunos[i].disciplina);
                
                //alunos[i] = aux_aluno
                strcpy(alunos[i].nome, aux_aluno.nome);
                strcpy(alunos[i].matricula, aux_aluno.matricula);
                alunos[i].idade = aux_aluno.idade;
                strcpy(alunos[i].disciplina, aux_aluno.disciplina);
            }
        }
    }
}