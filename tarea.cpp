/*
* Integrantes:Paula Lineros
*             David Martinez
* */

#include <iostream>
#include <postgresql/libpq-fe>

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
        res = PQexec(cnn,"SELECT  curso_id, AVG(nota)as ranking FROM asignaturas_cursadas where curso_id = (SELECT curso_id FROM cursos GROUP BY docente_id)");

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
