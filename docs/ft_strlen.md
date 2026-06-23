# Introduction à l'assembleur x86-64
> Les bases nécessaires pour comprendre et implémenter `ft_strlen` en NASM.

---

# Pourquoi l'assembleur ?

Lorsque tu écris un programme en C :

```c
int main(void)
{
    return (42);
}
```

Le processeur **ne comprend pas le C**.

Il comprend uniquement des instructions machine, par exemple :

```
mov eax, 42
ret
```

L'assembleur est simplement une manière **lisible** d'écrire ces instructions.

On peut résumer :

```
C
│
│ gcc
▼
Assembleur
│
│ nasm / assembleur
▼
Code machine
│
▼
CPU
```

---

# Le processeur

Le processeur est extrêmement simple.

Il répète toujours le même cycle :

```
Lire une instruction

↓

L'exécuter

↓

Lire la suivante

↓

L'exécuter
```

Par exemple :

```
mov rax, 5
add rax, 3
ret
```

Le CPU fait :

```
Instruction 1
↓

RAX = 5

↓

Instruction 2

↓

RAX = 8

↓

Instruction 3

↓

Fin
```

Il ne "comprend" rien.

Il exécute uniquement des instructions.

---

# Les registres

Les registres sont de **toutes petites mémoires situées dans le processeur**.

Ils sont extrêmement rapides.

Imagine :

```
RAM
───────────────

8 Go

↓

Accès relativement lent
```

```
CPU

+-------+
| RAX   |
| RBX   |
| RCX   |
| RDX   |
+-------+
```

Les registres sont directement dans le CPU.

Ils servent à manipuler les données.

---

# Les registres importants

Pour Libasm, retiens seulement ceux-ci.

## RAX

Très important.

Il sert souvent :

- aux calculs
- à la valeur de retour d'une fonction

Exemple :

```asm
mov rax, 42
```

Après :

```
RAX

+------+
| 42   |
+------+
```

---

## RDI

Premier argument d'une fonction.

Exemple :

```c
strlen("bonjour");
```

Le compilateur place :

```
RDI

↓

adresse de "bonjour"
```

---

## RSI

Deuxième argument.

Exemple :

```c
strcpy(dest, src);
```

```
RDI -> dest

RSI -> src
```

---

## RDX

Troisième argument.

Exemple :

```c
write(fd, buffer, size);
```

```
RDI = fd

RSI = buffer

RDX = size
```

---

## RSP

Le pointeur de pile.

On ne l'utilisera presque pas dans `ft_strlen`.

Nous le verrons plus tard.

---

# La mémoire

Imagine la mémoire comme une immense rue.

```
Adresse

0
1
2
3
4
5
6
7
8
9
...
```

Chaque adresse contient **1 octet**.

Par exemple :

```
Adresse

1000
↓

'H'

1001
↓

'e'

1002
↓

'l'

1003
↓

'l'

1004
↓

'o'

1005
↓

'\0'
```

Une chaîne C est simplement une suite de caractères terminée par `'\0'`.

---

# Les pointeurs

En C :

```c
char *str = "Hello";
```

`str` ne contient **pas** les caractères.

Il contient une adresse.

Par exemple :

```
str

↓

1000
```

À l'adresse 1000 :

```
1000 H

1001 e

1002 l

1003 l

1004 o

1005 \0
```

---

# Les arguments d'une fonction

En Linux x86-64 :

Le premier argument arrive dans :

```
RDI
```

Donc :

```c
ft_strlen(str);
```

devient :

```
RDI

↓

adresse de str
```

Le processeur ne reçoit pas la chaîne.

Il reçoit son adresse.

---

# Lire la mémoire

En NASM :

```asm
mov al, [rdi]
```

Signifie :

> Lire **l'octet situé à l'adresse contenue dans RDI**.

Si :

```
RDI = 1000
```

Et :

```
1000 = 'H'
```

Alors :

```
AL = 'H'
```

---

# Avancer dans la chaîne

Supposons :

```
1000 H
1001 e
1002 l
1003 l
1004 o
1005 \0
```

Si :

```
RDI = 1000
```

Alors :

```asm
mov al, [rdi]
```

lit :

```
'H'
```

Si on fait :

```asm
inc rdi
```

Alors :

```
RDI = 1001
```

Maintenant :

```asm
mov al, [rdi]
```

lit :

```
'e'
```

Puis :

```
inc rdi
```

↓

```
'l'
```

Puis

```
'l'
```

Puis

```
'o'
```

Puis

```
'\0'
```

---

# Que fait ft_strlen ?

En C :

```c
size_t ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;

    return (i);
}
```

Le principe est très simple.

On part du premier caractère.

```
'H'
```

↓

On avance.

```
'e'
```

↓

On avance.

```
'l'
```

↓

On avance.

↓

Jusqu'à trouver :

```
'\0'
```

Le nombre de déplacements effectués est la longueur de la chaîne.

---

# Les instructions que nous utiliserons

Pour `ft_strlen`, seulement six instructions suffisent.

## mov

Copie une valeur.

```asm
mov rax, 0
```

---

## cmp

Compare deux valeurs.

```asm
cmp al, 0
```

---

## je

Saute si les deux valeurs sont égales.

---

## inc

Ajoute 1.

```asm
inc rax
```

---

## jmp

Saute toujours.

---

## ret

Retourne au programme appelant.

---

# Ce que tu dois retenir avant de commencer ft_strlen

✅ Une chaîne est une suite d'octets terminée par `'\0'`.

✅ Un pointeur contient une adresse mémoire.

✅ Le premier argument d'une fonction arrive dans **RDI**.

✅ On lit la mémoire avec :

```asm
mov al, [rdi]
```

✅ On avance avec :

```asm
inc rdi
```

✅ La valeur de retour d'une fonction doit être placée dans **RAX**.

---

# Objectif

Tu connais maintenant **90 % de la théorie nécessaire pour comprendre `ft_strlen`**.

Le prochain chapitre consistera à écrire `ft_strlen` **instruction par instruction**, en simulant ce que fait le processeur à chaque étape.