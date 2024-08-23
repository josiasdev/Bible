# Projeto de Pesquisa de Versículos Bíblicos com Sockets em C++

Este projeto consiste em um sistema de cliente-servidor que permite a pesquisa de versículos bíblicos utilizando sockets em C++. O servidor faz requisições ao site [Biblia Online](https://www.bibliaonline.com.br/) para obter os versículos solicitados pelo cliente.

## Pré-requisitos

Antes de começar, certifique-se de ter o seguinte instalado:

- **g++** (compilador C++)
- **libcurl** (biblioteca para requisições HTTP)
  
### Instalando o g++ e a libcurl no Ubuntu
```
sudo apt-get update
sudo apt-get install g++
sudo apt-get install libcurl4-openssl-dev
```

### Compilação e Execução
Passos para compilar e executar o servidor
#### 1. Compile o Servidor:
Execute o seguinte comando para compilar o servidor:
```
g++ -o Executaveis/executavel_servidor Servidor/servidor.cpp Servidor/main.cpp -lcurl
```
#### 2. Inicie o Servidor:
Inicie o servidor com o comando:
```
sudo ./Executaveis/executavel_servidor
```
### Passos para compilar e executar o cliente
#### 3. Compile a parte do cliente:
Execute o seguinte comando para compilar o cliente:
```
g++ -o Executaveis/executavel_cliente Cliente/cliente.cpp Cliente/main.cpp -lcurl
```
#### 4. Execute a parte do cliente:
Inicie o cliente com o comando:
```
sudo ./Executaveis/executavel_cliente
```
## Estrutura do Projeto
A estrutura básica do projeto é a seguinte:
```
├── Executaveis
│   ├──  executavel_servidor
│   ├──  executavel_cliente
├── Servidor
│   ├──  servidor.cpp
│   ├──  servidor.h
│   ├──  main.cpp
├── Cliente
│   ├──  cliente.cpp
│   ├──  cliente.h
│   ├──  main.cpp
```
## Exemplo de Uso
Após iniciar o servidor e o cliente, você pode realizar pesquisas de versículos bíblicos através do cliente. Por exemplo, digite João 3:16 no cliente e ele retornará o versículo correspondente.

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE). Sinta-se à vontade para usar, modificar e distribuir o código, desde que os avisos de copyright e a licença sejam mantidos.






