#include "pyunrealsdk/pch.h"
#include "unrealsdk/memory.h"


static inline std::optional<uintptr_t>
sigscan_or_none(
    std::vector<uint8_t> &bytes,
    std::vector<uint8_t> &mask
) {
    auto location = unrealsdk::memory::sigscan(
        bytes.data(), mask.data(), bytes.size()
    );
    return location ? std::optional(location) : std::nullopt;
}

static inline std::optional<uintptr_t>
sigscan_or_none(
    std::vector<uint8_t> &bytes,
    std::vector<uint8_t> &mask,
    uintptr_t start,
    size_t size
) {
    auto location = unrealsdk::memory::sigscan(
        bytes.data(), mask.data(), bytes.size(), start, size
    );
    return location ? std::optional(location) : std::nullopt;
}


std::tuple<std::vector<uint8_t>, std::vector<uint8_t>>
convert_bytes_and_mask(py::bytes &py_bytes, std::optional<py::bytes> &py_mask) {
    auto bytes_view = std::string_view(py_bytes);
    std::vector<uint8_t> bytes(bytes_view.begin(), bytes_view.end());
    std::vector<uint8_t> mask;

    if (py_mask) {
        auto mask_view = std::string_view(*py_mask);
        mask = std::vector<uint8_t>(mask_view.begin(), mask_view.end());
        if (mask.size() != bytes.size())
            throw py::value_error(
                std::format("scan bytes and mask must be the same length")
            );
    }
    else
        mask = std::vector<uint8_t>(bytes.size(), 0xFF);

    return { bytes, mask };
}


std::tuple<std::vector<uint8_t>, std::vector<uint8_t>>
parse_pattern(const std::string& pattern) {
    auto bytes = std::vector<uint8_t>();
    auto mask = std::vector<uint8_t>();
    bool upper_nibble = true;

    for (const auto& character : pattern) {
        if (character == '\0')
            break;

        if (character == ' ')
            continue;

        uint8_t nibble = 0;
        uint8_t nibble_mask = 0;

        if ('0' <= character && character <= '9') {
            nibble = character - '0';
            nibble_mask = 0xF;
        }
        else if ('A' <= character && character <= 'F') {
            nibble = character - 'A' + 0xA;
            nibble_mask = 0xF;
        }
        else if ('a' <= character && character <= 'f') {
            nibble = character - 'a' + 0xA;
            nibble_mask = 0xF;
        }

        if (upper_nibble) {
            bytes.push_back(nibble << 4);
            mask.push_back(nibble_mask << 4);
            upper_nibble = false;
        }
        else {
            bytes.back() |= nibble;
            mask.back() |= nibble_mask;
            upper_nibble = true;
        }
    }

    return { bytes, mask };
}


PYBIND11_MODULE(witch, m)
{
    m.def(
        "sigscan",
        [](py::bytes py_bytes, std::optional<py::bytes> py_mask) {
            auto [bytes, mask] = convert_bytes_and_mask(py_bytes, py_mask);
            return sigscan_or_none(bytes, mask);
        },
        py::arg("bytes"),
        py::arg("mask") = std::nullopt
    );

    m.def(
        "sigscan",
        [](py::bytes py_bytes, std::optional<py::bytes> py_mask, uintptr_t start, size_t size) {
            auto [bytes, mask] = convert_bytes_and_mask(py_bytes, py_mask);
            return sigscan_or_none(bytes, mask, start, size);
        },
        py::arg("bytes"),
        py::arg("mask") = std::nullopt,
        py::kw_only(),
        py::arg("start"),
        py::arg("size")
    );

    m.def(
        "sigscan",
        [](const std::string &pattern) {
            auto [bytes, mask] = parse_pattern(pattern);
            return sigscan_or_none(bytes, mask);
        },
        py::arg("pattern")
    );

    m.def(
        "sigscan",
        [](const std::string& pattern, uintptr_t start, size_t size) {
            auto [bytes, mask] = parse_pattern(pattern);
            return sigscan_or_none(bytes, mask, start, size);
        },
        py::arg("pattern"),
        py::kw_only(),
        py::arg("start"),
        py::arg("size")
    );

    m.def(
        "memory_range",
        [](uintptr_t start, size_t size, bool unlock) {
            if (unlock)
                unrealsdk::memory::unlock_range(start, size);
            return py::memoryview::from_memory((void *)start, size, !unlock);
        },
        py::arg("start"),
        py::arg("size"),
        py::arg("unlock") = false
    );
}
