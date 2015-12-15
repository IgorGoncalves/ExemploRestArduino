
## Exemplo de uso aRest e Ethernet

Exemplo de uso da biblioteca aRest para criação de API's e serviços com Arduino. Abaixo, os passos necessários para que o experimento possa ser replicado

### Sensores e componentes

	* Arduino Uno
	* Shield Ethernet
	* Sensor de umidade e Temperatura DHT11
	* Potenciômetro
	* LED Vermelho
	* Servo motor SG90

### Bibliotecas

Todas as bibliotecas aRest e do DHT11 estão na pasta "libs", elas devem ser adicionadas ao seu ambiente para a execução do programa

### Esquema Físico

![Esquema físico](/Fritzing\ Project/ExemploEthernetRest_bb.png)

### Instruções

Para replicar o exemplo é necessário que vc esteja conectado ao seu Arduino na mesma rede, para tal usei um roteador comum onde só estavam conectados a minha máquina e o Arduino.

1. Digite no seu Console/Cmd o comando `ifconfig` (Linux) ou `ipconfig` (Windows) para identificar o IP da sua máquina na rede onde estão conectado.

2. Altere as linhas abaixo no código com o número de IP disponível na rede, o gateway e a máscara da sua rede. Caso tenha dúvidas do que seja cada um, veja esse [link](http://www.portaleducacao.com.br/educacao/artigos/49129/afinal-o-que-e-ip-mascara-gateway-e-dns)

```cpp

	IPAddress ip(192,168,2,10); //Define o endereco IP
	IPAddress gateway(192,168,2,1); //Define o gateway
	IPAddress subnet(255, 255, 255, 0); //Define a máscara de red

```
3. Adicione o código ao seu Arduino e digite o IP do Arduino no seu navegador favorito, a saída deve ser uma arquivo JSON com todas as  informações dos componentes conectados a placa que foram definidos na API. Para visualizar valores de variáveis específicas você deve digitar `http://{SeuIp}/{nomeVariavel}`, para executar funções, digite em seu navegador `http://{SeuIp}/{nomeFuncoes}/{parametros}`

#### Exemplos de requisições da API

-- To Do --
