#pragma once

using dimension_t = unsigned short;
// needs to fit dimension_t*dimension_t result
using area_t = unsigned int;

/**
 * @brief
 * Wrapper used to make the code more readable
 */
struct Point {
    dimension_t x;
    dimension_t y;
};