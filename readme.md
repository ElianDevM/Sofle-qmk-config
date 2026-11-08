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
- RGB en la matriz: `UG_HUEU`/`UG_HUED`, `UG_SATU`/`UG_SATD`, `UG_VALU`/`UG_VALD`.
- Encoders: izquierdo = tono, derecho = brillo.
- Pulsadores de encoder: izquierdo = siguiente efecto, derecho = encender/apagar.
- Los cambios de tono/brillo del encoder se guardan en EEPROM **al soltar Adjust** (una sola escritura, no una por clic).
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
- El color del tema se **guarda en EEPROM** (sólo cuando cambia respecto al actual), así que al apagar y volver a encender se conserva el último acento en vez de volver al rojo por defecto.
- Los ajustes manuales de tono y brillo se guardan al salir de Adjust, también sin escribir la EEPROM en cada detent.
- En capas distintas de QWERTY se atenúan los LEDs normales (el efecto sigue visible) y se encienden unos marcadores con el color actual al brillo real. Funciona con color sólido y con animaciones.

## Pantallas OLED

- **Maestro (vertical 32×128)**:

  ```
  RORS
  ----
  LYR
  LOWER

  SCAG        <- modificadores pulsados

  CW ON       <- sólo con Caps Word

  WPM
  42
  ```

- **Esclavo (horizontal 128×32)**: logo Berserk 2 segundos al encender y después:

  ```
      SOFLE RGB
  LAYER LOWER
  FX 12  HUE 123
  [######------] V120
  ```

El panel del esclavo recibe la capa y la configuración RGB por el enlace split, así que refleja lo que hagas en el maestro.

Cada línea se dibuja con ancho fijo y **no se limpia el buffer en cada frame**: el driver de QMK refresca un solo bloque por actualización, y limpiar el buffer cada vez reiniciaba la marca de "sucio" y dejaba los bloques inferiores sin actualizar (las partículas del borde inferior).

## Notas de implementación

- `tap_code16()` no puede enviar keycodes cuánticos como `UG_HUEU`: sólo manda el byte bajo (`0x7823` → `0x23` = `6`, `0x7827` → `0x27` = `0`). Por eso los encoders de Adjust llaman directamente a `rgb_matrix_increase_hue_noeeprom()` / `..._val_noeeprom()`.
- `MS_WHLU`/`MS_WHLD` sí funcionan con `tap_code16()` porque su valor (`0x00D9`) cabe en 8 bits y `register_code()` lo reconoce como mouse key.
- Las etiquetas de capa van en flash (`PSTR`) y se leen con `pgm_read_byte`; mezclar `oled_write_*_P` con cadenas en RAM produce los símbolos extraños que aparecieron al principio.

## Compilar

```bash
cd ~/qmk_firmware
qmk compile -kb sofle/rev1 -km elianSofle -t elf \
  -e BUILD_DIR=/tmp/sofle-build -e ALLOW_WARNINGS=yes
avr-objcopy -O ihex -R .eeprom \
  /tmp/sofle-build/sofle_rev1_elianSofle.elf sofle_rev1_elianSofle.hex
avr-size /tmp/sofle-build/sofle_rev1_elianSofle.elf
```

El keymap vive en `~/qmk_firmware/keyboards/sofle/keymaps/elianSofle`, que es un symlink a este repo.

## Flashear

El keymap usa `MASTER_LEFT` (no `EE_HANDS`): la mitad izquierda conectada por USB es siempre la maestra y **no hace falta escribir el EEPROM de handedness**. Por eso se flashea con el objetivo `avrdude` normal, que **no toca la configuración guardada** (color, brillo, modo RGB):

```bash
cd ~/qmk_firmware
qmk flash -kb sofle/rev1 -km elianSofle -bl avrdude -e ALLOW_WARNINGS=yes
```

Desconecta el cable TRRS y flashea **una mitad cada vez**. Pulsa Reset cuando aparezca `Waiting for USB serial port`; la ventana del bootloader es corta. Repite con la otra mitad.

> No uses `avrdude-split-left` / `avrdude-split-right` salvo que cambies a `EE_HANDS`. Esos objetivos escriben `eeprom-lefthand.eep` / `eeprom-righthand.eep`, que ponen a cero el *magic* del EEPROM y hacen que QMK reinicialice toda la configuración en el siguiente arranque: el teclado vuelve al rojo por defecto y pierde el brillo.

## Límites de firmware

Medición actual: **28 492 / 28 672 bytes (99,4 %, 180 libres)**, RAM **72,3 %**.
El máximo es 28 672 porque el bootloader Caterina ocupa los primeros 4 KB.

Para añadir código hay que liberar espacio en `config.h`. El candidato natural es dejar sólo el efecto que usas y quitar los reactivos extra:

```c
// quitar
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
```

Dejando sólo `ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE` se recuperan varios cientos de bytes sin cambiar el efecto que usas a diario.
