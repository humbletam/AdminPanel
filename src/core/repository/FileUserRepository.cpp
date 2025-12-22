#include "FileUserRepository.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return r;
}

FileUserRepository::FileUserRepository(const std::string& filename) : filename_(filename) {
    load();
}

void FileUserRepository::validateUser(const User& u) {
    if (u.age <= 0) throw ValidationException("Age must be greater than 0");
    if (u.name.empty()) throw ValidationException("Name must not be empty");
    if (u.lastName.empty()) throw ValidationException("Last-name must not be empty");
}

void FileUserRepository::validateListing(const Listing& l) {
    if (l.price < 0.0) throw ValidationException("Price must be greater than or equal to 0");
    if (l.title.empty()) throw ValidationException("Title must not be empty");
}

const User& FileUserRepository::createUser(User u) {
    validateUser(u);
    auto nameLower = toLower(u.name);
    auto lastLower = toLower(u.lastName);
    auto it = std::find_if(users_.begin(), users_.end(), [&](const User& existing){
        return toLower(existing.name) == nameLower && toLower(existing.lastName) == lastLower;
    });
    if (it != users_.end()) throw DuplicateEntryException("User with the same name and last-name already exists");
    
    u.id = nextUserId_++;
    users_.push_back(u);
    save();
    return users_.back();
}

void FileUserRepository::deleteUserById(int userId) {
    auto it = std::find_if(users_.begin(), users_.end(), [&](const User& u){ return u.id == userId; });
    if (it == users_.end()) throw NotFoundException("User not found");
    users_.erase(it);
    save();
}

User* FileUserRepository::findUserById(int userId) {
    for (auto& u : users_) {
        if (u.id == userId) return &u;
    }
    return nullptr;
}

const Listing& FileUserRepository::addListingToUser(int userId, Listing l) {
    User* u = findUserById(userId);
    if (!u) throw NotFoundException("User not found");
    validateListing(l);

    auto titleLower = toLower(l.title);
    auto it = std::find_if(u->listings.begin(), u->listings.end(), [&](const Listing& ex){
        return toLower(ex.title) == titleLower;
    });
    if (it != u->listings.end()) throw DuplicateEntryException("Listing with the same title already exists for this user");

    l.id = nextListingId_++;
    u->listings.push_back(l);
    save();
    return u->listings.back();
}

void FileUserRepository::deleteListingFromUser(int userId, int listingId) {
    User* u = findUserById(userId);
    if (!u) throw NotFoundException("User not found");
    auto it = std::find_if(u->listings.begin(), u->listings.end(), [&](const Listing& l){ return l.id == listingId; });
    if (it == u->listings.end()) throw NotFoundException("Listing not found");
    u->listings.erase(it);
    save();
}

void FileUserRepository::load() {
    std::ifstream file(filename_);
    if (!file.is_open()) return;

    users_.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line == "USER") {
            User u;
            std::getline(file, line); u.id = std::stoi(line);
            if (u.id >= nextUserId_) nextUserId_ = u.id + 1;
            std::getline(file, u.name);
            std::getline(file, u.lastName);
            std::getline(file, line); u.age = std::stoi(line);
            std::getline(file, u.gender);
            std::getline(file, u.address);
            
            std::getline(file, line);
            int listingCount = std::stoi(line);
            for (int i = 0; i < listingCount; ++i) {
                Listing l;
                std::getline(file, line); l.id = std::stoi(line);
                if (l.id >= nextListingId_) nextListingId_ = l.id + 1;
                std::getline(file, l.title);
                std::getline(file, l.description);
                std::getline(file, line); l.price = std::stod(line);
                u.listings.push_back(l);
            }
            users_.push_back(u);
        }
    }
}

void FileUserRepository::save() {
    std::ofstream file(filename_);
    if (!file.is_open()) return;

    for (const auto& u : users_) {
        file << "USER\n"
             << u.id << "\n"
             << u.name << "\n"
             << u.lastName << "\n"
             << u.age << "\n"
             << u.gender << "\n"
             << u.address << "\n"
             << u.listings.size() << "\n";
        for (const auto& l : u.listings) {
            file << l.id << "\n"
                 << l.title << "\n"
                 << l.description << "\n"
                 << l.price << "\n";
        }
    }
}
