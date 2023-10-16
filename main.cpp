#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File file;
File imageFile; // Un único objeto File para lectura y escritura
#define SD_CHIP_SELECT  5
String imageText = ""; // Variable para almacenar el texto de la imagen
bool creatingImage = false; // Variable para rastrear si estamos creando una imagen

void setup() {
  Serial.begin(115200);
  pinMode(SD_CHIP_SELECT, OUTPUT);
  while (!Serial) {
    ;
  }

  Serial.println("Bienvenido al Menú");
  Serial.println("Seleccione una opción:");
  Serial.println("1. Abrir archivo 1: Mario Bros");
  Serial.println("2. Abrir archivo 2");
  Serial.println("3. Abrir archivo 3");
  Serial.println("4. Crear y guardar una imagen");

  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("No se pudo inicializar la tarjeta SD.");
    return;
  }
}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();
    switch (opcion) {
      case '1':
        Serial.println("Seleccionó la Opción 1 - Abriendo archivo 1");
        abrirYMostrarArchivo("/ascii-art.txt");
        break;
      case '2':
        Serial.println("Seleccionó la Opción 2 - Abriendo archivo 2");
        abrirYMostrarArchivo("/ascii-art (1).txt");
        break;
      case '3':
        Serial.println("Seleccionó la Opción 3 - Abriendo archivo 3");
        abrirYMostrarArchivo("/ascii-art (2).txt");
        break;
      case '4':
        Serial.println("Seleccionó la Opción 4 - Crear y guardar una imagen");
        crearYGuardarImagen();
        break;
      default:
        if (creatingImage) {
          imageText += opcion; // Agregar el carácter al texto de la imagen en curso
        } else {
          Serial.println("Opción no válida. Por favor, seleccione 1, 2, 3 o 4.");
        }
        break;
    }
  }

  if (creatingImage && imageText.endsWith("guardar\n")) {
    imageText.trim(); // Eliminar la cadena "GUARDAR\n" del texto de la imagen
    if (imageFile) {
      imageFile.print(imageText);
      imageFile.close();
      Serial.println("Imagen guardada.");
      creatingImage = false;
      imageText = "";
    } else {
      Serial.println("Error al guardar la imagen.");
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
  Serial.println("Ingrese el texto de la imagen. Para guardar, ingrese 'guardar'.");
  creatingImage = true;
  imageFile = SD.open("imagen.txt", FILE_WRITE);
}
