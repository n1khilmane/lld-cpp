# Library Management System - Design Questions & Answers

## 1. Scalability for Millions of Books

### Question
What if the library has millions of books? How will you scale your system?

### Answer
If the library scales to millions of books, we can't rely on in-memory data structures like unordered maps alone. Instead, I would:

- Use a relational database like PostgreSQL to store books and book copies
- Add indexes on columns like ISBN, title, and author to ensure fast search queries
- Apply pagination for large result sets
- Use in-memory caching (e.g., Redis) to store results for frequently searched books

This design separates fast, volatile access (cache) from persistent, reliable storage (DB), and supports horizontal scaling of the backend service.

---

## 2. Concurrent Access Handling

### Question
What if multiple users try to borrow or return the same book at the same time?

### Answer
To handle concurrent access and avoid race conditions, especially for operations like borrowing or returning a book, I would:

- Add locking mechanisms at the book item (barcode) level
- In memory, use a mutex or synchronized block (in C++ or Java)
- In a real system with a database, use row-level locking or optimistic concurrency control

For example, when a user tries to borrow a book:
1. Check if it's issued inside a critical section
2. Update the state only if it's still available

This ensures atomicity of the borrow/return operation and prevents two users from issuing the same book at the same time.

---

## 3. eBook Support

### Question
How will you support eBooks in the future?

### Answer
To support eBooks in the future without disrupting the current design, I would apply the Open/Closed Principle by extending the existing BookItem structure instead of modifying it.

Specifically:
- Create an abstract base class `BookItem`
- Keep `PhysicalBookItem` for barcoded physical copies
- Introduce a new class `EBookItem` that includes:
  - downloadLink
  - accessDuration
  - DRMRestrictions
- Store both types in a unified `vector<BookItem*>`, enabling polymorphic access

This approach avoids if-else logic, keeps the code extensible, and supports different borrowing logic (e.g., immediate access for eBooks vs availability checks for physical books).

---

## 4. Multiple Library Branches

### Question
What if we want to support multiple library branches?

### Answer
To support multiple library branches, I'd introduce a new entity: `LibraryBranch`, with fields like branchId, name, and location.

Then I would:
- Associate each BookItem with a branchId to indicate its physical location
- Modify queries to filter books by branch (e.g., show only available books at a member's home branch)
- Optionally, add inter-branch borrowing rules and transfer workflows (e.g., request from another branch)

This setup maintains separation of data per branch and allows future extensions like:
- Per-branch inventory tracking
- Regional borrowing limits
- Decentralized admin controls

---

## 5. ISBN Map Usage

### Question
Why did you use a map for storing books by ISBN?

### Answer
I used an `unordered_map<string, Book*>` to store books by ISBN because:
- ISBNs are unique identifiers for books, making them ideal keys
- Maps provide O(1) average-case lookup time, ensuring fast access when searching or updating book records
- It simplifies operations like addBook, searchBookByISBN, and linking book copies

In a scaled system, this map could be backed by a database with an indexed ISBN column to retain the same fast lookup property.

---

## 6. User Inheritance vs Composition

### Question
Why did you choose inheritance for users? Could composition work?

### Answer
I chose inheritance (User → Member, Librarian) because:
- The roles are clearly defined and share common attributes like userId and name
- Their behaviors are role-specific (e.g., only Librarian can add books), which makes overriding functions logical and clean
- It allows polymorphism — I can store all users as User* but invoke their role-specific methods dynamically

However, composition is also a valid alternative:
- We could have a User class with a Role object (e.g., MemberRole, LibrarianRole)
- This is more flexible if roles are dynamic or users have multiple roles
- In this case, since roles are static and exclusive, inheritance was simpler and sufficient

---

## 7. Decorator Pattern Usage

### Question
Why did you use the Decorator pattern? Could inheritance handle premium members?

### Answer
While inheritance could work for premium members (e.g., creating a PremiumMember subclass), it becomes inflexible and hard to scale when features vary or stack.

I used the Decorator pattern because:
- It allows us to dynamically add features like lounge access, early access, or discounts to any Member object without modifying the base class
- You can stack decorators (e.g., Premium + Discount + EventAccess) without a subclass explosion
- It follows the Open/Closed Principle — behavior is extended without touching existing code

So compared to a rigid inheritance tree (Member, PremiumMember, SuperPremiumMember, etc.), the decorator pattern keeps the system modular and flexible.

---

## 8. Observer Pattern Application

### Question
Where would the Observer pattern be useful?

### Answer
Use Observer Pattern when:
- A member reserves a book that's currently issued
- When the book is returned, notify all waiting users

This decouples notification logic from core borrowing logic, enabling:
- Email/SMS/Push updates
- Subscriber-based waitlist notifications

---

## 9. Non-existent Book Handling

### Question
What happens if a user tries to borrow a book that doesn't exist?

### Answer
This is an edge case. I'd:
- Validate that the barcode exists in barcodeMap
- Return an appropriate error or throw an exception
- Log the attempt for audit

Defensive programming prevents crashes and improves system robustness.

---

## 10. Overdue Book Management

### Question
What if a book is borrowed but never returned?

### Answer
Extend the Transaction model:
- Add a dueDate field (e.g., 14 days from borrowDate)
- Periodically scan for overdue books using a scheduler
- Apply fines using a FineStrategy
- Optionally send automated reminders using Observer pattern

This supports accountability and late fee enforcement.

---

## 11. Borrow Limit Enforcement

### Question
What if a member tries to borrow more than allowed?

### Answer
Add a borrow limit:
- Keep a count of borrowed books per member
- Before issuing, check if current borrow count < allowed limit
- Return an error if exceeded

This enforces policy and ensures fair access to resources.

---

## 12. Role-Based Access Control

### Question
How do you ensure only librarians can add books?

### Answer
Use role-based access control:
- Add a getRole() method on users
- Before calling addBook(), check if user.getRole() == "Librarian"
- Prevent unauthorized actions programmatically

In a real system, you'd enforce this at the API/service layer using authentication middleware.

---

## 13. Database Schema Design

### Question
How would you store this data in a database?

### Answer
I'd use a normalized schema with tables:
- books (isbn, title, author)
- book_items (barcode, isbn, branch_id, is_issued)
- users (id, name, role)
- transactions (id, member_id, barcode, borrow_date, return_date, fine)
- branches (id, name, location)

Use foreign keys for relationships and indexes for fast lookups.

---

## 14. Transaction Persistence

### Question
How do you persist transactions?

### Answer
Store each borrow/return as a row in the transactions table:
- Include borrowDate, returnDate, and fine fields
- Query this for reports, fines, and audit logs

This provides traceability and helps support billing, analytics, and accountability.