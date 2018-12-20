/**
 * @file prelude.hpp
 * @brief どのコードでも必ず使うだろうものを宣言またはインクルードする。
 * `procon-assistant init` で生成されるファイルのテンプレートにはデフォルトで
 * `#include "prelude.hpp"`が含まれている。また、全ての他のヘッダはこのファイ
 * ルはインクルードされているものとしてよい。(もちろん各ヘッダがそれぞれ自分で
 * インク ルードすることを推奨する。)
 */
#pragma once

using ll  = long long;
using ull = unsigned long long;

#include "globals.hpp"
#include "util/alias.hpp"
#include "util/stream/overloads.hpp"
