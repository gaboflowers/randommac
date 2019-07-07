#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // setuid

/*
 * Aleatoriza la dirección MAC del adaptador especificado.
 * El adaptador se especifica definiendo el macro IFACE.
 *
 * Ejemplo: para aleatorizar la MAC de wlan0
 *      gcc randommac.c -o randommac -DIFACE=wlan0
 *
 * Es necesario correrlo como root, o asignarle el suid 0.
 *
 * Para no necesitar contraseña, después de compilar:
 * > sudo chown root randommac
 * > sudo chmod +x randommac # lo vuelve ejecutable
 * > sudo chmod +s randommac # hereda los permisos del dueño,
 *                           # en vez del usuario que lo ejecuta
 * */

#ifndef IFACE
#define IFACE wlp3s0
#endif

// https://stackoverflow.com/a/2653351
#define STRINGISE(s) #s
#define MACROSTR(s) STRINGISE(s)

int main(int argc, char* args[]) {
    char *cmd = "ip link set " MACROSTR(IFACE) " down;"
                " macchanger -A " MACROSTR(IFACE) ";"
                "ip link set " MACROSTR(IFACE) " up";

    setuid(0); // para ser efectivamente root

    if (cmd) {
        system(cmd);
    }

    return 0;
}
