1. Compile o Servidor:
<br>
g++ -o Executaveis/executavel_servidor Servidor/servidor.cpp Servidor/main.cpp -lcurl

2. Inicie o Servidor:
<br>
sudo ./Executaveis/executavel_servidor

4. Compile a parte do cliente:
<br>
g++ -o Executaveis/executavel_cliente Cliente/cliente.cpp Cliente/main.cpp -lcurl

5. Execute a parte do cliente:
<br>
sudo ./Executaveis/executavel_cliente
