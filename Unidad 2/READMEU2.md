# U N I D A D  2
_________________________________________________________________________________________________________________________________________________________________________________________
# Ejercicio 1
Estudia con detenimiento el código para el controlador y para el computador. Busca la definición de todas las funciones usadas en la documentación de Arduino y de Microsoft.
- ¿Quién debe comenzar primero la comunicación, el *computador* o el *controlador*? **¿Por qué?**

####
Programa el controlador con este código:
``` c++
void setup() {
  Serial.begin(115200);
}

void loop() {
if(Serial.available()){
if(Serial.read() == '1'){
      Serial.print("Hello from Raspberry Pi Pico");
    }
  }
}
```
- Prueba la aplicación con ScriptCommunicator. **¿Cómo funciona?**

####


En el proyecto de Unity, en un script de C# poner el siugiente código:
``` c++
using UnityEngine;
using System.IO.Ports;
public class Serial : MonoBehaviour
{
private SerialPort _serialPort =new SerialPort();
private byte[] buffer =new byte[32];

void Start()
    {
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

void Update()
    {

				if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = {0x31};// or byte[] data = {'1'};            
						_serialPort.Write(data,0,1);
            Debug.Log("Send Data");
        }

				if (Input.GetKeyDown(KeyCode.B))
        {
						if (_serialPort.BytesToRead >= 16)
            {
                _serialPort.Read(buffer, 0, 20);
                Debug.Log("Receive Data");
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            }
        }

    }
}
```
Analiza:
- ¿Por qué es importante considerar las propiedades *PortName* y *BaudRate*?

####
- ¿Qué relación tienen las propiedades anteriores con el controlador?


# Ejercicio 2




