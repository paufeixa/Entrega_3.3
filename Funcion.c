#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	char nombre[20];
	printf ("Dame el nombre de un jugador\n"); 
	scanf ("%s", nombre);
	
	char consulta [80];
	strcpy (consulta,"SELECT DISTINCT Partida.ganador FROM Jugador,Partida,Historial WHERE Jugador.nombre = '");
	strcat (consulta, nombre);
	strcat (consulta,"'AND Jugador.id = Historial.idJ AND Historial.idP = Partida.id AND Jugador.nombre!=Partida.ganador");
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf ("Los que han ganado a %s son:\n", nombre);
		while (row !=NULL) {
			printf ("%s\n", row[0]);
			row = mysql_fetch_row (resultado);
	}
		
		mysql_close (conn);
		exit(0);
}
