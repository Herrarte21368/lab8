#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File file;

const int SD_CHIP_SELECT = 5; // Pin CS/SS de la tarjeta SD

//Configuración del menu para el usuario
void setup() {
  Serial.begin(115200);
  Serial.println("Bienvenido al Menú ESP32");
  Serial.println("Seleccione una opción:");
  Serial.println("1. Abrir archivo 1");
  Serial.println("2. Abrir archivo 2");
  Serial.println("3. Abrir archivo 3");
  Serial.println("4. Crear y guardar una imagen");

  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("No se pudo inicializar la tarjeta SD.");
    return;
  }
}

//Dentro del loop de ecnuentra la función para selaccionar la
//opcion y el despliegue de los archivos.
void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();
    switch (opcion) {
      case '1':
        Serial.println("Seleccionó la Opción 1 - Abriendo archivo 1");
        abrirYMostrarArchivo("archivo1.txt");
        break;
      case '2':
        Serial.println("Seleccionó la Opción 2 - Abriendo archivo 2");
        abrirYMostrarArchivo("archivo2.txt");
        break;
      case '3':
        Serial.println("Seleccionó la Opción 3 - Abriendo archivo 3");
        abrirYMostrarArchivo("archivo3.txt");
        break;
      case '4':
        Serial.println("Seleccionó la Opción 4 - Crear y guardar una imagen");
        crearYGuardarImagen();
        break;
      default:
        Serial.println("Opción no válida. Por favor, seleccione 1, 2, 3 o 4.");
        break;
    }
  }
}

void abrirYMostrarArchivo(const char* nombreArchivo) {
  file = SD.open(nombreArchivo);
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.println("Error al abrir el archivo.");
  }
}

void crearYGuardarImagen() {
  Serial.println("Ingrese el contenido de la imagen (termina con una línea en blanco):");

  String contenidoImagen = "";
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        break;
      }
      contenidoImagen += c;
    }
  }

  if (contenidoImagen.length() > 0) {
    String nombreArchivo = "imagen_personalizada.txt";
    file = SD.open(nombreArchivo, FILE_WRITE);
    if (file) {
      file.println(contenidoImagen);
      file.close();
      Serial.println("Imagen guardada como " + nombreArchivo);
    } else {
      Serial.println("Error al guardar la imagen.");
    }
  } else {
    Serial.println("La imagen está vacía y no se guardará.");
  }
}
