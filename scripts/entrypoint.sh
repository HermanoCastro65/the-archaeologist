#!/usr/bin/env bash

echo ""
echo "=============================================="
echo "The Archaeologist UI Container"
echo "=============================================="
echo ""
echo "The Python UI is running inside a virtual display (Xvfb)."
echo ""
echo "Because this container is headless, the Tkinter window"
echo "will NOT appear on your host machine."
echo ""
echo "This is expected behaviour."
echo ""
echo "If you want to see the UI, run it on the host machine:"
echo ""
echo "python archaeologist_ui/main.py"
echo ""
echo "Starting UI..."
echo ""

xvfb-run -a python3 archaeologist_ui/main.py