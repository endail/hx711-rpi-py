
apt-get update -y
apt-get full-upgrade -y
apt-get install python3-dev git-all python3-setuptools python3-pip python3-venv -y

./install-deps.sh
apt-get autoremove -y

python3 -m pip install build --user
python3 -m build --sdist --wheel --outdir dist/ .