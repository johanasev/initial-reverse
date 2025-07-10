# Autoría
- Johana Liseth Sevillano Herrera
- Angie Paola Yarce Gómez
- Angi Sirley Hoyos RUíz

# Enlace al video


# Initial reverse

**Initial Reverse** es una aplicación escrita en lenguaje **C** que invierte el orden de las líneas de un archivo de texto. 
El resultado se puede mostrar en consola o guardar en un archivo. 
Además, el proyecto incluye una **interfaz gráfica (GUI) con GTK** para facilitar su uso sin necesidad de terminal.

---

## Funcionalidad principal

El programa realiza las siguientes operaciones:

✅ Lee un archivo de texto línea por línea  
✅ Usa memoria dinámica con `malloc`, `getline` y `strdup`  
✅ Invierte el orden de las líneas  
✅ Muestra el resultado en consola o lo guarda en otro archivo  
✅ Informa si el archivo está vacío o no existe  
✅ Tiene una interfaz gráfica amigable con GTK

---

## 📦 Estructura del proyecto

initial_reverse/
├── main.c // Lógica del programa en consola
├── gui.c // Interfaz gráfica con GTK
├── Makefile // Automatiza compilación y ejecución
├── input.txt // Archivo de prueba
└── README.md // Este archivo

## Requisitos

- Sistema operativo: Linux (o WSL en Windows)
- Compilador: `gcc`
- GTK 3 para interfaz gráfica:

```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev
```

---

## 📦 Compilación
Compilar versión de consola: make
Compilar interfaz gráfica (GTK): make gui

## ▶️ Ejecución
Consola: ./initial_reverse input.txt
Guardar archivo de salida: ./initial_reverse input.txt -o salida.txt

## 🖼️ Interfaz Gráfica (GTK)
Ejecutar: ./gui_reverse

## Funciones de C utilizadas
fopen(), fclose() → manejo de archivos

getline() → lectura dinámica de líneas

malloc(), realloc(), free() → gestión de memoria

strdup() → duplicación segura de cadenas

fprintf() → impresión a consola o archivo

strcmp(), strcat(), strlen() → manejo de strings

## ✅ Validaciones incluidas
❌ Archivo de entrada inexistente → mensaje de error

⚠️ Archivo vacío → advertencia

✔ Guardado exitoso → mensaje de confirmación

GUI con mensajes gráficos y flujo controlado

### 📄 Documentación del proyecto

Puedes acceder a la propuesta, cronograma, avances, pruebas y documentación completa del trabajo en el siguiente enlace de Google Drive:

📂 [Ver carpeta en Google Drive](https://drive.google.com/drive/folders/1MXlgtsiB3nULAIhtrBrFd5WAwmQYrtf0?usp=sharing)




