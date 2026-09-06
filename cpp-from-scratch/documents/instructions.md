# **Instructions**

---

## **Issue: garbled box-drawing characters in terminal output**

**Symptom:**
```
ΓöÇΓöÇΓöÇΓöÇ program structure ΓöÇΓöÇΓöÇΓöÇ
```
instead of:
```
──── program structure ────
```

**Cause:**
- Source files use the Unicode box-drawing character `─` (U+2500), saved in UTF-8.
- The Windows console's active code page defaults to a legacy encoding (437/850), not UTF-8.
- The `.exe` writes correct UTF-8 bytes to stdout — the terminal just decodes them wrong.

**Not the cause:**
- `LANG`/`LC_ALL` (bash locale) — controls how bash interprets text for sorting/globbing, not how the Windows console displays program output. Setting these does not fix this.

---

## **Fix**

Run before executing the program, in the same MinGW64/mintty session:
```bash
chcp.com 65001
./main.exe
```

**To make it permanent** (so you don't repeat this every session):
```bash
echo 'chcp.com 65001 > /dev/null' >> ~/.bashrc
```

---

## **If it's still garbled after this**

The terminal/font layer is fighting the fix (common in some Windows Terminal profiles or embedded terminals). At that point, stop patching the environment — switch source files to plain ASCII separators instead of Unicode box-drawing characters:
```cpp
std::cout << "---- program structure ----\n";
```
This renders correctly on every terminal, every code page, with zero configuration.