#pragma once

namespace sparks {
struct RendererSettings {
  int num_samples{1024};
  int num_bounces{16};
};
}  // namespace sparks
