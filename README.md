# Inventory Management System

A simple Command Line Interface (CLI) program for managing inventory in a **manufacturing** or **production-based** company. The system supports recording purchase transactions, managing stock levels using the **Weighted Average Cost** method, and tracking raw material expenses (cost records).

---

## 📌 Project Goals

- Record and view purchase transactions.
- Track inventory quantity and value based on purchases and usage.
- View cost records (expenses) of used raw materials.
- Ensure **data consistency and accounting logic** across all operations.

---

## 👥 Intended Users

Company staff responsible for:
- Purchasing raw materials
- Managing inventory
- Tracking production material expenses

---

## 🧠 Program Logic & Features

### 🔹 Main Menu Options:
1. **Purchase** – Add/view/remove purchase records.
2. **Inventory** – View current stock with sorting/searching.
3. **Cost Record** – View expense records of used raw materials.
4. **Exit & Save** – Save progress into `.txt` files and close program.

### 🔹 Smart Business Rules:
- **Purchase → Inventory**: New purchases automatically increase inventory.
- **Remove Purchase**: Cancels a purchase and reduces inventory *only* if enough stock is available.
- **Inventory → Cost Record**: Materials removed from inventory are automatically added to cost record.
- **Remove Cost Record**: Cancels an expense and adds materials back to inventory.
- **No manual add to Inventory or Cost Record** to prevent invalid data (e.g. "phantom stock").

### 📊 Inventory Valuation:
- Inventory is managed using **Weighted Average Method** to calculate unit cost when reducing stock.

---

## ✏️ User Input & Output

### ➕ Input:
- **Purchase**: product name, quantity, unit price, supplier, and date.
- **Remove Purchase**: index number (auto-detects matching info).
- **Remove Inventory**: product name, quantity to remove, and date.
- **Remove Cost Record**: index number (auto-detects matching info).

### 📤 Output:
- Lists of purchases, inventory, or cost records displayed in a table-style format.
- Includes features like:
  - Sorting (by date or quantity)
  - Searching
  - Selective removal of entries

---

## 💻 Tech Stack

- **Language**: C/C++
- **Platform**: Windows (uses `windows.h` for console manipulation)
- **Storage**: Local `.txt` files (human-readable format, no binary)

---

## 🚀 How to Install and Run

> *(Assumes you're using Windows and a C++ compiler like Code::Blocks or Dev-C++)*

1. Clone or download the repository: git clone https://github.com/limdaravotey/Inventory-Management-System.git
2. Open the project in your IDE.
3. Compile the `main.cpp` (or equivalent entry point).
4. Run the program. It will:
- Load from `.txt` files if present.
- Create new files (`purchaseFile.txt`, `inventoryFile.txt`, `costrecordFile.txt`) if not present.
5. Use the CLI interface to operate the system.

---

## 📂 Data Files

The repo includes:
- `purchaseFile.txt`
- `inventoryFile.txt`
- `costrecordFile.txt`

These are for demo/testing purposes with prefilled data.  
You may delete them to start fresh — the program will auto-generate new blank ones on first run.

---

## 🛠️ Future Plans

- Rebuild the project in **Java** with a GUI interface.
- Replace `.txt` file storage with a **MySQL** database.
- Improve structure and modularity for enterprise-level backend development.

---

## 📣 Author

**Lim Daravotey**  
Aspiring Backend Developer | IT Student  
📧 limdaravotey@gmail.com  

---

## 📘 License

This project is open-source and free to use for educational and non-commercial purposes.
