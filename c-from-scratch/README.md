# Learn C

Structured C learning notes and practice programs, organized topic by topic in the same style as `cpp-from-scratch`.

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white"/>
  <img src="https://img.shields.io/badge/Status-In%20Progress-FFB300?style=flat-square"/>
  <img src="https://img.shields.io/badge/Focus-C%20Programming-6A1B9A?style=flat-square"/>
</p>


This repo keeps lesson notes close to their examples. Generated binaries, data files, notebooks, and older assets are preserved so nothing from the original folder is lost.

---

## Roadmaps

- `resources/roadmaps/01-core-c-roadmap.md` - full C language learning roadmap

---

## Roadmap Overview

| Phase | Folder | Focus |
|---|---|---|
| 0 | `00-c-setup/` | Compiler setup and first build commands |
| 1 | `01-c-basics/` | First programs, operators, input/output, simple conditions |
| 2 | `02-control-flow/` | `if`, `switch`, loops, patterns, branching practice |
| 3 | `03-arrays-strings/` | Arrays, character arrays, strings, array operations |
| 4 | `04-c-functions/` | Function declarations, definitions, calls, return values |
| 5 | `05-pointers/` | Pointer basics and pointer examples |
| 6 | `06-structures-unions/` | `struct`, `union`, `enum`, and related examples |
| 7 | `07-dynamic-memory/` | `malloc`, `calloc`, `realloc`, `free`, heap memory |
| 8 | `08-file-handling/` | Text files, binary files, file pointers, contact manager |
| 9 | `09-data-structures/` | Future home for linked lists, stacks, queues, trees, graphs |
| 10 | `10-advanced-c/` | Future home for macros, headers, storage classes, debugging |
| 11 | `11-projects/` | Mini projects built from the course topics |

---

## Repo Structure

```text
c-from-scratch/
|-- README.md
|-- documents/
|   |-- instructions.md
|   `-- organization-log.md
|-- resources/
|   |-- images/
|   `-- roadmaps/
|-- 00-c-setup/
|-- 01-c-basics/
|-- 02-control-flow/
|-- 03-arrays-strings/
|-- 04-c-functions/
|-- 05-pointers/
|-- 06-structures-unions/
|-- 07-dynamic-memory/
|-- 08-file-handling/
|-- 09-data-structures/
|-- 10-advanced-c/
`-- 11-projects/
```

## Working Pattern

- Put each topic's notes directly inside its numbered folder.
- Put practice source files inside that topic's `examples/` folder.
- Use lowercase, hyphen-separated names for C files, usually with a two-digit prefix like `01-first-program.c`.
- Keep compiled `.exe` files and lesson data files only when they are useful historical outputs.
- Put shared diagrams, screenshots, and reference images under `resources/images/`.
- Put repo-level notes, setup guidance, and organization notes under `documents/`.
