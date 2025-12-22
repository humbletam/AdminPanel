### Domain Logic Document (DLD)

#### Scope
This document describes validation rules, exception types, and the flow for one complete operation in the AdminPanel application. It also outlines repository interfaces to enable future persistence options (e.g., file or DB storage).

---

### Validation Rules

| Entity  | Field     | Constraint                          | Notes                                  |
|---------|-----------|-------------------------------------|----------------------------------------|
| User    | name      | not empty                           | leading/trailing spaces should be avoided by UI |
| User    | lastName  | not empty                           |                                         |
| User    | age       | age > 0                             | integer only                            |
| Listing | title     | not empty                           | unique per user (case-insensitive)      |
| Listing | price     | price ≥ 0                           | decimal allowed                         |

---

### Exceptions

| Exception                | When it is thrown                                                     | Example message                                           |
|--------------------------|------------------------------------------------------------------------|-----------------------------------------------------------|
| ValidationException      | Input violates a validation rule (age ≤ 0, empty name, negative price) | "Age must be greater than 0"                              |
| DuplicateEntryException  | Creating a duplicate entity (user duplicate or per-user listing title) | "User with the same name and last-name already exists"    |
| NotFoundException        | Entity not found (user or listing)                                     | "User not found", "Listing not found"                    |

---

### Repository Abstractions

- IUserRepository
  - `createUser(User u)` — validates and assigns ID; duplicate check by `(name,lastName)` case-insensitive.
  - `deleteUserById(int userId)` — throws if missing.
  - `findUserById(int userId)` — pointer or nullptr.
  - `getAllUsers()` — read-only list of all users.
  - `addListingToUser(int userId, Listing l)` — validates and assigns ID; title unique per user (case-insensitive).
  - `deleteListingFromUser(int userId, int listingId)` — throws if missing.

The current app uses `InMemoryUserRepository`, but any future `FileUserRepository` or `DbUserRepository` can implement the same interface without changing UI code.

---

### Activity Diagram — Create User

```mermaid
flowchart TD
    A[Start] --> B[Admin selects "Create user"]
    B --> C[Enter name, lastName, age, gender, address]
    C --> D[Repository.validateUser]
    D -->|Invalid| E[Throw ValidationException]
    E --> F[Show error message]
    D -->|Valid| G[Check duplicate (name+lastName)]
    G -->|Exists| H[Throw DuplicateEntryException]
    H --> F
    G -->|Not found| I[Assign userId]
    I --> J[Persist in repository]
    J --> K[Show success with new ID]
    K --> L[End]
```

---

### Sequence Diagram — Create User

```mermaid
sequenceDiagram
    participant Admin as AdminPanel (UI)
    participant Repo as IUserRepository

    Admin->>Admin: Prompt for user input
    Admin->>Repo: createUser(u)
    activate Repo
    Repo->>Repo: validateUser(u)
    Repo->>Repo: check duplicate (name+lastName)
    alt invalid input
        Repo-->>Admin: throw ValidationException
        deactivate Repo
        Admin-->>Admin: show "Validation error"
    else duplicate
        Repo-->>Admin: throw DuplicateEntryException
        deactivate Repo
        Admin-->>Admin: show "Duplicate"
    else success
        Repo->>Repo: assign id; save in-memory
        Repo-->>Admin: return created User
        deactivate Repo
        Admin-->>Admin: show success with ID
    end
```

---

### Notes
- Duplicate user rule: `(name,lastName)` case-insensitive within the in-memory dataset.
- Duplicate listing rule: `title` case-insensitive unique per user.
- Validation and exception handling reside in the repository; the UI (`AdminPanel`) only collects data and displays messages.
