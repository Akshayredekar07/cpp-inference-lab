# **Notes Style Guide**

**Scope:** Formatting rules for every `.md` file in this repo (topic notes, docs, resources).

---

## **Headings**

- Use `##` for top-level section headings, `###` for sub-sections — but write heading text in **bold**, not as plain heading text alone (e.g. `## **Phase 1 — Modern C++ Core**`).
- No emoji in headings or body text.
- No skipping levels (`##` → `####`).

---

## **Structure**

- Bullet points over paragraphs. If a concept needs more than 2-3 sentences, break it into bullets instead.
- No long theory/motivational prose ("this is important because...", "don't skip this or you'll regret it"). State the fact, move on.
- Each topic file follows the same shape: **Topics** list → **Practice/Project** list. Don't invent a different structure per file.

---

## **Separators**

- Use `---` between major sections only (not between every bullet block).
- Don't overuse — one `---` per phase/section, not per sub-heading.

---

## **Code blocks**

- Always tag the language: ` ```bash `, ` ```cpp `, ` ```powershell `, ` ```cmake `.
- Keep commands copy-pasteable — no placeholder text mixed into a command line without a comment marking it.
- Verification commands go directly under the install command they verify.

---

## **Lists**

- Use `-` for bullets, not `*`.
- Use numbered lists (`1.`, `2.`) only for sequential steps where order matters (build steps, setup steps). Everything else is a `-` bullet.

---

## **Tables**

- Use tables only for reference data (version numbers, comparisons, time budgets) — never for narrative content that reads better as bullets.

---

## **Naming inside notes**

- File name and top `#` title stay consistent with the folder name (e.g. `07-oper-overload/07-oper-overload.md` → title `# **Operator Overloading**`).
- Cross-references between files use relative paths, not full descriptions: `See ../docs/compiler-setup.md`, not "check the compiler setup guide I mentioned earlier."

---

## **What NOT to include**

- No motivational language, no filler transitions ("Now let's move on to...", "Great, next we'll cover...").
- No resource/reading-list sections unless explicitly requested for that file.
- No timelines/hour estimates unless explicitly requested for that file.
- No tick/cross icons or decorative symbols standing in for pass/fail — write "Correct" / "Incorrect" or use a table.