# Massachusetts
[ABPCE17] Proyecto de videojuego del grupo Hola Mundo Estudio del ABP 2017/18


Lista de comandos de git:

git status
	Devuelve el status de archivos que hayas modificado o creado
git add <archivo>
	Añade a confirmados el archivo mencionado
git add -A
	Añade a confirmados todos los archivos
git add .
	Añade a confirmados todos los archivos nuevos y modificados. No los borrados
git add -u
	Añade a confirmados todos los archivos modificados y borrados. No los nuevos
git commit
	Añades los cambios que hayas hecho
git commit --amend
	Útil para añadir archivos que hayas olvidado poner en el commit, o para cambiar el mensaje de commit
git push
	Actualizas el repositorio con tu último commit
git pull
	Descargas los cambios que se hayan hecho en el repositorio
git reset HEAD <archivo>
	Quita el archivo mencionado del área de preparación, evitando que entre en el próximo commit
git checkout -- <archivo>
	Revierte los cambios del archivo mencionado

Ramas: https://git-scm.com/book/es/v1/Ramificaciones-en-Git-¿Qué-es-una-rama%3F

git branch
	Devuelve una lista de las ramas que hay en el proyecto. Pone un * delante de la rama en la qu te encuentras
git branch <nombre>
	Añade una nueva rama con el nombre dado
git branch -d <nombre>
	Borra una rama de nombre dado
git checkout <nombreRama>
	Salta a la rama mencionada
git checkout -b <nombreRama>
	Creas y saltas a la rama nombreRama
git merge
	Añades a la rama master los cambios hechos en la rama en la que se esta
git merge <nombreRama>
	Fusiona la rama de nombre dado con la rama en la que te encuentras

