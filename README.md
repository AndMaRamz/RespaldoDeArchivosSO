# RespaldoDeArchivosSO
Proyecto de respaldo de archivos para la materia de sistemas operativos.

## Sobre el proyecto
El proyecto fue desarrollado para la materia de Sistemas Operativos, consiste en un programa que permite realizar el respaldo a profundidad de un directorio
a otra localización cualquiera dentro del mismo ordenador, para ello se pasan ambos argumentos mediante terminal al momento de la ejecución del programa.

## Documentación
La documentación correspondiente a este proyecto se puede encontrar en:
[Documentación](https://docs.google.com/document/d/1u6vL572ZWJtVGFvS3nItcwSYZpw3dbUuBqgfSAUmGtg/)

## Previos
> [!Important]
> Es necesario revisar que la instalación de GNU gcc y de make haya sido realizada.

- Desde Ubuntu (o distribuciones basadas en Fedora)
> sudo apt install make

- Desde Fedora (o distribuciones basadas en RedHat)
> sudo dnf install make

- Desde Arch (o distribuciones basadas en Manjaro)
> sudo pacman -S make

- Desde MacOS
> brew install gcc make

- Desde Windows
> choco install mingw make

## Compilar y ejecutar
Para generar el archivo ejecutable basta con ejecutar el siguiente comando desde la raíz del proyecto:
> make

Para poder ejecutar debe llamarse a programa y pasar como argumentos en orden, primero el directorio de origen y después el directorio de destino del respaldo:
> ./programa path/to/source path/to/destiny

## Colaboradores
- **[Andrea Mata](https://github.com/AndMaRamz)**
- **[Brayan Téllez](https://github.com/BrayanTCc83)**