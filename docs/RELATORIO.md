# Analisador Lexico da Linguagem Domus

## Capa

Disciplina: Compiladores

Trabalho: Desenvolvimento de um analisador lexico para a linguagem Domus

Integrantes: PREENCHER COM OS NOMES COMPLETOS DO GRUPO

## 1. Lexemas e tokens

O analisador reconhece os seguintes grupos de tokens:

| Grupo | Tokens |
| --- | --- |
| Controle | `ENDFILE`, `ERROR` |
| Palavras-chave | `SENSOR`, `ATUADOR`, `PORTA`, `ANALOGICO`, `DIGITAL`, `SE`, `ENTAO`, `SENAO`, `FIMSE`, `ENQUANTO`, `FIMENQUANTO`, `LER`, `ESCREVER` |
| Operadores | `MAIS`, `MENOS`, `MULT`, `BARRA`, `MENORQUE`, `MENORIGUAL`, `MAIORQUE`, `MAIORIGUAL`, `IGUAL`, `DIFERENTE`, `ATRIBUICAO` |
| Separadores | `PONTO`, `DOISPONTOS`, `VIRGULA`, `ABREPARENTESE`, `FECHAPARENTESE` |
| Outros | `ID`, `NUM` |

Os lexemas de `NUM` sao sequencias de um ou mais digitos. Os lexemas de `ID`
iniciam por letra ou sublinhado e continuam com letras, digitos ou sublinhado.
As palavras-chave sao reconhecidas depois da leitura de um identificador. Espacos, tabulacoes, quebras de linha e comentarios `/* ... */` sao ignorados.

## 2. Estrategia de desenvolvimento

Foi implementado um analisador manual com uma maquina de estados finitos. A
funcao `getToken()` le caracteres do arquivo-fonte externo, acumula o lexema e
transita entre os estados de identificador, numero, operadores compostos e
comentarios. Quando alcanca um estado final, retorna um valor de `TokenType`.

Operadores que podem ter dois caracteres sao tratados com estados intermediarios:
`<`, `>`, `!`, `=` e `/`. O caractere excedente e devolvido ao buffer quando o
operador reconhecido tem apenas um caractere. Comentarios podem atravessar linhas; um comentario que chega ao fim de arquivo sem `*/` produz `ERROR`.

O diagrama do automato esta em `automato.svg`; o arquivo-fonte Graphviz usado para gera-lo tambem esta disponivel em `automato.dot`.

## 3. Gerador automatico

Nao foi utilizado gerador automatico de analisador lexico. Todo o scanner foi
implementado manualmente em C.

## 4. Compilacao e execucao

No diretorio raiz do projeto, execute `make` para compilar e `make run` para
executar o programa de teste. Tambem pode ser usado `./domus-lexico <arquivo-fonte>`.
O arquivo-fonte e obrigatoriamente externo ao executavel.

## 5. Resultados do programa de teste

O arquivo `ExemploDomus.txt` exercita declaracoes, palavras-chave, identificadores, numeros, operadores aritmeticos e relacionais, atribuicao, separadores, parenteses e comentario em multiplas linhas. A execucao imprime uma tabela com as colunas `Linha`, `Token` e `Lexema`, encerrada por `ENDFILE` na linha 24.

Exemplos observados na execucao:

| Linha | Token | Lexema |
| --- | --- | --- |
| 2 | `SENSOR` | `sensor` |
| 2 | `ID` | `temperatura` |
| 2 | `DOISPONTOS` | `:` |
| 12 | `ATRIBUICAO` | `<-` |
| 19 | `MAIS` | `+` |
| 21 | `MAIORQUE` | `>` |
| 24 | `ENDFILE` | `-` |
