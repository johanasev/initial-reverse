# Initial-reverse

Proyecto desarrollado para la materia de **Sistemas Operativos**, basado en el repositorio [OSTEP Projects](https://github.com/remzi-arpacidusseau/ostep-projects).

Este programa implementa una utilidad básica en C que **invierte el contenido de un archivo de texto**, ya sea por caracteres o por líneas. La herramienta se ejecuta desde la línea de comandos y permite comprender el manejo de archivos, buffers y operaciones de entrada/salida a bajo nivel.

---

## Objetivo

Explorar el manejo de archivos en sistemas operativos mediante la implementación de un programa que invierta el contenido de archivos de texto.

---

## Funcionalidad

- Leer un archivo de texto (`input.txt`)
- Opción para invertir:
  - 🔁 Línea por línea (modo texto)
  - 🔁 Carácter por carácter (modo binario)
- Guardar el resultado invertido en un nuevo archivo (`output.txt`)

---

## Ejemplo de uso

```bash
# Compilar
gcc -o reverse reverse.c

# Ejecutar en modo por líneas
./reverse -l input.txt output.txt

# Ejecutar en modo por caracteres
./reverse -c input.txt output.txt

```
### Documentación  
Puedes acceder a la propuesta, cronograma y referencias en la siguiente carpeta:  
📂 [Documentos del proyecto](https://drive.google.com/drive/folders/1rsQ9DA81OBceGEDGNZS5XE2W3fZr1V9J?usp=sharing)


## Integrantes

- Angi Sirley Hoyos
- Angie Yarce
- Johana Sevillano
