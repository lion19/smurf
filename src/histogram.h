#pragma once
#include <chrono>
#include <hdr/hdr_histogram.h>

namespace smf {
  class histogram;
  struct histogram_measure;
}

namespace smf {
/// brief - simple wrapper for hdr_histogram_c project
///
class histogram {
  public:
  histogram();
  void record(const uint64_t &v);
  void record_multiple_times(const uint64_t &v, const uint32_t &times);
  void record_corrected(const uint64_t &v, const uint64_t &interval);
  size_t memory_size();
  const struct hdr_histogram *get() const;
  void operator+=(const histogram &o);

  struct histogram_measure auto_measure();

  ~histogram();

  private:
  struct hdr_histogram *hist_;
};
/// simple struct that records the measurement at the dtor
/// similar to boost_scope_exit;
struct histogram_measure {
  histogram_measure(histogram *hist)
    : h(hist), begin_t(std::chrono::high_resolution_clock::now()) {}
  ~histogram_measure() {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      std::chrono::high_resolution_clock::now() - begin_t)
                      .count();
    h->record(duration);
  }
  histogram *h;
  std::chrono::high_resolution_clock::time_point begin_t;
};
}
