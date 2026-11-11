# Firmware precompilado

- Archivo: `sofle_rev1_elianSofle.hex`
- Teclado: `sofle/rev1`
- Keymap: `elianSofle`
- Código: el de este repo (commit `437cc89`; el fuente del keymap no cambió después)
- Tamaño: 28 492 / 28 672 bytes (99,4 %, 180 libres)
- SHA256: `d6014345f6f4f9552b10ad5931390c128d61208495801033329ea65672081d3f`

## Flashear en otro equipo (sin compilar)

Requisitos: `avrdude` (Arch: `sudo pacman -S avrdude`).

1. Desconecta el cable TRRS.
2. Conecta por USB **solo la mitad que vas a flashear**.
3. Ejecuta:

   ```bash
   ./firmware/flash.sh
   ```

4. Cuando el script muestre `Esperando el bootloader`, pulsa el botón **Reset** del Pro Micro
   (o mantén `Lower + Raise` y pulsa la tecla superior derecha si tienes las dos mitades unidas por TRRS).
5. Repite los pasos 1-4 con la otra mitad.

También puedes hacerlo a mano si el bootloader ya está en `/dev/ttyACM0`:

```bash
avrdude -p atmega32u4 -c avr109 -P /dev/ttyACM0 \
  -U flash:w:firmware/sofle_rev1_elianSofle.hex
```

> No escribas `eeprom-lefthand.eep` ni `eeprom-righthand.eep`: con `MASTER_LEFT` no hacen falta y
> ponen a cero el *magic* del EEPROM, borrando el color, el brillo y el modo guardados.

## Verificar el archivo

```bash
cd firmware
sha256sum -c SHA256SUMS
```

## Recompilar desde el código

Consulta la sección **Compilar** del `readme.md` principal. El `.hex` se genera con:

```bash
avr-objcopy -O ihex -R .eeprom \
  /tmp/sofle-build/sofle_rev1_elianSofle.elf firmware/sofle_rev1_elianSofle.hex
```
