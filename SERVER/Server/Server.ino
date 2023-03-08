#include <WiFi.h>

//Developed by reycotallo98
//https://github.com/reycotallo98


//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------

const char* ssid     = "WIFISSID";
const char* password = "PASSWORD";

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request


//------------------------CODIGO HTML------------------------------
String pagina = "<!doctype html>"
"<html lang='es'>"
"<head>"
    "<title>JorgeCams</title>" 
    "<meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"
    "<meta http-equiv=”refresh” content='1'>"
    "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"
"</head>"
"<body class='bg-secondary'>"
    "<div class='container bg-dark'>"
        "<h1 class='text-white'>Bienvenido a JorgeCams</h1>"
        "<div class='row'>"
            "<div class='col-11 col-lg-6 col-md-8 col-sm-10 col-xs-11 row'><img class='col-11' src='http://192.168.0.110' >"
                    "<div class='col-7 justify-content-center'>"
                        "<input type='button' value='arriba'>"
                        "<div class='row'>"
                            "<input type='button' value='izquierda' onclick=''>"
                            "<input type='button' value='derecha' onclick=''>"
                        "</div>"
                        "<input type='button' value='abajo' onclick=''>"
                        "<div class='row'>"
                            "<input type='button' value='On' onclick=''>"
                            "<input type='button' value='flash' onclick='flash(110)'>"
                        "</div>"
                    "</div>"
                "</div>"
                "<div class='col-11 col-lg-6 col-md-8 col-sm-10 col-xs-11 row'><img class='col-11' src='http://192.168.0.74'>"
                    "<div class='col-7 justify-content-center'>"
                        "<input type='button' value='arriba'>"
                        "<div class='row'>"
                            "<input type='button' value='izquierda' onclick=''>"
                            "<input type='button' value='derecha' onclick=''>"
                        "</div>"
                        "<input type='button' value='abajo' onclick=''>"
                        "<div class='row'>"
                            "<input type='button' value='On' onclick=''>"
                            "<input type='button' value='flash' onclick='flash(74)'>"
                        "</div>"
                    "</div>"
                "</div>"
        "</div>"
        "</div>"
    "<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"
    "<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"
    "<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"
    "<script type='text/JavaScript'>"
        "function flash(number) {\n"
            "const url = 'http://192.168.0.'+number+'/flash'\n"
            "const http = new XMLHttpRequest()\n"
            "http.open('GET', url)\n"
            "location.reload()\n" 
        "http.send()\n"
        "console.log('ll')}\n"

        "</script>"
"</body>"

"</html>";


//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");
  


  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
      IPAddress ip(192,168,0,90); 
      IPAddress gateway(192,168,1,1); 
      IPAddress subnet(255,255,255,0); 
      WiFi.config(ip, gateway, subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}

//----------------------------LOOP----------------------------------

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            

            
            // Muestra la página web
            client.println(pagina);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}