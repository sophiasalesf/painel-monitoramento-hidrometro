#include "../../../include/subsistemas/fachada/Fachada.hpp"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

// Construtor
Fachada::Fachada()
    : logger("logs/painel.log") {
    cout << "[FACHADA] Sistema inicializado com sucesso!" << endl;

    notificadorAlertas = std::make_shared<Notificador>("Alertas de Consumo");
    armazenamentoStrategy = nullptr;

    logger.info("Sistema inicializado pela Fachada");
}


// INTERFACE SIMPLIFICADA PARA USUÁRIOS 
bool Fachada::criarUsuario(const string& cpf, const string& nome, const string& email) {
    cout << "[FACHADA] ";
    return usuarioService.criarUsuario(cpf, nome, email);
}

Usuario* Fachada::obterUsuario(const string& cpf) {
    return usuarioService.obterUsuario(cpf);
}

bool Fachada::atualizarUsuario(const string& cpf, const string& email) {
    cout << "[FACHADA] ";
    return usuarioService.atualizarUsuario(cpf, email);
}

vector<Usuario> Fachada::listarUsuarios() {
    return usuarioService.listarUsuarios();
}

void Fachada::definirLimiteConsumoUsuario(const string& cpf, double limite) {
    cout << "[FACHADA] ";
    usuarioService.definirLimiteConsumo(cpf, limite);
}

// INTERFACE SIMPLIFICADA PARA CONTAS 
bool Fachada::criarConta(const string& numeroConta, const string& cpfTitular, const string& endereco) {
    cout << "[FACHADA] ";
    return usuarioService.criarConta(numeroConta, cpfTitular, endereco);
}

Conta* Fachada::obterConta(const string& numeroConta) {
    return usuarioService.obterConta(numeroConta);
}

vector<Conta> Fachada::listarContasPorUsuario(const string& cpfTitular) {
    return usuarioService.listarContasPorUsuario(cpfTitular);
}

// INTERFACE SIMPLIFICADA PARA HIDRÔMETROS 
bool Fachada::criarHidrometro(const string& numeroHidrometro, const string& numeroConta) {
    cout << "[FACHADA] ";
    bool criado = usuarioService.criarHidrometro(numeroHidrometro, numeroConta);

    if (criado) {
        Hidrometro* hidrometro = usuarioService.obterHidrometro(numeroHidrometro);
        if (hidrometro != nullptr) {
            hidrometro->adicionarObservador(notificadorAlertas);
        }
    }

    return criado;
}

Hidrometro* Fachada::obterHidrometro(const string& numeroHidrometro) {
    return usuarioService.obterHidrometro(numeroHidrometro);
}

vector<Hidrometro> Fachada::listarHidrometrosPorConta(const string& numeroConta) {
    return usuarioService.listarHidrometrosPorConta(numeroConta);
}

void Fachada::listarHistoricoHidrometro(const string& numeroHidrometro) {
    cout << "[FACHADA] ";
    usuarioService.listarHistoricoHidrometro(numeroHidrometro);
}

// INTERFACE SIMPLIFICADA PARA ARMAZENAMENTO
void Fachada::configurarArmazenamento(std::shared_ptr<ArmazenamentoStrategy> strategy) {
    armazenamentoStrategy = strategy;
}

void Fachada::salvarSistema() {
    if (!armazenamentoStrategy) {
        cout << "[FACHADA] Nenhuma estrategia de armazenamento configurada.\n";
        logger.aviso("Tentativa de salvar sistema sem estrategia de armazenamento configurada");
        return;
    }

    auto usuarios = usuarioService.listarUsuarios();
    auto contas = usuarioService.listarTodasContas();
    auto hidrometros = usuarioService.listarTodosHidrometros();

    armazenamentoStrategy->salvar(usuarios, contas, hidrometros);
    logger.info("Sistema salvo via ArmazenamentoStrategy\n");
}

void Fachada::carregarSistema() {
    if (!armazenamentoStrategy) {
        cout << "[FACHADA] Nenhuma estrategia de armazenamento configurada.\n";
        return;
    }

    vector<Usuario> usuarios;
    vector<Conta> contas;
    vector<Hidrometro> hidrometros;

    armazenamentoStrategy->carregar(usuarios, contas, hidrometros);

    usuarioService.recarregarDados(usuarios, contas, hidrometros);
}


// TESTES
void Fachada::testar() {
    cout << "\n- CENARIO 1: CADASTRO E CONSULTA\n" << endl;

    // 1. Criar usuários
    cout << "[1] Criando usuarios..." << endl;
    criarUsuario("12345678900", "Sophia Sales", "sophia@email.com");
    criarUsuario("98765432100", "Arley Pereira", "arley@email.com");

    // 2. Listar usuários
    cout << "\n[2] Listando usuarios..." << endl;
    auto usuarios = listarUsuarios();
    cout << "[FACHADA] Total de usuarios: " << usuarios.size() << endl;

    // 3. Criar contas
    cout << "\n[3] Criando contas..." << endl;
    criarConta("0001-001", "12345678900", "Rua A, 123");
    criarConta("0001-002", "12345678900", "Rua B, 456");

    // 4. Listar contas de um usuário
    cout << "\n[4] Listando contas de Sophia..." << endl;
    auto contas = listarContasPorUsuario("12345678900");
    cout << "[FACHADA] Contas do usuario: " << contas.size() << endl;

    // 5. Criar hidrômetro
    cout << "\n[5] Criando hidrometro..." << endl;
    criarHidrometro("H123456", "0001-001");

    // 6. Atualizar usuário
    cout << "\n[6] Atualizando usuario..." << endl;
    atualizarUsuario("12345678900", "sophia.novo@email.com");

    cout << "\n[FIM DO CENARIO 1]\n" << endl;
}

double Fachada::processarImagemOCR(const std::string& caminhoImagem) {
    cout << "[FACHADA] Iniciando leitura via OCR: " << caminhoImagem << endl;
    ProcessadorOCR processador(caminhoImagem);
    double valor = processador.processar();

    cout << "[PROCESSADOR] Processamento OCR concluido." << endl;
    cout << "[FACHADA] Valor obtido (OCR): " << valor << " m^3" << endl;

    return valor;
}

double Fachada::processarImagemSegmentacao(const string& caminhoImagem) {
    cout << "[FACHADA] Iniciando leitura via Segmentacao: " << caminhoImagem << endl;
    cout << "[PROCESSADOR] Processamento por segmentacao concluido." << endl;

    ProcessadorSegmentacao processador(caminhoImagem);
    double valor = processador.processar();
    cout << "[FACHADA] Valor obtido (Segmentacao): " << valor << " m^3" << endl;

    // Integração com hidrômetro e Observer
    Hidrometro* hidrometro = usuarioService.obterHidrometro("H123456");
    if (hidrometro != nullptr) {
        hidrometro->setLeituraAtual(valor);
    }

    // Verificação de limite de consumo (CPF 12345678900)
    double limite = usuarioService.obterLimiteConsumo("12345678900");
    if (limite > 0.0) {
        double consumoTotal = usuarioService.obterConsumoTotalUsuario("12345678900");
        if (consumoTotal > limite && notificadorAlertas) {
            string msg = "LIMITE EXCEDIDO para usuario 12345678900: "
                              + to_string(consumoTotal) + " m^3 (limite "
                              + to_string(limite) + " m^3)";
            notificadorAlertas->atualizar(msg);
        }
    }

    return valor;
}