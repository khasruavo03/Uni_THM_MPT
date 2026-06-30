# C to Assembler
---

## Aufgabe 1

```
int add(void) {
 return 1+2+3;
}
```

a.) 
Das Prologue ist ein paar Zeilen am Anfang des Code also am Anfang der Funktion, was das Stack und Register für die Nutzung in der Funktion ermöglicht. Es folgt keine spezifische Befehle, sondern legt die Stack-frames und reserviert den Speicher für lokale Variablen.

b.) Im Code ist es: 
```
    push r28 
    push r29
    in r28,__SP_L__
    in r29,__SP_H__
```
-> Sicherung von Register r28 und r29 und Ladung das Low-Byte und High-Byte auf dem Stack-Pointer

c.) Das Epilogue ist sozusagen eine Wiedserherstellung der Register und Stack die gesichert würden für die Nutzung im Funktion. Es ist am Ende der Funktion. Es setzt alles zurück was das Prolog gemacht hat.

d.) Im Code:

```
    pop r29
    pop r28
    ret
```
-> Wiederherstellung der Register r28 und r29 und springt zurück zur aufrufendem Funtion


##Aufgabe 2

a.) - Der Speicher wird im Stack reserviert (`rcall`)
```
    push r28
    push r29
    rcall .
    rcall .
    rcall .
    in r28,__SP_L__
    in r29,__SP_H__
```
b.) Hier wird zuerst das Low-Byte addiert und das High-Byte inklusive den Carry mit `adc` addiert. Der Grund dafür ist, das der AVR ein 8-Bit-Architektur ist, also ist der Register auch 8-Bit breit. Deshalb muss ein 2 Byte also 16 Bit Wert in zwei Registern geschrieben werden und in 2 Schritten bearbeitet werden.

c.) Y+3 und Y+4

d.) Y+5 und Y+6

e.) Bei -O0 kopiert GCC die Parameter auf den Stack, damit jede Variable einen festen Speicherplatz hat und das Debugging erleichtert wird.


## Aufgabe 3

a.) Der AVR ist eine 8-Bit-Architektur. Da ein Register nur 8 Bit speichern kann, muss ein 16-Bit int in zwei Registern abgelegt werden. Deshalb werden zuerst die Low-Bytes und anschließend die High-Bytes verglichen. Im Gegensatz dazu können viele x86-Prozessoren 16- oder 32-Bit-Werte mit einer einzigen Vergleichsinstruktion (cmp) vergleichen.

b.) Der bedingte Branch brge springt zum else-Zweig, wenn a > b nicht erfüllt ist.

c.) Nachdem der Code im if-Zweig ausgeführt wurde, erfolgt ein unbedingter Sprung über den else-Block hinweg. Dadurch wird der else-Teil übersprungen und das Programm setzt hinter der gesamten if-else-Anweisung fort.


## Aufgabe 4

a.) Der Compiler erkennt, dass die Schleife immer genau 10-mal ausgeführt wird und das Ergebnis immer 10 ist. Deshalb werden die Schleife vollständig entfernt und die Variable a ebenfalls entfernt. Übrig bleibt nur das Laden des Rückgabewerts und der Rücksprung. Es bleiben also 3 Instruktionen für die Berechnung bzw. Rückgabe übrig.

b.) Der Compiler darf optimieren, solange sich das beobachtbare Verhalten des Programms nicht ändert. Da `a` nur innerhalb der Funktion verwendet wird, die Schleife keine Seiteneffekt und das Ergebnis immer `10` ist, kann der Compiler das Ergebnis direkt berechnen und die Schleife entfernen.

c.) Dazu wird die Variable mit dem Schlüsselwort volatile deklariert: `volatile int a = 0;`

`volatile` teilt dem Compiler mit, dass sich der Wert jederzeit ändern kann oder jeder Speicherzugriff wichtig ist. Dadurch dürfen Zugriffe auf die Variable nicht wegoptimiert werden, und die CPU führt die Inkrementierungen tatsächlich Schritt für Schritt aus.