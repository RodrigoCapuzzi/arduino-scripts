# arduino-scripts

Este repositório faz parte da matéria OBJETOS INTELIGENTES CONECTADOS cursada pelo aluno e demais colegas de grupo na disciplina ANALISE E DESENVOLVIMENTO DE SISTEMAS, ano 2024.2, turma 201825139.000.05B.

Nele, descreveremos os detalhes do nosso projeto Arduino, caso alguém queira reproduzi-lo. 

## Hardware utilizado

Você precisará de:
1. 01 placa Arduino Uno R4 Minima
2. 01 placa breadboard
3. 01 LED RGB
4. 02 Sensores RFID-RC522
5. Wires para conectar os pinos
6. Tags azuis para ler nos sensores

## Softwares necessários

Você precisará instalar os seguintes softwares no seu sistema:

1. Arduino IDE
2. Node JS
3. Node-red
4. MQTT Explorer

## Códigos

Após ter comprado os hardwares listados acima, conectado todos os pinos e baixado os softwares acima listados, é hora de fazer upload do código.

- Voce poderá recriar o nosso fluxo no node-red fazendo upload do arquivo "codigo_node_red.json" no seu no node-red. Isso criará todos os nós e conexões.
- Caso os nós "function1", "function2" e "function3" nao tenha os codigos javascript listado dentro deles, você poderá achá-los nos aquivos Javascript correspondente nesse repositório.
- Por fim, copie e cole o "codiog_arduino.ino" em uma nova sketch no Arduino IDE, compile e faça upload.
- E pronto, voçê pode agora começar a ler suas tags e fazer o controle do seu estoque!
