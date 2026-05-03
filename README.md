# Sistema gerenciador de eventos críticos

Este projeto implementa um sistema de gerenciamento de eventos críticos de uma cidade inteligente.

## Capacidades

O sistema permite registrar, consultar, atualizar, priorizar e encerrar eventos urbanos críticos, como:

- Acidentes de trânsito
- Falhas em semáforos
- Interrupções de energia
- Alagamentos
- Incêndios

## Núcleo do sistema

O núcleo do sistema foi implementado utilizando uma **Árvore AVL**, garantindo operações eficientes de inserção, remoção, busca e consultas, mesmo com grande volume de dados, além de permitir visualização de métricas de saúde da árvore.

## Como compilar para Linux?

Antes de compilar o projeto, verifique se os seguintes pacotes estão instalados:

| Pacote | Descrição |
|---|---|
| `gcc` | Compilador C |
| `make` | Ferramenta para executar o `Makefile` |

> [!NOTE]
> No Linux, esses pacotes geralmente podem ser instalados pelo gerenciador de pacotes da sua distribuição.

### Passos para compilar

Na raiz do repositório, execute:

```bash
make
```

Após a compilação, o executável será gerado em:

```txt
bin/main
```

### Como executar

Para iniciar o programa, execute:

```bash
./bin/main
```

### Resumo rápido

```bash
make
./bin/main
```

<details>
<summary>Possíveis problemas</summary>

Caso o comando `make` não funcione, verifique se você está na raiz do repositório.

</details>

## Executando pelo VS Code

Também é possível executar o projeto diretamente pelo **Visual Studio Code** usando a tecla <kbd>F5</kbd>.

O repositório já possui um arquivo de configuração:

```txt
.vscode/launch.json
```

Com isso, basta:

1. Abrir o projeto no VS Code
2. Pressionar <kbd>F5</kbd> para compilar e executar o programa pelo depurador

> Usar o <kbd>F5</kbd> permite executar o programa em modo de depuração, facilitando a análise do código, uso de breakpoints e inspeção de variáveis.
