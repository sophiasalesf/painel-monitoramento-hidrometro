# Painel de Monitoramento de Hidrômetro (Fachada)

Sistema em C++ que implementa os padrões de projeto Facade, Template Method e Observer para gerenciar usuários, contas de consumo de água, hidrômetros, o monitoramento de imagens do hidrômetro e as notificações automáticas de atualização de leitura.

## Evolução atual do projeto 
▰▰▰▰▰▰▰▱▱▱ 75%

## Padrões de projeto implementados

| Padrão           | Onde ver no código                                                                                             |
|------------------|-----------------------------------------------------------------------------------------------------------------|
| **Facade**       | `include/subsistemas/fachada/Fachada.hpp` e `src/subsistemas/fachada/Fachada.cpp` – Coordena usuários, contas, hidrômetros e o subsistema de monitoramento de imagens. |
| **Template Method** | `include/subsistemas/monitoramento/ProcessadorImagem.hpp` e `src/subsistemas/monitoramento/ProcessadorImagem.cpp` – Define o algoritmo de processamento de imagens, com etapas especializadas nas subclasses. |
| **Observer**     | `include/subsistemas/notificacoes/*.hpp` e `src/subsistemas/notificacoes/*.cpp` – Notifica automaticamente quando a leitura de um hidrômetro é atualizada a partir do processamento de imagens. |


## Funcionalidades

- Criação de usuários com CPF, nome e e‑mail.
- Criação de contas de água associadas a um usuário (número da conta, endereço).
- Criação de hidrômetros vinculados a uma conta.
- Associação de múltiplas contas a um mesmo usuário.
- Associação de múltiplos hidrômetros a uma mesma conta.
- Atualização de dados de usuário.
- Listagem de usuários, contas e hidrômetros por meio da fachada.
- Execução de um roteiro de teste no `main.cpp` que exercita as operações principais pela fachada. 

### Monitoramento de imagens com Template Method

- Leitura simulada do valor do hidrômetro a partir de imagens usando a classe `LeitorImagem`. 
- Processamento de imagens com o padrão Template Method por meio de `ProcessadorImagem` e das classes concretas `ProcessadorOCR` e `ProcessadorSegmentacao`. 
- Integração do monitoramento à fachada com os métodos `processarImagemOCR` e `processarImagemSegmentacao`, permitindo chamar tudo a partir de `Fachada`.

### Notificações com Observer

- Subsistema de notificações baseado em Observer (`Observer`, `Subject`, `Notificador`) para reagir a mudanças na leitura dos hidrômetros.
- A entidade `Hidrometro` passa a herdar de `Subject` e notifica observadores sempre que `setLeituraAtual` é chamado.
- Integração com a fachada: após o processamento por segmentação em `processarImagemSegmentacao`, a fachada atualiza o hidrômetro e dispara um alerta no terminal indicando o novo valor lido.

## Estrutura do código

- `include/subsistemas/usuarios/Usuario.hpp` → Declara a entidade Usuario (CPF, nome, e‑mail, lista de contas).
- `include/subsistemas/usuarios/Conta.hpp` → Declara a entidade Conta (número da conta, CPF do titular, endereço, hidrômetro associado).
- `include/subsistemas/usuarios/Hidrometro.hpp` → Declara a entidade Hidrometro (identificador, leitura atual, etc.).
- `include/subsistemas/usuarios/UsuarioService.hpp` → Camada de serviço responsável pelo CRUD de Usuario, Conta e Hidrometro.
- `include/subsistemas/fachada/Fachada.hpp` → Declara a classe Fachada, que expõe métodos de alto nível para o painel e para o monitoramento de imagens.  
- `include/subsistemas/monitoramento/LeitorImagem.hpp` → Classe base simples para simular a leitura do valor do hidrômetro a partir de um caminho de imagem.  
- `include/subsistemas/monitoramento/ProcessadorImagem.hpp` → Classe abstrata que define o Template Method de processamento de imagens.  
- `include/subsistemas/monitoramento/ProcessadorOCR.hpp` → Implementação concreta do Template Method usando uma abordagem de OCR simulada.  
- `include/subsistemas/monitoramento/ProcessadorSegmentacao.hpp` → Implementação concreta do Template Method usando uma abordagem simulada de segmentação. 
- `include/subsistemas/notificacoes/Observer.hpp` → Interface base para observadores de notificações.
- `include/subsistemas/notificacoes/Subject.hpp` → Classe base que gerencia a lista de observadores e a notificação.
- `include/subsistemas/notificacoes/Notificador.hpp` → Observador concreto que exibe alertas de atualização de leitura no terminal.

- `src/subsistemas/usuarios/*.cpp` → Implementações de Usuario, Conta, Hidrometro e UsuarioService.
- `src/subsistemas/fachada/Fachada.cpp` → Implementação da classe Fachada.
- `src/subsistemas/monitoramento/*.cpp` → Implementações de LeitorImagem, ProcessadorImagem, ProcessadorOCR e ProcessadorSegmentacao.  
- `src/main.cpp` → Ponto de entrada. Executa um roteiro de teste que usa apenas a fachada para criar dados e processar imagens do hidrômetro.  
- `src/subsistemas/notificacoes/*.cpp` → Implementações de `Subject` e `Notificador`.


## Como compilar e executar

1. Compile o projeto no PowerShell (Windows, usando g++) na pasta raiz do projeto:
```
g++ -o main src/main.cpp
src/subsistemas/monitoramento/LeitorImagem.cpp src/subsistemas/monitoramento/ProcessadorImagem.cpp
src/subsistemas/monitoramento/ProcessadorOCR.cpp src/subsistemas/monitoramento/ProcessadorSegmentacao.cpp
src/subsistemas/fachada/Fachada.cpp src/subsistemas/usuarios/UsuarioService.cpp
src/subsistemas/usuarios/Usuario.cpp src/subsistemas/usuarios/Conta.cpp
src/subsistemas/usuarios/Hidrometro.cpp src/subsistemas/notificacoes/Notificador.cpp
src/subsistemas/notificacoes/Subject.cpp -Iinclude
```

2. Execute o programa:
`.\main`

## Exemplo de saída no terminal
<img width="627" height="835" alt="image" src="https://github.com/user-attachments/assets/39300cc4-9fc7-4d96-955d-8c7682ec66a9" />


## Desenvolvedora
Sophia Sales

IFPB – Engenharia de Computação

GitHub: https://github.com/sophiasalesf
