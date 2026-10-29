"""Render PNG cheat sheets from the keymap.c files.

Usage: python tools/cheatsheets.py   (writes docs/cheatsheets/*.png)
Needs Pillow. Labels come from the keymap code, not the ASCII comments.
"""
import colorsys
import re
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "docs" / "cheatsheets"
FONT_DIR = Path("C:/Windows/Fonts")
FONT = str(FONT_DIR / "segoeui.ttf")
FONT_BOLD = str(FONT_DIR / "segoeuib.ttf")
FONT_ICONS = str(FONT_DIR / "SegoeIcons.ttf")   # Segoe Fluent Icons (Windows 11)

U = 96          # pixels per key unit
GAP = 6         # gap between keys
RADIUS = 12

# ---------------------------------------------------------------- colours
LAYERS = [
    ("Basic layer", None, "#5b6b7d"),
    ("Symbol layer", "hold Fn1", "#2f9a5b"),
    ("Function layer", "hold Fn2", "#2f72d0"),
    ("Misc layer", "hold Fn3", "#d9822b"),
]
BASIC_FILLS = {"alpha": "#ffffff", "mod": "#e6e9ee"}   # Basic layer; anything else is white
ICONS = {                    # category: (font file, glyph)
    "symbol": (FONT_BOLD, "#"),
    "fkey":   (FONT_ICONS, ""),   # keyboard
    "media":  (FONT_ICONS, ""),   # speaker
    "window": (FONT_ICONS, ""),   # window
    "mouse":  (FONT_ICONS, ""),   # mouse
    "rgb":    (FONT_ICONS, ""),   # light bulb
    "system": (FONT_ICONS, ""),   # power
}
GROUP_SHADES = {             # category: (hue shift in degrees, amount of white) off the layer colour
    "symbol": (0, 0.84), "mod": (0, 0.92), "fkey": (0, 0.88),
    "media": (15, 0.72), "rgb": (-45, 0.76), "window": (4, 0.80),
    "mouse": (-25, 0.76), "system": (-45, 0.76),
}
GROUP_LAYER = {"system": 3, "fkey": 2}  # categories with one colour on every layer, taken from this layer
LEGEND = {                   # layer: the groups listed after it in the legend
    1: [("symbol", "Symbols")],
    2: [("fkey", "F-keys"), ("rgb", "LEDs"), ("media", "Media"), ("mouse", "Mouse")],
    3: [("window", "Windows shortcuts"), ("system", "System")],
}
BG = "#f6f7f9"
TRANSPARENT_FILL = "#eef0f3"
TRANSPARENT_TEXT = "#b4bac3"
TEXT_DARK = "#1f2328"
TEXT_MUTED = "#6b7280"

# ---------------------------------------------------------------- labels
# Swiss German keycodes (QMK keymap_swiss_de.h) and the character each one types
CH_BASE = {
    "CH_SECT": "§", "CH_QUOT": "'", "CH_CIRC": "^", "CH_UDIA": "Ü", "CH_DIAE": "¨",
    "CH_ODIA": "Ö", "CH_ADIA": "Ä", "CH_DLR": "$", "CH_LABK": "<", "CH_COMM": ",",
    "CH_DOT": ".", "CH_MINS": "-",
}
CH_SYMBOLS = {  # typed with Shift or AltGr
    "CH_DEG": "°", "CH_PLUS": "+", "CH_DQUO": '"', "CH_ASTR": "*", "CH_CCED": "ç",
    "CH_PERC": "%", "CH_AMPR": "&", "CH_SLSH": "/", "CH_LPRN": "(", "CH_RPRN": ")",
    "CH_EQL": "=", "CH_QUES": "?", "CH_GRV": "`", "CH_EGRV": "è", "CH_EXLM": "!",
    "CH_EACU": "é", "CH_AGRV": "à", "CH_PND": "£", "CH_RABK": ">", "CH_SCLN": ";",
    "CH_COLN": ":", "CH_UNDS": "_", "CH_BRKP": "¦", "CH_AT": "@", "CH_HASH": "#",
    "CH_NOT": "¬", "CH_PIPE": "|", "CH_CENT": "¢", "CH_ACUT": "´", "CH_TILD": "~",
    "CH_EURO": "€", "CH_LBRC": "[", "CH_RBRC": "]", "CH_LCBR": "{", "CH_RCBR": "}",
    "CH_BSLS": "\\",
}
NAMED = {
    "KC_TAB": ("Tab", "mod"), "KC_LSFT": ("Shift", "mod"), "KC_RSFT": ("Shift", "mod"),
    "KC_LALT": ("Alt", "mod"), "KC_LCTL": ("Ctrl", "mod"), "KC_LGUI": ("Gui", "mod"),
    "KC_BSPC": ("Bksp", "mod"), "KC_DEL": ("Del", "mod"), "KC_ENT": ("Enter", "mod"),
    "KC_SPC": ("Space", "mod"), "KC_HOME": ("Home", "mod"), "KC_END": ("End", "mod"),
    "KC_PGUP": ("PgUp", "mod"), "KC_PGDN": ("PgDn", "mod"),
    "KC_LEFT": ("←", "mod"), "KC_RGHT": ("→", "mod"), "KC_RIGHT": ("→", "mod"),
    "KC_UP": ("↑", "mod"), "KC_DOWN": ("↓", "mod"),
    "LCTL_T(KC_ESC)": ("Esc /\nCtrl", "mod"), "RCTL_T(KC_ESC)": ("Esc /\nCtrl", "mod"),
    "GRV_TLD": ("` ~", "alpha"), "CIRC": ("^", "symbol"),
    "KC_PSCR": ("PrtSc", "mod"), "KC_BRK": ("Pause", "mod"), "KC_PAUS": ("Pause", "mod"),
    "KC_SCRL": ("ScrLk", "mod"),
    "KC_MPRV": ("Prev", "media"), "KC_MNXT": ("Next", "media"), "KC_MPLY": ("Play", "media"),
    "KC_MUTE": ("Mute", "media"), "KC_VOLU": ("Vol +", "media"), "KC_VOLD": ("Vol −", "media"),
    "MS_BTN1": ("Left\nclick", "mouse"), "MS_BTN2": ("Right\nclick", "mouse"),
    "MS_UP": ("Mouse\n↑", "mouse"), "MS_DOWN": ("Mouse\n↓", "mouse"),
    "MS_LEFT": ("Mouse\n←", "mouse"), "MS_RGHT": ("Mouse\n→", "mouse"),
    "RGB_TOG": ("LEDs\non/off", "rgb"), "RGB_MOD": ("Effect\nnext", "rgb"),
    "RGB_RMOD": ("Effect\nprev", "rgb"), "RGB_VAI": ("Bright\n+", "rgb"),
    "RGB_VAD": ("Bright\n−", "rgb"), "RGB_SPI": ("Speed\n+", "rgb"), "RGB_SPD": ("Speed\n−", "rgb"),
    "RGB_HUI": ("Hue +", "rgb"), "RGB_HUD": ("Hue −", "rgb"), "RGB_SAI": ("Sat +", "rgb"),
    "RGB_SAD": ("Sat −", "rgb"), "RGB_M_B": ("Breathe", "rgb"), "LED_AREA": ("LED\narea", "rgb"),
    "MISC_FN2": ("Fn2", "layer2"),
    "LM_TOGG": ("Backlight\non/off", "rgb"), "LM_BRIU": ("Backlight\n+", "rgb"),
    "LM_BRID": ("Backlight\n−", "rgb"),
    "BREATHE": ("Breathe", "rgb"), "LM_PREV": ("Effect\nprev", "rgb"), "LM_NEXT": ("Effect\nnext", "rgb"),
    "QK_BOOT": ("Reset", "system"), "VRSN": ("Version", "system"), "NK_TOGG": ("NKRO", "system"),
    "LAUNCHER": (("Ctrl+Shift+Space\nLauncher", "Ctrl+Shift\n+Space\nLauncher"), "window"),
    "C(S(CH_M))": ("Teams\nmute", "media"), "C(S(CH_O))": ("Teams\ncamera", "media"),
    "C(S(CH_P))": ("Teams\nblur", "media"),
    "C(S(KC_ESC))": ("Task\nmanager", "window"),
}
ARROWS = {"KC_LEFT": "←", "KC_RIGHT": "→", "KC_RGHT": "→", "KC_UP": "↑", "KC_DOWN": "↓"}
GUI_ACTIONS = {  # what Gui+key does in Windows 11
    "CH_A": "Quick\nsettings", "CH_C": "Copilot", "CH_D": "Desktop", "CH_E": "Explorer",
    "CH_I": "Settings", "CH_L": "Lock", "CH_M": "Min. all", "CH_R": "Run", "CH_V": "Clipboard",
    "KC_UP": "Maximize", "KC_DOWN": "Minimize", "KC_LEFT": "Snap", "KC_RIGHT": "Snap",
}


def base_char(kc):
    if kc in CH_BASE:
        return CH_BASE[kc]
    m = re.fullmatch(r"CH_([A-Z0-9])", kc)
    return m.group(1) if m else None


def label(kc):
    """Return (text, category) for a keycode; category None = layer key."""
    if kc in NAMED:
        return NAMED[kc]
    if m := re.fullmatch(r"MO\((\d)\)", kc):
        return f"Fn{m.group(1)}", f"layer{m.group(1)}"
    if m := re.fullmatch(r"KC_F(\d+)", kc):
        return f"F{m.group(1)}", "fkey"
    if kc in CH_SYMBOLS:
        return CH_SYMBOLS[kc], "symbol"
    if m := re.fullmatch(r"G\((\w+)\)", kc):
        k = m.group(1)
        text = "Gui+" + (ARROWS.get(k) or base_char(k))
        if k in GUI_ACTIONS:
            text += "\n" + GUI_ACTIONS[k]
        return text, "window"
    if m := re.fullmatch(r"C\(S\((\w+)\)\)", kc):
        return "Ctrl+Shift\n+" + base_char(m.group(1)), "window"
    if (c := base_char(kc)) is not None:
        return c, "alpha"
    raise KeyError(f"no label for {kc}")


# ---------------------------------------------------------------- keymap parsing
def parse_keymap(path):
    src = path.read_text(encoding="utf-8")
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    src = re.sub(r"//[^\n]*", "", src)
    layers = {}
    for m in re.finditer(r"\[(\d)\]\s*=\s*LAYOUT\w*\(", src):
        i, depth, start = m.end(), 1, m.end()
        while depth:
            depth += {"(": 1, ")": -1}.get(src[i], 0)
            i += 1
        body = src[start:i - 1]
        keys, depth, cur = [], 0, ""
        for ch in body:
            if ch == "," and depth == 0:
                keys.append(cur.strip())
                cur = ""
                continue
            depth += {"(": 1, ")": -1}.get(ch, 0)
            cur += ch
        if cur.strip():
            keys.append(cur.strip())
        layers[int(m.group(1))] = [re.sub(r"\s+", "", k) for k in keys]
    return [layers[i] for i in sorted(layers)]


# ---------------------------------------------------------------- geometries
def preonic_geometry():
    return [(c, r, 1, 1) for r in range(5) for c in range(12)]


ALT_KEYS = [
    (0, 0, 1), (1, 0, 1), (2, 0, 1), (3, 0, 1), (4, 0, 1), (5, 0, 1), (6, 0, 1), (7, 0, 1), (8, 0, 1),
    (9, 0, 1), (10, 0, 1), (11, 0, 1), (12, 0, 1), (13, 0, 2), (15, 0, 1),
    (0, 1, 1.5), (1.5, 1, 1), (2.5, 1, 1), (3.5, 1, 1), (4.5, 1, 1), (5.5, 1, 1), (6.5, 1, 1),
    (7.5, 1, 1), (8.5, 1, 1), (9.5, 1, 1), (10.5, 1, 1), (11.5, 1, 1), (12.5, 1, 1), (13.5, 1, 1.5),
    (15, 1, 1),
    (0, 2, 1.75), (1.75, 2, 1), (2.75, 2, 1), (3.75, 2, 1), (4.75, 2, 1), (5.75, 2, 1), (6.75, 2, 1),
    (7.75, 2, 1), (8.75, 2, 1), (9.75, 2, 1), (10.75, 2, 1), (11.75, 2, 1), (12.75, 2, 2.25), (15, 2, 1),
    (0, 3, 2.25), (2.25, 3, 1), (3.25, 3, 1), (4.25, 3, 1), (5.25, 3, 1), (6.25, 3, 1), (7.25, 3, 1),
    (8.25, 3, 1), (9.25, 3, 1), (10.25, 3, 1), (11.25, 3, 1), (12.25, 3, 1.75), (14, 3, 1), (15, 3, 1),
    (0, 4, 1.25), (1.25, 4, 1.25), (2.5, 4, 1.25), (3.75, 4, 6.25), (10, 4, 1.25), (11.25, 4, 1.25),
    (13, 4, 1), (14, 4, 1), (15, 4, 1),
]


def alt_geometry():
    return [(x, y, w, 1) for x, y, w in ALT_KEYS]


def ergodox_geometry():
    col_x = [0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5]
    col_w = [1.5, 1, 1, 1, 1, 1, 1]
    stagger = [0.375, 0.375, 0.125, 0, 0.125, 0.25, 0.25]

    def key(c, y, h=1):
        return (col_x[c], y + stagger[c], col_w[c], h)

    left = []
    left += [key(c, 0) for c in range(7)]
    left += [key(c, 1) for c in range(6)] + [key(6, 1, 1.5)]
    left += [key(c, 2) for c in range(6)]
    left += [key(c, 3) for c in range(6)] + [key(6, 2.5, 1.5)]
    bottom = [(0.5, 0.375), (1.5, 0.375), (2.5, 0.125), (3.5, 0), (4.5, 0.125)]
    bottom_keys = [(x, 4 + s, 1, 1) for x, s in bottom]
    left += bottom_keys
    tx, ty = [5.0, 6.0, 7.0], 5.6
    thumbs = [(tx[1], ty, 1, 1), (tx[2], ty, 1, 1), (tx[2], ty + 1, 1, 1),
              (tx[0], ty + 1, 1, 2), (tx[1], ty + 1, 1, 2), (tx[2], ty + 2, 1, 1)]
    left += thumbs

    width = 2 * 8.0 + 1.5

    def mirror(k):
        x, y, w, h = k
        return (width - x - w, y, w, h)

    right = []
    right += [mirror(key(c, 0)) for c in reversed(range(7))]
    right += [mirror(key(6, 1, 1.5))] + [mirror(key(c, 1)) for c in reversed(range(6))]
    right += [mirror(key(c, 2)) for c in reversed(range(6))]
    right += [mirror(key(6, 2.5, 1.5))] + [mirror(key(c, 3)) for c in reversed(range(6))]
    right += [mirror(k) for k in reversed(bottom_keys)]
    right += [mirror(thumbs[1]), mirror(thumbs[0]), mirror(thumbs[2]),
              mirror(thumbs[5]), mirror(thumbs[4]), mirror(thumbs[3])]
    return left + right


KEYBOARDS = [
    ("Preonic", "preonic", ROOT / "layouts/ortho_5x12/swissgerman_programmer/keymap.c", preonic_geometry),
    ("Drop ALT", "drop_alt", ROOT / "keyboards/massdrop/alt/keymaps/swissgerman_programmer/keymap.c", alt_geometry),
    ("ErgoDox / ErgoDox Infinity", "ergodox", ROOT / "layouts/ergodox/swissgerman_programmer/keymap.c", ergodox_geometry),
]


# ---------------------------------------------------------------- drawing
_fonts = {}


def font(size, bold=False, path=None):
    path = path or (FONT_BOLD if bold else FONT)
    key = (size, path)
    if key not in _fonts:
        _fonts[key] = ImageFont.truetype(path, size)
    return _fonts[key]


def mix(color, other, amount):
    """Blend two #rrggbb colours; amount 0 = color, 1 = other."""
    a = [int(color[i:i + 2], 16) for i in (1, 3, 5)]
    b = [int(other[i:i + 2], 16) for i in (1, 3, 5)]
    return "#" + "".join(f"{round(x + (y - x) * amount):02x}" for x, y in zip(a, b))


def shift_hue(color, degrees):
    r, g, b = (int(color[i:i + 2], 16) / 255 for i in (1, 3, 5))
    h, l, s = colorsys.rgb_to_hls(r, g, b)
    r, g, b = colorsys.hls_to_rgb((h + degrees / 360) % 1, l, s)
    return "#" + "".join(f"{round(c * 255):02x}" for c in (r, g, b))


def key_colours(n, cat="symbol"):
    """fill, text, outline for a key of category cat on layer n: a variation of the layer colour."""
    shift, white = GROUP_SHADES.get(cat, (0, 0.84))
    accent = shift_hue(LAYERS[GROUP_LAYER.get(cat, n)][2], shift)
    return mix(accent, "#ffffff", white), mix(accent, "#000000", 0.55), mix(accent, "#ffffff", white - 0.3)


def draw_glyph(draw, xy, glyph, size, color, anchor="lt"):
    """Draw a glyph so its ink box sits at xy (anchor: l/m/r + t/m/b)."""
    path, ch = glyph
    f = font(size, path=path)
    x0, y0, x1, y1 = f.getbbox(ch)
    x = xy[0] - {"l": x0, "m": (x0 + x1) / 2, "r": x1}[anchor[0]]
    y = xy[1] - {"t": y0, "m": (y0 + y1) / 2, "b": y1}[anchor[1]]
    draw.text((x, y), ch, font=f, fill=color)
    return x1 - x0


def text_height(lines, sizes, descender=True):
    """Height from the cap top of the first line to the baseline (or descender) of the last one."""
    fonts = [font(s) for s in sizes]
    h = -fonts[0].getbbox("A", anchor="ls")[1]
    h += sum(f.getbbox("A")[3] + 2 for f in fonts[1:])
    return h + (fonts[-1].getmetrics()[1] if descender else 0)


def fit_lines(draw, lines, max_w, max_h, start):
    """Font size per line: all lines share the largest size whose height fits,
    then a line that is too wide shrinks on its own."""
    size = start
    while size > 10 and text_height(lines, [size] * len(lines)) > max_h:
        size -= 1
    sizes = []
    for line in lines:
        s = size
        while s > 10 and draw.textlength(line, font=font(s)) > max_w:
            s -= 1
        sizes.append(s)
    return sizes


def fit_key_text(draw, text, max_w, max_h):
    lines = text.splitlines()
    longest = max(len(line) for line in lines)
    start = int(U * (0.36 if longest == 1 else 0.27 if longest <= 3 else 0.23))
    return lines, fit_lines(draw, lines, max_w, max_h, start)


def draw_key(draw, rect, text, fill, color, outline=None, bold=False, width=2,
             corner=None, corner_color=None):
    """text may be a tuple of alternative wrappings; the one whose smallest line is largest wins.
    corner: Basic-layer key label drawn top right."""
    x0, y0, x1, y1 = rect
    draw.rounded_rectangle(rect, RADIUS, fill=fill, outline=outline or "#c9ced6", width=width)
    pad, small = 10, int(U * 0.22)
    top = 0
    if corner:
        draw_glyph(draw, (x1 - pad, y0 + pad - 2), (FONT_BOLD, corner), small, corner_color, "rt")
        top = small + 2
    if not text:
        return
    variants = [text] if isinstance(text, str) else text
    fits = [fit_key_text(draw, t, x1 - x0 - 2 * pad, y1 - y0 - 2 * pad - top) for t in variants]
    lines, sizes = max(fits, key=lambda ls: min(ls[1]))
    fonts = [font(s, bold) for s in sizes]
    cx, cy = (x0 + x1) / 2, (y0 + top + y1) / 2
    baseline = cy - text_height(lines, sizes, descender=False) / 2 -fonts[0].getbbox("A", anchor="ls")[1]
    for i, (line, f) in enumerate(zip(lines, fonts)):
        if i:
            baseline += f.getbbox("A")[3] + 2
        draw.text((cx, baseline), line, font=f, fill=color, anchor="ms")


def render_layer(layers, n, geometry):
    keys = layers[n]
    extent_w = max(x + w for x, y, w, h in geometry)
    extent_h = max(y + h for x, y, w, h in geometry)
    header = 70
    img = Image.new("RGB", (int(extent_w * U) + 40, int(extent_h * U) + header + 30), BG)
    d = ImageDraw.Draw(img)
    name, how, accent = LAYERS[n]
    d.rounded_rectangle((20, 14, 34, 56), 4, fill=accent)
    d.text((48, 35), name, font=font(34, bold=True), fill=TEXT_DARK, anchor="lm")
    if how:
        tw = d.textlength(name, font=font(34, bold=True))
        d.text((48 + tw + 18, 37), how, font=font(26), fill=TEXT_MUTED, anchor="lm")

    for i, (x, y, w, h) in enumerate(geometry):
        rect = (20 + x * U + GAP / 2, header + y * U + GAP / 2,
                20 + (x + w) * U - GAP / 2, header + (y + h) * U - GAP / 2)
        kc = keys[i]
        if kc == "_______":
            base = layers[0][i]
            text, cat = label(base) if base != "_______" else ("", "")
            if n and cat == f"layer{n}":            # the key held to reach this layer
                draw_key(d, rect, f"{text}\nheld", accent, "#ffffff", outline=accent, width=4, bold=True)
            else:
                draw_key(d, rect, text if n else "", TRANSPARENT_FILL, TRANSPARENT_TEXT)
            continue
        text, cat = key_category(kc, n)
        if cat.startswith("layer"):
            name, _, col = LAYERS[int(cat[-1])]
            draw_key(d, rect, f"{text}\n{name.replace(' layer', '')}", col, "#ffffff", bold=True)
        elif n:
            fill, color, outline = key_colours(n, cat)
            draw_key(d, rect, text, fill, color, outline=outline,
                     corner=base_hint(layers[0][i]), corner_color=mix(color, fill, 0.2))
        else:
            draw_key(d, rect, text, BASIC_FILLS.get(cat, "#ffffff"), TEXT_DARK)
    return img


def key_category(kc, n):
    text, cat = label(kc)
    if n and cat == "alpha":                        # plain CH key placed on a symbol layer
        cat = "symbol"
    return text, cat


def base_hint(kc):
    """Short label of the Basic-layer key at this position, or None."""
    if kc == "_______":
        return None
    text, cat = label(kc)
    if cat.startswith("layer") or not isinstance(text, str) or "\n" in text or len(text) > 4:
        return None
    return text.strip()


def render_keyboard(title, layers, geometry):
    panels = [render_layer(layers, n, geometry) for n in range(4)]
    pw, ph = panels[0].size
    margin, title_h, legend_h = 30, 90, 80
    W = 2 * pw + 3 * margin
    H = title_h + 2 * ph + 3 * margin + legend_h
    sheet = Image.new("RGB", (W, H), BG)
    d = ImageDraw.Draw(sheet)
    d.text((margin + 10, title_h / 2 + 10), title, font=font(48, bold=True), fill=TEXT_DARK, anchor="lm")
    d.text((W - margin - 10, title_h / 2 + 10), "Swiss German programmer layout",
           font=font(28), fill=TEXT_MUTED, anchor="rm")
    for n, p in enumerate(panels):
        x = margin + (n % 2) * (pw + margin)
        y = title_h + margin + (n // 2) * (ph + margin)
        sheet.paste(p, (x, y))
        d.rounded_rectangle((x, y, x + pw, y + ph), 16, outline="#dde1e7", width=2)

    legend = render_legend(layers)
    if legend.width > W - 2 * margin - 10:          # narrow sheet: shrink the legend to fit
        scale = (W - 2 * margin - 10) / legend.width
        legend = legend.resize((int(legend.width * scale), int(legend.height * scale)), Image.LANCZOS)
    sheet.paste(legend, (margin + 10, int(H - legend_h / 2 - 10 - legend.height / 2)))
    return sheet


def render_legend(layers):
    """Layer swatches, then per group one chip in each colour it has on this keyboard."""
    img = Image.new("RGB", (4000, 48), BG)
    d = ImageDraw.Draw(img)
    f = font(26)
    y = 24
    caps = f.getbbox("H", anchor="lm")
    ty = y - (caps[1] + caps[3]) / 2                # text anchor that centres the capitals on y

    def entry(x, text):
        d.text((x + 10, ty), text, font=f, fill=TEXT_DARK, anchor="lm")
        return x + 10 + d.textlength(text, font=f) + 40

    x = 0
    for n in range(1, 4):
        fill, color, outline = key_colours(n)
        d.rounded_rectangle((x, y - 18, x + 36, y + 18), 8, fill=fill, outline=outline, width=2)
        d.rounded_rectangle((x + 3, y - 15, x + 9, y + 15), 3, fill=LAYERS[n][2])
        x = entry(x + 36, f"{LAYERS[n][1].replace('hold ', '')}: {LAYERS[n][0].replace(' layer', '')}")
        for cat, text in LEGEND[n]:
            chips = []
            for m in range(1, 4):
                if any(key_category(kc, m)[1] == cat for kc in layers[m] if kc != "_______"):
                    if (c := key_colours(m, cat)) not in chips:
                        chips.append(c)
            if not chips:
                continue
            for fill, color, outline in chips:
                d.rounded_rectangle((x, y - 20, x + 40, y + 20), 8, fill=fill, outline=outline, width=2)
                draw_glyph(d, (x + 20, y), ICONS[cat], 24, color, "mm")
                x += 44
            x = entry(x - 4, text)
        x += 30
    d.rounded_rectangle((x, y - 18, x + 36, y + 18), 8, fill=TRANSPARENT_FILL, outline="#c9ced6", width=2)
    x = entry(x + 36, "Grey text: falls through to the Basic layer")
    return img.crop((0, 0, int(x - 36), 48))


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    for title, slug, path, geo in KEYBOARDS:
        layers = parse_keymap(path)
        geometry = geo()
        for n, keys in enumerate(layers):
            assert len(keys) == len(geometry), f"{slug} layer {n}: {len(keys)} keys, {len(geometry)} positions"
        out = OUT / f"{slug}.png"
        render_keyboard(title, layers, geometry).save(out, optimize=True)
        print(out.relative_to(ROOT))


if __name__ == "__main__":
    main()
