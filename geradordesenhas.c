#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void embaralhar(char *senha, int comprimento) {
    for (int i = comprimento - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = senha[i];
        senha[i] = senha[j];
        senha[j] = temp;
    }
}

void gerarSenha(int comprimento, int incluirMaiusculas, int incluirMinusculas, int incluirNumeros, int incluirEspeciais) {
    const char caracteresMaiusculos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char caracteresMinusculos[] = "abcdefghijklmnopqrstuvwxyz";
    const char caracteresNumeros[] = "0123456789";
    const char caracteresEspeciais[] = "!@#$%^&*()";

    char caracteresPermitidos[100] = "";
    char senha[100] = "";
    int indice = 0;

    srand(time(0));

    // Etapa 1: Adicionar pelo menos um de cada tipo selecionado
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

    // Etapa 2: Preencher o restante da senha com caracteres aleatórios
    for (; indice < comprimento; indice++) {
        senha[indice] = caracteresPermitidos[rand() % strlen(caracteresPermitidos)];
    }

    // Etapa 3: Embaralhar a senha final
    embaralhar(senha, comprimento);

    // Exibir a senha
    senha[comprimento] = '\0'; // finaliza a string
    printf("Senha gerada: %s\n", senha);
}

int main() {
   int comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais;

   printf("Bem-vindo ao Gerador de Senhas!\n");

   printf("Digite o comprimento da senha: ");
   scanf("%d", &comprimento);

   if (comprimento < 12) {
        printf("Erro: O comprimento mínimo recomendado para uma senha segura é 12 caracteres.\n");
        return 1;
    }

   printf("Incluir letras maiúsculas? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirMaiusculas);

   printf("Incluir letras minúsculas? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirMinusculas);

   printf("Incluir números? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirNumeros);

   printf("Incluir caracteres especiais? (1 - Sim / 0 - Não): ");
   scanf("%d", &incluirEspeciais);

   int totalTipos = incluirMaiusculas + incluirMinusculas + incluirNumeros + incluirEspeciais;

   if (comprimento < totalTipos) {
       printf("Erro: Você escolheu %d tipos de caracteres, mas o comprimento da senha é %d.\n", totalTipos, comprimento);
       printf("A senha precisa ter pelo menos %d caracteres para incluir todos os tipos.\n", totalTipos);
       return 1; // encerra o programa com erro
   }

   gerarSenha(comprimento, incluirMaiusculas, incluirMinusculas, incluirNumeros, incluirEspeciais);

   return 0;
}
