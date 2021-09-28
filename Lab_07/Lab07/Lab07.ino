
// Libraries
#include <SPI.h>
#include <SD.h>

// Define variable
File root;
char option = '0';
uint8_t control = 0;
char inByte;

// Prototypes
void printDirectory(File dir, int numTabs);
void readText(char dir);

void setup()
{
  // Iniciar comunicacion serial y esperar a que el puerto respoda:
  Serial.begin(9600); // baudRate 
  SPI.setModule(0); //esto indica que puertos se van a usar

  Serial.print("Initializing SD card...\n");

  pinMode(PA_3, OUTPUT);  // Se define como output

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  }
  Serial.println("Initialization suceed...");
  Serial.println("Wiring is correct and a card is present.");

}

void loop()
{
  if (control == 0) {
    root = SD.open("/");
    printDirectory(root, 0);
    Serial.println("\n Write the option you want to see... ");
    Serial.println(" Option 1 : Rebellion");
    Serial.println(" Option 2 : Yoshi");
    Serial.println(" Option 3 : DarthVader");
    control++; //al aumentar el valor de control se asegura que el mensaje de menu no aparesca hasta que se halla seleccionado
  }             //una option.
  if (Serial.available()) {
    inByte = Serial.read();//se guarda el valor enviado por serial
  }
  if (inByte == '1') {//si el valor recibido es un 1
    option = '1'; //se coloca un 1 a la option 
    control--; //se coloca en 0 control para que se muestre el menu
  }
  if (inByte == '2') {//misma logica que cuando se recibe un 1
    option = '2';
    control--;
  }
  if (inByte == '3') {//misma logica que cuando se recibe un 1
    option = '3';
    control--;
  }
  readText(option);
  option = '0'; //se asegura que option siempre sea 0 para evitar que se muestre valores no deseados
}

void readText(char dir) {
  uint8_t seleccion;
  File archivo;
  switch (dir) {//Se abre el archivo dependiendo del valor que tenga la variable option 
    case '1':
      archivo = SD.open("rebell~1.txt");
      seleccion = 1; //habilita la rutina de mostrar el contenido
      break;
    case '2':
      archivo = SD.open("yoshi.txt");
      seleccion = 1;
      break;
    case '3':
      archivo = SD.open("vader.txt");
      seleccion = 1;
      break;
    default:
      seleccion = 0;//inhabilita la rutina de mostrar el contenido
      break;
  }
  if (seleccion == 1) {//rutina que sirve para mostrar la informacion guardada en el archivo seleccionado
    if (archivo) {
      Serial.println(archivo.name());

      // read from the file until there's nothing else in it:
      while (archivo.available()) {
        Serial.write(archivo.read());
      }
      // close the file:
      archivo.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening file...");
    }
  }
}

void printDirectory(File dir, int numTabs) {//en esta rutina se muestra el contenido guardado en la SD
  dir.rewindDirectory();
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
