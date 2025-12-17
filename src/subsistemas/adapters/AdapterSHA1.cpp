#include "../../../include/subsistemas/adapters/AdapterSHA1.hpp"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

AdapterSHA1::AdapterSHA1(const std::string& pastaSaida)
    : pastaSaida(pastaSaida) {
    std::cout << "[ADAPTER SHA1] Inicializado com pasta: " << pastaSaida << std::endl;
}

std::string AdapterSHA1::obterImagemMaisRecente() {
    if (!verificarDisponibilidade()) {
        std::cerr << "[ADAPTER SHA1] Pasta de saida nao disponivel: " << pastaSaida << std::endl;
        return "";
    }

    fs::file_time_type tempoMaisRecente;
    std::string imagemMaisRecente = "";
    bool encontrouImagem = false;

    try {
        // Percorre todos os arquivos na pasta
        for (const auto& entrada : fs::directory_iterator(pastaSaida)) {
            if (entrada.is_regular_file() && ehArquivoImagem(entrada.path().filename().string())) {
                auto tempoModificacao = fs::last_write_time(entrada);
                
                if (!encontrouImagem || tempoModificacao > tempoMaisRecente) {
                    tempoMaisRecente = tempoModificacao;
                    imagemMaisRecente = entrada.path().string();
                    encontrouImagem = true;
                }
            }
        }

        if (encontrouImagem) {
            std::cout << "[ADAPTER SHA1] Imagem mais recente encontrada: " << imagemMaisRecente << std::endl;
            return imagemMaisRecente;
        } else {
            std::cerr << "[ADAPTER SHA1] Nenhuma imagem encontrada na pasta." << std::endl;
            return "";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ADAPTER SHA1] Erro ao acessar pasta: " << e.what() << std::endl;
        return "";
    }
}

bool AdapterSHA1::verificarDisponibilidade() {
    if (!fs::exists(pastaSaida)) {
        std::cerr << "[ADAPTER SHA1] Pasta nao existe: " << pastaSaida << std::endl;
        return false;
    }

    if (!fs::is_directory(pastaSaida)) {
        std::cerr << "[ADAPTER SHA1] Caminho nao e um diretorio: " << pastaSaida << std::endl;
        return false;
    }

    return true;
}

std::string AdapterSHA1::obterInformacoes() const {
    return "SHA1 - Simulador de Pedro (branch de Sophia)\n"
           "Pasta de saida: " + pastaSaida;
}

bool AdapterSHA1::ehArquivoImagem(const std::string& nomeArquivo) const {
    std::string extensao = nomeArquivo.substr(nomeArquivo.find_last_of(".") + 1);
    
    // Converter para minúsculas
    std::transform(extensao.begin(), extensao.end(), extensao.begin(), ::tolower);
    
    return (extensao == "jpg" || extensao == "jpeg" || extensao == "png" || extensao == "bmp");
}

double AdapterSHA1::lerValorDoArquivo(const std::string& caminhoImagem) {
    // Troca extensão .bmp por .txt
    std::string caminhoTxt = caminhoImagem;
    size_t pos = caminhoTxt.find_last_of(".");
    if (pos != std::string::npos) {
        caminhoTxt = caminhoTxt.substr(0, pos) + ".txt";
    }
    
    // Tenta abrir o arquivo .txt
    std::ifstream arquivo(caminhoTxt);
    if (!arquivo.is_open()) {
        std::cout << "[ADAPTER SHA1] ERRO: Arquivo .txt nao encontrado: " << caminhoTxt << "\n";
        return 0.0;
    }
    
    double valor;
    arquivo >> valor;
    arquivo.close();
    
    std::cout << "[ADAPTER SHA1] Valor lido do arquivo: " << std::fixed << std::setprecision(3) << valor << " m^3\n";
    return valor;
}