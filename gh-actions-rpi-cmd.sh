
# update os
apt-get update -y && apt-get full-upgrade -y

# install needed packages
apt-get install git-all python3-dev python3-setuptools python3-pip python3-venv -y

# install liblgpio and libhx711
./install-deps.sh

# build and package
python3 -m pip install build --user
python3 -m build --sdist --wheel --outdir dist/ .
