# Infotify---Public
El proyecto infotify es una aplicación de downloading de audio, la cual contará de una arquitectura cliente-servidor, en la cual el servidor tomará un archivo de audio seleccionado previamente por el cliente y se lo enviará a través de una conexión de internet.

---------------------GUIA DE USO-----------------------
Para poder porbar el programa se debe hacer mediante la terminal, yo uso la de linux pero cualquier terminar que pueda compilar c esta bien

1.0-	Entramos a la carpeta del servidor y parados dentro de esa carpeta abrimos una terminal.
1.1-	Siguiente a eso ejecutamos el comando "make" sin moverse de directorio. Entonces sera visible una carpeta bin que contendra el ejecutable
1.2-	Aun sin movernos de directorio, corremos el ejecutable que esta dentro de la carpeta bin de la siguiente forma "./bin/serv". Y nos mostrara que debemos indicar un nro de puerto para que el servidor escuche. Le ponen el nro de puerto que quieran y ya estaria levantado el servidor quedando a la escucha de conexiones

Para hacer correr el cliente es basicamente lo mismo

2.0-	Entramos a la carpeta del cliente y abrimos una terminal
2.1-	En esa posicion ejecutamos el make y entonces veremos la carpeta bin del ejecutable del cliente
2.2-	Aun sin movernos de directorio corremos el ejecutable de la siguiente forma "./bin/client" y nos mostrara que debemos ingresar un nro puerto y una dir IP para conectarnos. El nro de puerto tiene que ser el mismo que se puso en el servidor y la dir IP tiene q ser de la computadora donde se levanto el servidor. Si ambos programas se prueban en la misma computadora se pone la IP "127.0.0.1". Se corre el cliente con los datos indicados y el ya estaria levantado el cliente y haria tambien la conexion al servidor


