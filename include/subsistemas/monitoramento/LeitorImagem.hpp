#ifndef LEITOR_IMAGEM_HPP
#define LEITOR_IMAGEM_HPP

#include <string>

class LeitorImagem {
    
public:
    LeitorImagem(const std::string& caminho);
    virtual ~LeitorImagem() = default;
    
    virtual double lerValorHidrometro();
    
    std::string getCaminhoImagem() const;

private:
    std::string caminhoImagem;
};

#endif