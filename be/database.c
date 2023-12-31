#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "database.h"

// global variable for connection with the database
PGconn *conn;

// init the connection with db using a predefined connection string
void init_database() {
    const char *conninfo = "dbname=ntdb user=jd password=jd hostaddr=127.0.0.1 port=5432";
    conn = PQconnectdb(conninfo);
    
    // checks if the connection to the db was successful
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);  // Exits the program in case of an error.
    }
}

// closes the connection with the db and releases the allocated resources
void close_database() {
    PQfinish(conn);
}

// fetches data from the db and returns 0 in case of success and -1 in case of error
int fetch_data_from_db() {
    PGresult *res;
    res = PQexec(conn, "SELECT * FROM your_table_name");

    // checks if the query was successful
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return -1;  // Error while reading.
    }
    
    // in this part you might process the query results ..
    // TODO

    PQclear(res);
    return 0;  // success.
}

// inserts data into db and returns 0 in case of success and -1 in case of error
int insert_data_to_db(const char *data) {
    PGresult *res;
    char query[512];
    
    sprintf(query, "INSERT INTO your_table_name (column_name) VALUES ('%s')", data);
    res = PQexec(conn, query);

    // checks if the query was successful
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        return -1;  // error while inserting
    }

    PQclear(res);
    return 0;  // success
}

// updates data in the database by a given ID and returns 0 in case of success and -1 in case of error
int update_data_in_db(int id, const char *updated_data) {
    PGresult *res;
    char query[512];
    
    sprintf(query, "UPDATE your_table_name SET column_name = '%s' WHERE id = %d", updated_data, id);
    res = PQexec(conn, query);

    // checks if the query was successful
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        return -1;  // error while updating
    }

    PQclear(res);
    return 0;  // success
}

// deletes data from the database by a given ID and returns 0 in case of success and -1 in case of error
int delete_data_from_db(int id) {
    PGresult *res;
    char query[256];

    sprintf(query, "DELETE FROM your_table_name WHERE id = %d", id);
    res = PQexec(conn, query);

    // checks if the query was successful
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        return -1;  // error while deleting
    }

    PQclear(res);
    return 0;  // success
}

// void do_exit(PGconn *conn, PGresult *res)
// {
//     if (res != NULL)
//     {
//         PQclear(res);
//     }

//     if (conn != NULL)
//     {
//         PQfinish(conn);
//     }
//     exit(1);
// }

// void connection_db_test(int _id)
// {
//     // DB connect
//     PGconn *conn = PQconnectdb("user=user1 dbname=DBname host=host1");
//     PGresult *res = NULL;

//     // Error handling
//     if (PGstatus(conn) == CONNECTION_BAD)
//     {
//         fprintf(stderr, "Connection has failed. %s\n", PQerrorMessage(conn));
//         do_exit(conn, NULL);
//     }

//     const char *paramValues[1];
//     char id_str[12];

//     paramValues[0] = id_str;

//     // Query call
//     res = PQexecParams(conn, "SELECT * FROM tablename WHERE id = $1", 1, NULL, paramValues, NULL, NULL, 0);

//     if (PQresultStatus(res) != PGRES_TUPLES_OK)
//     {
//         printf("No data found.\n");
//         do_exit(conn, res);
//     }

//     int rows = PQntuples(res);

//     for (int i = 0; i < rows; i++)
//     {
//         printf("%s\n", PQgetvalue(res, i, 0));
//     }

//     PQclear(res);
//     PQclear(conn);
// }


// void do_exit(PGconn *conn, PGresult *res) {
//     if (res != NULL) {
//         PQclear(res);
//     }

//     if (conn != NULL) {
//         PQfinish(conn);
//     }

//     exit(1);
// }

// void connection_db_test(int _id) {
//     PGconn *conn = PQconnectdb("user=user1 dbname=DBname host=host1");
//     PGresult *res = NULL;

//     if (PQstatus(conn) == CONNECTION_BAD) {
//         fprintf(stderr, "Connection has failed %s\n", PQerrorMessage(conn));
//         do_exit(conn, NULL);
//     }

//     const char *paramValues[1];
//     char id_str[12];
//     snprintf(id_str, sizeof(id_str), "%d", _id);
//     paramValues[0] = id_str;

//     res = PQexecParams(conn, "SELECT * FROM tablename WHERE id = $1", 1, NULL, paramValues, NULL, NULL, 0);

//     if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//         printf("No data found.\n");
//         do_exit(conn, res);
//     }

//     int rows = PQntuples(res);
//     for (int i = 0; i < rows; i++) {
//         printf("%s\n", PQgetvalue(res, i, 0));
//     }

//     PQclear(res);
//     PQfinish(conn);
// }

