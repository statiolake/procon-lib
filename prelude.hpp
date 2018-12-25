/**
 * @file prelude.hpp
 * @brief どのコードでも必ず使うだろうものを宣言またはインクルードする。
 * `procon-assistant init` で生成されるファイルのテンプレートにはデフォルトで `#include "prelude.hpp"`が含まれている。全ての他のヘッダはこのファイルはインクルードされているものとしてよい。(もちろん各ヘッダがそれぞれ自分でインクルードすることを推奨する。)
 */
#pragma once

using ll  = long long;
using ull = unsigned long long;

#include "globals.hpp"
#include "util/alias.hpp"
#include "util/stream/overloads.hpp"
