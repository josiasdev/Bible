#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <curl/curl.h>  // Biblioteca libcurl para requisições HTTP

#define PORT 8080

// Callback function to handle the data received from the curl request
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Server::start() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Falha ao criar socket" << std::endl;
        return;
    }

    // Configurar o endereço e porta
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Falha ao associar socket ao endereço" << std::endl;
        return;
    }

    // Listen para conexões
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Falha ao escutar" << std::endl;
        return;
    }

    std::cout << "Servidor iniciado. Aguardando conexões..." << std::endl;

    while ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        processClientRequest(client_socket);
        close(client_socket);
    }
}

void Server::processClientRequest(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    std::string request(buffer);
    std::string verse = request.substr(0, request.find(";"));
    std::string translation = request.substr(request.find(";") + 1);

    std::string result = fetchVerse(verse, translation);
    send(client_socket, result.c_str(), result.length(), 0);
}

std::string Server::fetchVerse(const std::string& verse, const std::string& translation) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string extractedVerse;

    curl = curl_easy_init();
    if (curl) {
        // Construir a URL
        std::string url = "https://www.bibliaonline.com.br/" + translation + "/" + verse;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Erro na requisição: " << curl_easy_strerror(res) << std::endl;
            return "Erro ao buscar o versículo";
        }

        // Extração simples de texto
        size_t startPos = readBuffer.find("<div class=\"verse-text\">");
        if (startPos != std::string::npos) {
            startPos += 24; // Tamanho da string "<div class=\"verse-text\">"
            size_t endPos = readBuffer.find("</div>", startPos);
            if (endPos != std::string::npos) {
                extractedVerse = readBuffer.substr(startPos, endPos - startPos);
            } else {
                extractedVerse = "Conteúdo do versículo não encontrado";
            }
        } else {
            extractedVerse = "Versículo não encontrado";
        }
    }
    return extractedVerse;
}
