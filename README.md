# Admin Panel Console Application (C++)

A simple console application to manage Users and their Listings. It demonstrates a clean separation of concerns with repository abstraction, domain validation, and structured exception handling.

- Language/Std: C++20
- Build system: CMake
- Target: `AdminPanel` (console executable)

## Features
- Manage Users: create, delete, list, and find by ID
- Manage Listings per User: create and delete
- Domain validation with clear error messages
- Duplicate detection for users and listings
- Repository interface (`IUserRepository`) enabling future file/DB storage

## Validation Rules
- User `age` must be > 0
- Listing `price` must be ≥ 0
- Duplicate user (same `name` + `lastName`, case-insensitive) is forbidden
- Duplicate listing title per user (case-insensitive) is forbidden

Violations raise `ValidationException` or `DuplicateEntryException`.

## Exceptions
- `ValidationException` — invalid input domain rules
- `DuplicateEntryException` — duplicate user or listing
- `NotFoundException` — missing user or listing

All user actions in the UI are wrapped with try/catch and show friendly error messages.

## Architecture Overview
- Presentation (Console UI): `src/core/AdminPanel.{h,cpp}` handles input/output and commands
- Domain Models: `src/models/User/*`, `src/models/Listing/*`
- Repository Abstraction:
  - Interface: `src/core/repository/IUserRepository.h`
  - In-memory implementation: `src/core/repository/InMemoryUserRepository.{h,cpp}` (default)
- Exceptions: `src/core/exceptions/DomainExceptions.h`

The UI depends only on the `IUserRepository` interface, so you can swap in a different implementation (e.g., `FileUserRepository`) later without changing the UI.

## Build and Run
Using CLion (recommended):
- Open the project. CLion configures a Debug profile automatically.
- Build target: `AdminPanel`
- Run target: `AdminPanel`

Command line (example):
```
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target AdminPanel
./cmake-build-debug/AdminPanel
```

In this workspace, the active profile is `Debug` with build dir `/Users/sunflower/CLionProjects/AdminPanel/cmake-build-debug`.

## Usage
When you start the app you’ll see a menu like:
```
==== Admin Panel ====
1. Create user
2. Delete user
3. Find user by ID
4. Show all users
5. Create listing for certain user
6. Remove listing for certain user
0. Logout
```
- Enter values when prompted. Multiline text is supported for `address` and `description` via `getline` where applicable.
- Invalid inputs (age 0, negative price, duplicates) will display a clear error and the app keeps running.

## Example
- Try creating a user with age `0`: you will get a validation error.
- Create a user, then create a listing with price `-1`: you will get a validation error.
- Create two users with the same `name` and `lastName` (case-insensitive): duplicate error.
- Create two listings for the same user with the same title (case-insensitive): duplicate error.

## Project Structure
```
CMakeLists.txt
README.md
src/
  main.cpp
  core/
    AdminPanel.h
    AdminPanel.cpp
    exceptions/DomainExceptions.h
    repository/
      IUserRepository.h
      InMemoryUserRepository.h
      InMemoryUserRepository.cpp
  models/
    User/
      User.h
      User.cpp
    Listing/
      Listing.h
      Listing.cpp
docs/
  DLD.md
```

## Documentation
See `docs/DLD.md` for the Detailed Level Design (DLD), including:
- Validation table
- Exception table
- Activity diagram and Sequence diagram for `createUser`

## Next Steps (optional)
- Implement `FileUserRepository` that persists users/listings to disk and implements `IUserRepository`
- Trim/normalize whitespace for input fields before validation and duplicate checks
- Add tests and logging

## Authors
- Rustam Zaloldinov
- Ekaterina Lugovets
