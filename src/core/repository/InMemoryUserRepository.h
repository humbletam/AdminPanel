#ifndef INMEMORYUSERREPOSITORY_H
#define INMEMORYUSERREPOSITORY_H

#include <vector>
#include <algorithm>
#include <memory>
#include "IUserRepository.h"
#include "../exceptions/DomainExceptions.h"

class InMemoryUserRepository : public IUserRepository {
private:
    std::vector<User> users_;
    int nextUserId_ = 1;
    int nextListingId_ = 1;

public:
    const User& createUser(User u) override;
    void deleteUserById(int userId) override;
    User* findUserById(int userId) override;
    const std::vector<User>& getAllUsers() const override { return users_; }

    const Listing& addListingToUser(int userId, Listing l) override;
    void deleteListingFromUser(int userId, int listingId) override;

private:
    static void validateUser(const User& u);
    static void validateListing(const Listing& l);
};

#endif
