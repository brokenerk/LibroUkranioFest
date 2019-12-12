#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "mongoose.h"
#include "MapCreator.h"
#include "Solicitud.h"
#include <iostream>
using namespace std;

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
char* ip_servidorA = new char[16];
int ptoA = 0, ptoB = 0;
char* ip_servidorB = new char[16];

struct file_writer_data {
	FILE *fp;
	size_t bytes_written;
};

static void handle_upload(struct mg_connection *nc, int ev, void *p) {
	clock_t t_ini, t_fin;
    t_ini = clock();

	struct file_writer_data *data = (struct file_writer_data *) nc->user_data;
	struct mg_http_multipart_part *mp = (struct mg_http_multipart_part *) p;

	switch (ev) {
		case MG_EV_HTTP_PART_BEGIN: {
			if (data == NULL) {
				data = (struct file_writer_data *)calloc(1, sizeof(struct file_writer_data));
				data->fp = fopen("temp.txt","wb");
				data->bytes_written = 0;

				if (data->fp == NULL) {
					mg_printf(nc, "%s",
								"HTTP/1.1 500 Failed to open a file\r\n"
								"Content-Length: 0\r\n\r\n");
					nc->flags |= MG_F_SEND_AND_CLOSE;
					free(data);
					return;
				}
				nc->user_data = (void *) data;
				cout << "Iniciando carga..." << endl;
				cout << "Subiendo archivo..." << endl;
			}
			break;
		}
		case MG_EV_HTTP_PART_DATA: {
				if (fwrite(mp->data.p, 1, mp->data.len, data->fp) != mp->data.len) {
					mg_printf(nc, "%s",
								"HTTP/1.1 500 Failed to write to a file\r\n"
								"Content-Length: 0\r\n\r\n");
					nc->flags |= MG_F_SEND_AND_CLOSE;
					return;
				}
				data->bytes_written += mp->data.len;
			break;
		}
		case MG_EV_HTTP_PART_END: {
			cout << "Archivo recibido. Escrito en temp.txt" << endl;
			/*Analisis libro*/
			MapCreator m;
			int totalWords = 0;
    		map<string, int> lectura = m.getMapFromFile("temp.txt");

    		for(auto it = lectura.cbegin(); it != lectura.cend(); it++){
		        totalWords = totalWords + it->second;
		    }
    		cout << "Map generado. Num Palabras leídas: " << totalWords << endl;
    		cout << "Palabras en el map: " << lectura.size() << endl;

    		/*Borrar archivo temporal*/
    		if(remove("temp.txt") == 0)
		    	printf("temp.txt eliminado\n");
		  	else {
				perror("Error");
			}

			int numServidores = 2;
			int reparto = lectura.size() / numServidores;

			/* Se llena para obtener las posiciones */
		    vector<int> posiciones;
		    posiciones.reserve(numServidores);

		    vector<string> direccionesIp;
		    direccionesIp.reserve(numServidores);
		    direccionesIp.push_back(ip_servidorA);
		    direccionesIp.push_back(ip_servidorB);

		    vector<int> puertos;
		    puertos.reserve(numServidores);
		    puertos.push_back(ptoA);
		    puertos.push_back(ptoB);

		    for (int i = 0; i < numServidores ; i++) {
		        posiciones.push_back(reparto * (i + 1));
		        cout << "Reparto: " << reparto * (i + 1) << endl;
		    }

		    //vector<string> cadenas;
		    int z = 0;
		    /* Generar las cadenas */
		    int j = 0;
		    int error = 0;
		    
		    map<string, int> analisis;
		    int ptoAux = 0;
		    char* ip = (char*)calloc(16, sizeof(char));
		    strcpy(ip, direccionesIp[z].c_str());
		    ptoAux = puertos[z];
		    cout << "Enviando a servidor " << z + 1 << endl;
		    Solicitud s;

		    for(auto it2 = lectura.cbegin(); it2 != lectura.cend(); it2++){
		    	int tamP = (it2->first).length();
		    	char* cadenaEnviar = (char*)calloc(tamP, sizeof(char));
		    	strcpy(cadenaEnviar, (it2->first).c_str());
		        s.doOperation(ip, ptoAux, 1, cadenaEnviar, tamP, (int)it2->second);

		        if(j == posiciones[z] - 1) {
		        	cout << "Terminando servidor " << z + 1 << endl;
		    		error = error + s.doOperation(ip, ptoAux, 1, "END+", 4, 0);
		    		if(error == 0){
			        	cout << "Error al cambiar de servidor" << endl;
			        	exit(0);
			        }
			        z++;

			        if(numServidores > 1 and z < numServidores) {
			        	strcpy(ip, "");
		            	strcpy(ip, direccionesIp[z].c_str());
		            	ptoAux = puertos[z];
		            	cout << "Cambiando a servidor " << z + 1 << endl;
			        }
		        }
		        j++;
		    }

		    printf("Errores: %d\n\n", error);
		    int correctos = totalWords - error;
			double porcentaje = ((double)correctos / (double)totalWords) * 100.0;
			printf("Porcentaje: %.2f\n\n", porcentaje);
    		t_fin = clock();

			double time = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
			mg_printf(nc,
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/plain\r\n"
					"Connection: close\r\n\r\n"
					"%.2f %.2f\n", (double) porcentaje, (double)time);
			nc->flags |= MG_F_SEND_AND_CLOSE;
			fclose(data->fp);
			free(data);
			nc->user_data = NULL;
			cout << "Archivo analizado. Resultados enviados." << endl;
			break;
		}
	}
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	if (ev == MG_EV_HTTP_REQUEST) {
		mg_serve_http(nc, (struct http_message *)ev_data, s_http_server_opts);
	}
}

int main(int argc, char *argv[]){
	if(argc != 5){
		printf("Forma de uso: %s ip_servidorA ptoA servidorB ptoB\n", argv[0]);
		exit(0);
	}
	struct mg_mgr mgr;
	struct mg_connection *c;
	strcpy(ip_servidorA, argv[1]);
	ptoA = atoi(argv[2]);
	strcpy(ip_servidorB, argv[3]);
	ptoB = atoi(argv[4]);

	mg_mgr_init(&mgr, NULL);
	c = mg_bind(&mgr, s_http_port, ev_handler);
	if (c == NULL) {
		fprintf(stderr, "Cannot start server on port %s\n", s_http_port);
		exit(EXIT_FAILURE);
	}

	s_http_server_opts.document_root = ".";  // Serve current directory
	mg_register_http_endpoint(c, "/upload", handle_upload MG_UD_ARG(NULL));

	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(c);

	printf("Servidor web iniciado en http://localhost:%s\n", s_http_port);
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);

	return 0;
}