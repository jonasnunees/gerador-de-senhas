# 🔐 Gerador de Senhas em C

Este projeto é um **Gerador de Senhas Seguras** desenvolvido em linguagem C.  
Ele permite que o usuário personalize sua senha com letras maiúsculas, minúsculas, números e caracteres especiais, garantindo maior segurança.

---

## 🚀 Funcionalidades

- Gera senhas seguras com comprimento personalizado.
- Permite escolher:
  - Letras maiúsculas
  - Letras minúsculas
  - Números
  - Caracteres especiais
- Garante que todos os tipos selecionados apareçam na senha.
- Embaralha os caracteres para maior aleatoriedade.

---

## 💻 Como usar

### 1. Compile o programa

Você pode usar o GCC para compilar:

```bash
gcc -o geradordesenhas.exe main.c
```

### 2. Execute o programa

```
./main.c
```

### 3. Interaja com o menu

O programa irá pedir:
- Comprimento da senha (mínimo 12 caracteres)
- Se deseja incluir letras maiúsculas
- Se deseja incluir letras minúsculas
- Se deseja incluir números
- Se deseja incluir caracteres especiais

🧠 Exemplo de uso

```
Digite o comprimento da senha: 16
Incluir letras maiúsculas? (1 - Sim / 0 - Não): 1
Incluir letras minúsculas? (1 - Sim / 0 - Não): 1
Incluir números? (1 - Sim / 0 - Não): 1
Incluir caracteres especiais? (1 - Sim / 0 - Não): 1

Senha gerada: dA@4p&E5b!Z0McaL
```

📂 Estrutura do Código

- gerarSenha() — Função principal que monta a senha com base nas opções do usuário.
- embaralhar() — Mistura os caracteres da senha para deixá-la mais aleatória.
- main() — Interface com o usuário, validações e chamada da geração da senha.

⚠️ Requisitos

- Compilador C (ex: GCC)
- Terminal ou prompt de comando

📌 Observações

- O código utiliza srand(time(0)) para garantir senhas diferentes a cada execução.
- O programa impede que você gere senhas curtas ou que não possam conter todos os tipos escolhidos.

📄 Licença

Este projeto está sob a licença MIT.
Sinta-se livre para usar, modificar e compartilhar!

🙌 Contribuições

Contribuições são bem-vindas!
Abra uma issue ou envie um pull request com melhorias ou sugestões.
