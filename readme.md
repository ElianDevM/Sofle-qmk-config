# Sofle RGB — keymap de Rorschard

Keymap personal para Sofle RGB (QMK, `sofle/rev1`) pensado para Omarchy y trabajo de código.

## Capas

| Capa | Cómo se activa |
|---|---|
| `QWERTY` (base) | — |
| `LOWER` | pulgar izquierdo `LOWER` |
| `RAISE` | pulgar derecho `RAISE` |
| `NUMPAD` | pulgar derecho `NUMPAD` |
| `ADJUST` | `LOWER` + `RAISE` (tri-layer) |

Cada tecla `LOWER`/`RAISE` se mantiene; al soltarlas se sale de la capa. `ADJUST` sólo existe mientras ambas están pulsadas.

## QWERTY

```
,-------------------------------------------.                  ,-----------------------------------------.
| Compose |  1  |  2  |  3  |  4  |  5  |                  |  6  |  7  |  8  |  9  |  0  | Bspc |
|---------+-----+-----+-----+-----+-----|                  |-----+-----+-----+-----+-----+------|
|   TAB   |  Q  |  W  |  E  |  R  |  T  |                  |  Y  |  U  |  I  |  O  |  P  |  `   |
|---------+-----+-----+-----+-----+-----|                  |-----+-----+-----+-----+-----+------|
|CTRL-ESC |  A  |  S  |  D  |  F  |  G  |------.    ,------|  H  |  J  |  K  |  L  |  ;  |  '   |
|---------+-----+-----+-----+-----+-----|Click |    |CtrlF |-----+-----+-----+-----+-----+------|
|  LSFT   |  Z  |  X  |  C  |  V  |  B  |------|    |------|  N  |  M  |  ,  |  .  |  /  | RSFT |
`---------------------------------------/      /    \      \---------------------------------------'
          |CapsWd| WIN | LAlt |LOWER| /Space/       \Enter\ |RAISE|NUMPAD| RAlt | Menu |
          `----------------------------'             '-------''----------------------------'
```

- `Compose` es la tecla Caps del teclado físico (`compose:caps` en Hyprland).
- `WIN` y `Enter` son `GUI_T(KC_ENT)` en ambos pulgares: pulsación corta = Enter, mantener = Super. Así `Super+Enter` funciona desde los dos lados.
- `Ctrl+Esc` en la A (`LCTL_T(KC_ESC)`).

## LOWER — navegación y edición

| Fila | Izquierda | Derecha |
|---|---|---|
| Números | dígitos (transparentes) | `Delete` |
| QWERTY | `Ctrl+Home`, `Ctrl+End`, `Ctrl+Shift+←`, `Ctrl+Shift+→`, `Ctrl+0` | `Home`, `↑`, `End`, `PrtSc` |
| Home | `Ctrl+Bspc`, `Ctrl+Del` | `Ctrl+←`, `←`, `↓`, `→`, `Ctrl+→`, `Insert` |
| Z | — | `Backspace`, `Delete` |

## RAISE — símbolos en la mano izquierda

| Fila | Izquierda | Derecha |
|---|---|---|
| Números | `~ ! @ # $ %` | `^ & * ( ) _` |
| QWERTY | `{ } [ ] *` | — |
| Home | `( ) = + -` | — |
| Z | `\ \| < > :` | — |

`Ctrl+X`, `Ctrl+C` y `Ctrl+V` quedan libres: ya no se reasignan. `Tab`, `Ctrl+Esc`, `Shift` y los pulgares pasan transparentes.

## NUMPAD

- `F1`–`F12` en la mitad izquierda.
- Bloque numérico a la derecha, con `7-8-9 / 4-5-6 / 0-1-2-3` alineado.
- `Mute`, `Numpad Enter`, `.`, `+ - * /`.

## ADJUST — RGB y boot

- Brillo de pantalla: `BRIU`/`BRID`.
- RGB: tono, saturación y valor (arriba/abajo).
- `QK_BOOT` en la esquina superior derecha, lejos de los controles RGB.

## Encoders

Convención: **horario = siguiente / derecha / arriba / subir**.

| Capa | Giro izquierdo | Pulsar izquierdo | Giro derecho | Pulsar derecho |
|---|---|---|---|---|
| QWERTY | `Alt+Tab` / `Alt+Shift+Tab` | clic central | scroll ↑ / ↓ | `Ctrl+F` |
| LOWER | `Ctrl+Tab` / `Ctrl+Shift+Tab` | `Ctrl+W` | `PgUp` / `PgDn` | `Ctrl+T` |
| RAISE | `Ctrl+Z` / `Ctrl+Y` | `?` | zoom `Ctrl+=` / `Ctrl+-` | `Ctrl+S` |
| NUMPAD | volumen ↑ / ↓ | `Mute` | media siguiente / anterior | `Play/Pause` |
| ADJUST | tono ↑ / ↓ | siguiente efecto | brillo ↑ / ↓ | encender/apagar |

`Alt+Tab` usa `KC_LALT` (el Alt derecho es AltGr en esta máquina y no dispara el atajo de Omarchy). La dirección se puede invertir con `ENCODER_DIRECTION_FLIP` en `config.h`.

## RGB sincronizado con el tema de Omarchy

- `config.h` define `RAW_USAGE_PAGE 0xFF60` y `RAW_USAGE_ID 0x61`.
- El helper `host/omarchy-sofle-rgb.c` envía por Raw HID el paquete `0xA1`, hue, saturación.
- El firmware **ignora el byte de brillo** y conserva el brillo que fijaste con el encoder o las teclas: cambiar de tema nunca lo baja.
- En capas distintas de QWERTY se atenúan los LEDs normales (el efecto sigue visible) y se encienden unos marcadores con el acento del tema al brillo actual. Funciona con color sólido y con animaciones.

## Pantallas OLED

- **Esclavo (horizontal 128×32)**: el logo Berserk 2 segundos al encender y después un panel con capa activa, número de efecto RGB, tono y una barra de tono con el brillo actual.
- **Maestro (vertical 32×128)**: iniciales, capa activa, modificadores pulsados, indicador `CW ON` cuando Caps Word está activo y WPM.

El panel del esclavo recibe la capa y la configuración RGB por el enlace split, así que refleja lo que hagas en el maestro.

## Compilar

```bash
cd ~/qmk_firmware
qmk compile -kb sofle/rev1 -km elianSofle -t elf \
  -e BUILD_DIR=/tmp/sofle-build -e ALLOW_WARNINGS=yes
avr-objcopy -O ihex -R .eeprom \
  /tmp/sofle-build/sofle_rev1_elianSofle.elf sofle_rev1_elianSofle.hex
```

El keymap vive en `~/qmk_firmware/keyboards/sofle/keymaps/elianSofle`, que es un symlink a este repo.

## Flashear

Desconecta el cable TRRS y flashea **una mitad cada vez**:

```bash
cd ~/qmk_firmware
qmk flash --bootloader avrdude-split-left  sofle_rev1_elianSofle.hex
qmk flash --bootloader avrdude-split-right sofle_rev1_elianSofle.hex
```

Pulsa Reset en cuanto el comando entre en modo bootloader (la ventana es corta).
