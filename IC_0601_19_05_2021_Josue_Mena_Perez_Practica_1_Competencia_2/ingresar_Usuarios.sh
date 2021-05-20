#!/bin/bash
ROOT_UID=0
SUCCESS=0

# Run as root, of course. (this might not be necessary, because we have to run the script somehow with root anyway)
if [ "$UID" -ne "$ROOT_UID" ]
then
  echo "Se debe estar como root para ejecutar este script"
  exit $E_NOTROOT
fi  

file=$1

if [ "${file}X" = "X" ];
then
   echo "Debe indicar el archivo del listado con Nombres de usuario a ingresar..."
   exit 1
fi

# Del archivo con el listado de grupos a ingresar:
# Este es el formato:
# ejemplo
#    |   
#    f1  
#$f1 = nombreGrupo

crearUsuario(){
	#echo "----> Crear Usuario <----"
	#eval nombreUsuario="$1"
	#echo "nombreUsuario 		  = ${nombreUsuario}"
	#echo "-------------------------"
	eval username="$1"		#Almacena el nombre del usuario.
	eval password="$2"		#Almacena la contraseña del usuario.
	eval UserID="$3"		#Almacena el ID del usuario.
	eval GroupID="$4"		#Almacena el ID del grupo en el que se crea el usuario.
	eval UserIDinf="$5"		#Almacena la información del ID.
	eval HomeDir="$6"		#Dirección de la carpeta que se creará
	eval ComandSell="$7"		#Indica que debe usar shell Bash
	
	#Comprobar grupos buscando en /etc/group
	#El usuario sera creado solo si existe el grupo en que se creará.
	if grep -q ${GroupID} /etc/group
	then 
		echo -e "\n------------------Creando-Usuario------------------"
		echo -e "El grupo [${GroupID}] ya existe"
		#Comprobar usuarios buscando en /etc/passwd
		if grep -q ${username} /etc/passwd 
		then 
		  echo "**********************Warning**********************"
		  echo -e "\tEl Usuario [${username}] ya existe."
		  echo "---------------------------------------------------"
		else 
		  echo -e "\tNuevo usuario [${username}] ¡Creado!." 
		  #-u Valor numérico de identificación del usuario.
		  #-c Cadena de texto.
		  #-s Nombre del shell de inicio de sesión del usuario.
		  #-g Nombre o número del grupo de inicio de sesión inicial del usuario.
		  #-m -d Crea un usuario con un directorio específico.	  
		  useradd -u "${UserID}" -c "${UserIDinf}" -s "${ComandSell}" -g "${GroupID}" -m -d "${HomeDir}" "${username}"
		  #Indica la contraseña que se le asignará al usuario
		  echo "${username}:${password}" | chpasswd --md5
		  
		  echo "***************************************************"
		fi
	else
		#Imprime un mensaje en dado caso que el grupo no exista y no deja crear el usuario.
		echo -e "\n**********************Warning**********************"
		echo -e "El grupo [${GroupID}] no existe."
		echo -e "\tNo se ha podido crear el usuario [${username}]."
		echo "---------------------------------------------------"
	fi
}

while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do
	crearUsuario "\${f1}" "\${f2}" "\${f3}" "\${f4}" "\${f5}" "\${f6}" "\${f7}"
done < ${file}

exit
