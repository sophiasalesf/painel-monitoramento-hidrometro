#include "../../../include/subsistemas/usuarios/Usuario.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

// Construtor padrão
Usuario::Usuario() 
    : cpf(""), nome(""), email(""), ativo(true), perfil("usuario"), dataCriacao("") 
{}

// Construtor com 3 parâmetros (SEM senha)
Usuario::Usuario(const std::string& cpf, const std::string& nome, const std::string& email)
    : cpf(cpf), nome(nome), email(email), ativo(true), perfil("usuario"), senha("") {
    time_t agora = time(nullptr);
    dataCriacao = std::to_string(agora);
}

// Construtor com 4 parâmetros (COM senha) ← ADICIONAR ESTE
Usuario::Usuario(const std::string& cpf, const std::string& nome, const std::string& email, const std::string& senha)
    : cpf(cpf), nome(nome), email(email), ativo(true), perfil("usuario"), senha(senha) {
    time_t agora = time(nullptr);
    dataCriacao = std::to_string(agora);
}

// Getters
std::string Usuario::getCpf() const {
    return cpf;
}

std::string Usuario::getNome() const {
    return nome;
}

std::string Usuario::getEmail() const {
    return email;
}

std::string Usuario::getPerfil() const {
    return perfil;
}

bool Usuario::getAtivo() const {
    return ativo;
}

std::string Usuario::getDataCriacao() const {
    return dataCriacao;
}

std::vector<std::string> Usuario::getContas() const {
    return contas;
}

std::string Usuario::getSenha() const {
    return senha;
}

// Setters
void Usuario::setEmail(const std::string& novoEmail) {
    email = novoEmail;
}

void Usuario::setPerfil(const std::string& novoPerfil) {
    perfil = novoPerfil;
}

void Usuario::setAtivo(bool novoStatus) {
    ativo = novoStatus;
}

void Usuario::setSenha(const std::string& novaSenha) {
    senha = novaSenha;
}

// Gerenciar contas
void Usuario::adicionarConta(const std::string& numeroConta) {
    contas.push_back(numeroConta);
}

void Usuario::removerConta(const std::string& numeroConta) {
    auto it = std::find(contas.begin(), contas.end(), numeroConta);
    if (it != contas.end()) {
        contas.erase(it);
    }
}

// Exibição
std::string Usuario::toString() const {
    std::stringstream ss;
    ss << "Usuario(" << cpf << ", " << nome << ", " << contas.size() << " contas)";
    return ss.str();
}