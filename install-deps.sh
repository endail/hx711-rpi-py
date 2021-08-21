
apt-get install gpiod libgpiod-dev libgpiod-doc

git clone https://github.com/joan2937/lg@v0.1
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
