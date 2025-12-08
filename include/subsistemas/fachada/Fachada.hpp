#ifndef FACHADA_HPP
#define FACHADA_HPP

#include "../usuarios/UsuarioService.hpp"
#include "../monitoramento/ProcessadorOCR.hpp"
#include "../monitoramento/ProcessadorSegmentacao.hpp"

#include <string>
#include <memory>

class Fachada {
public:
    // Construtor
    Fachada();

    // INTERFACE SIMPLIFICADA PARA USUÁRIOS
    bool criarUsuario(const std::string& cpf, const std::string& nome, const std::string& email);
    Usuario* obterUsuario(const std::string& cpf);
    bool atualizarUsuario(const std::string& cpf, const std::string& email);
    std::vector<Usuario> listarUsuarios();

    // INTERFACE SIMPLIFICADA PARA CONTAS 
    bool criarConta(const std::string& numeroConta, const std::string& cpfTitular, const std::string& endereco);
    Conta* obterConta(const std::string& numeroConta);
    std::vector<Conta> listarContasPorUsuario(const std::string& cpfTitular);

    // INTERFACE SIMPLIFICADA PARA HIDRÔMETROS 
    bool criarHidrometro(const std::string& numeroHidrometro, const std::string& numeroConta);
    Hidrometro* obterHidrometro(const std::string& numeroHidrometro);
    std::vector<Hidrometro> listarHidrometrosPorConta(const std::string& numeroConta);

    // INTERFACE SIMPLIFICADA PARA MONITORAMENTO DE IMAGENS
    double processarImagemOCR(const std::string& caminhoImagem);
    double processarImagemSegmentacao(const std::string& caminhoImagem);

    // TESTES 
    void testar();

private:
    UsuarioService usuarioService;
};

#endif
