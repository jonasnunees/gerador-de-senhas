#include <stdio.h>   // Biblioteca padrão para entrada e saída (como printf, scanf e FILE)
#include <stdlib.h>  // Biblioteca para funções como rand() e srand()
#include <time.h>    // Biblioteca usada para trabalhar com tempo e data
#include <string.h>  // Biblioteca para manipular strings (como strlen, strcat, fgets)
#include <locale.h> // Biblioteca usada para configurar o idioma e a formatação regional, como acentuação e símbolos do idioma português

// Função que embaralha os caracteres da senha para deixá-la mais aleatória
void embaralhar(char *senha, int comprimento) {
    for (int i = comprimento - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Gera um índice aleatório entre 0 e i
        // Troca os caracteres de posição (técnica conhecida como Fisher–Yates shuffle)
        char temp = senha[i];
        senha[i] = senha[j];
        senha[j] = temp;
    }
}

// Função que salva a senha gerada em um arquivo de texto, junto com o nome do serviço e data/hora
void salvarSenha(const char *senha, const char *servico) {
    FILE *arquivo = fopen("senhas.txt", "a"); // Abre o arquivo em modo de adição (append)
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar a senha.\n");
        return;
    }

    // Obtém a data e hora atual formatada
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char dataHora[26];
    strftime(dataHora, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // Escreve os dados no arquivo
    fprintf(arquivo, "[%s] Serviço: %s | Senha: %s\n", dataHora, servico, senha);
    fclose(arquivo); // Fecha o arquivo
}

// Função principal que gera a senha com base nas opções escolhidas
void gerarSenha(int comprimento, int incluirMaiusculas, int incluirMinusculas, int incluirNumeros, int incluirEspeciais) {
    // Conjuntos de caracteres disponíveis
    const char caracteresMaiusculos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char caracteresMinusculos[] = "abcdefghijklmnopqrstuvwxyz";
    const char caracteresNumeros[] = "0123456789";
    const char caracteresEspeciais[] = "!@#$%^&*()";

    char caracteresPermitidos[100] = ""; // Todos os caracteres válidos combinados
    char senha[100] = ""; // Senha final gerada
    int indice = 0; // Posição atual na senha

    srand(time(0)); // Inicializa o gerador de números aleatórios com o tempo atual

    // Garante ao menos 1 caractere de cada tipo escolhido
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

    // Preenche o restante da senha com caracteres aleatórios do conjunto permitido
    for (; indice < comprimento; indice++) {
        senha[indice] = caracteresPermitidos[rand() % strlen(caracteresPermitidos)];
    }

    // Embaralha os caracteres para aumentar a aleatoriedade
    embaralhar(senha, comprimento);

    // Finaliza a string com o caractere nulo '\0'
    senha[comprimento] = '\0';

    // Exibe a senha na tela
    printf("Senha gerada: %s\n", senha);

    // Pergunta ao usuário para qual serviço essa senha será usada
    char servico[100];
    printf("Digite o nome do serviço (ex: Gmail, Netflix, etc.): ");
    getchar(); // Limpa o '\n' deixado pelo último scanf
    fgets(servico, sizeof(servico), stdin);

    // Remove o caractere '\n' do final, se presente
    size_t len = strlen(servico);
    if (len > 0 && servico[len - 1] == '\n') {
        servico[len - 1] = '\0';
    }

    // Salva a senha no arquivo
    salvarSenha(senha, servico);
    printf("Senha salva com sucesso no arquivo 'senhas.txt'.\n");
}

// Função principal (ponto de entrada do programa)
int main() {

    system("chcp 65001 > nul");         // Muda a página de código para UTF-8
    setlocale(LC_ALL, "Portuguese");    // Configura para o idioma português

    // Variáveis que armazenam as opções do usuário
    int comprimento;
    int incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais;

    // Mensagem inicial
    printf("🔐 Bem-vindo ao Gerador de Senhas Seguras!\n");

    // Pergunta o comprimento da senha
    printf("Digite o comprimento da senha (mínimo 12): ");
    scanf("%d", &comprimento);

    // Laço que obriga o usuário a digitar um número maior ou igual a 12
    // Se ele digitar um número menor, mostra uma mensagem de erro e pergunta de novo
    do {
        printf("Digite o comprimento da senha (mínimo 12): ");
        scanf("%d", &comprimento);

        if (comprimento < 12) {
            printf("Erro: O comprimento mínimo recomendado para uma senha segura é 12 caracteres.\n");
            printf("Tente novamente.\n\n");
        }
    } while (comprimento < 12); // Continua enquanto o número for menor que 12

    // Pergunta quais tipos de caracteres incluir
    printf("Incluir letras maiúsculas? (1 - Sim / 0 - Não): ");
    scanf("%d", &incluirMaiusculas);

    printf("Incluir letras minúsculas? (1 - Sim / 0 - Não): ");
    scanf("%d", &incluirMinusculas);

    printf("Incluir números? (1 - Sim / 0 - Não): ");
    scanf("%d", &incluirNumeros);

    printf("Incluir caracteres especiais? (1 - Sim / 0 - Não): ");
    scanf("%d", &incluirEspeciais);

    // Verifica se o usuário escolheu ao menos um tipo de caractere
    int totalTipos = incluirMaiusculas + incluirMinusculas + incluirNumeros + incluirEspeciais;
    if (totalTipos == 0) {
        printf("❌ Erro: Você deve escolher pelo menos um tipo de caractere.\n");
        return 1;
    }

    // Verifica se o número de tipos cabe no comprimento da senha
    if (comprimento < totalTipos) {
        printf("❌ Erro: Você escolheu %d tipos de caracteres, mas o comprimento da senha é apenas %d.\n", totalTipos, comprimento);
        printf("A senha precisa ter pelo menos %d caracteres para incluir todos os tipos escolhidos.\n", totalTipos);
        return 1;
    }

    // Chama a função para gerar a senha
    gerarSenha(comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais);

    return 0; // Encerra o programa normalmente
}
