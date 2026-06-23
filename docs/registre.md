# Les registres x86-64

Avant de programmer en assembleur, il faut comprendre que les registres sont simplement des **petites mémoires ultra-rapides** situées directement dans le processeur.

Ils servent à :

- stocker des variables
- passer les arguments d'une fonction
- retourner une valeur
- effectuer les calculs

---

# La famille des registres

Chaque registre 64 bits peut être découpé en plusieurs sous-registres.

Exemple avec **RAX** :

```
                     64 bits
+---------------------------------------------------------------+
|                           RAX                                 |
+---------------------------------------------------------------+

                 32 bits
                 +-------------------------------+
                 |              EAX              |
                 +-------------------------------+

                        16 bits
                        +-------------+
                        |     AX      |
                        +-------------+

                      8 bits    8 bits
                    +------+ +------+
                    |  AH  | |  AL  |
                    +------+ +------+
```

---

# Les tailles

| Nom | Taille |
|------|---------|
| AL | 8 bits |
| AH | 8 bits |
| AX | 16 bits |
| EAX | 32 bits |
| RAX | 64 bits |

---

# Le registre RAX

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| AL | 8 bits |
| AH | 8 bits |
| AX | 16 bits |
| EAX | 32 bits |
| RAX | 64 bits |

## Utilisation

- Valeur de retour d'une fonction
- Calculs
- Multiplication / Division

### Exemple

```asm
mov rax, 42
ret
```

Retourne :

```c
return 42;
```

---

# RBX

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| BL | 8 bits |
| BH | 8 bits |
| BX | 16 bits |
| EBX | 32 bits |
| RBX | 64 bits |

## Utilisation

Registre général.

Particularité :

Le registre doit être restauré lorsqu'une fonction le modifie (callee-saved).

---

# RCX

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| CL | 8 bits |
| CH | 8 bits |
| CX | 16 bits |
| ECX | 32 bits |
| RCX | 64 bits |

## Utilisation

Très souvent utilisé comme :

- compteur
- index

Exemple :

```c
for (i = 0; i < n; i++)
```

↓

```asm
xor rcx, rcx
```

---

# RDX

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| DL | 8 bits |
| DH | 8 bits |
| DX | 16 bits |
| EDX | 32 bits |
| RDX | 64 bits |

## Utilisation

- troisième argument
- registre temporaire
- multiplication / division

Dans Libasm on l'utilise souvent :

```asm
mov dl, [rsi]
```

---

# RSI

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| SIL | 8 bits |
| SI | 16 bits |
| ESI | 32 bits |
| RSI | 64 bits |

## Utilisation

Deuxième argument d'une fonction.

Très souvent :

```text
source
```

Exemple

```c
strcpy(dest, src);
```

↓

```
RSI = src
```

---

# RDI

## Taille

64 bits

## Sous-registres

| Registre | Taille |
|----------|---------|
| DIL | 8 bits |
| DI | 16 bits |
| EDI | 32 bits |
| RDI | 64 bits |

## Utilisation

Premier argument d'une fonction.

Très souvent :

```
destination
```

Exemple

```c
strcpy(dest, src);
```

↓

```
RDI = dest
```

---

# RBP

Base Pointer.

Permet de retrouver facilement les variables locales.

Nous le verrons lorsque nous étudierons la pile.

---

# RSP

Stack Pointer.

Pointe toujours vers le sommet de la pile.

Très important pour :

- call
- ret
- push
- pop

---

# RIP

Instruction Pointer.

Il contient l'adresse de l'instruction actuellement exécutée.

Le processeur fait :

```
RIP

↓

instruction

↓

instruction suivante

↓

instruction suivante
```

---

# RFLAGS

Registre contenant les flags.

Les plus utilisés :

| Flag | Signification |
|-------|---------------|
| ZF | Zero Flag |
| CF | Carry Flag |
| OF | Overflow Flag |
| SF | Sign Flag |

Pour l'instant, seul **ZF** nous intéresse.

---

# Les arguments d'une fonction (System V AMD64)

Sous Linux :

| Argument | Registre |
|----------|----------|
| 1 | RDI |
| 2 | RSI |
| 3 | RDX |
| 4 | RCX |
| 5 | R8 |
| 6 | R9 |

Exemple :

```c
write(fd, buffer, size);
```

↓

```
RDI = fd
RSI = buffer
RDX = size
```

---

# Valeur de retour

Toutes les fonctions retournent leur résultat dans :

```
RAX
```

Exemple :

```c
int foo(void)
{
    return 42;
}
```

↓

```asm
mov eax, 42
ret
```

---

# Quelle taille utiliser ?

| Type C | Registre conseillé |
|----------|--------------------|
| char | AL / BL / CL / DL |
| short | AX / BX / CX / DX |
| int | EAX / EBX / ECX / EDX |
| long | RAX / RBX / RCX / RDX |
| pointeur | RAX / RBX / RCX / RDX |

---

# À retenir

✅ Les registres 64 bits possèdent plusieurs sous-registres.

✅ Modifier AL ne modifie que 8 bits.

✅ Modifier AX ne modifie que 16 bits.

✅ Modifier EAX modifie les 32 bits de poids faible **et remet automatiquement les 32 bits de poids fort de RAX à zéro.**

✅ Modifier RAX modifie les 64 bits.
