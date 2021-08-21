
yum install -y gpiod libgpiod-dev libgpiod-doc

git clone --depth 1 --branch v0.1 https://github.com/joan2937/lg
cd lg
make
make install

#sudo ldconfig
#sudo chown -R $USER:$USER /home/runner/work

git clone https://github.com/endail/hx711
cd hx711
make
make install

#sudo sh -c "echo '/usr/local/lib' >> /etc/ld.so.conf"
#sudo ldconfig
#sudo chown -R $USER:$USER /home/runner/work
