#pragma once



namespace seoncore::sparse
{

struct SparseType
{
    /** @brief Compressed Row Storage (CRS/CSR). */
    struct CRS {};
    /** @brief Compressed Column Storage (CSC). */
    struct CSC {};
};

};
