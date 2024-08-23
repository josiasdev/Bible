1. Compile o Servidor:
g++ -o Executaveis/executavel_servidor Servidor/servidor.cpp Servidor/main.cpp -lcurl

2. Inicie o Servidor
sudo ./Executaveis/executavel_servidor

3. Compile a parte do cliente:
g++ -o Executaveis/executavel_cliente Cliente/cliente.cpp Cliente/main.cpp -lcurl

4. Execute a parte do cliente:
sudo ./Executaveis/executavel_cliente
