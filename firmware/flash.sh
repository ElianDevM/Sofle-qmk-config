#!/usr/bin/env bash
# Flashea una mitad del Sofle con el firmware precompilado.
# Uso: ./firmware/flash.sh
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
hex="$here/sofle_rev1_elianSofle.hex"

if [[ ! -r $hex ]]; then
    echo "No encuentro $hex" >&2
    exit 1
fi

if ! command -v avrdude >/dev/null 2>&1; then
    echo "Falta avrdude. En Arch: sudo pacman -S avrdude" >&2
    exit 1
fi

cat <<'MSG'
Desconecta el TRRS y conecta SOLO la mitad que quieres flashear.
Cuando aparezca "Esperando el bootloader", pulsa Reset en el Pro Micro.
MSG

dev=""
for _ in $(seq 1 300); do
    dev=$(ls -t /dev/ttyACM* 2>/dev/null | head -n1 || true)
    [[ -n $dev ]] && break
    printf '.'
    sleep 1
done
echo

if [[ -z $dev ]]; then
    echo "No apareció el bootloader. Pulsa Reset y vuelve a intentarlo." >&2
    exit 1
fi

echo "Flasheando $hex en $dev"
sleep 2
avrdude -p atmega32u4 -c avr109 -P "$dev" -U flash:w:"$hex"

echo
echo "Listo. Repite con la otra mitad (TRRS desconectado)."
