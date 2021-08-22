
yum install -y gpiod libgpiod-dev libgpiod-doc

git clone https://github.com/joan2937/lg@v0.1
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
