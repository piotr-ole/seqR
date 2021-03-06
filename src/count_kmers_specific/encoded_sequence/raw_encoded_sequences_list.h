#pragma once

#include <vector>

#include "encoded_sequence_proxy.h"

template <class init_elem_t_, class encoded_elem_t_>
class RawEncodedSequencesList {
 public:
  using init_elem_t = init_elem_t_;
  using encoded_elem_t = encoded_elem_t_;
  using Entry = EncodedSequenceProxy<RawEncodedSequencesList>;

  RawEncodedSequencesList(
      std::vector<encoded_elem_t> &&items,
      std::vector<std::size_t> &&sequenceStarts,
      const std::vector<init_elem_t> &elemDecoder,
      encoded_elem_t invalidElemCode,
      bool allElementsAllowed)
      : _items(std::move(items)),
        _sequenceStarts(std::move(sequenceStarts)),
        _elemDecoder(elemDecoder),
        _invalidElemCode(invalidElemCode),
        _allElementsAllowed(allElementsAllowed) {
  }

  RawEncodedSequencesList() = delete;

  RawEncodedSequencesList(const RawEncodedSequencesList &) = delete;

  RawEncodedSequencesList(RawEncodedSequencesList &&) = default;

  RawEncodedSequencesList &operator=(const RawEncodedSequencesList &other) = default;

  RawEncodedSequencesList &operator=(RawEncodedSequencesList &&other) = default;

  inline Entry operator[](std::size_t sequenceNum) const {
    return Entry(sequenceNum, *this);
  }

  inline encoded_elem_t getElem(std::size_t sequenceNum,
                                std::size_t offset) const {
    return _items[_getRawIndex(sequenceNum, offset)];
  }

  inline init_elem_t decode(std::size_t sequenceNum,
                            std::size_t offset) const {
    return _elemDecoder[getElem(sequenceNum, offset)];
  }

  inline std::size_t getSequenceSize(std::size_t sequenceNum) const {
    return _sequenceStarts[sequenceNum + 1] - _sequenceStarts[sequenceNum];
  }

  inline std::size_t size() const {
    return _sequenceStarts.size() - 1;
  }

  inline bool isAllowed(std::size_t sequenceNum,
                        std::size_t offset) const {
    return areAllElementsAllowed() || getElem(sequenceNum, offset) != _invalidElemCode;
  }

  inline bool areAllElementsAllowed() const {
    return _allElementsAllowed;
  }

 private:
  std::vector<encoded_elem_t> _items;
  std::vector<std::size_t> _sequenceStarts;
  const std::vector<init_elem_t> &_elemDecoder;
  const encoded_elem_t _invalidElemCode;
  bool _allElementsAllowed;

  inline std::size_t _getRawIndex(std::size_t sequenceNum,
                                  std::size_t offset) const {
    return _sequenceStarts[sequenceNum] + offset;
  }
};
