# 🔐 Gerador de Senhas Seguras em C

Este é um gerenciador de senhas simples escrito em linguagem C, que permite gerar senhas seguras, salvá-las criptografadas e acessá-las posteriormente. Ideal para iniciantes em C que desejam aprender sobre manipulação de arquivos, criptografia básica, argumentos de linha de comando e boas práticas de programação.

---

## 🚀 Funcionalidades

- Geração de senhas seguras com tamanho e composição personalizáveis
- Armazenamento das senhas criptografadas em um arquivo local (`senhas.txt`)
- Suporte a dois modos de uso:
  - Modo interativo (com menus)
  - Modo direto via linha de comando
- Interface amigável para usuários iniciantes
- Código comentado e organizado para facilitar o aprendizado

---

## ⚙️ Como compilar

Use o `gcc` para compilar o programa:

```bash
gcc -o geradorSenha geradorSenha.c
```

🧪 Modo Interativo (padrão)

Ao executar o programa sem argumentos, ele entra no modo interativo com menus:

```
./geradorSenha
```

🧩 Modo via Linha de Comando

Permite gerar uma senha diretamente com parâmetros:

```
./geradorSenha -l TAMANHO -M -m -n -s -S SERVICO -U USUARIO
```

Parâmetros:

| Parâmetro | Descrição                                |
| --------: | ---------------------------------------- |
|      `-l` | Tamanho da senha                         |
|      `-M` | Incluir letras **maiúsculas**            |
|      `-m` | Incluir letras **minúsculas**            |
|      `-n` | Incluir **números**                      |
|      `-s` | Incluir **símbolos**                     |
|      `-S` | Nome do **serviço** (ex: Gmail, Netflix) |
|      `-U` | Nome do **usuário** ou email             |

Exemplo:

```
./geradorSenha -l 16 -M -m -n -s -S Gmail -U usuario@email.com
```

🔒 Segurança

As senhas são criptografadas usando o algoritmo XOR com uma chave fixa (pode ser modificada no código). Elas são armazenadas no arquivo senhas.txt de forma criptografada, sendo descriptografadas apenas em tempo de execução.

- Aviso: Este projeto é didático. Para aplicações reais, recomenda-se o uso de bibliotecas seguras e algoritmos de criptografia robustos.

📁 Arquivo senhas.txt

- O arquivo senhas.txt é usado para armazenar os registros de serviço, usuário e senha (criptografada).

🛠 Próximas melhorias sugeridas

- Alterar a chave de criptografia para uma chave segura e variável
- Interface gráfica (CLI avançada ou GUI com GTK)
- Suporte a remoção e edição de senhas
- Exportação para CSV/JSON
- Testes automatizados

👨‍💻 Autor
- Desenvolvido por Jonas – apaixonado por programação, segurança e software open source.

📝 Licença
- Este projeto está licenciado sob a MIT License.
