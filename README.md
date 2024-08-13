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
![image](https://github.com/user-attachments/assets/0ed6bf80-82e6-40d7-b2bd-0ebf591791f9)
1. Analiza el programa. ¿Por qué enviaste la letra con el botón send? ¿Qué evento verifica si ha llegado algo por el puerto serial?
#### 
Porque el botón `send` envía los datos actuales ingresados al puerto serial, y luego el `if (Serial.available() > 0)` verifica si efectivamente se han ingresado datos o no. Si se han ingresado, el valor será mayor a cero y se imprimirá el mensaje.

2. [Abre](https://www.asciitable.com/) esta tabla.
####
3. Analiza los números que se ven debajo de las letras. Nota que luego de la r, abajo, hay un número. ¿Qué es ese número?
#### 
El valor en datos numéricos de cada tecla del teclado.

4. ¿Qué relación encuentras entre las letras y los números?
#### 
Tienen un una especie de orden, siendo el de los números ascendente.

5. ¿Qué es el 0a al final del mensaje y para qué crees que sirva?
#### 
Editando el mensaje, por ahora se podría presumir que representa el `\n`, osea, el salto de línea.

6. Nota que luego de verificar si hay datos en el puerto serial se DEBE HACER UNA LECTURA del puerto. Esto se hace para retirar del puerto el dato que llegó. Si esto no se hace entonces parecerá que siempre tiene un datos disponible en el serial para leer. ¿Tiene sentido esto? Si no es así habla con el profe.
#### 
Digamos que sí -b.

# Ejercicio 12
``` c++
void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial? 
       if (Serial.available() > 0)
        {
            // DEBES leer ese dato, sino se acumula y el buffer de recepción 
            //del serial se llenará.   
		        Serial.read();
            uint32_t var = 0;

            // Almacena en pvar la dirección de var.      
			      uint32_t *pvar = &var;

            // Envía por el serial el contenido de var usando 
           // el apuntador pvar.    
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');

            // ESCRIBE el valor de var usando pvar   
            *pvar = 10;
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');
        }
        break;
    }

    default:
    {
        break;
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
![image](https://github.com/user-attachments/assets/d7e2064e-f1af-449c-ac29-c202209cb98a)
La variable `pvar` se conoce como puntero. Simplemente es una variable en la cual se almacenan direcciones de otras variables. En este caso, en pvar se almacena la dirección de `var`. Nota que debes decirle al compilador el tipo de la variable (uint32_t en este caso) cuya dirección será almacenada en pvar.
Ejecuta el programa. Observa lo que hace. Ahora responde las siguientes preguntas mediante un ejercicio de ingeniería inversa:

- ¿Cómo se declara un puntero?
####
Se declara poniéndole el tipo de variable de la variable a la cual se le almacenará la dirección, de la forma: `tipoDeVariable *pVariableReferente;`. Lo que lo hace un puntero es ponerle el '*', y para identificarlo ponerle la 'p' al inicio.

- ¿Cómo se define un puntero? (cómo se inicializa)
####
Se le pueden asignar otros valores acorde al tipo de variable de `pvar`, igualándolo a dicho valor. Por ejemplo en el caso de que sea un `uint32_t`, se pueden poner números enteros, como sería en: `*pvar = 10;`

- ¿Cómo se obtiene la dirección de una variable?
#### 
Se iguala a la variable a la cual se desea almacenar la dirección, fijándose que ambas tengas el mismo tipo de variable. En este caso se iguala a `var`, quedando de la forma: `*pvar = &var;`.

- ¿Cómo se puede leer el contenido de una variable por medio de un puntero?
#### 
-blank-

- ¿Cómo se puede escribir el contenido de una variable por medio de un puntero?
#### 
-blank-

# Ejercicio 13
Vas a escribir el siguiente programa, pero antes de ejecutarlo vas a tratar de lanzar una HIPÓTESIS de qué hace. Luego lo vas a ejecutar y compararás el resultado con lo que creías. Si el resultado no es el esperado, no deberías seguir al siguiente ejercicio hasta que no experimentes y salgas de la duda.
``` c++
static void changeVar(uint32_t *pdata)
{
    *pdata = 10;
}

static void printVar(uint32_t value)
{
    Serial.print("var content: ");
    Serial.print(value);
    Serial.print('\n');
}

void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial?        
	if (Serial.available() > 0)
        {
            Serial.read();
            uint32_t var = 0;
            uint32_t *pvar = &var;
            printVar(*pvar);
            changeVar(pvar);
            printVar(var);
        }
        break;
    }

    default:
    {
        break;
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
### Hipótesis
-

### Qué hace realmente
-

# Ejercicio 14








