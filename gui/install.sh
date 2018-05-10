#!/usr/bin/env bash

pwd=`pwd`
build_dir="$pwd/build/"

mkdir -p $build_dir
cd godot
godot --export "pck" $build_dir/prologin2018.pck

replay="$build_dir/prologin2018-replay"
echo -e "#!/usr/bin/env sh\n" > $replay
echo "test \$# -eq 0 && echo "Usage: \$0 dump.json" && exit 1" >> $replay
echo "godot --main-pack /opt/prologin2018.pck -json=\$1" >> $replay
chmod +x $replay

gui="$build_dir/prologin2018-gui"
echo -e "#!/usr/bin/env sh\n" > $gui
echo "test \$# -eq 0 && echo "Usage: \$0 socket_port" && exit 1" >> $gui
echo "godot --main-pack /opt/prologin2018.pck -ssockt=\$1" >> $gui
chmod +x $gui

echo "The installer will install two files in /usr/bin and one in /opt"
sudo cp "$gui" "$replay" /usr/bin
sudo cp "$build_dir/prologin2018.pck" /opt

echo "To uninstall:"
echo "sudo rm /usr/bin/prologin2018-{gui,replay} /opt/prologin2018.pck"
