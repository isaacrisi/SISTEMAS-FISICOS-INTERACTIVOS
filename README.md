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
   - Este estado se ejecuta solo una vez ya que no se cambia de estado por el resto del programa.

2. **Estado `WAIT_TIMEOUT`**:
   - En cada iteración del `loop()`, se comprueba si ha transcurrido el intervalo de tiempo definido por `INTERVAL` (1000 ms o 1 segundo).
   - Si ha transcurrido el intervalo, se actualiza `lastTime` y se imprime el valor de `currentTime` en el monitor serie.
   - Este estado se ejecuta repetidamente cada vez que se cumple el intervalo de 1 segundo.

### ¿Pudiste ver este mensaje: `Serial.print("Task1States::WAIT_TIMEOUT\n");`. ¿Por qué crees que ocurre esto?

No, y esto no es porque el mensaje no se haya imprimido. Lo que sucede es que el mensaje se envía tan pronto el programa inicia, es decir, incluso antes que pase el primer segundo, y ya que el monutor serie toca volverlo a abrir cada vez que se vuelve a iniciarlizar el programa, el mensaje se pierde al estar en todo el inicio; solo alcanzándose a ver los mensajes a partir del primer o segundo segundo transcurrido desde que se inicializó el programa.

### ¿Cuántas veces se ejecuta el código en el case Task1States::INIT?

Una vez.

# Ejercicio 7
Observa la función 
```c++
millis(); 
```
¿Para qué sirve?
###
Esta devuelve la cantidad de milisegundos que han transcurrido desde que se inicio el programa.


# Ejercicio 8
Realiza un programa que envíe un mensaje al pasar un segundo, dos segundos y tres segundos. Luego de esto debe volver a comenzar.
```c++
   void mess()
{
    // Definición de estados y variable de estado
    enum class MessSTates
    {
        ONE,
        TWO,
        THREE
    };
    static MessSTates state = MessSTates::ONE;
    static uint32_t previousTime = millis();
    uint32_t currentTime = millis();

    // MÁQUINA de ESTADOS
    switch (state)
    {
    case MessSTates::ONE:
    {
        if ((currentTime - previousTime) >= 1000)
        {
            Serial.print("UNO SECOND"); Serial.print('\n');
            previousTime = currentTime;
            state = MessSTates::TWO;
        }
        break;
    }
    case MessSTates::TWO:
    {
        if ((currentTime - previousTime) >= 1000)
        {
            Serial.print("DOS SECOND"); Serial.print('\n');
            previousTime = currentTime;
            state = MessSTates::THREE;
        }        
        break;
    }
    case MessSTates::THREE:
    {
        if ((currentTime - previousTime) >= 1000)
        {
            Serial.print("TRES SECOND"); Serial.print('\n'); Serial.print('\n');
            previousTime = currentTime;
            state = MessSTates::ONE;
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
    Serial.begin(9600);
}

void loop()
{
    mess();
}
```
En el README.md del repositorio responde:
- ¿Cuáles son los estados del programa?
#### 
   - ONE: Para el mensaje de un segundo, y llamar al estado `TWO`.
   - TWO: Para el mensaje de dos segundos, y llamar el estado `THREE`.
   - THREE: Para el mensaje de tres segundos, y llamar el estado `ONE`, para que sea un bucle.

- ¿Cuáles son los eventos?
#### 
Son los `if` incorporados en cada estado, por los cuales se imprime el mensaje y se reasigna el estado de `state`.

- ¿Cuáles son las acciones?
#### 
`Serial.begin(9600)` son las acciones presentes en el programa.

# Ejercicio 9
Te voy a mostrar el código para la task1 y luego con tu equipo vas a construir las demás tareas. La frecuencia del mensaje será de 1 Hz.

El objetivo es que hagas un programa donde tengas 3 tareas. La tarea 1 enviará un mensaje a 1 Hz., la tarea 2 a 0.5 Hz., la tarea 3 a 0.25 Hz.

Te voy a dejar como ejemplo el programa de una de las tareas. Te queda entonces el reto de realizar las otras tareas. No olvides sincronizar tu repositorio local con el remoto donde está la evaluación.
```c++
void task1(){
    enum class Task1States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task1States task1State = Task1States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task1State){
        case Task1States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task1State = Task1States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task1States::WAIT_FOR_TIMEOUT:{
            // evento 1:            
            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 1Hz\n"); Serial.print('\n');
            }
            break;
        }

        default:{
            break;
        }
    }

}

void task2(){
    enum class Task1States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task1States task1State = Task1States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 500;

    switch(task1State){
        case Task1States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task1State = Task1States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task1States::WAIT_FOR_TIMEOUT:{
            // evento 1:            
            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 0.5Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void task3(){
    enum class Task2States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task2States task2State = Task2States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 250;

    switch(task2State){
        case Task2States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task2State = Task2States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task2States::WAIT_FOR_TIMEOUT:{
            // evento 1:            
            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 0.25Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void setup()
{
    task1(); task2(); task3();
}

void loop()
{
    task1(); task2(); task3();
}
```

# Ejercicio 11









