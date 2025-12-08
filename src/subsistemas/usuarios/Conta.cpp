#include "../../../include/subsistemas/usuarios/Conta.hpp"
#include <iostream>
#include <sstream>
#include <ctime>

// Construtor padrão
Conta::Conta()
    : numeroConta(""), cpfTitular(""), endereco(""), dataCriacao("") {
}

// Construtor com parâmetros
Conta::Conta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco)
    : numeroConta(numeroConta), cpfTitular(cpfTitular), endereco(endereco) {
    // Gerar timestamp (simplificado)
    time_t agora = time(nullptr);
    dataCriacao = std::to_string(agora);
}

// Getters
std::string Conta::getNumeroConta() const {
    return numeroConta;
}

std::string Conta::getCpfTitular() const {
    return cpfTitular;
}

std::string Conta::getEndereco() const {
    return endereco;
}

std::string Conta::getDataCriacao() const {
    return dataCriacao;
}

// Setters
void Conta::setEndereco(const std::string& novoEndereco) {
    endereco = novoEndereco;
}

// Exibição
std::string Conta::toString() const {
    std::stringstream ss;
    ss << "Conta(" << numeroConta << ", " << endereco << ")";
    return ss.str();
}