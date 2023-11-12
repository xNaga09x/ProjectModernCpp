#include "usersDB.h"

void populateStorage(Storage& storage)
{
	std::vector<User> users{
		User{ -1, "Pavel", 5.f },
		User{ -1, "Petru", 0.2f },  //Punem -1 pt ca atunci cand inseram nu stim cate elemente avem in BD
		User{ -1, "Sergiu", 2.f },
		User{ -1, "Iulian", 8.f },
	};
	storage.insert_range(users.begin(), users.end());
}

AddToUser::AddToUser(Storage& storage)
{

}
