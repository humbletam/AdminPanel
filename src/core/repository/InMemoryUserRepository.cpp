#include "InMemoryUserRepository.h"
#include <cctype>

static std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return r;
}

void InMemoryUserRepository::validateUser(const User& u) {
    if (u.age <= 0) {
        throw ValidationException("Age must be greater than 0");
    }
    if (u.name.empty()) {
        throw ValidationException("Name must not be empty");
    }
    if (u.lastName.empty()) {
        throw ValidationException("Last-name must not be empty");
    }
}

void InMemoryUserRepository::validateListing(const Listing& l) {
    if (l.price < 0.0) {
        throw ValidationException("Price must be greater than or equal to 0");
    }
    if (l.title.empty()) {
        throw ValidationException("Title must not be empty");
    }
}

const User& InMemoryUserRepository::createUser(User u) {
    validateUser(u);
    // duplicate: same name+lastName (case-insensitive)
    auto nameLower = toLower(u.name);
    auto lastLower = toLower(u.lastName);
    auto it = std::find_if(users_.begin(), users_.end(), [&](const User& existing){
        return toLower(existing.name) == nameLower && toLower(existing.lastName) == lastLower;
    });
    if (it != users_.end()) {
        throw DuplicateEntryException("User with the same name and last-name already exists");
    }
    u.id = nextUserId_++;
    users_.push_back(u);
    return users_.back();
}

void InMemoryUserRepository::deleteUserById(int userId) {
    auto it = std::find_if(users_.begin(), users_.end(), [&](const User& u){ return u.id == userId; });
    if (it == users_.end()) {
        throw NotFoundException("User not found");
    }
    users_.erase(it);
}

User* InMemoryUserRepository::findUserById(int userId) {
    for (auto& u : users_) {
        if (u.id == userId) return &u;
    }
    return nullptr;
}

const Listing& InMemoryUserRepository::addListingToUser(int userId, Listing l) {
    User* u = findUserById(userId);
    if (!u) {
        throw NotFoundException("User not found");
    }
    validateListing(l);

    auto titleLower = toLower(l.title);
    auto it = std::find_if(u->listings.begin(), u->listings.end(), [&](const Listing& ex){
        return toLower(ex.title) == titleLower;
    });
    if (it != u->listings.end()) {
        throw DuplicateEntryException("Listing with the same title already exists for this user");
    }

    l.id = nextListingId_++;
    u->listings.push_back(l);
    return u->listings.back();
}

void InMemoryUserRepository::deleteListingFromUser(int userId, int listingId) {
    User* u = findUserById(userId);
    if (!u) {
        throw NotFoundException("User not found");
    }
    auto it = std::find_if(u->listings.begin(), u->listings.end(), [&](const Listing& l){ return l.id == listingId; });
    if (it == u->listings.end()) {
        throw NotFoundException("Listing not found");
    }
    u->listings.erase(it);
}
