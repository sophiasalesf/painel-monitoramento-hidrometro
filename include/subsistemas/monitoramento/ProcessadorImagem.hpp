#ifndef PROCESSADOR_IMAGEM_HPP
#define PROCESSADOR_IMAGEM_HPP

#include <string>

class ProcessadorImagem {
public:
    ProcessadorImagem(const std::string& caminho);
    virtual ~ProcessadorImagem() = default;
    
    double processar();

protected:
    std::string caminhoImagem;
    
    virtual void carregarImagem() = 0;
    virtual void preprocessar() = 0;
    virtual void detectarDigitos() = 0;
    virtual double interpretarValor() = 0;
};

#endif
