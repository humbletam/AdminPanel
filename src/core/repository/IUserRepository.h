#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include <vector>
#include <optional>
#include "../../models/User/User.h"
#include "../../models/Listing/Listing.h"

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual const User& createUser(User u) = 0;
    virtual void deleteUserById(int userId) = 0;
    virtual User* findUserById(int userId) = 0;
    virtual const std::vector<User>& getAllUsers() const = 0;

    virtual const Listing& addListingToUser(int userId, Listing l) = 0;
    virtual void deleteListingFromUser(int userId, int listingId) = 0;
};

#endif
