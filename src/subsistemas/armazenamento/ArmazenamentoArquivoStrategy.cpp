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
        std::cerr << "[ARMAZENAMENTO] Erro ao abrir arquivos para escrita.\n";
        return;
    }

    // cpf;nome;email;senha
    for (const auto& u : usuarios) {
        arqUsuarios << u.getCpf() << ';'
                    << u.getNome() << ';'
                    << u.getEmail() << ';'
                    << u.getSenha() << '\n';
    }

    // id;usuarioId;endereco
    for (const auto& c : contas) {
    arqContas << c.getNumeroConta() << ';'
              << c.getCpfTitular() << ';'
              << c.getEndereco() << '\n';
    }

    // numeroHidrometro;numeroConta;leituraAtual;historico
    for (const auto& h : hidrometros) {
        arqHidrometros << h.getNumero() << ';'
                    << h.getNumeroConta() << ';'
                    << h.getLeituraAtual() << ';';
        
        // Salvar histórico no formato [valor1,valor2,valor3]
        const auto& historico = h.getHistoricoLeituras();
        arqHidrometros << '[';
        for (size_t i = 0; i < historico.size(); ++i) {
            arqHidrometros << historico[i];
            if (i < historico.size() - 1) {
                arqHidrometros << ',';
            }
        }
        arqHidrometros << "]\n";
    }

    std::cout << "[ARMAZENAMENTO] Dados salvos em arquivos na pasta " << caminhoBase << "\n";
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
        std::cerr << "[ARMAZENAMENTO] Arquivos de dados nao encontrados; nada carregado.\n";
        return;
    }

    std::string linha;

    // Leitura usuarios
    while (std::getline(arqUsuarios, linha)) {
        if (linha.empty()) continue;
        size_t p1 = linha.find(';');
        size_t p2 = linha.find(';', p1 + 1);
        size_t p3 = linha.find(';', p2 + 1);

        std::string cpf = linha.substr(0, p1);
        std::string nome = linha.substr(p1 + 1, p2 - (p1 + 1));
        std::string email = linha.substr(p2 + 1, p3 - (p2 + 1));
        std::string senha = linha.substr(p3 + 1);

        usuarios.emplace_back(cpf, nome, email, senha);
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
        size_t p2 = linha.find(';', p1 + 1);
        size_t p3 = linha.find(';', p2 + 1);

        std::string numero = linha.substr(0, p1);
        std::string numeroConta = linha.substr(p1 + 1, p2 - (p1 + 1));
        double leitura = std::stod(linha.substr(p2 + 1, p3 - (p2 + 1)));

        Hidrometro h(numero, leitura);
        h.setNumeroConta(numeroConta);
        
        // Carregar histórico
        size_t inicioHistorico = linha.find('[', p3);
        size_t fimHistorico = linha.find(']', inicioHistorico);
        
        if (inicioHistorico != std::string::npos && fimHistorico != std::string::npos) {
            std::string strHistorico = linha.substr(inicioHistorico + 1, fimHistorico - inicioHistorico - 1);
            
            // Parse dos valores separados por vírgula
            size_t pos = 0;
            while (pos < strHistorico.length()) {
                size_t proxVirgula = strHistorico.find(',', pos);
                if (proxVirgula == std::string::npos) {
                    proxVirgula = strHistorico.length();
                }
                
                std::string valorStr = strHistorico.substr(pos, proxVirgula - pos);
                if (!valorStr.empty()) {
                    double valor = std::stod(valorStr);
                    h.setLeituraAtual(valor);  // Adiciona ao histórico
                }
                
                pos = proxVirgula + 1;
            }
        }
        
        hidrometros.push_back(h);
    }
}