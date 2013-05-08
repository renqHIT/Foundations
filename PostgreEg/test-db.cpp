#include <iostream>
#include <libpq-fe.h>

using namespace std;

int main()
{
        const char *conninfo;
        PGconn     *conn;   //PostgreSQL Connection
        PGresult   *res;

        conninfo = "dbname = renq-db user = renq";

        //CONNECT TO DATABASE
        conn = PQconnectdb(conninfo);

        if(PQstatus(conn) != CONNECTION_OK)
        {
                cout << "Connection to database failed: " << PQerrorMessage(conn) << endl;
        }
        else
                cout << "Connection success :)" << endl;

	char query[1000];

	sprintf(query,"CREATE TABLE Graph1(graphID int4, attrName varchar, attrType char(1))");
        //DO SOME SQL
        res = PQexec(conn,query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
                cout <<  "create failed :( \n" << PQerrorMessage(conn);
                PQclear(res);
        }
	else
		cout << " create graph1 success :) " << endl;

	for (int i = 0; i < 10; i++)
	{
		sprintf(query,"INSERT INTO Graph1(graphID, attrName, attrType) VALUES (%d, \'age\', \'i\')", i);
		res = PQexec(conn,query);
		if(PQresultStatus(res) != PGRES_COMMAND_OK)
		{
			cout << "insert failed :(\n" << PQerrorMessage(conn);
			PQclear(res);
		}
		else 
			cout << "insert " << i << " success :)" << endl;
	}

	sprintf(query, "SELECT (graphID, attrName, attrType) FROM Graph1");
	res = PQexec(conn,query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		cout << "SELECT failed :( \n" << PQerrorMessage(conn);
		PQclear(res);
	}
	else
		cout << "select graph1 sucess :) " << endl;

	int nFields = PQnfields(res);
	for (int i = 0; i < nFields; i++)
	{
		cout << PQfname(res, i) << '\t';
	}
	cout << endl;

	int nTuples = PQntuples(res);
	for (int i = 0; i< nTuples; i++)
	{
		for (int j = 0; j < nFields; j++)
		{
			cout << PQgetvalue(res, i, j) << '\t';
		}
		cout << endl;
	}

        //RELEASE RESOURCE
        PQfinish(conn);

        return 0;
}

