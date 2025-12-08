# Painel de Monitoramento de Hidrômetro (Fachada)

Sistema em C++ que implementa o padrão de projeto Facade para gerenciar usuários, contas de consumo de água e hidrômetros. O projeto organiza o código em camadas (Fachada → Serviço → Entidades), demonstrando como simplificar o acesso a subsistemas complexos por meio de uma interface unificada.

## Evolução atual do projeto 


## Padrões de projeto implementados


Facade (Fachada)
A classe Fachada encapsula e simplifica o acesso ao subsistema de usuários, contas e hidrômetros. Em vez de o código cliente lidar diretamente com múltiplas classes e serviços, interage apenas com a fachada, que coordena as chamadas internas.

## Funcionalidades
- Criação de usuários com CPF, nome e e‑mail.
- Criação de contas de água associadas a um usuário (número da conta, endereço).
- Criação de hidrômetros vinculados a uma conta.
- Associação de múltiplas contas a um mesmo usuário.
- Associação de múltiplos hidrômetros a uma mesma conta.
- Atualização de dados de usuário.
- Listagem de usuários, contas e hidrômetros por meio da fachada.
- Execução de um “teste rápido” no main.cpp que exercita as operações principais.

## Estrutura do código
- `include/subsistemas/usuarios/Usuario.hpp` → Declara a entidade Usuario (CPF, nome, e‑mail, lista de contas).

- `include/subsistemas/usuarios/Conta.hpp` → Declara a entidade Conta (número da conta, CPF do titular, endereço, hidrômetro associado).

- `include/subsistemas/usuarios/Hidrometro.hpp` → Declara a entidade Hidrometro (identificador, leitura atual, etc.).

- `include/subsistemas/usuarios/UsuarioService.hpp` → Camada de serviço responsável pelo CRUD de Usuário, Conta e Hidrometro.

- `include/subsistemas/fachada/Fachada.hpp` → Declara a classe Fachada, que expõe métodos de alto nível para o painel.

- `src/subsistemas/usuarios/*.cpp` → Implementações de Usuario, Conta, Hidrometro e UsuarioService.

- `src/subsistemas/fachada/Fachada.cpp` → Implementação da classe Fachada.

- `src/main.cpp` → Ponto de entrada. Executa um roteiro de teste chamando apenas a fachada (cria usuários, contas, hidrômetro, atualiza dados e imprime logs no terminal).

## Como compilar e executar
1. Compile o projeto no PowerShell (Windows, usando g++ instalado e estando na pasta raiz do projeto):
```
g++ -std=c++17 -I include `
  src/main.cpp `
  src/subsistemas/usuarios/Usuario.cpp `
  src/subsistemas/usuarios/Conta.cpp `
  src/subsistemas/usuarios/Hidrometro.cpp `
  src/subsistemas/usuarios/UsuarioService.cpp `
  src/subsistemas/fachada/Fachada.cpp `
  -o painel.exe
```

2. Execute o executáxel:
`.\painel.exe`

## Exemplo de saída no terminal
<img width="643" height="410" alt="image" src="https://github.com/user-attachments/assets/3974825e-9884-4942-a112-9167538f0862" />

## Desenvolvedora
Sophia Sales
IFPB – Engenharia de Computação
GitHub: https://github.com/Sophia7b
