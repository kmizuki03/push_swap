# push_swap

限られた命令セットを用いて、スタック上のデータを最も効率的にソートするプロジェクトです。

## ルール
- `a` と `b` という名前の2つのスタックがあります。
- 開始時、スタック`a`にはユニークな正負の整数がランダムな順序で入っており、スタック`b`は空です。
- 目標は、スタック`a`の数値を昇順にソートすることです。
- 利用できる命令は以下の通りです。
    - `sa`: スタック `a` の先頭2要素を交換します。
    - `sb`: スタック `b` の先頭2要素を交換します。
    - `ss`: `sa` と `sb` を同時に行います。
    - `pa`: スタック `b` の先頭要素を `a` の先頭に置きます。
    - `pb`: スタック `a` の先頭要素を `b` の先頭に置きます。
    - `ra`: スタック `a` の全要素を1つ上にシフトします（先頭が末尾になります）。
    - `rb`: スタック `b` の全要素を1つ上にシフトします。
    - `rr`: `ra` と `rb` を同時に行います。
    - `rra`: スタック `a` の全要素を1つ下にシフトします（末尾が先頭になります）。
    - `rrb`: スタック `b` の全要素を1つ下にシフトします。
    - `rrr`: `rra` と `rrb` を同時に行います。

## `push_swap` プログラム
| 項目 | 内容 |
| :--- | :--- |
| **プログラム名** | push_swap |
| **提出ファイル** | Makefile, *.h, *.c |
| **Makefile** | NAME, all, clean, fclean, re |
| **引数** | スタック `a`: 整数のリスト |
| **許可されている外部関数** | read, write, malloc, free, exit, 自作のft_printfまたはそれに相当する関数 |
| **Libftの使用** | 許可 |
| **説明** | スタックをソートします |

- **引数:** 整数のリストとしてフォーマットされたスタック `a` を引数として受け取ります。最初の引数がスタックの先頭になります。
- **出力:** スタック `a` をソートするために必要な最短の命令シーケンスを、`\n` で区切って表示しなければなりません。
- **目標:** 可能な限り少ない操作回数でスタックをソートすることです。
- **エラー処理:** エラー（引数が整数でない、重複があるなど）の場合、標準エラーに "Error" と改行を表示しなければなりません。
- **引数なし:** パラメータが指定されない場合、プログラムは何も表示せず、プロンプトに戻るべきです。

## ベンチマーク
プロジェクトを検証するためには、以下の操作回数でソートを成功させる必要があります。
- **最高評価（100%）を得るには:**
    - 100個のランダムな数値を700操作未満でソートする。
    - 500個のランダムな数値を5500操作以内でソートする。
- **最低評価（80%）を得るには:** 上記より緩い基準がいくつか設定されています。
