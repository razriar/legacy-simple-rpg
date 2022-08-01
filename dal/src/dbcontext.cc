#include "dal/dbcontext.h"

namespace dal {
DBContext::DBContext() { comparators_[bll::Comparator::Equal] = "="; }
}  // namespace dal
