#pragma once
#include "Generator.h"
#include <iosfwd>

namespace miit::algebra {
class IStreamGenerator final : public Generator {
    std::istream& in_;
public:
    explicit IStreamGenerator(std::istream& in);
    int generate() override;
};
}
