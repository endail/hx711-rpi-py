
yum check-update -y
yum update -y
yum install -y "kernel-devel-uname-r == $(uname -r)"

yum install -y gpiod libgpiod-dev libgpiod-doc

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
