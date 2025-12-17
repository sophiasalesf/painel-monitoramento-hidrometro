# Painel de Monitoramento de Hidrômetro (Fachada)

Sistema em C++ que implementa os padrões de projeto Facade, Template Method, Observer, Strategy e Adapter para gerenciar usuários, contas de consumo de água, hidrômetros, monitoramento de imagens, notificações automáticas e armazenamento configurável de dados.

## Evolução atual do projeto 
▰▰▰▰▰▰▰▰▰▰ 100%

## Padrões de projeto implementados

| Padrão            | Descrição                                                                                                                   |
|-------------------|---------------------------------------------------------------------------------------------------------------------------------------|
| **Facade**        | `include/subsistemas/fachada/Fachada.hpp` e `src/subsistemas/fachada/Fachada.cpp` – coordena usuários, contas, hidrômetros, monitoramento de imagens, adapters e armazenamento. |
| **Template Method** | `include/subsistemas/monitoramento/ProcessadorImagem.hpp` e `src/subsistemas/monitoramento/*.cpp` – define o algoritmo de processamento de imagens com etapas especializadas (OCR e Segmentação). |
| **Observer**      | `include/subsistemas/notificacoes/*.hpp` e `src/subsistemas/notificacoes/*.cpp` – notifica automaticamente mudanças na leitura dos hidrômetros. |
| **Strategy**      | `include/subsistemas/armazenamento/*.hpp` e `src/subsistemas/armazenamento/*.cpp` – define estratégias de armazenamento (console ou arquivos). |
| **Adapter**       | `include/subsistemas/adapters/ISHAAdapter.hpp`, `AdapterSHA1.hpp` e `AdapterSHA2.hpp` – interface comum para múltiplos adaptadores de hash SHA. |

## Funcionalidades

- Gerenciamento de usuários, contas e hidrômetros
- Processamento de imagens com Template Method (OCR e Segmentação)
- Sistema de notificações com Observer Pattern
- Histórico de leituras e limites de consumo por usuário
- Armazenamento flexível (console ou arquivos)
- Adapters SHA1 e SHA2 com interface comum
- Registro de eventos em log (`logs/painel.log`)

## Estrutura do código

**Headers (include/subsistemas/)**
- `usuarios/` – Usuario, Conta, Hidrometro, UsuarioService
- `fachada/` – Fachada (orquestra todos os subsistemas)
- `monitoramento/` – LeitorImagem, ProcessadorImagem, ProcessadorOCR, ProcessadorSegmentacao
- `notificacoes/` – Observer, Subject, Notificador
- `armazenamento/` – ArmazenamentoStrategy, ArmazenamentoConsoleStrategy, ArmazenamentoArquivoStrategy
- `adapters/` – ISHAAdapter, AdapterSHA1, AdapterSHA2

**Implementação (src/subsistemas/)**
- Arquivos `.cpp` correspondentes para cada subsistema
- `main.cpp` – roteiro de teste completo

## Como compilar e executar

1. Compile no PowerShell (Windows):
```
g++ -o main src/main.cpp src/subsistemas/fachada/*.cpp src/subsistemas/usuarios/*.cpp src/subsistemas/monitoramento/*.cpp src/subsistemas/notificacoes/*.cpp src/subsistemas/armazenamento/*.cpp src/subsistemas/adapters/*.cpp -Iinclude
```

2. Execute o programa:
`.\main`

**Colaboradores:**
- Simulador de Pedro (branch de Sophia) – AdapterSHA1
- Simulador de Lígia (branch de Ayrton) – AdapterSHA2

## Desenvolvedora

**Sophia Sales** – Desenvolvedora principal (Facade, Template Method, Observer, Strategy)
IFPB – Engenharia de Computação

GitHub: https://github.com/sophiasalesf
