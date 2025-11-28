#!/usr/bin/env bash
set -e

PREFIX="/usr"
APP_NAME="tray-pumpkin"

echo "Installing TrayPumpkin into $PREFIX ..."
echo

# Paths inside TGZ
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BIN_DIR="$ROOT_DIR/bin"
SHARE_DIR="$ROOT_DIR/share"

# Install binary
echo "[1/5] Installing binary..."
install -Dm755 "$BIN_DIR/$APP_NAME" "$PREFIX/bin/$APP_NAME"

# Install desktop file
echo "[2/5] Installing .desktop file..."
install -Dm644 "$SHARE_DIR/applications/tray-pumpkin.desktop" \
    "$PREFIX/share/applications/tray-pumpkin.desktop"

# Install main icon for desktop environment
echo "[3/5] Installing main icon..."
install -Dm644 "$SHARE_DIR/icons/hicolor/48x48/apps/tray-pumpkin.png" \
    "$PREFIX/share/icons/hicolor/48x48/apps/tray-pumpkin.png"

# Install default config (system-wide)
echo "[4/5] Installing default system config..."
install -Dm644 "$SHARE_DIR/tray-pumpkin/default-config.yaml" \
    "$PREFIX/share/tray-pumpkin/default-config.yaml"

# Install tray-pumpkin icon pack
echo "[5/5] Installing tray icon set..."
install -Dm644 "$SHARE_DIR/tray-pumpkin/icons/tray-pumpkin.png" \
    "$PREFIX/share/tray-pumpkin/icons/tray-pumpkin.png"

install -Dm644 "$SHARE_DIR/tray-pumpkin/icons/tray-pumpkin-green.png" \
    "$PREFIX/share/tray-pumpkin/icons/tray-pumpkin-green.png"

# Update icon cache if available
if command -v gtk-update-icon-cache >/dev/null; then
    echo "Updating icon cache..."
    gtk-update-icon-cache -f "$PREFIX/share/icons/hicolor" || true
fi

echo
echo "TrayPumpkin installation completed!"
echo "Run with: tray-pumpkin"
echo
