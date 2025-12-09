#include "../../../include/subsistemas/usuarios/UsuarioService.hpp"
#include <iostream>
#include <algorithm>

// Construtor
UsuarioService::UsuarioService() 
{}

// CRUD USUÁRIOS 
bool UsuarioService::criarUsuario(const std::string& cpf, const std::string& nome, const std::string& email) {
    if (usuarioExiste(cpf)) {
        std::cerr << "[USUARIOSERVICE] Erro: Usuario com CPF " << cpf << " ja existe!" << std::endl;
        return false;
    }
    
    Usuario novoUsuario(cpf, nome, email);
    usuarios[cpf] = novoUsuario;
    std::cout << "[USUARIOSERVICE] Usuario criado: " << novoUsuario.toString() << std::endl;
    return true;
}

Usuario* UsuarioService::obterUsuario(const std::string& cpf) {
    auto it = usuarios.find(cpf);
    if (it != usuarios.end()) {
        return &(it->second);
    }
    std::cerr << "[USUARIOSERVICE] Usuario com CPF " << cpf << " nao encontrado!" << std::endl;
    return nullptr;
}

bool UsuarioService::atualizarUsuario(const std::string& cpf, const std::string& email) {
    auto it = usuarios.find(cpf);
    if (it != usuarios.end()) {
        it->second.setEmail(email);
        std::cout << "[USUARIOSERVICE] Usuario atualizado!" << std::endl;
        return true;
    }
    std::cerr << "[USUARIOSERVICE] Usuario com CPF " << cpf << " nao encontrado!" << std::endl;
    return false;
}

bool UsuarioService::deletarUsuario(const std::string& cpf) {
    auto it = usuarios.find(cpf);
    if (it != usuarios.end()) {
        usuarios.erase(it);
        std::cout << "[USUARIOSERVICE] Usuario deletado!" << std::endl;
        return true;
    }
    std::cerr << "[USUARIOSERVICE] Usuario com CPF " << cpf << " nao encontrado!" << std::endl;
    return false;
}

std::vector<Usuario> UsuarioService::listarUsuarios() {
    std::vector<Usuario> lista;
    for (auto& par : usuarios) {
        lista.push_back(par.second);
    }
    return lista;
}

// CRUD CONTAS 
bool UsuarioService::criarConta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco) {
    if (!usuarioExiste(cpfTitular)) {
        std::cerr << "[USUARIOSERVICE] Erro: Usuario com CPF " << cpfTitular << " nao encontrado!" << std::endl;
        return false;
    }

    if (contaExiste(numeroConta)) {
        std::cerr << "[USUARIOSERVICE] Erro: Conta " << numeroConta << " ja existe!" << std::endl;
        return false;
    }

    Conta novaConta(numeroConta, cpfTitular, endereco);
    contas[numeroConta] = novaConta;
    usuarios[cpfTitular].adicionarConta(numeroConta);
    std::cout << "[USUARIOSERVICE] Conta criada: " << novaConta.toString() << std::endl;
    return true;
}

Conta* UsuarioService::obterConta(const std::string& numeroConta) {
    auto it = contas.find(numeroConta);
    if (it != contas.end()) {
        return &(it->second);
    }
    std::cerr << "[USUARIOSERVICE] Conta " << numeroConta << " nao encontrada!" << std::endl;
    return nullptr;
}

std::vector<Conta> UsuarioService::listarContasPorUsuario(const std::string& cpfTitular) {
    std::vector<Conta> lista;
    auto it = usuarios.find(cpfTitular);
    if (it != usuarios.end()) {
        for (const auto& numeroConta : it->second.getContas()) {
            auto contaIt = contas.find(numeroConta);
            if (contaIt != contas.end()) {
                lista.push_back(contaIt->second);
            }
        }
    }
    return lista;
}

bool UsuarioService::deletarConta(const std::string& numeroConta) {
    auto it = contas.find(numeroConta);
    if (it != contas.end()) {
        std::string cpfTitular = it->second.getCpfTitular();
        contas.erase(it);
        
        auto usuarioIt = usuarios.find(cpfTitular);
        if (usuarioIt != usuarios.end()) {
            usuarioIt->second.removerConta(numeroConta);
        }
        std::cout << "[USUARIOSERVICE] Conta deletada!" << std::endl;
        return true;
    }
    std::cerr << "[USUARIOSERVICE] Conta " << numeroConta << " nao encontrada!" << std::endl;
    return false;
}
// CRUD HIDRÔMETROS 

bool UsuarioService::criarHidrometro(const std::string& numeroHidrometro, const std::string& numeroConta) {
    if (!contaExiste(numeroConta)) {
        std::cerr << "[USUARIOSERVICE] Erro: Conta " << numeroConta << " nao encontrada!" << std::endl;
        return false;
    }

    if (hidrometroExiste(numeroHidrometro)) {
        std::cerr << "[USUARIOSERVICE] Erro: Hidrometro " << numeroHidrometro << " ja existe!" << std::endl;
        return false;
    }

    Hidrometro novoHidrometro(numeroHidrometro, 0.0);
    hidrometros[numeroHidrometro] = novoHidrometro;
    std::cout << "[USUARIOSERVICE] Hidrometro criado: Hidrometro(" << numeroHidrometro << ", Leitura: 0 m3)" << std::endl;
    return true;
}

Hidrometro* UsuarioService::obterHidrometro(const std::string& numeroHidrometro) {
    auto it = hidrometros.find(numeroHidrometro);
    if (it != hidrometros.end()) {
        return &(it->second);
    }
    std::cerr << "[USUARIOSERVICE] Hidrometro " << numeroHidrometro << " nao encontrado!" << std::endl;
    return nullptr;
}

std::vector<Hidrometro> UsuarioService::listarHidrometrosPorConta(const std::string& /*numeroConta*/) {
    std::vector<Hidrometro> lista;
    for (auto& par : hidrometros) {
        lista.push_back(par.second);
    }
    return lista;
}

bool UsuarioService::deletarHidrometro(const std::string& numeroHidrometro) {
    auto it = hidrometros.find(numeroHidrometro);
    if (it != hidrometros.end()) {
        hidrometros.erase(it);
        std::cout << "[USUARIOSERVICE] Hidrometro deletado!" << std::endl;
        return true;
    }
    std::cerr << "[USUARIOSERVICE] Hidrometro " << numeroHidrometro << " nao encontrado!" << std::endl;
    return false;
}

// VERIFICAÇÕES 
bool UsuarioService::usuarioExiste(const std::string& cpf) {
    return usuarios.find(cpf) != usuarios.end();
}

bool UsuarioService::contaExiste(const std::string& numeroConta) {
    return contas.find(numeroConta) != contas.end();
}

bool UsuarioService::hidrometroExiste(const std::string& numeroHidrometro) {
    return hidrometros.find(numeroHidrometro) != hidrometros.end();
}