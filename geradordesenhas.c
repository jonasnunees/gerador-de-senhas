#include <stdio.h> // Biblioteca padrão de entrada e saída (para printf e scanf)
#include <stdlib.h> // Biblioteca para funções como rand() e srand()
#include <time.h> // Biblioteca usada para obter o tempo atual (para gerar números aleatórios diferentes a cada execução)
#include <string.h> // Biblioteca para manipular strings (como strcat e strlen)

// Função que embaralha os caracteres da senha para deixá-la mais aleatória
void embaralhar(char *senha, int comprimento) {
    for (int i = comprimento - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera um índice aleatório entre 0 e i
        // Troca os caracteres de posição
        char temp = senha[i];
        senha[i] = senha[j];
        senha[j] = temp;
    }
}

// Função principal que gera a senha conforme as opções escolhidas
void gerarSenha(int comprimento, int incluirMaiusculas, int incluirMinusculas, int incluirNumeros, int incluirEspeciais) {
    // Conjuntos de caracteres disponíveis para cada tipo
    const char caracteresMaiusculos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char caracteresMinusculos[] = "abcdefghijklmnopqrstuvwxyz";
    const char caracteresNumeros[] = "0123456789";
    const char caracteresEspeciais[] = "!@#$%^&*()";

    char caracteresPermitidos[100] = ""; // Armazena todos os caracteres válidos, dependendo da escolha do usuário
    char senha[100] = ""; // Aqui será armazenada a senha gerada
    int indice = 0; // Controla a posição atual dentro da senha

    srand(time(0)); // Inicializa o gerador de números aleatórios com base no tempo atual

    // Etapa 1: Garante que pelo menos um caractere de cada tipo escolhido seja adicionado à senha
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

    // Etapa 2: Preencher o restante da senha com caracteres aleatórios permitidos
    for (; indice < comprimento; indice++) {
        senha[indice] = caracteresPermitidos[rand() % strlen(caracteresPermitidos)];
    }

    // Etapa 3: Embaralha os caracteres da senha para não deixar os primeiros previsíveis
    embaralhar(senha, comprimento);

    // Exibir a senha
    senha[comprimento] = '\0'; // Finaliza a string com o caractere nulo
    printf("Senha gerada: %s\n", senha);
}

int main() {
   // Variáveis que vão armazenar as escolhas do usuário
   int comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais;

   printf("Bem-vindo ao Gerador de Senhas!\n");

   printf("Digite o comprimento da senha: ");
   scanf("%d", &comprimento);

   // Verifica se o comprimento mínimo recomendado foi respeitado
   if (comprimento < 12) {
        printf("Erro: O comprimento mínimo recomendado para uma senha segura é 12 caracteres.\n");
        return 1;
    }

   // Pergunta se o usuário deseja incluir cada tipo de caractere
   printf("Incluir letras maiúsculas? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirMaiusculas);

   printf("Incluir letras minúsculas? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirMinusculas);

   printf("Incluir números? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirNumeros);

   printf("Incluir caracteres especiais? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirEspeciais);

   // Verifica quantos tipos de caracteres foram escolhidos
   int totalTipos = incluirMaiusculas + incluirMinusculas + incluirNumeros + incluirEspeciais;

   // Impede que o número de tipos escolhidos seja maior que o comprimento total da senha
   if (comprimento < totalTipos) {
       printf("Erro: Você escolheu %d tipos de caracteres, mas o comprimento da senha é %d.\n", totalTipos, comprimento);
       printf("A senha precisa ter pelo menos %d caracteres para incluir todos os tipos.\n", totalTipos);
       return 1; // encerra o programa com erro
   }

   // Gera e exibe a senha
   gerarSenha(comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais);

   return 0;
}
