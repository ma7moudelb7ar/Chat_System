#!/bin/bash
set -e

# ===============================
# Determine script & project path
# ===============================
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

echo "======================================"
echo "[1/2] Building Network Chat (Sockets)"
echo "======================================"

make -C "$PROJECT_ROOT/net_chat"

echo
echo "======================================"
echo "[2/2] How to run the system"
echo "======================================"
echo
echo "Terminal 1 (Server):"
echo "  $PROJECT_ROOT/net_chat/server 5050"
echo
echo "Terminal 2 (Client 1):"
echo "  $PROJECT_ROOT/net_chat/client 127.0.0.1 5050 elb7ar"
echo
echo "Terminal 3 (Client 2):"
echo "  $PROJECT_ROOT/net_chat/client 127.0.0.1 5050 elb7ar2"
echo
echo "======================================"
