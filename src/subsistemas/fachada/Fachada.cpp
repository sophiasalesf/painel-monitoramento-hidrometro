#include "../../../include/subsistemas/fachada/Fachada.hpp"
#include <iostream>
#include <iomanip>

// Construtor
Fachada::Fachada() {
    std::cout << "[FACHADA] Sistema inicializado com sucesso!" << std::endl;

    notificadorAlertas = std::make_shared<Notificador>("Alertas de Consumo");
    armazenamentoStrategy = nullptr;
}

// INTERFACE SIMPLIFICADA PARA USUÁRIOS 
bool Fachada::criarUsuario(const std::string& cpf, const std::string& nome, const std::string& email) {
    std::cout << "[FACHADA] ";
    return usuarioService.criarUsuario(cpf, nome, email);
}

Usuario* Fachada::obterUsuario(const std::string& cpf) {
    return usuarioService.obterUsuario(cpf);
}

bool Fachada::atualizarUsuario(const std::string& cpf, const std::string& email) {
    std::cout << "[FACHADA] ";
    return usuarioService.atualizarUsuario(cpf, email);
}

std::vector<Usuario> Fachada::listarUsuarios() {
    return usuarioService.listarUsuarios();
}

void Fachada::definirLimiteConsumoUsuario(const std::string& cpf, double limite) {
    std::cout << "[FACHADA] ";
    usuarioService.definirLimiteConsumo(cpf, limite);
}

// INTERFACE SIMPLIFICADA PARA CONTAS 
bool Fachada::criarConta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco) {
    std::cout << "[FACHADA] ";
    return usuarioService.criarConta(numeroConta, cpfTitular, endereco);
}

Conta* Fachada::obterConta(const std::string& numeroConta) {
    return usuarioService.obterConta(numeroConta);
}

std::vector<Conta> Fachada::listarContasPorUsuario(const std::string& cpfTitular) {
    return usuarioService.listarContasPorUsuario(cpfTitular);
}

// INTERFACE SIMPLIFICADA PARA HIDRÔMETROS 
bool Fachada::criarHidrometro(const std::string& numeroHidrometro, const std::string& numeroConta) {
    std::cout << "[FACHADA] ";
    bool criado = usuarioService.criarHidrometro(numeroHidrometro, numeroConta);

    if (criado) {
        Hidrometro* hidrometro = usuarioService.obterHidrometro(numeroHidrometro);
        if (hidrometro != nullptr) {
            hidrometro->adicionarObservador(notificadorAlertas);
        }
    }

    return criado;
}

Hidrometro* Fachada::obterHidrometro(const std::string& numeroHidrometro) {
    return usuarioService.obterHidrometro(numeroHidrometro);
}

std::vector<Hidrometro> Fachada::listarHidrometrosPorConta(const std::string& numeroConta) {
    return usuarioService.listarHidrometrosPorConta(numeroConta);
}

void Fachada::listarHistoricoHidrometro(const std::string& numeroHidrometro) {
    std::cout << "[FACHADA] ";
    usuarioService.listarHistoricoHidrometro(numeroHidrometro);
}

// INTERFACE SIMPLIFICADA PARA ARMAZENAMENTO
void Fachada::configurarArmazenamento(std::shared_ptr<ArmazenamentoStrategy> strategy) {
    armazenamentoStrategy = strategy;
}

void Fachada::salvarSistema() {
    if (!armazenamentoStrategy) {
        std::cout << "[FACHADA] Nenhuma estrategia de armazenamento configurada.\n";
        return;
    }

    auto usuarios = usuarioService.listarUsuarios();
    auto contas = usuarioService.listarTodasContas();
    auto hidrometros = usuarioService.listarTodosHidrometros();

    armazenamentoStrategy->salvar(usuarios, contas, hidrometros);
}

void Fachada::carregarSistema() {
    if (!armazenamentoStrategy) {
        std::cout << "[FACHADA] Nenhuma estrategia de armazenamento configurada.\n";
        return;
    }

    std::vector<Usuario> usuarios;
    std::vector<Conta> contas;
    std::vector<Hidrometro> hidrometros;

    armazenamentoStrategy->carregar(usuarios, contas, hidrometros);

    usuarioService.recarregarDados(usuarios, contas, hidrometros);
}


// TESTES
void Fachada::testar() {
    std::cout << "\nPRIMEIRO TESTE DA FACHADA\n" << std::endl;

    // 1. Criar usuários
    std::cout << "[1] Criando usuarios..." << std::endl;
    criarUsuario("12345678900", "Sophia Sales", "sophia@email.com");
    criarUsuario("98765432100", "Arley Pereira", "arley@email.com");

    // 2. Listar usuários
    std::cout << "\n[2] Listando usuarios..." << std::endl;
    auto usuarios = listarUsuarios();
    std::cout << "[FACHADA] Total de usuarios: " << usuarios.size() << std::endl;

    // 3. Criar contas
    std::cout << "\n[3] Criando contas..." << std::endl;
    criarConta("0001-001", "12345678900", "Rua A, 123");
    criarConta("0001-002", "12345678900", "Rua B, 456");

    // 4. Listar contas de um usuário
    std::cout << "\n[4] Listando contas de Sophia..." << std::endl;
    auto contas = listarContasPorUsuario("12345678900");
    std::cout << "[FACHADA] Contas do usuario: " << contas.size() << std::endl;

    // 5. Criar hidrômetro
    std::cout << "\n[5] Criando hidrometro..." << std::endl;
    criarHidrometro("H123456", "0001-001");

    // 6. Atualizar usuário
    std::cout << "\n[6] Atualizando usuario..." << std::endl;
    atualizarUsuario("12345678900", "sophia.novo@email.com");

    std::cout << "\nFIM DO PRIMEIRO TESTE\n" << std::endl;
}

double Fachada::processarImagemOCR(const std::string& caminhoImagem) {
    std::cout << "[FACHADA] Processando imagem com OCR: " 
              << caminhoImagem << std::endl;
    ProcessadorOCR processador(caminhoImagem);
    double valor = processador.processar();
    std::cout << "[FACHADA] Valor obtido (OCR): " 
              << valor << " m^3" << std::endl;
    return valor;
}

double Fachada::processarImagemSegmentacao(const std::string& caminhoImagem) {
    std::cout << "[FACHADA] Processando imagem com Segmentacao: " 
              << caminhoImagem << std::endl;
    ProcessadorSegmentacao processador(caminhoImagem);
    double valor = processador.processar();
    std::cout << "[FACHADA] Valor obtido (Segmentacao): " 
              << valor << " m^3" << std::endl;

    // Integração com hidrômetro e Observer (Semana 3)
    Hidrometro* hidrometro = usuarioService.obterHidrometro("H123456");
    if (hidrometro != nullptr) {
        hidrometro->setLeituraAtual(valor);
    }

    // Verificação de limite de consumo (exemplo para CPF 12345678900)
    double limite = usuarioService.obterLimiteConsumo("12345678900");
    if (limite > 0.0) {
        double consumoTotal = usuarioService.obterConsumoTotalUsuario("12345678900");
        if (consumoTotal > limite && notificadorAlertas) {
            std::string msg = "LIMITE EXCEDIDO para usuario 12345678900: "
                              + std::to_string(consumoTotal) + " m^3 (limite "
                              + std::to_string(limite) + " m^3)";
            notificadorAlertas->atualizar(msg);
        }
    }

    return valor;
}