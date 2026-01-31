# Arabic Morphology Project in C++

## 1. Project Goal

Build a C++ application that:

- Stores Arabic roots efficiently in an AVL tree.
- Stores morphological schemes (patterns) in a manually implemented hash table.
- Generates derived words from a root using one or multiple schemes.
- Validates an input word by decomposing it to detect its root and scheme.
- Maintains, for each root, a list of validated derived words with frequencies.
- Provides both a CLI and a graphical interface.

---

## 2. Functional Requirements

### 2.1 Root Management

- Load roots from a UTF-8 text file (one root per line).
- Insert, search, and display roots.
- Each root node stores:
  - The root string (example: كتب)
  - Height and balance information (AVL)
  - A list of validated derived words with frequency counters

### 2.2 Scheme Management

- Implement a hash table manually (open addressing or chaining, recommended chaining).
- Operations:
  - Add a scheme
  - Modify a scheme
  - Delete a scheme
  - Search a scheme
  - Display schemes
- Each scheme stores:
  - Scheme name (example: فاعل)
  - Pattern template with placeholders C1, C2, C3
  - Rule metadata (positions of placeholders, fixed letters, optional prefix and infix)

### 2.3 Word Generation

- Input:
  - Root (example: كتب)
  - Scheme or list of schemes (example: فاعل, مفعول)
- Output:
  - Generated derived word(s) (example: كاتب, مكتوب)
- Update:
  - Add generated word to the validated list of the root only if validation is confirmed.
  - If the word already exists, increase its frequency.

### 2.4 Word Validation and Decomposition

- Input:
  - Word (example: مكتوب)
- Output:
  - YES or NO
  - If YES, show:
    - Extracted root (كتب)
    - Detected scheme (مفعول)
- Method:
  - Try matching the word against each scheme template.
  - If match is possible, extract C1 C2 C3 from mapped positions.
  - Confirm extracted root exists in the AVL.
  - If valid, update root validated list and increment frequency.

---

## 3. Data Structures Design

### 3.1 AVL Tree for Roots

**Node structure**

- `root`: string
- `height`: int
- `left`: pointer
- `right`: pointer
- `derivedWords`: list of entries
  - `word`: string
  - `freq`: int

**Operations**

- Insert with balancing
- Search
- Inorder traversal to display
- Rotations: LL, RR, LR, RL

### 3.2 Hash Table for Schemes

**Entry structure**

- `name`: string
- `template`: sequence of tokens (fixed letters + placeholders)
- `placeholderPositions`: indices for C1 C2 C3
- `next`: pointer (if chaining)
**Hash function**

- Custom string hash on UTF-8 bytes or normalized code points.
**Operations**

- Insert
- Search
- Update
- Delete
- Display

### 3.3 Derived Word List per Root

Two options:

- Vector of entries, linear search for update
- Balanced tree or hash map internal to node (optional improvement)

Recommended:

- Vector plus update function, since list size is typically small in a mini project.

---

## 4. Arabic Text Handling Strategy

### 4.1 Encoding

- All input files stored in UTF-8.
- Use `std::string` for storage.
- Avoid indexing by bytes when positions matter.

### 4.2 Safe Position Handling

- Convert `std::string` to `std::u32string` internally for:
  - Scheme placeholder mapping
  - Character level comparisons
- Convert back to UTF-8 for display.

### 4.3 Normalization

Optional, but useful:

- Remove tatweel
- Normalize hamza forms
- Normalize alef variants

---

## 5. Program Modules

### 5.1 Core Modules

- `RootAVL`
  - insert, search, traverse, rotate, loadFromFile
- `SchemeHashTable`
  - insert, search, update, delete, loadDefaultSchemes
- `Generator`
  - generateWord(root, scheme)
  - generateFamily(root, schemeList or all schemes)
- `Validator`
  - validateWord(word)
  - decompose(word) returns (scheme, root) or failure
- `Storage`
  - load roots file
  - optional save results file
- `CLI`
  - menu, input parsing, output formatting

### 5.2 GUI Module

- `GUI`
  - visual forms for root management, scheme management, generation, validation
  - views for AVL and hash table contents

---

## 6. Graphical Interface Plan

### 6.1 Technology Choice

Choose one:

- Qt Widgets (recommended, rich UI, good for C++)
- wxWidgets (lighter alternative)
- ImGui (fast dev, less academic UI)

Recommended: Qt Widgets.

### 6.2 GUI Screens

**Screen A: Home Dashboard**

- Buttons:
  - Roots
  - Schemes
  - Generate
  - Validate
  - Statistics
**Screen B: Roots Manager**

- Load roots from file button
- Add root input field
- Search root input field
- Display AVL inorder list
- Root details panel:
  - root
  - derived words list with frequencies
**Screen C: Schemes Manager**

- Table of schemes:
  - name
  - template
  - placeholder mapping
- Buttons:
  - Add
  - Edit
  - Delete
  - Search

**Screen D: Generator**

- Root input
- Scheme selection list with multi select
- Generate button
- Output panel:
  - root, scheme, generated word
- Option:
  - Generate family using all schemes

**Screen E: Validator**

- Word input
- Validate button
- Output:
  - YES or NO
  - scheme detected
  - root extracted
  - update confirmation

**Screen F: Visualizer**
Optional but very strong for presentation:

- AVL tree view:
  - show nodes and left right links
  - highlight searched node
- Hash table view:
  - show buckets and chaining lists
  - show collisions

### 6.3 GUI Flow

- GUI calls the same core services used by CLI.
- No duplicated logic.
- Core modules are independent from UI.

---

## 7. Input and Output Formats

### 7.1 Roots File

- UTF-8 text file
- One root per line
- Example:
  - كتب
  - درس
  - خرج

### 7.2 Schemes Initialization

- Hard-coded defaults at start, plus optional file load later.
- Examples:
  - فاعل: C1 ا C2 C3
  - مفعول: م C1 C2 و C3
  - تفعيل: ت C1 C2 ي C3

---

## 8. Algorithms

### 8.1 Generation Algorithm

1. Check root exists in AVL.
2. Fetch scheme from hash table.
3. Convert root to code points.
4. Apply scheme mapping to build derived word.
5. Return derived word.

### 8.2 Validation and Decomposition Algorithm

1. For each scheme in hash table:
   - Try to match fixed letters and length constraints.
   - Extract C1 C2 C3 according to placeholder positions.
2. If extracted root exists in AVL:
   - Mark as valid
   - Update derived words list and frequency
   - Return YES with scheme and root
3. Otherwise return NO.

---

## 9. Testing Plan

### 9.1 Unit Tests

- AVL:
  - insert order causing rotations
  - search existing and missing roots
- Hash table:
  - collisions
  - insert and delete correctness
- Generator:
  - root كتب with فاعل produces كاتب
  - root كتب with مفعول produces مكتوب
- Validator:
  - مكتوب returns YES, root كتب, scheme مفعول
  - random word returns NO

### 9.2 Integration Tests

- Load roots, add schemes, generate, validate, check frequency updates.
- Test both CLI and GUI actions.

---

## 10. Delivery Checklist

- Source code:
  - modular design, headers and cpp files
- README:
  - project description
  - build instructions
  - usage examples for CLI and GUI
- Diagrams:
  - system architecture
  - AVL internal node structure
  - hash table buckets and entries
  - generation and validation flows
- Example data files:
  - roots.txt
  - optional schemes.txt
- Screenshots:
  - GUI screens
  - visualizer outputs if included

---

## 11. Suggested Milestones

1. Implement AVL and load roots.
2. Implement hash table and default schemes.
3. Implement generator and basic CLI.
4. Implement validator and decomposition.
5. Add derived words list with frequency.
6. Build GUI screens and connect core modules.
7. Add visualizer and finalize tests and report.
