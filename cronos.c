#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 
    #include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#else 
    #include <unistd.h>
#endif

// cargar fuentes
char fontData[11][4][16]; // matriz de dibujo
void chargeFont(const char* fontName) {
    char globalRoute[512];
    char localRoute[512];
    FILE *file = NULL;

    // Armamos ambas rutas
    snprintf(globalRoute, sizeof(globalRoute), "/usr/local/share/cronos/layout/%s.cf", fontName);
    snprintf(localRoute, sizeof(localRoute), "layout/%s.cf", fontName);

    // Intentar buscar en la ruta global del sistema
    file = fopen(globalRoute, "r");
    
    // si no existe globalmente buscar en la carpeta local
    if (file == NULL) {
        file = fopen(localRoute, "r");
    }

    // Si aun así no se encuentra en ninguna de las dos, tiramos error
    if (file == NULL){
        printf("ERR1: Unknown Font: %s\n  -> Global Route: %s\n  -> Local Route:  %s\n", fontName, globalRoute, localRoute);
        exit(1);
    }
    
    char line[256]; // reservamos espacio para la linea actual
    int currentDigit = -1; // no leimos ningun numero, por lo tanto es -1
    int currentRow = 0; // los dibujos son grillas de 3x4. leemos los 3 de ancho
    
    while(fgets(line, sizeof(line), file)){
        size_t len = strlen(line);
        if (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[len-1] = '\0';
        }
        // si arranca con ''', es encabezado de numero
        if(strncmp(line, "'''", 3) == 0){
            if (strchr(line, ':') != NULL){
                currentDigit = 10;
            } else {
                char *p = line + 3;
                while (*p && (*p < '0' || *p > '9')) p++;
                if (*p >= '0' && *p <= '9') {
                    currentDigit = atoi(p); // convertir string a int
                }
            }
            currentRow = 0; // reiniciamos currentrow
            continue;
        }
        if(currentDigit >= 0 && currentDigit <= 10 && currentRow < 4) {
            strncpy(fontData[currentDigit][currentRow], line, 15); 
            currentRow++;
        }
    }
    fclose(file); 
}
// parseo de comando
void commandParse(int argc, char *argv[], char *fontName, int *useFont) {
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--font") == 0 && i + 1 < argc) {
            strncpy(fontName, argv[i + 1], 255);
            fontName[255] = '\0'; // terminador nulo
            i++; // saltar al nombre de la fuente
        } else if(strcmp(argv[i], "--no-font") == 0) {
            *useFont = 0;            
        } else {
            printf("ERR2: Unknown Flag: RTFM!\n");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]){
    // cargamos la fuente default antes de arrancar el reloj
    char fontName[256] = "classic";
    int useFont = 1; // por default usamos fuente
    
    // llamamos parser pasándole argc y argv
    commandParse(argc, argv, fontName, &useFont);    
    
    // si se usa font, la cargamos
    if (useFont) {
        chargeFont(fontName);
    }
    
    int lastSs = -1; // para recordar el ultimo segundo  
    while(1){
        time_t actualTime; // creamos variable de tiempo
        time(&actualTime); // pedimos tiempo unix
        struct tm *timeInfo = localtime(&actualTime); // formateamos de forma legible
        
        if (timeInfo == NULL) {
            sleep(1);
            continue;
        } 
        
        int actualSs = timeInfo->tm_sec; // segundo actual
        
        // si el ultimo segundo no es igual al actual, printeamos
        if (actualSs != lastSs) {
            lastSs = actualSs; // actualizamos el registro con el nuevo segundo
            
            int actualHh = timeInfo->tm_hour; // hora
            int actualMm = timeInfo->tm_min; // minuto
            
            int tensHh = actualHh / 10; 
            int unitHh = actualHh % 10;
            int tensMm = actualMm / 10;
            int unitMm = actualMm % 10;
            int tensSs = actualSs / 10;
            int unitSs = actualSs % 10;
            
            printf("\033[H\033[J"); // limpiamos pantalla
            // print
            printf("CRONOS CLOCK\n\n");
            
            if (useFont) {
                for (int row = 0; row < 4; row++) {
                    printf("%s  %s  %s  %s  %s  %s  %s  %s\n", 
                        fontData[tensHh][row],
                        fontData[unitHh][row],
                        fontData[10][row],
                        fontData[tensMm][row],
                        fontData[unitMm][row],
                        fontData[10][row],
                        fontData[tensSs][row],
                        fontData[unitSs][row]
                    );
                }
            } else {
                // modo texto plano si usaron --no-font
                printf("%02d:%02d:%02d\n", actualHh, actualMm, actualSs);
            }
            
            printf("\n");
        }
        
        // Pausa ligera de 50ms: consume 0% de CPU y chequea el segundo al instante
        #ifdef _WIN32
            Sleep(50);
        #else
            usleep(50000);
        #endif
    }
}