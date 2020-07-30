#ifndef SEQR_SAFE_SEQUENCES_WRAPPER_H
#define SEQR_SAFE_SEQUENCES_WRAPPER_H

#include "rcpp_to_cpp_converters.h"

template<class elem_t>
class BaseSafeSequencesWrapper {
public:

    class Row {
    public:
        explicit Row(const std::vector<elem_t> &row) :
                row(row) {
        }

        Row() = delete;

        Row(const Row &) = delete;

        Row(Row &&) noexcept = default;

        Row &operator=(const Row &) = delete;

        Row &operator=(Row &&) noexcept = delete;

        const elem_t &operator[](std::size_t index) const {
            return row[index];
        }

        std::size_t size() const {
            return row.size();
        }

    private:
        const std::vector<elem_t> &row;
    };

    inline Row row(std::size_t index) const {
        return std::move(Row(sequences_[index]));
    }

    inline std::size_t size() const {
        return sequences_.size();
    }

protected:
    std::vector<std::vector<elem_t>> sequences_;

    BaseSafeSequencesWrapper() = default;
};

template<class elem_t>
class SafeSequencesWrapper : public BaseSafeSequencesWrapper<elem_t> {
public:
    explicit SafeSequencesWrapper(std::vector<std::vector<elem_t>> &&sequences) {
        this->sequences_ = std::move(sequences);
    }

    SafeSequencesWrapper(SafeSequencesWrapper &&) noexcept = default;

    SafeSequencesWrapper(const SafeSequencesWrapper &) = delete;

    SafeSequencesWrapper &operator=(SafeSequencesWrapper &&) noexcept = default;

    SafeSequencesWrapper &operator=(const SafeSequencesWrapper &) = delete;

    SafeSequencesWrapper() = delete;
};

template<class cell_t>
class SafeMatrixSequenceWrapper : public BaseSafeSequencesWrapper<cell_t> {
public:

    template<class matrix_t>
    explicit SafeMatrixSequenceWrapper(const matrix_t &matrix) {
        initSequences(matrix);
    }

    SafeMatrixSequenceWrapper(SafeMatrixSequenceWrapper &&) noexcept = default;

    SafeMatrixSequenceWrapper(const SafeMatrixSequenceWrapper &) = delete;

    SafeMatrixSequenceWrapper &operator=(SafeMatrixSequenceWrapper &&) noexcept = default;

    SafeMatrixSequenceWrapper &operator=(const SafeMatrixSequenceWrapper &) = delete;

    SafeMatrixSequenceWrapper() = delete;

private:

    template<class matrix_t>
    inline void initSequences(const matrix_t &matrix) {
        this->sequences_.resize(matrix.nrow());
        for (int row = 0; row < matrix.nrow(); ++row) {
            setSequenceRow(matrix, row);
        }
    }

    template<class matrix_t>
    inline void setSequenceRow(const matrix_t &matrix, int row) {
        this->sequences_[row].resize(matrix.ncol());
        for (int column = 0; column < matrix.ncol(); ++column) {
            auto matrixCell = matrix(row, column);
            this->sequences_[row][column] = convert<decltype(matrixCell), cell_t>(matrix(row, column));
        }
    }
};

#endif //SEQR_SAFE_SEQUENCES_WRAPPER_H