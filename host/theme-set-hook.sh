#!/usr/bin/env bash
set -euo pipefail

colors="$HOME/.local/state/omarchy/current/theme/colors.toml"
helper="$HOME/.local/bin/omarchy-sofle-rgb"

[[ -r $colors && -x $helper ]] || exit 0

accent=$(sed -nE 's/^accent = "#([[:xdigit:]]{6})"$/\1/p' "$colors")
[[ $accent =~ ^[[:xdigit:]]{6}$ ]] || exit 0

"$helper" "#$accent" >/dev/null 2>&1 || true
