# 🔎 Inverted Search Engine in C

## 📌 Overview
The **Inverted Search Engine** is a command-line application implemented in the **C programming language** that builds an **inverted index** from multiple text documents and enables fast word-based searching.

An **inverted index** is a data structure widely used in **document retrieval systems and search engines**. Instead of mapping documents to words, it maps **words to the documents in which they appear**, enabling efficient search operations.

This project scans multiple text files, tokenizes words, and stores them in a structured database using **hash tables and linked lists**. Each word is associated with the files where it appears and the number of times it occurs.

The system demonstrates how modern search engines internally organize and retrieve information efficiently.

---

# ✨ Features

## 📂 File Processing
- Accepts multiple **text files through command-line arguments**.
- Validates file existence, uniqueness, and ensures files are not empty.
- Processes each file to extract and tokenize words.

---

## 🗄 Create Database
The **Create Database** operation performs indexing by:

- Scanning all input text files
- Extracting words using delimiters
- Building an inverted index dynamically
- Storing each unique word with file occurrence details

---

## 📊 Display Database
Displays the entire inverted index including:

- Indexed words
- Number of files containing the word
- File names
- Word frequency in each file

---

## 🔍 Search Database
Allows the user to search for a word in the indexed database.

The system displays:
- List of files containing the word
- Frequency of the word in each file

---

## 🔄 Update Database
Loads a previously saved database file and reconstructs the index.

During update:
- Files already processed are removed from the filename list
- Prevents duplication of indexed files

---

## 💾 Save Database
Stores the inverted index into a file using a predefined format.

This allows the database to be **reloaded later without re-indexing all files**.

---

# 🧠 What is an Inverted Index?

An **inverted index** is a data structure that maps **content (words)** to the **documents where they appear**.

Example:

| Word | Files |
|-----|------|
| data | file1.txt, file3.txt |
| search | file2.txt |
| engine | file1.txt, file2.txt |

This structure allows **fast full-text search** in large document collections.

Inverted indexing is used in:

- 🌐 Search engines
- 📚 Document retrieval systems
- 📄 Text analysis tools
- 📊 Information retrieval systems

---

# 🏗 Data Structure Design

The project uses a **two-level linked data structure with hashing**.

### Hash Table
- Words are indexed based on their **first character**.
- Provides faster lookup operations.

### Collision Handling
- Implemented using **Singly Linked Lists (SLL)**.

### Node Structure

#### Main Node
Stores:
- Word
- File count
- Pointer to sub node list

#### Sub Node
Stores:
- Filename
- Word occurrence count

Example representation:


Hash Table
|
v
[ 'a' ] → apple → file1.txt (3) → file2.txt (1)
[ 'b' ] → book → file3.txt (5)


---

# ⚙ Implementation Details

The system performs several steps:

### 1️⃣ Indexing
- Parse input files
- Extract words
- Build inverted index using hashing and linked lists
- Store the database

### 2️⃣ Querying
- Accept search word
- Locate corresponding hash index
- Traverse linked lists
- Display file names and frequencies

---

# 📋 Requirements

The application implements the following operations:

- Index multiple text files
- Tokenize words
- Store unique words with file details
- Display indexed database
- Search words efficiently
- Update database from saved file
- Save database for later usage

---

# ⚠ Validations and Error Handling

The system includes several validations:

- Invalid file names
- Duplicate file inputs
- Empty files
- Incorrect database format
- Invalid user operations
- Database not created before search

---

# 🛠 Technologies Used

This project demonstrates several important **Data Structures and C programming concepts**:

- 📂 File Handling
- 📍 Pointers
- 🧩 Structures
- 🔗 Singly Linked Lists
- ⚡ Hash Tables
- 💾 Dynamic Memory Allocation
- 🧾 Command Line Arguments
- 🔍 Tokenization and Parsing

---

# 🎯 Applications

Inverted indexing is used in:

- 🌐 Search engines (Google, Bing)
- 📚 Document search systems
- 📊 Information retrieval systems
- 🧠 Text analytics
- 📑 Content indexing platforms

---

# ⭐ Advantages

- Fast search operations
- Efficient document indexing
- Scalable for large datasets
- Modular and structured design
- Efficient data organization

---

# 🎓 Learning Outcomes

Through this project you will learn:

- Implementation of **hash tables**
- Design of **multi-level linked data structures**
- Efficient text indexing techniques
- File parsing and tokenization
- Real-world search engine concepts

---

# 🚀 Future Enhancements

Possible improvements include:

- Ranking search results based on frequency
- Phrase-based searching
- Case-insensitive indexing
- Support for larger datasets
- Implementing binary search trees or tries
- Web-based search interface

---

# 👨‍💻 Author
**Pranav Prasad**
