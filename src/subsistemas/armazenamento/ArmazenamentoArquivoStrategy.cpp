#include "../../../include/subsistemas/armazenamento/ArmazenamentoArquivoStrategy.hpp"
#include "../../../include/subsistemas/usuarios/Usuario.hpp"
#include "../../../include/subsistemas/usuarios/Conta.hpp"
#include "../../../include/subsistemas/usuarios/Hidrometro.hpp"

#include <fstream>
#include <iostream>

ArmazenamentoArquivoStrategy::ArmazenamentoArquivoStrategy(const std::string& caminhoBase)
    : caminhoBase(caminhoBase) {}

// Formato simples por linha, separado por ';'
void ArmazenamentoArquivoStrategy::salvar(
    const std::vector<Usuario>& usuarios,
    const std::vector<Conta>& contas,
    const std::vector<Hidrometro>& hidrometros
) {
    std::ofstream arqUsuarios(caminhoBase + "usuarios.txt");
    std::ofstream arqContas(caminhoBase + "contas.txt");
    std::ofstream arqHidrometros(caminhoBase + "hidrometros.txt");

    if (!arqUsuarios || !arqContas || !arqHidrometros) {
        std::cerr << "[ArmazenamentoArquivoStrategy] Erro ao abrir arquivos para escrita.\n";
        return;
    }

    // id;nome
    for (const auto& u : usuarios) {
        arqUsuarios << u.getCpf() << ';'
                    << u.getNome() << ';'
                    << u.getEmail() << '\n';
    }

    // id;usuarioId;endereco
    for (const auto& c : contas) {
    arqContas << c.getNumeroConta() << ';'
              << c.getCpfTitular() << ';'
              << c.getEndereco() << '\n';
    }

    // numeroSerie;contaId;leituraAtual
    for (const auto& h : hidrometros) {
    arqHidrometros << h.getNumero() << ';'
                   << h.getLeituraAtual() << '\n';
    }

    std::cout << "[ArmazenamentoArquivoStrategy] Dados salvos em arquivos na pasta " << caminhoBase << "\n";
}

void ArmazenamentoArquivoStrategy::carregar(
    std::vector<Usuario>& usuarios,
    std::vector<Conta>& contas,
    std::vector<Hidrometro>& hidrometros
) {
    usuarios.clear();
    contas.clear();
    hidrometros.clear();

    std::ifstream arqUsuarios(caminhoBase + "usuarios.txt");
    std::ifstream arqContas(caminhoBase + "contas.txt");
    std::ifstream arqHidrometros(caminhoBase + "hidrometros.txt");

    if (!arqUsuarios || !arqContas || !arqHidrometros) {
        std::cerr << "[ArmazenamentoArquivoStrategy] Arquivos de dados nao encontrados; nada carregado.\n";
        return;
    }

    std::string linha;

    // Leitura usuarios
    while (std::getline(arqUsuarios, linha)) {
        if (linha.empty()) continue;
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);

        std::string cpf = linha.substr(0, p1);
        std::string nome = linha.substr(p1 + 1, p2 - (p1 + 1));
        std::string email = linha.substr(p2 + 1);

        usuarios.emplace_back(cpf, nome, email);
    }

    // Leitura contas
    while (std::getline(arqContas, linha)) {
        if (linha.empty()) continue;
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);

        std::string numeroConta = linha.substr(0, p1);
        std::string cpfTitular = linha.substr(p1 + 1, p2 - (p1 + 1));
        std::string endereco = linha.substr(p2 + 1);

        contas.emplace_back(numeroConta, cpfTitular, endereco);
    }

    // Leitura hidrometros
    while (std::getline(arqHidrometros, linha)) {
        if (linha.empty()) continue;
        size_t p1 = linha.find(';');

        std::string numero = linha.substr(0, p1);
        double leitura = std::stod(linha.substr(p1 + 1));

        Hidrometro h(numero, leitura);
        hidrometros.push_back(h);
    }

    std::cout << "[ArmazenamentoArquivoStrategy] Dados carregados de arquivos na pasta "
              << caminhoBase << "\n";
}
