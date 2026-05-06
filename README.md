*This project has been created as part of the 42 curriculum by blidriss*

---

# 📖 Get Next Line

## 🧠 Description

**Get Next Line (GNL)** is a C project that implements a function capable of reading a file descriptor line by line.

The main idea is to repeatedly call a function that returns the next line from a file, including the `\n` character when present. This project introduces an important concept in C programming: **static variables**, which allow persistent state between function calls.

### 🎯 Goal

- Read a file **line by line**
- Handle different file descriptors (mandatory + bonus)
- Manage memory correctly without leaks
- Learn how buffered reading works internally

---

## ⚙️ Instructions

### 🧩 Function Prototype

```c
char *get_next_line(int fd);
```

### 📁 Files to submit

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### 📥 External functions allowed

- `read`
- `malloc`
- `free`

### 🛠 Compilation

Compile your project using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

You can change `BUFFER_SIZE`:

```bash
-D BUFFER_SIZE=n
```

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 *.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 *.c
```

---

## ▶️ Usage

Example usage in a program:

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## 🧠 Algorithm Overview

The implementation is based on a **buffered reading + stash (static memory)** approach.

### 📌 Core idea

Each call to `get_next_line()`:

1. Reads data from the file using a buffer (`BUFFER_SIZE`)
2. Stores leftover data in a **static variable** (stash)
3. Searches for `\n` in the accumulated data
4. Extracts one full line
5. Keeps remaining data for the next call

### 🧩 Why use a static variable?

A static variable allows the function to **remember unread data between calls**, which is essential because:

- File reading happens in chunks (`read`)
- Lines may be split across multiple reads
- We must preserve remaining characters after `\n`

### ⚙️ Workflow

**Read loop**
- Read from `fd` into buffer
- Append to stash

**Line extraction**
- Find `\n`
- Split:
  - Return left part (line)
  - Keep right part (for next call)

**Edge cases**
- End of file → return last line without `\n`
- Error → return `NULL`

---

## 🔀 Bonus Part

The bonus implementation extends the project with:

- Only **one static variable**
- Support for **multiple file descriptors** simultaneously

### 💡 Idea

Instead of a single stash, a structure (or indexed storage) is used internally to track each `fd` independently.

This allows:

```
fd1 → line 1
fd2 → line 1
fd1 → line 2
fd3 → line 1
```

Without losing state between calls.
