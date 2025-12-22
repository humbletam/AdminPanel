#ifndef FILEUSERREPOSITORY_H
#define FILEUSERREPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include "IUserRepository.h"
#include "../exceptions/DomainExceptions.h"

class FileUserRepository : public IUserRepository {
private:
    std::vector<User> users_;
    int nextUserId_ = 1;
    int nextListingId_ = 1;
    std::string filename_;

public:
    explicit FileUserRepository(const std::string& filename);

    const User& createUser(User u) override;
    void deleteUserById(int userId) override;
    User* findUserById(int userId) override;
    const std::vector<User>& getAllUsers() const override { return users_; }

    const Listing& addListingToUser(int userId, Listing l) override;
    void deleteListingFromUser(int userId, int listingId) override;

private:
    void load();
    void save();
    static void validateUser(const User& u);
    static void validateListing(const Listing& l);
};

#endif
