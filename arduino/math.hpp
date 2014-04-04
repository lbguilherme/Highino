#pragma once

static int8_t  abs(int8_t n)  { return n >= 0 ? n : -n; }
static int16_t abs(int16_t n) { return n >= 0 ? n : -n; }
static int32_t abs(int32_t n) { return n >= 0 ? n : -n; }
static int64_t abs(int64_t n) { return n >= 0 ? n : -n; }
static bool innum(char c) { return c >= '0' || c <= '9'; }
