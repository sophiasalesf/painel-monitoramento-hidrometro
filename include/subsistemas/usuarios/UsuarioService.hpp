#ifndef USUARIOSERVICE_HPP
#define USUARIOSERVICE_HPP

#include "Usuario.hpp"
#include "Conta.hpp"
#include "Hidrometro.hpp"
#include <map>
#include <vector>
#include <memory>

class UsuarioService 
{
public:
    // Construtor
    UsuarioService();

    // CRUD Usuários
    bool criarUsuario(const std::string& cpf, const std::string& nome, const std::string& email);
    Usuario* obterUsuario(const std::string& cpf);
    bool atualizarUsuario(const std::string& cpf, const std::string& email);
    bool deletarUsuario(const std::string& cpf);
    std::vector<Usuario> listarUsuarios();

    // CRUD Contas
    bool criarConta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco);
    Conta* obterConta(const std::string& numeroConta);
    std::vector<Conta> listarContasPorUsuario(const std::string& cpfTitular);
    bool deletarConta(const std::string& numeroConta);

    // CRUD Hidrômetros
    bool criarHidrometro(const std::string& numeroHidrometro, const std::string& numeroConta);
    Hidrometro* obterHidrometro(const std::string& numeroHidrometro);
    std::vector<Hidrometro> listarHidrometrosPorConta(const std::string& numeroConta);
    bool deletarHidrometro(const std::string& numeroHidrometro);

    // Verificações
    bool usuarioExiste(const std::string& cpf);
    bool contaExiste(const std::string& numeroConta);
    bool hidrometroExiste(const std::string& numeroHidrometro);

private:
    std::map<std::string, Usuario> usuarios;  // Chave: CPF
    std::map<std::string, Conta> contas;      // Chave: Número da conta
    std::map<std::string, Hidrometro> hidrometros;  // Chave: Número do hidrômetro
};

#endif