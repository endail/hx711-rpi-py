
#yum check-update -y
#yum update -y
#yum install -y "kernel-devel-uname-r == $(uname -r)"

apt-get update && apt-get install -y --no-install-recommends apt-utils
apt-get update -y
apt-get upgrade -y
apt-get dist-upgrade -y
apt full-upgrade -y
apt-get install gpiod libgpiod-dev libgpiod-doc
apt-get install ligpiod2 libgpiod2-dev

git clone --depth 1 --branch v0.1 https://github.com/joan2937/lg
cd lg
make && sudo make install
cd ..

#sudo ldconfig
#sudo chown -R $USER:$USER /home/runner/work

git clone https://github.com/endail/hx711
cd hx711
make && sudo make install
cd ..

#sudo sh -c "echo '/usr/local/lib' >> /etc/ld.so.conf"
sudo ldconfig
#sudo chown -R $USER:$USER /home/runner/work
