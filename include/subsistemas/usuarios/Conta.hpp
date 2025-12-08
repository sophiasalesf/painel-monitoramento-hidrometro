#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>
#include <ctime>

class Conta 
{
public:
    // Construtores
    Conta();
    Conta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco);

    // Getters
    std::string getNumeroConta() const;
    std::string getCpfTitular() const;
    std::string getEndereco() const;
    std::string getDataCriacao() const;

    // Setters
    void setEndereco(const std::string& novoEndereco);

    // Exibição
    std::string toString() const;

private:
    std::string numeroConta;
    std::string cpfTitular;
    std::string endereco;
    std::string dataCriacao;
};

#endif