#include "user.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define SERVER_IP "127.0.0.1"  // Endereço IP do servidor
#define SERVER_PORT 8080       // Porta do servidor

int sock = 0;

void User::connectToServer() {
    struct sockaddr_in serv_addr;
    
    // Criar socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Erro ao criar o socket" << std::endl;
        return;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    
    // Converter endereço IP para formato binário
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Endereço inválido" << std::endl;
        return;
    }
    
    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Conexão falhou" << std::endl;
        return;
    }
}

void User::sendRequestToServer(const std::string& request) {
    // Enviar a requisição ao servidor
    send(sock, request.c_str(), request.length(), 0);
}

std::string User::receiveResponseFromServer() {
    char buffer[1024] = {0};
    
    // Receber a resposta do servidor
    int bytesRead = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        std::cerr << "Erro ao receber a resposta do servidor" << std::endl;
    }
    
    // Fechar o socket após receber a resposta
    close(sock);
    
    return std::string(buffer);
}

void User::searchVerse(const std::string& verse, const std::string& translation) {
    connectToServer();
    
    std::string request = verse + ";" + translation; // Monta a requisição
    sendRequestToServer(request);
    
    std::string response = receiveResponseFromServer();
    std::cout << "Resultado: " << response << std::endl;
}
