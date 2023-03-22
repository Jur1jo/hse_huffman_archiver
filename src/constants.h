#pragma once

#include <cstdint>
#include <cstdio>

using CharType = int;  // Так как хоть убей не могу понять, откуда warning на 24 строчке в buffer.cpp при int16
const int CHAR_LENGTH = 8;
const int BIT_LENGTH = 8;
const CharType FILENAME_END = 256;
const CharType ONE_MORE_FILE = 257;
const CharType ARCHIVE_END = 258;
const CharType NON_TERMINAL = 259;