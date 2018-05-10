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
echo "godot --main-pack /opt/prologin2018.pck -socket=\$1" >> $gui
chmod +x $gui

cd $build_dir
stechec2-generator player prologin2018 .
cp "$pwd/spectator.cc" "$build_dir/cxx/prologin.cc"
make -C $build_dir/cxx

echo "The installer will install 2 files in /usr/bin, and 2 in /opt"
sudo cp "$gui" "$replay" /usr/bin
sudo cp "$build_dir/prologin2018.pck" /opt
sudo cp "$build_dir/cxx/champion.so" /opt/prologin2018-gui.so

echo "To uninstall:"
echo "sudo rm /usr/bin/prologin2018-{gui,replay} /opt/prologin2018{.pck,-gui.so}"
