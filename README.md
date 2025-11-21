# **Smart Incubator – Qt Application for Incubator Control**

**University of Passo Fundo (UPF)**  
 **Student: Pedro Augusto Pizoni Freitas (202379)**  
 **Professor: Dr. Marcos José Brusso**  
 **Course: Programming Lab III**

---

## **Description**

This project implements a system for **real-time monitoring and intelligent control of temperature and humidity** in an experimental incubation environment.  
 The application was developed using **Qt6 (C++), CMake, and Arduino**, enabling serial communication with the microcontroller and displaying the readings through a clean and intuitive graphical interface.

Main features:

* Real-time temperature (°C) and relative humidity (%) monitoring

* Automatic logging of sensor readings

* Dedicated History window for log visualization

* Adjustable **target temperature**

* Automatic detection of the Arduino serial port

* Modular Qt6 interface (Main Window, History, About)

---

## 

## 

## 

## **System Architecture**

### **Arduino (Back-end)**

Responsibilities:

* Reading values from a DHT sensor

Sending data in the format:

 `TEMP:xx.x;HUM:yy.y`

*   
* Receiving the target temperature (future extension)

### **Qt6 Application (Front-end)**

Main components:

* `MainWindow` – main GUI

* `SerialComm` – serial communication handler

* `DataStorage` – log writing and reading

* `HistoryDialog` – log viewer

* `AboutDialog` – project information

* `IncubatorController` – control logic and automation

---

## **Development Environment**

Requirements:

* Qt6 (Widgets \+ SerialPort modules)

* CMake ≥ 3.16

* GCC/G++ compiler

* Qt Creator (recommended)

Install on Linux:

`sudo apt update && sudo apt upgrade -y`  
`sudo apt install qtcreator cmake qt6-base-dev qt6-serialport-dev -y`

---

## **How to Run the Qt Application**

1. Clone the repository:

`git clone https://github.com/Pedro-Pizoni/SmartIncubator.git`  
`cd SmartIncubator`

2. Build using CMake:

`mkdir build`  
`cd build`  
`cmake ..`  
`make -j4`

3. Run the application:

`./smartincubator`

---

## **Operating System Used**

* Kali Linux Rolling

---

## **Author**

**Pedro Augusto Pizoni Freitas (202379)**  
 Computer Engineering Student – UPF  
 GitHub: [https://github.com/Pedro-Pizoni](https://github.com/Pedro-Pizoni)
 
## **License**
**This project is licensed under the MIT License.**
You are free to use, modify, distribute, and build upon this software for academic, personal, or commercial purposes.
See the full license in the file:

`./LICENSE`

