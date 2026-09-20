#pragma once

namespace miit::algebra {
class Generator {
public:
    virtual ~Generator() = 0;
    virtual int generate() = 0;
};
}
