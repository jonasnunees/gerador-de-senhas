#include <stdio.h> // Biblioteca padrão de entrada e saída (printf, scanf)
#include <stdlib.h> // Biblioteca para funções como rand() e system()
#include <string.h> // Biblioteca para manipular strings (strcat, strlen)
#include <time.h> // Biblioteca para trabalhar com tempo (seed aleatória e data/hora)
#include <ctype.h> // Biblioteca padrão da linguagem C que fornece funções para testar e manipular caracteres.

// Nome do arquivo onde as senhas serão salvas
#define ARQUIVO_SENHAS "senhas.txt"

// Chave usada para criptografia XOR
#define CHAVE_XOR 0xAA

// Função para criptografar a senha usando XOR
void criptografarSenha(char *senha) {
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] ^= CHAVE_XOR;
    }
}

// Função para descriptografar a senha (mesma operação da criptografia)
void descriptografarSenha(char *senha) {
    criptografarSenha(senha); // XOR reversível
}

// Função que gera uma senha aleatória com base nas opções selecionadas
char *gerarSenha(int tamanho, int usarMaiusculas, int usarMinusculas, int usarNumeros, int usarSimbolos) {
    static char senha[100]; // senha gerada será armazenada aqui
    char caracteres[100] = ""; // string que vai conter todos os caracteres possíveis

    // Adiciona grupos de caracteres conforme as opções selecionadas
    if (usarMaiusculas) strcat(caracteres, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (usarMinusculas) strcat(caracteres, "abcdefghijklmnopqrstuvwxyz");
    if (usarNumeros)    strcat(caracteres, "0123456789");
    if (usarSimbolos)   strcat(caracteres, "!@#$%&*()-_=+[]{};:,.<>/?");

    // Verifica se ao menos um tipo de caractere foi selecionado
    if (strlen(caracteres) == 0) {
        printf("\nErro: Nenhum tipo de caractere foi selecionado para a senha.\n");
        return NULL;
    }

    // Gera cada caractere da senha escolhendo aleatoriamente da string de caracteres disponíveis
    for (int i = 0; i < tamanho; i++) {
        senha[i] = caracteres[rand() % strlen(caracteres)];
    }
    senha[tamanho] = '\0'; // finaliza a string com caractere nulo
    return senha; // retorna o ponteiro para a senha gerada
}

// Função que salva a senha no arquivo com o serviço, usuário e data/hora da criação
void salvarSenha(const char *servico, const char *usuario, const char *senha) {
    FILE *arquivo = fopen(ARQUIVO_SENHAS, "a"); // abre arquivo para acrescentar dados
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Obter data e hora atual para registrar quando a senha foi criada
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char dataHora[30];
    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tm_info);

     // Escreve no arquivo a linha formatada com serviço, usuário, senha (criptografada) e data/hora
    fprintf(arquivo, "Servico: %s | Usuario: %s | Senha: %s | Criada em: %s\n", servico, usuario, senha, dataHora);
    fclose(arquivo); // fecha o arquivo para garantir que dados foram salvos
}

// Função para listar todas as senhas salvas no arquivo, exibindo as senhas descriptografadas
void listarSenhas() {
    FILE *arquivo = fopen(ARQUIVO_SENHAS, "r"); // abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("Nenhuma senha salva ainda.\n");
        return;
    }

    char linha[200];
    printf("\n=== Senhas Salvas (descriptografadas) ===\n\n");

    // Lê o arquivo linha a linha até o fim
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Procura a substring "Senha: " na linha para encontrar a senha criptografada
        char *ptrSenha = strstr(linha, "Senha: ");
        if (ptrSenha != NULL) {
            ptrSenha += 7; // pula a palavra "Senha: " para pegar só a senha
            char senhaCripto[100];
            int i = 0;
            // Copia a senha criptografada para uma variável separada
            while (ptrSenha[i] != '\0' && ptrSenha[i] != '\n' && i < 99) {
                senhaCripto[i] = ptrSenha[i];
                i++;
            }
            senhaCripto[i] = '\0';

            // Descriptografa a senha para mostrar ao usuário
            descriptografarSenha(senhaCripto);

            // Copia a parte da linha antes da senha para manter o restante da informação
            char linhaServico[200];
            strncpy(linhaServico, linha, ptrSenha - linha);
            linhaServico[ptrSenha - linha] = '\0';

            // Exibe a linha com a senha descriptografada
            printf("%s%s\n", linhaServico, senhaCripto);
        } else {
            // Caso a linha não tenha senha (ex: linha em branco), imprime direto
            printf("%s", linha);
        }
    }

    fclose(arquivo);
    printf("======================\n\n");
}

// Função para apagar todas as senhas salvas
void excluirSenhas() {
    FILE *arquivo = fopen("senhas.txt", "w");  // Abre no modo de escrita (apaga tudo)
    if (arquivo != NULL) {
        fclose(arquivo);
        printf("Todas as senhas foram apagadas!\n\n");
    }
}

// Função que apresenta o menu interativo para o usuário usar o programa de forma amigável
void menuInterativo() {
    int opcao;
    do {
        printf("\n=== Gerador de Senhas ===\n\n");
        printf("1. Gerar nova senha\n");
        printf("2. Listar senhas salvas\n");
        printf("3. Excluir todas as senhas\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        if (opcao == 1) {
            char servico[50], usuario[50];
            int tamanho;
            int usarMaiusculas = 0, usarMinusculas = 0, usarNumeros = 0, usarSimbolos = 0;

            printf("\nNome do servico: ");
            fgets(servico, sizeof(servico), stdin);
            servico[strcspn(servico, "\n")] = '\0';

            printf("Nome do usuario: ");
            fgets(usuario, sizeof(usuario), stdin);
            usuario[strcspn(usuario, "\n")] = '\0';

            printf("Tamanho da senha: ");
            scanf("%d", &tamanho);
            getchar();

            char resposta;
            printf("\nIncluir letras maiusculas? (s/n): "); scanf("%c", &resposta); getchar(); usarMaiusculas = (resposta == 's');
            printf("Incluir letras minusculas? (s/n): "); scanf("%c", &resposta); getchar(); usarMinusculas = (resposta == 's');
            printf("Incluir numeros? (s/n): "); scanf("%c", &resposta); getchar(); usarNumeros = (resposta == 's');
            printf("Incluir simbolos? (s/n): "); scanf("%c", &resposta); getchar(); usarSimbolos = (resposta == 's');

            // Gera a senha com as opções selecionadas
            char *senha = gerarSenha(tamanho, usarMaiusculas, usarMinusculas, usarNumeros, usarSimbolos);
            if (senha) {
                printf("\nSenha gerada: %s\n", senha);
                criptografarSenha(senha);
                salvarSenha(servico, usuario, senha);
                descriptografarSenha(senha);
            }

        } else if (opcao == 2) {
            listarSenhas();
        } else if (opcao == 3) {
            excluirSenhas();
        }

    } while (opcao != 0);
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // inicializa o gerador de números aleatórios com base no tempo atual

    // Verifica se o programa foi executado sem argumentos (apenas o nome do programa)
    if (argc == 1) {
        menuInterativo(); // Executa o menu interativo para o usuário escolher opções manualmente
    } else {
        // Se o usuário pedir ajuda, exibe a explicação dos parâmetros
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                printf("\nModo de uso:\n");
                printf("  ./geradorSenha [opções]\n\n");
                printf("Opções disponíveis:\n");
                printf("  -l [tamanho]       Define o tamanho da senha\n");
                printf("  -M                 Incluir letras MAIÚSCULAS\n");
                printf("  -m                 Incluir letras minúsculas\n");
                printf("  -n                 Incluir números\n");
                printf("  -s                 Incluir símbolos\n");
                printf("  -S [serviço]       Nome do serviço (ex: Gmail)\n");
                printf("  -U [usuário]       Nome do usuário ou e-mail\n");
                printf("  --help             Exibe esta mensagem de ajuda\n\n");
                printf("Exemplo:\n");
                printf("  ./geradorSenha -l 12 -M -m -n -s -S Gmail -U usuario@email.com\n\n");
                return 0;
            }
        }
        // Variáveis para armazenar configurações passadas por linha de comando
        int tamanho = 0;
        int usarMaiusculas = 0, usarMinusculas = 0, usarNumeros = 0, usarSimbolos = 0;

        // strings para armazenar serviço e usuário
        char servico[50] = "", usuario[50] = "";

        // Loop para ler os argumentos passados na linha de comando
        for (int i = 1; i < argc; i++) {
            // Verifica cada argumento e atualiza as variáveis conforme o parâmetro reconhecido
            if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
                tamanho = atoi(argv[++i]);
            } else if (strcmp(argv[i], "-M") == 0) {
                usarMaiusculas = 1;
            } else if (strcmp(argv[i], "-m") == 0) {
                usarMinusculas = 1;
            } else if (strcmp(argv[i], "-n") == 0) {
                usarNumeros = 1;
            } else if (strcmp(argv[i], "-s") == 0) {
                usarSimbolos = 1;
            } else if (strcmp(argv[i], "-S") == 0 && i + 1 < argc) {
                strncpy(servico, argv[++i], sizeof(servico));
            } else if (strcmp(argv[i], "-U") == 0 && i + 1 < argc) {
                strncpy(usuario, argv[++i], sizeof(usuario));
            }
        }

        // Verifica se os parâmetros obrigatórios foram informados: tamanho, serviço e usuário
        if (tamanho > 0 && strlen(servico) > 0 && strlen(usuario) > 0) {
            // Gera a senha com as opções indicadas
            char *senha = gerarSenha(tamanho, usarMaiusculas, usarMinusculas, usarNumeros, usarSimbolos);
            if (senha) {
                printf("Senha gerada: %s\n", senha);
                criptografarSenha(senha);
                salvarSenha(servico, usuario, senha);
            }
        } else {
            // Caso falte algum parâmetro obrigatório, exibe mensagem de ajuda para o usuário
            printf("\nParametros insuficientes.\nExemplo: ./geradorSenha -l 12 -M -m -n -s -S Gmail -U usuario@email.com\n\n");
            printf("Use --help para ver as opções disponíveis.\n\n");
        }
    }

    return 0;
}
