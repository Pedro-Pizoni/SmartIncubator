# **Smart Incubator – Aplicação Qt para Controle de Incubadora**

**Universidade de Passo Fundo (UPF)**  
 **Aluno: Pedro Augusto Pizoni Freitas (202379)**  
 **Professor: Dr. Marcos José Brusso**  
 **Disciplina: Laboratório de Programação III**

---

## **Descrição**

Este projeto consiste em um sistema para **monitoramento e controle inteligente de temperatura e umidade** em uma incubadora experimental.  
 A aplicação foi desenvolvida utilizando **Qt6 (C++), CMake e Arduino**, permitindo comunicação em tempo real com o microcontrolador e apresentando as leituras de forma clara na interface gráfica.

Funções principais:

* Leitura em tempo real de **temperatura (°C)** e **umidade relativa (%)**

* Registro automático das medições em arquivo local

* Exibição do histórico completo em uma janela dedicada

* Definição de **temperatura alvo**

* Detecção automática da porta serial do Arduino

* Interface Qt organizada e modular (Janela Principal, Sobre, Histórico)

---

## **Arquitetura do Sistema**

### **Arduino (Back-end)**

Responsável por:

* Ler dados do sensor DHT

Enviar dados no formato:

 `TEMP:xx.x;HUM:yy.y`

*   
* Receber temperatura alvo (controle futuro)

### **Aplicação Qt (Front-end)**

Componentes principais:

* `MainWindow` – interface principal

* `SerialComm` – comunicação serial

* `DataStorage` – gravação/leitura de histórico

* `HistoryDialog` – janela de histórico

* `AboutDialog` – informações do projeto

* `IncubatorController` – lógica de controle

---

## **Ambiente de Desenvolvimento**

Requisitos:

* Qt6 (Qt Widgets \+ SerialPort)

* CMake ≥ 3.16

* GCC/G++

* Qt Creator (recomendado)

Instalação no Linux:

`sudo apt update && sudo apt upgrade -y`  
`sudo apt install qtcreator cmake qt6-base-dev qt6-serialport-dev -y`

---

## **Como Executar a Aplicação Qt**

1. Clonar o repositório:

`git clone https://github.com/Pedro-Pizoni/SmartIncubator.git`  
`cd SmartIncubator`

2. Compilar com CMake:

`mkdir build`  
`cd build`  
`cmake ..`  
`make -j4`

3. Executar:

`./smartincubator`

---

## **Sistema Operacional Utilizado**

* Kali Linux Rolling

---

## **Autor**

**Pedro Augusto Pizoni Freitas (202379)**  
 Estudante de Engenharia da Computação – UPF  
 GitHub: [https://github.com/Pedro-Pizoni](https://github.com/Pedro-Pizoni)
 ---

##**Licença**

**Este projeto está licenciado sob a Licença MIT.**
Você pode usar, modificar, distribuir e adaptar este software livremente para fins acadêmicos, pessoais ou comerciais.
O texto completo da licença pode ser encontrado no arquivo:

`./LICENSE`
