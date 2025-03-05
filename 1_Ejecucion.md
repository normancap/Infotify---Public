#---------------------------------GUIA DE EJECUCION DEL PROGRAMA---------------------------------

Para poder probar el programa se debe hacer mediante la terminal, yo uso la de linux pero cualquier terminar que pueda compilar c esta bien.

#Ejecutar servidor

1.1-	Abre una terminal y navega hasta la carpeta del servidor.


1.2-	Ejecuta el comando make sin cambiar de directorio. Esto generará una carpeta bin que contendrá el ejecutable.


1.3-	Sin moverte de directorio, ejecuta el servidor con: "./bin/serv".

	El programa pedirá que ingreses un número de puerto para que el servidor escuche conexiones.

	Introduce cualquier puerto disponible y el servidor quedará a la espera de conexiones entrantes.



#Ejecutar cliente


2.1-	Abre otra terminal y navega hasta la carpeta del cliente.


2.2-	Ejecuta make sin cambiar de directorio. Esto generará la carpeta bin con el ejecutable del cliente.


2.3-	Sin moverte de directorio, ejecuta el cliente con: "./bin/client". Se solicitará ingresar un número de puerto y una dirección IP.

	-El número de puerto debe ser el mismo que se utilizó en el servidor.

	-La dirección IP debe corresponder a la computadora donde está corriendo el servidor. Si ambos programas se ejecutan en la misma máquina, usa 127.0.0.1

	Una vez ingresados estos datos, el cliente se conectará al servidor y la comunicación entre ambos estará establecida.
