#include "../include/subsistemas/fachada/Fachada.hpp"
#include "../include/subsistemas/armazenamento/ArmazenamentoArquivoStrategy.hpp"
#include "../include/subsistemas/adapters/AdapterSHA1.hpp"
#include "../include/subsistemas/adapters/AdapterSHA2.hpp"

#include <iostream>
#include <memory>
#include <iomanip>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Função auxiliar para limpar buffer do cin
void limparBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    cout << "\nPAINEL DE MONITORAMENTO - MENU\n" << endl;
    cout << "1.  Login" << endl;
    cout << "2.  Criar Usuario" << endl;
    cout << "3.  Listar Usuarios" << endl;
    cout << "4.  Criar Conta" << endl;
    cout << "5.  Listar Contas de um Usuario" << endl;
    cout << "6.  Criar Hidrometro" << endl;
    cout << "7.  Listar Hidrometros" << endl;
    cout << "8.  Processar Imagem (OCR)" << endl;
    cout << "9.  Processar Imagem (Segmentacao)" << endl;
    cout << "10. Ver Historico de Hidrometro" << endl;
    cout << "11. Definir Limite de Consumo" << endl;
    cout << "12. Processar Imagem de SHA (via Adapter)" << endl;
    cout << "13. Mudar Adapter SHA" << endl;
    cout << "0.  Sair e Salvar" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    cout << std::fixed << std::setprecision(3);

    cout << "\nPAINEL DE MONITORAMENTO DE HIDROMETROS\n";
    cout << "--------------------------------------\n\n";

    Fachada fachada;
    auto strategy = std::make_shared<ArmazenamentoArquivoStrategy>("dados/");
    fachada.configurarArmazenamento(strategy);

    // Carregar dados salvos
    cout << "[SISTEMA] Carregando dados..." << endl;
    fachada.carregarSistema();

    // Configurar Adapter SHA1
    auto adapterSHA1 = std::make_shared<AdapterSHA1>("C:/Users/Sophia Sales/Desktop/6p/SHA1-para-adapter/simulador_hidrometro_real-dev_sophia.sales/Medicoes_Simulador_1/");
    
    // Configurar Adapter SHA2
    auto adapterSHA2 = std::make_shared<AdapterSHA2>("C:/Users/Sophia Sales/Desktop/6p/SHA2-para-adapter/projeto_hidrometro_pp-dev_ayrton.matos/Medicoes_202311250003_1/");
    
    Usuario* usuarioLogado = nullptr;
    int opcao = -1;

    // Loop do menu
    while (opcao != 0) {
        exibirMenuPrincipal();
        cin >> opcao;
        limparBuffer();

        cout << "\n";

        switch (opcao) {
            case 1: { // Login
                string cpf, senha;
                cout << "=== LOGIN ===" << endl;
                cout << "CPF: ";
                getline(cin, cpf);
                cout << "Senha: ";
                getline(cin, senha);

                usuarioLogado = fachada.login(cpf, senha);
                if (usuarioLogado) {
                    cout << "\n>>> Bem-vindo(a), " << usuarioLogado->getNome() << "! <<<" << endl;
                }
                break;
            }

            case 2: { // Criar Usuario
                string cpf, nome, email, senha;
                cout << "=== CRIAR USUARIO ===" << endl;
                cout << "CPF: ";
                getline(cin, cpf);
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Email: ";
                getline(cin, email);
                cout << "Senha: ";
                getline(cin, senha);

                if (fachada.criarUsuario(cpf, nome, email, senha)) {
                    cout << "\n>>> Usuario criado com sucesso! <<<" << endl;
                }
                break;
            }

            case 3: { // Listar Usuarios
                cout << "=== LISTA DE USUARIOS ===" << endl;
                auto usuarios = fachada.listarUsuarios();
                if (usuarios.empty()) {
                    cout << "Nenhum usuario cadastrado." << endl;
                } else {
                    for (const auto& u : usuarios) {
                        cout << "- " << u.toString() << endl;
                    }
                }
                break;
            }

            case 4: { // Criar Conta
                string numeroConta, cpfTitular, endereco;
                cout << "=== CRIAR CONTA ===" << endl;
                cout << "Numero da Conta: ";
                getline(cin, numeroConta);
                cout << "CPF do Titular: ";
                getline(cin, cpfTitular);
                cout << "Endereco: ";
                getline(cin, endereco);

                if (fachada.criarConta(numeroConta, cpfTitular, endereco)) {
                    cout << "\n>>> Conta criada com sucesso! <<<" << endl;
                }
                break;
            }

            case 5: { // Listar Contas
                string cpf;
                cout << "=== LISTAR CONTAS ===" << endl;
                cout << "CPF do Usuario: ";
                getline(cin, cpf);

                auto contas = fachada.listarContasPorUsuario(cpf);
                if (contas.empty()) {
                    cout << "Nenhuma conta encontrada para este usuario." << endl;
                } else {
                    for (const auto& c : contas) {
                        cout << "- " << c.toString() << endl;
                    }
                }
                break;
            }

            case 6: { // Criar Hidrometro
                string numeroHidrometro, numeroConta;
                cout << "=== CRIAR HIDROMETRO ===" << endl;
                cout << "Numero do Hidrometro: ";
                getline(cin, numeroHidrometro);
                cout << "Numero da Conta: ";
                getline(cin, numeroConta);

                if (fachada.criarHidrometro(numeroHidrometro, numeroConta)) {
                    cout << "\n>>> Hidrometro criado com sucesso! <<<" << endl;
                }
                break;
            }

            case 7: { // Listar Hidrometros
                string numeroConta;
                cout << "=== LISTAR HIDROMETROS ===" << endl;
                cout << "Numero da Conta: ";
                getline(cin, numeroConta);

                auto hidrometros = fachada.listarHidrometrosPorConta(numeroConta);
                if (hidrometros.empty()) {
                    cout << "Nenhum hidrometro encontrado para esta conta." << endl;
                } else {
                    for (const auto& h : hidrometros) {
                        cout << "- Hidrometro " << h.getNumero() 
                             << " | Leitura: " << h.getLeituraAtual() << " m^3" << endl;
                    }
                }
                break;
            }

            case 8: { // Processar OCR
                string caminho, numeroHidrometro;
                cout << "\n=== PROCESSAR IMAGEM (OCR) ===" << endl;
                cout << "Caminho da imagem: ";
                getline(cin, caminho);
                cout << "Numero do Hidrometro: ";
                getline(cin, numeroHidrometro);

                double valor = fachada.processarImagemOCR(caminho, numeroHidrometro);
                cout << "\n>>> Valor lido: " << valor << " m^3 <<<" << endl;
                break;
            }

            case 9: { // Processar Segmentacao
                string caminho, numeroHidrometro;
                cout << "\n=== PROCESSAR IMAGEM (SEGMENTACAO) ===" << endl;
                cout << "Caminho da imagem: ";
                getline(cin, caminho);
                cout << "Numero do Hidrometro: ";
                getline(cin, numeroHidrometro);

                double valor = fachada.processarImagemSegmentacao(caminho, numeroHidrometro);
                cout << "\n>>> Valor lido: " << valor << " m^3 <<<" << endl;
                break;
            }


            case 10: { // Historico
                string numeroHidrometro;
                cout << "=== HISTORICO DE LEITURAS ===" << endl;
                cout << "Numero do Hidrometro: ";
                getline(cin, numeroHidrometro);

                fachada.listarHistoricoHidrometro(numeroHidrometro);
                break;
            }

            case 11: { // Definir Limite
                string cpf;
                double limite;
                cout << "=== DEFINIR LIMITE DE CONSUMO ===" << endl;
                cout << "CPF do Usuario: ";
                getline(cin, cpf);
                cout << "Limite (m^3): ";
                cin >> limite;
                limparBuffer();

                fachada.definirLimiteConsumoUsuario(cpf, limite);
                cout << "\n>>> Limite definido! <<<" << endl;
                break;
            }

            case 12: { // Processar imagem de SHA via Adapter
                string numeroHidrometro;
                cout << "\n=== PROCESSAR IMAGEM DE SHA ===";
                cout << "\nNumero do Hidrometro: ";
                getline(cin, numeroHidrometro);

                double valor = fachada.processarImagemDeSHA(numeroHidrometro);
                if (valor > 0) {
                    cout << "\n>>> Valor lido do SHA: " << valor << " m^3 <<<" << endl;
                }
                break;
            }

            case 13: { // Mudar adapter SHA (novo)
                int escolha;
                cout << "\n=== MUDAR ADAPTER SHA ===" << endl;
                cout << "1. SHA1 - Simulador de Pedro (branch de Sophia)" << endl;
                cout << "2. SHA2 - Simulador de Ligia (branch de Ayrton)" << endl;
                cout << "Escolha: ";
                cin >> escolha;
                limparBuffer();
                
                if (escolha == 1) {
                    fachada.configurarAdapterSHA(adapterSHA1);
                    cout << ">>> SHA1 ativado! <<<" << endl;
                } else if (escolha == 2) {
                    fachada.configurarAdapterSHA(adapterSHA2);
                    cout << ">>> SHA2 ativado! <<<" << endl;
                }
                break;
            }


            case 0: { // Sair
                cout << "=== SALVANDO DADOS ===" << endl;
                fachada.salvarSistema();
                cout << "\n>>> Sistema encerrado. <<<" << endl;
                break;
            }

            default:
                cout << ">>> Opcao invalida! Tente novamente. <<<" << endl;
                break;
        }
    }

    return 0;
}