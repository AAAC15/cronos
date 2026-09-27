# Definición de variables
CC = gcc
CFLAGS = -Wall -Wextra -O3
TARGET = cronos
NAME = reloj con aneurisma

# Rutas de instalación estándar en Linux
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = $(PREFIX)/share/cronos

all: $(TARGET)

$(TARGET): cronos.c
	$(CC) $(CFLAGS) cronos.c -o $(TARGET)

install: all
	# Creamos los directorios de destino si no existen
	install -d $(DESTDIR)$(BINDIR)
	install -d $(DESTDIR)$(DATADIR)/layout
	
	# Copiamos el binario ejecutable
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	
	# Copiamos los archivos de diseño/fuentes
	install -m 644 layout/*.cf $(DESTDIR)$(DATADIR)/layout/

uninstall:
	# Eliminamos el binario y los archivos compartidos
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -rf $(DESTDIR)$(DATADIR)

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean