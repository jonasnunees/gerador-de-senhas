#include <stdio.h>      // Biblioteca padrão de entrada e saída (printf, scanf)
#include <stdlib.h>     // Biblioteca para funções como rand() e system()
#include <time.h>       // Biblioteca para trabalhar com tempo (seed aleatória e data/hora)
#include <string.h>     // Biblioteca para manipular strings (strcat, strlen)
#include <locale.h>     // Biblioteca para configurar a linguagem e acentuação

// Esta é a chave usada para "embaralhar" (criptografar) os caracteres da senha.
// O valor está em hexadecimal, uma forma comum de representar números em programação.
#define CHAVE_XOR 0x7B

// Função para criptografar as senhas
void criptografarSenha(char *senha) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] ^= CHAVE_XOR;
    }
}

// Função para descriptografar as senhas
void descriptografarSenha(char *senha) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] ^= CHAVE_XOR;
    }
}

// Função que embaralha os caracteres da senha
void embaralhar(char *senha, int comprimento) {
    for (int i = comprimento - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = senha[i];
        senha[i] = senha[j];
        senha[j] = temp;
    }
}

// Função para gerar a senha com base nas escolhas do usuário
void gerarSenha(int comprimento, int incluirMaiusculas, int incluirMinusculas, int incluirNumeros, int incluirEspeciais) {
    const char caracteresMaiusculos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char caracteresMinusculos[] = "abcdefghijklmnopqrstuvwxyz";
    const char caracteresNumeros[] = "0123456789";
    const char caracteresEspeciais[] = "!@#$%^&*()";

    char caracteresPermitidos[100] = "";
    char senha[100] = "";
    int indice = 0;

    srand(time(0));  // Semente aleatória baseada no tempo atual

    // Garante pelo menos um caractere de cada tipo escolhido
    if (incluirMaiusculas) {
        senha[indice++] = caracteresMaiusculos[rand() % strlen(caracteresMaiusculos)];
        strcat(caracteresPermitidos, caracteresMaiusculos);
    }
    if (incluirMinusculas) {
        senha[indice++] = caracteresMinusculos[rand() % strlen(caracteresMinusculos)];
        strcat(caracteresPermitidos, caracteresMinusculos);
    }
    if (incluirNumeros) {
        senha[indice++] = caracteresNumeros[rand() % strlen(caracteresNumeros)];
        strcat(caracteresPermitidos, caracteresNumeros);
    }
    if (incluirEspeciais) {
        senha[indice++] = caracteresEspeciais[rand() % strlen(caracteresEspeciais)];
        strcat(caracteresPermitidos, caracteresEspeciais);
    }

    // Preenche o resto da senha
    for (; indice < comprimento; indice++) {
        senha[indice] = caracteresPermitidos[rand() % strlen(caracteresPermitidos)];
    }

    senha[comprimento] = '\0';  // Finaliza a string
    embaralhar(senha, comprimento);  // Embaralha a senha

    // Exibe a senha
    printf("Senha gerada: %s\n", senha);

    // Salva a senha em um arquivo com nome do serviço e data/hora
    char nomeServico[50];
    printf("Digite o nome do serviço para associar à senha: ");
    scanf(" %[^\n]", nomeServico);  // Lê até o Enter (inclui espaços)

    // Criptografa a senha
    criptografarSenha(senha);

    FILE *arquivo = fopen("senhas.txt", "a");  // Abre arquivo no modo de adicionar

    // Adiciona data e hora
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char dataHora[30];
    strftime(dataHora, 30, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(arquivo, "[%s] Serviço: %s | Senha: %s\n", dataHora, nomeServico, senha);
    fclose(arquivo);

    printf("Senha salva com sucesso!\n\n");
}

// Função para exibir todas as senhas salvas
void listarSenhas() {
    FILE *arquivo = fopen("senhas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhuma senha salva ainda.\n");
        return;
    }

    char linha[200];

    printf("=== Senhas Salvas (descriptografadas) ===\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Encontrar a posição da senha na linha
        char *ptrSenha = strstr(linha, "Senha: ");
        if (ptrSenha != NULL) {
            ptrSenha += 7;  // Pular o texto "Senha: "

            // Copiar a senha criptografada para uma nova string
            char senhaCripto[100];
            int i = 0;
            // Copia até o fim da linha ou até \n
            while (ptrSenha[i] != '\0' && ptrSenha[i] != '\n' && i < 99) {
                senhaCripto[i] = ptrSenha[i];
                i++;
            }
            senhaCripto[i] = '\0';  // Termina a string

            // Descriptografa a senha
            descriptografarSenha(senhaCripto);

            // Agora imprime a linha original até "Senha: " + a senha descriptografada
            // Para manter o serviço na impressão, vamos copiar até "Senha: "
            char linhaServico[200];
            strncpy(linhaServico, linha, ptrSenha - linha);
            linhaServico[ptrSenha - linha] = '\0';

            printf("%s%s\n", linhaServico, senhaCripto);
        } else {
            // Caso a linha não tenha senha, imprime normal
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

int main() {
    // Configura o idioma (corrige acentuação no Windows)
    setlocale(LC_ALL, "");

    int opcao;

    do {
        // Exibe o menu para o usuário
        printf("\n======= MENU =======\n");
        printf("[1] Gerar nova senha\n");
        printf("[2] Listar senhas salvas\n");
        printf("[3] Excluir todas as senhas\n");
        printf("[4] Sair\n");
        printf("====================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais;

            // Laço que obriga o usuário a digitar um número maior ou igual a 12
            // Se ele digitar um número menor, mostra uma mensagem de erro e pergunta de novo
            do {
                printf("Digite o comprimento da senha (mínimo 12): ");
                scanf("%d", &comprimento);

                if (comprimento < 12) {
                    printf("Comprimento muito curto. Tente novamente.\n");
                }
            } while (comprimento < 12);

            // Pergunta quais tipos de caracteres incluir
            printf("Incluir letras maiúsculas? (1-Sim / 0-Não): ");
            scanf("%d", &incluirMaiusculas);
            printf("Incluir letras minúsculas? (1-Sim / 0-Não): ");
            scanf("%d", &incluirMinusculas);
            printf("Incluir números? (1-Sim / 0-Não): ");
            scanf("%d", &incluirNumeros);
            printf("Incluir caracteres especiais? (1-Sim / 0-Não): ");
            scanf("%d", &incluirEspeciais);

            // Verifica se o usuário escolheu ao menos um tipo de caractere
            int totalTipos = incluirMaiusculas + incluirMinusculas + incluirNumeros + incluirEspeciais;

            // Verifica se o número de tipos cabe no comprimento da senha
            if (comprimento < totalTipos) {
                printf("Erro: A senha deve ter ao menos %d caracteres.\n", totalTipos);
            } else if (totalTipos == 0) {
                printf("Erro: Você deve escolher pelo menos um tipo de caractere.\n");
            } else {
                gerarSenha(comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais);
            }

        } else if (opcao == 2) {
            listarSenhas();
        } else if (opcao == 3) {
            excluirSenhas();
        } else if (opcao == 4) {
            printf("Saindo do programa. Até logo!\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}
