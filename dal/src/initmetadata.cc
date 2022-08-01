#include "bll/metadata.h"
#include "bll/user.h"

namespace bll {
void InitMetadata() {
    Metadata<User>::TableName_ = "users";
    Metadata<User::Email>::ColumnName_ = "email";
    Metadata<User::Password>::ColumnName_ = "password";
    Metadata<User::FirstName>::ColumnName_ = "first_name";
    Metadata<User::LastName>::ColumnName_ = "last_name";
    Metadata<User::Nick>::ColumnName_ = "nick";
}
}  // namespace bll
