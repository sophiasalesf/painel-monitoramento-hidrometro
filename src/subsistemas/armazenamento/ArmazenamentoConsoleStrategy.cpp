#include "../../../include/subsistemas/armazenamento/ArmazenamentoConsoleStrategy.hpp"
#include "../../../include/subsistemas/usuarios/Usuario.hpp"
#include "../../../include/subsistemas/usuarios/Conta.hpp"
#include "../../../include/subsistemas/usuarios/Hidrometro.hpp"

#include <iostream>

void ArmazenamentoConsoleStrategy::salvar(
    const std::vector<Usuario>& usuarios,
    const std::vector<Conta>& contas,
    const std::vector<Hidrometro>& hidrometros
) {
    std::cout << "=== Snapshot do sistema (Console) ===\n";

    std::cout << "\nUsuarios:\n";
    for (const auto& u : usuarios) {
        std::cout << "- CPF: " << u.getCpf()
                  << ", Nome: " << u.getNome() << "\n";
    }

    std::cout << "\nContas:\n";
    for (const auto& c : contas) {
        std::cout << "- Numero: " << c.getNumeroConta()
                  << ", CPF Titular: " << c.getCpfTitular()
                  << ", Endereco: " << c.getEndereco() << "\n";
    }

    std::cout << "\nHidrometros:\n";
    for (const auto& h : hidrometros) {
        std::cout << "- Numero: " << h.getNumero()
                  << ", Leitura atual: " << h.getLeituraAtual() << " m^3\n";
    }

    std::cout << "=== Fim do snapshot ===\n";
}

void ArmazenamentoConsoleStrategy::carregar(
    std::vector<Usuario>&,
    std::vector<Conta>&,
    std::vector<Hidrometro>& 
) {
    std::cout << "[ArmazenamentoConsoleStrategy] carregar(): "
                 "nenhuma acao (modo somente exibicao).\n";
}