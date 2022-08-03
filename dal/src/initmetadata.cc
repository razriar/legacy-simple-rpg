#include "bll/metadata.h"
#include "bll/user.h"

namespace bll {
void InitMetadata() {
    Metadata<User>::TableName_ = "users";
    Metadata<User::Id>::ColumnName_ = "id";
    Metadata<User::Email>::ColumnName_ = "email";
    Metadata<User::Password>::ColumnName_ = "password";
    Metadata<User::Name>::ColumnName_ = "name";
    Metadata<User::Nick>::ColumnName_ = "nick";
    Metadata<User::Secret>::ColumnName_ = "secret";
}
}  // namespace bll
