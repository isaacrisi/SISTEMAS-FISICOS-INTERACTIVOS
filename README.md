## Nombre del equipo
Menos -1

## Integrantes
- Simara Villasmil - 000509719
- Isaac Pineda - 000509927

### ¿Qué sucedio al cambiar el 100 por el 500?
El led en vez de apagar y prenderse bastante rápido, tenía pausas más alargadas entre estar prendido y entre estar apagado. Es decir, los lapsos de prender y apagarse se alargaron.

# Documentación | Ejercicio 5
El núcleo Arduino-Pico es un conjunto de herramientas y bibliotecas desarrollado por la comunidad para programar la placa Raspberry Pi Pico (RP2040) utilizando el entorno de Arduino. Está diseñado para hacer más fácil y divertido el uso de estas placas, integrándolas en el ecosistema de Arduino.

Este núcleo utiliza un conjunto de herramientas personalizado que incluye GCC 10.3 y Newlib 4.0.0, y no requiere la instalación de software adicional en tu sistema.

### Raspberry Pi Pico

La **Raspberry Pi Pico** es una placa de microcontrolador de bajo costo y alto rendimiento con interfaces digitales flexibles. Sus principales características son:

- **Microcontrolador**: Chip RP2040 diseñado por Raspberry Pi en el Reino Unido.
- **Procesador**: Dual-core Arm Cortex M0+ con un reloj flexible que puede alcanzar hasta 133 MHz.
- **Memoria**: 264kB de SRAM y 2MB de memoria flash a bordo.
- **Conectividad**: USB 1.1 con soporte para dispositivo y host.
- **Modos de bajo consumo**: Soporte para modos de suspensión y dormancia.
- **Programación fácil**: Programación mediante arrastrar y soltar utilizando almacenamiento masivo a través de USB.
- **GPIO**: 26 pines GPIO multifuncionales.
- **Interfaces**: 2 × SPI, 2 × I2C, 2 × UART, 3 × ADC de 12 bits, 16 canales PWM controlables.
- **Otros componentes**: Reloj y temporizador precisos en chip, sensor de temperatura, y bibliotecas de punto flotante aceleradas en chip.
- **Soporte PIO**: 8 máquinas de estado PIO programables para soporte de periféricos personalizados.

La Raspberry Pi Pico viene como un módulo con bordes castellados para soldar directamente a placas portadoras. La variante **Pico H** incluye encabezados pre-soldados y un conector de dep.

# Ejercicio 6
``` C++
void task1()
{
    // Definición de estados y variable de estado
    enum class Task1States
    {
        INIT,
        WAIT_TIMEOUT
    };
    static Task1States task1State = Task1States::INIT;

    // Definición de variables static (conservan su valor entre llamadas a task1)
    static uint32_t lastTime = 0;

    // Constantes
    constexpr uint32_t INTERVAL = 1000;

    // MÁQUINA de ESTADOS
    switch (task1State)
    {
    case Task1States::INIT:
    {
        // Acciones:
        Serial.begin(115200);

        // Garantiza los valores iniciales para el siguiente estado.
        lastTime = millis();
        task1State = Task1States::WAIT_TIMEOUT;

        Serial.print("Task1States::WAIT_TIMEOUT\n");

        break;
    }
    case Task1States::WAIT_TIMEOUT:
    {
        uint32_t currentTime = millis();

        // Evento
        if ((currentTime - lastTime) >= INTERVAL)
        {
            // Acciones:
            lastTime = currentTime;
            Serial.print(currentTime);
            Serial.print('\n');
        }
        break;
    }
    default:
    {
        Serial.println("Error");
    }
    }
}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
```
### ¿Cómo se ejecuta este programa?

El programa define una máquina de estados que se ejecuta dentro de una función llamada `task1()`. Esta función se llama tanto en `setup()` como en `loop()` en el entorno de Arduino, lo que significa que se ejecutará repetidamente durante el tiempo que la placa esté encendida. La máquina de estados tiene dos estados principales: `INIT` y `WAIT_TIMEOUT`.

1. **Estado `INIT`**:
   - Se inicializa la comunicación serial con `Serial.begin(115200)`.
   - Se establece el tiempo inicial `lastTime` usando `millis()`.
   - Se cambia el estado a `WAIT_TIMEOUT` y se imprime el mensaje `"Task1States::WAIT_TIMEOUT\n"` por el puerto serial.
   - Este estado se ejecuta solo una vez.

2. **Estado `WAIT_TIMEOUT`**:
   - En cada iteración del `loop()`, se comprueba si ha transcurrido el intervalo de tiempo definido por `INTERVAL` (1000 ms o 1 segundo).
   - Si ha transcurrido el intervalo, se actualiza `lastTime` y se imprime el valor de `currentTime` en el monitor serie.
   - Este estado se ejecuta repetidamente cada vez que se cumple el intervalo de 1 segundo.

### ¿Pudiste ver este mensaje: `Serial.print("Task1States::WAIT_TIMEOUT\n");`. ¿Por qué crees que ocurre esto?

Este nunca apareció, y no sabemos por qué ya que los estados no parecen definirse en ningún momento antes del `switch`.

### ¿Cuántas veces se ejecuta el código en el case Task1States::INIT?

Una vez.

# Ejercicio 7
Observa la función 
```c++
millis(); 
```
¿Para qué sirve?
Esta devuelve la cantidad de milisegundos que han transcurrido desde que se inicio el programa.


# Ejercicio 8
- Realiza un programa que envíe un mensaje al pasar un segundo, dos segundos y tres segundos. Luego de esto debe volver a comenzar.
```c++
void setup() 
{
  // put your setup code here, to run once:
  const int inter = 0;
}

void loop() {

  uint32_t currentTime = millis();

  if (millis() > currentTime)
  {
    inter++;
  }
  
  if(inter == 1000){
    Serial.print("UNO SECOND"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter == 2000){
    Serial.print("DOS SECONDS"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter == 3000){
    Serial.print("TRES SECONDS"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter > 3000){
    Serial.print("START_OVER"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
    inter = 0;
  }
}
```
Por alguna razón el programa dice que una variable no está declarada -b

En el README.md del repositorio responde:
- ¿Cuáles son los estados del programa?
#### 
No hay ??.

- ¿Cuáles son los eventos?
#### 
Cada que pasa cierta cantidad de segundos se ejecuta uno de los if.

- ¿Cuáles son las acciones?
#### 
Escribir en el monitor serie.

