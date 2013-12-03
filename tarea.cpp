/*
* Integrantes:Paula Lineros
*             David Martinez
* */
/* Se debe agregar la libreria libpq-fe.h */


#include <iostream>
#include "libpq-fe.h">

using namespace std;

int main(int argc, char *argv[])
{
    PGconn *cnn = NULL;
    PGresult *res = NULL;

    int i;
    cnn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");

    if (PQstatus(cnn) != CONNECTION_BAD) 
    {
        cout << "\tConexion Establecida" << endl;
        res = PQexec(cnn,"SELECT curso_id, AVG(nota) as Ranking FROM asignaturas_cursadas where curso_id = (SELECT curso_id, docente_id as Docente FROM cursos GROUP BY docente_id)");

        if (res != NULL) 
        {
            int filas = PQntuples(res);
            int columnas = PQnfields(res);

            cout << "Columnas" << endl << endl;

            for (i=0; i<columnas; i++) {
                cout << PQfname(res,i) << "\t\t|\t\t";
            }

            cout << endl;


            for (i=0; i<filas; i++) {
                for (int j=0; j<columnas; j++) {
                    cout << PQgetvalue(res,i,j) << "\t\t\t";
                }
                cout << endl;
            }
        }

        PQclear(res);

    } else {
        cout << "Error de conexion" << endl;
        return 0;
    }

    PQfinish(cnn);

    return 0;
}
