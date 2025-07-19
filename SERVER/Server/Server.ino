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
String pagina = R"rawliteral(
<!doctype html>
<html lang='es'>
<head>
    <title>JorgeCams</title>
    <meta charset='utf-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>
    <meta http-equiv='refresh' content='1'>
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>
</head>
<body class='bg-secondary'>
    <div class='container py-4'>
        <h1 class='text-white text-center mb-4'>Bienvenido a JorgeCams</h1>
        <div class='row'>
            <div class='col-md-6 mb-4'>
                <div class='card'>
                    <img class='img-fluid' src='http://192.168.0.110'>
                    <div class='card-body text-center'>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>arriba</button>
                        </div>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>izquierda</button>
                            <button class='btn btn-light'>derecha</button>
                        </div>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>abajo</button>
                        </div>
                        <div class='btn-group'>
                            <button class='btn btn-light'>On</button>
                            <button class='btn btn-primary' onclick='flash(110)'>Flash</button>
                        </div>
                    </div>
                </div>
            </div>
            <div class='col-md-6 mb-4'>
                <div class='card'>
                    <img class='img-fluid' src='http://192.168.0.74'>
                    <div class='card-body text-center'>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>arriba</button>
                        </div>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>izquierda</button>
                            <button class='btn btn-light'>derecha</button>
                        </div>
                        <div class='btn-group mb-2'>
                            <button class='btn btn-light'>abajo</button>
                        </div>
                        <div class='btn-group'>
                            <button class='btn btn-light'>On</button>
                            <button class='btn btn-primary' onclick='flash(74)'>Flash</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script>
    function flash(number) {
        const url = 'http://192.168.0.' + number + '/flash';
        const http = new XMLHttpRequest();
        http.open('GET', url);
        http.send();
    }
    </script>
    <script src='https://code.jquery.com/jquery-3.3.1.slim.min.js'></script>
    <script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js'></script>
    <script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js'></script>
</body>

</html>
)rawliteral";


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