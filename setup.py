from skbuild import setup


# https://stackoverflow.com/questions/58533084/what-keyword-arguments-does-setuptools-setup-accept

setup(
    name="example",
    version="1.0.56",
    description="a minimal example package",
    author="silviana amethyst",
    license="I have no idea",
    packages=["example"],
    python_requires=">=3.9",
    package_dir={"": "src"},
    cmake_install_dir="src/example",
)