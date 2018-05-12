Prologin 2018 website
=====================

## Replay

The replay works with Godot is webassembly. For this to work, we need a wasm
file from godot. It is commited in `static/godot/prologin2018.wasm`, and was
obtained like this:

    wget https://downloads.tuxfamily.org/godotengine/3.0.2/Godot_v3.0.2-stable_export_templates.tpz
    unzip Godot_v3.0.2-stable_export_templates.tpz templates/webassembly_release.zip
    unzip templates/webassembly_release.zip godot.wasm
    mv godot.wasm static/godot/prologin2018.wasm

Also `webassembly_release.zip` contained a `godot.js` file that was commited
in `static/js`, but with a one line change to fix a bug with absolute path.

So this is already commited so you should not bother with it, unless you have
issues with newer Godot versions.

What you need, and not commited, is a `static/godot/prologin2018.pck`, which
is the game that Godot will play. in `../gui/godot`, run
`godot --export "pck" prologin2018.pck` and you will get the file, that can
then copy.
