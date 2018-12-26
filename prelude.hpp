/**
 * @file prelude.hpp
 * @brief どのコードでも必ず使うだろうものを宣言またはインクルードする。
 * `procon-assistant init` で生成されるファイルのテンプレートにはデフォルトで
 * `#include
 * "prelude.hpp"`が含まれている。全ての他のヘッダはこのファイルはインクルードされているものとしてよい。(もちろん各ヘッダがそれぞれ自分でインクルードすることを推奨する。)
 */
#pragma once

/// @brief long long 型のエイリアス。多くの箇所で使われる。
using ll = long long;

/// @brief unsigned long long 型のエイリアス。多くの箇所で使われる。
using ull = unsigned long long;

#include "globals.hpp"
#include "util/alias.hpp"
#include "util/stream/overloads.hpp"
