#include "../../../include/subsistemas/adapters/AdapterSHA2.hpp"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

AdapterSHA2::AdapterSHA2(const std::string& pastaSaida)
    : pastaSaida(pastaSaida) {
    std::cout << "[ADAPTER SHA2] Inicializado com pasta: " << pastaSaida << std::endl;
}

std::string AdapterSHA2::obterImagemMaisRecente() {
    if (!verificarDisponibilidade()) {
        std::cerr << "[ADAPTER SHA2] Pasta de saida nao disponivel: " << pastaSaida << std::endl;
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
            std::cout << "[ADAPTER SHA2] Imagem mais recente encontrada: " << imagemMaisRecente << std::endl;
            return imagemMaisRecente;
        } else {
            std::cerr << "[ADAPTER SHA2] Nenhuma imagem encontrada na pasta." << std::endl;
            return "";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ADAPTER SHA2] Erro ao acessar pasta: " << e.what() << std::endl;
        return "";
    }
}

bool AdapterSHA2::verificarDisponibilidade() {
    if (!fs::exists(pastaSaida)) {
        std::cerr << "[ADAPTER SHA2] Pasta nao existe: " << pastaSaida << std::endl;
        return false;
    }

    if (!fs::is_directory(pastaSaida)) {
        std::cerr << "[ADAPTER SHA2] Caminho nao e um diretorio: " << pastaSaida << std::endl;
        return false;
    }

    return true;
}

std::string AdapterSHA2::obterInformacoes() const {
    return "SHA2 - Simulador de Ligia (branch de Ayrton)\n"
           "Pasta de saida: " + pastaSaida;
}

bool AdapterSHA2::ehArquivoImagem(const std::string& nomeArquivo) const {
    std::string extensao = nomeArquivo.substr(nomeArquivo.find_last_of(".") + 1);
    // Converter para minusculas
    std::transform(extensao.begin(), extensao.end(), extensao.begin(), ::tolower);
    // SHA da Ligia gera PNG, mas mantem compatibilidade com outros formatos se necessario
    return (extensao == "png" || extensao == "jpg" || extensao == "jpeg" || extensao == "bmp");
}

double AdapterSHA2::lerValorDoArquivo(const std::string& caminhoImagem) {
    // Extrai apenas o nome do arquivo a partir do caminho
    fs::path caminho(caminhoImagem);
    std::string nomeArquivo = caminho.filename().string();

    std::cout << "[ADAPTER SHA2] Processando arquivo de imagem: " << nomeArquivo << std::endl;

    // Verifica se eh PNG
    std::string extensao = nomeArquivo.substr(nomeArquivo.find_last_of(".") + 1);
    std::transform(extensao.begin(), extensao.end(), extensao.begin(), ::tolower);
    if (extensao != "png") {
        std::cout << "[ADAPTER SHA2] AVISO: Extensao esperada .png, encontrado: ." 
                  << extensao << ". Tentando ler mesmo assim.\n";
    }

    // Encontra ultimo '_' no nome do arquivo
    size_t posUnderscore = nomeArquivo.find_last_of('_');
    size_t posPonto = nomeArquivo.find_last_of('.');

    if (posUnderscore == std::string::npos || posPonto == std::string::npos || posUnderscore >= posPonto) {
        std::cout << "[ADAPTER SHA2] ERRO: Nao foi possivel extrair valor do nome do arquivo: "
                  << nomeArquivo << "\n";
        return 0.0;
    }

    std::string valorStr = nomeArquivo.substr(posUnderscore + 1, posPonto - posUnderscore - 1);

    std::cout << "[ADAPTER SHA2] Valor extraido do nome do arquivo (string): " << valorStr << "\n";

    // Converte string para double
    std::stringstream ss(valorStr);
    double valor = 0.0;
    ss >> valor;

    if (ss.fail()) {
        std::cout << "[ADAPTER SHA2] ERRO: Falha ao converter valor '" << valorStr << "' para double.\n";
        return 0.0;
    }

    std::cout << "[ADAPTER SHA2] Valor convertido: " << std::fixed << std::setprecision(3)
              << valor << " m^3\n";

    return valor;
}