#!/usr/bin/env bash
set -euo pipefail

theme_dir="$HOME/.local/state/omarchy/current/theme"
helper="$HOME/.local/bin/omarchy-sofle-rgb"

[[ -x $helper ]] || exit 0

# Omarchy stages a per-theme keyboard.rgb (generated from the accent unless the
# theme overrides it). Prefer it over colors.toml so custom keyboard colors
# (e.g. Tokyo Night's ff00ff) are respected.
color=""
if [[ -r $theme_dir/keyboard.rgb ]]; then
    raw=$(tr -d '[:space:]' <"$theme_dir/keyboard.rgb")
    if [[ $raw =~ ^#?[[:xdigit:]]{6}$ ]]; then
        color="#${raw#\#}"
    fi
fi

if [[ -z $color ]]; then
    colors="$theme_dir/colors.toml"
    [[ -r $colors ]] || exit 0
    accent=$(sed -nE 's/^accent = "#([[:xdigit:]]{6})"$/\1/p' "$colors")
    [[ $accent =~ ^[[:xdigit:]]{6}$ ]] || exit 0
    color="#$accent"
fi

"$helper" "$color" >/dev/null 2>&1 || true
