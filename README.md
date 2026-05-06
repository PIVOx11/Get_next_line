*This project has been created as part of the 42 curriculum by \<login1\>[, \<login2\>[, \<login3\>[...]]]*

# 🧠 Description

**Libft** is your very first custom C library.  
The goal of this project is to recreate a set of standard C library functions and extend them with additional utility functions.

This project teaches:
- Memory management in C
- String manipulation
- Low-level data handling
- Writing reusable and modular code
- Building and maintaining your own static library (`libft.a`)

By the end, you will have your own toolbox of fundamental functions that you will reuse throughout your C journey.

---

# ⚙️ Instructions

## 📦 Compilation

To build the library, simply run:

```bash
make
```

This will generate the static library:

```
libft.a
```

## 🧹 Cleaning

```bash
make clean   # removes object files
make fclean  # removes object files + libft.a
make re      # rebuild everything
```

## 🛠️ Compiler Flags

The project is compiled using:

```
-Wall -Wextra -Werror
```

---

# 📚 Library Content

Libft is divided into two main parts:

## 🔹 Part 1 — Libc Reimplementation

Recreation of standard C functions:

**Character checks**
- `ft_isalpha`
- `ft_isdigit`
- `ft_isalnum`
- `ft_isascii`
- `ft_isprint`

**Strings & memory**
- `ft_strlen`
- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_memmove`
- `ft_strlcpy`
- `ft_strlcat`

**Searching & comparison**
- `ft_strchr`
- `ft_strrchr`
- `ft_strncmp`
- `ft_memchr`
- `ft_memcmp`
- `ft_strnstr`

**Conversion**
- `ft_toupper`
- `ft_tolower`
- `ft_atoi`

**Dynamic allocation**
- `ft_calloc`
- `ft_strdup`

---

## 🔹 Part 2 — Additional Utilities

Useful helper functions for string processing and I/O:

**String manipulation**
- `ft_substr` → extract substring
- `ft_strjoin` → concatenate strings
- `ft_strtrim` → trim characters
- `ft_split` → split string by delimiter
- `ft_strmapi` → map function over string
- `ft_striteri` → iterate with modification

**Integer conversion**
- `ft_itoa` → int to string

**File descriptor output**
- `ft_putchar_fd`
- `ft_putstr_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`

---

# 🚀 Usage Example

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *s = ft_strjoin("Hello ", "World");
    printf("%s\n", s);
    free(s);
    return 0;
}
```

Compile with:

```bash
cc main.c libft.a
```
