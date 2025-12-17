# Painel de Monitoramento de Hidrômetro (Fachada)

Sistema em C++ que implementa os padrões de projeto Facade, Template Method, Observer e Strategy para gerenciar usuários, contas de consumo de água, hidrômetros, o monitoramento de imagens do hidrômetro, notificações automáticas e armazenamento configurável de dados.

## Evolução atual do projeto 
▰▰▰▰▰▰▰▰▰▱ 90%

## Padrões de projeto implementados

| Padrão            | Onde ver no código                                                                                                                   |
|-------------------|---------------------------------------------------------------------------------------------------------------------------------------|
| **Facade**        | `include/subsistemas/fachada/Fachada.hpp` e `src/subsistemas/fachada/Fachada.cpp` – coordena usuários, contas, hidrômetros, monitoramento de imagens e armazenamento. |
| **Template Method** | `include/subsistemas/monitoramento/ProcessadorImagem.hpp` e `src/subsistemas/monitoramento/*.cpp` – define o algoritmo de processamento de imagens, com etapas especializadas nas subclasses (OCR e Segmentação). |
| **Observer**      | `include/subsistemas/notificacoes/*.hpp` e `src/subsistemas/notificacoes/*.cpp` – notifica automaticamente quando a leitura de um hidrômetro é atualizada a partir do processamento de imagens. |
| **Strategy**      | `include/subsistemas/armazenamento/*.hpp` e `src/subsistemas/armazenamento/*.cpp` – define estratégias de armazenamento (console ou arquivos na pasta \`dados/\`). |

## Funcionalidades

- Criação de usuários com CPF, nome e e‑mail.
- Criação de contas de água associadas a um usuário (número da conta, endereço).
- Criação de hidrômetros vinculados a uma conta.
- Associação de múltiplas contas a um mesmo usuário.
- Associação de múltiplos hidrômetros a uma mesma conta.
- Atualização de dados de usuário.
- Listagem de usuários, contas e hidrômetros por meio da fachada.
- Registro de eventos do painel em log com níveis de informação/aviso em `logs/painel.log`.
- Execução de um roteiro de teste no `main.cpp` que exercita as operações principais pela fachada. 

### Monitoramento de imagens com Template Method

- Leitura simulada do valor do hidrômetro a partir de imagens usando a classe `LeitorImagem`. 
- Processamento de imagens com o padrão Template Method por meio de `ProcessadorImagem` e das classes concretas `ProcessadorOCR` e `ProcessadorSegmentacao`. 
- Integração do monitoramento à fachada com os métodos `processarImagemOCR` e `processarImagemSegmentacao`, permitindo chamar tudo a partir de `Fachada`.

### Notificações com Observer

- Subsistema de notificações baseado em Observer (`Observer`, `Subject`, `Notificador`) para reagir a mudanças na leitura dos hidrômetros.
- A entidade `Hidrometro` passa a herdar de `Subject` e notifica observadores sempre que `setLeituraAtual` é chamado.
- Integração com a fachada: após o processamento por segmentação em `processarImagemSegmentacao`, a fachada atualiza o hidrômetro e dispara um alerta no terminal indicando o novo valor lido.

### Histórico de leituras e limites de consumo
- Cada hidrômetro mantém um histórico de leituras em memória, registrado sempre que a leitura é atualizada.​
- A fachada expõe um método para listar o histórico de um hidrômetro específico, mostrando todas as leituras registradas.​
- O serviço de usuários permite definir um limite de consumo por usuário (em m³).​
- Quando o consumo total de um usuário ultrapassa o limite configurado, o sistema dispara uma notificação de alerta pelo Notificador.

### Armazenamento com Strategy

- Interface `ArmazenamentoStrategy` define a operação de salvar os dados do sistema.
- `ArmazenamentoConsoleStrategy` implementa a estratégia que apenas exibe os dados no console.
- `ArmazenamentoArquivoStrategy` implementa a estratégia que salva usuários, contas e hidrômetros em arquivos texto na pasta `dados/`.
- A fachada utiliza uma instância de `ArmazenamentoStrategy`, permitindo trocar a forma de armazenamento sem alterar o restante do sistema.

## Estrutura do código

- `include/subsistemas/usuarios/Usuario.hpp` → entidade `Usuario` (CPF, nome, e‑mail, lista de contas).
- `include/subsistemas/usuarios/Conta.hpp` → entidade `Conta` (número da conta, CPF do titular, endereço, hidrômetro associado).
- `include/subsistemas/usuarios/Hidrometro.hpp` → entidade `Hidrometro` (identificador, leitura atual, histórico de leituras).
- `include/subsistemas/usuarios/UsuarioService.hpp` → serviço responsável pelo CRUD de usuário, conta, hidrômetro, histórico e limites de consumo.
- `include/subsistemas/fachada/Fachada.hpp` → classe `Fachada`, que expõe métodos de alto nível para o painel, imagens, histórico, limites e armazenamento.
- `include/subsistemas/monitoramento/LeitorImagem.hpp` → simula a leitura de valor do hidrômetro a partir de um caminho de imagem.
- `include/subsistemas/monitoramento/ProcessadorImagem.hpp` → Template Method de processamento de imagens.
- `include/subsistemas/monitoramento/ProcessadorOCR.hpp` → implementação concreta com abordagem de OCR simulada.
- `include/subsistemas/monitoramento/ProcessadorSegmentacao.hpp` → implementação concreta com abordagem simulada de segmentação.
- `include/subsistemas/notificacoes/Observer.hpp` → interface base de observadores.
- `include/subsistemas/notificacoes/Subject.hpp` → classe base que gerencia observadores e notificação.
- `include/subsistemas/notificacoes/Notificador.hpp` → observador concreto que exibe alertas no terminal.
- `include/subsistemas/armazenamento/ArmazenamentoStrategy.hpp` → interface de Strategy para armazenamento.
- `include/subsistemas/armazenamento/ArmazenamentoConsoleStrategy.hpp` → Strategy que mostra dados no console.
- `include/subsistemas/armazenamento/ArmazenamentoArquivoStrategy.hpp` → Strategy que salva dados na pasta `dados/`.

- `src/subsistemas/usuarios/*.cpp` → implementações de `Usuario`, `Conta`, `Hidrometro` e `UsuarioService`.
- `src/subsistemas/fachada/Fachada.cpp` → implementação da classe `Fachada`.
- `src/subsistemas/monitoramento/*.cpp` → implementações de `LeitorImagem`, `ProcessadorImagem`, `ProcessadorOCR` e `ProcessadorSegmentacao`.
- `src/subsistemas/notificacoes/*.cpp` → implementações de `Subject` e `Notificador`.
- `src/subsistemas/armazenamento/*.cpp` → implementações das estratégias de armazenamento.
- `src/main.cpp` → ponto de entrada; executa um roteiro de teste que usa apenas a fachada para criar dados, processar imagens, atualizar hidrômetros, listar histórico, verificar limites e salvar dados.

## Como compilar e executar

1. Compile o projeto no PowerShell (Windows, usando g++) na pasta raiz do projeto:
```
g++ -o main src/main.cpp src/subsistemas/fachada/*.cpp src/subsistemas/usuarios/*.cpp src/subsistemas/monitoramento/*.cpp src/subsistemas/notificacoes/*.cpp src/subsistemas/armazenamento/*.cpp -Iinclude
```

2. Execute o programa:
`.\main`

## Exemplo de saída no terminal
<img width="824" height="910" alt="image" src="https://github.com/user-attachments/assets/6d2b04d5-482a-4598-8f41-507c163ce2fe" />


## Desenvolvedora
Sophia Sales

IFPB – Engenharia de Computação

GitHub: https://github.com/sophiasalesf