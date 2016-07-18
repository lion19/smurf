#include <cstdlib>
#include "histogram.h"

namespace smf {
histogram::histogram() {
  hdr_init(1,                   // Minimum value
           INT64_C(3600000000), // Maximum value
           3,                   // Number of significant figures
           &hist_);             // Pointer to initialise
}
void histogram::record(const uint64_t &v) { hdr_record_value(hist_, v); }

void histogram::record_multiple_times(const uint64_t &v,
                                      const uint32_t &times) {
  hdr_record_values(hist_, v, times);
}

void histogram::record_corrected(const uint64_t &v, const uint64_t &interval) {
  hdr_record_corrected_value(hist_, v, interval);
}

size_t histogram::memory_size() { return hdr_get_memory_size(hist_); }

const struct hdr_histogram *histogram::get() const { return hist_; }

void histogram::operator+=(const histogram &o) { hdr_add(hist_, o.get()); }

struct histogram_measure histogram::auto_measure() {
  return histogram_measure(this);
}

histogram::~histogram() {
  if(hist_) {
    free(hist_);
  }
}
} // end namespace
