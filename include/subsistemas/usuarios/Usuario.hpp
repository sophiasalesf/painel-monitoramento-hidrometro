#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include <ctime>

class Usuario 
{
public:
    // Construtores
    Usuario();
    Usuario(const std::string& cpf, const std::string& nome, const std::string& email);

    // Getters
    std::string getCpf() const;
    std::string getNome() const;
    std::string getEmail() const;
    std::string getPerfil() const;
    bool getAtivo() const;
    std::string getDataCriacao() const;
    std::vector<std::string> getContas() const;

    // Setters
    void setEmail(const std::string& novoEmail);
    void setPerfil(const std::string& novoPerfil);
    void setAtivo(bool novoStatus);

    // Gerenciar contas
    void adicionarConta(const std::string& numeroConta);
    void removerConta(const std::string& numeroConta);

    // Exibição
    std::string toString() const;

private:
    std::string cpf;
    std::string nome;
    std::string email;
    std::string perfil;
    std::string dataCriacao;
    std::vector<std::string> contas;
    bool ativo;
};

#endif
