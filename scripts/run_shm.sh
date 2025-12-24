#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

echo "[1/2] Building Shared Memory Chat..."
make -C "$PROJECT_ROOT/shm_chat"

echo
echo "[2/2] How to run:"
echo " Terminal 1:"
echo "   $PROJECT_ROOT/shm_chat/shm_chat 0 elb7ar"
echo " Terminal 2:"
echo "   $PROJECT_ROOT/shm_chat/shm_chat 1 elb7ar2"
