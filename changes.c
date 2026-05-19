Modifications Made (Document 1 → Document 2)

1. File Initialization on First Run
Document 2 adds automatic file creation if `credit.dat` doesn't exist — it creates the file and pre-fills 100 blank records. Document 1 simply exits if the file isn't found.

2. New Menu Options (expanded from 7 to 9 choices)
| Choice | Doc 1 | Doc 2 |
|--------|-------|-------|
| 5 | Search by **last name** | Search by **account number** |
| 6 | Display **summary** (count, total, average) | Display **all records** (tabular list) |
| 7 | End program | **Deposit money** |
| 8 | *(none)* | **Withdraw money** |
| 9 | *(none)* | End program |

3. `searchRecord()` — Logic Changed
Doc 1 searches by **last name** (string comparison, scans all records). Doc 2 searches by **account number** (direct seek, faster lookup).

4. `displaySummary()` → `displayAllRecords()`
Doc 1's `displaySummary()` prints aggregate stats (total accounts, total deposits, average balance). Doc 2 replaces this with `displayAllRecords()`, which prints every active record in a formatted table.

5. Two New Functions Added
- **`depositMoney()`** — adds a positive amount to a specific account with validation.
- **`withdrawMoney()`** — subtracts from a specific account, with an **insufficient balance check** (new safeguard not present anywhere in Doc 1).

6. Improved `textFile()` Output Format
Doc 2 uses wider column widths (`%-15s` vs `%-16s`/`%-11s`) and prints a success message after writing. Doc 1 silently completes.

7. `main()` — `argc/argv` Removed
Doc 1 uses `int main(int argc, char *argv[])` and prints the program name on file error. Doc 2 simplifies to `int main()`.

8. Menu Styling
Doc 2 adds a decorative header (`=== BANK MANAGEMENT SYSTEM ===`) and cleaner option labels.