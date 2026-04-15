#define BIT3 3
unsigned char status;

status = 0b00110101;      // Paso 0 valor inicial
status = status | 0xFA;   // Paso 1 OR pone en 1 los bits donde cualquiera de los dos operandos tiene un 1.
/* status : 0 0 1 1 0 1 0 1   (53)
  0xFA   : 1 1 1 1 1 0 1 0   (250)
  OR (|) : 1 1 1 1 1 1 1 1   = 0xFF = 255*/

status = status & 20;     // Paso 2 AND conserva solo los bits que son 1 en ambos operandos. 20 = 00010100.
status |= (1 << 6);       // Paso 3 → Poner en 1 el bit 6
status &= ~(1 << BIT3);   // Paso 4 → Poner en 0 el bit 3
status |= (1 << BIT3);    // Paso 5 → Poner en 1 el bit 3

if (status & (1 << 4))   // ¿El bit 4 es 1?
    printf("bit 4 está en 1\n");

unsigned char upper = status & 0xF0;
// 0xF0 = 11110000 → conserva bit7..bit4, borra bit3..bit0